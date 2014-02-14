#include "stack.h"


CStack::CStack(void)
{
	m_pStackHead = new StackVar;
	m_pStackHead->pVariable = NULL;
	m_pStackHead->pNext = NULL;
	m_pStackHead->pPrev = NULL;
	m_pStackHead->nLevel = -1;

	m_pStackBottom = m_pStackHead;
}

CStack::~CStack(void)
{
	DeleteAll();
}

void CStack::DeleteAll()
{
	StackVar* pLocVar = GetLast();

	while (pLocVar)
	{
		StackVar* pTemp = pLocVar;
		pLocVar = pLocVar->pPrev;

		try 
		{
			if (pTemp->pVariable) {
				if (pTemp->pVariable->pData) {
					delete pTemp->pVariable->pData;
				}
				delete pTemp->pVariable;
			}

			delete pTemp;
		}
		catch (...)
		{

		}
	}

}

CStack::StackVar* CStack::Add(CVariable *pVariable, int nLevel)
{
	// copy variable into local address space
	CVariable *pLocVar = new CVariable(pVariable->cName);
	*pLocVar = *pVariable;

	// get last element on the stack
	StackVar *pLastElement = m_pStackBottom; //GetLast();

	// initialize new element
	StackVar *pNewElement = new StackVar;
	pNewElement->nLevel = nLevel;
	pNewElement->pVariable = pLocVar;
	pNewElement->pPrev = pLastElement;
	pNewElement->pNext = NULL;

	// set next element on last element
	pLastElement->pNext = pNewElement;

	m_pStackBottom = pNewElement;

	// return new element
	return pNewElement;
}

bool CStack::Delete(char *cName, int nLevel)
{
	StackVar *pSearchElement = Search(cName, nLevel);
	if (!pSearchElement) return false;

	StackVar *pPrev = pSearchElement->pPrev;
	StackVar *pNext = pSearchElement->pNext;

	if (pSearchElement == m_pStackBottom)
		m_pStackBottom = pSearchElement->pPrev;

	if (pPrev != m_pStackHead)
		pPrev->pNext = pNext;
	else
		pPrev->pNext = NULL;

	if (pNext)
		pNext->pPrev = pPrev;


	try 
	{
		if (pSearchElement->pVariable) {
			if (pSearchElement->pVariable->pData) {
				delete pSearchElement->pVariable->pData;
			}
			delete pSearchElement->pVariable;
		}
		delete pSearchElement;
	}
	catch (...)
	{

	}

	return true;
}

CStack::StackVar* CStack::Search(char *cName, int nLevel)
{
	StackVar *pElement = m_pStackBottom;
	// go through stack until matching variable found
	while (pElement != m_pStackHead) {
		// compare the variable names
		if (strcmp(pElement->pVariable->cName, cName) == 0) {
			if (nLevel < 0 || nLevel == pElement->nLevel)
				return pElement;
		}
		pElement = pElement->pPrev;
	}

	return NULL;
}

CStack::StackVar* CStack::GetLast()
{
	StackVar *pLastElement = m_pStackHead;
	// go through stack until last element found
	while (pLastElement->pNext)
		pLastElement = pLastElement->pNext;

	return pLastElement;
}