// Confwiz32.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"

#include <commctrl.h>
#include <commdlg.h>

#include <stdio.h>

#include <fstream>
using namespace std;

void Init(HWND hDlg)
{
	// set text
	char szText[] = "יש באפשרותך להפעיל את גנו/לינוקס כנרת מהתקליטור וללא התקנה או הגדרות כלשהן, על-מנת להתרשם מיכולות המערכת.\r\nעל-מנת לאפשר לעבודתך עם גנו/לינוקס כינרת להיות יעילה ככל האפשר, וכן לאפשר לך לשמור הגדרות התאמה-אישית וכן מסמכים לכונן הקשיח, עליך להקדיש מספר דקות מעטות להשלמת פעולת אשף זה.\r\n\r\nיש לבחור את המחיצה שבה יישמרו קבצי ההגדרות והמסמכים שלך. על מחיצה זו תיווצר תת תיקיה בשם kinneret שתכיל שני קבצים, קובץ תיקיית הבית, שם יישמרו העדפותיך האישיות וקבצים מערכת, וקובץ החלפה, לשיפור ביצועי המערכת.\r\n\r\nערכי ברירת המחדל לקבצים אלו אמורים להתאים לכל צרכיו של המשתמש הביתי. אם אין ברשותך מקום פנוי רב בדיסק, ניתן לשנות ערכים אלו, כמו גם במקרה וקיים מקום פנוי רק אותו ברצונך להקצות לכנרת.\r\n\r\nלאחר קביעת הערכים יש ללחוץ על \"בצע\". פעולה זו עלולה לקחת זמן מה. לאחר סיום הפעולה, יש לאתחל את המחשב מחדש, הפעם מדיסק כנרת, על מנת לסיים את תהליך ההתקנה.";
	SetDlgItemText(hDlg, IDC_TEXT, szText);
	// set home to 100
	SetDlgItemInt(hDlg, IDC_HOME, 100, false);

	// set swap to 256
	SetDlgItemInt(hDlg, IDC_SWAP, 256, false);

	// set spins
	SendDlgItemMessage(hDlg, IDC_SPIN_HOME, UDM_SETRANGE, 0, (LPARAM)MAKELONG((short)4096, (short)100));
	SendDlgItemMessage(hDlg, IDC_SPIN_SWAP, UDM_SETRANGE, 0, (LPARAM)MAKELONG((short)4096, (short)0));

	// fill combo with partitions and free space, e.g.
	// C: (1GB Free)
	DWORD dwDrives = GetLogicalDrives();
	DWORD dwMask = 1;
	char chLetter = 'A';

	for (int j = 1 ; j < 32 ; j++, dwMask <<= 1, chLetter++)
	{
		if (dwDrives & dwMask)
		{
			char szBuffer[0xFF];
			ULARGE_INTEGER bigFree;

			sprintf(szBuffer, "%c:\\", chLetter);

			if (GetDriveType(szBuffer) != DRIVE_FIXED) continue;
			GetDiskFreeSpaceEx(szBuffer, &bigFree, 0, 0);

			char exts[][3] = 
			{
				{ 'b',  0,  0 },	// bytes		1024^0
				{ 'K', 'B', 0 },	// kilobytes	1024^1
				{ 'M', 'B', 0 },	// megabytes	1024^2
				{ 'G', 'B', 0 },	// gigabytes	1024^3
				{ 'T', 'B', 0 },	// terabytes	1024^4
				{ 'P', 'B', 0 },	// petabytes	1024^5
				{ 'E', 'B', 0 },	// exabytes		1024^6
			};

			int i = 0;
			while (bigFree.QuadPart > 1024 * 1204)
			{
				bigFree.QuadPart /= 1024;
				i++;
			}

			DWORD dw = (DWORD)bigFree.QuadPart;

			sprintf(szBuffer, "%c:\\ (%.2f%s Free)", chLetter, dw / 1024.0f, exts[i + 1]);
			SendDlgItemMessage(hDlg, IDC_COMBO, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)szBuffer);
		}
	}

	// select the first
	SendDlgItemMessage(hDlg, IDC_COMBO, CB_SETCURSEL, 0, 0);
}

