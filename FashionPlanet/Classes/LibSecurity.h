#ifndef __LIB_SECURITY_H__
#define __LIB_SECURITY_H__

typedef struct _SECURITY
{
	unsigned char checkSum;
	int encData;
	int oriData;
} SECURITY;


void initSecurity(SECURITY *Security, int value);
void setSecurity(SECURITY *Security ,int value);
M_Boolean getSecurity(SECURITY *Security);

#endif