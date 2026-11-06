import numpy as np
import secrets
import string


# Generate MT19937 keystream
def generate_keystream(seed: int, length: int) -> bytes:
    bit_generator = np.random.MT19937(seed)
    rng = np.random.Generator(bit_generator)

    return rng.integers(
        0, 256, size=length, dtype=np.uint8
    ).tobytes()


# XOR encryption/decryption
def xor_cipher(data: bytes, seed: int) -> bytes:
    keystream = generate_keystream(seed, len(data))
    return bytes(a ^ b for a, b in zip(data, keystream))


# Generate plaintext with unknown prefix and known sequence
def generate_plaintext() -> bytes:
    prefix_length = secrets.randbelow(16) + 5

    printable_chars = string.ascii_letters + string.digits + string.punctuation + " "
    prefix = ''.join(
        secrets.choice(printable_chars)
        for _ in range(prefix_length)
    )

    return (prefix + "A" * 14).encode("utf-8")


# Brute-force all possible 16-bit seeds
def recover_seed(ciphertext: bytes):
    known_sequence = b"A" * 14
    matching_candidates = []

    for candidate_seed in range(65536):
        plaintext = xor_cipher(ciphertext, candidate_seed)

        if known_sequence in plaintext:
            matching_candidates.append((candidate_seed, plaintext))

    return matching_candidates


def main():
    # Generate plaintext and random 16-bit seed
    plaintext = generate_plaintext()
    original_seed = secrets.randbelow(65536)

    # Encrypt
    ciphertext = xor_cipher(plaintext, original_seed)

    # Decrypt using the original seed
    decrypted = xor_cipher(ciphertext, original_seed)

    print("=== MT19937 Stream Cipher ===")
    print("Original plaintext:", plaintext.decode())
    print("Original seed:", original_seed)
    print("Ciphertext (hex):", ciphertext.hex())
    print("Decryption successful:", decrypted == plaintext)

    # Recover seed using known plaintext
    print("\n=== Brute-Force Seed Recovery ===")
    matches = recover_seed(ciphertext)

    print("Total seeds tested:", 65536)
    print("Matching candidates:", len(matches))

    for recovered_seed, recovered_plaintext in matches:
        print("Recovered seed:", recovered_seed)
        print("Recovered plaintext:", recovered_plaintext.decode())
        print("Seed matches original:", recovered_seed == original_seed)
        print("Plaintext matches original:", recovered_plaintext == plaintext)
        print("Known sequence verified:", b"A" * 14 in recovered_plaintext)


if __name__ == "__main__":
    main()