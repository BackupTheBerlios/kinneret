object FormAbout: TFormAbout
  Left = 328
  Top = 92
  Width = 221
  Height = 287
  AutoSize = True
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSizeToolWin
  BorderWidth = 10
  Caption = 'About'
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
    Width = 193
    Height = 201
    Cursor = crIBeam
    BiDiMode = bdLeftToRight
    Lines.WideStrings = (
      'Kinneret Make Boot Floppy'
      ''
      'Version: 0.0.3 alpha'
      'Date: 21/3/2003'
      'Written by: Nir Misgav.'
      'Lincense: GPL.'
      '(Not include TGIFImage)'
      ''
      'Based on: RawWriteWin-0.7'
      'Written by: John Newbigin'
      'License: GPL.'
      ''
      'Graphics made with: TGIFImage'
      'Author: Andres Melander'
      'Ported to D7 by: Finn Tolderlund.'
      'License: See TGIFImage.hlp,'
      'under section : License.'
      ''
      'Unicode Libraries from:'
      'Tnt Unicode Controls'
      'by Tnt Software Products'
      'License: Unspecific open source,'
      'See: TntUnicode.txt')
    ParentBiDiMode = False
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 0
  end
  object Button1: TTntButton
    Left = 56
    Top = 208
    Width = 81
    Height = 25
    Caption = 'Close'
    TabOrder = 1
    OnClick = Button1Click
  end
end
