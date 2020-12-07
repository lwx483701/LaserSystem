/*########################################################################
  ########################################################################*/
#include "stdafx.h"
//#include "resource.h"
#include "AdoCommand.h"
#include "..\\WarningInfo.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/*########################################################################
			------------------------------------------------
						   CAdoCommand class
			------------------------------------------------
  ########################################################################*/

CAdoCommand::CAdoCommand()
{
	///���� Connection ����---------------------------
	m_pCommand.CreateInstance("ADODB.Command");
	#ifdef _DEBUG
	if (m_pCommand == NULL)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14021),256);
		AfxMessageBox(ez);//"Command ���󴴽�ʧ��! ��ȷ���Ƿ��ʼ����Com����."
	}
	#endif
	ASSERT(m_pCommand != NULL);
}

CAdoCommand::CAdoCommand(CAdoConnection* pAdoConnection, CString strCommandText, CommandTypeEnum CommandType)
{
	///���� Connection ����---------------------------
	m_pCommand.CreateInstance("ADODB.Command");
	#ifdef _DEBUG
	if (m_pCommand == NULL)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14021),256);
		AfxMessageBox(ez);//"Command ���󴴽�ʧ��! ��ȷ���Ƿ��ʼ����Com����."
	}
	#endif
	ASSERT(m_pCommand != NULL);
	ASSERT(pAdoConnection != NULL);
	SetConnection(pAdoConnection);
	if (strCommandText != _T(""))
	{
		SetCommandText(LPCTSTR(strCommandText));
	}
	SetCommandType(CommandType);
}

CAdoCommand::~CAdoCommand()
{
	Release();
}

void CAdoCommand::Release()
{
	try
	{
		m_pCommand.Release();
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14042),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: Release���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
	} 
}

_RecordsetPtr CAdoCommand::Execute(long Options)
{
	ASSERT(m_pCommand != NULL);
	try
	{
		return m_pCommand->Execute(NULL, NULL, Options);
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14020),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: Execute ���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
		return NULL;
	} 
}

BOOL CAdoCommand::Cancel()
{
	ASSERT(m_pCommand != NULL);
	
	try
	{
		return (m_pCommand->Cancel() == S_OK);
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14025),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: Cancel ���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
		return FALSE;
	} 
}

_ParameterPtr CAdoCommand::CreateParameter(LPCTSTR lpstrName, 
								  DataTypeEnum Type, 
								  ParameterDirectionEnum Direction, 
								  long Size, 
								  _variant_t Value)
{

	ASSERT(m_pCommand != NULL);
	try
	{
		return m_pCommand->CreateParameter(_bstr_t(lpstrName), Type, Direction, Size, Value);
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14043),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: CreateParameter ���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
		return NULL;
	} 
}

BOOL CAdoCommand::SetCommandText(LPCTSTR lpstrCommand)
{
	ASSERT(m_pCommand != NULL);
	try
	{
		m_pCommand->PutCommandText(_bstr_t(lpstrCommand));
		return TRUE;
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14044),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: PutCommandText ���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
		return FALSE;
	} 
}

