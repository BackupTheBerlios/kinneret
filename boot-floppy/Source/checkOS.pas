UNIT checkOS;

interface

uses
  Windows, SysUtils,fWarning,GnuGetText,ShlObj,ActiveX,comObj;

var
  osis95, osisMe : boolean;

function getOs() : boolean;
function MyDesktopFolder : string;

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

end.

