unit ParInstall2;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls, TntStdCtrls,gnuGetText, drives,
  ComCtrls, TntComCtrls, fWarning, checkOS, parinstall3;

type
  Tparinst2 = class(TForm)
    ButtonStart: TTntButton;
    ButtonCancel: TTntButton;
    TntGroupBox1: TTntGroupBox;
    CBDesktop: TTntCheckBox;
    CBMenu: TTntCheckBox;
    TntGroupBox2: TTntGroupBox;
    LabelChoose: TTntLabel;
    LabelBoot: TTntLabel;
    ListDrives: TTntListView;
    LabelNote: TTntLabel;
    procedure FormShow(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure ListDrivesMouseUp(Sender: TObject; Button: TMouseButton;
      Shift: TShiftState; X, Y: Integer);
    procedure ButtonCancelClick(Sender: TObject);
    procedure ButtonStartClick(Sender: TObject);
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
  LabelChoose.Caption:=pwidechar(_('Choose a drive to install GNU/Linux Kinneret :'));
  LabelNote.Caption:=pwideChar(_('Note: In some cases, a small directory will be created in'+#10#13+
  'drive C:, even if you choose another drive.'));
  LabelBoot.Caption:=pwidechar(_('In order to start Kinneret, you can always boot with the'+#10#13+
  'Kinneret CD, or with a Boot-Floppy. After booting, Kinneret'+#10#13+
  'continues to load from the Hard-Drive automatically.'+#10#13+
  'However, if you don''t want to use the CD at all, You can'+#10#13+
  'choose one or more of the next options (recommended) :'));
  if osis95 then
  begin
    CBDesktop.Checked:=true;
    CBDesktop.Enabled:=true;
    CBMenu.Checked:=false;
    CBMenu.Enabled:=true;

  end else  //is os NT
  begin
    CBDesktop.Checked:=false;
    CBDesktop.Enabled:=false;
    CBMenu.Checked:=true;
    CBMenu.Enabled:=true;
  end;
end;

procedure Tparinst2.FormCreate(Sender: TObject);
var
  f : THandle;
  i : Integer;
  DriveItem :TtntListItem;
begin
  ChosenDrive:='';
  {get KNOPPIX SIZE}
  f:=CreateFile('C:\KNOPPIX\knoppix', GENERIC_READ, FILE_SHARE_READ, nil, OPEN_EXISTING, 0, 0);
  knoppixSize:=GetFileSize(f,nil)/1048576;
  closeHandle(f);
  GetAllFixedDrives(DrivesArray);
  for i:=low(DrivesArray) to high(DrivesArray) do
  begin
      DriveItem := ListDrives.Items.Add;
      DriveItem.Caption := wideformat('%s:  ',
                [DrivesArray[i].DriveLetter]);
      DriveItem.SubItems.Add(wideformat(_('%n MB'),
                [DrivesArray[i].DriveFreeSpace]));
      DriveItem.SubItems.add('');
  end;
  for i:=low(DrivesArray) to high(DrivesArray) do
  begin
    if DrivesArray[i].DriveFreeSpace-KnoppixSize>0 then
    begin
      DriveItem:=ListDrives.Items.Item[i];
      DriveItem.Checked:=true;
      DriveItem.SubItems[1]:=wideformat(_('%n MB'),
                [DrivesArray[DriveItem.index].DriveFreeSpace-knoppixSize]);
      ButtonStart.Enabled:=true;
      ChosenDrive:=DrivesArray[DriveItem.index].DriveLetter;
      break;
    end;
  end;
 // ListDrives.
end;

procedure Tparinst2.ListDrivesMouseUp(Sender: TObject;
  Button: TMouseButton; Shift: TShiftState; X, Y: Integer);
var
  Item: TListItem; 
  HitTest: THitTests;
  i : integer;
begin
  Item := ListDrives.GetItemAt(x, y);
  HitTest := ListDrives.GetHitTestInfoAt(x, y);
  if (Item <> nil) and (HitTest = [htOnStateIcon]) then
  begin 
    if item.Checked=true then
    begin
      if DrivesArray[Item.index].DriveFreeSpace-KnoppixSize>0 then
      begin
        for i:=0 to ListDrives.Items.Count-1 do
          ListDrives.Items.item[i].SubItems[1]:='';
        Item.SubItems[1]:=wideformat(_('%n MB'),
                [DrivesArray[Item.index].DriveFreeSpace-knoppixSize]);
        ChosenDrive:=DrivesArray[Item.index].DriveLetter;
        ButtonStart.Enabled:=true;
      end else
      begin    //Not enough free space
        Item.Checked:=false;
        ButtonStart.Enabled:=false;
        showWarning(ERR, WideFormat(_('Not enough free space on drive %s:'+#10#13+
                                      'Choose another one.'),
            [DrivesArray[Item.Index].DriveLetter]));
      end;
    end else begin   //Uncheck
      Item.SubItems[1]:='';
      ButtonStart.Enabled:=false;
    end;
  end;

end;

procedure Tparinst2.ButtonCancelClick(Sender: TObject);
begin
  close;
end;

procedure Tparinst2.ButtonStartClick(Sender: TObject);
begin
  hide;
  parInst3.createMenu:=CBMenu.Checked;
  parInst3.createShortcut:=CBDesktop.Checked;
  parInst3.showModal;
  show;
end;

end.