BOOL CAdoCommand::SetConnection(CAdoConnection *pConnect)
{
	ASSERT(pConnect != NULL);
	ASSERT(pConnect->GetConnection() != NULL);
	ASSERT(m_pCommand != NULL);
	
	try
	{
		m_pCommand->PutActiveConnection(_variant_t((IDispatch*)pConnect->GetConnection(), true));
		return TRUE;
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14045),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: SetConnection ���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
		return FALSE;
	} 
}
/*========================================================================
	Name:		ָʾ Command ��������͡�
    ----------------------------------------------------------
	returns:	��������ĳ�� CommandTypeEnum ��ֵ.
		[����]				 [˵��] 
		----------------------------------
		adCmdText			ָʾstrSQLΪ�����ı�, ����ͨ��SQL���. 
		adCmdTable			ָʾADO����SQL��ѯ������ strSQL �����ı��е�
						������. 
		adCmdTableDirect	ָʾ�����ĸ�����strSQL�������ı��з���������. 
		adCmdStoredProc		ָʾstrSQLΪ�洢����. 
		adCmdUnknown		ָʾstrSQL�����е���������Ϊδ֪. 
		adCmdFile			ָʾӦ����strSQL���������ļ��лָ�����(�����)
						Recordset. 
		adAsyncExecute		ָʾӦ�첽ִ��strSQL. 
		adAsyncFetch		ָʾ����ȡ Initial Fetch Size ������ָ���ĳ�ʼ
						������, Ӧ���첽��ȡ����ʣ�����. ������������δ
						��ȡ, ��Ҫ���߳̽�������ֱ�������¿���. 
		adAsyncFetchNonBlocking ָʾ��Ҫ�߳�����ȡ�ڼ��δ����. ���������
						������δ��ȡ, ��ǰ���Զ��Ƶ��ļ�ĩβ. 
   ----------------------------------------------------------
	Remarks: ʹ�� CommandType ���Կ��Ż� CommandText ���Եļ��㡣
		��� CommandType ���Ե�ֵ���� adCmdUnknown(Ĭ��ֵ), ϵͳ�����ܽ���
	����, ��Ϊ ADO ��������ṩ����ȷ�� CommandText ������ SQL ��䡢���Ǵ�
	�����̻������ơ����֪������ʹ�õ����������, ��ͨ������ CommandType 
	����ָ�� ADO ֱ��ת����ش��롣��� CommandType ������ CommandText ��
	���е��������Ͳ�ƥ��, ���� Execute ����ʱ����������
==========================================================================*/
BOOL CAdoCommand::SetCommandType(CommandTypeEnum CommandType)
{
	ASSERT(m_pCommand != NULL);
	
	try
	{
		m_pCommand->PutCommandType(CommandType);
		return TRUE;
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14046),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: PutCommandType ���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
		return FALSE;
	} 
}

long CAdoCommand::GetState()
{
	ASSERT(m_pCommand != NULL);
	
	try
	{
		return m_pCommand->GetState();
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14034),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: GetState ���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
		return -1;
	} 
}

BOOL CAdoCommand::SetCommandTimeOut(long lTime)
{
	ASSERT(m_pCommand != NULL);
	
	try
	{
		m_pCommand->PutCommandTimeout(lTime);
		return TRUE;
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14047),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: SetCommandTimeOut ���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
		return FALSE;
	} 
}

ParametersPtr CAdoCommand::GetParameters()
{
	ASSERT(m_pCommand != NULL);
	
	try
	{
		return m_pCommand->GetParameters();
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14047),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: SetCommandTimeOut ���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
		return NULL;
	} 
}

BOOL CAdoCommand::Append(_ParameterPtr param)
{
	ASSERT(m_pCommand != NULL);
	
	try
	{
		return m_pCommand->GetParameters()->Append((IDispatch*)param);
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14048),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: Append ���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
		return FALSE;
	} 
}


_ParameterPtr CAdoCommand::GetParamter(LPCTSTR lpstrName)
{
	ASSERT(m_pCommand != NULL);
	
	try
	{
		return m_pCommand->GetParameters()->GetItem(_variant_t(lpstrName));
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14049),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: GetParamter ���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
		return NULL;
	} 
}

_ParameterPtr CAdoCommand::GetParameter(long index)
{
	ASSERT(m_pCommand != NULL);
	
	try
	{
		return m_pCommand->GetParameters()->GetItem(_variant_t(index));
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14049),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: GetParamter ���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
		return NULL;
	} 
}

_variant_t CAdoCommand::GetValue(long index)
{
	ASSERT(m_pCommand != NULL);
	
	try
	{
		return m_pCommand->GetParameters()->GetItem(_variant_t(index))->Value;
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14050),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: GetValue ���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
		_variant_t vt;
		vt.vt = VT_NULL;
		return vt;
	} 
}

_variant_t CAdoCommand::GetValue(LPCTSTR lpstrName)
{
	ASSERT(m_pCommand != NULL);
	
	try
	{
		return m_pCommand->GetParameters()->GetItem(_variant_t(lpstrName))->Value;
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14050),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: GetValue ���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
		_variant_t vt;
		vt.vt = VT_NULL;
		return vt;
	} 
}

_CommandPtr& CAdoCommand::GetCommand()
{
	return m_pCommand;
}

CAdoParameter CAdoCommand::operator [](int index)
{
	CAdoParameter pParameter;
	ASSERT(m_pCommand != NULL);
	try
	{
		pParameter = m_pCommand->GetParameters()->GetItem(_variant_t(long(index)));
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14051),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: operator [] ���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
	}
	return pParameter;
}

