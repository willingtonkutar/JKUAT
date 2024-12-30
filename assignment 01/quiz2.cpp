#include <iostream>
#include <vector>

void reverseArray(std::vector<int>& arr) {
    int start = 0;
    int end = arr.size() - 1;
    int temp;

    while (start < end) {
        // Swap the elements
        temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;

        // Move towards the middle
        start++;
        end--;
    }
}

// Function to print the array (for testing purposes)
void printArray(const std::vector<int>& arr) {
    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> arr = {1, 2, 3, 4, 5};

    std::cout << "Original array: ";
    printArray(arr);

    reverseArray(arr);

    std::cout << "Reversed array: ";
    printArray(arr);

    return 0;
}