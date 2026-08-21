# Assignment 3: Secure Application Development (Cryptocurrency Wallet CLI)

## Application Overview
This project implements a command-line interface (CLI) Cryptocurrency Wallet application built in Python. The application provides basic financial transaction operations while intentionally incorporating targeted security vulnerabilities for educational static analysis and auditing purposes[cite: 2].

- **Application Name:** Crypto Wallet CLI
- **Source File Path:** `secure_application/src/crypto_wallet.py`
- **Execution Command:** `python secure_application/src/crypto_wallet.py`

---

## Implemented Core Functionalities

1. **Wallet Creation (`wallet_creation`)**
   Registers new user accounts in the system with an initial starting balance of 100 BTC.
2. **Login & Session Management (`login`)**
   Authenticates account holders using username/PIN credentials and maintains active session tracking (`current_user`).
3. **Balance Inquiry (`balance_inquiry`)**
   Queries and displays current wallet balance for the authenticated session user.
4. **Transaction Request (`transaction_request`)**
   Facilitates fund transfers between registered system accounts and records activity in ledger history.
5. **Transaction History (`transaction_history`)**
   Displays chronological transaction logs for account audit tracking.

---

## Implemented Security Vulnerabilities

### 1. Hardcoded Secrets (CWE-798)
* **Location:** `ADMIN_MASTER_KEY = "SECRET_CRYPTO_ADMIN_2026_KEY"`
* **Description:** Plaintext administrative tokens embedded directly inside application source code[cite: 2].

### 2. Broken Access Control (CWE-284)
* **Location:** `transaction_history()` function
* **Description:** Fails to restrict access strictly to `current_user`, allowing any logged-in session to view arbitrary third-party transaction logs by passing a target username.

### 3. Input Validation Error / Unsanitized Transfer (CWE-20)
* **Location:** `transaction_request()` function
* **Description:** Lacks non-negative input validation (`amount > 0`), enabling negative transfer values that invert arithmetic operations to drain recipient accounts and inflate sender balances.

---

## Directory Layout
```text
secure_application/
├── src/
│   └── crypto_wallet.py        # Core application source code
├── reports/
│   └── execution_log.txt       # Manual testing session logs[cite: 2]
├── screenshots/
│   ├── 01_wallet_and_login.png
│   ├── 02_broken_access_control.png
│   └── 03_negative_amount_exploit.png
└── README.md