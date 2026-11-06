# Padding Oracle Attack on AES-CBC

## 1. Overview

This assignment demonstrates a Padding Oracle Attack against AES-CBC encryption using PKCS#7 padding.

The attack exploits a padding oracle that reveals whether decrypted ciphertext has valid padding. By modifying ciphertext blocks and observing oracle responses, the original plaintext can be recovered without knowing the AES encryption key.

## 2. Implementation

The attack is implemented in Python using PyCryptodome for AES-CBC encryption and decryption operations.

The implementation:
- Uses AES-CBC encryption with a randomly generated key and IV.
- Implements PKCS#7 padding.
- Provides a padding oracle that checks padding validity.
- Modifies the previous ciphertext block to manipulate decrypted plaintext.
- Recovers plaintext bytes from right to left.
- Reconstructs the complete plaintext and removes PKCS#7 padding.

The AES key is used only by the encryption and oracle simulation. The attack logic does not access or use the key.

## 3. Attack Execution

Run the program using:

```bash
pip install pycryptodome
python attacks/oracle_attack/main.py
```

## 4. Recovered Plaintext

The attack successfully recovered the following plaintext:

```text
CryptoLabX: Padding Oracle recovered plaintext without the AES key!
```

## 5. Experimental Results

| Parameter | Result |
|---|---|
| Encryption algorithm | AES-CBC |
| Padding scheme | PKCS#7 |
| Total ciphertext blocks | 5 |
| Total ciphertext bytes | 80 |
| Oracle queries | 10,245 |
| Execution time | 0.09 seconds |
| Plaintext recovery | Successful |

*Note: Query count and execution time are from one execution. They may vary between runs because the key, IV and ciphertext are randomly generated.*

## 6. Why the Attack Works

AES-CBC decryption is defined as:

\[
P_i = D_K(C_i) \oplus C_{i-1}
\]

Here, modifying the previous ciphertext block changes the corresponding plaintext block after decryption.

The attacker exploits this property to construct specific padding patterns. The padding oracle reveals whether the resulting plaintext has valid PKCS#7 padding.

By recovering intermediate values one byte at a time, the attacker can reconstruct the original plaintext without knowing the AES key.

## 7. Security Recommendations

Padding oracle vulnerabilities can be prevented by:

1. Using authenticated encryption such as AES-GCM or ChaCha20-Poly1305.
2. Authenticating ciphertext before attempting decryption.
3. Avoiding distinguishable error messages for padding and decryption failures.
4. Ensuring that error responses and timing do not reveal padding validity.
5. Using secure, well-maintained cryptographic libraries.

## 8. Execution Screenshots

The `outputs/` directory contains screenshots demonstrating:

- `attack_execution.png` – Padding oracle attack execution.
- `plaintext_recovery.png` – Successfully recovered plaintext.
- `query_count.png` – Total oracle queries and execution time.

## 9. Conclusion

The experiment demonstrates that AES-CBC encryption with distinguishable padding validation can expose plaintext even when the encryption key is unknown. It highlights the importance of authenticated encryption and secure error handling in cryptographic systems.