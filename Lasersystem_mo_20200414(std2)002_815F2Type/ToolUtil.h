#pragma once
#ifndef STRUTIL_H
#define STRUTIL_H
#include <fstream>
#include <sstream>
#include <iostream>
#include <strstream>
#include <string>
#include <vector>
#include <Windows.h>
#include <set>
#include <iomanip>
#include "deelx.h"
#include <algorithm>
using namespace std;
#define	PerBatchMaximum 150
#define	Percision 6
#define bzero(a, b)             memset(a, 0, b)

//Declaration
namespace ToolUtil
{
	inline std::wstring AnsiToUnicode(const char* buf);
	inline std::string AnsiToUtf8(const char* buf);
	inline std::string UnicodeToAnsi(const wchar_t* buf);
	inline std::wstring Utf8ToUnicode(const char* buf);
	inline std::string UnicodeToUtf8(const wchar_t* buf);
	inline std::string TrimLeft(const std::string& str);
	inline std::string TrimRight(const std::string& str);
	inline std::string Trim(const std::string& str);
	inline std::vector<int> split(char * str, char del);
	inline std::vector<std::string> Split(std::string& str, const char* c);
	inline void SplitStringToVector(const string src,const string separator,vector<string> &dest); 
	inline void Replace(std::string&srcstr,const std::string&oldstr,const std::string&newstr);
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	inline double StringToDouble(const std::string &str);
	inline std::string DoubleToString(double Num);
	inline void string_replace(std::string &strBig, const std::string &strsrc, const std::string &strdst);
	
	inline double CountVectorAve(vector<std::string> vet);
	inline double CountVectorMedian(vector<std::string> vet);
	
	inline int CheckFIleDataFormat(const char * lineStr);
	inline int CountSubString(std::string const& str, std::string const& substr);
	
	inline std::string SplitFileName(std::string& str);
	inline vector<std::string> splitString(std::string str, std::string pattern);
	inline void SplitStringGenerateFixAndInc(CString &srcStr, CString &fix, CString &inc);
	inline int CountStrInFile(std::string const& filename,  std::string const& str);
	
	inline bool IsUTF8(const void* pBuffer, long size);
	inline bool IsUTF8File(const char* pFileName);
	inline const char* UTF8ToGB(const char* lineStr);
	inline CString GbkToUtf8(const char *src_str);
	inline int API_StringToTimeEX(char* strDateStr, time_t &timeData);
	inline string time_t2string(const time_t time_t_time);
	inline time_t stringtotime_t(const string string_time);
	inline bool ParseJsonFromFile(const char* filename, vector<string> &reqsVet);
	inline BOOL DelDirFiles(CString strPath);
};


//Definition
namespace ToolUtil 
{
	void Replace(std::string&srcstr,const std::string&oldstr,const std::string&newstr)  
	{  
		string::size_type pos=0;  
		string::size_type a=oldstr.size();  
		string::size_type b=newstr.size();  
		while((pos=srcstr.find(oldstr,pos))!=string::npos)  
		{  
			srcstr.replace(pos,a,newstr);  
			pos+=b;  
		}  
	} 
	
	vector<int> split(char * str, char del) //忽略“空位”（::192:168:ABC::416）->（192 168 ABC 416）
	{
		stringstream ss(str);
		string tok;
		vector<int> ret;
		while (getline(ss, tok, del))
		{
			if (tok > "")
				ret.push_back(atoi(tok.c_str()));
		}
		return ret;
	}
	
	void SplitStringToVector(const string src,const string separator,vector<string> &dest)
	{
		string str = src;
		string substring;
		string::size_type start = 0,index;
		dest.clear();
		index = str.find_first_of(separator,start);
		do
		{
			if (index != string::npos)
			{
				substring  =  str.substr(start,index-start);
				dest.push_back(substring);
				start = index+separator.size();
				index = str.find(separator,start);
				if (start == string::npos)
				{
					break;
				}
			}
		}while (index!=string::npos);
	}

	
	std::wstring AnsiToUnicode(const char* buf)
	{
		int len = ::MultiByteToWideChar(CP_ACP, 0, buf, -1, NULL, 0);
		if (len == 0) return L"";
		std::vector<wchar_t> unicode(len);
		::MultiByteToWideChar(CP_ACP, 0, buf, -1, &unicode[0], len);
		return &unicode[0];
	}
	
	std::string AnsiToUtf8( const char* buf )
	{
		return UnicodeToUtf8(AnsiToUnicode(buf).c_str());
	}
	
