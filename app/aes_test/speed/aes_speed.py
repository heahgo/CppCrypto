from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
from Crypto.Random import get_random_bytes

with open(f"plaintext.txt", "w") as pf:
    for _ in range(1000000):
        plaintext = get_random_bytes(64)
        pf.write(plaintext.hex() + "\n")
