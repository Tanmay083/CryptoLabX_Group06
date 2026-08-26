def encrypt(plaintext: str, key: int) -> str:
    ciphertext = []
    key = key % 26
    
    for char in plaintext:
        if char.isalpha():
            base = ord('A') if char.isupper() else ord('a')
            shifted = (ord(char) - base + key) % 26 + base
            ciphertext.append(chr(shifted))
        else:
            ciphertext.append(char)
            
    return "".join(ciphertext)

def decrypt(ciphertext: str, key: int) -> str:
    return encrypt(ciphertext, -key)