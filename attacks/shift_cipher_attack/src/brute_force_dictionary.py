import os
from shift_cipher import decrypt

def load_dictionary(file_path: str) -> set:
    if not os.path.exists(file_path):
    
        return {"THE", "BE", "TO", "OF", "AND", "A", "IN", "THAT", "HAVE", "I", 
                "IT", "FOR", "NOT", "ON", "WITH", "HE", "AS", "YOU", "DO", "AT", 
                "THIS", "BUT", "HIS", "BY", "FROM", "THEY", "WE", "SAY", "HER", 
                "SHE", "OR", "AN", "WILL", "MY", "ONE", "ALL", "WOULD", "THERE", 
                "THEIR", "WHAT", "QUICK", "BROWN", "FOX", "JUMPS", "OVER", "LAZY", 
                "DOG", "CRYPTOGRAPHY", "PRACTICE", "STUDY", "HIDING", "INFORMATION"}
    
    with open(file_path, 'r', encoding='utf-8') as f:
        return set(line.strip().upper() for line in f if line.strip())

def attack_dictionary(ciphertext: str, dict_file_path: str = "attacks/shift_cipher_attack/dictionary/english_words.txt") -> tuple[int, str, int]:
    dictionary = load_dictionary(dict_file_path)
    best_key = 0
    best_score = -1
    best_plaintext = ""

    for key in range(26):
        candidate_text = decrypt(ciphertext, key)
        words = candidate_text.upper().split()
        
        # Count words matching dictionary
        score = sum(1 for word in words if word in dictionary)
        
        if score > best_score:
            best_score = score
            best_key = key
            best_plaintext = candidate_text

    return best_key, best_plaintext, best_score