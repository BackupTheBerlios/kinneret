unit ParInstall3;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, TntStdCtrls, TNTForms, gnuGetText, ShellAPI, fWarning,checkos,
  INIfiles, strUtils;

type
  textpos = (Start, Anywhere);
  TParInst3 = class(TtntForm)
    LabelWait: TTntLabel;
    ButtonClose: TTntButton;
    procedure FormActivate(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure ButtonCloseClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);

  private
    configsys,autoexec : TStrings ;
    function FileOperation (sources, dests: TStrings; op, flags: Integer) : bool;
    function filesExist(files : TStrings) : bool;
    procedure addMenu;
    procedure removeMenu;
    function install9xMenu : boolean;
    { Private declarations }
  public
    createMenu : bool;
    createShortcut : bool;
    { Public declarations }
  end;

  function SearchFor(item : string; list : TStrings; position : textpos) : integer;

var
  ParInst3: TParInst3;
  chosenDrive : string;

implementation

uses welcomeForm;
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
    source.Add(cdrom+'\boot\grubinstall.exe.nt');
    destination.add('c:\boot\grubinstall.exe');
    source.Add(cdrom+'\boot\reinstall.bat.nt');
    destination.add('c:\boot\reinstall.bat');
    source.Add(cdrom+'\boot\stage1');
    destination.add('c:\boot\stage1');
    source.Add(cdrom+'\boot\stage2');
    destination.add('c:\boot\stage2');
    source.Add(cdrom+'\boot\MINIROOT.GZ');
    destination.add('c:\boot\MINIROOT.GZ');
    source.Add(cdrom+'\boot\VMLINUZ');
    destination.add('c:\boot\VMLINUZ');
  end;
  if osis95 and (createmenu or createShortcut) then
  begin
    source.Add(cdrom+'\boot\loadlin.exe.9x');
    destination.add('c:\boot\loadlin.exe');
    source.Add(cdrom+'\boot\Kinneret.bat.9x');
    destination.add('c:\boot\Kinneret.bat');
    source.Add(cdrom+'\boot\loadlin.par');
    destination.add('c:\boot\loadlin.par');
    source.Add(cdrom+'\boot\Kinneret.pif.9x');
    destination.add('c:\boot\Kinneret.pif');
    if createShortcut then begin
      source.Add(cdrom+'\boot\Kinneret.pif.9x');
      destination.add(MyDesktopFolder+'\Kinneret.pif');
    end;

  end;

  //not enough space in C: (rare)
  if (CreateMenu or CreateShortcut) and (diskFree(3)<2097152) {2MB} then
  begin
    error:=true;
    ShowWarning(ERR,(_('Drive C: is full, Unable to copy files.'+#10#13+
    'Free up some space, or try again without Boot Options.')));
  end;
  //Copying all files
  if not error and (not filesExist(source) or
  (FileOperation (source, destination , FO_COPY, FOF_ALLOWUNDO or FOF_NOCONFIRMATION))
  or not filesExist(destination))
  then begin
    error:=true;
    ShowWarning(ERR,pWideChar(_('Error while copying files.')));
    buttonClose.Enabled:=true;
  end;
  source.free;
  destination.free;

  if not error and not osis95 and createmenu then
  begin       //Windows NT Create Menu with GRUB
    if not fileExists('c:\boot.ini') or not fileExists('c:\ntldr') then
    begin
      ShowWarning(ERR,pWideChar(_('Error, Can''t find C:\boot.ini'+#10#13+
      'Unable to install Boot-Menu.')));
      error:=true;
    end else begin
      copyFile('c:\boot.ini','c:\boot\boot.ini.old',false);
      ShellExecute(Handle, 'open',PChar('c:\boot\reinstall.bat'),nil, nil, SW_HIDE);
      attribute:=GetFileAttributes(pchar('c:\boot.ini'));
      SetFileAttributes(pchar('c:\boot.ini'), attribute and not FILE_ATTRIBUTE_READONLY	);
      BootIni := TIniFile.Create('c:\boot.ini');
      try
        BootIni.WriteInteger('boot loader', 'timeout' ,10);
        BootIni.WriteString( 'operating systems', 'C:\boot\stage1', '"GNU/Linux Kinneret"' );
      except
        ShowWarning(ERR,pWideChar(_('Error, Can''t modify C:\boot.ini'+#10#13+
        'Unable to install Boot-Menu.')));
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
      'Would you like to remove it ?'))) then
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
  if not error and osis95 and createMenu then error:=install9xMenu
  else if not error and osis95 and not createMenu then removeMenu;

  if not error then
  begin
    LabelWait.Caption:=pWideChar(_('Installation finished successfully.'));
    wForm.Condition:=parInst_made;
  end
  else LabelWait.Caption:=pWideChar(_('Installation failed.'));
  ButtonClose.Enabled:=true;
end;

procedure TParInst3.FormShow(Sender: TObject);
begin
  if (GetCurrentLanguage='he') or (GetCurrentLanguage='ar') then BidiMode:=bdRightToLeft
    else Bidimode:=bdLeftToRight;
  LabelWait.Caption:=pWideChar(_('Please wait while installing Kinneret,'+#10#13+
  'this may take several minutes...'));
  Caption:=pWideChar(_('Installing Kinneret'));
  ButtonClose.enabled:=false;
  ButtonClose.Caption:=pWideChar(_('Close'));
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

function SearchFor(item : string; list : TStrings; position : textpos) : integer;
var
  i : integer;
begin
  result:=-1;
  for i:=0 to list.Count-1 do
  begin
    if ((position=Anywhere) and AnsiContainsStr(AnsiLowerCase(list[i]),AnsiLowerCase(item)))
    or ((position=Start) and (AnsiStartsStr(AnsiLowerCase(list[i]),AnsiLowerCase(item)))) then
    begin
      result:=i;
      break;
    end;
  end;
