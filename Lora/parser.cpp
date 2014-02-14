#include "parser.h"
#include <stdio.h>


void strclr(char* pcMem, int nSize)
{
	for (int i = 0; i < nSize; i++)
		pcMem[i] = '\0';
}

CParser::CParser(void)
{
	m_pcScript = NULL;
	m_bError = false;

	m_lastError.nLine = -1;
	m_lastError.pcError = (char*) calloc(250, sizeof(char));
	m_lastError.pcLine = (char*) calloc(250, sizeof(char));
}

CParser::~CParser(void)
{
	if (m_pcScript) free(m_pcScript);
	if (m_lastError.pcError) free(m_lastError.pcError);
	if (m_lastError.pcLine) free(m_lastError.pcLine);
}

void CParser::Reset()
{
	if (m_pcScript) free(m_pcScript);
	m_bError = false;

	m_lastError.nLine = -1;
	strclr(m_lastError.pcError, 250);
	strclr(m_lastError.pcLine, 250);
}

bool CParser::ReadFile(char* pcFilepath)
{
	FILE* pFile;
	long lSize;
	size_t sResult;
	
	// try to open the file
	pFile = fopen(pcFilepath, "r");
	if (!pFile) return false;

	// get the file size
	fseek(pFile, 0, SEEK_END);
	lSize = ftell(pFile);
	rewind(pFile);

	// allocate memory for the script
	if (m_pcScript) delete m_pcScript;
	m_pcScript = (char *) calloc(lSize, sizeof(char));

	if (!m_pcScript) return false;

	// read file to end
	sResult = fread(m_pcScript, 1, lSize, pFile);

	fclose(pFile);
	return true;
}

bool CParser::ParseScript(char* pcScript)
{
	if (!pcScript) {
		if (!m_pcScript) return false;
		else pcScript = m_pcScript;
	}

	string strScript(pcScript);
	int nPos = 0;
	int nFoundNewline = strScript.find("\n", nPos);

	while (nFoundNewline >= 0) {
		string strLine = strScript.substr(nPos, nFoundNewline - nPos);

		bool bReturn = ParseLine(&strLine);
		if (!bReturn) return false;
		
		nPos = nFoundNewline + 1;
		nFoundNewline = strScript.find("\n", nPos);
	}
	
	return true;
}

bool CParser::ParseLine(string* pstrLine)
{
	if (!pstrLine) {
		SetError("pstrLine is NULL", "");
		return false;
	}

	int nLine = pstrLine->find("(", 0);
	if (nLine >= 0) {
		int nParamStart = pstrLine->find("(", 0);
		int nParamEnd = pstrLine->find(")", nParamStart);

		string strCommand = pstrLine->substr(0, nParamStart);
		string strParams = pstrLine->substr(nParamStart + 1, nParamEnd - nParamStart - 1);

		int nParamCount = 0;
		if (strParams.length() > 0)
			nParamCount = 1;

		int nCurPos = 0;
		bool bInBrackets = false;
		do {
			char cChar = strParams.at(nCurPos);

			if (cChar == '\"') bInBrackets ? bInBrackets = false : bInBrackets = true;
			if (cChar == ',' && !bInBrackets) nParamCount++;

		} while (++nCurPos < strParams.length());

		void* pFunction = m_Functions.GetFunction(strCommand, nParamCount);

		vector<string> vParams = CreateParamList(&strParams);

		bool bSuccess;
		switch (nParamCount)
		{
		case 0:
			bSuccess = ((sfunc_0*) pFunction)();
			break;
		case 1:
			bSuccess = ((sfunc_1*) pFunction)(&vParams[0]);
			break;
		case 2:
			bSuccess = ((sfunc_2*) pFunction)(&vParams[0], &vParams[1]);
		}
	}
}

void CParser::SetError(char* pcError, char* pcLine, int nLine)
{
	strclr(m_lastError.pcError, 250);
	strclr(m_lastError.pcLine, 250);
	
	strcpy(m_lastError.pcError, pcError);
	strcpy(m_lastError.pcLine, pcLine);
	m_lastError.nLine = nLine;

	m_bError = true;
}

bool CParser::PopParam(string* pstrParams, string* pstrParam)
{
	if (!pstrParam) pstrParam = new string;

	if (pstrParams)
	{
		int nPos = pstrParams->find(",");
		if (nPos >= 0)
		{
			*pstrParam = pstrParams->substr(0, nPos);
			*pstrParams = pstrParams->substr(nPos + 1, (pstrParams->length() - nPos));
			return true;
		}
		else if (pstrParams->length() > 0)
		{
			*pstrParam = pstrParams->substr(0, pstrParams->length());
			pstrParams->clear();
			return true;
		}
	}
	return false;
}

vector<string> CParser::CreateParamList(string* pstrParams)
{
	vector<string> vParams;
	
	string strParam;
	while (PopParam(pstrParams, &strParam))
		vParams.push_back(strParam);
	
	return vParams;
}