#include <iostream>
#include <fstream>
#include <unordered_set>
#include <string>
#include <regex>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <json/json.h>

class PasswordStrengthChecker {
private:
    std::unordered_set<std::string> weakPasswords;

public:
    PasswordStrengthChecker() {
        std::srand(std::time(0));
        loadWeakPasswords();
    }

    void loadWeakPasswords() {
        std::ifstream file("weakPasswords.txt");
        if (!file) {
            std::cerr << "Cannot open weakPasswords.txt!\n";
            exit(1);
        }

        std::string password;
        while (std::getline(file, password)) {
            weakPasswords.insert(password);
        }
        file.close();
    }

    std::string checkPasswordStrength(const std::string &password) {
        if (weakPasswords.find(password) != weakPasswords.end()) {
            return "Weak: This password is commonly used and insecure.";
        }

        if (password.length() < 8) {
            return "Weak: Password must be at least 8 characters.";
        }

        bool hasUpper = std::regex_search(password, std::regex("[A-Z]"));
        bool hasLower = std::regex_search(password, std::regex("[a-z]"));
        bool hasDigit = std::regex_search(password, std::regex("[0-9]"));
        bool hasSpecial = std::regex_search(password, std::regex("[!@#$%^&*(),.?\":{}|<>]"));

        if (!hasUpper || !hasLower || !hasDigit || !hasSpecial) {
            return "Weak: Password must contain at least one uppercase letter, one lowercase letter, one number, and one special character.";
        }

        if (password.length() > 12) {
            return "Strong: Password is strong and meets the criteria.";
        } else if (password.length() >= 8 && password.length() <= 12) {
            return "Medium: Password is of medium strength.";
        }

        return "Weak: Password is too weak for security.";
    }

    std::string generatePassword(int length = 16) {
        const std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*(),.?\":{}|<>";

        std::string password;
        for (int i = 0; i < length; ++i) {
            password += characters[std::rand() % characters.length()];
        }

        return password;
    }

    void exportResults(const std::vector<std::string> &results) {
        Json::Value root;
        for (const auto &result : results) {
            root.append(result);
        }

        std::ofstream file("results.json");
        file << root;
        file.close();
    }
};

int main() {
    PasswordStrengthChecker checker;
    std::vector<std::string> results;

    std::cout << "🔐 Password Strength Checker 🔐\n";

    while (true) {
        std::cout << "\n1. Check Password Strength\n2. Generate Strong Password\n3. Exit\n";
        std::cout << "Enter choice: ";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            std::cout << "Enter password to check: ";
            std::string password;
            std::cin >> password;
            std::string result = checker.checkPasswordStrength(password);
            std::cout << "Password Check Result: " << result << std::endl;
            results.push_back(result);
        } else if (choice == 2) {
            int length;
            std::cout << "Enter desired password length (default 16): ";
            std::cin >> length;
            std::string password = checker.generatePassword(length);
            std::cout << "Generated Password: " << password << std::endl;
            results.push_back("Generated password: " + password);
        } else if (choice == 3) {
            checker.exportResults(results);
            std::cout << "Results exported to results.json\n";
            break;
        } else {
            std::cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
