// Registry.cpp

#include "stdafx.h"
#include "Registry.h"

CRegistry::CRegistry()
{

	m_hKey = NULL;
	//Open( _hKey, m_strUseKey );

}

CRegistry::CRegistry( HKEY hKey, const char *lpszSubKey )
{

	m_hKey = NULL;
	Open( hKey, lpszSubKey );

}

CRegistry::~CRegistry()
{

	Close();

}

BOOL CRegistry::Open( HKEY hKey, const char *lpszSubKey )
{

	Close();

	if( ::RegOpenKeyEx( hKey, lpszSubKey, 0, KEY_ALL_ACCESS, &m_hKey ) != ERROR_SUCCESS ){
		m_hKey = NULL;
		m_dwLastError = GetLastError();
		return( FALSE );
	}
 //   CreateKey(m_hKey,"User4",NULL);
 //   DeleteKey(m_hKey,"1");
#if 0
DWORD MaxsubKLen,NumsubKs,Index,subKnameLen;
RegQueryInfoKey(m_hKey,NULL,NULL,NULL,&NumsubKs,&MaxsubKLen,
              NULL,NULL,NULL,NULL,NULL,NULL);
//	int n = RegEnumKey(hKey,1,"user1",255);
DWORD dwIndex=0,lpcbname=100,ret=0; 
char T_name[100],Buffer[100]; 
FILETIME lpftlast; 
int i=0; 
//for(i=0;ret==ERROR_SUCCESS;i++,dwIndex++) 
for(i=0;ret==ERROR_SUCCESS;i++,dwIndex++) 
{ 

	ret=RegEnumKeyEx(m_hKey,dwIndex,T_name,&lpcbname, 
	NULL,NULL,NULL,&lpftlast); 
	//dwIndex：欲获取的子项的索引。第一个子项的索引编号为零 
	//T_name：用于装载指定索引处项名的一个缓冲区 
	//&lpcbname：指定一个变量，用于装载lpName缓冲区的实际长度（包括空字符）。 
	//一旦返回，它会设为实际装载到lpName缓冲区的字符数量 
	//NULL：未用，设为零 
	//NULL：项使用的类名 
	//NULL：用于装载lpClass缓冲区长度的一个变量 
	//&lpftlast：FILETIME，枚举子项上一次修改的时间 

	//strcat(name[i],T_name); 
//ReadStringInSubkey(T_name,NULL);
lpcbname=100; 
} 

	ret=RegEnumKeyEx(m_hKey,0,T_name,&lpcbname, 
	NULL,NULL,NULL,&lpftlast); 
#else


#endif
	return( TRUE );

}

BOOL CRegistry::Close( void )
{
	BOOL bRet = TRUE;
	if( m_hKey == NULL )
		return( FALSE );

	bRet = ( ::RegCloseKey( m_hKey ) == ERROR_SUCCESS );
	m_hKey = NULL;
	return( bRet );
}

BOOL CRegistry::IsOpen( void )
{
	return( m_hKey != NULL );
}

BOOL CRegistry::Read( const char *lpszValueName, LPVOID lpReturnBuffer, int nSize )
{

	if( m_hKey == NULL )
		return( FALSE );

	DWORD dwSize = (DWORD) nSize;
	BOOL bRet = ( ::RegQueryValueEx( m_hKey, lpszValueName, NULL, NULL, 
		(unsigned char *) lpReturnBuffer, &dwSize ) == ERROR_SUCCESS );

	m_dwLastError = GetLastError();

	return( bRet );

}

BOOL CRegistry::ReadDWORD( const char *lpszValueName, DWORD *pdwData, DWORD *pdwLastError )
{

	if( m_hKey == NULL )
		return( FALSE );

	BOOL bRet = Read( lpszValueName, pdwData, sizeof( DWORD ) );

	if( pdwLastError != NULL )
		*pdwLastError = m_dwLastError;

	return( bRet );

}

BOOL CRegistry::ReadString( const char *lpszValueName, LPVOID lpReturnBuffer, int nSize, DWORD *pdwLastError )
{

	if( m_hKey == NULL )
		return( FALSE );

	char *lpWork = (char *) lpReturnBuffer;
	lpWork[0] = 0;
	BOOL bRet = Read( lpszValueName, lpReturnBuffer, nSize );

	if( pdwLastError != NULL )
		*pdwLastError = m_dwLastError;

	return( bRet );

}

