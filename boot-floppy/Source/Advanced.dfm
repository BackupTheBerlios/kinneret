object FormAdvanced: TFormAdvanced
  Left = 396
  Top = 206
  VertScrollBar.Smooth = True
  BorderIcons = [biSystemMenu]
  BorderStyle = bsToolWindow
  ClientHeight = 361
  ClientWidth = 413
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnClose = FormClose
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Explanation: TTntLabel
    Left = 24
    Top = 16
    Width = 369
    Height = 65
    AutoSize = False
  end
  object ParamList: TValueListEditor
    Left = 120
    Top = 104
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
  object ButtonRemove: TTntButton
    Left = 16
    Top = 192
    Width = 81
    Height = 25
    ParentShowHint = False
    ShowHint = True
    TabOrder = 1
    OnClick = ButtonRemoveClick
  end
  object ButtonSave: TTntButton
    Left = 16
    Top = 104
    Width = 81
    Height = 25
    ParentShowHint = False
    ShowHint = True
    TabOrder = 2
    OnClick = ButtonSaveClick
  end
  object ButtonCancel: TTntButton
    Left = 16
    Top = 136
    Width = 81
    Height = 25
    ParentShowHint = False
    ShowHint = True
    TabOrder = 3
    OnClick = ButtonCancelClick
  end
  object EditKey: TTntEdit
    Left = 120
    Top = 320
    Width = 113
    Height = 21
    ParentShowHint = False
    ShowHint = True
    TabOrder = 4
    OnKeyPress = EditKeyKeyPress
  end
end
