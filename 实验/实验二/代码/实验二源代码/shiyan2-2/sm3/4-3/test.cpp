#include <stdio.h>
#include <string.h>
#include "sm3hash.h"

int main(void)
{
	const unsigned char sample1[] = { 'a', 'b', 'c', 0 };
	unsigned int sample1_len = strlen((char *)sample1);
	const unsigned char sample2[] = { 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64,
										 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64,
										 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64,
										 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64,
										 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64,
										 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64,
										 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64,
										 0x61, 0x62, 0x63, 0x64, 0x61, 0x62, 0x63, 0x64 };
	unsigned int sample2_len = sizeof(sample2);
	unsigned char hash_value[64];
	unsigned int i, hash_len;

	sm3_hash(sample1, sample1_len, hash_value, &hash_len);
	printf("raw data: %s\n", sample1);
	printf("hash length: %d bytes.\n", hash_len);
	printf("hash value:\n");
	for (i = 0; i < hash_len; i++)
	{
		printf("0x%x  ", hash_value[i]);
	}
	printf("\n\n");

	sm3_hash(sample2, sample2_len, hash_value, &hash_len);
	printf("raw data:\n");
	for (i = 0; i < sample2_len; i++)
	{
		printf("0x%x  ", sample2[i]);
	}
	printf("\n");
	printf("hash length: %d bytes.\n", hash_len);
	printf("hash value:\n");
	for (i = 0; i < hash_len; i++)
	{
		printf("0x%x  ", hash_value[i]);
	}
	printf("\n");

	return 0;
}
 
