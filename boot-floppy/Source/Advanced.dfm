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
  object Explanation: TLabel
    Left = 24
    Top = 8
    Width = 369
    Height = 65
    AutoSize = False
  end
  object Label1: TLabel
    Left = 80
    Top = 328
    Width = 107
    Height = 13
    Caption = 'Insert a new key name'
  end
  object ParamList: TValueListEditor
    Left = 24
    Top = 96
    Width = 273
    Height = 209
    Hint = 'Edit the Values here'
    KeyOptions = [keyDelete, keyUnique]
    ParentShowHint = False
    ShowHint = False
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
    Hint = 'Add a new Key'
    Caption = 'Add'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 1
    OnClick = ButtonAddClick
  end
  object ButtonRemove: TButton
    Left = 312
    Top = 280
    Width = 81
    Height = 25
    Hint = 'Remove a selected Key and his Value'
    Caption = 'Remove'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 2
    OnClick = ButtonRemoveClick
  end
  object ButtonSave: TButton
    Left = 312
    Top = 96
    Width = 81
    Height = 25
    Hint = 'Save changes and exit'
    Caption = 'Save && Exit'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 3
    OnClick = ButtonSaveClick
  end
  object ButtonCancel: TButton
    Left = 312
    Top = 144
    Width = 81
    Height = 25
    Hint = 'Exit without saving'
    Caption = 'Cancel'
    ParentShowHint = False
    ShowHint = True
    TabOrder = 4
    OnClick = ButtonCancelClick
  end
  object EditKey: TEdit
    Left = 200
    Top = 328
    Width = 97
    Height = 21
    TabOrder = 5
    OnKeyPress = EditKeyKeyPress
  end
end
