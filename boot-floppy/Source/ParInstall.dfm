object parinst: Tparinst
  Left = 370
  Top = 185
  BorderStyle = bsToolWindow
  ClientHeight = 339
  ClientWidth = 355
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
    Width = 305
    Height = 217
    AutoSize = False
    WordWrap = True
  end
  object YesButton: TTntButton
    Left = 192
    Top = 280
    Width = 129
    Height = 33
    TabOrder = 0
    OnClick = YesButtonClick
  end
  object NoButton: TTntButton
    Left = 32
    Top = 280
    Width = 129
    Height = 33
    TabOrder = 1
    OnClick = NoButtonClick
  end
end
