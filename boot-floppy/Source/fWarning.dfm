object FormWarning: TFormWarning
  Left = 425
  Top = 248
  BorderIcons = [biSystemMenu]
  BorderStyle = bsToolWindow
  Caption = 'Warning'
  ClientHeight = 81
  ClientWidth = 161
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnCreate = FormCreate
  OnPaint = TntFormPaint
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TTntLabel
    Left = 48
    Top = 0
    Width = 3
    Height = 13
  end
  object ButtonCancel: TTntButton
    Left = 0
    Top = 56
    Width = 81
    Height = 25
    TabOrder = 0
    OnClick = ButtonCancelClick
  end
  object ButtonContinune: TTntButton
    Left = 80
    Top = 56
    Width = 81
    Height = 25
    TabOrder = 1
    OnClick = ButtonContinuneClick
  end
end
