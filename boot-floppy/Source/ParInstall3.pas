unit ParInstall3;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, TntStdCtrls,gnuGetText, ShellAPI, fWarning,checkos, INIfiles;

type
  TParInst3 = class(TForm)
    LabelWait: TTntLabel;
    ButtonClose: TTntButton;
    procedure FormActivate(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure ButtonCloseClick(Sender: TObject);

  private
function FileOperation (sources, dests: TStrings; op, flags: Integer) : bool;
function filesExist(files : TStrings) : bool;
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

procedure TParInst3.FormActivate(Sender: TObject);
var
  source,destination : TStrings ;
  CDROM : string;
  error : boolean;
  attribute : dword;
  BootIni: TIniFile;

begin
  error:=false;
  cdrom:='..\';
  if (CreateMenu or CreateShortcut) and diskFree(2)<2097152 {2MB} then
  begin
    error:=true;
    labelWait.Caption:=pwidechar(_('Drive C: is full, Unable to copy files.'));
  end;
  source:=TStringList.Create;
  destination:=TStringList.Create;
  // ADDING FILES TO COPY
  source.Add(cdrom+'\KNOPPIX\knoppix');
  destination.add(ChosenDrive+':\KNOPPIX\knoppix');
  source.Add(cdrom+'\KNOPPIX\knoppix.sh');
  destination.add(ChosenDrive+':\KNOPPIX\knoppix.sh');
  if not osis95 and createmenu then
  begin
    source.Add(cdrom+'\boot\menu.lst');
    destination.add('c:\boot\menu.lst');
    source.Add(cdrom+'\boot\ntfsinstall.exe');
    destination.add('c:\boot\ntfsinstall.exe');
    source.Add(cdrom+'\boot\ntfsinstall.txt');
    destination.add('c:\boot\ntfsinstall.txt');
    source.Add(cdrom+'\boot\ntfsinstall.bat');
    destination.add('c:\boot\ntfsinstall.bat');
    source.Add(cdrom+'\boot\stage1');
    destination.add('c:\boot\stage1');
    source.Add(cdrom+'\boot\stage2');
    destination.add('c:\boot\stage2');
    source.Add(cdrom+'\boot\MINIROOT.GZ');
    destination.add('c:\boot\MINIROOT.GZ');
    source.Add(cdrom+'\boot\VMLINUZ');
    destination.add('c:\boot\VMLINUZ');
  end;
  if not error and (not filesExist(source) or
  (FileOperation (source, destination , FO_COPY, FOF_ALLOWUNDO or FOF_NOCONFIRMATION))
  or not filesExist(destination)))
  then begin
    error:=true;
    LabelWait.Caption:=pWideChar(_('Error while copying files.'+#10#13+
    'Unable to continue.'));
    messagebeep(MB_ICONERROR);
    buttonClose.Enabled:=true;
  end;
  if not error and not osis95 and createmenu then
  begin       //Windows NT Create Menu with GRUB
    if not fileExists('c:\boot.ini') or not fileExists('c:\ntldr') then
    begin
      LabelWait.Caption:=pWideChar(_('Error, Can''t find C:\boot.ini'+#10#13+
      'Unable to install Boot-Menu.'));
      messagebeep(MB_ICONERROR);
      error:=true;
    end else begin
      copyFile('c:\boot.ini','c:\boot\boot.ini.old',false);
      ShellExecute(Handle, 'open',PChar('c:\boot\ntfsinstall.bat'),nil, nil, SW_HIDE);
      attribute:=GetFileAttributes(pchar('c:\boot.ini'));
      SetFileAttributes(pchar('c:\boot.ini'), attribute and not FILE_ATTRIBUTE_READONLY	);
      BootIni := TIniFile.Create('c:\boot.ini');
      try
        BootIni.WriteInteger('boot loader', 'timeout' ,10);
        BootIni.WriteString( 'operating systems', 'C:\boot\stage1', '"GNU/Linux Kinneret"' );
      except
        LabelWait.Caption:=pWideChar(_('Error, Can''t modify C:\boot.ini'+#10#13+
        'Unable to install Boot-Menu.'));
        error:=true;
      end;
      BootIni.Free;
      SetFileAttributes(pchar('c:\boot.ini'), attribute);
    end;
  end;
  // Remove old boot-menu windows NT
  if not error and not osis95 and not createmenu and fileExists('c:\boot.ini') then
  begin
    BootIni := TIniFile.Create('c:\boot.ini');
    try
      if (BootIni.ReadString( 'operating systems', 'C:\boot\stage1', '' )<>'') and
      ShowWarning(QST,pWideChar(_('An old Boot-Menu was detected on your system,'+#10#13+
      'Would you want to remove it ?'))) then
      begin
        attribute:=GetFileAttributes(pchar('c:\boot.ini'));
        SetFileAttributes(pchar('c:\boot.ini'), attribute and not FILE_ATTRIBUTE_READONLY	);
        BootIni.DeleteKey( 'operating systems', 'C:\boot\stage1');
        SetFileAttributes(pchar('c:\boot.ini'), attribute);
      end;
    finally
      BootIni.Free;
    end;
  end;
  source.free;
  destination.free;
  if not error then LabelWait.Caption:=pWideChar(_('Installation finished successfully'));
  ButtonClose.Enabled:=true;
end;

procedure TParInst3.FormShow(Sender: TObject);
begin
  LabelWait.Caption:=pWideChar(_(
  'Please wait while installing Kinneret,'+#10#13+
  'this may take several minutes...'));
  ButtonClose.enabled:=false;
end;

procedure TParInst3.ButtonCloseClick(Sender: TObject);
begin
  close;
end;

function TparInst3.FileOperation (sources, dests: TStrings;
                         op, flags: Integer) : bool;
var shf: TSHFileOpStruct;
    s1, s2: string;
    i : integer;
begin
  FillChar (shf, SizeOf (shf), #0);
  s1:='';
  for i:=0 to sources.Count-1 do
  begin
    s1:= s1 + sources[i] + #0;
    s2:= s2 + dests[i] + #0;
  end;
  s1:= s1+#0;
  s2:= s2+#0;
  shf.Wnd:= 0;
  shf.wFunc:= op;
  shf.pFrom:= PCHAR (s1);
  shf.pTo:= PCHAR (s2);
  shf.fFlags:= flags or FOF_MULTIDESTFILES;
  SHFileOperation (shf);
  FileOperation:=shf.fAnyOperationsAborted;
end (*FileOperation*);

function TParInst3.filesExist(files : TStrings) : bool;
var
  i : integer;
begin
  filesExist:=true;
  for i:=0 to files.count-1 do if not fileExists(files[i]) then
  begin
    filesExist:=false;
    break;
  end;
end;

end.
