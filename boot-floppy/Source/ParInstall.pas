unit ParInstall;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, TntStdCtrls,gnuGetText,fWarning,ShellAPI,parInstall2;

type
  Tparinst = class(TForm)
    explanation: TTntLabel;
    YesButton: TTntButton;
    NoButton: TTntButton;
    procedure FormShow(Sender: TObject);
    procedure NoButtonClick(Sender: TObject);
    procedure YesButtonClick(Sender: TObject);
  private
    function FileOperation (const source, dest: string; op, flags: Integer) : bool;
    { Private declarations }
  public
    { Public declarations }
  end;

var
  parinst: Tparinst;

implementation

{$R *.dfm}

procedure Tparinst.FormShow(Sender: TObject);
begin
  if GetCurrentLanguage='iw' then BidiMode:=bdRightToLeft
  else Bidimode:=bdLeftToRight;
  if GetCurrentLanguage='he' then Explanation.Alignment:=taRightJustify
  else Explanation.Alignment:=taLeftJustify;
  explanation.Caption:=pWideChar(_('What is partial installation ?'+#10#13+#10#13+
  'For your knowledge, Kinneret CD contains about 2.3 GB'+#10#13+
  'of installed software, compressed into one CD.'+#10#13+
  'With this installation method, all the data is copied'+#10#13+
  'into the hard-drive, but it does not decompressed.'+#10#13+
  'therefore, you will be able to fully use Kinneret'+#10#13+
  'without the CD in drive, and it will be much faster,'#10#13+
  'but you still won''t be able to install anything.'+#10#13+#10#13+
  'A complete installation method will be (hopefuly)'+#10#13+
  'available in the future.'+#10#13+#10#13+
  'Do you want to make a partial installation ?'));
end;

procedure Tparinst.NoButtonClick(Sender: TObject);
begin
  close;
end;

procedure Tparinst.YesButtonClick(Sender: TObject);

begin
  if not showWarning(WRN, pWideChar(_('Warning - This installation method is still HIGHLY EXPERIMENTAL'+#10#13+
  'Do you want to continune ?'))) then close;
  hide;
  parinst2.Show;
//  if(FileOperation ('D:\KNOPPIX\knoppix', 'C:\KNOPPIX\knoppix', FO_COPY, FOF_ALLOWUNDO or FOF_NOCONFIRMATION	))
//    then showWarning(ERR,pWideChar(_('Error while copying files')));
  close;
end;

function TparInst.FileOperation (const source, dest: string;
                         op, flags: Integer) : bool;
var shf: TSHFileOpStruct;
    s1, s2: string;
begin
 FillChar (shf, SizeOf (shf), #0);
 s1:= source + #0#0;
 s2:= dest + #0#0;
 shf.Wnd:= Handle;
 shf.wFunc:= op;
 shf.pFrom:= PCHAR (s1);
 shf.pTo:= PCHAR (s2);
 shf.fFlags:= flags;
 SHFileOperation (shf);
 FileOperation:=shf.fAnyOperationsAborted;
end (*FileOperation*);

end.
