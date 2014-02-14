#include <Windows.h>
#include <string>
#include <vector>
#include "stack.h"
#include "functionmap.h"

using namespace std;

#pragma once

struct LastScriptError {
	char* pcError;
	char* pcLine;
	int nLine;
};

class CParser
{
public:
	CParser(void);
	~CParser(void);

	bool ReadFile(char* pcFilepath);
	bool ParseScript(char* pcScript = NULL);
	bool ParseLine(string* pstrLine);
	void SetError(char* pcError, char* pcLine, int nLine = -1);
	void Reset();

	static bool PopParam(string* pstrParams, string* pstrParam);
	static vector<string> CreateParamList(string* pstrParams);

private:
	char* m_pcScript;
	LastScriptError m_lastError;

public:
	CStack m_VarStack;
	bool m_bError;
	functions m_Functions;
};

