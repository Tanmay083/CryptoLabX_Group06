import os
import time
from Crypto.Cipher import AES

BLOCK_SIZE = 16

class PaddingOracleServer:
    def __init__(self):
        self.__key = os.urandom(16)
        self.query_count = 0

    def encrypt(self, plaintext: bytes):
        """Generates sample ciphertext with valid PKCS#7 padding."""
        pad_len = BLOCK_SIZE - (len(plaintext) % BLOCK_SIZE)
        padded_text = plaintext + bytes([pad_len] * pad_len)
        iv = os.urandom(BLOCK_SIZE)
        cipher = AES.new(self.__key, AES.MODE_CBC, iv)
        return iv, cipher.encrypt(padded_text)

    def padding_oracle(self, iv: bytes, ciphertext: bytes) -> bool:
        """The Oracle: Returns True if PKCS#7 padding is valid, False otherwise."""
        self.query_count += 1
        cipher = AES.new(self.__key, AES.MODE_CBC, iv)
        decrypted = cipher.decrypt(ciphertext)
        
        pad_len = decrypted[-1]
        if pad_len < 1 or pad_len > BLOCK_SIZE:
            return False
        return decrypted[-pad_len:] == bytes([pad_len] * pad_len)


def unpad_pkcs7(padded_data: bytes) -> bytes:
    """Removes PKCS#7 padding from fully recovered plaintext."""
    pad_len = padded_data[-1]
    return padded_data[:-pad_len]

def attack_block(oracle: PaddingOracleServer, block_num: int, prev_block: bytes, target_block: bytes) -> bytes:
    """Recovers intermediate state I_i and computes plaintext P_i byte by byte."""
    intermediate = bytearray(BLOCK_SIZE)
    recovered_bytes = bytearray(BLOCK_SIZE)
    
    print(f"\n[+] ATTACKING BLOCK {block_num} (Hex: {target_block.hex()})")
    print("-" * 70)
    print(f"{'Byte Index':<12} | {'Target Pad':<12} | {'Found Candidate':<16} | {'Intermediate (I)':<18} | {'Recovered Char'}")
    print("-" * 70)

    for byte_idx in range(BLOCK_SIZE - 1, -1, -1):
        target_pad = BLOCK_SIZE - byte_idx
        c_prime = bytearray(BLOCK_SIZE)

        for k in range(byte_idx + 1, BLOCK_SIZE):
            c_prime[k] = intermediate[k] ^ target_pad

        for candidate in range(256):
            c_prime[byte_idx] = candidate
            
            if byte_idx == BLOCK_SIZE - 1 and candidate == prev_block[byte_idx] ^ target_pad:
                continue

            if oracle.padding_oracle(bytes(c_prime), target_block):
                inter_val = candidate ^ target_pad
                plain_val = inter_val ^ prev_block[byte_idx]
                
                intermediate[byte_idx] = inter_val
                recovered_bytes[byte_idx] = plain_val

                char_repr = chr(plain_val) if 32 <= plain_val <= 126 else f"\\x{plain_val:02x}"
                print(f"{byte_idx:<12} | 0x{target_pad:02x} ({target_pad:<2d})    | 0x{candidate:02x} ({candidate:<3d})        | 0x{inter_val:02x}               | {char_repr}")
                break

    plaintext_block = bytes(recovered_bytes)
    print("-" * 70)
    print(f"[✔] BLOCK {block_num} COMPLETED -> Plaintext: {plaintext_block}\n")
    return plaintext_block

def run_padding_oracle_attack(oracle: PaddingOracleServer, iv: bytes, ciphertext: bytes):
    """Executes attack across all CBC blocks."""
    blocks = [iv] + [ciphertext[i:i+BLOCK_SIZE] for i in range(0, len(ciphertext), BLOCK_SIZE)]
    recovered_plaintext = bytearray()

    print("========================================================================")
    print("           STARTING INTERACTIVE PADDING ORACLE ATTACK                   ")
    print("========================================================================")
    print(f"IV (Block 0)       : {iv.hex()}")
    print(f"Total Cipher Blocks: {len(blocks) - 1}")
    print(f"Total Cipher Bytes : {len(ciphertext)} bytes")
    print("========================================================================")

    start_time = time.time()
    
    for i in range(1, len(blocks)):
        prev_block = blocks[i-1]
        target_block = blocks[i]
        
        block_pt = attack_block(oracle, i, prev_block, target_block)
        recovered_plaintext.extend(block_pt)

    elapsed_time = time.time() - start_time
    return bytes(recovered_plaintext), elapsed_time

if __name__ == "__main__":
    server = PaddingOracleServer()
    original_message = b"CryptoLabX: Padding Oracle recovered plaintext without the AES key!"
    
    iv, ciphertext = server.encrypt(original_message)

    raw_plaintext, duration = run_padding_oracle_attack(server, iv, ciphertext)
    final_plaintext = unpad_pkcs7(raw_plaintext)

    print("========================================================================")
    print("                        ATTACK COMPLETE SUMMARY                          ")
    print("========================================================================")
    print(f"[1] Raw Ciphertext (Hex) :\n    {(iv + ciphertext).hex()}\n")
    print(f"[2] Recovered Raw Plaintext (With PKCS#7 Padding) :\n    {raw_plaintext}\n")
    print(f"[3] Final Decrypted Plaintext (Unpadded String) :\n    {final_plaintext.decode('utf-8')}\n")
    print("------------------------------------------------------------------------")
    print(f"[*] Total Padding Oracle Queries Sent : {server.query_count}")
    print(f"[*] Total Time Elapsed              : {duration:.2f} seconds")
    print("========================================================================")