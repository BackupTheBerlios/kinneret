object parinst2: Tparinst2
  Left = 319
  Top = 122
  BorderStyle = bsToolWindow
  Caption = 'Partial Installation'
  ClientHeight = 436
  ClientWidth = 387
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
    Left = 232
    Top = 384
    Width = 113
    Height = 33
    Caption = 'Start Installation'
    Enabled = False
    TabOrder = 0
  end
  object ButtonCancel: TTntButton
    Left = 40
    Top = 384
    Width = 113
    Height = 33
    Caption = 'Cancel'
    TabOrder = 1
    OnClick = ButtonCancelClick
  end
  object TntGroupBox1: TTntGroupBox
    Left = 16
    Top = 176
    Width = 353
    Height = 185
    Caption = '2. Boot Options'
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
      Top = 120
      Width = 297
      Height = 17
      Caption = 'Desktop shortcut (Windows 95,98,ME)'
      TabOrder = 0
    end
    object TntCheckBox1: TTntCheckBox
      Left = 24
      Top = 144
      Width = 297
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
    Caption = '1. Drive Options'
    TabOrder = 3
    object LabelChoose: TTntLabel
      Left = 16
      Top = 24
      Width = 321
      Height = 25
      AutoSize = False
    end
    object ListDrives: TTntListView
      Left = 16
      Top = 56
      Width = 321
      Height = 73
      Checkboxes = True
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
      ReadOnly = True
      RowSelect = True
      TabOrder = 0
      ViewStyle = vsReport
      OnMouseUp = ListDrivesMouseUp
    end
  end
end
