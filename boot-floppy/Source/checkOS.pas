UNIT checkOS;

interface

uses
  Windows, SysUtils;

function osis95(): boolean;

implementation

function osis95(): boolean ;
var
    Version : TOSVersionInfo;
begin
   Version.dwOSVersionInfoSize := Sizeof(Version);
   if GetVersionEx(Version) then
   begin
      if Version.dwPlatformId = VER_PLATFORM_WIN32_WINDOWS then
      begin
         osis95 := True;
      end
      else
      begin
         osis95 := False;
      end;
   end
   else
   begin
//      MessageDlg(pWideChar(_('Error - Cannot find Windows version')), mtError, [mbOK], 0);
   end;
end;

end.

