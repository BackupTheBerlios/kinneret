object ParInst3: TParInst3
  Left = 255
  Top = 237
  BorderStyle = bsToolWindow
  Caption = 'Installing Kinneret'
  ClientHeight = 159
  ClientWidth = 329
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnActivate = FormActivate
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object LabelWait: TTntLabel
    Left = 16
    Top = 32
    Width = 289
    Height = 41
    Alignment = taCenter
    AutoSize = False
  end
  object ButtonClose: TTntButton
    Left = 104
    Top = 104
    Width = 113
    Height = 33
    Caption = 'Close'
    Enabled = False
    TabOrder = 0
    OnClick = ButtonCloseClick
  end
end