void Do(HWND hDlg)
{
	EnableWindow(GetDlgItem(hDlg, IDC_COMBO), false);
	EnableWindow(GetDlgItem(hDlg, IDC_HOME), false);
	EnableWindow(GetDlgItem(hDlg, IDC_SWAP), false);
	EnableWindow(GetDlgItem(hDlg, IDC_SPIN_HOME), false);
	EnableWindow(GetDlgItem(hDlg, IDC_SPIN_SWAP), false);
	EnableWindow(GetDlgItem(hDlg, IDOK), false);

	SetDlgItemText(hDlg, IDC_STAT, "יוצר תיקייה בשם kinneret בשורש המחיצה...");
	
	char buff[0xFF];
	long l = SendDlgItemMessage(hDlg, IDC_COMBO, CB_GETCURSEL, 0, 0);
	SendDlgItemMessage(hDlg, IDC_COMBO, CB_GETLBTEXT, l, (LPARAM)(LPSTR)buff);
	buff[3] = 0;

	strcat(buff, "kinneret");
	if (CreateDirectory(buff, 0) == 0)
	{
		MessageBox(hDlg, "שגיאה בעת יצירת תיקיה", "שגיאה", MB_ICONERROR);
		PostQuitMessage(-1);
	}

	strcat(buff, "\\.config");

	HANDLE out = CreateFile(buff, GENERIC_WRITE, 0, 0, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, 0);

	if (out == INVALID_HANDLE_VALUE)
	{
		MessageBox(hDlg, "שגיאה בעת יצירת  קובץ", "שגיאה", MB_ICONERROR);
		PostQuitMessage(-1);
	}

	char *mega;

	try
	{
		mega = new char[1024 * 1024];
	}

	catch (bad_alloc)
	{
		MessageBox(hDlg, "שגיאה בעת יצירת  קובץ", "שגיאה", MB_ICONERROR);
		PostQuitMessage(-1);
	}

	memset(mega, 0, 1024 * 1024);

	MSG msg;

	SetTimer(hDlg, 0, 50, 0);

	int size = GetDlgItemInt(hDlg, IDC_HOME, 0, false);
	for (long j = 0 ; j < size ; j++)
	{
		DWORD dw2;
		WriteFile(out, mega, 1024 * 1024, &dw2, 0);

		if (dw2 != 1024 * 1024)
		{
			MessageBox(hDlg, "שגיאה בעת יצירת  קובץ", "שגיאה", MB_ICONERROR);
			PostQuitMessage(-1);
		}

		if (GetMessage(&msg, hDlg, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		char sz[0xFF];
		sprintf(sz, "יוצר קובץ בית... [%d / %d]", j + 1, size);
		SetDlgItemText(hDlg, IDC_STAT, sz);
	}

	CloseHandle(out);

	buff[3] = 0;

	strcat(buff, "kinneret");
	strcat(buff, "\\.swap");

	out = CreateFile(buff, GENERIC_WRITE, 0, 0, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, 0);

	if (out == INVALID_HANDLE_VALUE)
	{
		MessageBox(hDlg, "שגיאה בעת יצירת  קובץ", "שגיאה", MB_ICONERROR);
		PostQuitMessage(-1);
	}

	size = GetDlgItemInt(hDlg, IDC_SWAP, 0, false);
	for (j = 0 ; j < size ; j++)
	{
		DWORD dw2;
		WriteFile(out, mega, 1024 * 1024, &dw2, 0);

		if (dw2 != 1024 * 1024)
		{
			MessageBox(hDlg, "שגיאה בעת יצירת  קובץ", "שגיאה", MB_ICONERROR);
			PostQuitMessage(-1);
		}

		if (GetMessage(&msg, hDlg, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		char sz[0xFF];
		sprintf(sz, "יוצר קובץ החלפה... [%d / %d]", j + 1, size);
		SetDlgItemText(hDlg, IDC_STAT, sz);
	}

	delete mega;

	CloseHandle(out);

	SetDlgItemText(hDlg, IDCANCEL, "יציאה");
}

LONG FAR CALLBACK MainDlgProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		Init(hDlg);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			MessageBox(hDlg, ".תהליך זה עלול לארוך דקות אחדות", "...לידיעתך", MB_OK);
			Do(hDlg);
			MessageBox(hDlg, ".התהליך הסתיים בהצלחה, יש לאתחל את המחשב מהדיסק על מנת להשלים את ההתקנה", "הצלחה", MB_OK);
			break;

		case IDCANCEL:
			PostQuitMessage(0);
			EndDialog(hDlg, IDCANCEL);
			break;
		}
	}

	return FALSE;
}

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	InitCommonControls();
 	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)MainDlgProc);
}
