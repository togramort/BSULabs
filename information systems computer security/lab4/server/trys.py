from Crypto.Random import get_random_bytes
from Crypto.Cipher import AES
import hashlib
import base64
import binascii

# def encrypt_file_with_aes(plaintext, key):
#     cipher = AES.new(key, AES.MODE_CFB)
#     ciphertext_bytes = cipher.encrypt(plaintext)
#     return ciphertext_bytes, cipher.iv

# key = bytes.fromhex('ddabb34a9455060928465c412516b2bf')
# plaintext = "pusto pryam kak v golove".encode()

# text, iv = encrypt_file_with_aes(plaintext, key)
# print(text.hex() + ":" + iv.hex())


# def decrypt_file_with_aes(ciphertext_bytes, key, iv):
#     cipher = AES.new(key, AES.MODE_CFB, iv=iv)
#     plaintext_bytes = cipher.decrypt(ciphertext_bytes)
#     return plaintext_bytes

# plain = decrypt_file_with_aes(text, key, iv)
# print(plain.decode())

secret_key = "super_secret_key"
def generate_token(username):
    with open('./server/token_key.txt', 'rb') as file:
        key = file.read()
    print(key)
    #key = bytes.fromhex(key)
    print(key.decode())

tamp = hashlib.sha256(secret_key.encode()).hexdigest()
print(tamp)
generate_token("l")