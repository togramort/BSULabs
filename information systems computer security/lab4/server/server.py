import os
import socket
import rsa
import time
import time
import hashlib
from Crypto.Cipher import AES
from Crypto.Random import get_random_bytes
import jwt

def list_files(directory):
    return [f for f in os.listdir(directory) if os.path.isfile(os.path.join(directory, f))]

def read_file(file_path):
    with open(file_path, 'r') as file:
        line = file.read()
        line = line.split(":")
        return bytes.fromhex(line[0]), bytes.fromhex(line[1])

def encrypt_file_with_aes(plaintext, key):
    cipher = AES.new(key, AES.MODE_CFB)
    ciphertext_bytes = cipher.encrypt(plaintext)
    return ciphertext_bytes, cipher.iv

def decrypt_file_with_aes(ciphertext_bytes, key, iv):
    cipher = AES.new(key, AES.MODE_CFB, iv=iv)
    plaintext_bytes = cipher.decrypt(ciphertext_bytes)
    return plaintext_bytes

def encrypt_aes_key_with_rsa(aes_key, rsa_public_key):
    encrypted_key = rsa.encrypt(aes_key, rsa_public_key)
    return encrypted_key

def receive_public_key(client_socket, username):
    check_token(client_socket, username)
    public_key_bytes = client_socket.recv(2048)
    public_key = rsa.PublicKey.load_pkcs1(public_key_bytes)
    #print("Public key: ", public_key)
    return public_key

def generate_aes_key():
    return get_random_bytes(16)

def handle_client(client_socket, rsa_public_key, aes_key, username):
    file_names = list_files('./server/text_encoded')
    file_list = '\n'.join(file_names)
    client_socket.send(file_list.encode())
    check_token(client_socket, username)
    selected_file_name = client_socket.recv(1024).decode()

    file_path = os.path.join('./server/text_encoded/', selected_file_name)
    bytes_text, iv = read_file(file_path)
    with open('./server/key_for_files.key', 'r') as file:
        key = file.read()
        key = bytes.fromhex(key)
    plaintext = decrypt_file_with_aes(bytes_text, key, iv)
    ciphertext_bytes, iv = encrypt_file_with_aes(plaintext, aes_key)
    encrypted_aes_key = encrypt_aes_key_with_rsa(aes_key, rsa_public_key)

    client_socket.send(ciphertext_bytes)
    client_socket.send(iv)
    client_socket.send(encrypted_aes_key)

def authorize_user(username, password):
    login_string = username + password
    hashed_login = hashlib.sha256(login_string.encode()).hexdigest()

    with open('./server/user_credentials.txt', 'r') as file:
        for line in file:
            stored_hash = line.strip()
            if hashed_login == stored_hash:
                return True
    return False

def generate_token(username):
    with open('./server/token_key.txt', 'r') as file:
        key = file.read()
    payload = {"username": username, "timestamp": time.time()}
    token = jwt.encode(payload, key, algorithm='HS256')
    save_token(token, username)
    return token

def save_token(token, username):
    tokens_path = './server/tokens.txt'
    token_data = username + ':' + token + ':' + str(time.time()) + '\n'
    updated = False

    with open(tokens_path, 'r') as f:
        lines = f.readlines()

    with open(tokens_path, 'w') as f:
        for line in lines:
            parts = line.split(":")
            if len(parts) == 3 and parts[0] == username:
                f.write(token_data)
                updated = True
            else:
                f.write(line)

    if not updated:
        with open(tokens_path, 'a') as f:
            f.write(token_data)

def find_token(username):
    tokens_path = './server/tokens.txt'
    with open(tokens_path, 'r') as f:
        for line in f.readlines():
            parts = line.split(":")
            if len(parts) == 3 and parts[0] == username:
                return parts[1], float(parts[2])
    return None, None

def check_token(client_socket, username):
    token_to_check = client_socket.recv(516).decode()
    saved_token, timestamp = find_token(username)
    if saved_token is not None and saved_token == token_to_check:
        if time.time() - timestamp <= 30 * 60:
            client_socket.send("correct".encode())
            print("Token confirmed.")
        else:
            client_socket.send("expired".encode())
            print("Token expired.")
            client_socket.close()
    else:
        client_socket.send("invalid".encode())
        print("Invalid token.")
        client_socket.close()

def main():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(('localhost', 8080))
    server_socket.listen(1)
    end_session = False

    print(f"Server listening on {'localhost'}, port 8080")
    client_socket, addr = server_socket.accept()
    print(f"Connection from {addr}")

    while not end_session:
        change_user = False
        credentials = client_socket.recv(1024).decode()
        username, password = credentials.split(':')
        if authorize_user(username, password):
            client_socket.send(b"authorized")

            global token
            all_token = find_token(username)
            if all_token[0] is not None:
                if time.time() - all_token[1] <= 30 * 60:
                    print("Token found. Reading token...")
                    token = all_token[0]
                else:
                    print("Generatinh new token...")
                    token = generate_token(username)
            else:
                print("Generatinh new token...")
                token = generate_token(username)
            client_socket.send(token.encode())
            print("Token send.")
                
            print("Waiting for public key from the client...")
            client_public_key = receive_public_key(client_socket, username)
            print("Public key received.")

            last_aes_key_time = time.time()
            aes_key = None

            while not change_user and not end_session:
                if aes_key is None or time.time() - last_aes_key_time > 60:
                    aes_key = generate_aes_key()
                    last_aes_key_time = time.time()
                    print("New AES key generated.")
                else:
                    print("Using existing AES key.")
                
                print("Handling client request...")
                handle_client(client_socket, client_public_key, aes_key, username)
                print(f"{username} request handled.")

                while True:
                    check_token(client_socket, username)
                    password_check = client_socket.recv(1024).decode()
                    if authorize_user(username, password_check):
                        client_socket.send(b"authorized")
                        check_token(client_socket, username)
                        choice = client_socket.recv(1024)

                        if choice == b"end_session":
                            print(f"{username} ended the session.\n")
                            end_session = True
                            break
                        elif choice == b"change_user":
                            print(f"{username} requested to change user.\n")
                            change_user = True
                            break
                        elif choice == b"continue_session":
                            print(f"{username} chose to continue session.\n")
                            break
                        else:
                            print("Invalid choice. Ending session.\n")
                            end_session = True
                            break
                    else:
                        client_socket.send(b"unauthorized")
        else:
            client_socket.send(b"unauthorized")

    client_socket.close()

if __name__ == "__main__":
    main()
