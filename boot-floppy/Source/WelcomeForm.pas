unit WelcomeForm;

// The contents of this file are subject to the General Public License.
// Version 2 (the "License"); you may not use this file except in compliance
// with the License. You may obtain a copy of the License at http://www.gnu.org/copyleft/gpl.html
//
// Software distributed under the License is distributed on an "AS IS" basis,
// WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for the
// specific language governing rights and limitations under the License.

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls, Menus,gnugettext, About, gifimage,fWarning,
  Buttons, TntStdCtrls, TntForms, Advanced, ParInstall,checkOS;

function MyExitWindows(RebootParam: Longword): Boolean;

type
  TWForm = class(TTntForm)
    WriteButton: TTntButton;
    Button3: TTntButton;
    label1: TTntLabel;
    Label2: TTntLabel;
    Button1: TTntButton;
    Image1: TImage;
    Button2: TTntButton;
    RadioButton1: TTntRadioButton;
    RadioButton2: TTntRadioButton;
    ButtonAdvanced: TTntButton;
    TntButton1: TTntButton;
    procedure Button3Click(Sender: TObject);
    procedure WriteButtonClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure RadioButton2Click(Sender: TObject);
    procedure RadioButton1Click(Sender: TObject);
    procedure refreshlabel2();
    procedure ButtonAdvancedClick(Sender: TObject);
    procedure TntButton1Click(Sender: TObject);
  private
    Retranslator:TExecutable;
  public
    WriteSucceed : Boolean;

    { Public declarations }
  end;

var
  WForm: TWForm;
  Explanation, Explanation2, RebootWarning: pWideChar;

implementation

uses rawwrite;

{$R *.dfm}

procedure TWForm.Button3Click(Sender: TObject);
begin
  close;
end;

procedure TWForm.WriteButtonClick(Sender: TObject);
begin
  WriteButton.Enabled:=false;
  Button3.Enabled:=false;
  MainForm.ShowModal;
  if Writesucceed then Label2.Caption:=PWideChar(_('Floppy has been successfully written.'+#10#13+
  #10#13+'To restart Kinneret:'+#10#13+#10#13+
  'Make sure the Floppy and the CD are still in place,'+#10#13+
  'Close any running programs'+#10#13+
  'And Reboot the computer.'));

end;

procedure TWForm.FormCreate(Sender: TObject);
begin
  if not getOS then exit;
  WriteSucceed:=false;

  Retranslator:=gnugettext.DefaultInstance.TP_CreateRetranslator;
  if (osis95=false) then UseLanguage('he')
  else if (copy(getCurrentLanguage,0,2)='iw') then UseLanguage('iw');
  if (osis95) and (GetCurrentLanguage<>'iw') then
  begin
    RadioButton2.Hide;
    RadioButton1.Hide;
  end;
  if (GetCurrentLanguage='he') or (GetCurrentLanguage='iw') then RadioButton1.Checked:=true
  else RadioButton2.Checked:=true;
  TranslateProperties (self);      //GNUGETTEXT
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


procedure TWForm.Button2Click(Sender: TObject);
begin
  if not ShowWarning(WRN, pWideChar(_('You are going to reboot the computer.'#10#13+
  'In order to prevent data loss, Please close'+#10#13+
  'all running programs. Continune ?'))) then exit;
  MyExitWindows(EWX_REBOOT);
end;

procedure TWForm.Button1Click(Sender: TObject);
begin
  FormAbout.ShowModal;
end;


procedure TWForm.RadioButton2Click(Sender: TObject);
begin

    BiDiMode:=bdLeftToRight;
    Label2.Alignment:=taLeftJustify;
    UseLanguage('en');
    Retranslator.Execute;
    Label2.Repaint;
    refreshlabel2;
end;

procedure TWForm.RadioButton1Click(Sender: TObject);
begin
    if osis95 then
    begin
      UseLanguage('iw');
      BidiMode:=bdRightToLeft
    end
    else
    begin
      UseLanguage('he');
      Label2.Alignment:=taRightJustify;
    end;
    Retranslator.Execute;
    refreshlabel2;
end;

procedure TWForm.refreshlabel2();
begin
    if Writesucceed then Label2.Caption:=PWideChar(_('Floppy has been successfully written.'+#10#13+
    #10#13+'To restart Kinneret:'+#10#13+#10#13+
   'Make sure the Floppy and the CD are still in place,'+#10#13+
   'Close any running programs'+#10#13+
   'And Reboot the computer.'))
  else label2.Caption:=PWideChar(_('Welcome to GNU/Linux "Kinneret"'+
   #10#13+'This program is not an installation Program.'+
   #10#13+'Kinneret doesn''t need to be installed.'+
   #10#13+'To start Kinneret, You should boot the computer'+
   #10#13+'from the Kinneret CD.'+#10#13#10#13+
   'If You can''t or don''t know how to boot from CD,'+#10#13+
   'You can make a bootable floppy here.'));
end;

procedure TWForm.ButtonAdvancedClick(Sender: TObject);
var
  Line: string;
  word: string;
  key: string;
  i: integer;
begin
    try
        FormAdvanced.Strings:=TStringList.Create;
        FormAdvanced.FileName := 'A:\SYSLINUX.CFG';	{ set the file name }
        FormAdvanced.Strings.LoadFromFile(FormAdvanced.Filename); { load from file }
        Line:=FormAdvanced.Strings[1];
    //Seperating Line to words
    for i:=1 to Length(Line) do
    begin
        if line[i]='=' then
        begin
            key:=word;
            word:='';
        end
        else if (line[i]=' ') then
        begin
            if key='' then begin key:=word; word:=''; end;
            if key<>'APPEND' then FormAdvanced.ParamList.InsertRow(key,word,TRUE);
            word:='';
            key:='';
        end
        else word:=word+line[i];
    end;
    if key='' then begin key:=word; word:=''; end;
    FormAdvanced.ParamList.InsertRow(key,word,TRUE);
    FormAdvanced.ShowModal;
  except
    ShowWarning(MSG,pWideChar(_('In order to enter the Advanced options, You must put your boot-floppy'+#10#13+
        '(The floppy you can make here) in drive A:')));
  end;

end;

procedure TWForm.TntButton1Click(Sender: TObject);
begin
  parinst.ShowModal();
end;

end.

