unit Advanced;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, CheckLst, ValEdit, TntForms, Grids, strutils, gnugettext,
  TntStdCtrls,fWarning;

type
  TFormAdvanced = class(TTntForm)
    ParamList: TValueListEditor;
    ButtonRemove: TTntButton;
    ButtonSave: TTntButton;
    ButtonCancel: TTntButton;
    EditKey: TTntEdit;
    Explanation: TTntLabel;
    addLabel: TTntLabel;
    procedure ButtonRemoveClick(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure FormShow(Sender: TObject);
    procedure ButtonCancelClick(Sender: TObject);
    procedure ButtonSaveClick(Sender: TObject);
    procedure AddKey;
    procedure EditKeyKeyPress(Sender: TObject; var Key: Char);
    procedure FormCreate(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  Strings : TStringList;
  FileName : string;
  end;

var
  FormAdvanced: TFormAdvanced;

implementation

{$R *.dfm}

procedure TFormAdvanced.ButtonRemoveClick(Sender: TObject);
var
        toRemove : string;
begin
        toRemove:=ParamList.Strings[ParamList.Row-1];
        if toRemove[Length(toRemove)]='=' then toRemove:=leftstr(toRemove,Length(toRemove)-1);
        if ShowWarning(QST, WideFormat(_('Really remove %s ?'),[toRemove])) then ParamList.DeleteRow(ParamList.row);
end;

procedure TFormAdvanced.FormClose(Sender: TObject;
  var Action: TCloseAction);
var
    i: integer;
begin
     Strings.Free;
     for i:=1 to ParamList.RowCount-1 do ParamList.DeleteRow(1);

end;

procedure TFormAdvanced.FormShow(Sender: TObject);
begin
    if (GetCurrentLanguage='he') or (GetCurrentLanguage='ar') then BidiMode:=bdRightToLeft
    else Bidimode:=bdLeftToRight;
    Explanation.Caption:=pWideChar(_('These options are for advanced users only'+#10#13+
    'You can ruin the boot-floppy easily here.'+#10#13#10#13+
    'You can change the kernel parameters here,'+#10#13+
    'These parameters will be saved in the floppy, for future boot-ups.'));
    Caption:=(_('Advanced options'));
    EditKey.Hint:=pWideChar(_('To add a new key, insert the key name and press Enter.'));
    ButtonRemove.Caption:=pWideChar(_('Remove key'));
    AddLabel.Caption:=pWideChar(_('Add a new key here'));
    ButtonRemove.Hint:=pWideChar(_('Remove a selected Key and his Value'));
    ButtonCancel.Caption:=pWideChar(_('Cancel'));
    ButtonCancel.Hint:=pWideChar(_('Exit without saving'));
    ButtonSave.Caption:=pWideChar(_('Save && Exit'));
    ButtonSave.Hint:=pWideChar(_('Save changes and exit'));
end;

procedure TFormAdvanced.AddKey;
var
        i : integer;
        Error : Boolean;

begin
        if EditKey.Text='' then
        begin
          ShowWarning(ERR,pWideChar(_('You must Insert a key')));
          exit;
        end;
        Error:=false;
        for i:=0 to Length(EditKey.text) do if EditKey.Text[i]=' ' then Error:=TRUE;
        if Error then
          ShowWarning(ERR,pWideChar(_('Error - You can''t enter spaces')))
        else begin
            if ParamList.FindRow(EditKey.Text,i) then
            begin
                ParamList.Row:=i;
                ParamList.SetFocus;
                ShowWarning(MSG,pWideChar(_('This key is already in the list, Edit it instead.')));
                EditKey.Text:='';
            end else begin
                ParamList.InsertRow(EditKey.Text,'',TRUE);
                ParamList.Row:=ParamList.RowCount-1;
                ParamList.SetFocus;
                EditKey.Text:='';
            end;
        end;
end;

procedure TFormAdvanced.ButtonCancelClick(Sender: TObject);
begin
        close;
end;

procedure TFormAdvanced.ButtonSaveClick(Sender: TObject);
var
        i : integer;
        line : string;
        temp : string;
begin
    if ShowWarning(QST, pWideChar(_('Save changes and exit ?'))) then
    begin
        line:='APPEND';
        for i:=1 to ParamList.RowCount-1 do
        begin
            temp:=paramList.Strings[i-1];
            if temp[Length(temp)]='=' then temp:=leftstr(temp,Length(temp)-1);
            line:=line+' '+temp;
        end;
        Strings[1]:=line;
        try
            Strings.SaveToFile(FileName);
            close;
        Except
            ShowWarning(ERR,pWideChar(_('Unable to save changes,'+#10#13+
            'Verify the floppy is in place and try again.')));
        end;
    end;
end;

procedure TFormAdvanced.EditKeyKeyPress(Sender: TObject; var Key: Char);
begin
    if key=#13 then
    begin
        Key:=#0;
        AddKey;
    end;
    if key=' ' then key:=#13;
end;

procedure TFormAdvanced.FormCreate(Sender: TObject);
begin
  TranslateProperties (self);      //GNUGETTEXT
end;

end.

