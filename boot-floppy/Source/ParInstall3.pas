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
begin
  source:= 'c:\CDROM\KNOPPIX\knoppix' ;
  destination:=format('%s:\KNOPPIX\',[ChosenDrive]);
  if not fileexists(source) or
  (FileOperation (source, destination , FO_COPY, FOF_ALLOWUNDO or FOF_NOCONFIRMATION	))
    then showWarning(ERR,pWideChar(_('Error while copying files.'+#10#13+
    'Unable to continue.')));
  source:= 'c:\CDROM\KNOPPIX\knoppix.sh' ;
  if not fileexists(source) or
  (FileOperation (source, destination , FO_COPY, FOF_ALLOWUNDO or FOF_NOCONFIRMATION	))
    then showWarning(ERR,pWideChar(_('Error while copying files.'+#10#13+
    'Unable to continue.')));
end;

procedure TParInst3.FormShow(Sender: TObject);
begin
  LabelWait.Caption:=pWideChar(_(
  'Please wait while installing Kinneret, this may take several menutes...'));
end;

end.
