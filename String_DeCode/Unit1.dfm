object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'KeyForm'
  ClientHeight = 123
  ClientWidth = 502
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 40
    Top = 16
    Width = 46
    Height = 13
    Caption = 'Open key'
  end
  object Label2: TLabel
    Left = 32
    Top = 56
    Width = 54
    Height = 13
    Caption = 'Private key'
  end
  object Edit1: TEdit
    Left = 104
    Top = 13
    Width = 377
    Height = 21
    ReadOnly = True
    TabOrder = 0
  end
  object Button1: TButton
    Left = 200
    Top = 90
    Width = 97
    Height = 25
    Caption = #1043#1077#1085#1077#1088#1072#1094#1080#1103
    TabOrder = 1
    OnClick = Button1Click
  end
  object Edit2: TEdit
    Left = 104
    Top = 53
    Width = 377
    Height = 21
    ReadOnly = True
    TabOrder = 2
  end
end
