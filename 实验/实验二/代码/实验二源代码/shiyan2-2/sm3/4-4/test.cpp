// test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <string.h>
#include <stdio.h>
#include "sm3.h"

int main(int argc, char *argv[])
{
	unsigned char *input = (unsigned char*)"abc";
	unsigned char *key = (unsigned char*)"123456";
	int ilen = 3;
	unsigned char output[32];
	int i;
	sm3_context ctx;

	printf("Message: ");
	printf("%s\n", input);

	sm3_hmac(key, 6, input, 3, output);
	printf("HMAC:   ");
	for (i = 0; i < 32; i++)
	{
		printf("%02x", output[i]);
		if (((i + 1) % 4) == 0) printf(" ");
	}
	printf("\n");

}
