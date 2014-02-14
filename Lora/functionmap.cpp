#include <Windows.h>
#include <string>
#include "functionmap.h"
#include <time.h>

using namespace::std;

functions::functions()
{
	nFuncCount[0] = 0;
	nFuncCount[1] = 0;
	nFuncCount[2] = 0;

	srand(time(NULL));

	AddFunction_1("Print", (sfunc_1*)&PrintText);
	AddFunction_2("Random", (sfunc_2*)&Random);
}

void* functions::GetFunction(std::string strFunctionName, int nParams)
{
	for (int i = 0; i < nFuncCount[nParams]; i++)
	{
		switch (nParams)
		{
		case 0:
			if (m_Func0[i].strFunctionName.compare(strFunctionName) == 0)
				return m_Func0[i].pFunction;
			break;
		case 1:
			if (m_Func1[i].strFunctionName.compare(strFunctionName) == 0)
					return m_Func1[i].pFunction;
			break;
		case 2:
			if (m_Func2[i].strFunctionName.compare(strFunctionName) == 0)
					return m_Func2[i].pFunction;
			break;
		default:
			return NULL;
		}
	}

	return NULL;
}

bool functions::AddFunction_0(std::string strFunctionName, sfunc_0* pFunction)
{
	int nParams = 0;
	m_Func0[nFuncCount[nParams]].pFunction = (sfunc_0*)pFunction;
	m_Func0[nFuncCount[nParams]].strFunctionName = strFunctionName;

	nFuncCount[nParams]++;
	if (nFuncCount[nParams] == FUNCTION_MAP_SIZE) {
		nFuncCount[nParams]--;
		return false;
	}

	return true;
}

bool functions::AddFunction_1(std::string strFunctionName, sfunc_1* pFunction)
{
	int nParams = 1;
	m_Func1[nFuncCount[nParams]].pFunction = (sfunc_1*)pFunction;
	m_Func1[nFuncCount[nParams]].strFunctionName = strFunctionName;

	nFuncCount[nParams]++;
	if (nFuncCount[nParams] == FUNCTION_MAP_SIZE) {
		nFuncCount[nParams]--;
		return false;
	}

	return true;
}

bool functions::AddFunction_2(std::string strFunctionName, sfunc_2* pFunction)
{
	int nParams = 2;
	m_Func2[nFuncCount[nParams]].pFunction = (sfunc_2*)pFunction;
	m_Func2[nFuncCount[nParams]].strFunctionName = strFunctionName;

	nFuncCount[nParams]++;
	if (nFuncCount[nParams] == FUNCTION_MAP_SIZE) {
		nFuncCount[nParams]--;
		return false;
	}

	return true;
}


bool functions::PrintText(void* pVar)
{
	printf("%s\r\n", (char*)pVar);
	return true;
}

bool functions::Random(void* pMin, void* pMax)
{
	int nMin = stoi(*(string*)pMin);
	int nMax = stoi(*(string*)pMax);

	int nRandom = (rand() % (nMax - nMin)) + nMin;

	printf("%i\r\n", nRandom);
	return true;
}