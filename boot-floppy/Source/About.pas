unit About;
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
  Dialogs, StdCtrls,gnugettext,TntForms,TntStdCtrls;

type
  TFormAbout = class(TtntForm)
    Memo1: TtntMemo;
    Button1: TtntButton;
    procedure Button1Click(Sender: TObject);
    procedure FormCreate(Sender: TObject);
    procedure FormShow(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  version: string;
  date: string;
  email: string;
  end;

var
  FormAbout: TFormAbout;

implementation

{$R *.dfm}

procedure TFormAbout.Button1Click(Sender: TObject);
begin
  FormAbout.Close;
end;

procedure TFormAbout.FormCreate(Sender: TObject);
begin
  TranslateProperties (self);      //GNUGETTEXT
  date:='24/3/04';
  version:='0.7.3';
  email:='nirro@linux-kinneret.org';
end;

procedure TFormAbout.FormShow(Sender: TObject);
begin
    if (GetCurrentLanguage='he') or (GetCurrentLanguage='ar') then BidiMode:=bdRightToLeft
    else Bidimode:=bdLeftToRight;
    memo1.Text:=wideFormat(_('Kinneret''s Boot Floppy Maker,'+#10#13+
    'And "HD operation" wizard.'+#10#13+#10#13+
    'Version: %s,'+#10#13+
    'Date: %s,'+#10#13+
    'Written by: Nir Misgav.'+#10#13+
    'Email: %s'+#10#13+
    'All rights reserved to'+#10#13+
    'GNU/Linux Kinneret,'+#10#13+
    'http://www.linux-kinneret.org'+#10#13+
    'Lincense: GPL.'+#10#13+#10#13+
    'First version (0.1) was'+#10#13+
    'based on: RawWriteWin-0.7,'+#10#13+
    'Written by: John Newbigin,'+#10#13+#10#13+
    'Graphics made with: TGIFImage,'+#10#13+
    'Author: Andres Melander,'+#10#13+
    'Ported to D7 by: Finn Tolderlund.'+#10#13+
    'License: See TGIFImage.hlp,'+#10#13+
    'under section : License.'+#10#13#10#13+
    'Unicode Libraries from:'+#10#13+
    'Tnt Unicode Controls,'+#10#13+
    'by Tnt Software Products.'+#10#13+
    'License: Unspecific open source,'+#10#13+
    'See: TntUnicode.txt.'+#10#13+#10#13+
    '"HD Operation" wizard is using:'+#10#13+
    'GRUBINSTALL ver:9b'+#10#13+
    'by: Lode Leroy,'+#10#13+#10#13+
    'and LOADLIN ver:1.6c'+#10#13+
    'by: Hans Lermen.'),[version,date,email]);
    Caption:=PWideChar(_('About'));
    Button1.Caption:=PWideChar(_('Close'));
    memo1.SetFocus;
end;

end.