end;

procedure TparInst3.addMenu;
begin
  with configsys do
  begin
    insert(0,';**Kinneret edit start**, don''t edit this line.');
    insert(1,'[menu]');
    insert(2,'menuitem=windows, Windows');
    insert(3,'menuitem=kinneret, GNU/Linux Kinneret');
    insert(4,'menucolor=15,1');
    insert(5,'menudefault=Windows, 10');
    insert(6,'[kinneret]');
    insert(7,'[windows]');
    insert(8,';**Kinneret edit end**, don''t edit this line.');
  end;
  with autoexec do
  begin
    insert(0,'@rem **Kinneret edit start**, don''t edit this line.');
    insert(1,'@echo off');
    insert(2,'goto %config%');
    insert(3,':kinneret');
    insert(4,'echo Starting Kinneret...');
    insert(5,'call c:\boot\Kinneret.bat');
    insert(6,':windows');
    insert(7,'echo Starting Windows...');
    insert(8,'rem **Kinneret edit end**, don''t edit this line.');
  end;
end;

function TparInst3.install9xMenu : boolean;
var
  configsysFile,autoexecFile : string;
  confstart,confend,autostart,autoend,i : integer;
  toAdd : boolean;
begin
  toAdd:=false;
  result:=true; //Assume there is an error
  configsysFile := getWindowsDrive+'\config.sys';
  autoexecFile := getWindowsDrive+'\autoexec.bat';
  try
    configsys := TStringList.Create;
    autoexec := TStringList.Create;
    if fileexists(configsysfile) then configsys.LoadFromFile(configsysFile);
    if fileexists(autoexecFile) then autoexec.LoadFromFile(autoexecFile);
    confstart:=searchfor('**kinneret edit start**',configsys,anywhere);
    confend:=searchfor('**kinneret edit end**',configsys,anywhere);
    autostart:=searchfor('**kinneret edit start**',autoexec,anywhere);
    autoend:=searchfor('**kinneret edit end**',autoexec,anywhere);
    if ((confstart=-1) and (confend=-1) and (autostart=-1) and (autoend=-1)) and
      (searchfor('[menu]',configsys,anywhere)>-1) then
    begin
      ShowWarning(ERR,pWideChar(_('Another Boot-Menu which is not related to Kinneret was'+#10#13+
      'detected on your system.'+#10#13+'Kinneret boot-menu cannot be installed.')));
    end
    else if ((confstart>-1) and (confend>confstart) and (autostart>-1) and (autoend>autostart)) then
    begin
      result:=false;
      if ShowWarning(QST,pWideChar(_('There is an old Kinneret Boot-Menu installed,'+#10#13+
        'would you like to overwrite it ?'))) then
      begin
        for i:=confstart to confend do configsys.delete(0);
        for i:=autostart to autoend do autoexec.delete(0);
        toAdd:=true;
      end;
    end
    else if ((confstart>-1) or (confend>-1) or (autostart>-1) or (autoend>-1)) then
    begin
      ShowWarning(ERR,pWideChar(_('It seems that there is an old Kinneret Boot-Menu installed,'+#10#13+
      'but it is corrupted.')));
    end
    // There is nothing in config.sys or autoexec.bat, just install normally.
    else toAdd:=true;
    if (toAdd=true) and (searchfor('[menu]',configsys,anywhere)=-1) then
    begin
      addMenu;
      //make a backup and save changes
      if fileExists(configsysFile) then copyFile(pchar(configsysFile),'c:\boot\config.bak',True);
      if fileExists(autoexecFile) then copyFile(pchar(autoexecFile),'c:\boot\autoexec.bak',True);
      configsys.SaveToFile(configsysFile);
      autoexec.SaveToFile(autoexecFile);
      result:=false;      //result is not error
    end else if toAdd=true then
    begin
      ShowWarning(ERR,(_('There is an unknown problem with the Boot-Menu.')));
      result:=true;
    end;
  finally
    configsys.free;
    autoexec.Free;
  end;
end;

procedure TparInst3.removeMenu;
var
  configsysFile,autoexecFile : string;
  confstart,confend,autostart,autoend,i : integer;
begin
  configsysFile := getWindowsDrive+'\config.sys';
  autoexecFile := getWindowsDrive+'\autoexec.bat';
  try
    configsys := TStringList.Create;
    autoexec := TStringList.Create;
    if fileexists(configsysfile) then configsys.LoadFromFile(configsysFile);
    if fileexists(autoexecFile) then autoexec.LoadFromFile(autoexecFile);
    confstart:=searchfor('**kinneret edit start**',configsys,anywhere);
    confend:=searchfor('**kinneret edit end**',configsys,anywhere);
    autostart:=searchfor('**kinneret edit start**',autoexec,anywhere);
    autoend:=searchfor('**kinneret edit end**',autoexec,anywhere);
    if ((confstart>-1) and (confend>confstart) and (autostart>-1) and (autoend>autostart)) then
    begin
      if ShowWarning(QST,pWideChar(_('There is an old Kinneret Boot-Menu installed,'+#10#13+
        'Do you want to remove it ?'))) then
      begin
        for i:=confstart to confend do configsys.delete(0);
        for i:=autostart to autoend do autoexec.delete(0);
        configsys.SaveToFile(configsysFile);
        autoexec.SaveToFile(autoexecFile);
      end;
    end;
  finally
    configsys.free;
    autoexec.free;
  end;
end;

procedure TParInst3.FormCreate(Sender: TObject);
begin
  TranslateProperties (self);      //GNUGETTEXT
end;

end.
