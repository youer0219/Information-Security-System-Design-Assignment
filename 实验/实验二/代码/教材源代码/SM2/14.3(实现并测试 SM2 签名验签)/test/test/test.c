
#include "SM2_sv.h"

void main()
{
	if (SM2_SelfCheck())
	{
		puts("SM2ǩ����ǩ����");
		return;
	}
	puts("SM2ǩ����ǩ�ɹ�");
}