
#include "SM2_sv.h"

void main()
{
	if (SM2_SelfCheck())
	{
		puts("SM2 签名验签出错");
		return;
	}
	puts("SM2 签名验签成功");
}
