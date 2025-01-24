#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;


string encrypt(const string& output, const string& key_input) {
    string output_d = "";
    int key_length = key_input.length();
    for (size_t i = 0; i < output.length(); i++) {
        char letter = output[i];
        if (isalpha(letter)) {
            bool check = isupper(letter);
            char z = check ? 'A' : 'a';
            int keys = tolower(key_input[i % key_length]) - 'a';
            char e_letter = (letter - z + keys) % 26 + z;
            output_d += e_letter;
        }
        else {
            output_d += letter;
        }
    }
    return output_d;
}

string decrypt(const string& encrypted, const string& key_input) {
    string output = "";
    int key_length = key_input.length();
    for (size_t i = 0; i < encrypted.length(); i++) {
        char letter = encrypted[i];
        if (isalpha(letter)) {
            bool check = isupper(letter);
            char z = check ? 'A' : 'a';
            int keys = tolower(key_input[i % key_length]) - 'a';
            char d_letter = (letter - z - keys) % 26 + z;
            output += d_letter;
        }
        else {
            output += letter;
        }
    }
    return output;
}
void readFileContent(const string& fileName, string& content) {
    ifstream file(fileName);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            content += line + '\n';
        }
        file.close();
    }
}

int main(int argc, char* argv[]) {
    string input;
    string output;
    string key_input;
    string key;
    string output_d;
    string inputFile, outputFile, keyFile;
    string inputText, keyInput, result;
    for (int i = 1; i < argc; i++) {
        cout << argv[i] << ' ';
        if (strcmp(argv[i], "-i") == 0) {
            inputFile = argv[i + 1];
        }
        if (strcmp(argv[i], "-o") == 0) {
            outputFile = argv[i + 1];
        }
        if (strcmp(argv[i], "-klucz") == 0) {
            keyFile = argv[i + 1];
        }
        if (strcmp(argv[i], "-h") == 0) {
            ifstream help("help.txt");
            string line;
            while (getline(help, line)) {
                cout << line << endl;
            }
            help.close();
        }
        if (strcmp(argv[i], "-key") == 0) {
            ifstream key("klucz.txt");
            string line;
            while (getline(key, line)) {
                cout << line << endl;
            }
            key.close();
        }
        if (strcmp(argv[i], "-e") == 0) {
            readFileContent(inputFile, inputText);
            readFileContent(keyFile, keyInput);
            result = encrypt(inputText, keyInput);
            if (!outputFile.empty()) {
                ofstream output(outputFile);
                output << result;
                output.close();
            }
            cout << result;
        }
        if (strcmp(argv[i], "-d") == 0) {
            readFileContent(inputFile, inputText);
            readFileContent(keyFile, keyInput);
            result = decrypt(inputText, keyInput);
            if (!outputFile.empty()) {
                ofstream output(outputFile);
                output << result;
                output.close();
                cout << result;
            }
        }
    }
}