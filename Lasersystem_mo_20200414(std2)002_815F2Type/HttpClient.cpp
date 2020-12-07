
#include "stdafx.h"
#include "HttpClient.h"
#include <stdio.h>
//#include <stdint.h>
#include <string>
#include <iostream>
#include <objbase.h>
#include "json/json.h"
#include "SysParameter.h"
#include "ToolUtil.h"
using namespace std;
 
#define  BUFFER_SIZE       1024
#define	 GUID_LEN		   64
#define  NORMAL_CONNECT             INTERNET_FLAG_KEEP_CONNECTION
#define  SECURE_CONNECT             NORMAL_CONNECT | INTERNET_FLAG_SECURE
#define  NORMAL_REQUEST             INTERNET_FLAG_RELOAD | INTERNET_FLAG_DONT_CACHE 
#define  SECURE_REQUEST             NORMAL_REQUEST | INTERNET_FLAG_SECURE | INTERNET_FLAG_IGNORE_CERT_CN_INVALID

CHttpClient::CHttpClient(LPCTSTR strAgent)
{
	m_pSession = new CInternetSession(strAgent);
	m_pConnection = NULL;
	m_pFile = NULL;
}
 
 
CHttpClient::~CHttpClient(void)
{
	Clear();
	if (NULL != m_pSession)
	{
		m_pSession->Close();
		delete m_pSession;
		m_pSession = NULL;
	}
}
 
void CHttpClient::Clear()
{
	if (NULL != m_pFile)
	{
		m_pFile->Close();
		delete m_pFile;
		m_pFile = NULL;
	}
 
	if (NULL != m_pConnection)
	{
		m_pConnection->Close();
		delete m_pConnection;
		m_pConnection = NULL;
	}
}


CString CHttpClient::generate()
{
	char buf[GUID_LEN] = { 0 };
	GUID guid;
	
	if (CoCreateGuid(&guid))
	{
		return CString("");
	}
	
	sprintf(buf,"%08X%04X%04x%02X%02X%02X%02X%02X%02X%02X%02X",
		guid.Data1, guid.Data2, guid.Data3,guid.Data4[0], guid.Data4[1], guid.Data4[2],guid.Data4[3], guid.Data4[4], guid.Data4[5],guid.Data4[6], guid.Data4[7]);
	
	return buf;
}
 
int CHttpClient::ExecuteRequest(int strMethod, LPCTSTR strUrl, LPCTSTR strPostData, CString &strResponse)
{
	int result =FAILURE ;
	//WCHAR* wPostData = strPostData.GetBuffer();
	CString strServer;
	CString strObject;
	DWORD dwServiceType;
	INTERNET_PORT nPort;
 
 
	AfxParseURL(strUrl, dwServiceType, strServer, strObject, nPort);
	if (AFX_INET_SERVICE_HTTP != dwServiceType && AFX_INET_SERVICE_HTTPS != dwServiceType)
	{
		return FAILURE;
	}
 
	try
	{
		m_pConnection = m_pSession->GetHttpConnection(strServer,
			dwServiceType == AFX_INET_SERVICE_HTTP ? NORMAL_CONNECT : SECURE_CONNECT,
			nPort);
		m_pFile = m_pConnection->OpenRequest(strMethod, strObject,
			NULL, 1, NULL, NULL,
			(dwServiceType == AFX_INET_SERVICE_HTTP ? NORMAL_REQUEST : SECURE_REQUEST));
 
		/*设置请求相关参数*/
		m_pFile->AddRequestHeaders("Accept: */*,application/json");//accept请求报头域，表示客户端接受哪些类型的信息
		m_pFile->AddRequestHeaders("Accept-Charset:UTF8");
		m_pFile->AddRequestHeaders("Accept-Language: zh-cn;q=0.8,en;q=0.6,ja;q=0.4");
		m_pFile->AddRequestHeaders("Content-Type:application/json");//content为实体报头域，格式及编码
 
	//	m_pFile->SendRequest(NULL, 0, (LPVOID)(LPCTSTR)strPostData, strPostData == NULL ? 0 : _tcslen(strPostData));
 
		printf("before = %s\n\n\n", strPostData);
		/*请求body内容先转为UTF-8编码，与服务端保持一致,cword为要发送内容*/
		if (strPostData != NULL){
			string postData = ToolUtil::GbkToUtf8(strPostData);
			printf("after = %s\n", postData.c_str());
			printf("content长度为%d\n", postData.length());
			m_pFile->SendRequest(NULL, 0, (LPVOID)postData.c_str(), postData.length());//发送请求
		}
		else{
			m_pFile->SendRequest(NULL, 0, NULL, 0);//发送请求
		}
 
		DWORD dwRet;
		m_pFile->QueryInfoStatusCode(dwRet);//查询执行状态
		printf("HTTP_STATUS_code:%d\n", dwRet);
		if (dwRet == HTTP_STATUS_OK){//http请求执行失败
			result = SUCCESS;
		}
 
		/*保存http响应*/
		char szChars[BUFFER_SIZE + 1] = { 0 };
		string strRawResponse = "";
		UINT nReaded = 0;
		while ((nReaded = m_pFile->Read((void*)szChars, BUFFER_SIZE)) > 0)
		{
			szChars[nReaded] = '\0';
			strRawResponse += szChars;
			memset(szChars, 0, BUFFER_SIZE + 1);
		}
 
		/*utf8转unicode*/
		int unicodeLen = MultiByteToWideChar(CP_UTF8, 0, strRawResponse.c_str(), -1, NULL, 0);
		WCHAR *pUnicode = new WCHAR[unicodeLen + 1];
		memset(pUnicode, 0, (unicodeLen + 1)*sizeof(wchar_t));
		MultiByteToWideChar(CP_UTF8, 0, strRawResponse.c_str(), -1, pUnicode, unicodeLen);
		strResponse = pUnicode;//最终响应结果
		//TRACE(strResponse + L"");
		delete[]pUnicode;
		pUnicode = NULL;
		
		Clear();
	}
	catch (CInternetException* e)
	{
		Clear();
		DWORD dwErrorCode = e->m_dwError;
		e->Delete();
 
		DWORD dwError = GetLastError();
 
		printf("dwError = %d\n", dwError, 0);
 
		strResponse = L"CInternetException\n";
 
		if (ERROR_INTERNET_TIMEOUT == dwErrorCode)
		{
			return OUTTIME;
		}
		else
		{
			return FAILURE;
		}
	}
	return result;
}
 
