// test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <stdio.h>
#include <memory>
#include <cstring>
#include <cstdint>  // 包含标准整数类型

unsigned char IV[256 / 8] = { 0x73,0x80,0x16,0x6f,0x49,0x14,0xb2,0xb9,0x17,0x24,0x42,0xd7,0xda,0x8a,0x06,0x00,0xa9,0x6f,0x30,0xbc,0x16,0x31,0x38,0xaa,0xe3,0x8d,0xee,0x4d,0xb0,0xfb,0x0e,0x4e };

// 循环左移
unsigned long SL(unsigned long X, int n)
{
	uint64_t x = X;  // 修改为标准类型
	x = x << (n % 32);
	unsigned long l = (unsigned long)(x >> 32);
	return x | l;
}

unsigned long Tj(int j)
{
	if (j <= 15)
	{
		return 0x79cc4519;
	}
	else
	{
		return 0x7a879d8a;
	}
}

unsigned long FFj(int j, unsigned long X, unsigned long Y, unsigned long Z)
{
	if (j <= 15)
	{
		return X ^ Y ^ Z;
	}
	else
	{
		return (X & Y) | (X & Z) | (Y & Z);
	}
}

unsigned long GGj(int j, unsigned long X, unsigned long Y, unsigned long Z)
{
	if (j <= 15)
	{
		return X ^ Y ^ Z;
	}
	else
	{
		return (X & Y) | (~X & Z);
	}
}

unsigned long P0(unsigned long X)
{
	return X ^ SL(X, 9) ^ SL(X, 17);
}

unsigned long P1(unsigned long X)
{
	return X ^ SL(X, 15) ^ SL(X, 23);
}

// 扩展
void EB(unsigned char Bi[512 / 8], unsigned long W[68], unsigned long W1[64])
{
	// Bi 分为W0~W15
	for (int i = 0; i < 16; ++i)
	{
		W[i] = Bi[i * 4] << 24 | Bi[i * 4 + 1] << 16 | Bi[i * 4 + 2] << 8 | Bi[i * 4 + 3];
	}

	for (int j = 16; j <= 67; ++j)
	{
		W[j] = P1(W[j - 16] ^ W[j - 9] ^ SL(W[j - 3], 15)) ^ SL(W[j - 13], 7) ^ W[j - 6];
	}

	for (int j = 0; j <= 63; ++j)
	{
		W1[j] = W[j] ^ W[j + 4];
	}
}

// 压缩函数
void CF(unsigned char Vi[256 / 8], unsigned char Bi[512 / 8], unsigned char Vi1[256 / 8])
{
	// Bi 扩展为132个字
	unsigned long W[68] = { 0 };
	unsigned long W1[64] = { 0 };

	EB(Bi, W, W1);

	// 串联 ABCDEFGH = Vi
	unsigned long R[8] = { 0 };
	for (int i = 0; i < 8; ++i)
	{
		R[i] = ((unsigned long)Vi[i * 4]) << 24 | ((unsigned long)Vi[i * 4 + 1]) << 16 | ((unsigned long)Vi[i * 4 + 2]) << 8 | ((unsigned long)Vi[i * 4 + 3]);
	}

	unsigned long A = R[0], B = R[1], C = R[2], D = R[3], E = R[4], F = R[5], G = R[6], H = R[7];

	unsigned long SS1, SS2, TT1, TT2;
	for (int j = 0; j <= 63; ++j)
	{
		SS1 = SL(SL(A, 12) + E + SL(Tj(j), j), 7);
		SS2 = SS1 ^ SL(A, 12);
		TT1 = FFj(j, A, B, C) + D + SS2 + W1[j];
		TT2 = GGj(j, E, F, G) + H + SS1 + W[j];
		D = C;
		C = SL(B, 9);
		B = A;
		A = TT1;
		H = G;
		G = SL(F, 19);
		F = E;
		E = P0(TT2);
	}

	// Vi1 = ABCDEFGH 串联
	R[0] = A, R[1] = B, R[2] = C, R[3] = D, R[4] = E, R[5] = F, R[6] = G, R[7] = H;
	for (int i = 0; i < 8; ++i)
	{
		Vi1[i * 4] = (R[i] >> 24) & 0xFF;
		Vi1[i * 4 + 1] = (R[i] >> 16) & 0xFF;
		Vi1[i * 4 + 2] = (R[i] >> 8) & 0xFF;
		Vi1[i * 4 + 3] = (R[i]) & 0xFF;
	}
	// Vi1 = ABCDEFGH ^ Vi
	for (int i = 0; i < 256 / 8; ++i)
	{
		Vi1[i] ^= Vi[i];
	}
}

//参数 m 是原始数据，ml 是数据长度，r 是输出参数,存放hash结果
void SM3Hash(unsigned char* m, int ml, unsigned char r[32])
{
	int l = ml * 8;
	int k = 448 - 1 - l % 512; // 添加k个0，k 是满足 l + 1 + k ≡ 448mod512 的最小的非负整数
	if (k <= 0)
	{
		k += 512;
	}

	int n = (l + k + 65) / 512;

	int m1l = n * 512 / 8; // 填充后的长度，512位的倍数
	unsigned char* m1 = new unsigned char[m1l];
	memset(m1, 0, m1l);
	memcpy(m1, m, l / 8);

	m1[l / 8] = 0x80; // 消息后补1

	// 再添加一个64位比特串，该比特串是长度l的二进制表示
	unsigned long l1 = l;
	for (int i = 0; i < 64 / 8 && l1 > 0; ++i)
	{
		m1[m1l - 1 - i] = l1 & 0xFF;
		l1 = l1 >> 8;
	}

	//将填充后的消息m′按512比特进行分组：m′ = B(0)B(1)· · · B(n−1),其中n=(l+k+65)/512。
	unsigned char** B = new unsigned char*[n];
	for (int i = 0; i < n; ++i)
	{
		B[i] = new unsigned char[512 / 8];
		memcpy(B[i], m1 + (512 / 8)*i, 512 / 8);
	}

	delete[] m1;

	unsigned char** V = new unsigned char*[n + 1];
	for (int i = 0; i <= n; ++i)
	{
		V[i] = new unsigned char[256 / 8];
		memset(V[i], 0, 256 / 8);
	}

	// 初始化 V0 = VI
	memcpy(V[0], IV, 256 / 8);

	// 压缩函数，V 与扩展的B
	for (int i = 0; i < n; ++i)
	{
		CF(V[i], B[i], V[i + 1]);
	}

	for (int i = 0; i < n; ++i)
	{
		delete[] B[i];
	}
	delete[] B;

	// V[n]是结果
	memcpy(r, V[n], 32);

	for (int i = 0; i <= n; ++i)
	{
		delete[] V[i];
	}
	delete[] V;
}

// 打印缓冲区内容
void dumpbuf(unsigned char* buf, int len) 
{
	for (int i = 0; i < len; ++i) {
		printf("%02x", buf[i]);
		if ((i + 1) % 16 == 0) 
		printf("\n");
		else
			printf(" ");
	}
	printf("\n");
}

int main() 
{
	// 输入数据
	unsigned char message[] = "abc";
	int message_len = strlen((char*)message);

	// 输出缓冲区
	unsigned char hash_result[32] = { 0 };

	// 调用 SM3 哈希函数
	SM3Hash(message, message_len, hash_result);

	// 输出哈希结果
	printf("SM3 Hash:\n");
	dumpbuf(hash_result, 32);

	return 0;
}