CAdoParameter CAdoCommand::operator [](LPCTSTR lpszParamName)
{
	CAdoParameter pParameter;
	ASSERT(m_pCommand != NULL);
	try
	{
		pParameter = m_pCommand->GetParameters()->GetItem(_variant_t(lpszParamName));
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14051),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: operator [] ���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
	}
	return pParameter;
}


/*########################################################################
			  ------------------------------------------------
						     CAdoParameter class
			  ------------------------------------------------
  ########################################################################*/
CAdoParameter::CAdoParameter()
{
	m_pParameter = NULL;
	m_pParameter.CreateInstance("ADODB.Parameter");
	#ifdef _DEBUG
	if (m_pParameter == NULL)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14022),256);
		AfxMessageBox(ez);//"Parameter ���󴴽�ʧ��! ��ȷ���Ƿ��ʼ����Com����."
	}
	#endif
	ASSERT(m_pParameter != NULL);
	m_strName = _T("");
}

CAdoParameter::CAdoParameter(DataTypeEnum DataType, long lSize, ParameterDirectionEnum Direction, CString strName)
{
	m_pParameter = NULL;
	m_pParameter.CreateInstance("ADODB.Parameter");
	#ifdef _DEBUG
	if (m_pParameter == NULL)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14022),256);
		AfxMessageBox(ez);//"Parameter ���󴴽�ʧ��! ��ȷ���Ƿ��ʼ����Com����."
	}
	#endif
	ASSERT(m_pParameter != NULL);

	m_pParameter->Direction = Direction;
	m_strName = strName;
	m_pParameter->Name = m_strName.AllocSysString();
	m_pParameter->Type = DataType;
	m_pParameter->Size = lSize;
}

_ParameterPtr& CAdoParameter::operator =(_ParameterPtr& pParameter)
{
	if (pParameter != NULL)
	{
		m_pParameter = pParameter;
	}
	else
	{
		return pParameter;
	}
	return m_pParameter;
}

CAdoParameter::~CAdoParameter()
{
	m_pParameter.Release();
	m_pParameter = NULL;
	m_strName = _T("");
}

/*========================================================================
	Name:		ָʾ�� Parameter ����������ֵ������ Field ����ľ��ȡ�
    ----------------------------------------------------------
	Params:		���û򷵻� Byte ֵ��������ʾֵ�����λ������ֵ�� Parameter
			������Ϊ��/д������ Field ������Ϊֻ����
    ----------------------------------------------------------
	Remarks:	ʹ�� Precision ���Կ�ȷ����ʾ���� Parameter �� Field ����ֵ
			�����λ��
==========================================================================*/
BOOL CAdoParameter::SetPrecision(char nPrecision)
{
	ASSERT(m_pParameter != NULL);
	try
	{
		m_pParameter->PutPrecision(nPrecision);
		return TRUE;
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14052),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: SetPrecision ���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
		return FALSE;
	}
}

/*========================================================================
	Name:		ָ�� Parameter �� Field ����������ֵ�ķ�Χ��
    ----------------------------------------------------------
	Params:		���û򷵻��ֽ�ֵ��ָʾ����ֵ����ȷ����С����λ����
    ----------------------------------------------------------
	Remarks:	ʹ�� NumericScale ���Կ�ȷ�����ڱ��������� Parameter �� Field 
		�����ֵ��С��λ����
		���� Parameter ����NumericScale ����Ϊ��/д������ Field ����
	NumericScale ����Ϊֻ����

==========================================================================*/
BOOL CAdoParameter::SetNumericScale(int nScale)
{
	ASSERT(m_pParameter != NULL);
	try
	{
		m_pParameter->PutNumericScale(nScale);
		return TRUE;
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14052),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: SetPrecision ���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
		return FALSE;
	}	
}

/*========================================================================
	Name:		ָʾ Parameter �������������.
    ----------------------------------------------------------
	Params:		[DataType]: DataTypeEnum ����ֵ, ��ο� CRecordSet �����
			����.
==========================================================================*/
BOOL CAdoParameter::SetType(DataTypeEnum DataType)
{
	ASSERT(m_pParameter != NULL);
	try
	{
		m_pParameter->PutType(DataType);
		return TRUE;
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14053),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: SetType ���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
		return FALSE;
	}	
}

