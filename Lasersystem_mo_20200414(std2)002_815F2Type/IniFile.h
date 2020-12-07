// IniFile.h: interface for the CIniFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_INIFILE_H__C363CC34_88F5_4277_B3C3_D78E98163899__INCLUDED_)
#define AFX_INIFILE_H__C363CC34_88F5_4277_B3C3_D78E98163899__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CIniFile  
{
	//all private variables
private:

private:

	//stores path of ini file to read/write
	CString FilePath;

	//stores name of ini file to read/write
	CString FileName;

	//get value(CString) from str
	CString GetValueString(CString str);

	//find Section in ini file
	BOOL FindSection(CString Section);

	//ini file
	CStdioFile IniFile;

	//public variables
public:

	//public functions
public:
	BOOL WriteItemF64(CString Item, double Value);
	BOOL GetItemF64(CString Section, CString Item, double &Value);
	
	//read value of int from ini file
	BOOL GetItemInt(CString Section,CString Item,long & Value);
	BOOL GetItemInt(CString Section, CString Item, DWORD &Value);
	//read value of CString from ini file
	BOOL GetItemString(CString Section,CString Item,CString & Value);
	
	//write any string to ini file,"\n"
	BOOL WriteString(CString str);
	
	//write Section to ini file
	BOOL WriteSection(CString Section);
	
	//write Item and value of int to ini file
	BOOL WriteItemInt(CString Item,long Value);
	
	//write Item and value of CString to ini file
	BOOL WriteItemString(CString Item,CString Value);
	
	//open ini file for read
	BOOL OpenIniFileForRead(void);
	
	//open ini file for write
	BOOL OpenIniFileForWrite(void);
	
	//default constructor
	CIniFile();
	
	//sets name of ini file to read and write from
	void SetName(CString Name);
	
	//sets path of ini file to read and write from
	void SetPath(CString Path);

	//verify dir is exist
	bool VerifyPathExist(CString dir);
	
	//copy the file of srcDir to desDir
	int CopyFileOfDirtoPath(std::string srcDir, std::string desDir);
	
	//close ini file
	virtual void CloseIniFile(void);
	
	//default destructor
	virtual ~CIniFile();
};

#endif // !defined(AFX_INIFILE_H__C363CC34_88F5_4277_B3C3_D78E98163899__INCLUDED_)
