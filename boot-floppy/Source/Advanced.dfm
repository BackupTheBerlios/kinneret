object FormAdvanced: TFormAdvanced
  Left = 305
  Top = 168
  VertScrollBar.Smooth = True
  BorderIcons = [biSystemMenu]
  BorderStyle = bsToolWindow
  Caption = 'Advanced options'
  ClientHeight = 368
  ClientWidth = 413
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 16
    Top = 328
    Width = 18
    Height = 13
    Caption = 'Key'
  end
  object Label2: TLabel
    Left = 136
    Top = 328
    Width = 27
    Height = 13
    Caption = 'Value'
  end
  object Explanation: TLabel
    Left = 24
    Top = 8
    Width = 369
    Height = 65
    AutoSize = False
  end
  object ParamList: TValueListEditor
    Left = 24
    Top = 96
    Width = 273
    Height = 209
    KeyOptions = [keyDelete, keyUnique]
    TabOrder = 0
    ColWidths = (
      116
      151)
  end
  object ButtonAdd: TButton
    Left = 312
    Top = 328
    Width = 81
    Height = 25
    Caption = 'Add a key'
    TabOrder = 1
    OnClick = ButtonAddClick
  end
  object ButtonRemove: TButton
    Left = 312
    Top = 280
    Width = 81
    Height = 25
    Caption = 'Remove a key'
    TabOrder = 2
    OnClick = ButtonRemoveClick
  end
  object ButtonSave: TButton
    Left = 312
    Top = 96
    Width = 81
    Height = 25
    Caption = 'Save && Exit'
    TabOrder = 3
    OnClick = ButtonSaveClick
  end
  object ButtonCancel: TButton
    Left = 312
    Top = 144
    Width = 81
    Height = 25
    Caption = 'Cancel'
    TabOrder = 4
    OnClick = ButtonCancelClick
  end
  object EditKey: TEdit
    Left = 40
    Top = 328
    Width = 81
    Height = 21
    TabOrder = 5
  end
  object EditValue: TEdit
    Left = 168
    Top = 328
    Width = 121
    Height = 21
    TabOrder = 6
  end
end
