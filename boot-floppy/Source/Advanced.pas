unit Advanced;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, CheckLst, TntCheckLst, Grids, ValEdit, strutils, gnugettext;

type
  TFormAdvanced = class(TForm)
    ParamList: TValueListEditor;
    ButtonAdd: TButton;
    ButtonRemove: TButton;
    ButtonSave: TButton;
    ButtonCancel: TButton;
    EditKey: TEdit;
    Explanation: TLabel;
    Label1: TLabel;
    procedure ButtonRemoveClick(Sender: TObject);
    procedure FormClose(Sender: TObject; var Action: TCloseAction);
    procedure FormShow(Sender: TObject);
    procedure ButtonAddClick(Sender: TObject);
    procedure ButtonCancelClick(Sender: TObject);
    procedure ButtonSaveClick(Sender: TObject);
    procedure AddKey;
    procedure EditKeyKeyPress(Sender: TObject; var Key: Char);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  FormAdvanced: TFormAdvanced;
  Strings : TStringList;
  FileName : string;

implementation

{$R *.dfm}

procedure TFormAdvanced.ButtonRemoveClick(Sender: TObject);
var
        toRemove : string;
begin
        toRemove:=ParamList.Strings[ParamList.Row-1];
        if toRemove[Length(toRemove)]='=' then toRemove:=leftstr(toRemove,Length(toRemove)-1);
        if MessageDlg(pWideChar(_('Really remove ')+toRemove+' ?'),
        mtConfirmation, [mbOk, mbCancel], 0) = mrOk then
                ParamList.DeleteRow(ParamList.row);
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
var
  Line: string;
  word: string;
  key: string;
  i: integer;
begin
    FileName := 'A:\SYSLINUX.CFG';	{ set the file name }
    Explanation.Caption:=pWideChar(_('These options are for advanced users only'+#10#13+
    'You can ruin the boot-floppy easily here.'+#10#13#10#13+
    'You can change the kernel parameters here,'+#10#13+
    'These parameters will be saved in the floppy, for future boot-ups.'));


    Strings:=TStringList.Create;
    try
        Strings.LoadFromFile(Filename); { load from file }
        Line:=Strings[1];
    //Seperating Line to words
    for i:=1 to Length(Line) do
    begin
        if line[i]='=' then
        begin
            key:=word;
            word:='';
        end
        else if (line[i]=' ') then
        begin
            if key='' then begin key:=word; word:=''; end;
            if key<>'APPEND' then ParamList.InsertRow(key,word,TRUE);
            word:='';
            key:='';
        end
        else word:=word+line[i];
    end;
    if key='' then begin key:=word; word:=''; end;
    ParamList.InsertRow(key,word,TRUE);
    except
        showmessage(pWideChar(_('Unable to load settings,'+#10#13+
        'Verify the floppy is in place and try again.')));
        close;
    end;
end;

procedure TFormAdvanced.AddKey;
var
        i : integer;

begin
        if EditKey.Text='' then showmessage(pWideChar(_('You must insert a key name.')))
        else begin
            if ParamList.FindRow(EditKey.Text,i) then
            begin
                ParamList.Row:=i;
                ParamList.SetFocus;
                ShowMessage(pWideChar(_('This key is already in the list, Edit it instead.')));
                EditKey.Text:='';
            end else begin
                ParamList.InsertRow(EditKey.Text,'',TRUE);
                ParamList.Row:=ParamList.RowCount-1;
                ParamList.SetFocus;
                EditKey.Text:='';
            end;
        end;
end;

procedure TFormAdvanced.ButtonAddClick(Sender: TObject);
begin
        AddKey;
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
    if MessageDlg(pWideChar(_('Save changes and exit ?')),mtConfirmation, [mbOk, mbCancel], 0) = mrOk then
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
            showmessage(pWideChar(_('Unable to save changes,'+#10#13+
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
end;

end.