int CHttpClient::HttpGet(LPCTSTR strUrl, LPCTSTR strPostData, CString &strResponse)
{
	return ExecuteRequest(CHttpConnection::HTTP_VERB_GET, strUrl, NULL, strResponse);
}
 
int CHttpClient::HttpPost(LPCTSTR strUrl, LPCTSTR strPostData, CString &strResponse)
{
	return ExecuteRequest(CHttpConnection::HTTP_VERB_POST, strUrl, strPostData, strResponse);
}
int CHttpClient::HttpPut(LPCTSTR strUrl, LPCTSTR strPostData, CString &strResponse)
{
	return ExecuteRequest(CHttpConnection::HTTP_VERB_PUT, strUrl, strPostData, strResponse);
}



RequsetParam::RequsetParam()
{
	reqCode = "";
	reqTime = "";
	clientCode = "";
	tokenCode = "";
	interfaceName = "";
	agvCode = "";
	taskCodes = "";

	taskTyp = "";
	wbCode = "";
	positionCodePath = "";
	riseStaPositionCode = "";
	riseEndPositionCode = "";
	downStaPositionCode = "";
	downEndPositionCode = "";
	podCode = "";
	podTyp = "";
	podDir = "";
	materialLot = "";
	priority = "";
	taskCode = "";
	data = "";
}

CString RequsetParam::writeParamInfoJson()
{
	// 构建json数组
	Json::Value root;
	Json::Value array;
    Json::Value positionCode;
    Json::FastWriter writer;

	//genAgvSchedulingTask\queryTaskStatus\cancelTask方法相同根节点属性
    root["reqCode"] = Json::Value(reqCode);
	root["reqTime"] = Json::Value(reqTime);
	root["clientCode"] = Json::Value(clientCode);
	root["tokenCode"] = Json::Value(tokenCode);
	root["interfaceName"] = Json::Value(interfaceName);
	root["agvCode"] = Json::Value(agvCode);
	
	//需要根据不同的方法名来拼接不同的json param
	if (interfaceName == "genAgvSchedulingTask")
	{
		root["taskTyp"] = Json::Value(taskTyp);
		root["wbCode"] = Json::Value(wbCode);
		
		//上料
		if (GetDoc().GetSysTaskTypeRise() == taskTyp)
		{
			positionCode["positionCode"] = Json::Value(riseStaPositionCode);
			positionCode["type"] = Json::Value("00");
			if (riseStaPositionCode != "")
			{
				array.append(positionCode);
			}
			
			positionCode["positionCode"] = Json::Value(riseEndPositionCode);
			positionCode["type"] = Json::Value("00");
			if (riseEndPositionCode != "")
			{
				array.append(positionCode);
			}	
		} 
		//下料
		if (GetDoc().GetSysTaskTypeDown() == taskTyp)
		{
			positionCode["positionCode"] = Json::Value(downStaPositionCode);
			positionCode["type"] = Json::Value("00");
			if (downStaPositionCode != "")
			{
				array.append(positionCode);
			}
			
			
			positionCode["positionCode"] = Json::Value(downEndPositionCode);
			positionCode["type"] = Json::Value("00");
			if (downEndPositionCode != "")
			{
				array.append(positionCode);
			}	
		} 

		// 子节点挂到根节点上
		root["positionCodePath"] = Json::Value(array);
		root["podCode"] = Json::Value(podCode);
		root["podTyp"] = Json::Value(podTyp);
		root["podDir"] = Json::Value(podDir);
		root["materialLot"] = Json::Value(materialLot);
		root["priority"] = Json::Value(priority);
		root["taskCode"] = Json::Value(taskCode);
		root["data"] = Json::Value(data);
	}

	if (interfaceName == "queryTaskStatus")
	{
		root["taskCodes"].append(Json::Value(taskCodes));
	}
	
	if (interfaceName == "cancelTask")
	{
		root["taskCode"] = Json::Value(taskCode);
	}

    // 添加数组格式
    //array["array"].append(root);
    
	string strValue = root.toStyledString();	// json对象转变为json字符串
	CString jsonParam;
	jsonParam.Format("%s",strValue.c_str());
	return jsonParam;
}

