unit ParInstall;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, TntStdCtrls,gnuGetText,fWarning,parInstall2;

type
  Tparinst = class(TForm)
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
  'but you still won''t be able to install new software.'+#10#13+#10#13+
  'A complete installation method will be (hopefuly)'+#10#13+
  'available in the future.'+#10#13+#10#13+
  'Do you want to make a partial installation ?'));
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