	std::string UnicodeToAnsi(const wchar_t* buf)
	{
		int len = ::WideCharToMultiByte(CP_ACP, 0, buf, -1, NULL, 0, NULL, NULL);
		if (len == 0) return "";
		std::vector<char> utf8(len);
		::WideCharToMultiByte(CP_ACP, 0, buf, -1, &utf8[0], len, NULL, NULL);
		return &utf8[0];
	}
	
	std::wstring Utf8ToUnicode(const char* buf)
	{
		int len = ::MultiByteToWideChar(CP_UTF8, 0, buf, -1, NULL, 0);
		if (len == 0) return L"";
		std::vector<wchar_t> unicode(len);
		::MultiByteToWideChar(CP_UTF8, 0, buf, -1, &unicode[0], len);
		return &unicode[0];
	}
	
	std::string UnicodeToUtf8(const wchar_t* buf)
	{
		int len = ::WideCharToMultiByte(CP_UTF8, 0, buf, -1, NULL, 0, NULL, NULL);
		if (len == 0) return "";
		std::vector<char> utf8(len);
		::WideCharToMultiByte(CP_UTF8, 0, buf, -1, &utf8[0], len, NULL, NULL);
		return &utf8[0];
	}
	
	std::string TrimLeft(const std::string& str) {
		std::string t = str;
		for (std::string::iterator i = t.begin(); i != t.end(); i++) {
			if (!isspace(*i)) {
				t.erase(t.begin(), i);
				break;
			}
		}
		return t;
	}
	
	std::string TrimRight(const std::string& str) {
		if (str.begin() == str.end()) {
			return str;
		}
		std::string t = str;
		for (std::string::iterator i = t.end() - 1; i != t.begin(); i--) {
			if (!isspace(*i)) {
				t.erase(i + 1, t.end());
				break;
			}
		}
		return t;
	}
	
	std::string Trim(const std::string& str) {
		std::string t = str;
		
		std::string::iterator i;
		for (i = t.begin(); i != t.end(); i++) {
			if (!isspace(*i)) {
				t.erase(t.begin(), i);
				break;
			}
		}
		if (i == t.end()) {
			return t;
		}
		
		for (i = t.end() - 1; i != t.begin(); i--) {
			if (!isspace(*i)) {
				t.erase(i + 1, t.end());
				break;
			}
		}
		return t;
	}
	
	
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//类型转换 String转Double
	double StringToDouble(const std::string &str)
	{
		double val;
		strstream ss;
		ss << str;
		ss >> val;
		return val;
	}
	
	//time_t转换为string  时间格式为2014/03/28 18:25:26
	string time_t2string(const time_t time_t_time)
	{
		char szTime[100] = {'\0'};
		
		tm pTm;
		pTm = *localtime(&time_t_time);
		//pTm = localtime(&time_t_time);
		pTm.tm_year += 1900;
		pTm.tm_mon +=1;
		
		sprintf(szTime, "%04d/%02d/%02d %02d:%02d:%02d",
			pTm.tm_year,
			pTm.tm_mon,
			pTm.tm_mday,
			pTm.tm_hour,
			pTm.tm_min,
			pTm.tm_sec);
		
		string strTime = szTime;
		return strTime;
	}
	
	time_t stringtotime_t(const string string_time)
	{
		tm tm1;
		memset(&tm1, 0, sizeof(tm1));
		time_t time1;
		
		sscanf(string_time.c_str(), "%d-%d-%d %d:%d:%d",
			&(tm1.tm_year),
			&(tm1.tm_mon),
			&(tm1.tm_mday),
			&(tm1.tm_hour),
			&(tm1.tm_min),
			&(tm1.tm_sec));
		
		tm1.tm_year -= 1900;
		tm1.tm_mon -= 1;
		time1 = mktime(&tm1);
		return time1;
	}
	
	//string to time_t 时间格式 2009-3-24 0:00:08 或 2009-3-24
	int API_StringToTimeEX(char* strDateStr, time_t &timeData)
	{
		char *pBeginPos = strDateStr;
		char *pPos = strstr(pBeginPos, "-");
		if (pPos == NULL)
		{
			printf("strDateStr[%s] err \n", strDateStr);
			return -1;
		}
		int iYear = atoi(pBeginPos);
		int iMonth = atoi(pPos + 1);
		pPos = strstr(pPos + 1, "-");
		if (pPos == NULL)
		{
			printf("strDateStr[%s] err \n", strDateStr);
			return -1;
		}
		int iDay = atoi(pPos + 1);
		int iHour = 0;
		int iMin = 0;
		int iSec = 0;
		pPos = strstr(pPos + 1, "T");
		//为了兼容有些没精确到时分秒的
		if (pPos != NULL)
		{
			iHour = atoi(pPos + 1);
			pPos = strstr(pPos + 1, ":");
			if (pPos != NULL)
			{
				iMin = atoi(pPos + 1);
				pPos = strstr(pPos + 1, ":");
				if (pPos != NULL)
				{
					iSec = atoi(pPos + 1);
				}
			}
		}

		tm sourcedate;
		bzero((void*)&sourcedate, sizeof(sourcedate));
		sourcedate.tm_sec = iSec;
		sourcedate.tm_min = iMin;
		sourcedate.tm_hour = iHour+8;
		sourcedate.tm_mday = iDay;
		sourcedate.tm_mon = iMonth-1;
		sourcedate.tm_year = iYear-1900;
		timeData = mktime(&sourcedate);
		return 0;
	}
	
	
	//类型转换 Double转String
	std::string DoubleToString(double Num)
	{
		ostringstream oss;
		oss << fixed << setprecision(Percision) << Num;
		std::string str(oss.str());
		return str;
	}
	
