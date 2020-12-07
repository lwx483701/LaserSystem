#include <afxwin.h>         // MFC core and standard components
#include "FGCamera.h"

class __declspec(dllimport) CImageCaptor
{
public:
	void InitImageCaptor(UINT32HL* cameraSN);
	void ReleaseImageCaptor();

	long GetCurrentChannel();
	BOOL SelectChannel(long lChannel);

	void Display(HWND hwndDisplayArea,CSize sizeDisplayArea);
	void UnDisplay();

	void CaptFullImage(const char *pchFileName);
	void CaptROIImage(const char *pchFileName,int width,int height);

	void SaveBmp();	
	void ReadBmp(CFile* pFile);

	void SetSelectROI(bool bIsSelectROI);
	void SetROIStartPoint(CPoint start);
	void SetROIEndPoint(CPoint end);

	CImageCaptor();
	virtual ~CImageCaptor();

	friend __declspec(dllimport) CImageCaptor& GetImageCaptor();
};

class __declspec(dllexport) CImageBMP						//20190814
{
public:
	void BmpDisplay(unsigned char* pImageBMP,CSize sizeImage,HWND hwndDisplayArea,CSize sizeDisplayArea);	
	void BmpSave(const char* pchFileName,unsigned char* pImageBMP,long imageWidth,int imageHeight);

	CImageBMP();
	virtual ~CImageBMP();

	friend __declspec(dllexport) CImageBMP& GetImageBMP();
};