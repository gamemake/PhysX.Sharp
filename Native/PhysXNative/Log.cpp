#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdarg.h>

#include "Log.h"

void LogWrite(const char* format, ...)
{
	char buffer[1024];
	va_list arglist;
	va_start(arglist, format);
	vsprintf(buffer, format, arglist);
	va_end(arglist);

	FILE* fp = fopen("D:\\PhysX.Native.log", "at");
	if (fp != nullptr)
	{
		fputs(buffer, fp);
		fputs("\n", fp);
		fclose(fp);
	}
}
