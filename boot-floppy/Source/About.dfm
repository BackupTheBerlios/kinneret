object FormAbout: TFormAbout
  Left = 288
  Top = 244
  AutoSize = True
  BorderIcons = [biSystemMenu]
  BorderStyle = bsToolWindow
  BorderWidth = 10
  Caption = 'About'
  ClientHeight = 233
  ClientWidth = 217
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Memo1: TTntMemo
    Left = 0
    Top = 0
    Width = 217
    Height = 201
    Cursor = crIBeam
    Color = clBtnFace
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 0
  end
  object Button1: TTntButton
    Left = 64
    Top = 208
    Width = 89
    Height = 25
    Caption = 'Close'
    TabOrder = 1
    OnClick = Button1Click
  end
end
