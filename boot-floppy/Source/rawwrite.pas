unit rawwrite;

// The contents of this file are subject to the General Public License.
// Version 2 (the "License"); you may not use this file except in compliance
// with the License. You may obtain a copy of the License at http://www.gnu.org/copyleft/gpl.html
//
// Software distributed under the License is distributed on an "AS IS" basis,
// WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for the
// specific language governing rights and limitations under the License.

interface

uses
  Windows, Messages, SysUtils, Classes, Graphics, Controls, Forms, Dialogs,
  StdCtrls, ComCtrls, ExtCtrls, BlockDev, WelcomeForm, fWarning,
  TntStdCtrls, TntForms;

type
  TMainForm = class(TtntForm)
    ProgressBar1: TProgressBar;
    Labelup: TtntLabel;
    ButtonStart: TtntButton;
    ButtonCancel: TtntButton;
    Labeldown: TtntLabel;
    procedure FormCreate(Sender: TObject);
    procedure WriteButtonClick(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure FormShow(Sender: TObject);
  private
    { Private declarations }

  public
    { Public declarations }
    procedure Wait;
    procedure UnWait;
  end;

var
  MainForm: TMainForm;
   CmdImage : String;

function ReadFile2(hFile: THandle; Buffer : Pointer; nNumberOfBytesToRead: DWORD;
   var lpNumberOfBytesRead: DWORD; lpOverlapped: POverlapped): BOOL; stdcall;
function WriteFile2(hFile: THandle; Buffer : Pointer; nNumberOfBytesToWrite: DWORD;
   var lpNumberOfBytesWritten: DWORD; lpOverlapped: POverlapped): BOOL; stdcall;

implementation

uses DiskIO, ShellAPI,gnugettext;

{$R *.DFM}

function ReadFile2; external kernel32 name 'ReadFile';
function WriteFile2; external kernel32 name 'WriteFile';

procedure TMainForm.Wait;
begin
   Screen.Cursor := crHourGlass;
end;

procedure TMainForm.UnWait;
begin
   Screen.Cursor := crDefault;
end;

procedure TMainForm.FormCreate(Sender: TObject);
begin
    TranslateProperties (self);      //GNUGETTEXT
   // Prevent error messages being displayed by NT
   wForm.WriteSucceed:=False;
   SetErrorMode(SEM_FAILCRITICALERRORS);

   CmdImage := '\boot\boot.img';
end;

procedure TMainForm.WriteButtonClick(Sender: TObject);
var
   h1       : THandle;
   Buffer   : String;
   Read     : DWORD;
   Blocks   : Integer;
   WrittenBlocks  : Integer;
   BlocksCount    : Integer;
   BlocksRemaining : Integer;
   BlockCount     : Integer;
   FileSize  : Integer;

   Device   : TBlockDevice;
   Zero     : _Large_Integer;
   DiskSize : _Large_Integer;
   HadError : Boolean;
   Error : DWORD;
begin
   HadError := False;
   Wait;

   try
         FormWarning.Label1.Caption:=pWideChar(_('Warning - All the data in this floppy will be erased.'+#10#13+
            'Do you want to continune ?'));
         FormWarning.Showmodal;
         if FormWarning.Cancel then exit;
         BlocksCount := 64;
         // make sure that the file exists...
         h1 := CreateFile(PChar(CmdImage), GENERIC_READ, FILE_SHARE_READ, nil, OPEN_EXISTING, 0, 0);
         if h1 <> INVALID_HANDLE_VALUE then
         try
            FileSize := GetFileSize(h1, nil);
            if FileSize = 0 then
            begin
               raise Exception.Create('File ' + CmdImage + ' is 0 bytes long');
            end;
            Blocks := FileSize div 512;
            if (Blocks * 512) < FileSize then
            begin
               Blocks := Blocks + 1;
            end;

            WrittenBlocks := 0;

            SetLength(Buffer, 512 * BlocksCount);
            // open the drive
            if wForm.osIs95 then
            begin
               Device := TWin95Disk.Create;
               TWin95Disk(Device).SetDiskNumber(0);
               TWin95Disk(Device).SetOffset(0);
               // read the 1st sector to settle the disk...
               try
                  Device.ReadPhysicalSector(1, 1, PChar(Buffer));
               except
               end;
               TWin95Disk(Device).SetOffset(0);
            end
            else
            begin
               Zero.Quadpart := 0;
               DiskSize.Quadpart := 512 * 80 * 2 * 18;
               Device := TNTDisk.Create;
               TNTDisk(Device).SetFileName('\\.\A:');
               TNTDisk(Device).SetMode(True);
               TNTDisk(Device).SetPartition(Zero, DiskSize);
            end;
            if Device.Open then
            try
               try
                  LabelDown.Caption:=pWideChar(_('Making disk, Please wait...'));
                  Labelup.Caption:='';
                  ButtonStart.Enabled:=false;
                  ButtonCancel.Enabled:=false;
                  MainForm.ProgressBar1.Position:=0;
                  // write away...
                  while WrittenBlocks < Blocks do
                  begin
                     BlocksRemaining := Blocks - WrittenBlocks;
                     if BlocksRemaining > BlocksCount then
                     begin
                        BlockCount := BlocksCount;
                     end
                     else
                     begin
                        BlockCount := BlocksRemaining;
                     end;

                     ReadFile2(h1, PChar(Buffer), 512 * BlockCount, Read, nil);
                     if Read = 0 then break;
                     Device.WritePhysicalSector(WrittenBlocks, BlockCount, PChar(Buffer));
                     WrittenBlocks := WrittenBlocks + BlockCount;
                     ProgressBar1.Max := Blocks;
                     ProgressBar1.StepBy(BlockCount);
                     Application.ProcessMessages;
                  end;
               except
                  on E : Exception do
                  begin
                     if wForm.osis95=false then begin
                       Error:=GetLastError;
                       case error of
                          21 : LabelDown.Caption:=pWideChar(_('Error - Floppy is not found on drive A:'));
                          19 : LabelDown.Caption:=pWideChar(_('Error - The floppy is write protected'));
                          32 : LabelDown.Caption:=pWideChar(_('Error - The floppy is being used by another process'));
                          27 : LabelDown.Caption:=pWideChar(_('Error - The floppy is defected, Try another floppy'));
                       else
                          LabelDown.Caption:=pWideChar(_('Unknown Error - No''-')+inttostr(Error));
                       end;
                     end else LabelDown.Caption:=pWideChar(_('Error - Unable to write to disk,'+#10#13+
                                        'Please verify that the disk is in drive and not write protected.'));
                     HadError := True;
                 end;
               end;
            finally
               Device.Close;
               if (wForm.osis95=false) then
               begin
                Device.Open;
                Device.Close;
               end;
               Device.Free;
            end
            else
            begin
               LabelDown.Caption:=pWideChar(_('Error - Cannot find Drive A:'));
               HadError := True;
            end;
         finally
            CloseHandle(h1);
         end
      else
         begin
            Error := GetLastError;
            MessageDlg('Error '+ IntToStr(GetLastError) + ' opening image file ''' + CmdImage + ''''#10 + SysErrorMessage(Error) , mtError, [mbOK], 0);
            HadError := True;
         end;

            if HadError=false then
            begin
                wForm.WriteSucceed:=true;
               messagebeep(MB_OK);
               Labelup.Caption:='';
               LabelDown.Caption:=pWideChar(_('The disk was succesfully written.'));
               ButtonCancel.Enabled:=true;
               ButtonCancel.Caption:=pWideChar(_('Close'));
            end
            else
            begin
             messagebeep(MB_ICONASTERISK) ;
             Labelup.Caption:=pWideChar(_('Operation has faild, Please try again.'));
             ButtonStart.Enabled:=true;
             ButtonCancel.Enabled:=true;
            end;
   finally
      UnWait;
   end;
end;

procedure TMainForm.Button3Click(Sender: TObject);
begin
   Close;

end;

procedure TMainForm.FormClose(Sender: TObject; var Action: TCloseAction);
begin
   WForm.WriteButton.Enabled:=true;
   WForm.Button3.Enabled:=true;

end;

procedure TMainForm.FormShow(Sender: TObject);
begin
    if GetCurrentLanguage='iw' then BidiMode:=bdRightToLeft
    else Bidimode:=bdLeftToRight;
    ProgressBar1.Position:=0;
    LabelUp.Caption:=pWideChar(_('Please Insert a floppy to drive A:'));
    LabelDown.Caption:='';
    Caption:=_('Make a bootable floppy');
    ButtonStart.Caption:=pWideChar(_('Start'));
    ButtonCancel.Caption:=PWideChar(_('Cancel'));
    Buttonstart.Enabled:=true;
    ButtonCancel.Enabled:=true;
end;

end.


