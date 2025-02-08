#include <iostream>
#include <fstream>
#include <cctype>
#include <string>

using namespace std;

void encrypt(const string& inputFile, const string& keyFile, const string& outputFile) {
    ifstream input(inputFile);
    if (!input) {
        cerr << "Error: Nie mozna otworzyc pliku wejsciowego!" << endl;
        return;
    }
    string inputText((istreambuf_iterator<char>(input)), istreambuf_iterator<char>());
    input.close();

    ifstream keyInput(keyFile);
    if (!keyInput) {
        cerr << "Error: Nie mozna otworzyc pliku klucza!" << endl;
        return;
    }
    string key;
    keyInput >> key;
    keyInput.close();

    string result;
    int key_length = key.size();
    for (size_t i = 0, keyIndex = 0; i < inputText.size(); ++i) {
        char currentChar = inputText[i];
        if (isalpha(currentChar)) {
            char base = isupper(currentChar) ? 'A' : 'a';
            char keyChar = tolower(key[keyIndex % key_length]);
            int shift = keyChar - 'a';
            char newChar = base + (currentChar - base + shift + 26) % 26;
            result += newChar;
            keyIndex++;
        }
        else {
            result += currentChar;
        }
    }

}

void decrypt(const string& inputFile, const string& keyFile, const string& outputFile) {
    ifstream input(inputFile);
    if (!input) {
        cerr << "Error: Nie mozna otworzyc pliku wejsciowego!" << endl;
        return;
    }
    string inputText((istreambuf_iterator<char>(input)), istreambuf_iterator<char>());
    input.close();

    ifstream keyInput(keyFile);
    if (!keyInput) {
        cerr << "Error: Nie mozna otworzyc pliku klucza!" << endl;
        return;
    }
    string key;
    keyInput >> key;
    keyInput.close();

    string result;
    int key_length = key.size();
    for (size_t i = 0, keyIndex = 0; i < inputText.size(); ++i) {
        char currentChar = inputText[i];
        if (isalpha(currentChar)) {
            char base = isupper(currentChar) ? 'A' : 'a';
            char keyChar = tolower(key[keyIndex % key_length]);
            int shift = keyChar - 'a';
            shift = -shift;
            char newChar = base + (currentChar - base + shift + 26) % 26;
            result += newChar;
            keyIndex++;
        }
        else {
            result += currentChar;
        }
    }
}

int main(int argc, char* argv[]) {
    string inputFile, keyFile, outputFile;
    bool encrypt = true;

    for (int i = 1; i < argc; i++) {
        string arg = argv[i];

        if (arg == "-i" && i + 1 < argc) {
            inputFile = argv[i + 1];
            i++;
        }
        if (arg == "-o" && i + 1 < argc) {
            outputFile = argv[i + 1];
            i++;
        }
        if (arg == "-k" && i + 1 < argc) {
            keyFile = argv[i + 1];
            i++;
        }
        if (arg == "-e") {
            encrypt = true;
        }
        if (arg == "-d") {
            encrypt = false;
        }
    }

    if (encrypt) {
        string encrypted = encryptFile(inputFile, keyFile, outputFile);
        cout << encrypted;
    }
    else {
        string decrypted = decryptFile(inputFile, keyFile, outputFile);
        cout << decrypted;
    }

    return 0;
}

