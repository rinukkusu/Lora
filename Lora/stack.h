#include <Windows.h>
#include "variable.h"

class CStack
{
private:
	struct StackVar
	{
		CVariable *pVariable;
		int nLevel;
		StackVar *pNext;
		StackVar *pPrev;
	};

	StackVar *m_pStackHead;
	StackVar *m_pStackBottom;

public:
	CStack(void);
	~CStack(void);

	StackVar* Add(CVariable *pVariable, int nLevel);
	bool Delete(char *cName, int nLevel = -1);
	void DeleteAll();
	StackVar* GetLast();
	StackVar* Search(char *cName, int nLevel);

	CVariable* GetVar(char *cName, BYTE *pData, UINT nLength, int nLevel = -1);
	bool SetVar(char *cName, BYTE *pData, UINT nLength, int nLevel = -1);

};