DataTypeEnum CAdoParameter::GetType()
{
	ASSERT(m_pParameter != NULL);
	try
	{
		return m_pParameter->GetType();
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14054),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: SetDirection ���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
		return adEmpty;
	}
}

/*========================================================================
	Name:		��ʾ Parameter ���������С�����ֽڻ��ַ�����
    ----------------------------------------------------------
	Params:		[size]: ��ʾ Parameter ���������С�����ֽڻ��ַ����ĳ�
			����ֵ��
==========================================================================*/
BOOL CAdoParameter::SetSize(int size)
{
	ASSERT(m_pParameter != NULL);
	try
	{
		m_pParameter->PutSize(long(size));
		return TRUE;
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14055),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: SetSize ���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
		return FALSE;
	}	
}

int CAdoParameter::GetSize()
{
	ASSERT(m_pParameter != NULL);
	try
	{
		return (int)m_pParameter->GetSize();
		
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14054),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: SetDirection ���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
		return -1;
	}
}

/*========================================================================
	Name:		ָʾ��������ơ�
==========================================================================*/
BOOL CAdoParameter::SetName(CString strName)
{
	ASSERT(m_pParameter != NULL);
	try
	{
		m_pParameter->PutName(_bstr_t(LPCTSTR(strName)));
		return TRUE;
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14056),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: SetName ���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
		return FALSE;
	}	
}

CString CAdoParameter::GetName()
{
	ASSERT(m_pParameter != NULL);
	try
	{
		return CString(LPCTSTR(m_pParameter->GetName()));
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14056),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: SetName ���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
		return CString(_T(""));
	}
}

/*========================================================================
	Name:		ָʾ Parameter �����������������������������Ǽ��������
		�������������ò����Ƿ�Ϊ�洢���̷��ص�ֵ��
    ----------------------------------------------------------
	Params:		[Direction]: ��������ĳ�� ParameterDirectionEnum ֵ��
		[����]				[˵��] 
		-------------------------------------------
		AdParamUnknown		ָʾ��������δ֪�� 
		AdParamInput		Ĭ��ֵ��ָʾ��������� 
		AdParamOutput		ָʾ��������� 
		AdParamInputOutput	ͬʱָʾ������������������ 
		AdParamReturnValue	ָʾ����ֵ�� 
==========================================================================*/
BOOL CAdoParameter::SetDirection(ParameterDirectionEnum Direction)
{
	ASSERT(m_pParameter != NULL);
	try
	{
		m_pParameter->PutDirection(Direction);
		return TRUE;
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14054),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: SetDirection ���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
		return FALSE;
	}	
}

ParameterDirectionEnum CAdoParameter::GetDirection()
{
	ASSERT(m_pParameter != NULL);
	try
	{
		return m_pParameter->GetDirection();
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14054),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: SetDirection ���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
		return adParamUnknown;
	}	
}

/*########################################################################
			  ------------------------------------------------
						
			  ------------------------------------------------
  ########################################################################*/

BOOL CAdoParameter::SetValue(const  _variant_t &value)
{
	ASSERT(m_pParameter != NULL);

	try
	{
		if (m_pParameter->Size == 0)
		{
			m_pParameter->Size = sizeof(VARIANT);
		}
		m_pParameter->Value = value;
		return TRUE;
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14050),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: GetValue ���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
		return FALSE;
	}
}

BOOL CAdoParameter::SetValue(const bool &value)
{
	try
	{
		if (m_pParameter->Size == 0)
		{
			m_pParameter->Size = sizeof(short);
		}
		m_pParameter->Value = _variant_t(value);
		return TRUE;
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14057),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: SetValue ���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
		return FALSE;
	}
}

BOOL CAdoParameter::SetValue(const int &value)
{
	try
	{
		if (m_pParameter->Size == 0)
		{
			m_pParameter->Size = sizeof(int);
		}
		m_pParameter->Value = _variant_t(long(value));
		return TRUE;
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14057),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: SetValue ���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
		return FALSE;
	}
}

BOOL CAdoParameter::SetValue(const long &value)
{
	try
	{
		if (m_pParameter->Size == 0)
		{
			m_pParameter->Size = sizeof(long);
		}
		m_pParameter->Value = _variant_t(value);
		return TRUE;
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14057),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: SetValue ���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
		return FALSE;
	}
}