	//计算Vector的平均值
	double CountVectorAve(vector<std::string> vet)
	{
		if (vet.size() == 0)
		{
			return 0;
		}
		vector<std::string>::iterator it;
		double d = 0;
		for (it = vet.begin(); it != vet.end(); it++)
		{
			d += StringToDouble((*it));
		}
		return d / vet.size();
	}
	
	//计算Vector的中间值
	double CountVectorMedian(vector<std::string> vet)
	{
		double median = 0;
		sort(vet.begin(),vet.end());
		if (vet.size() == 0)
		{
			return median;
		}
		if (vet.size() == 1)
		{
			median = StringToDouble(*vet.begin());
		}
		if (vet.size() >= 2)
		{
			if (vet.size()%2 == 0)//双数取中间两个值的平均值
			{
				double left = StringToDouble(vet[vet.size()/2-1]);
				double right = StringToDouble(vet[vet.size()/2]);
				median =  (left + right)/2;
			}
			else
			{
				median = StringToDouble(vet[vet.size()/2]);
			}
		}
		return median;
	}
	
	//正则表达式校验文本行内容格式
	int CheckFIleDataFormat(const char * lineStr)
	{
		static CRegexpT <char> regexp("^(([\\?0-9a-zA-Z\\w]+)=([^\\x00–\\x1F\\x7F]*)+[;,\\s]{0,1})*$");
		MatchResult result = regexp.MatchExact(lineStr);
		return result.IsMatched();
	}
	
	//获取路径的最后一个文件名
	std::string SplitFileName(std::string& str)
	{
		unsigned int found = str.find_last_of("/\\");
		return str.substr(found + 1);
	}
	
	//按特定字符分割字符串写入到vector //（AAA:BBB）->（AAA BBB）
	vector<std::string> splitString(std::string str, std::string pattern)
	{
		std::string::size_type pos;
		std::vector<std::string> result;
		
		str += pattern;//扩展字符串以方便操作
		int size = str.size();
		
		for (int i = 0; i < size; i++)
		{
			pos = str.find(pattern, i);
			if (pos < size)
			{
				std::string s = str.substr(i, pos - i);
				result.push_back(s);
				i = pos + pattern.size() - 1;
			}
		}
		return result;
	}

	void SplitStringGenerateFixAndInc(CString &srcStr, CString &fix, CString &inc)
	{
		string str = srcStr;
		string separator="-";
		string::size_type start = 0,index;
		
		index = str.find_last_of(separator);
		if (index != string::npos)
		{
			fix.Format("%s",str.substr(start,index-start).c_str());
			start = index+separator.size();
			if (start != string::npos)
			{
				inc.Format("%s",str.substr(start).c_str());
			}
		}
	}
	
	//文本行匹配字符串个数
	int CountSubString(std::string const& str, std::string const& substr)
	{
		int nCount = 0;
		
		std::string::size_type substrSize = substr.size();
		std::string::size_type idxSub = str.find(substr, 0);
		while (idxSub!=string::npos) {
			++nCount;
			++idxSub;
			idxSub = str.find(substr, idxSub);      
		}
		
		return nCount;
	}
	
	
	//把字符串strBig的strsrc替换成strdst
	void string_replace(std::string &strBig, const std::string &strsrc, const std::string &strdst)
	{
		std::string::size_type pos = 0;
		std::string::size_type srclen = strsrc.size();
		std::string::size_type dstlen = strdst.size();
		
		while ((pos = strBig.find(strsrc, pos)) != std::string::npos)
		{
			strBig.replace(pos, srclen, strdst);
			pos += dstlen;
		}
	}
	
