
{*****************************************************************************}
{                                                                             }
{    Tnt Delphi Unicode Controls                                              }
{      http://home.ccci.org/wolbrink/tnt/delphi_unicode_controls.htm          }
{                                                                             }
{    Copyright (c) 2002, 2003 Troy Wolbrink (troy.wolbrink@ccci.org)          }
{                                                                             }
{*****************************************************************************}

unit TntWindows;

{$INCLUDE Compilers.inc}

interface

uses
  Windows, ShellApi, ShlObj;

// ......... compatibility
{$IFNDEF COMPILER_6_UP} // Delphi 5 compatibility
const
  WS_EX_LAYERED = $00080000;
{$ENDIF}

// ................ ANSI TYPES ................
{TNT-WARN LPSTR}
{TNT-WARN PLPSTR}
{TNT-WARN LPCSTR}
{TNT-WARN LPCTSTR}
{TNT-WARN LPTSTR}

// ........ EnumResourceTypesW, EnumResourceNamesW and EnumResourceLanguagesW are supposed ....
// ........ to work on Win95/98/ME but have caused access violations in testing on Win95 ......
// .. TNT--WARN EnumResourceTypes ..
// .. TNT--WARN EnumResourceTypesA ..
// .. TNT--WARN EnumResourceNames ..
// .. TNT--WARN EnumResourceNamesA ..
// .. TNT--WARN EnumResourceLanguages ..
// .. TNT--WARN EnumResourceLanguagesA ..

// ......... The Unicode form of these functions are supported on Windows 95/98/ME .........
{TNT-WARN ExtTextOut}
{TNT-WARN ExtTextOutA}
{TNT-WARN FindResource}
{TNT-WARN FindResourceA}
{TNT-WARN FindResourceEx}
{TNT-WARN FindResourceExA}
{TNT-WARN GetCharWidth}
{TNT-WARN GetCharWidthA}
{TNT-WARN GetCommandLine}
{TNT-WARN GetCommandLineA}
{TNT-WARN GetTextExtentPoint}
{TNT-WARN GetTextExtentPointA}
{TNT-WARN GetTextExtentPoint32}
{TNT-WARN GetTextExtentPoint32A}
{TNT-WARN lstrcat}
{TNT-WARN lstrcatA}
{TNT-WARN lstrcpy}
{TNT-WARN lstrcpyA}
{TNT-WARN lstrlen}
{TNT-WARN lstrlenA}
{TNT-WARN MessageBox}
{TNT-WARN MessageBoxA}
{TNT-WARN MessageBoxEx}
{TNT-WARN MessageBoxExA}
{TNT-WARN TextOut}
{TNT-WARN TextOutA}

{TNT-WARN LOCALE_USER_DEFAULT} // <-- use GetThreadLocale
{TNT-WARN LOCALE_SYSTEM_DEFAULT} // <-- use GetThreadLocale

{TNT-WARN CreateFile}
{TNT-WARN CreateFileA}
function Tnt_CreateFileW(lpFileName: PWideChar; dwDesiredAccess, dwShareMode: DWORD;
  lpSecurityAttributes: PSecurityAttributes; dwCreationDisposition, dwFlagsAndAttributes: DWORD;
    hTemplateFile: THandle): THandle;

{TNT-WARN FindFirstFile}
{TNT-WARN FindFirstFileA}
function Tnt_FindFirstFileW(lpFileName: PWideChar; var lpFindFileData: TWIN32FindDataW): THandle;

{TNT-WARN FindNextFile}
{TNT-WARN FindNextFileA}
function Tnt_FindNextFileW(hFindFile: THandle; var lpFindFileData: TWIN32FindDataW): BOOL;

{TNT-WARN GetFileAttributes}
{TNT-WARN GetFileAttributesA}
function Tnt_GetFileAttributesW(lpFileName: PWideChar): DWORD;

{TNT-WARN SetFileAttributes}
{TNT-WARN SetFileAttributesA}
function Tnt_SetFileAttributesW(lpFileName: PWideChar; dwFileAttributes: DWORD): BOOL;

{TNT-WARN CreateDirectory}
{TNT-WARN CreateDirectoryA}
function Tnt_CreateDirectoryW(lpPathName: PWideChar;
  lpSecurityAttributes: PSecurityAttributes): BOOL;

{TNT-WARN MoveFile}
{TNT-WARN MoveFileA}
function Tnt_MoveFileW(lpExistingFileName, lpNewFileName: PWideChar): BOOL;

{TNT-WARN CopyFile}
{TNT-WARN CopyFileA}
function Tnt_CopyFileW(lpExistingFileName, lpNewFileName: PWideChar; bFailIfExists: BOOL): BOOL;

{TNT-WARN DeleteFile}
{TNT-WARN DeleteFileA}
function Tnt_DeleteFileW(lpFileName: PWideChar): BOOL;

{TNT-WARN DrawText}
{TNT-WARN DrawTextA}
function Tnt_DrawTextW(hDC: HDC; lpString: PWideChar; nCount: Integer;
  var lpRect: TRect; uFormat: UINT): Integer;

{TNT-WARN GetDiskFreeSpace}
{TNT-WARN GetDiskFreeSpaceA}
function Tnt_GetDiskFreeSpaceW(lpRootPathName: PWideChar; var lpSectorsPerCluster,
  lpBytesPerSector, lpNumberOfFreeClusters, lpTotalNumberOfClusters: DWORD): BOOL;

{TNT-WARN GetModuleFileName}
{TNT-WARN GetModuleFileNameA}
function Tnt_GetModuleFileNameW(hModule: HINST; lpFilename: PWideChar; nSize: DWORD): DWORD;

{TNT-WARN GetTempPath}
{TNT-WARN GetTempPathA}
function Tnt_GetTempPathW(nBufferLength: DWORD; lpBuffer: PWideChar): DWORD;

{TNT-WARN GetWindowsDirectory}
{TNT-WARN GetWindowsDirectoryA}
function Tnt_GetWindowsDirectoryW(lpBuffer: PWideChar; uSize: UINT): UINT;

{TNT-WARN GetSystemDirectory}
{TNT-WARN GetSystemDirectoryA}
function Tnt_GetSystemDirectoryW(lpBuffer: PWideChar; uSize: UINT): UINT;

{TNT-WARN GetComputerName}
{TNT-WARN GetComputerNameA}
function Tnt_GetComputerNameW(lpBuffer: PWideChar; var nSize: DWORD): BOOL;

{TNT-WARN ShellExecute}
{TNT-WARN ShellExecuteA}
function Tnt_ShellExecuteW(hWnd: HWND; Operation, FileName, Parameters,
  Directory: PWideChar; ShowCmd: Integer): HINST;

{TNT-WARN LoadLibraryEx}
{TNT-WARN LoadLibraryExA}
function Tnt_LoadLibraryExW(lpLibFileName: PWideChar; hFile: THandle; dwFlags: DWORD): HMODULE;

{TNT-WARN CreateProcess}
{TNT-WARN CreateProcessA}
function Tnt_CreateProcessW(lpApplicationName: PWideChar; lpCommandLine: PWideChar;
  lpProcessAttributes, lpThreadAttributes: PSecurityAttributes;
    bInheritHandles: BOOL; dwCreationFlags: DWORD; lpEnvironment: Pointer;
      lpCurrentDirectory: PWideChar; const lpStartupInfo: TStartupInfo;
        var lpProcessInformation: TProcessInformation): BOOL;

{TNT-WARN CompareString}
{TNT-WARN CompareStringA}
function Tnt_CompareStringW(Locale: LCID; dwCmpFlags: DWORD; lpString1: PWideChar;
  cchCount1: Integer; lpString2: PWideChar; cchCount2: Integer): Integer;

{TNT-WARN CharUpper}
{TNT-WARN CharUpperA}
function Tnt_CharUpperW(lpsz: PWideChar): PWideChar;

{TNT-WARN CharUpperBuff}
{TNT-WARN CharUpperBuffA}
function Tnt_CharUpperBuffW(lpsz: PWideChar; cchLength: DWORD): DWORD;

{TNT-WARN CharLower}
{TNT-WARN CharLowerA}
function Tnt_CharLowerW(lpsz: PWideChar): PWideChar;

{TNT-WARN CharLowerBuff}
{TNT-WARN CharLowerBuffA}
function Tnt_CharLowerBuffW(lpsz: PWideChar; cchLength: DWORD): DWORD;

{TNT-WARN GetStringTypeEx}
{TNT-WARN GetStringTypeExA}
function Tnt_GetStringTypeExW(Locale: LCID; dwInfoType: DWORD;
  lpSrcStr: PWideChar; cchSrc: Integer; var lpCharType): BOOL; stdcall;

{TNT-WARN GetFileVersionInfoSize}
{TNT-WARN GetFileVersionInfoSizeA}
function Tnt_GetFileVersionInfoSizeW(lptstrFilename: PWideChar; var lpdwHandle: DWORD): DWORD;

{TNT-WARN GetFileVersionInfo}
{TNT-WARN GetFileVersionInfoA}
function Tnt_GetFileVersionInfoW(lptstrFilename: PWideChar; dwHandle, dwLen: DWORD;
  lpData: Pointer): BOOL;

const
  VQV_FIXEDFILEINFO = '\';
  VQV_VARFILEINFO_TRANSLATION = '\VarFileInfo\Translation';
  VQV_STRINGFILEINFO = '\StringFileInfo';

  VER_COMMENTS         = 'Comments';
  VER_INTERNALNAME     = 'InternalName';
  VER_PRODUCTNAME      = 'ProductName';
  VER_COMPANYNAME      = 'CompanyName';
  VER_LEGALCOPYRIGHT   = 'LegalCopyright';
  VER_PRODUCTVERSION   = 'ProductVersion';
  VER_FILEDESCRIPTION  = 'FileDescription';
  VER_LEGALTRADEMARKS  = 'LegalTrademarks';
  VER_PRIVATEBUILD     = 'PrivateBuild';
  VER_FILEVERSION      = 'FileVersion';
  VER_ORIGINALFILENAME = 'OriginalFilename';
  VER_SPECIALBUILD     = 'SpecialBuild';

{TNT-WARN VerQueryValue}
{TNT-WARN VerQueryValueA}
function Tnt_VerQueryValueW(pBlock: Pointer; lpSubBlock: PWideChar;
  var lplpBuffer: Pointer; var puLen: UINT): BOOL;

type
  TSHNameMappingHeaderA = record
   cNumOfMappings: Cardinal;
   lpNM: PSHNAMEMAPPINGA;
  end;
  PSHNameMappingHeaderA = ^TSHNameMappingHeaderA;

  TSHNameMappingHeaderW = record
   cNumOfMappings: Cardinal;
   lpNM: PSHNAMEMAPPINGW;
  end;
  PSHNameMappingHeaderW = ^TSHNameMappingHeaderW;

{TNT-WARN SHFileOperation}
{TNT-WARN SHFileOperationA}
{TNT-WARN SHFileOperationW} // <-- no stub on early Windows 95
function Tnt_SHFileOperationW(var lpFileOp: TSHFileOpStructW): Integer;

{TNT-WARN SHFreeNameMappings}
procedure Tnt_SHFreeNameMappings(hNameMappings: THandle);

{TNT-WARN SHBrowseForFolder}
{TNT-WARN SHBrowseForFolderA}
{TNT-WARN SHBrowseForFolderW} // <-- no stub on early Windows 95
function Tnt_SHBrowseForFolderW(var lpbi: TBrowseInfoW): PItemIDList;

{TNT-WARN SHGetPathFromIDList}
{TNT-WARN SHGetPathFromIDListA}
{TNT-WARN SHGetPathFromIDListW} // <-- no stub on early Windows 95
function Tnt_SHGetPathFromIDListW(pidl: PItemIDList; pszPath: PWideChar): BOOL;

// ......... introduced .........
function Tnt_Is_IntResource(ResStr: LPCWSTR): Boolean;

function LANGIDFROMLCID(lcid: LCID): WORD;
function MAKELANGID(usPrimaryLanguage, usSubLanguage: WORD): WORD;
function MAKELCID(wLanguageID: WORD; wSortID: WORD = SORT_DEFAULT): LCID;
function PRIMARYLANGID(lgid: WORD): WORD;
function SORTIDFROMLCID(lcid: LCID): WORD;
function SUBLANGID(lgid: WORD): WORD;

implementation

uses
  SysUtils, TntSysUtils;

function _PAnsiCharWithNil(const S: AnsiString): PAnsiChar;
begin
  if S = '' then
    Result := nil {Win9x needs nil for some parameters instead of empty strings}
  else
    Result := PAnsiChar(S);
end;

function _PWideCharWithNil(const S: WideString): PWideChar;
begin
  if S = '' then
    Result := nil {Win9x needs nil for some parameters instead of empty strings}
  else
    Result := PWideChar(S);
end;

function _WStr(lpString: PWideChar; cchCount: Integer): WideString;
begin
  if cchCount = -1 then
    Result := lpString
  else
    Result := Copy(WideString(lpString), 1, cchCount);
end;

function _IsWideCharMappableToAnsi(const WC: WideChar): Boolean;
var
  UsedDefaultChar: BOOL;
begin
  WideCharToMultiByte(DefaultUserCodePage, 0, PWideChar(@WC), 1, nil, 0, nil, @UsedDefaultChar);
  Result := not UsedDefaultChar;
end;

procedure _MakeWideWin32FindData(var WideFindData: TWIN32FindDataW; AnsiFindData: TWIN32FindDataA);
begin
  CopyMemory(@WideFindData, @AnsiFindData,
    Integer(@WideFindData.cFileName) - Integer(@WideFindData));
  StrPCopyW{TNT-ALLOW StrPCopyW}(WideFindData.cFileName, AnsiFindData.cFileName);
  StrPCopyW{TNT-ALLOW StrPCopyW}(WideFindData.cAlternateFileName, AnsiFindData.cAlternateFileName);
end;

function Tnt_CreateFileW(lpFileName: PWideChar; dwDesiredAccess, dwShareMode: DWORD;
  lpSecurityAttributes: PSecurityAttributes; dwCreationDisposition, dwFlagsAndAttributes: DWORD;
    hTemplateFile: THandle): THandle;
begin
  if Win32PlatformIsUnicode then
    Result := CreateFileW(lpFileName, dwDesiredAccess, dwShareMode,
      lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile)
  else
    Result := CreateFileA{TNT-ALLOW CreateFileA}(PAnsiChar(AnsiString(lpFileName)), dwDesiredAccess, dwShareMode,
      lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile)
end;

function Tnt_FindFirstFileW(lpFileName: PWideChar; var lpFindFileData: TWIN32FindDataW): THandle;
var
  Ansi_lpFindFileData: TWIN32FindDataA;
begin
  if Win32PlatformIsUnicode then
    Result := FindFirstFileW(lpFileName, lpFindFileData)
  else begin
    Result := FindFirstFileA{TNT-ALLOW FindFirstFileA}(PAnsiChar(AnsiString(lpFileName)),
      Ansi_lpFindFileData);
    if Result <> INVALID_HANDLE_VALUE then
      _MakeWideWin32FindData(lpFindFileData, Ansi_lpFindFileData);
  end;
end;

function Tnt_FindNextFileW(hFindFile: THandle; var lpFindFileData: TWIN32FindDataW): BOOL;
var
  Ansi_lpFindFileData: TWIN32FindDataA;
begin
  if Win32PlatformIsUnicode then
    Result := FindNextFileW(hFindFile, lpFindFileData)
  else begin
    Result := FindNextFileA{TNT-ALLOW FindNextFileA}(hFindFile, Ansi_lpFindFileData);
    if Result then
      _MakeWideWin32FindData(lpFindFileData, Ansi_lpFindFileData);
  end;
end;

function Tnt_GetFileAttributesW(lpFileName: PWideChar): DWORD;
begin
  if Win32PlatformIsUnicode then
    Result := GetFileAttributesW(lpFileName)
  else
    Result := GetFileAttributesA{TNT-ALLOW GetFileAttributesA}(PAnsiChar(AnsiString(lpFileName)));
end;

function Tnt_SetFileAttributesW(lpFileName: PWideChar; dwFileAttributes: DWORD): BOOL;
begin
  if Win32PlatformIsUnicode then
    Result := SetFileAttributesW(lpFileName, dwFileAttributes)
  else
    Result := SetFileAttributesA{TNT-ALLOW SetFileAttributesA}(PAnsiChar(AnsiString(lpFileName)), dwFileAttributes);
end;

function Tnt_CreateDirectoryW(lpPathName: PWideChar;
  lpSecurityAttributes: PSecurityAttributes): BOOL;
begin
  if Win32PlatformIsUnicode then
    Result := CreateDirectoryW(lpPathName, lpSecurityAttributes)
  else
    Result := CreateDirectoryA{TNT-ALLOW CreateDirectoryA}(PAnsiChar(AnsiString(lpPathName)), lpSecurityAttributes);
end;

function Tnt_MoveFileW(lpExistingFileName, lpNewFileName: PWideChar): BOOL;
begin
  if Win32PlatformIsUnicode then
    Result := MoveFileW(lpExistingFileName, lpNewFileName)
  else
    Result := MoveFileA{TNT-ALLOW MoveFileA}(PAnsiChar(AnsiString(lpExistingFileName)), PAnsiChar(AnsiString(lpNewFileName)));
end;

function Tnt_CopyFileW(lpExistingFileName, lpNewFileName: PWideChar; bFailIfExists: BOOL): BOOL;
begin
  if Win32PlatformIsUnicode then
    Result := CopyFileW(lpExistingFileName, lpNewFileName, bFailIfExists)
  else
    Result := CopyFileA{TNT-ALLOW CopyFileA}(PAnsiChar(AnsiString(lpExistingFileName)),
      PAnsiChar(AnsiString(lpNewFileName)), bFailIfExists);
end;

function Tnt_DeleteFileW(lpFileName: PWideChar): BOOL;
begin
  if Win32PlatformIsUnicode then
    Result := DeleteFileW(lpFileName)
  else
    Result := DeleteFileA{TNT-ALLOW DeleteFileA}(PAnsiChar(AnsiString(lpFileName)));
end;

function Tnt_DrawTextW(hDC: HDC; lpString: PWideChar; nCount: Integer;
  var lpRect: TRect; uFormat: UINT): Integer;
begin
  if Win32PlatformIsUnicode then
    Result := DrawTextW(hDC, lpString, nCount, lpRect, uFormat)
  else
    Result := DrawTextA{TNT-ALLOW DrawTextA}(hDC,
      PAnsiChar(AnsiString(_WStr(lpString, nCount))), -1, lpRect, uFormat);
end;

function Tnt_GetDiskFreeSpaceW(lpRootPathName: PWideChar; var lpSectorsPerCluster,
  lpBytesPerSector, lpNumberOfFreeClusters, lpTotalNumberOfClusters: DWORD): BOOL;
begin
  if Win32PlatformIsUnicode then
    Result := GetDiskFreeSpaceW(lpRootPathName,
      lpSectorsPerCluster, lpBytesPerSector, lpNumberOfFreeClusters, lpTotalNumberOfClusters)
  else
    Result := GetDiskFreeSpaceA{TNT-ALLOW GetDiskFreeSpaceA}(PAnsiChar(AnsiString(lpRootPathName)),
      lpSectorsPerCluster, lpBytesPerSector, lpNumberOfFreeClusters, lpTotalNumberOfClusters)
end;

function Tnt_GetModuleFileNameW(hModule: HINST; lpFilename: PWideChar; nSize: DWORD): DWORD;
var
  AnsiBuff: AnsiString;
begin
  if Win32PlatformIsUnicode then
    Result := GetModuleFileNameW(hModule, lpFilename, nSize)
  else begin
    SetLength(AnsiBuff, MAX_PATH);
    SetLength(AnsiBuff, GetModuleFileNameA{TNT-ALLOW GetModuleFileNameA}(hModule, PAnsiChar(AnsiBuff), Length(AnsiBuff)));
    if Length(AnsiBuff) = 0 then
      Result := 0
    else begin
      StrPLCopyW{TNT-ALLOW StrPLCopyW}(lpFileName, AnsiBuff, nSize - 1);
      Result := StrLenW(lpFileName);
    end;
  end;
end;

function Tnt_GetTempPathW(nBufferLength: DWORD; lpBuffer: PWideChar): DWORD;
var
  AnsiBuff: AnsiString;
begin
  if Win32PlatformIsUnicode then
    Result := GetTempPathW(nBufferLength, lpBuffer)
  else begin
    SetLength(AnsiBuff, MAX_PATH);
    SetLength(AnsiBuff, GetTempPathA{TNT-ALLOW GetTempPathA}(Length(AnsiBuff), PAnsiChar(AnsiBuff)));
    if Length(AnsiBuff) = 0 then
      Result := 0
    else begin
      StrPLCopyW{TNT-ALLOW StrPLCopyW}(lpBuffer, AnsiBuff, nBufferLength - 1);
      Result := StrLenW(lpBuffer);
    end;
  end;
end;

function Tnt_GetWindowsDirectoryW(lpBuffer: PWideChar; uSize: UINT): UINT;
var
  AnsiBuff: AnsiString;
begin
  if Win32PlatformIsUnicode then
    Result := GetWindowsDirectoryW(lpBuffer, uSize)
  else begin
    SetLength(AnsiBuff, MAX_PATH);
    SetLength(AnsiBuff, GetWindowsDirectoryA{TNT-ALLOW GetWindowsDirectoryA}(PAnsiChar(AnsiBuff), Length(AnsiBuff)));
    if Length(AnsiBuff) = 0 then
      Result := 0
    else begin
      StrPLCopyW{TNT-ALLOW StrPLCopyW}(lpBuffer, AnsiBuff, uSize - 1);
      Result := StrLenW(lpBuffer);
    end;
  end;
end;

function Tnt_GetSystemDirectoryW(lpBuffer: PWideChar; uSize: UINT): UINT;
var
  AnsiBuff: AnsiString;
begin
  if Win32PlatformIsUnicode then
    Result := GetSystemDirectoryW(lpBuffer, uSize)
  else begin
    SetLength(AnsiBuff, MAX_PATH);
    SetLength(AnsiBuff, GetSystemDirectoryA{TNT-ALLOW GetSystemDirectoryA}(PAnsiChar(AnsiBuff), Length(AnsiBuff)));
    if Length(AnsiBuff) = 0 then
      Result := 0
    else begin
      StrPLCopyW{TNT-ALLOW StrPLCopyW}(lpBuffer, AnsiBuff, uSize - 1);
      Result := StrLenW(lpBuffer);
    end;
  end;
end;


function Tnt_GetComputerNameW(lpBuffer: PWideChar; var nSize: DWORD): BOOL;
var
  AnsiBuff: AnsiString;
  AnsiBuffLen: DWORD;
begin
  if Win32PlatformIsUnicode then
    Result := GetComputerNameW(lpBuffer, nSize)
  else begin
    SetLength(AnsiBuff, MAX_COMPUTERNAME_LENGTH + 1);
    AnsiBuffLen := Length(AnsiBuff);
    Result := GetComputerNameA{TNT-ALLOW GetComputerNameA}(PAnsiChar(AnsiBuff), AnsiBuffLen);
    if Result then begin
      SetLength(AnsiBuff, AnsiBuffLen);
      if Length(AnsiBuff) = 0 then
        nSize := 0
      else begin
        StrPLCopyW{TNT-ALLOW StrPLCopyW}(lpBuffer, AnsiBuff, nSize - 1);
        nSize := StrLenW(lpBuffer);
      end;
    end;
  end;
end;

function Tnt_ShellExecuteW(hWnd: HWND; Operation, FileName, Parameters,
  Directory: PWideChar; ShowCmd: Integer): HINST;
begin
  if Win32PlatformIsUnicode then
    Result := ShellExecuteW(hWnd, _PWideCharWithNil(WideString(Operation)),
      FileName, Parameters,
        Directory, ShowCmd)
  else begin
    Result := ShellExecuteA{TNT-ALLOW ShellExecuteA}(hWnd, _PAnsiCharWithNil(AnsiString(Operation)),
      _PAnsiCharWithNil(AnsiString(FileName)), _PAnsiCharWithNil(AnsiString(Parameters)),
        _PAnsiCharWithNil(AnsiString(Directory)), ShowCmd)
  end;
end;

function Tnt_LoadLibraryExW(lpLibFileName: PWideChar; hFile: THandle; dwFlags: DWORD): HMODULE;
begin
  if Win32PlatformIsUnicode then
    Result := LoadLibraryExW(lpLibFileName, hFile, dwFlags)
  else
    Result := LoadLibraryExA{TNT-ALLOW LoadLibraryExA}(PAnsiChar(AnsiString(lpLibFileName)), hFile, dwFlags);
end;

function Tnt_CreateProcessW(lpApplicationName: PWideChar; lpCommandLine: PWideChar;
  lpProcessAttributes, lpThreadAttributes: PSecurityAttributes;
    bInheritHandles: BOOL; dwCreationFlags: DWORD; lpEnvironment: Pointer;
      lpCurrentDirectory: PWideChar; const lpStartupInfo: TStartupInfo;
        var lpProcessInformation: TProcessInformation): BOOL;
begin
  if Win32PlatformIsUnicode then begin
    Result := CreateProcessW(lpApplicationName, lpCommandLine,
      lpProcessAttributes, lpThreadAttributes, bInheritHandles, dwCreationFlags, lpEnvironment,
        lpCurrentDirectory, lpStartupInfo, lpProcessInformation)
  end else begin
    Result := CreateProcessA{TNT-ALLOW CreateProcessA}(_PAnsiCharWithNil(AnsiString(lpApplicationName)),
      _PAnsiCharWithNil(AnsiString(lpCommandLine)),
        lpProcessAttributes, lpThreadAttributes, bInheritHandles, dwCreationFlags, lpEnvironment,
          _PAnsiCharWithNil(AnsiString(lpCurrentDirectory)), lpStartupInfo, lpProcessInformation);
  end;
end;

function Tnt_CompareStringW(Locale: LCID; dwCmpFlags: DWORD; lpString1: PWideChar;
  cchCount1: Integer; lpString2: PWideChar; cchCount2: Integer): Integer;
var
  WideStr1, WideStr2: WideString;
  AnsiStr1, AnsiStr2: AnsiString;
begin
  if Win32PlatformIsUnicode then
    Result := CompareStringW(Locale, dwCmpFlags, lpString1, cchCount1, lpString2, cchCount2)
  else begin
    WideStr1 := _WStr(lpString1, cchCount1);
    WideStr1 := _WStr(lpString1, cchCount1);
    if (dwCmpFlags = 0) then begin
      // binary comparison
      if WideStr1 < WideStr2 then
        Result := 1
      else if WideStr1 = WideStr2 then
        Result := 2
      else
        Result := 3;
    end else begin
      AnsiStr1 := WideStr1;
      AnsiStr2 := WideStr2;
      Result := CompareStringA{TNT-ALLOW CompareStringA}(Locale, dwCmpFlags,
        PAnsiChar(AnsiStr1), -1, PAnsiChar(AnsiStr2), -1);
    end;
  end;
end;

function Tnt_CharUpperW(lpsz: PWideChar): PWideChar;
var
  AStr: AnsiString;
  WStr: WideString;
begin
  if Win32PlatformIsUnicode then
    Result := CharUpperW(lpsz)
  else begin
    if HiWord(Cardinal(lpsz)) = 0 then begin
      // literal char mode
      Result := lpsz;
      if _IsWideCharMappableToAnsi(WideChar(lpsz)) then begin
        AStr := WideChar(lpsz); // single character may be more than one byte
        CharUpperA{TNT-ALLOW CharUpperA}(PAnsiChar(AStr));
        WStr := AStr; // should always be single wide char
        if Length(WStr) = 1 then
          Result := PWideChar(WStr[1]);
      end
    end else begin
      // null-terminated string mode
      Result := lpsz;
      while lpsz^ <> #0 do begin
        lpsz^ := WideChar(Tnt_CharUpperW(PWideChar(lpsz^)));
        Inc(lpsz);
      end;
    end;
  end;
end;

function Tnt_CharUpperBuffW(lpsz: PWideChar; cchLength: DWORD): DWORD;
var
  i: integer;
begin
  if Win32PlatformIsUnicode then
    Result := CharUpperBuffW(lpsz, cchLength)
  else begin
    Result := cchLength;
    for i := 1 to cchLength do begin
      lpsz^ := WideChar(Tnt_CharUpperW(PWideChar(lpsz^)));
      Inc(lpsz);
    end;
  end;
end;

function Tnt_CharLowerW(lpsz: PWideChar): PWideChar;
var
  AStr: AnsiString;
  WStr: WideString;
begin
  if Win32PlatformIsUnicode then
    Result := CharLowerW(lpsz)
  else begin
    if HiWord(Cardinal(lpsz)) = 0 then begin
      // literal char mode
      Result := lpsz;
      if _IsWideCharMappableToAnsi(WideChar(lpsz)) then begin
        AStr := WideChar(lpsz); // single character may be more than one byte
        CharLowerA{TNT-ALLOW CharLowerA}(PAnsiChar(AStr));
        WStr := AStr; // should always be single wide char
        if Length(WStr) = 1 then
          Result := PWideChar(WStr[1]);
      end
    end else begin
      // null-terminated string mode
      Result := lpsz;
      while lpsz^ <> #0 do begin
        lpsz^ := WideChar(Tnt_CharLowerW(PWideChar(lpsz^)));
        Inc(lpsz);
      end;
    end;
  end;
end;

function Tnt_CharLowerBuffW(lpsz: PWideChar; cchLength: DWORD): DWORD;
var
  i: integer;
begin
  if Win32PlatformIsUnicode then
    Result := CharLowerBuffW(lpsz, cchLength)
  else begin
    Result := cchLength;
    for i := 1 to cchLength do begin
      lpsz^ := WideChar(Tnt_CharLowerW(PWideChar(lpsz^)));
      Inc(lpsz);
    end;
  end;
end;

function Tnt_GetStringTypeExW(Locale: LCID; dwInfoType: DWORD;
  lpSrcStr: PWideChar; cchSrc: Integer; var lpCharType): BOOL; stdcall;
var
  AStr: AnsiString;
begin
  if Win32PlatformIsUnicode then
    Result := GetStringTypeExW(Locale, dwInfoType, lpSrcStr, cchSrc, lpCharType)
  else begin
    AStr := _WStr(lpSrcStr, cchSrc);
    Result := GetStringTypeExA{TNT-ALLOW GetStringTypeExA}(Locale, dwInfoType,
      PAnsiChar(AStr), -1, lpCharType);
  end;
end;

function Tnt_GetFileVersionInfoSizeW(lptstrFilename: PWideChar; var lpdwHandle: DWORD): DWORD;
begin
  if Win32PlatformIsUnicode then
    Result := GetFileVersionInfoSizeW(lptstrFilename, lpdwHandle)
  else
    Result := GetFileVersionInfoSizeA{TNT-ALLOW GetFileVersionInfoSizeA}(PAnsiChar(AnsiString(lptstrFilename)), lpdwHandle);
end;

function Tnt_GetFileVersionInfoW(lptstrFilename: PWideChar; dwHandle, dwLen: DWORD;
  lpData: Pointer): BOOL;
begin
  if Win32PlatformIsUnicode then
    Result := GetFileVersionInfoW(lptstrFilename, dwHandle, dwLen, lpData)
  else
    Result := GetFileVersionInfoA{TNT-ALLOW GetFileVersionInfoA}(PAnsiChar(AnsiString(lptstrFilename)), dwHandle, dwLen, lpData);
end;

var
  Last_VerQueryValue_String: WideString;

function Tnt_VerQueryValueW(pBlock: Pointer; lpSubBlock: PWideChar;
  var lplpBuffer: Pointer; var puLen: UINT): BOOL;
var
  AnsiBuff: AnsiString;
begin
  if Win32PlatformIsUnicode then
    Result := VerQueryValueW(pBlock, lpSubBlock, lplpBuffer, puLen)
  else begin
    Result := VerQueryValueA{TNT-ALLOW VerQueryValueA}(pBlock, PAnsiChar(AnsiString(lpSubBlock)), lplpBuffer, puLen);
    if WideTextPos(VQV_STRINGFILEINFO, lpSubBlock) <> 1 then
    else begin
      {  /StringFileInfo, convert ansi result to unicode }
      SetString(AnsiBuff, PAnsiChar(lplpBuffer), puLen);
      Last_VerQueryValue_String := AnsiBuff;
      lplpBuffer := PWideChar(Last_VerQueryValue_String);
      puLen := Length(Last_VerQueryValue_String);
    end;
  end;
end;

//---------------------------------------------------------------------------------------
//  Wide functions from Shell32.dll should be loaded dynamically (no stub on early Win95)
//---------------------------------------------------------------------------------------

type
  TSHFileOperationW = function(var lpFileOp: TSHFileOpStructW): Integer; stdcall;
  TSHBrowseForFolderW = function(var lpbi: TBrowseInfoW): PItemIDList; stdcall;
  TSHGetPathFromIDListW = function(pidl: PItemIDList; pszPath: PWideChar): BOOL; stdcall;

var
  Safe_SHFileOperationW: TSHFileOperationW = nil;
  Safe_SHBrowseForFolderW: TSHBrowseForFolderW = nil;
  Safe_SHGetPathFromIDListW: TSHGetPathFromIDListW = nil;

var Shell32DLL: HModule = 0;

procedure LoadWideShell32Procs;
begin
  if Shell32DLL = 0 then begin
    Shell32DLL := WinCheckH(LoadLibrary('shell32.dll'));
    Safe_SHFileOperationW := WinCheckP(GetProcAddress(Shell32DLL, 'SHFileOperationW'));
    Safe_SHBrowseForFolderW := WinCheckP(GetProcAddress(Shell32DLL, 'SHBrowseForFolderW'));
    Safe_SHGetPathFromIDListW := WinCheckP(GetProcAddress(Shell32DLL, 'SHGetPathFromIDListW'));
  end;
end;

function Tnt_SHFileOperationW(var lpFileOp: TSHFileOpStructW): Integer;
var
  AnsiFileOp: TSHFileOpStructA;
  MapCount: Integer;
  PAnsiMap: PSHNameMappingA;
  PWideMap: PSHNameMappingW;
  OldPath: WideString;
  NewPath: WideString;
  i: integer;
begin
  if Win32PlatformIsUnicode then begin
    LoadWideShell32Procs;
    Result := Safe_SHFileOperationW(lpFileOp);
  end else begin
    AnsiFileOp := TSHFileOpStructA(lpFileOp);
    // convert PChar -> PWideChar
    AnsiFileOp.pFrom := PAnsiChar(AnsiString(ExtractStringArrayStr(lpFileOp.pFrom)));
    AnsiFileOp.pTo := PAnsiChar(AnsiString(ExtractStringArrayStr(lpFileOp.pTo)));
    AnsiFileOp.lpszProgressTitle := PAnsiChar(AnsiString(lpFileOp.lpszProgressTitle));
    Result := SHFileOperationA{TNT-ALLOW SHFileOperationA}(AnsiFileOp);
    // return struct results
    lpFileOp.fAnyOperationsAborted := AnsiFileOp.fAnyOperationsAborted;
    lpFileOp.hNameMappings := nil;
    if (AnsiFileOp.hNameMappings <> nil)
    and ((FOF_WANTMAPPINGHANDLE and AnsiFileOp.fFlags) <> 0) then begin
      // alloc mem
      MapCount := PSHNameMappingHeaderA(AnsiFileOp.hNameMappings).cNumOfMappings;
      lpFileOp.hNameMappings :=
        AllocMem(SizeOf({hNameMappings}Cardinal) + SizeOf(TSHNameMappingW) * MapCount);
      PSHNameMappingHeaderW(lpFileOp.hNameMappings).cNumOfMappings := MapCount;
      // init pointers
      PAnsiMap := PSHNameMappingHeaderA(AnsiFileOp.hNameMappings).lpNM;
      PWideMap := PSHNameMappingHeaderW(lpFileOp.hNameMappings).lpNM;
      for i := 1 to MapCount do begin
        // old path
        OldPath := Copy(PAnsiMap.pszOldPath, 1, PAnsiMap.cchOldPath);
        PWideMap.pszOldPath := StrNewW(PWideChar(OldPath));
        PWideMap.cchOldPath := StrLenW(PWideMap.pszOldPath);
        // new path
        NewPath := Copy(PAnsiMap.pszNewPath, 1, PAnsiMap.cchNewPath);
        PWideMap.pszNewPath := StrNewW(PWideChar(NewPath));
        PWideMap.cchNewPath := StrLenW(PWideMap.pszNewPath);
        // next record
        Inc(PAnsiMap);
        Inc(PWideMap);
      end;
    end;
  end;
end;

procedure Tnt_SHFreeNameMappings(hNameMappings: THandle);
var
  i: integer;
  MapCount: Integer;
  PWideMap: PSHNameMappingW;
begin
  if Win32PlatformIsUnicode then
    SHFreeNameMappings{TNT-ALLOW SHFreeNameMappings}(hNameMappings)
  else begin
    // free strings
    MapCount := PSHNameMappingHeaderW(hNameMappings).cNumOfMappings;
    PWideMap := PSHNameMappingHeaderW(hNameMappings).lpNM;
    for i := 1 to MapCount do begin
      StrDisposeW(PWideMap.pszOldPath);
      StrDisposeW(PWideMap.pszNewPath);
      Inc(PWideMap);
    end;
    // free struct
    FreeMem(Pointer(hNameMappings));
  end;
end;

function Tnt_SHBrowseForFolderW(var lpbi: TBrowseInfoW): PItemIDList;
var
  AnsiInfo: TBrowseInfoA;
begin
  if Win32PlatformIsUnicode then begin
    LoadWideShell32Procs;
    Result := Safe_SHBrowseForFolderW(lpbi);
  end else begin
    AnsiInfo := TBrowseInfoA(lpbi);
    AnsiInfo.pszDisplayName := PAnsiChar(AnsiString(lpbi.pszDisplayName));
    AnsiInfo.lpszTitle := PAnsiChar(AnsiString(lpbi.lpszTitle));
    Result := SHBrowseForFolderA{TNT-ALLOW SHBrowseForFolderA}(AnsiInfo);
  end;
end;

function Tnt_SHGetPathFromIDListW(pidl: PItemIDList; pszPath: PWideChar): BOOL;
var
  AnsiPath: AnsiString;
begin
  if Win32PlatformIsUnicode then begin
    LoadWideShell32Procs;
    Result := Safe_SHGetPathFromIDListW(pidl, pszPath);
  end else begin
    SetLength(AnsiPath, MAX_PATH);
    Result := SHGetPathFromIDListA{TNT-ALLOW SHGetPathFromIDListA}(pidl, PAnsiChar(AnsiPath));
    if Result then
      StrPCopyW{TNT-ALLOW StrPCopyW}(pszPath, PAnsiChar(AnsiPath))
  end;
end;

function Tnt_Is_IntResource(ResStr: LPCWSTR): Boolean;
begin
  Result := HiWord(Cardinal(ResStr)) = 0;
end;

function LANGIDFROMLCID(lcid: LCID): WORD;
begin
  Result := LoWord(lcid);
end;

function MAKELANGID(usPrimaryLanguage, usSubLanguage: WORD): WORD;
begin
  Result := (usSubLanguage shl 10) or usPrimaryLanguage;
end;

function MAKELCID(wLanguageID: WORD; wSortID: WORD = SORT_DEFAULT): LCID;
begin
  Result := MakeLong(wLanguageID, wSortID);
end;

function PRIMARYLANGID(lgid: WORD): WORD;
begin
  Result := lgid and $03FF;
end;

function SORTIDFROMLCID(lcid: LCID): WORD;
begin
  Result := HiWord(lcid);
end;

function SUBLANGID(lgid: WORD): WORD;
begin
  Result := lgid shr 10;
end;

initialization

finalization
  if Shell32DLL <> 0 then
    FreeLibrary(Shell32DLL);

end.