RequsetParam::~RequsetParam()
{
} 
 


RemoteResult::RemoteResult()
{
	code = "";
	message = "";
	reqCode = "";
	data = "";
}

RemoteResult::~RemoteResult()
{
} 

/*
int main()
{
	
	CHttpClient   conn;
	CString postResponse = "";

	//queryTaskStatus
	//string url = "http://115.236.50.12:808/cms/services/rest/hikRpcService/queryTaskStatus";
	//string postData = "{\"reqCode\":\"SANDLEE0001\",\"reqTime\":\"\",\"clientCode\":\"\",\"tokenCode\":\"\",\"interfaceName\":\"queryTaskStatus\",\"agvCode\":\"\",\"taskCodes\":[\"09FDC25F32F043569ACB5D622BCB37DF\"]}";
	//int result = conn.HttpPost(url.c_str(),postData.c_str(),postResponse);

	//genAgvSchedulingTask
	/*string url = "http://115.236.50.12:808/cms/services/rest/hikRpcService/genAgvSchedulingTask";
	string postData = "{\"reqCode\":\"TEST2580\",\"reqTime\":\"\",\"clientCode\":\"TEST\",\"tokenCode\":\"\",\"interfaceName\":\"genAgvSchedulingTask\",\"taskTyp\":\"F002\", \"wbCode\": \"\", \"positionCodePath\": [ {\"positionCode\":\"176000AA115022\",\"type\":\"00\"}],\"podCode\":\"\",\"podTyp\":\"0\",\"podDir\":\"\",\"materialLot\":\"\",\"priority\":\"2\",\"taskCode\":\"C5AA930071214B649DEB1B948DC9MMMM\",\"agvCode\":\"\",\"data\":\"\"}";
	int result = conn.HttpPost(url.c_str(),postData.c_str(),postResponse);

	//cancelTask
	//string url = "http://115.236.50.12:808/cms/services/rest/hikRpcService/cancelTask";
	//string postData = "{ \"reqCode\": \"70221AED81B94474844A569603C95FF3\", \"reqTime\":\"2019-10-30 11:35:49\", \"clientCode\": \"\", \"tokenCode\":\"\", \"interfaceName\":\"cancelTask\", \"agvCode\": \"\", \"taskCode\": \"task002\" }";
	//int result = conn.HttpPost(url.c_str(),postData.c_str(),postResponse);

	//continueTask
	//string url = "http://115.236.50.12:808/cms/services/rest/hikRpcService/continueTask";
	//string postData = "{ \"reqCode\": \"D89CD7339B9642DA9E3B42E3BA15647G\", \"reqTime\": \"2019-10-30 10:12:58\", \"clientCode\": \"\", \"tokenCode\": \"\", \"interfaceName\": \"continueTask\", \"wbCode\": \"\", \"podCode\": \"\", \"agvCode\": \"\", \"taskCode\": \"task002\", \"taskSeq\": \"\", \"data\": \"\" }";
	//int result = conn.HttpPost(url.c_str(),postData.c_str(),postResponse);

	
	
	//agvCallback
	//http://IP:PORT/xxx/agv/agvCallbackService/agvCallback

	printf("result = %d\n",result);
	printf("postResponse = %s\n",postResponse);

	string strValue = postResponse.GetBuffer(0);
	//std::string strValue="{\"key1\":\"value1\",\"array\":[{\"key2\":\"value2\"},{\"key2\":\"value3\"},{\"key2\":\"value4\"}]}"; 
	Json::Reader reader;//json解析
	Json::Value value;//表示一个json格式的对象
	
	if(reader.parse(strValue,value))//解析出json放到json中区
	{
		string out=value["code"].asString();
		cout << "code = "<< out << endl;
		out = value["message"].asString();
		cout << "message = " << out << endl;
		const Json::Value arrayObj=value["array"];//迭代器
        for (int i=0; i < arrayObj.size();i++)  
		{
			out=arrayObj[i]["key2"].asString();
			std::cout<<out;
			if(i!=arrayObj.size()-1)
				std::cout<<std::endl;;
		}
	}

	std::string temp = utility::uuid::generate();
	cout << temp << endl;

	std::string temp1 = utility::uuid::generate();
	cout << temp1 << endl;

	system("pause");
	return 0;
}*/

