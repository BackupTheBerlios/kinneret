UNIT checkOS;

interface

uses
  Windows, SysUtils,fWarning,GnuGetText,ShlObj,ActiveX,comObj;

var
  osis95, osisMe : boolean;

function getOs() : boolean;
function MyDesktopFolder : string;
function GetWindowsDrive: TFileName;
function MyExitWindows(RebootParam: Longword): Boolean;

implementation

function getOs() : boolean;
var
    Version : TOSVersionInfo;
begin
   Version.dwOSVersionInfoSize := Sizeof(Version);
   if GetVersionEx(Version) then begin
      if Version.dwPlatformId = VER_PLATFORM_WIN32_WINDOWS
      then begin
        osis95 := True;
        if (Version.dwMajorVersion = 4)
        and (Version.dwMinorVersion >= 90 )
        then osisMe := True;
      end else begin
        osis95 := False;
        osisMe := False;
      end;
      result := true;
   end
   else
   begin
      ShowWarning(ERR, pWideChar(_('Unable to find Windows version')));
      result := false;
   end;
end;

function MyDesktopFolder : string;
var
 pidl : PItemIDList;
 var Malloc: IMalloc;

begin
 SHGetSpecialFolderLocation(0, CSIDL_DESKTOPDIRECTORY, pidl);
 SetLength(Result, MAX_PATH);
 SHGetPathFromIDList(pidl, pchar(Result));
 SetLength(Result, StrLen(pchar(Result)));
 OLECheck(SHGetMalloc(Malloc));
 if pidl <> nil then Malloc.Free(pidl);
end;

function GetWindowsDrive: TFileName;
var
  WinDir: array [0..MAX_PATH-1] of char;
begin
  SetString(Result, WinDir, GetWindowsDirectory(WinDir, MAX_PATH));
  if Result = '' then
    raise Exception.Create(SysErrorMessage(GetLastError));
  if (copy(result,1,2)<>':\') then result:='C:'
  else result:=copy(result,0,2);
end;

function MyExitWindows(RebootParam: Longword): Boolean;
var
  TTokenHd: THandle;
  TTokenPvg: TTokenPrivileges;
  cbtpPrevious: DWORD;
  rTTokenPvg: TTokenPrivileges;
  pcbtpPreviousRequired: DWORD;
  tpResult: Boolean;
const
  SE_SHUTDOWN_NAME = 'SeShutdownPrivilege';
begin
  if Win32Platform = VER_PLATFORM_WIN32_NT then
  begin
    tpResult := OpenProcessToken(GetCurrentProcess(),
      TOKEN_ADJUST_PRIVILEGES or TOKEN_QUERY,
      TTokenHd);
    if tpResult then
    begin
      tpResult := LookupPrivilegeValue(nil,
                                       SE_SHUTDOWN_NAME,
                                       TTokenPvg.Privileges[0].Luid);
      TTokenPvg.PrivilegeCount := 1;
      TTokenPvg.Privileges[0].Attributes := SE_PRIVILEGE_ENABLED;
      cbtpPrevious := SizeOf(rTTokenPvg);
      pcbtpPreviousRequired := 0;
      if tpResult then
        Windows.AdjustTokenPrivileges(TTokenHd,
                                      False,
                                      TTokenPvg,
                                      cbtpPrevious,
                                      rTTokenPvg,
                                      pcbtpPreviousRequired);
    end;
  end;
  Result := ExitWindowsEx(RebootParam, 0);
end;

end.

