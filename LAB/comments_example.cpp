#include <iostream>
#include <string>

// Function that creates a string of a specified length and returns it
std::string createString(size_t length, char fillChar) {
    // Create a character array of the specified length, filled with the fillChar
    char* arr = new char[length + 1]; // +1 for the null terminator
    std::fill_n(arr, length, fillChar);
    arr[length] = '\0'; // Null terminator
    
    // Create a string from the character array
    std::string str(arr);
    
    // Clean up the allocated memory for the character array
    delete[] arr;
    
    return str;
}

int main() {
    // Specify the length and the character to fill the string with
    size_t length = 10;
    char fillChar = 'a';
    
    // Call the function and get the resulting string
    std::string result = createString(length, fillChar);
    
    // Output the string
    std::cout << "Resulting string: " << result << std::endl;
    
    return 0;
}
