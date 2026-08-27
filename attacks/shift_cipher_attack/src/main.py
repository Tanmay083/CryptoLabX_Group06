import os

from shift_cipher import encrypt
from brute_force_dictionary import attack_dictionary
from chi_square_attack import attack_chi_square


def main():
    test_cases = [
        ("THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG", 7),
        ("CRYPTOGRAPHY IS THE PRACTICE AND STUDY OF HIDING INFORMATION", 15),
        ("SHORT TEXT", 3)
    ]

    print("=" * 85)
    print(
        f"{'Test Case':<10} | "
        f"{'Actual Key':<10} | "
        f"{'Dict Key':<10} | "
        f"{'Chi Key':<10} | "
        f"{'Dict Correct?':<14} | "
        f"{'Chi Correct?':<12}"
    )
    print("=" * 85)

    dict_path = os.path.join(
        os.path.dirname(__file__),
        "../dictionary/english_words.txt"
    )

    for idx, (plaintext, actual_key) in enumerate(test_cases, 1):
        # Generate ciphertext
        ciphertext = encrypt(plaintext, actual_key)

        # Run cryptanalysis attacks
        dict_key, _, _ = attack_dictionary(ciphertext, dict_path)
        chi_key, _, _ = attack_chi_square(ciphertext)

        # Evaluate accuracy
        dict_correct = "Yes" if dict_key == actual_key else "No"
        chi_correct = "Yes" if chi_key == actual_key else "No"

        print(
            f"{idx:<10} | "
            f"{actual_key:<10} | "
            f"{dict_key:<10} | "
            f"{chi_key:<10} | "
            f"{dict_correct:<14} | "
            f"{chi_correct:<12}"
        )

    print("=" * 85)


if __name__ == "__main__":
    main()