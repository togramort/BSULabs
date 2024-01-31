import socket
import rsa
import os
from Crypto.Cipher import AES

def generate_or_load_rsa_keys():
    public_key_path = './client/rsa/client_public_key.pem'
    private_key_path = './client/rsa/client_private_key.pem'

    if os.path.exists(public_key_path) and os.path.exists(private_key_path):
        with open(public_key_path, 'rb') as f:
            public_key_data = f.read()
            public_key = rsa.PublicKey.load_pkcs1(public_key_data)

        with open(private_key_path, 'rb') as f:
            private_key_data = f.read()
            private_key = rsa.PrivateKey.load_pkcs1(private_key_data)

        return public_key, private_key
    else:
        public_key, private_key = rsa.newkeys(2048)

        with open(public_key_path, 'wb') as f:
            f.write(public_key.save_pkcs1())

        with open(private_key_path, 'wb') as f:
            f.write(private_key.save_pkcs1())

        return public_key, private_key

def receive_file_list(client_socket):
    file_list = client_socket.recv(1024).decode()
    print("Available files:")
    print(file_list)

def send_selected_file(client_socket, selected_file_name):
    send_token(token, client_socket)
    client_socket.send(selected_file_name.encode())

def receive_encrypted_aes_key_and_ciphertext(client_socket, rsa_private_key):
    ciphertext_bytes = client_socket.recv(1024)
    iv = client_socket.recv(16)
    encrypted_aes_key = client_socket.recv(256)
    aes_key = rsa.decrypt(encrypted_aes_key, rsa_private_key)

    return aes_key, ciphertext_bytes, iv

def decrypt_file_with_aes(ciphertext_bytes, key, iv):
    cipher = AES.new(key, AES.MODE_CFB, iv=iv)
    plaintext_bytes = cipher.decrypt(ciphertext_bytes)
    return plaintext_bytes

def send_credentials(client_socket):
    global username
    username = input("Enter your username: ")
    password = input("Enter your password: ")
    credentials = f"{username}:{password}"
    client_socket.send(credentials.encode())
    response = client_socket.recv(1024).decode()
    return response

def login(client_socket):
    response = send_credentials(client_socket)
    if response == "authorized":
        print("Login successful.")
        return True
    elif response == "unauthorized":
        print("Invalid username or password.")
    else:
        print("Unknown response from server.")
    return False

def send_public_key(client_socket):
    send_token(token, client_socket)
    public_key, private_key = generate_or_load_rsa_keys()
    print("Sending public key to the server...")
    client_socket.send(public_key.save_pkcs1())
    print("Public key sent.")
    return private_key

def send_token(token, client_socket):
    client_socket.send(token.encode())
    response = client_socket.recv(516).decode()
    if response == "invalid":
        client_socket.close()

def save_text_into_file(text, filename):
    with open('./client/key_for_files.key', 'r') as file:
        key = file.read()
        key = bytes.fromhex(key)
    cipher = AES.new(key, AES.MODE_CFB)
    ciphertext_bytes = cipher.encrypt(text.encode())
    with open('./client/text_encoded/' + filename, 'w') as file:
        file.write(ciphertext_bytes.hex() + ":" + cipher.iv.hex())
        print("Text successfully saved.")

def open_files():
    dir = './client/text_encoded/'
    files = os.listdir(dir)
    print("\navailable files:")
    for filename in files:
        print(filename)       
    filename = input("choose file to read:")
    filename = dir + str(filename)
    with open('./client/key_for_files.key', 'r') as file:
        key = file.read()
    with open(filename, 'r') as file:
        line = file.read()
        line = line.split(":")
    text = bytes.fromhex(line[0])
    iv = bytes.fromhex(line[1])
    plain_text = decrypt_file_with_aes(text, bytes.fromhex(key), iv)
    print("text from file\n", plain_text.decode())
    return 0

def main():
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client_socket.connect(('localhost', 8080))
    end_session = False

    while not end_session:
        if not login(client_socket):
            break

        files_or_server = input("what you wanna do:\n(1) check files\n(2) connect to server\n")
        if int(files_or_server) == 1:
            open_files()
            end_session = True
            break

        global token
        token = client_socket.recv(1024).decode()
        print("Token received.")

        private_key = send_public_key(client_socket)
        while True:
            receive_file_list(client_socket)
            selected_file_name = input("Enter the name of the file you want to receive: ")
            send_selected_file(client_socket, selected_file_name)

            print("Waiting for encrypted AES key and ciphertext from the server...")
            aes_key, ciphertext_bytes, iv = receive_encrypted_aes_key_and_ciphertext(client_socket, private_key)
            print("AES key and ciphertext received.")

            password_check = input("Enter your password to decrypt the file: ")
            send_token(token, client_socket)
            client_socket.send(password_check.encode())
            response = client_socket.recv(1024).decode()

            if response == "authorized":
                plaintext_bytes = decrypt_file_with_aes(ciphertext_bytes, aes_key, iv)
                print("Decrypted Text:")
                print(plaintext_bytes.decode())
                save_text_into_file(plaintext_bytes.decode(), selected_file_name)

                choice = input("Continue session? (1 - End session, 2 - Change user, 3 - Continue session): ")
                send_token(token, client_socket)

                if choice == "1":
                    client_socket.send(b"end_session")
                    end_session = True
                    break
                elif choice == "2":
                    client_socket.send(b"change_user")
                    break
                elif choice == "3":
                    client_socket.send(b"continue_session")
                else:
                    print("Invalid choice. Ending session.")
                    client_socket.send(b"end_session")
                    break
            elif response == "unauthorized":
                print("Incorrect password. Please try again.")
            else:
                print("Unknown response from server. Ending session.")
                client_socket.send(b"end_session")
                break

    client_socket.close()

if __name__ == "__main__":
    main()
