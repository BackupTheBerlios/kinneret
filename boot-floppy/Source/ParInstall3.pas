unit ParInstall3;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, TntStdCtrls,gnuGetText, ShellAPI, fWarning;

type
  TParInst3 = class(TForm)
    LabelWait: TTntLabel;
    procedure FormActivate(Sender: TObject);
    procedure FormShow(Sender: TObject);
  private
    function FileOperation (const source, dest: string; op, flags: Integer) : bool;
    { Private declarations }
  public
    createMenu : bool;
    createShortcut : bool;
    { Public declarations }
  end;

var
  ParInst3: TParInst3;
  chosenDrive : string;

implementation

{$R *.dfm}

function TparInst3.FileOperation (const source, dest: string;
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

procedure TParInst3.FormActivate(Sender: TObject);
var
  destination : string;
  source : string ;
  file1,file2 : string;

begin
  source:= 'c:\CDROM\KNOPPIX\';
  file1:='knoppix' ;
  file2:= 'knoppix.sh' ;
  destination:=format('%s:\KNOPPIX\',[ChosenDrive]);
  if not fileexists(source+file1)
  or not fileexists(source+file2)
  or (FileOperation (source+file1, destination , FO_COPY, FOF_ALLOWUNDO or FOF_NOCONFIRMATION	))
  or (FileOperation (source+file2, destination , FO_COPY, FOF_ALLOWUNDO or FOF_NOCONFIRMATION	))
  then begin
    showWarning(ERR,pWideChar(_('Error while copying files.'+#10#13+
    'Unable to continue.')));
  end else
    ShellExecute(Handle, 'open', PChar('command.com'), PChar('/c copy file1.txt file2.txt'), nil, SW_SHOW);
end;

procedure TParInst3.FormShow(Sender: TObject);
begin
  LabelWait.Caption:=pWideChar(_(
  'Please wait while installing Kinneret, this may take several menutes...'));
end;

end.
