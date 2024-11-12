#include <stdio.h>
#include <stdlib.h>

// 函数声明：将整数转换为8位字节串
void int_to_bytes(int x, int mlen, unsigned char *M);

int main(int argc, char *argv[]) {
    // 确保传入正确的参数
    if (argc != 3) {
        printf("Usage: %s <integer> <byte length>\n", argv[0]);
        return 1;
    }

    // 解析命令行参数
    int x = atoi(argv[1]);  // 整数x
    int mlen = atoi(argv[2]);  // 字节串长度mlen

    // 检查长度是否合理
    if (mlen <= 0 || mlen > 4) {  // 假设我们支持最大4字节（32位）整数
        printf("Error: mlen should be between 1 and 4\n");
        return 1;
    }

    // 创建一个数组来存储结果字节串
    unsigned char M[mlen];

    // 调用转换函数
    int_to_bytes(x, mlen, M);

    // 输出转换后的字节串
    printf("Byte array (in hexadecimal): ");
    for (int i = 0; i < mlen; i++) {
        printf("%02X ", M[i]);
    }
    printf("\n");

    return 0;
}

// 实现整数到8位字节串的转换
void int_to_bytes(int x, int mlen, unsigned char *M) {
    for (int i = 0; i < mlen; i++) {
        M[i] = (unsigned char)((x >> (8 * (mlen - 1 - i))) & 0xFF);
    }
}
