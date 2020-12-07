#ifndef DYNAMIC_h
#define DYNAMIC_h
#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include "json/json.h"
using namespace std;
#ifdef	CLASS_EXPORTS
#define CLASS_EXPORTS __declspec(dllexport)
#else
#define CLASS_EXPORTS __declspec(dllimport)
#endif

//利用宏定义类中的get/set方法
#define ATTRIBUTE_MEMBER_FUNC(argType, arg)\
public:\
	void set_##arg(argType& v) {\
	arg = v;\
	}\
	argType get_##arg() {\
	return arg;\
	}
/*
class __declspec(dllexport) CJsonObejectBase
{
protected:
enum CEnumJsonTypeMap
{
	asInt  = 1,
	asUInt,
	asString,
	asInt64,
	asUInt64
};
public:
	CJsonObejectBase(void){}
public:
	virtual ~CJsonObejectBase(void){}
	
	string Serialize()
	{
		Json::Value new_item;
		int nSize  = m_listName.size();
		for (int i = 0; i<nSize; ++i)
		{
			void* pAddr = m_listPropertyAddr[i];
			switch(m_listType[i])
			{
			case asInt:
				new_item[m_listName[i]] = (*(INT*)pAddr);
				break;
			case asUInt:
				new_item[m_listName[i]] = (*(UINT*)pAddr);
				break;
			case asInt64:
				new_item[m_listName[i]] = (*(LONGLONG*)pAddr);
				break;
			case asUInt64:
				new_item[m_listName[i]] = (*(ULONGLONG*)pAddr);
				break;
			case asString:
				new_item[m_listName[i]] = (*(string*)pAddr);
				break;
			}
		}
		Json::FastWriter writer;
		string out2 = writer.write(new_item);
		return out2;
	}
	
	bool DeSerilalize(const char*str)
	{
		Json::Reader reader;
		Json::Value root;
		if (reader.parse(str,root))
		{
			int nSize  = m_listName.size();
			for (int i = 0; i<nSize; ++i)
			{
				void* pAddr = m_listPropertyAddr[i];
				switch(m_listType[i])
				{
				case asInt:
					(*(INT*)pAddr) = root.get(m_listName[i],0).asInt();
					break;
				case asUInt:
					(*(UINT*)pAddr) = root.get(m_listName[i],0).asUInt();
					break;
				case asInt64:
					(*(LONGLONG*)pAddr) = root.get(m_listName[i],0).asInt64();
					break;
				case asUInt64:
					(*(ULONGLONG*)pAddr) = root.get(m_listName[i],0).asUInt64();
					break;
				case asString:
					(*(string*)pAddr) = root.get(m_listName[i],0).asString();
					break;
				default:
					break;
				}
			}
			return true;
		}
		return false;
	}
	
protected:
	void SetProperty(string name, CEnumJsonTypeMap type,void* addr)
	{
		m_listName.push_back(name);
		m_listPropertyAddr.push_back(addr);
		m_listType.push_back(type);
		
	}
	virtual void SetPropertys() = 0;
	vector<string> m_listName;
	vector<void *>m_listPropertyAddr;
	vector<CEnumJsonTypeMap> m_listType;
};
*/
enum ReturnStatus
{
	STS_OK=0,
	STS_NG,
	STS_ERR_FAILED,
	STS_ERR_NOT_INITIALIZED,
	STS_ERR_NOT_DATA,
	STS_ERR_NULL_PTR,
	STS_ERR_INIT,
	STS_ERR_END_OF_STREAM,
	STS_ERR_ALLOC ,
	STS_ERR_UNSUPPORTED,
	STS_ERR_INVALID_PARAMS,
	STS_ERR_FILE_OPEN,
	STS_ERR_FORMAT,
	STS_ERR_NETCONNECTFAILD 
};

struct CodeStringTable
{
	int         iCode;
	const char *pString;
};

static const CodeStringTable StringOfBaseStatus[] = {
	{ STS_OK, "Success" },
	{ STS_NG, "Failed" },
	{ STS_ERR_FAILED, "General failure" },
	{ STS_ERR_NOT_INITIALIZED, "Object is not initialized" },
	{ STS_ERR_NOT_DATA, "Not data" },
	{ STS_ERR_NULL_PTR, "Unexpected NULL pointer" },
	{ STS_ERR_INIT, "Failed to initialize object" },
	{ STS_ERR_END_OF_STREAM, "End of stream" },
	{ STS_ERR_ALLOC, "Failed to allocate memory" },
	{ STS_ERR_UNSUPPORTED, "Unsupported parameters/mode" },
	{ STS_ERR_INVALID_PARAMS, "Invalid parameters" },
	{ STS_ERR_FILE_OPEN, "Failed to open file" },
	{ STS_ERR_FORMAT, "Invalid format" },
	{ STS_ERR_NETCONNECTFAILD, "Network connection failure" },
};


//请求体
class __declspec(dllexport) Request
{
public:
	Request();
	~Request();
	CString UuidGenerator();
public:

	void setReqSetting(Json::Value &setting);
	void setReqHead(Json::Value &head);
	void setReqBody(Json::Value &body);

	Json::Value getReqSetting();
	Json::Value getReqHead();
	Json::Value getReqBody();

public:
	Json::Value reqSetting;
	Json::Value reqHead;
	Json::Value reqBody;
};

//响应体
class __declspec(dllexport) Response
{
public:
	Response();
	~Response();
public:

	void setRspHead(Json::Value &head);
	void setRspBody(Json::Value &body);

	Json::Value getRspHead();
	Json::Value getRspBody();

public:

	Json::Value rspHead;
	Json::Value rspBody;
};


class __declspec(dllexport) WSInterfaceImplementor
{
public:
	string wideCharToMultiByte(wchar_t* pWCStrKey);
	wchar_t *multiByteToWideChar(char* pKey);
	int UserVerify(Request &req, Response &rsp);
	int ParamVerify(Request &req, Response &rsp);
	int StatusChangeReport(Request &req, Response &rsp);
	int AlarmReport(Request &req, Response &rsp);
	int EQPInfoVerify(Request &req, Response &rsp);
	int RealStatusReport(Request &req, Response &rsp);
	int WIPTrackingReport(Request &req, Response &rsp);
	int UtilityReport(Request &req, Response &rsp);
	int MaterialVerify(Request &req, Response &rsp);
	int RecipeChangeReport(Request &req, Response &rsp);
	int RecipeReport(Request &req, Response &rsp);
	int RTMReport(Request &req, Response &rsp);
	int MaterialStatusReport(Request &req, Response &rsp);

	//int WSInterfaceImplEntry(char* strMethod, Request &req, Response &rsp);

	WSInterfaceImplementor();
	~WSInterfaceImplementor();
	WSInterfaceImplementor(const WSInterfaceImplementor &);
	WSInterfaceImplementor & operator= (const WSInterfaceImplementor &);
	
	static WSInterfaceImplementor& GetWSInterface()
	{
        static WSInterfaceImplementor instance;
        return instance;
    }
	friend __declspec(dllexport) WSInterfaceImplementor & GetWSInterfaceImplementor();
};
#endif