	//判断字符串的每个字符是否为UTF8
	bool IsUTF8(const void* pBuffer, long size)
	{
		bool IsUTF8 = true;
		unsigned char* start = (unsigned char*)pBuffer;
		unsigned char* end = (unsigned char*)pBuffer + size;
		while (start < end)
		{
			if (*start < 0x80) // (10000000): 值小于0x80的为ASCII字符  
			{
				start++;
			}
			else if (*start < (0xC0)) // (11000000): 值介于0x80与0xC0之间的为无效UTF-8字符  
			{
				IsUTF8 = false;
				break;
			}
			else if (*start < (0xE0)) // (11100000): 此范围内为2字节UTF-8字符  
			{
				if (start >= end - 1)
				{
					break;
				}
				
				if ((start[1] & (0xC0)) != 0x80)
				{
					IsUTF8 = false;
					break;
				}
				start += 2;
			}
			else if (*start < (0xF0)) // (11110000): 此范围内为3字节UTF-8字符  
			{
				if (start >= end - 2)
				{
					break;
				}
				
				if ((start[1] & (0xC0)) != 0x80 || (start[2] & (0xC0)) != 0x80)
				{
					IsUTF8 = false;
					break;
				}
				start += 3;
			}
			else
			{
				IsUTF8 = false;
				break;
			}
		}
		return IsUTF8;
	}
	
	CString GbkToUtf8(const char *src_str)
	{
		int len = MultiByteToWideChar(CP_ACP, 0, src_str, -1, NULL, 0);
		wchar_t* wstr = new wchar_t[len + 1];
		memset(wstr, 0, len + 1);
		MultiByteToWideChar(CP_ACP, 0, src_str, -1, wstr, len);
		len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
		char* str = new char[len + 1];
		memset(str, 0, len + 1);
		WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
		CString strTemp = str;
		if (wstr) delete[] wstr;
		if (str) delete[] str;
		return strTemp;
	}
	
	//解决读取文本行内容乱码问题
	const char* UTF8ToGB(const char* lineStr)
	{
		std::string result;
		WCHAR *strSrc;
		LPSTR szRes;
		
		int i = MultiByteToWideChar(CP_UTF8, 0, lineStr, -1, NULL, 0);
		strSrc = new WCHAR[i + 1];
		MultiByteToWideChar(CP_UTF8, 0, lineStr, -1, strSrc, i);
		
		i = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, NULL, 0, NULL, NULL);
		szRes = new CHAR[i + 1];
		WideCharToMultiByte(CP_ACP, 0, strSrc, -1, szRes, i, NULL, NULL);
		
		result = szRes;
		delete[]strSrc;
		delete[]szRes;
		return result.c_str();
	}
	
	bool ParseJsonFromFile(const char* filename,vector<string> &reqsVet)  
	{  
		// 解析json用Json::Reader   
		Json::Reader reader;  
		// Json::Value是一种很重要的类型，可以代表任意类型。如int, string, object, array...   
		Json::Value root;
		vector<string> vet;
		std::ifstream is,file;  
		file.open(filename,ios::in);
		if (!file.is_open())
		{
			return false;
		}
		string mystr,textStr;
		
		is.open (filename, std::ios::binary ); 
		while (getline(file,mystr))
		{
			textStr+=mystr;
		}
		
		SplitStringToVector(textStr,";",vet);
		reqsVet = vet;
		TRACE("reqsVet size is%d\n",reqsVet.size());
		if (reqsVet.size() == 0)
		{
			return false;
		}
		if (!reader.parse(is, root))  
		{  
			return false;
		}  
		is.close();  
		file.close();
		return true;  
	} 


	BOOL DelDirFiles(CString strPath)
	{
		WIN32_FIND_DATA wfd;
		HANDLE hFind;
		CString strFullPath;
		CString strFindFilter;
		DWORD dwAttributes = 0;
		
		strFindFilter = strPath + _T("\\*.*");
		hFind = FindFirstFile(strFindFilter, &wfd);
		if (INVALID_HANDLE_VALUE == hFind)
		{
			return FALSE;
		}
		
		do
		{
			if (_tcscmp(wfd.cFileName, _T(".")) == 0 ||
				_tcscmp(wfd.cFileName, _T("..")) == 0 )
			{
				continue;
			}
			
			strFullPath = strPath + _T("\\") + wfd.cFileName;
			//去掉文件的只读属性
			dwAttributes = GetFileAttributes(strFullPath);
			if (dwAttributes & FILE_ATTRIBUTE_READONLY)
			{
				dwAttributes &= ~FILE_ATTRIBUTE_READONLY;
				SetFileAttributes(strFullPath, dwAttributes);
			}
			
			if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				DelDirFiles(strFullPath);
				RemoveDirectory(strFullPath);
			}
			else
			{
				DeleteFile(strFullPath);
			}
		}while (FindNextFile(hFind, &wfd));
		
		FindClose(hFind);
		return TRUE;
	}
	
}

#endif