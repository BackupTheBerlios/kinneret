object parinst: Tparinst
  Left = 380
  Top = 185
  BorderStyle = bsToolWindow
  Caption = 'Partial installation wizard'
  ClientHeight = 318
  ClientWidth = 345
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object explanation: TTntLabel
    Left = 24
    Top = 32
    Width = 297
    Height = 185
    AutoSize = False
  end
  object YesButton: TTntButton
    Left = 184
    Top = 256
    Width = 129
    Height = 33
    Caption = 'Yes'
    TabOrder = 0
    OnClick = YesButtonClick
  end
  object NoButton: TTntButton
    Left = 32
    Top = 256
    Width = 129
    Height = 33
    Caption = 'Not now, thanks'
    TabOrder = 1
    OnClick = NoButtonClick
  end
end
