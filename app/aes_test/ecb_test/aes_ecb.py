from Crypto.Cipher import AES
from Crypto.Util.Padding import pad
from Crypto.Random import get_random_bytes

key_size = [128, 192, 256]

for i in range(3):
    with open(f"test-{key_size[i]}.txt", "w") as f:
        key = get_random_bytes(key_size[i] // 8)
        cipher = AES.new(key, AES.MODE_ECB)
        f.write(key.hex() + "\n")
        for _ in range(10000):
            plaintext = get_random_bytes(get_random_bytes(1)[0])
            ciphertext = cipher.encrypt(pad(plaintext, AES.block_size))
            f.write(plaintext.hex() + "\n")
            f.write(ciphertext.hex() + "\n")
