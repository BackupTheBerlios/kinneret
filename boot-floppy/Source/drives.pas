UNIT drives;

interface

uses
  Windows, SysUtils;

type TDriveType = (dtUnknown, dtDoesNotExist, dtRemovable, dtFixed,
dtNetwork, dtCDROM, dtRAMDisk);

type TDriveInfo = record
   DriveLetter: string;
   DriveType: TDriveType;
   DriveSize: double;  //size in Kilobytes
   DriveFreeSpace: double; //free space in Kilobytes
end;

type TDriveInfoArray = array of TDriveInfo;

function DriveType(DriveLetter: string): TDriveType;
procedure GetAllDriveTypes(var DriveInfoArray: TDriveInfoArray);
procedure GetAllFixedDrives(var DriveInfoArray: TDriveInfoArray);

implementation
//pass a single character string as the 'DriveLetter' param
function DriveType(DriveLetter: string): TDriveType;
var
  DrvType   : Integer;
begin

  result := dtUnknown;
  DriveLetter := DriveLetter + ':\';

  // get the drive type
  DrvType := GetDriveType(pChar(DriveLetter));

  // set our drive type string accordingly
  case DrvType of
    0                 : result := dtUnknown;
    1                 : result := dtDoesNotExist;
    DRIVE_REMOVABLE  : result := dtRemovable;
    DRIVE_FIXED : result := dtFixed;
    DRIVE_REMOTE : result := dtNetwork;
    DRIVE_CDROM : result := dtCDROM;
    DRIVE_RAMDISK : result := dtRAMDisk;
  end;
end;

//returns a listing of all drives and types on the system
procedure GetAllDriveTypes(var DriveInfoArray: TDriveInfoArray);
var
  x: integer;

begin
  DriveInfoArray := nil;
  SetLength(DriveInfoArray, 0);

  //25 possible drives ... a-z
  for x := Ord('A') to Ord('Z') do
  begin
    if not ( DriveType(Chr(x)) = dtDoesNotExist) then
    begin
      SetLength(DriveInfoArray, Length(DriveInfoArray) + 1);
      DriveInfoArray[Length(DriveInfoArray) - 1].DriveLetter := Chr(x);
      DriveInfoArray[Length(DriveInfoArray) - 1].DriveType :=DriveType(Chr(x));
      DriveInfoArray[Length(DriveInfoArray) - 1].DriveSize := DiskSize(x -64) / 1048576;  //size in MB
      DriveInfoArray[Length(DriveInfoArray) - 1].DriveFreeSpace :=DiskFree(x - 64) / 1048576;  //size in MB
    end;
  end;
end;

procedure GetAllFixedDrives(var DriveInfoArray: TDriveInfoArray);
var
  x: integer;

begin
  DriveInfoArray := nil;
  SetLength(DriveInfoArray, 0);

  //25 possible drives ... a-z
  for x := Ord('A') to Ord('Z') do
  begin
    if ( DriveType(Chr(x)) = dtFixed) then
    begin
      SetLength(DriveInfoArray, Length(DriveInfoArray) + 1);
      DriveInfoArray[Length(DriveInfoArray) - 1].DriveLetter := Chr(x);
      DriveInfoArray[Length(DriveInfoArray) - 1].DriveSize := DiskSize(x -64) / 1048576;  //size in MB
      DriveInfoArray[Length(DriveInfoArray) - 1].DriveFreeSpace :=DiskFree(x - 64) / 1048576;  //size in MB
    end;
  end;
end;
end.

