object FormWarning: TFormWarning
  Left = 438
  Top = 375
  BorderIcons = [biSystemMenu]
  BorderStyle = bsToolWindow
  Caption = 'Warning'
  ClientHeight = 95
  ClientWidth = 329
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
  object Label1: TTntLabel
    Left = 56
    Top = 8
    Width = 257
    Height = 41
    AutoSize = False
  end
  object Image1: TImage
    Left = 8
    Top = 8
    Width = 36
    Height = 44
    AutoSize = True
    Picture.Data = {
      0954474946496D61676547494638396124002C00A2FF00FFFFFFFFFF00C6C3C6
      848284848200000000C0C0C000000021F90401000006002C0000000024002C00
      4003B768BADCFE3032126A1065C8BDA82D20686183C6299EA51245AA5E99E9B8
      6F6DBFB17CEE7CEF3FB451EC670886442A920E781316044DA5A444AD5AAF58A2
      9647E86E2341E937981CFE68C742B9C4B56140D09718DCACA8A3E6061917AACF
      3B758142555F85868788898A5B1E188B45386C8764798C4D95674E4F1F92991F
      472A982768A0A19DA3352C7D914B7436AB35A2337871AFA7B38275B290BAB0B6
      AD7B659BBAB7C1B96BB74569CBCCCB561158D1D2AD8FD5D62709003B}
  end
  object ButtonCancel: TTntButton
    Left = 56
    Top = 64
    Width = 81
    Height = 25
    Caption = 'Cancel'
    TabOrder = 0
    OnClick = ButtonCancelClick
  end
  object ButtonContinune: TTntButton
    Left = 192
    Top = 64
    Width = 81
    Height = 25
    Caption = 'Continune'
    TabOrder = 1
    OnClick = ButtonContinuneClick
  end
end
