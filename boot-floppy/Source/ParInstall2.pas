unit ParInstall2;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, FileCtrl, ExtCtrls, TntStdCtrls,gnuGetText,drives,
  ComCtrls, TntComCtrls;

type
  Tparinst2 = class(TForm)
    ButtonStart: TTntButton;
    ButtonCancel: TTntButton;
    TntGroupBox1: TTntGroupBox;
    TntCheckBox2: TTntCheckBox;
    TntCheckBox1: TTntCheckBox;
    TntGroupBox2: TTntGroupBox;
    LabelChoose: TTntLabel;
    LabelBoot: TTntLabel;
    LabelFree: TTntLabel;
    TntListView1: TTntListView;
    procedure FormShow(Sender: TObject);
    procedure DriveComboBox1Change(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  parinst2: Tparinst2;
  knoppixSize : double;
  drivesArray : TDriveInfoArray;

implementation

{$R *.dfm}

procedure Tparinst2.FormShow(Sender: TObject);
begin
  LabelChoose.Caption:=pwidechar(_('Install GNU/Linux Kinneret on drive :'));
end;

procedure Tparinst2.DriveComboBox1Change(Sender: TObject);
var
  Drive: char;
  DriveNum: byte;
  FreeSpace: double;
begin

  DriveNum:=ord(Drive)-96;
  FreeSpace:=diskfree(DriveNum)/1048576;

  if FreeSpace<knoppixSize then
  begin
    LabelFree.Caption:=pwideChar(_('No space in this Drive'));
    buttonStart.Enabled:=false;
  end
  else begin
    LabelFree.caption:=wideFormat(_('Drive %s:'+#10#13+#10#13+
    'Free space before installation : %n MB'+#10#13+
    'Installation size : %n MB'+#10+#13+
    'Free space after installation : %n MB'),
    [Drive,FreeSpace,knoppixSize,FreeSpace-knoppixSize]);
    buttonStart.Enabled:=true;
  end;
end;

procedure Tparinst2.FormCreate(Sender: TObject);
var
  f : THandle;
  i : Integer;
begin
  {get KNOPPIX SIZE}
  f:=CreateFile('D:\KNOPPIX\knoppix', GENERIC_READ, FILE_SHARE_READ, nil, OPEN_EXISTING, 0, 0);
  knoppixSize:=GetFileSize(f,nil)/1024;
  closeHandle(f);
  GetAllFixedDrives(DrivesArray);
  for i:=low(DrivesArray) to high(DrivesArray) do
  begin
//    ComboDrives.AddItem(DrivesArray[i].DriveLetter,nil);
  end;
end;

end.
