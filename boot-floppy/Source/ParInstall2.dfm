object parinst2: Tparinst2
  Left = 297
  Top = 111
  BorderStyle = bsToolWindow
  ClientHeight = 478
  ClientWidth = 387
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
  object ButtonStart: TTntButton
    Left = 232
    Top = 424
    Width = 113
    Height = 33
    Enabled = False
    TabOrder = 0
    OnClick = ButtonStartClick
  end
  object ButtonCancel: TTntButton
    Left = 40
    Top = 424
    Width = 113
    Height = 33
    TabOrder = 1
    OnClick = ButtonCancelClick
  end
  object TntGroupBox1: TTntGroupBox
    Left = 16
    Top = 216
    Width = 353
    Height = 185
    TabOrder = 2
    object LabelBoot: TTntLabel
      Left = 24
      Top = 32
      Width = 305
      Height = 65
      AutoSize = False
    end
    object LBDesktop: TTntLabel
      Left = 48
      Top = 122
      Width = 257
      Height = 17
      AutoSize = False
      Caption = 'LBDesktop'
      Color = clBtnFace
      ParentColor = False
    end
    object LBMenu: TTntLabel
      Left = 48
      Top = 146
      Width = 257
      Height = 17
      AutoSize = False
      Caption = 'LBMenu'
    end
    object CBDesktop: TTntCheckBox
      Left = 24
      Top = 120
      Width = 305
      Height = 17
      TabOrder = 0
    end
    object CBMenu: TTntCheckBox
      Left = 24
      Top = 144
      Width = 305
      Height = 17
      TabOrder = 1
    end
  end
  object TntGroupBox2: TTntGroupBox
    Left = 16
    Top = 16
    Width = 353
    Height = 185
    TabOrder = 3
    object LabelChoose: TTntLabel
      Left = 16
      Top = 24
      Width = 321
      Height = 25
      AutoSize = False
    end
    object LabelNote: TTntLabel
      Left = 24
      Top = 144
      Width = 305
      Height = 33
      AutoSize = False
    end
    object ListDrives: TTntListView
      Left = 16
      Top = 56
      Width = 321
      Height = 73
      BiDiMode = bdLeftToRight
      Checkboxes = True
      Columns = <
        item
        end
        item
          Alignment = taCenter
          Width = 125
        end
        item
          Alignment = taCenter
          Width = 125
        end>
      ReadOnly = True
      RowSelect = True
      ParentBiDiMode = False
      TabOrder = 0
      ViewStyle = vsReport
      OnMouseUp = ListDrivesMouseUp
    end
  end
end
