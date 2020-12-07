// IniFile.cpp: implementation of the CIniFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lasersystem.h"
#include "IniFile.h"
#include <io.h>
#include <iostream>
#include <windows.h>
#include <shellapi.h>
#include <fstream>
#pragma comment(lib, "SHELL32.LIB")

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//default constructor
CIniFile::CIniFile()
{
}

//default destructor
CIniFile::~CIniFile()
{

}

/////////////////////////////////////////////////////////////////////
// Public Functions
/////////////////////////////////////////////////////////////////////

//sets path of ini file to read and write from
void CIniFile::SetPath(CString Path)
{
	FilePath = Path;
}

bool CIniFile::VerifyPathExist(CString dir)
{
	if (_access(dir,0)==-1 || _access(dir,4)==-1)
	{
		return false;
	}
	fstream file;
	file.open(dir,ios::in);
	if (file.is_open())
	{
		file.seekg(0,ios::end);
		streampos fp = file.tellg();
		file.close();
		if (int(fp) == 0 )
		{
			return false;
		}
	}
	return true;
}


int CIniFile::CopyFileOfDirtoPath(std::string srcDir, std::string desDir)
{
	srcDir += '\0';
	desDir += '\0';
	SHFILEOPSTRUCT fop;
	ZeroMemory(&fop, sizeof fop);
	fop.wFunc = FO_COPY;
	fop.pFrom = srcDir.c_str();
	fop.pTo = desDir.c_str();
	fop.fFlags = FOF_SILENT | FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_NOCONFIRMMKDIR;
	
	return SHFileOperation(&fop);
}

//open ini file for read
BOOL CIniFile::OpenIniFileForRead()
{
	BOOL bExist=IniFile.Open(FilePath+FileName,CFile::modeRead ); 
	return bExist;
}

//open ini file for write
BOOL CIniFile::OpenIniFileForWrite()
{
	BOOL bExist=IniFile.Open(FilePath+FileName,CFile::modeCreate | CFile::modeWrite);
	return bExist;
}

void CIniFile::CloseIniFile()
{
	IniFile.Close();
}

//find Section in ini file
BOOL CIniFile::FindSection(CString Section)
{
	IniFile.SeekToBegin();
	CString str;
	BOOL bFind=FALSE;
	BOOL bEnd=IniFile.ReadString(str);
	while(!bFind && bEnd)
	{
		if(str.Find(Section)>=0)
		{
			bFind=TRUE;
			break;
		}
		bEnd=IniFile.ReadString(str);
	}
	return bFind;
}

//write Section to ini file
BOOL CIniFile::WriteSection(CString Section)
{
	CFileStatus status;
	if(IniFile.GetStatus(status))
	{
		IniFile.WriteString("["+Section+"]\n");
		return TRUE;
	}
	else
		return FALSE;
}

//write Item and value of int to ini file
BOOL CIniFile::WriteItemInt(CString Item, long Value)
{
	CFileStatus status;
	if(IniFile.GetStatus(status))
	{
		CString str;
		str.Format("%d",Value);
		str=Item+"="+str+"\n";
		IniFile.WriteString(str);
		return TRUE;
	}
	else
		return FALSE;
}

//write Item and value of CString to ini file
BOOL CIniFile::WriteItemString(CString Item, CString Value)
{
	CFileStatus status;
	if(IniFile.GetStatus(status))
	{
		IniFile.WriteString(Item+"="+Value+"\n");
		return TRUE;
	}
	else
		return FALSE;
}

//read value of int from ini file
BOOL CIniFile::GetItemInt(CString Section, CString Item, long &Value)
{
	CFileStatus status;
	if(IniFile.GetStatus(status))
	{
		if(FindSection(Section))
		{
			CString buf,sub;
			BOOL bFind=FALSE;
			BOOL bEnd=IniFile.ReadString(buf);
			while(!bFind && bEnd)
			{
				sub=buf.Left(buf.Find("="));
				if(buf.Find("[")<0 && !sub.IsEmpty() && sub.Find(Item)>=0)
				{
					sub=buf.Right(buf.GetLength()-buf.Find("=")-1);
					sub=GetValueString(sub);
					Value=atoi(sub);
					bFind=TRUE;
					break;
				}
				bEnd=IniFile.ReadString(buf);
			}
			return bFind;
		}
		else
			return FALSE;
	}
	else
		return FALSE;
}

