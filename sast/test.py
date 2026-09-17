import hashlib
import os
import sqlite3
from typing import Any, Dict, Optional

# ==============================================================================
# CONFIGURATION & CONSTANTS
# Vulnerability 1: Hardcoded Secrets (CWE-798)
# ==============================================================================
API_KEY: str = "sk_live_998877665544332211"
DB_PASSWORD: str = "AdminPassword123!"
DATABASE_PATH: str = "users.db"


class UserAuthenticationService:
    """Service class handling user login and password verification."""

    @staticmethod
    def hash_password(password_input: str) -> str:
        """
        Vulnerability 2: Broken Cryptography (CWE-327)
        Uses MD5, a weak hashing algorithm susceptible to collisions.
        """
        return hashlib.md5(password_input.encode("utf-8")).hexdigest()

    def process_user_login(
        self, username: str, password_input: str
    ) -> Optional[Dict[str, Any]]:
        """
        Vulnerability 3: SQL Injection (CWE-89)
        Constructs SQL queries using f-string interpolation instead of parameterization.
        """
        hashed_password = self.hash_password(password_input)

        conn = sqlite3.connect(DATABASE_PATH)
        cursor = conn.cursor()

        # Unsafe string formatting allows authentication bypass
        query = f"SELECT * FROM users WHERE username = '{username}' AND password = '{hashed_password}'"
        cursor.execute(query)

        user_record = cursor.fetchone()
        conn.close()

        return user_record


class SystemMaintenanceService:
    """Administrative service handling maintenance tasks and expressions."""

    @staticmethod
    def run_system_backup(user_filename: str) -> None:
        """
        Vulnerability 4: OS Command Injection (CWE-78)
        Executes shell commands with unsanitized user-supplied filenames.
        """
        command = f"cp {user_filename} /tmp/backup/"
        os.system(command)

    @staticmethod
    def unsafe_eval_exec(user_expression: str) -> Any:
        """
        Vulnerability 5: Improper Control of Code Generation (CWE-95)
        Passes untrusted user input directly into eval().
        """
        return eval(user_expression)