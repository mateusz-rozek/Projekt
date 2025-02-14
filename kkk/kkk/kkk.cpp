#include <iostream>
#include <fstream>
#include <cctype>
#include <string>

using namespace std;

string encrypting(const string& inputFile, const string& keyFile) {
    ifstream input(inputFile);
    if (!input) {
        cerr << "Error: Nie mozna otworzyc pliku wejsciowego!" << endl;
        return "";
    }
    string inputText((istreambuf_iterator<char>(input)), istreambuf_iterator<char>());
    input.close();

    ifstream keyInput(keyFile);
    if (!keyInput) {
        cerr << "Error: Nie mozna otworzyc pliku klucza!" << endl;
        return "";
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
    return result;
}

string decrypting(const string& inputFile, const string& keyFile) {
    ifstream input(inputFile);
    if (!input) {
        cerr << "Error: Nie mozna otworzyc pliku wejsciowego!" << endl;
        return "";
    }
    string inputText((istreambuf_iterator<char>(input)), istreambuf_iterator<char>());
    input.close();

    ifstream keyInput(keyFile);
    if (!keyInput) {
        cerr << "Error: Nie mozna otworzyc pliku klucza!" << endl;
        return "";
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
    return result;
}

void writeToFile(const string& outputFile, const string& content) {
    ofstream output(outputFile);
    if (!output) {
        cerr << "Error: Nie mozna otworzyc pliku wyjsciowego!" << endl;
        return;
    }
    output << content;
    output.close();
}

int main(int argc, char* argv[]) {
    string inputFile, keyFile, outputFile;
    bool encrypt = true;

    for (int i = 0; i < argc; i++) {
        cout << argv[i] << ' ';
        if (strcmp(argv[i], "-i") == 0) {
            inputFile = argv[i + 1];
            i++;
        }
        if (strcmp(argv[i], "-o") == 0) {
            outputFile = argv[i + 1];
            i++;
        }
        if (strcmp(argv[i], "-k") == 0) {
            keyFile = argv[i + 1];
            i++;
        }
        if (strcmp(argv[i], "-h") == 0) {
            ifstream help("help.txt");
            string line;
            while (getline(help, line)) {
                cout << line << endl;
            }
            help.close();
        }
        if (strcmp(argv[i], "-e" == 0)) {
            bool encrypt = true;
                i++;
        }
        if (strcmp(argv[i], "-d" == 0)) {
            bool encrypt = false;
            i++;
        }
    }

    string result;
    if (encrypt) {
        result = encrypting(inputFile, keyFile);
    }
    else {
        result = decrypting(inputFile, keyFile);
    }

    if (!outputFile.empty()) {
        writeToFile(outputFile, result);
    }
    else {
        cout << result;
    }

    return 0;
}