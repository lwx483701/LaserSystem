//////////////////////////////////// HttpClient.h
#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H
 
#include <afxinet.h>
#include <string>
using namespace std;
 
#define  IE_AGENT  _T("Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; .NET CLR 2.0.50727)")
 
// �����ɹ�
#define SUCCESS        0
// ����ʧ��
#define FAILURE        1
// ������ʱ www.it165.net
#define OUTTIME        2

//���ú궨�����е�get/set����
#define ATTRIBUTE_MEMBER_FUNC(argType, arg)\
public:\
	void set_##arg(const argType& v) {\
	arg = v;\
	}\
	argType get_##arg() {\
	return arg;\
	}
 
class CHttpClient
{
public:
	CHttpClient(LPCTSTR strAgent = IE_AGENT);
	virtual ~CHttpClient(void);
	
	CString generate();
	int HttpGet(LPCTSTR strUrl, LPCTSTR strPostData, CString &strResponse);
	int HttpPost(LPCTSTR strUrl, LPCTSTR strPostData, CString &strResponse);
	int HttpPut(LPCTSTR strUrl, LPCTSTR strPostData, CString &strResponse);
 
private:
	int ExecuteRequest(int strMethod, LPCTSTR strUrl, LPCTSTR strPostData, CString &strResponse);
	void Clear();
	
 
private:
	CInternetSession *m_pSession;
	CHttpConnection *m_pConnection;
	CHttpFile *m_pFile;
};


class RequsetParam 
{
public:
	RequsetParam();
	~RequsetParam();
	ATTRIBUTE_MEMBER_FUNC(CString, reqCode)
	ATTRIBUTE_MEMBER_FUNC(CString, reqTime)
	ATTRIBUTE_MEMBER_FUNC(CString, clientCode)
	ATTRIBUTE_MEMBER_FUNC(CString, tokenCode)
	ATTRIBUTE_MEMBER_FUNC(CString, interfaceName)
	ATTRIBUTE_MEMBER_FUNC(CString, agvCode)
	ATTRIBUTE_MEMBER_FUNC(CString, taskCodes)
	ATTRIBUTE_MEMBER_FUNC(CString, taskTyp)
	ATTRIBUTE_MEMBER_FUNC(CString, wbCode)
	ATTRIBUTE_MEMBER_FUNC(CString, podCode)
	ATTRIBUTE_MEMBER_FUNC(CString, podDir)
	ATTRIBUTE_MEMBER_FUNC(CString, priority)
	ATTRIBUTE_MEMBER_FUNC(CString, taskCode)
	CString writeParamInfoJson();

public:
	CString reqCode;
	CString reqTime;
	CString clientCode;
	CString tokenCode;
	CString interfaceName;
	CString agvCode;

	//queryTaskStatus
	CString taskCodes;

	//genAgvSchedulingTask
	CString taskTyp;
	CString wbCode;
	CString positionCodePath;
	CString riseStaPositionCode;//���������λ�ñ��
	CString riseEndPositionCode;//�������յ�λ�ñ��
	CString downStaPositionCode;//���������λ�ñ��
	CString downEndPositionCode;//�������յ�λ�ñ��
	CString podCode;
	CString podTyp;
	CString podDir;
	CString materialLot;
	CString priority;
	CString taskCode;
	CString data;
	
};


class RemoteResult
{
public:
	RemoteResult();
	~RemoteResult();
	ATTRIBUTE_MEMBER_FUNC(CString, code)
	ATTRIBUTE_MEMBER_FUNC(CString, message)
	ATTRIBUTE_MEMBER_FUNC(CString, reqCode)
	ATTRIBUTE_MEMBER_FUNC(CString, data)

public:
	CString code;
	CString message;
	CString reqCode;
	CString data;
};

 
#endif // HTTPCLIENT_H