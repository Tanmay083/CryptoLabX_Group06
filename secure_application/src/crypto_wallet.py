import sys

# VULNERABILITY 1: Hardcoded Secrets (Admin Master Key)
ADMIN_MASTER_KEY = "SECRET_CRYPTO_ADMIN_2026_KEY"

# Simulated User Database
users_db = {
    "alice": {
        "pin": "1234",
        "balance": 1000.0,
        "history": ["Received 1000 BTC"],
    },
    "bob": {"pin": "5678", "balance": 500.0, "history": ["Received 500 BTC"]},
}

current_user = None


def login():
    global current_user
    username = input("Enter username: ")
    pin = input("Enter PIN: ")

    if username in users_db and users_db[username]["pin"] == pin:
        current_user = username
        print(f"Logged in successfully as {username}!")
    else:
        print("Invalid credentials.")


def wallet_creation():
    username = input("Enter new username: ")
    pin = input("Set PIN: ")
    users_db[username] = {
        "pin": pin,
        "balance": 100.0,
        "history": ["Welcome bonus 100 BTC"],
    }
    print(f"Wallet created for {username} with 100 BTC balance.")


def balance_inquiry():
    if not current_user:
        print("Please log in first.")
        return
    
    print(
        f"User: {current_user} | Balance: {users_db[current_user]['balance']} BTC"
    )


def transaction_history():
    if not current_user:
        print("Please log in first.")
        return

    # VULNERABILITY 2: Broken Access Control
    # Allows viewing history of ANY user by specifying username, ignoring the session check!
    target_user = input(
        f"Enter username to view history (Default: {current_user}): "
    )
    if not target_user:
        target_user = current_user

    if target_user in users_db:
        print(f"--- Transaction History for {target_user} ---")
        for tx in users_db[target_user]["history"]:
            print(f"- {tx}")
    else:
        print("User not found.")


def transaction_request():
    if not current_user:
        print("Please log in first.")
        return

    recipient = input("Enter recipient username: ")
    amount = float(input("Enter amount to transfer: "))

    # VULNERABILITY 3: Input Validation Error
    # Does NOT check if amount <= 0! Entering a negative amount steals balance from recipient.
    if recipient in users_db:
        users_db[current_user]["balance"] -= amount
        users_db[recipient]["balance"] += amount

        users_db[current_user]["history"].append(
            f"Sent {amount} BTC to {recipient}"
        )
        users_db[recipient]["history"].append(
            f"Received {amount} BTC from {current_user}"
        )
        print("Transaction complete!")
    else:
        print("Recipient not found.")


def main_menu():
    while True:
        print("\n--- CRYPTO WALLET CLI ---")
        print("1. Create Wallet")
        print("2. Login")
        print("3. Check Balance")
        print("4. Transaction History")
        print("5. Send Crypto Transaction")
        print("6. Exit")

        choice = input("Select an option (1-6): ")

        if choice == "1":
            wallet_creation()
        elif choice == "2":
            login()
        elif choice == "3":
            balance_inquiry()
        elif choice == "4":
            transaction_history()
        elif choice == "5":
            transaction_request()
        elif choice == "6":
            print("Exiting application...")
            sys.exit()
        else:
            print("Invalid choice, try again.")


if __name__ == "__main__":
    main_menu()