#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;


string encrypt(const string& input, const string& key_input) {
    string output = "";
    int key_length = key_input.length();
    for (size_t i = 0; i < input.length(); i++) {
        char letter = input[i];
        if (isalpha(letter)) {
            bool check = isupper(letter);
            char z = check ? 'A' : 'a';
            int keys = tolower(key_input[i % key_length]) - 'a';
            char e_letter = (letter - z + keys) % 26 + z;
            output += e_letter;
        }
        else {
            output += letter;
        }
    }
    return output;
}

int main(int argc, char* argv[]) {
    string input;
    string output;
    string key_input;
    string key;
    for (int i = 1; i < argc; i++) {
        cout << argv[i] << ' ';
        if (strcmp(argv[i],  "-h") == 0) {
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
            string input;
            string key_input;
            cout << "wprowadz tekst: " << endl;
            getline(cin, input);
            cout << "wprowadz klucz: " << endl;
            getline(cin, key_input);
            string encrypted = encrypt(input, key_input);
            cout << encrypted << endl;
        }
    }
}
