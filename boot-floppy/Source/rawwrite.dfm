object MainForm: TMainForm
  Left = 460
  Top = 366
  AutoSize = True
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsToolWindow
  BorderWidth = 20
  Caption = 'Make a bootable floppy'
  ClientHeight = 165
  ClientWidth = 297
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = True
  Position = poScreenCenter
  OnClose = FormClose
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Labelup: TTntLabel
    Left = 0
    Top = 0
    Width = 297
    Height = 33
    Alignment = taCenter
    AutoSize = False
  end
  object Labeldown: TTntLabel
    Left = 0
    Top = 136
    Width = 297
    Height = 29
    Alignment = taCenter
    AutoSize = False
  end
  object ProgressBar1: TProgressBar
    Left = 0
    Top = 104
    Width = 297
    Height = 25
    TabOrder = 0
  end
  object ButtonStart: TTntButton
    Left = 184
    Top = 48
    Width = 97
    Height = 33
    TabOrder = 1
    OnClick = WriteButtonClick
  end
  object ButtonCancel: TTntButton
    Left = 16
    Top = 48
    Width = 97
    Height = 33
    TabOrder = 2
    OnClick = Button3Click
  end
end
