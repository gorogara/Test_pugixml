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
	extern __declspec(dllexport) bool CheckFileKhoaDmsFormat(CString _path);   // D-M-S, D-M-S ������ ��ǥ �������� �˻�
	extern __declspec(dllexport) bool CheckKhoaDmsFormat(CString _str);        // D-M-S, D-M-S �������� �˻�
	extern __declspec(dllexport) int CheckKhoaDMSForm(std::wstring str);
	extern __declspec(dllexport) CString GetClipboardText(HWND hWnd);
	extern __declspec(dllexport) std::wstring EraseAllSpace(std::wstring str);
	extern __declspec(dllexport) char* ConvertWCtoC(wchar_t* str); // ��ȯ�� ��Ʈ�� ���� ����� ��
	extern __declspec(dllexport) wchar_t* ConvertCtoWC(char* str); // ��ȯ�� ��Ʈ�� ���� ����� ��
	extern __declspec(dllexport) HTREEITEM FindTreeItem(CTreeCtrl* pTree, HTREEITEM hItem, DWORD data);
	extern __declspec(dllexport) int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
	extern __declspec(dllexport) CString GetMD5(BYTE* pBuf, UINT nLength);
	extern __declspec(dllexport) CString GetMD5(CFile& File);
	extern __declspec(dllexport) CString GetMD5(const CString& strFilePath);

	// ������ '.' ���� ���ڿ��� newExtension���� �ٲ۴�
	extern __declspec(dllexport) CString ReplaceExtension(CString path, CString newExtention);

	// ���� ��ο��� Ȯ���ڸ� �����´�(�� : txt, jpg)
	extern __declspec(dllexport) CString GetExtension(CString path);

	// ���� ��ο��� ���� �̸��� �����´�(Ȯ���� ����);
	extern __declspec(dllexport) CString GetFileName(CString path);

	// �������� Ư�� Ȯ���ڸ� ���� ���� ��θ� ���� �����´�
	// extension�� ""�� �־��ָ� ���� �����´�.
	// folderPath�� C:\FolderNameó�� �������� \�� �ʿ� ����.
	extern __declspec(dllexport) std::vector<CString> GetFilePathFromFolder(CString folderPath, CString extension = _T(""));
}