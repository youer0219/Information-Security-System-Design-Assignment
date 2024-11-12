#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 函数功能：将位串转换为字节串
// 参数：bitString为输入的位串，byteString为输出的字节串存储缓冲区
void bitStringToByteString(const char *bitString, char *byteString) {
    int blen = strlen(bitString);
    int mlen = (blen + 7) / 8; // 计算所需字节数
    int paddedLength = mlen * 8; // 填充后的长度

    // 为填充后的位串分配缓冲区并初始化为0
    char *paddedBitString = (char *)calloc(paddedLength + 1, sizeof(char));
    for (int i = 0; i < paddedLength - blen; i++) {
        paddedBitString[i] = '0'; // 添加前导0
    }
    // 追加原始位串
    strcat(paddedBitString, bitString);

    for (int i = 0; i < mlen; i++) {
        char byte[9]; // 临时存储8位 + 空终止符
        strncpy(byte, paddedBitString + 8 * i, 8);
        byte[8] = '\0'; // 空终止字符串

        // 将8位二进制字符串转换为字节
        unsigned char byteValue = (unsigned char)strtol(byte, NULL, 2);
        sprintf(byteString + 2 * i, "%02X", byteValue);
    }
    free(paddedBitString); // 释放分配的内存
}

int main(int argc, char *argv[]) {
    if (argc!= 2) {
        // 如果命令行参数数量不等于2（程序名 + 位串参数），则打印错误信息并退出
        printf("用法：%s [位串]\n", argv[0]);
        return 1;
    }

    // 获取命令行输入的位串
    const char *input = argv[1];

    // 检查输入是否有效（只包含'0'和'1'）
    for (int i = 0; i < strlen(input); i++) {
        if (input[i]!= '0' && input[i]!= '1') {
            printf("输入无效，请确保输入只包含 '0' 和 '1'。\n");
            return 1;
        }
    }

    // 准备存储输出字节串的缓冲区
    char output[100]; // 根据需要确保足够大
    memset(output, 0, sizeof(output)); // 初始化 为零

    // 将位串转换为字节串
    bitStringToByteString(input, output);

    // 打印转换后的字节串
    printf("转换后的字节串是：%s\n", output);

    return 0;
}