char **CRegistry::ReadMultipleStrings( const char *lpszValueName, DWORD *pdwLastError )
{
	char szEntireString[2500];

	if( !ReadString( lpszValueName, szEntireString, 2500, pdwLastError ) )
		return( NULL );

	if( szEntireString[0] == 0 )
		return( NULL );

	int nCount = 0;
	if( szEntireString[strlen(szEntireString)-1] != ';' )
		nCount = 1;
	char *pPointer = szEntireString;
	do{
		pPointer = strstr( pPointer, ";" );
		if( pPointer != NULL ){
			nCount++;
			pPointer++;
			}
		} while( pPointer != NULL );

	int i = 0;
	char *pEnd;
	char **pList = (char **) new char [(nCount+3)*sizeof(char *)];
	if( pList == NULL )
		return( NULL );
	memset( pList, 0, ( nCount + 3 ) * sizeof(char *) );

	pPointer = szEntireString;
	do{

		pEnd = strstr( pPointer, ";" );
		int nSize = strlen( pPointer );
		if( pEnd != NULL )
			nSize = pEnd - pPointer;

		pList[i] = new char [nSize+3];
		if( pList[i] != NULL ){
			memset( pList[i], 0, nSize + 3 );
			memcpy( pList[i], pPointer, nSize );
			}
		else pEnd = NULL;

		pPointer = pEnd;
		if( pPointer != NULL )
			pPointer++;

		i++;

		} while( pPointer != NULL && pPointer[0] != 0 );

	return( pList );

}

void CRegistry::DeleteList( char **pList )
{

	if( pList == NULL )
		return;

	int i = 0;
	while( pList[i] != NULL ){
		delete [] pList[i];
		i++;
		}
	delete pList;

}

BOOL CRegistry::WriteDWORD( const char *lpszValueName, DWORD dwData, DWORD *pdwLastError )
{

	if( m_hKey == NULL )
		return( FALSE );

	m_nSize = sizeof( DWORD );
	BOOL bRet = Write( lpszValueName, &dwData, REG_DWORD, sizeof( DWORD ) );

	if( pdwLastError != NULL )
		*pdwLastError = m_dwLastError;

	return( bRet );

}

BOOL CRegistry::WriteString( const char *lpszValueName, LPVOID lpData, DWORD *pdwLastError )
{

	if( m_hKey == NULL )
		return( FALSE );

	m_nSize = 2000;
	BOOL bRet = Write( lpszValueName, lpData, REG_SZ, (DWORD) strlen( (const char *) lpData ) + 1 );

	if( pdwLastError != NULL )
		*pdwLastError = m_dwLastError;

	return( bRet );

}

BOOL CRegistry::Write( const char *lpszValueName, LPVOID lpData, DWORD dwType, int nSize )
{

	if( m_hKey == NULL )
		return( FALSE );

	DWORD dwSize = (DWORD) m_nSize;
	BOOL bRet = ( ::RegSetValueEx( m_hKey, lpszValueName, 0, dwType, (unsigned char *) lpData, nSize ) == ERROR_SUCCESS );

	m_dwLastError = GetLastError();

	return( bRet );

}

BOOL CRegistry::CreateKey( HKEY hKey, const char *lpszSubKey, const char *lpszClass )
{
	HKEY hOpenedKey;
	DWORD dwDisposition;
	DWORD dwLastError;

	BOOL bRet = ( ::RegCreateKeyEx( hKey, lpszSubKey, 0, (char *) lpszClass, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hOpenedKey, &dwDisposition ) == ERROR_SUCCESS );
	if( bRet ) ::RegCloseKey( hOpenedKey );
	dwLastError = GetLastError();

	return( bRet );

}

BOOL CRegistry::DeleteKey( HKEY hKey, const char *lpszSubKey )
{
	BOOL bRet;
	DWORD dwLastError;

	bRet = ( ::RegDeleteKey( hKey, lpszSubKey ) == ERROR_SUCCESS );
	dwLastError = GetLastError();

	return( bRet );
}

long CRegistry::GetSubKeyNum(const char *lpKey)
{
    DWORD MaxsubKLen,NumsubKs;
    ::RegQueryInfoKey(m_hKey,NULL,NULL,NULL,&NumsubKs,&MaxsubKLen,
              NULL,NULL,NULL,NULL,NULL,NULL);
	m_dwLastError = GetLastError();
	return NumsubKs;
}

CString CRegistry::GetSubKeyName(int nIndex)
{
// char T_name[100];												//20200617
   char T_name[1024]; 
   DWORD lpcbname=1024;
   FILETIME lpftlast; 
   int ret;
   ret=RegEnumKeyEx(m_hKey,nIndex,T_name,&lpcbname, 
	                NULL,NULL,NULL,&lpftlast); 

   m_dwLastError = GetLastError();

	return T_name;
}


