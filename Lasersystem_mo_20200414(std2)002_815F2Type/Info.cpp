
#include "stdafx.h"
#include "Info.h"
#include <stdarg.h>
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

Information& GetInfo()
{
   static Information info;
   return info;
}

bool Information::SaveInfoToFile(const char* FileName, const char* Info) const
{
    FILE* fp;
    if(!(fp= fopen(FileName,"a+")))
        return false;
    fprintf(fp,"%s\n", Info);
    fclose(fp);
    return true;
}

bool Information::ClearFileData(const char* FileName, const char* Info)const
{
	FILE* fp;
    if(!(fp= fopen(FileName,"w+")))
        return false;
    fprintf(fp,"%s", Info);
    fclose(fp);
    return true;
}

bool Information::SaveToFile(const char *FileName, const char *fmt, ...) const
{
	FILE* fp;
	char buf[1024];
	va_list args;
	int n = strlen(fmt);
	if( strlen(fmt)<=0 || (!(fp= fopen(FileName,"a+"))))
        return false;
	va_start(args,fmt);
	vsprintf(buf,fmt,args);
	va_end(args);
	fputs(buf,fp);
    fclose(fp);

    return true;
}


bool Information::SaveToFileW(const char *FileName, const char *fmt, ...) const
{
	FILE* fp;
	char buf[1024];
	va_list args;
	int n = strlen(fmt);
	if( strlen(fmt)<=0 || (!(fp= fopen(FileName,"w+"))))
        return false;
	va_start(args,fmt);
	vsprintf(buf,fmt,args);
	va_end(args);
	fputs(buf,fp);
    fclose(fp);

    return true;
}

bool Information::SaveDataToFile(FILE* fp, const char *fmt, ...) const
{
//	FILE* fp;
	char buf[512];
	va_list args;
//	int n = strlen(fmt);
//	if( strlen(fmt)<=0 || (!(fp= fopen(FileName,"a+"))))
//      return false;
	if( strlen(fmt)<=0 )
        return false;
	va_start(args,fmt);
	vsprintf(buf,fmt,args);
	va_end(args);
	fputs(buf,fp);
//    fclose(fp);
    return true;
}





