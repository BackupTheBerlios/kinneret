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
end;

procedure TFormAbout.FormShow(Sender: TObject);
begin
    if GetCurrentLanguage='iw' then BidiMode:=bdRightToLeft
    else Bidimode:=bdLeftToRight;
    if GetCurrentLanguage='he' then memo1.Alignment:=taRightJustify
    else memo1.Alignment:=taLeftJustify;
    memo1.Text:=PWideChar(_('Kinneret''s Boot Floppy Maker'+#10#13#10#13+
    'Version: 0.2b,'+#10#13+
    'Date: 4/5/2003,'+#10#13+
    'Written by: Nir Misgav.'+#10#13+
    'Email: nirro@yahoo.com'+#10#13+
    'All rights reserved to'+#10#13+
    'GNU/Linux Kinneret.'+#10#13+
    'http://www.linux-kinneret.org'+#10#13#10#13+
    'Lincense: GPL'+#10#13+
    '(Not include TGIFImage).'+#10#13#10#13+
    'Based on: RawWriteWin-0.7,'+#10#13+
    'Written by: John Newbigin,'+#10#13+
    'License: GPL.'+#10#13#10#13+
    'Graphics made with: TGIFImage,'+#10#13+
    'Author: Andres Melander,'+#10#13+
    'Ported to D7 by: Finn Tolderlund.'+#10#13+
    'License: See TGIFImage.hlp,'+#10#13+
    'under section : License.'+#10#13#10#13+
    'Unicode Libraries from:'+#10#13+
    'Tnt Unicode Controls,'+#10#13+
    'by Tnt Software Products.'+#10#13+
    'License: Unspecific open source,'+#10#13+
    'See: TntUnicode.txt.'));

    Caption:=PWideChar(_('About'));
    Button1.Caption:=PWideChar(_('Close'));
end;

end.
