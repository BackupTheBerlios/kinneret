unit ParInstall2;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, FileCtrl, ExtCtrls, TntStdCtrls,gnuGetText;

type
  Tparinst2 = class(TForm)
    ButtonStart: TTntButton;
    ButtonCancel: TTntButton;
    TntGroupBox1: TTntGroupBox;
    TntCheckBox2: TTntCheckBox;
    TntCheckBox1: TTntCheckBox;
    TntGroupBox2: TTntGroupBox;
    DriveComboBox1: TDriveComboBox;
    LabelChoose: TTntLabel;
    LabelFree: TTntLabel;
    LabelBoot: TTntLabel;
    procedure FormShow(Sender: TObject);
    procedure DriveComboBox1Change(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  parinst2: Tparinst2;
  knoppixSize : double;

implementation

{$R *.dfm}

procedure Tparinst2.FormShow(Sender: TObject);
var
  f : File of byte;
begin
  LabelChoose.Caption:=pwidechar(_('Choose destination drive'));
  AssignFile(f, 'd:\knoppix\knoppix');
  knoppixSize:=fileSize(f);
  closeFile(f);
end;

procedure Tparinst2.DriveComboBox1Change(Sender: TObject);
var
  Drive: char;
  DriveNum: byte;
  FreeSpace: double;
begin
  Drive:=DriveComboBox1.drive;
  DriveNum:=ord(Drive)-96;
  FreeSpace:=diskfree(DriveNum);
  if FreeSpace<knoppixSize then LabelFree.Caption:=pwideChar(_('No space in this Drive'))
  else LabelFree.caption:=wideFormat(_('Drive %s:'+#10#13+#10#13+
  'Free space before installation : %n MB'+#10#13+
  'Free space after installation  : %n MB'),[Drive,FreeSpace/1024,FreeSpace/1024-knoppixSize/1024]);
end;

end.
