import hashlib
import os
import sqlite3

# 1. Hardcoded Credentials (CWE-798)
API_KEY = "sk_live_998877665544332211"
DB_PASSWORD = "AdminPassword123!"


def process_user_login(username, password_input):
    # 2. Broken Cryptography (CWE-327)
    hashed_password = hashlib.md5(password_input.encode()).hexdigest()

    conn = sqlite3.connect("users.db")
    cursor = conn.cursor()

    # 3. SQL Injection (CWE-89)
    query = f"SELECT * FROM users WHERE username = '{username}' AND password = '{hashed_password}'"
    cursor.execute(query)
    user = cursor.fetchone()
    conn.close()
    return user


def run_system_backup(user_filename):
    # 4. OS Command Injection (CWE-78)
    command = f"cp {user_filename} /tmp/backup/"
    os.system(command)


def unsafe_eval_exec(user_expression):
    # 5. Dangerous Code Evaluation (CWE-95)
    return eval(user_expression)