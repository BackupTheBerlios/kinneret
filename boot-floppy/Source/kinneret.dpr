program kinneret;

// The contents of this file are subject to the General Public License.
// Version 2 (the "License"); you may not use this file except in compliance
// with the License. You may obtain a copy of the License at http://www.gnu.org/copyleft/gpl.html
//
// Software distributed under the License is distributed on an "AS IS" basis,
// WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for the
// specific language governing rights and limitations under the License.

uses
  Forms,
  rawwrite in 'rawwrite.pas' {MainForm},
  DiskIO in 'DiskIO.pas',
  QTThunkU in 'QTThunkU.pas',
  BlockDev in 'BlockDev.pas',
  WelcomeForm in 'WelcomeForm.pas' {WForm},
  WinIOCTL in 'WinIOCTL.pas',
  BinFile in 'BinFile.pas',
  About in 'About.pas' {FormAbout},
  fWarning in 'fWarning.pas' {FormWarning},
  gnugettext in 'gnugettext.pas',
  Advanced in 'Advanced.pas' {FormAdvanced},
  ParInstall in 'ParInstall.pas' {parinst},
  ParInstall2 in 'ParInstall2.pas' {parinst2},
  drives in 'drives.pas';

{$R *.RES}

begin
  Application.Initialize;
  Application.Title := 'Kinneret Boot Floppy';
  Application.CreateForm(TWForm, WForm);
  Application.CreateForm(TMainForm, MainForm);
  Application.CreateForm(TFormAbout, FormAbout);
  Application.CreateForm(TFormWarning, FormWarning);
  Application.CreateForm(TFormAdvanced, FormAdvanced);
  Application.CreateForm(Tparinst, parinst);
  Application.CreateForm(Tparinst2, parinst2);
  Application.Run;
end.
