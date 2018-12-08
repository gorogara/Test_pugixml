// LibMFCUtil.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "LibMFCUtil.h"
#include <algorithm>
#include <regex>
#include <gdiplus.h>
#include "MD5ChecksumDefines.h"
#include "MD5Checksum.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: If this DLL is dynamically linked against the MFC DLLs,
//		any functions exported from this DLL which call into
//		MFC must have the AFX_MANAGE_STATE macro added at the
//		very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

// CLibMFCUtilApp

BEGIN_MESSAGE_MAP(CLibMFCUtilApp, CWinApp)
END_MESSAGE_MAP()


// CLibMFCUtilApp construction

CLibMFCUtilApp::CLibMFCUtilApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


// The one and only CLibMFCUtilApp object

CLibMFCUtilApp theApp;


// CLibMFCUtilApp initialization

BOOL CLibMFCUtilApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}


bool LibMFCUtil::ResizeCImage(CString _pathSrc, CString _pathDst, int _newWidth, int _newHeight)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CImage srcImage;
	HRESULT res = srcImage.Load(_pathSrc);

	if (SUCCEEDED(res))
	{
		// 새 이미지 생성
		CImage dstImage;
		dstImage.CreateEx(_newWidth, _newHeight, 32, BI_RGB, NULL, dstImage.createAlphaChannel);

		// StretchBlt 모드 설정
		SetStretchBltMode(dstImage.GetDC(), COLORONCOLOR);
		dstImage.ReleaseDC();

		// StretchBlt 실행
		srcImage.SetTransparentColor(RGB(255, 255, 255));
		srcImage.StretchBlt(dstImage.GetDC(), 0, 0, _newWidth, _newHeight, SRCCOPY);
		dstImage.ReleaseDC();

		dstImage.Save(_pathDst);

		return true;
	}
	else
	{
		
	}

	return false;
}


bool LibMFCUtil::ResizeCImage(CImage& _src, CImage& _dst, int _newWidth, int _newHeight)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// 새 이미지 생성
	_dst.CreateEx(_newWidth, _newHeight, 32, BI_RGB, NULL, _dst.createAlphaChannel);

	// StretchBlt 모드 설정
	SetStretchBltMode(_dst.GetDC(), COLORONCOLOR);
	_dst.ReleaseDC();

	// StretchBlt 실행
	_src.SetTransparentColor(RGB(255, 255, 255));
	_src.StretchBlt(_dst.GetDC(), 0, 0, _newWidth, _newHeight, SRCCOPY);
	_dst.ReleaseDC();

	return true;
}


bool LibMFCUtil::CheckFileKhoaDmsFormat(CString _path)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CStdioFile file;

	bool bCheck = true;

	if (file.Open(_path, CFile::modeRead))
	{
		CString line;

		while (file.ReadString(line)) {
			bCheck = LibMFCUtil::CheckKhoaDmsFormat(line);
			if (!bCheck)
			{
				return false;
			}
		}
	}
	else
	{
		return false;
	}

	return true;
}

#pragma warning(disable:4129)
bool LibMFCUtil::CheckKhoaDmsFormat(CString _str)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	std::wregex rx(L"^\\s*\\d+\\.?\\d*(\\s*\\-\\s*\\d+\\.?\\d*\\s*){0,2}\\s*[NSns]{1}\\s*\,?\\s*\\d+\\.?\\d*(\\s*\\-\\s*\\d+\\.?\\d*\\s*){0,2}\\s*[EWew]{1}\\s*$");
	std::wstring wstr(_str);

	if (!std::regex_match(wstr, rx))
	{
		return false;
	}

	return true;
}


int LibMFCUtil::CheckKhoaDMSForm(std::wstring str)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	std::wregex rx1(L"^\\d+\\.?\\d*(\\-\\d+\\.?\\d*){0,2}[NSns]{1}\\,?\\d+\\.?\\d*(\\-\\d+\\.?\\d*){0,2}[EWew]{1}$");
	std::wregex rx2(L"^\\d+\\.?\\d*(\\-\\d+\\.?\\d*){0,2}\\,{1}\\d+\\.?\\d*(\\-\\d+\\.?\\d*){0,2}$");

	if (std::regex_match(str, rx1))
	{
		return 1;
	}
	else if (std::regex_match(str, rx2))
	{
		return 2;
	}

	return 0;
}


CString LibMFCUtil::GetClipboardText(HWND hWnd)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	if (!OpenClipboard(hWnd))
	{
		OutputDebugString(_T("Can't open clipboard!\n"));
		return _T("");
	}

	HANDLE hData = GetClipboardData(CF_UNICODETEXT);
	WCHAR* buffer = (WCHAR*)GlobalLock(hData);
	CString text;
	text.Format(_T("%s"), buffer);
	GlobalUnlock(hData);
	CloseClipboard();

	return text;
}


