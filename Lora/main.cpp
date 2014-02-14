#include "main.h"

CParser *m_pParser;

int main()
{
	m_pParser = new CParser;

	m_pParser->ReadFile("C:\\Scripts\\Script.lr");
	m_pParser->ParseScript();

	delete m_pParser;

	printf ("\r\n\r\nDruecken Sie eine Taste, um das Programm zu beenden...");

	_getch();
	return 0;
}