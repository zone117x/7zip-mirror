#pragma once

#include "../../../../C/7zTypes.h"
#include "../../../../C/7zVersion.h"
#include "../../Archive/ArchiveExports.h"

using namespace std;


extern "C" {

	__declspec(dllexport) char* stringEcho(char* inputString);

	__declspec(dllexport) Int64 echoInt(Int64 intToEcho);

	__declspec(dllexport) void getLibVersion(Int32 *major, Int32 *minor, Int32 *build);

	__declspec(dllexport) Int32 getRegisteredArcCount();

	__declspec(dllexport) CArcInfo getArcInfo(Int32 arcIndex);

	__declspec(dllexport) CArcInfo* getArcInfoFromId(Byte arcId);
}