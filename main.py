import os
import datetime

LOG_FILE = "outputs/cryptolabx.log"
DATASETS_DIR = "datasets"

def log_action(option_name):
    """Task 5: Maintain a log file recording date, time, and selected menu option."""
    os.makedirs("outputs", exist_ok=True)
    now = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    with open(LOG_FILE, "a") as f:
        f.write(f"[{now}] Selected Option: {option_name}\n")

def analyze_file():
    """Task 4: File analysis implementation."""
    filename = input("\nEnter file name in 'datasets/' folder (e.g., sample1.txt): ").strip()
    filepath = os.path.join(DATASETS_DIR, filename)

    if not os.path.exists(filepath):
        print(f"Error: File '{filepath}' not found.")
        return

    with open(filepath, 'r', encoding='utf-8') as f:
        content = f.read()

    num_chars = len(content)
    num_words = len(content.split())
    num_lines = len(content.splitlines())
    unique_chars = len(set(content))
    
    
    freq = {}
    for char in content:
        if char.isalpha():
            char_lower = char.lower()
            freq[char_lower] = freq.get(char_lower, 0) + 1

    print("\n--- File Analysis Results ---")
    print(f"Total Characters : {num_chars}")
    print(f"Total Words      : {num_words}")
    print(f"Total Lines      : {num_lines}")
    print(f"Unique Characters: {unique_chars}")
    print("Letter Frequencies:")
    for letter in sorted(freq.keys()):
        print(f"  {letter}: {freq[letter]}")

def display_menu():
    """Task 3: Menu-driven CLI."""
    while True:
        print("\n==============================")
        print("    CryptoLabX Framework      ")
        print("==============================")
        print("1. Encrypt (Coming Soon)")
        print("2. Decrypt (Coming Soon)")
        print("3. Attack  (Coming Soon)")
        print("4. Analyze File")
        print("5. Exit")
        
        choice = input("Select an option (1-5): ").strip()

        if choice == '1':
            log_action("Encrypt")
            print("\n[!] Encrypt module is coming soon!")
        elif choice == '2':
            log_action("Decrypt")
            print("\n[!] Decrypt module is coming soon!")
        elif choice == '3':
            log_action("Attack")
            print("\n[!] Attack module is coming soon!")
        elif choice == '4':
            log_action("Analyze File")
            analyze_file()
        elif choice == '5':
            log_action("Exit")
            print("\nExiting CryptoLabX. Goodbye!")
            break
        else:
            print("\nInvalid choice. Please enter a number from 1 to 5.")

if __name__ == "__main__":
    display_menu()