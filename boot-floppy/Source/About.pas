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
    Caption:=_('About');
    Button1.Caption:=_('Close');
end;

end.
