unit ParInstall;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, TNTForms, TntStdCtrls,gnuGetText,fWarning,parInstall2;

type
  Tparinst = class(TTNTForm)
    explanation: TTntLabel;
    YesButton: TTntButton;
    NoButton: TTntButton;
    procedure FormShow(Sender: TObject);
    procedure NoButtonClick(Sender: TObject);
    procedure YesButtonClick(Sender: TObject);
    procedure FormCreate(Sender: TObject);
  private
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
  if (GetCurrentLanguage='he') or (GetCurrentLanguage='ar') then BidiMode:=bdRightToLeft
  else Bidimode:=bdLeftToRight;
  Caption:=pWideChar(_('Hard-Drive Operation Wizard'));
  explanation.Caption:=pWideChar(_('What is "Hard-Drive Operation" ?'+#10#13+#10#13+
  'You can work with GNU/Linux Kinneret from the CD, without '+
  'installing it to the hard-drive.'+#10#13+#10#13+
  '"HD Operation" can copy the system into the Hard-Drive, and '+
  'enable the work from there. This method will improve speed, '+
  'and performance, and also frees the CD driver for other uses '+
  '(like listening to music CD''s).'#10#13+#10#13+
  'For your knoledge, "HD Operation" is not a complete system '+
  'installation, therefore it does not require partitioning and, '+
  'doesn''t allow installation of more progrmas. '+
  'A "HD installation" will be hopefully available in the future.'+#10#13+#10#13+
  'Do you want to make a Hard-Drive Operation ?'));
  YesButton.Caption:=pWideChar(_('Yes'));
  noButton.Caption:=pWideChar(_('Not now, thanks'));
end;

procedure Tparinst.NoButtonClick(Sender: TObject);
begin
  close;
end;

procedure Tparinst.YesButtonClick(Sender: TObject);

begin
  if showWarning(WRN, pWideChar(_('Warning - This installation method is still HIGHLY EXPERIMENTAL.'+#10#13+
  'Continue at your own risk.'))) then
  begin
    hide;
    parinst2.ShowModal;
  end;
  close;
end;

procedure Tparinst.FormCreate(Sender: TObject);
begin
  TranslateProperties (self);      //GNUGETTEXT
end;

end.
