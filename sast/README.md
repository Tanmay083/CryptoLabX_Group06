# Static Application Security Testing (SAST) - Semgrep Analysis
## Overview
This directory contains the documentation, source scripts, logs, and vulnerability assessment reports for **Lab Assignment 2: Static Application Security Testing (SAST)**. Using **Semgrep**, an Abstract Syntax Tree (AST)-based static analysis engine, automated code scans were executed against a Python test application intentionally designed with common security vulnerabilities (CWE anti-patterns).


## Assigned SAST Tool Information

* **Tool Name:** Semgrep
* **Assigned Group:** Group 06
* **Supported Languages:** Python, C/C++, Java, Go, JavaScript, TypeScript, Ruby, C#, PHP, and HTML/YAML configuration formats.
* **Scan Engine Type:** Abstract Syntax Tree (AST) pattern matching driven by human-readable YAML rule sets.
* **Severity Levels:**
  * `ERROR`: High-risk vulnerabilities requiring immediate remediation (e.g., Hardcoded Credentials, Injection Flaws).
  * `WARNING`: Medium-risk security issues or insecure algorithm usage (e.g., Weak Cryptography).
  * `INFO`: Code quality, best practice violations, and style recommendations.

