from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
from Crypto.Random import get_random_bytes

with open(f"plaintext.txt", "w") as pf:
    for _ in range(100000):
        length = get_random_bytes(1)[0]
        length = length - length % 16
        plaintext = get_random_bytes(length)
        pf.write(plaintext.hex() + "\n")
