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
  math, Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, gnugettext, GIFImage, ExtCtrls, tntForms,TntStdCtrls;

type
  mType = (MSG,QST,WRN,ERR);
  TFormWarning = class(TtntForm)
    Label1: TtntLabel;
    ButtonCancel: TtntButton;
    ButtonContinune: TtntButton;
    procedure FormCreate(Sender: TObject);
    procedure ButtonContinuneClick(Sender: TObject);
    procedure ButtonCancelClick(Sender: TObject);
    procedure TntFormPaint(Sender: TObject);
  private
    { Private declarations }
    drIcon: HIcon;
    pic: pAnsiChar;
  public
    Cancel: Boolean;
    fType: mType;

    { Public declarations }
  end;
function showWarning(tType :mType; mtext: WideString) :boolean;

var
  FormWarning: TFormWarning;

implementation

{$R *.dfm}

function showWarning(tType :mType; mText: WideString) :boolean;
begin
  with FormWarning do begin
    fType:=tType;
    Label1.Caption:=mtext;
    if GetCurrentLanguage='he' then Label1.Alignment:=taRightJustify
    else if getCurrentLanguage='iw' then bidimode:=bdRightToLeft
    else begin
      Label1.Alignment:=taLeftJustify;
      BidiMode:=bdLeftToRight;
    end;
    if fType=MSG then begin
      pic:=IDI_INFORMATION;
      Caption:=pWideChar(_('Information'));
      messagebeep(MB_ICONASTERISK);
    end else if fType=QST then begin
      pic:=IDI_QUESTION;
      Caption:=pWideChar(_('Question'));
      messagebeep(MB_ICONQUESTION);
      ButtonCancel.Caption:=pWideChar(_('No'));
      ButtonContinune.Caption:=pWideChar(_('Yes'));
    end else if fType=WRN then begin
      pic:=IDI_EXCLAMATION;
      Caption:=pWideChar(_('Warning'));
      messagebeep(MB_ICONEXCLAMATION);
      ButtonCancel.Caption:=pWideChar(_('Cancel'));
      ButtonContinune.Caption:=pWideChar(_('Continue'));
    end else if fType=ERR then begin
      pic:=IDI_ERROR;
      Caption:=pWideChar(_('Error'));
      messagebeep(MB_ICONERROR);
    end;
    DrIcon:=LoadIcon(0,pic);
    if (fType=WRN) or (fType=QST) then
    begin
      ButtonContinune.Show;
      Width:=max(Label1.Width+70,220);
      ButtonCancel.Left:=Width div 2-ButtonCancel.width-10;
      ButtonContinune.Left:=Width div 2 + 4;
      ButtonContinune.Top:=Max(Label1.Height,30)+16;
      ButtonCancel.Top:=ButtonContinune.Top;
      Height:=ButtonCancel.Top+60;
    end else begin
      ButtonCancel.Caption:=pWideChar(_('Ok'));
      ButtonContinune.Hide;
      Width:=max(Label1.Width+70,150);
      ButtonCancel.Top:=Max(Label1.Height,30)+16;
      ButtonCancel.Left:=Width div 2-ButtonCancel.width div 2;
    end;
    Label1.Top:=8;
    if (GetCurrentLanguage='he') or (GetCurrentLanguage='iw') then Label1.Left:=width-20-Label1.Width
    else Label1.Left:=50;
    Height:=ButtonCancel.Top+60;
    cancel:=True;
    position:=poDesktopCenter;
    ShowModal;
    showWarning:=not Cancel;
  end;
end;

procedure TFormWarning.FormCreate(Sender: TObject);
begin
  TranslateProperties (self);      //GNUGETTEXT

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

procedure TFormWarning.TntFormPaint(Sender: TObject);
begin
  DrawIcon(canvas.Handle,10,8,drIcon);
end;

end.
