
#if !defined(AFX_INFO_H__B318F974_D597_447D_AD98_32D14749E035__INCLUDED_)
#define AFX_INFO_H__B318F974_D597_447D_AD98_32D14749E035__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class Information
{
  public:
	  bool ClearFileData(const char* FileName, const char* Info = "")const;
	  bool SaveToFile(const char* FileName, const char* fmt,...)const;
	  bool SaveToFileW(const char *FileName, const char *fmt, ...)const;
      bool SaveInfoToFile(const char* FileName, const char* Info) const;
	  bool SaveDataToFile(FILE* fp, const char *fmt, ...) const;

  private:
	 Information(){}
     friend Information& GetInfo();
};

#endif // !defined(AFX_INFO_H__B318F974_D597_447D_AD98_32D14749E035__INCLUDED_)
