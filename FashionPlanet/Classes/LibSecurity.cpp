#include "Global.h"


void initSecurity(SECURITY *Security, int value)
{
	memset(Security, 0, sizeof(SECURITY));
	setSecurity(Security ,value);	
}

void setSecurity(SECURITY *Security ,int value)
{
	if(getSecurity(Security) == FALSE)
	{
		//해킹감지
		if(xGame.isHacking == FALSE)
			setHackingPopup(0);
		return;
	}
	
	int checksum = sizeof(value);
	int length = sizeof(value);
	
	//실제값 기록
	Security->oriData = value;
	
	//체크섬 구하기
	for(int i=0; i<length; i++)
	{
		checksum += *((unsigned char*)&value + i);
	}
	checksum = checksum % 255;
	
	Security->checkSum = checksum;
	
	//XOR 연산으로 암호화
	for(int i=0; i<length; i++)
	{
		*((unsigned char*)&Security->encData + i) = *((unsigned char*)&value + i) ^ checksum;
	}
}

M_Boolean getSecurity(SECURITY *Security)
{
	int temp;
	int length = sizeof(temp);
	
	//XOR 연산으로 복호화
	for(int i=0; i<length; i++)
	{
		*((unsigned char*)&temp + i) = *((unsigned char*)&Security->encData + i) ^ Security->checkSum;
	}
	
	//데이타 비교
	if(Security->oriData != temp)
	{
		//이게 뚫린건가...
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}



