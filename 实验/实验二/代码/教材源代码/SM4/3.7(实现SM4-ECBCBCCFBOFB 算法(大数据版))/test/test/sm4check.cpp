#include "pch.h"
#include "sm4.h"
#include <stdio.h>
#include <string.h>


int sm4ecbcheck()
{
	int i,len,ret = 0;
	unsigned char key[16] = { 0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10 };
	unsigned char plain[16] = { 0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10 };
	unsigned char cipher[16] = { 0x68,0x1e,0xdf,0x34,0xd2,0x06,0x96,0x5e,0x86,0xb3,0xe9,0x4f,0x53,0x6e,0x42,0x46 };
	unsigned char En_output[16];
	unsigned char De_output[16];
	unsigned char in[4096], out[4096], chk[4096];

	sm4ecb(plain, En_output, 16, key, SM4_ENCRYPT);
	if (memcmp(En_output, cipher, 16)) puts("ecb enc(len=16) memcmp failed");
	else puts("ecb enc(len=16) memcmp ok");

	sm4ecb(cipher, De_output, SM4_BLOCK_SIZE, key, SM4_DECRYPT);
	if (memcmp(De_output, plain, SM4_BLOCK_SIZE)) puts("ecb dec(len=16) memcmp failed");
	else puts("ecb dec(len=16) memcmp ok");

	len = 32;
	for (i = 0; i < 8; i++)
	{
		memset(in, i, len);
		sm4ecb(in, out, len, key, SM4_ENCRYPT);
		sm4ecb(out, chk, len, key, SM4_DECRYPT);
		if (memcmp(in, chk, len))  printf("ecb enc/dec(len=%d) memcmp failed\n", len);
		else printf("ecb enc/dec(len=%d) memcmp ok\n", len);
		len = 2 * len;
	}
	return 0;
}


int sm4cbccheck()
{
	int i, len, ret = 0;
	unsigned char key[16] = { 0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10 };//密钥
	unsigned char iv[16] = { 0xeb,0xee,0xc5,0x68,0x58,0xe6,0x04,0xd8,0x32,0x7b,0x9b,0x3c,0x10,0xc9,0x0c,0xa7 }; //初始化向量
	unsigned char plain[32] = { 0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10,0x29,0xbe,0xe1,0xd6,0x52,0x49,0xf1,0xe9,0xb3,0xdb,0x87,0x3e,0x24,0x0d,0x06,0x47 }; //明文
	unsigned char cipher[32] = { 0x3f,0x1e,0x73,0xc3,0xdf,0xd5,0xa1,0x32,0x88,0x2f,0xe6,0x9d,0x99,0x6c,0xde,0x93,0x54,0x99,0x09,0x5d,0xde,0x68,0x99,0x5b,0x4d,0x70,0xf2,0x30,0x9f,0x2e,0xf1,0xb7 }; //密文

	unsigned char En_output[32];
	unsigned char De_output[32];
	unsigned char in[4096], out[4096], chk[4096];

	sm4cbc(plain, En_output, sizeof(plain), key,iv, SM4_ENCRYPT);
	if (memcmp(En_output, cipher, 16)) puts("cbc enc(len=32) memcmp failed");
	else puts("cbc enc(len=32) memcmp ok");

	sm4cbc(cipher, De_output, SM4_BLOCK_SIZE, key,iv, SM4_DECRYPT);
	if (memcmp(De_output, plain, SM4_BLOCK_SIZE)) puts("cbc dec(len=32) memcmp failed");
	else puts("cbc dec(len=32) memcmp ok");

 
	len = 32;
	for (i = 0; i < 8; i++)
	{
		memset(in, i, len);
		sm4cbc(in, out, len, key,iv, SM4_ENCRYPT);
		sm4cbc(out, chk, len, key,iv, SM4_DECRYPT);
		if (memcmp(in, chk, len))  printf("cbc enc/dec(len=%d) memcmp failed\n", len);
		else printf("cbc enc/dec(len=%d) memcmp ok\n", len);
		len = 2 * len;
	}
	return 0;
}

int sm4cfbcheck()
{
	int i, len, ret = 0;
	unsigned char key[16] = { 0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10 };//密钥
	unsigned char iv[16] = { 0xeb,0xee,0xc5,0x68,0x58,0xe6,0x04,0xd8,0x32,0x7b,0x9b,0x3c,0x10,0xc9,0x0c,0xa7 }; //初始化向量
	unsigned char in[4096], out[4096], chk[4096];
	len = 16;
	for (i = 0; i < 9; i++)
	{
		memset(in, i, len);
		sm4cfb(in, out, len, key, iv, SM4_ENCRYPT);
		sm4cfb(out, chk, len, key, iv, SM4_DECRYPT);
		if (memcmp(in, chk, len))  printf("cfb enc/dec(len=%d) memcmp failed\n", len);
		else printf("cfb enc/dec(len=%d) memcmp ok\n", len);
		len = 2 * len;
	}
	return 0;
}

int sm4ofbcheck()
{
	int i, len, ret = 0;
	unsigned char key[16] = { 0x01,0x23,0x45,0x67,0x89,0xab,0xcd,0xef,0xfe,0xdc,0xba,0x98,0x76,0x54,0x32,0x10 };//密钥
	unsigned char iv[16] = { 0xeb,0xee,0xc5,0x68,0x58,0xe6,0x04,0xd8,0x32,0x7b,0x9b,0x3c,0x10,0xc9,0x0c,0xa7 }; //初始化向量
	unsigned char in[4096], out[4096], chk[4096];
	len = 16;
	for (i = 0; i < 9; i++)
	{
		memset(in, i, len);
		sm4ofb(in, out, len, key, iv);
		sm4ofb(out, chk, len, key, iv);
		if (memcmp(in, chk, len))  printf("ofb enc/dec(len=%d) memcmp failed\n", len);
		else printf("ofb enc/dec(len=%d) memcmp ok\n", len);
		len = 2 * len;
	}
	return 0;
}