BOOL CIniFile::GetItemInt(CString Section, CString Item, DWORD &Value)
{
	CFileStatus status;
	if(IniFile.GetStatus(status))
	{
		if(FindSection(Section))
		{
			CString buf,sub;
			BOOL bFind=FALSE;
			BOOL bEnd=IniFile.ReadString(buf);
			while(!bFind && bEnd)
			{
				sub=buf.Left(buf.Find("="));
				if(buf.Find("[")<0 && !sub.IsEmpty() && sub.Find(Item)>=0)
				{
					sub=buf.Right(buf.GetLength()-buf.Find("=")-1);
					sub=GetValueString(sub);
					Value=atoi(sub);
					bFind=TRUE;
					break;
				}
				bEnd=IniFile.ReadString(buf);
			}
			return bFind;
		}
		else
			return FALSE;
	}
	else
		return FALSE;
}

//read value of CString from ini file
BOOL CIniFile::GetItemString(CString Section, CString Item, CString &Value)
{
	CFileStatus status;
	if(IniFile.GetStatus(status))
	{
		if(FindSection(Section))
		{
			CString buf,sub;
			BOOL bFind=FALSE;
			BOOL bEnd=IniFile.ReadString(buf);
			while(!bFind && bEnd)
			{
				sub=buf.Left(buf.Find("="));
				if(buf.Find("[")<0 && !sub.IsEmpty() && sub.Find(Item)>=0)
				{
					sub=buf.Right(buf.GetLength()-buf.Find("=")-1);
					Value=GetValueString(sub);
					bFind=TRUE;
					break;
				}
				bEnd=IniFile.ReadString(buf);
			}
			return bFind;
		}
		else
			return FALSE;
	}
	else
		return FALSE;
}

//get value(CString) from str
CString CIniFile::GetValueString(CString str)
{
	int length=str.GetLength();
	BOOL bSpace=TRUE;
	while(length && bSpace)
	{
		if(str[0]==' ')
			str=str.Right(--length);
		else
			bSpace=FALSE;
	}
	bSpace=TRUE;
	while(length && bSpace)
	{
		if(str[length-1]==' ')
			str=str.Left(--length);
		else
			bSpace=FALSE;
	}
	return str;
}

//write any string to ini file,"\n"
BOOL CIniFile::WriteString(CString str)
{
	CFileStatus status;
	if(IniFile.GetStatus(status))
	{
		IniFile.WriteString(str);
		return TRUE;
	}
	else
		return FALSE;
}

//sets name of ini file to read and write from
void CIniFile::SetName(CString Name)
{
	FileName=Name+".ini";
}

BOOL CIniFile::GetItemF64(CString Section, CString Item, double &Value)
{
	CFileStatus status;
	if(IniFile.GetStatus(status))
	{
		if(FindSection(Section))
		{
			CString buf,sub;
			BOOL bFind=FALSE;
			BOOL bEnd=IniFile.ReadString(buf);
			while(!bFind && bEnd)
			{
				sub=buf.Left(buf.Find("="));
				if(buf.Find("[")<0 && !sub.IsEmpty() && sub.Find(Item)>=0)
				{
					sub=buf.Right(buf.GetLength()-buf.Find("=")-1);
					sub=GetValueString(sub);
					Value=atof(sub);
					bFind=TRUE;
					break;
				}
				bEnd=IniFile.ReadString(buf);
			}
			return bFind;
		}
		else
			return FALSE;
	}
	else
		return FALSE;
}

BOOL CIniFile::WriteItemF64(CString Item, double Value)
{
	CFileStatus status;
	if(IniFile.GetStatus(status))
	{
		CString str;
		str.Format("%f",Value);
		str=Item+"="+str+"\n";
		IniFile.WriteString(str);
		return TRUE;
	}
	else
		return FALSE;
}
