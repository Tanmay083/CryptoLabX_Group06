from collections import Counter
from shift_cipher import decrypt


# Standard English letter frequencies
ENGLISH_FREQUENCIES = {
    'A': 0.08167,
    'B': 0.01492,
    'C': 0.02782,
    'D': 0.04253,
    'E': 0.12702,
    'F': 0.02228,
    'G': 0.02015,
    'H': 0.06094,
    'I': 0.06966,
    'J': 0.00153,
    'K': 0.00772,
    'L': 0.04025,
    'M': 0.02406,
    'N': 0.06749,
    'O': 0.07507,
    'P': 0.01929,
    'Q': 0.00095,
    'R': 0.05987,
    'S': 0.06327,
    'T': 0.09056,
    'U': 0.02758,
    'V': 0.00978,
    'W': 0.02360,
    'X': 0.00150,
    'Y': 0.01974,
    'Z': 0.00074
}


def calculate_chi_square(text: str) -> float:
    """Calculates Chi-Square statistic comparing observed letters
    to English expected frequencies.
    """

    letters = [char.upper() for char in text if char.isalpha()]
    total_letters = len(letters)

    if total_letters == 0:
        return float('inf')

    counts = Counter(letters)
    chi_square_score = 0.0

    for char in ENGLISH_FREQUENCIES:
        observed = counts.get(char, 0)
        expected = ENGLISH_FREQUENCIES[char] * total_letters

        chi_square_score += ((observed - expected) ** 2) / expected

    return chi_square_score


def attack_chi_square(ciphertext: str) -> tuple[int, str, float]:
    """Exhausts all 26 keys and selects the key with the minimum
    Chi-Square value.
    """

    best_key = 0
    min_chi_square = float('inf')
    best_plaintext = ""

    for key in range(26):
        candidate_text = decrypt(ciphertext, key)
        score = calculate_chi_square(candidate_text)

        if score < min_chi_square:
            min_chi_square = score
            best_key = key
            best_plaintext = candidate_text

    return best_key, best_plaintext, min_chi_square