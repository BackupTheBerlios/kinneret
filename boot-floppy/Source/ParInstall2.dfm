object parinst2: Tparinst2
  Left = 319
  Top = 122
  Width = 395
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
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object ButtonStart: TTntButton
    Left = 224
    Top = 360
    Width = 113
    Height = 33
    Caption = 'Start Installation'
    Enabled = False
    TabOrder = 0
  end
  object ButtonCancel: TTntButton
    Left = 64
    Top = 360
    Width = 113
    Height = 33
    Caption = 'Cancel'
    TabOrder = 1
  end
  object TntGroupBox1: TTntGroupBox
    Left = 16
    Top = 176
    Width = 353
    Height = 161
    Caption = 'Boot Options'
    TabOrder = 2
    object LabelBoot: TTntLabel
      Left = 24
      Top = 32
      Width = 305
      Height = 65
      AutoSize = False
    end
    object TntCheckBox2: TTntCheckBox
      Left = 24
      Top = 112
      Width = 305
      Height = 17
      Caption = 'Desktop Icon (Windows 95,98,ME)'
      TabOrder = 0
    end
    object TntCheckBox1: TTntCheckBox
      Left = 24
      Top = 128
      Width = 305
      Height = 17
      Caption = 'Boot Menu (Windows 95,98, NT,2000, XP)'
      TabOrder = 1
    end
  end
  object TntGroupBox2: TTntGroupBox
    Left = 16
    Top = 16
    Width = 353
    Height = 145
    Caption = 'Drive Options'
    TabOrder = 3
    object LabelChoose: TTntLabel
      Left = 24
      Top = 24
      Width = 305
      Height = 25
      AutoSize = False
    end
    object LabelFree: TTntLabel
      Left = 24
      Top = 64
      Width = 273
      Height = 65
      AutoSize = False
    end
    object TntListView1: TTntListView
      Left = 24
      Top = 56
      Width = 304
      Height = 73
      Columns = <
        item
          Caption = 'Drive'
        end
        item
          Caption = 'Free space before inst.'
          Width = 125
        end
        item
          Caption = 'Free space after inst.'
          Width = 125
        end>
      Items.Data = {
        240000000100000000000000FFFFFFFFFFFFFFFF010000000000000001430361
        6263FFFF}
      TabOrder = 0
      ViewStyle = vsReport
    end
  end
end