std::wstring LibMFCUtil::EraseAllSpace(std::wstring str)
{
	str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
	return str;
}


char* LibMFCUtil::ConvertWCtoC(wchar_t* str)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	//반환할 char* 변수 선언
	char* pStr = nullptr;

	//입력받은 wchar_t 변수의 길이를 구함
	int strSize = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);

	if (strSize <= 0)
	{
		OutputDebugString(_T("Failed to WideCharToMultiByte()\n"));
		return nullptr;
	}

	//char* 메모리 할당
	pStr = new char[strSize];

	//형 변환 
	WideCharToMultiByte(CP_ACP, 0, str, -1, pStr, strSize, 0, 0);
	return pStr;
}


wchar_t* LibMFCUtil::ConvertCtoWC(char* str)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	//wchar_t형 변수 선언
	wchar_t* pStr = nullptr;
	//멀티 바이트 크기 계산 길이 반환
	int strSize = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, NULL);

	if (strSize <= 0)
	{
		OutputDebugString(_T("Failed to MultiByteToWideChar()\n"));
		return nullptr;
	}

	//wchar_t 메모리 할당
	pStr = new WCHAR[strSize];
	//형 변환
	MultiByteToWideChar(CP_ACP, 0, str, strlen(str) + 1, pStr, strSize);
	return pStr;

}


HTREEITEM LibMFCUtil::FindTreeItem(CTreeCtrl* pTree, HTREEITEM hItem, DWORD data)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	HTREEITEM hItemFind, hItemChild, hItemSibling;
	hItemFind = hItemChild = hItemSibling = NULL;

	if (pTree->GetItemData(hItem) == data)
	{
		hItemFind = hItem;
	}
	else
	{
		hItemChild = pTree->GetChildItem(hItem);
		if (hItemChild)
		{
			hItemFind = FindTreeItem(pTree, hItemChild, data);
		}
	
		hItemSibling = pTree->GetNextSiblingItem(hItem);
		if (!hItemFind && hItemSibling)
		{
			hItemFind = FindTreeItem(pTree, hItemSibling, data);	
		}
	}

	return hItemFind;
}


CString LibMFCUtil::ReplaceExtension(CString path, CString newExtention)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	int indexLastDot = path.ReverseFind(_T('.'));

	int lengthExtension = path.GetLength() - indexLastDot;

	path.Delete(indexLastDot + 1, lengthExtension);

	path.Append(newExtention);

	return path;
}


CString LibMFCUtil::GetExtension(CString path)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString ext = _T("");

	int length = path.GetLength();

	if (length <= 0) 
		return ext;

	int indexOfLastDot = path.ReverseFind('.');
	if (indexOfLastDot >= 0)
	{
		int lengthOfExtension = path.GetLength() - indexOfLastDot - 1;
		ext = path.Right(lengthOfExtension);
		return ext;
	}
	
	return ext;
}


CString LibMFCUtil::GetFileName(CString path)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	CString name = _T("");

	int length = path.GetLength();

	if (length <= 0)
		return name;

	int indexOfLastReverseSlash = path.ReverseFind('\\');
	if (indexOfLastReverseSlash >= 0)
	{
		int indexOfLastDot = path.ReverseFind('.');
		if (indexOfLastDot >= 0)
		{
			return path.Mid(indexOfLastReverseSlash + 1, indexOfLastDot - indexOfLastReverseSlash - 1);
		}
	}

	

	return name;
}


int LibMFCUtil::GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes

	Gdiplus::ImageCodecInfo* pImageCodecInfo = NULL;

	Gdiplus::GetImageEncodersSize(&num, &size);
	if (size == 0)
		return -1;  // Failure

	pImageCodecInfo = (Gdiplus::ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
		return -1;  // Failure

	Gdiplus::GetImageEncoders(num, size, pImageCodecInfo);

	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;  // Success
		}
	}

	free(pImageCodecInfo);
	return -1;  // Failure
}


std::vector<CString> LibMFCUtil::GetFilePathFromFolder(CString folderPath, CString extension)
{
	CFileFind finder;

	BOOL bWorking = finder.FindFile(folderPath + _T("\\*.") + extension);

	std::vector<CString> vecFilePath;
	CString filePath;

	while (bWorking)
	{
		bWorking = finder.FindNextFileW();

		if (finder.IsArchived())
		{
			vecFilePath.push_back(finder.GetFilePath());
		}
	}

	return vecFilePath;
}


CString LibMFCUtil::GetMD5(BYTE* pBuf, UINT nLength)
{
	return CMD5Checksum::GetMD5(pBuf, nLength);
}


CString LibMFCUtil::GetMD5(CFile& File)
{
	return CMD5Checksum::GetMD5(File);
}


CString LibMFCUtil::GetMD5(const CString& strFilePath)
{
	return CMD5Checksum::GetMD5(strFilePath);
}