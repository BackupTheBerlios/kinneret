object parinst2: Tparinst2
  Left = 192
  Top = 114
  Width = 383
  Height = 470
  Caption = 'Partial Installation'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object ButtonStart: TTntButton
    Left = 216
    Top = 376
    Width = 113
    Height = 33
    Caption = 'Start Installation'
    Enabled = False
    TabOrder = 0
  end
  object ButtonCancel: TTntButton
    Left = 40
    Top = 376
    Width = 113
    Height = 33
    Caption = 'Cancel'
    TabOrder = 1
  end
  object TntGroupBox1: TTntGroupBox
    Left = 24
    Top = 176
    Width = 321
    Height = 161
    Caption = 'Boot Options'
    TabOrder = 2
    object LabelBoot: TTntLabel
      Left = 16
      Top = 32
      Width = 281
      Height = 65
      AutoSize = False
    end
    object TntCheckBox2: TTntCheckBox
      Left = 16
      Top = 112
      Width = 265
      Height = 17
      Caption = 'Desktop Icon (Windows 95,98,ME)'
      TabOrder = 0
    end
    object TntCheckBox1: TTntCheckBox
      Left = 16
      Top = 128
      Width = 265
      Height = 17
      Caption = 'Boot Menu (Windows 95,98, NT,2000, XP)'
      TabOrder = 1
    end
  end
  object TntGroupBox2: TTntGroupBox
    Left = 24
    Top = 16
    Width = 321
    Height = 145
    Caption = 'Drive Options'
    TabOrder = 3
    object LabelChoose: TTntLabel
      Left = 152
      Top = 16
      Width = 145
      Height = 25
      AutoSize = False
    end
    object LabelFree: TTntLabel
      Left = 16
      Top = 48
      Width = 281
      Height = 81
      AutoSize = False
    end
    object DriveComboBox1: TDriveComboBox
      Left = 8
      Top = 16
      Width = 129
      Height = 19
      TabOrder = 0
      OnChange = DriveComboBox1Change
    end
  end
end
