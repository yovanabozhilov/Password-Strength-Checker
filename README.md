# Password Strength Checker 

## Overview
This is a simple command-line interface (CLI) tool to check the strength of passwords. It evaluates password strength based on:
- **Length** (minimum of 8 characters required)
- **Character variety** (uppercase, lowercase, digits, special characters)
- **Commonly used passwords** (checks against a list of weak passwords from `weakPasswords.txt`)

Additionally, the tool can generate secure random passwords and export results to a JSON file.

## Features
- **Check password strength**: Classifies passwords as Weak, Medium, or Strong based on predefined criteria.
- **Detects common weak passwords**: Reads from `weakPasswords.txt` and flags commonly used passwords.
- **Generate secure passwords**: Creates a strong, random password of a user-defined length.
- **Export results**: Saves password strength evaluations to `results.json`.

## Installation
### Requirements:
Ensure you have `g++` and the `libjsoncpp-dev` library installed on your system.

Install Dependencies (if not installed): 
```sh
sudo apt update && sudo apt install g++ libjsoncpp-dev
```

### Compilation:
```sh
 g++ -o passwordChecker passwordChecker.cpp -I/usr/include/jsoncpp -ljsoncpp
```

### Running the Program:
```sh
 ./passwordChecker
```

## Usage
Once the program starts, you will be presented with the following menu:
```
1. Check Password Strength
2. Generate Strong Password
3. Exit
```

### 1. Checking Password Strength
- Enter a password to analyze.
- If the password is found in `weakPasswords.txt`, it will be marked as **Weak**.
- If the password meets security criteria, it will be classified as **Weak, Medium, or Strong**.

### 2. Generating a Strong Password
- Enter the desired password length (default is 16 characters).
- A randomly generated password will be displayed.

### 3. Exit and Export Results
- Saves all checked passwords and their strength ratings to `results.json`.

## Example weakPasswords.txt
```
123456
password
qwerty
12345678
abc123
111111
letmein
1234
monkey
```

## Example Output
```
Password Strength Checker CLI
1. Check Password Strength
2. Generate Strong Password
3. Exit
Enter choice: 1
Enter password to check: password123
Password Check Result: Weak: This password is commonly used and insecure.
```

## Notes
- Ensure `weakPasswords.txt` is present in the same directory as the program.


