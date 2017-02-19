#include "StdAfx.h"
#include "Exports.h"

using namespace std;

char* stringEcho(char* inputString) 
{
	return inputString;
}

Int64 echoInt(Int64 intToEcho)
{
	return intToEcho;
}

void getLibVersion(Int32 *major, Int32 *minor, Int32 *build)
{
	*major = Int32(MY_VER_MAJOR);
	*minor = Int32(MY_VER_MINOR);
	*build = Int32(MY_VER_BUILD);
}

Int32 getRegisteredArcCount()
{
	return Int32(g_NumArcs);
}

CArcInfo getArcInfo(Int32 arcIndex)
{
	auto arch = *g_Arcs[arcIndex];
	/*if (arch.IsArc != NULL) 
	{
		byte testArr[200];
		auto test = arch.IsArc(&(testArr[0]), 200);
	}*/
	return arch;
}

CArcInfo* getArcInfoFromId(Byte arcId)
{
	CArcInfo* f = NULL;
	for (unsigned i = 0; i < g_NumArcs; i++)
	{
		if (g_Arcs[i]->Id == arcId)
		{
			auto arch = (*g_Arcs[i]);
			f = &arch;
			break;
		}
	}
	
	return f;
}