BOOL CAdoParameter::SetValue(const double &value)
{
	try
	{
		if (m_pParameter->Size == 0)
		{
			m_pParameter->Size = sizeof(double);
		}
		m_pParameter->Value = _variant_t(value);
		return TRUE;
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14057),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: SetValue ���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
		return FALSE;
	}
}

BOOL CAdoParameter::SetValue(const CString &value)
{
	_variant_t var;
	var.vt = value.IsEmpty() ? VT_NULL : VT_BSTR;
	var.bstrVal = value.AllocSysString();

	try
	{
		if (m_pParameter->Size == 0)
		{
			m_pParameter->Size = value.GetLength();
		}
		m_pParameter->Value = var;
		return TRUE;
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14057),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: SetValue ���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
		return FALSE;
	}
}

BOOL CAdoParameter::SetValue(const COleDateTime &value)
{
	_variant_t var;
	var.vt = VT_DATE;
	var.date = value;
	
	try
	{
		if (m_pParameter->Size == 0)
		{
			m_pParameter->Size = sizeof(DATE);
		}
		m_pParameter->Value = var;
		return TRUE;
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14057),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: SetValue ���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
		return FALSE;
	}
	return TRUE;
}

BOOL CAdoParameter::SetValue(const BYTE &value)
{
	try
	{
		if (m_pParameter->Size == 0)
		{
			m_pParameter->Size = sizeof(BYTE);
		}
		m_pParameter->Value = _variant_t(value);
		return TRUE;
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14057),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: SetValue ���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
		return FALSE;
	}
}

BOOL CAdoParameter::SetValue(const short &value)
{
	try
	{
		if (m_pParameter->Size == 0)
		{
			m_pParameter->Size = sizeof(short);
		}
		m_pParameter->Value = _variant_t(value);
		return TRUE;
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14057),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: SetValue ���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
		return FALSE;
	}
}

BOOL CAdoParameter::SetValue(const float &value)
{
	try
	{
		if (m_pParameter->Size == 0)
		{
			m_pParameter->Size = sizeof(float);
		}
		m_pParameter->Value = _variant_t(value);
		return TRUE;
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14057),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: SetValue ���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
		return FALSE;
	}
}


BOOL CAdoParameter::GetValue(bool &value)
{
	try
	{
		value = vartobool(m_pParameter->Value);
		return TRUE;
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14050),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: GetValue ���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
		return FALSE;
	}
}

BOOL CAdoParameter::GetValue(BYTE &value)
{
	try
	{
		value = vartoby(m_pParameter->Value);
		return TRUE;
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14050),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: GetValue ���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
		return FALSE;
	}
}

BOOL CAdoParameter::GetValue(short &value)
{
	try
	{
		value = vartoi(m_pParameter->Value);
		return TRUE;
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14050),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: GetValue ���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
		return FALSE;
	}
}

BOOL CAdoParameter::GetValue(int &value)
{
	try
	{
		value = (int)vartol(m_pParameter->Value);
		return TRUE;
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14050),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: GetValue ���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
		return FALSE;
	}
}

BOOL CAdoParameter::GetValue(long &value)
{
	try
	{
		value = vartol(m_pParameter->Value);
		return TRUE;
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14050),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: GetValue ���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
		return FALSE;
	}
}

BOOL CAdoParameter::GetValue(double &value)
{
	try
	{
		value = vartof(m_pParameter->Value);
		return TRUE;
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14050),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: GetValue ���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
		return FALSE;
	}
}

BOOL CAdoParameter::GetValue(CString &value)
{
	try
	{
		value = vartostr(m_pParameter->Value);
		return TRUE;
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14050),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: GetValue ���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
		return FALSE;
	}
}

BOOL CAdoParameter::GetValue(COleDateTime &value)
{
	try
	{
		value = vartodate(m_pParameter->Value);
		return TRUE;
	}
	catch (_com_error e)
	{
		char ez[256]={""};//ly 20110405
		strncpy(ez ,GetLang().GetWarningText(14050),256);
		TRACE(_T(ez), e.ErrorMessage(), __FILE__, __LINE__);//"Warning: GetValue ���������쳣. ������Ϣ: %s; �ļ�: %s; ��: %d\n"
		return FALSE;
	}
}
