#include <iostream>
#include <cmath>

using namespace std;

// Function to check if a number is prime
bool isPrime(int num) {
    if (num < 2) {
        return false; // Numbers less than 2 are not prime
    }
    for (int i = 2; i <= sqrt(num); i++) { // Check for factors up to the square root of num
        if (num % i == 0) {
            return false; // Found a factor, so not prime
        }
    }
    return true; // No factors found, so it is prime
}

// Main function to print all prime numbers between 1 and 100
int main() {
    cout << "Prime numbers between 1 and 100 are:\n";
    for (int number = 1; number <= 100; number++) {
        if (isPrime(number)) {
            cout << number << " "; // Print the prime number
        }
    }
    cout << endl; // New line for clean output
    return 0; // Exit program
}
