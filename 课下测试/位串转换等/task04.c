#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 函数用于将十六进制字符转换为对应的十进制值
int hexCharToDecimal(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'F') return 10 + c - 'A';
    if (c >= 'a' && c <= 'f') return 10 + c - 'a';
    return -1; // 非法字符
}

// 函数用于将十六进制字符串转换为整数
unsigned long hexStringToDecimal(const char *hexStr, int mlen) {
    unsigned long decimalValue = 0;
    for (int i = 0; i < mlen; ++i) {
        int hexValue = hexCharToDecimal(hexStr[i]);
        if (hexValue == -1) {
            fprintf(stderr, "Invalid hexadecimal character: %c\n", hexStr[i]);
            exit(EXIT_FAILURE);
        }
        decimalValue = (decimalValue << 4) + hexValue;
    }
    return decimalValue;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <hex_string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int mlen = strlen(argv[1]);
    unsigned long x = hexStringToDecimal(argv[1], mlen);

    printf("The integer x is: %lu\n", x);

    return EXIT_SUCCESS;
}
