object ParInst3: TParInst3
  Left = 278
  Top = 237
  BorderStyle = bsToolWindow
  ClientHeight = 131
  ClientWidth = 276
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
    Top = 16
    Width = 241
    Height = 41
    Alignment = taCenter
    AutoSize = False
  end
  object ButtonClose: TTntButton
    Left = 80
    Top = 80
    Width = 113
    Height = 33
    Enabled = False
    TabOrder = 0
    OnClick = ButtonCloseClick
  end
end
