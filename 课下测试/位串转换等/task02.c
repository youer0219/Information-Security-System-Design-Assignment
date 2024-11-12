#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Helper function to convert a single hex character to a 4-bit binary string
void hexCharToBinary(char c, char *output) {
    int num = (c >= '0' && c <= '9') ? c - '0' : (c >= 'A' && c <= 'F') ? 10 + c - 'A' : 10 + c - 'a';
    for (int i = 3; i >= 0; --i) {
        output[3-i] = (num & (1 << i)) ? '1' : '0';
    }
}

// Function to convert a hex string to a binary string
void hexStringToBinaryString(const char *hexString, char *binaryString) {
    int len = strlen(hexString);
    char binSegment[5]; // Temporary storage for binary segments
    binSegment[4] = '\0'; // Null-terminator for strings
    binaryString[0] = '\0'; // Initialize the binary string as empty

    for (int i = 0; i < len; ++i) {
        hexCharToBinary(hexString[i], binSegment);
        strcat(binaryString, binSegment); // Concatenate the binary segment to the full binary string
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <hexadecimal string>\n", argv[0]);
        return 1;
    }

    char *hexString = argv[1];
    char binaryString[513]; // Enough to convert 128 hex digits to binary

    hexStringToBinaryString(hexString, binaryString);
    printf("Binary string: %s\n", binaryString);

    return 0;
}
