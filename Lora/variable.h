#include "global.h"

enum VarType
{
	TYPE_DEFAULT,
	TYPE_INT,
	TYPE_DOUBLE,
	TYPE_STRING
};

class CVariable
{
public:
	CVariable(char *pcName);
	~CVariable(void);

	int nId;
	char *cName;
	void *pData;
	UINT nLength;
	int nVarType;

	
};