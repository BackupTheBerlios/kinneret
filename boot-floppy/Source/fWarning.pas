unit fWarning;

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
  Dialogs, StdCtrls, gnugettext, GIFImage, ExtCtrls, tntForms,TntStdCtrls;

type
  TFormWarning = class(TtntForm)
    Label1: TtntLabel;
    ButtonCancel: TtntButton;
    ButtonContinune: TtntButton;
    Image1: TImage;
    procedure FormCreate(Sender: TObject);
    procedure FormShow(Sender: TObject);
    procedure ButtonContinuneClick(Sender: TObject);
    procedure ButtonCancelClick(Sender: TObject);
  private
    { Private declarations }
  public
    Cancel: Boolean;
    { Public declarations }
  end;

var
  FormWarning: TFormWarning;

implementation

{$R *.dfm}

procedure TFormWarning.FormCreate(Sender: TObject);
begin
  TranslateProperties (self);      //GNUGETTEXT
end;

procedure TFormWarning.FormShow(Sender: TObject);
begin
  if (GetCurrentLanguage='he') then Label1.Alignment:=taRightJustify
  else if (GetCurrentLanguage='iw') then bidimode:=bdRightToLeft
  else begin
    Label1.Alignment:=taLeftJustify;
    BidiMode:=bdLeftToRight;
  end;
  messagebeep(MB_ICONEXCLAMATION);
  Caption:=_('Warning');
  ButtonCancel.Caption:=_('Cancel');
  ButtonContinune.Caption:=_('Continune');
  cancel:=True;
end;

procedure TFormWarning.ButtonContinuneClick(Sender: TObject);
begin
  cancel:=false;
  close;
end;


procedure TFormWarning.ButtonCancelClick(Sender: TObject);
begin
  close;
end;

end.
