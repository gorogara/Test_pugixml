// LibMFCUtil.h : main header file for the LibMFCUtil DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include <vector>
#include <atlimage.h>
#include "StringTokenizer.h"
#include "Stopwatch.h"

#define DELETE_NULL(x) { delete[] x; x = nullptr; }

// CLibMFCUtilApp
// See LibMFCUtil.cpp for the implementation of this class
//

class CLibMFCUtilApp : public CWinApp
{
public:
	CLibMFCUtilApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

namespace LibMFCUtil
{
	extern __declspec(dllexport) bool ResizeCImage(CString _pathSrc, CString _pathDst, int _newWidth, int _newHeight);
	extern __declspec(dllexport) bool ResizeCImage(CImage& _src, CImage& _dst, int _newWidth, int _newHeight);
	extern __declspec(dllexport) bool CheckFileKhoaDmsFormat(CString _path);   // D-M-S, D-M-S 형태의 좌표 파일인지 검사
	extern __declspec(dllexport) bool CheckKhoaDmsFormat(CString _str);        // D-M-S, D-M-S 형태인지 검사
	extern __declspec(dllexport) int CheckKhoaDMSForm(std::wstring str);
	extern __declspec(dllexport) CString GetClipboardText(HWND hWnd);
	extern __declspec(dllexport) std::wstring EraseAllSpace(std::wstring str);
	extern __declspec(dllexport) char* ConvertWCtoC(wchar_t* str); // 반환된 스트링 해제 해줘야 함
	extern __declspec(dllexport) wchar_t* ConvertCtoWC(char* str); // 반환된 스트링 해제 해줘야 함
	extern __declspec(dllexport) HTREEITEM FindTreeItem(CTreeCtrl* pTree, HTREEITEM hItem, DWORD data);
	extern __declspec(dllexport) int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
	extern __declspec(dllexport) CString GetMD5(BYTE* pBuf, UINT nLength);
	extern __declspec(dllexport) CString GetMD5(CFile& File);
	extern __declspec(dllexport) CString GetMD5(const CString& strFilePath);

	// 마지막 '.' 뒤의 문자열을 newExtension으로 바꾼다
	extern __declspec(dllexport) CString ReplaceExtension(CString path, CString newExtention);

	// 파일 경로에서 확장자만 가져온다(예 : txt, jpg)
	extern __declspec(dllexport) CString GetExtension(CString path);

	// 파일 경로에서 파일 이름만 가져온다(확장자 제외);
	extern __declspec(dllexport) CString GetFileName(CString path);

	// 폴더에서 특정 확장자를 가진 파일 경로를 전부 가져온다
	// extension에 ""을 넣어주면 전부 가져온다.
	// folderPath는 C:\FolderName처럼 마지막에 \는 필요 없다.
	extern __declspec(dllexport) std::vector<CString> GetFilePathFromFolder(CString folderPath, CString extension = _T(""));
}