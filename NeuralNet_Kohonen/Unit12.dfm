object Form12: TForm12
  Left = 0
  Top = 0
  Caption = 'Receptron'
  ClientHeight = 388
  ClientWidth = 861
  Color = clMedGray
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 184
    Top = 135
    Width = 46
    Height = 13
    Caption = #1069#1090#1072#1083#1086#1085' 1'
  end
  object Label2: TLabel
    Left = 304
    Top = 135
    Width = 46
    Height = 13
    Caption = #1069#1090#1072#1083#1086#1085' 2'
  end
  object Shape1: TShape
    Left = 8
    Top = 160
    Width = 845
    Height = 1
  end
  object Label5: TLabel
    Left = 701
    Top = 135
    Width = 76
    Height = 13
    Caption = #1056#1072#1089#1087#1086#1079#1085#1072#1074#1072#1085#1080#1077
  end
  object StringGrid1: TStringGrid
    Left = 160
    Top = 24
    Width = 84
    Height = 105
    ColCount = 4
    DefaultColWidth = 20
    DefaultRowHeight = 20
    FixedCols = 0
    FixedRows = 0
    ScrollBars = ssNone
    TabOrder = 0
    OnSelectCell = StringGrid1SelectCell
  end
  object StringGrid2: TStringGrid
    Left = 280
    Top = 24
    Width = 84
    Height = 105
    ColCount = 4
    DefaultColWidth = 20
    DefaultRowHeight = 20
    FixedCols = 0
    FixedRows = 0
    ScrollBars = ssNone
    TabOrder = 1
    OnSelectCell = StringGrid2SelectCell
  end
  object StringGrid5: TStringGrid
    Left = 695
    Top = 24
    Width = 84
    Height = 105
    ColCount = 4
    DefaultColWidth = 20
    DefaultRowHeight = 20
    FixedCols = 0
    FixedRows = 0
    ScrollBars = ssNone
    TabOrder = 2
    OnSelectCell = StringGrid5SelectCell
  end
  object Memo1: TMemo
    Left = 24
    Top = 184
    Width = 689
    Height = 185
    ReadOnly = True
    ScrollBars = ssVertical
    TabOrder = 3
  end
  object Button2: TButton
    Left = 752
    Top = 256
    Width = 75
    Height = 25
    Caption = #1056#1072#1089#1087#1086#1079#1085#1072#1090#1100
    TabOrder = 4
    OnClick = Button2Click
  end
end
