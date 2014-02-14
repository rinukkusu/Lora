#include <map>

typedef bool sfunc_0();
typedef bool sfunc_1(void*);
typedef bool sfunc_2(void*, void*);

struct funcmap
{
	std::string strFunctionName;
	void* pFunction;
};

struct funcmap_0
{
	std::string strFunctionName;
	sfunc_0* pFunction;
};

struct funcmap_1
{
	std::string strFunctionName;
	sfunc_1* pFunction;
};

struct funcmap_2
{
	std::string strFunctionName;
	sfunc_2* pFunction;
};


class functions
{
private:
	static bool PrintText(void*);
	static bool Random(void*, void*);

public:
	functions();
	void* GetFunction(std::string strFunctionName, int nParams = 0);
	bool AddFunction_0(std::string strFunctionName, sfunc_0* pFunction);
	bool AddFunction_1(std::string strFunctionName, sfunc_1* pFunction);
	bool AddFunction_2(std::string strFunctionName, sfunc_2* pFunction);

private:
#define	FUNCTION_MAP_SIZE	100
	int nFuncCount[3];

public:
	funcmap_0 m_Func0[FUNCTION_MAP_SIZE];
	funcmap_1 m_Func1[FUNCTION_MAP_SIZE];
	funcmap_2 m_Func2[FUNCTION_MAP_SIZE];
};