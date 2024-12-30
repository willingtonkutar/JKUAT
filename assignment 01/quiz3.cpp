#include <iostream>
#include <string>

using namespace std;

// Function to count the number of vowels in a string
int countVowels(const string& str) {
    int count = 0;
    for (char ch : str) {
        // Check if the character is a vowel (both uppercase and lowercase)
        if (ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' ||
            ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U') {
            count++;
        }
    }
    return count;
}

int main() {
    string input;
    cout << "Enter a string: ";
    getline(cin, input);

    int vowelCount = countVowels(input);
    cout << "Number of vowels: " << vowelCount << endl;

    return 0;
}