#include <Windows.h>
#include "variable.h"

CVariable::CVariable(char *pcName)
{
	cName = new char[sizeof(pcName)+1];
	strcpy(cName, pcName);
	pData = NULL;
	nId = 0;
	nLength = 0;
	nVarType = TYPE_DEFAULT;
}


CVariable::~CVariable(void)
{
	if (cName) delete cName;
	if (pData) delete pData;
}