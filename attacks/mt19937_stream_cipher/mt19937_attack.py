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

# ============================================================
# PART B: PREDICTABLE PASSWORD RESET TOKEN ATTACK
# ============================================================

import time


def generate_reset_token(timestamp: int) -> bytes:
    """
    Generate a 16-byte reset token using MT19937
    seeded with a Unix timestamp.
    """
    bit_generator = np.random.MT19937(timestamp)
    rng = np.random.Generator(bit_generator)

    token = rng.integers(
        0, 256, size=16, dtype=np.uint8
    )

    return token.tobytes()


def predict_reset_token(observed_token: bytes,
                        timestamp: int,
                        window: int = 300):
    """
    Search timestamps from T-window to T+window
    to recover the seed used for token generation.
    """
    candidates_tested = 0
    recovered_timestamp = None

    for candidate in range(timestamp - window,
                           timestamp + window + 1):

        candidates_tested += 1

        candidate_token = generate_reset_token(candidate)

        if candidate_token == observed_token:
            recovered_timestamp = candidate
            break

    return recovered_timestamp, candidates_tested



def timestamp_token_attack():
    print("\n=== PART B: PREDICTABLE RESET TOKEN ATTACK ===")

    # Record actual Unix timestamp
    original_timestamp = int(time.time())

    # Generate token using actual timestamp
    original_token = generate_reset_token(original_timestamp)

    print("Original timestamp:", original_timestamp)
    print("Generated reset token:", original_token.hex())

    # Simulate attacker's approximate timestamp estimate
    window = 300
    attacker_estimate = original_timestamp + 120

    start_timestamp = attacker_estimate - window
    end_timestamp = attacker_estimate + window

    print("\n=== TIMESTAMP BRUTE-FORCE ATTACK ===")
    print("Attacker's estimated timestamp:", attacker_estimate)
    print("Search interval:", start_timestamp, "to", end_timestamp)
    print("Total possible timestamps:", 2 * window + 1)

    recovered_timestamp, candidates_tested = predict_reset_token(
        original_token,
        attacker_estimate,
        window
    )

    print("Candidates tested:", candidates_tested)
    print("Recovered timestamp:", recovered_timestamp)

    # Verify recovered timestamp
    if recovered_timestamp is not None:
        recovered_token = generate_reset_token(recovered_timestamp)

        print("\n=== VERIFICATION ===")
        print("Regenerated token:", recovered_token.hex())
        print(
            "Timestamp recovered correctly:",
            recovered_timestamp == original_timestamp
        )
        print(
            "Token verification successful:",
            recovered_token == original_token
        )
    else:
        print("No matching timestamp found.")

# Execute Part B
timestamp_token_attack()