unit ParInstall;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, TntStdCtrls;

type
  Tparinst = class(TForm)
    TntLabel1: TTntLabel;
    YesButton: TTntButton;
    NoButton: TTntButton;
    procedure FormShow(Sender: TObject);
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
  TntLabel1.Caption:='What is partial installation ?'+#10#13+#10#13+
  'For your knowledge, Kinneret CD contains about 2.3 GB'+#10#13+
  'of installed software, compressed into one CD.'+#10#13+
  'With this installation method, all the data is copied'+#10#13+
  'into the hard-drive, but it does not decompressed.'+#10#13+
  'therefore, you will be able to fully use Kinneret'+#10#13+
  'without the CD in drive, but you still cannot'+#10#13+
  'install anything.'+#10#13+
  'A complete installation method will be (hopefuly)'+#10#13+
  'available in the future.'+#10#13+#10#13+
  'Do you want to make a partial installation ?';
end;

end.
