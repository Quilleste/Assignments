object Form4: TForm4
  Left = 0
  Top = 0
  Caption = 'Lab01_07'
  ClientHeight = 483
  ClientWidth = 827
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
    Left = 493
    Top = 200
    Width = 46
    Height = 13
    Caption = #1069#1090#1072#1083#1086#1085' 1'
  end
  object Label2: TLabel
    Left = 493
    Top = 223
    Width = 46
    Height = 13
    Caption = #1069#1090#1072#1083#1086#1085' 2'
  end
  object Label3: TLabel
    Left = 493
    Top = 246
    Width = 46
    Height = 13
    Caption = #1069#1090#1072#1083#1086#1085' 3'
  end
  object Label4: TLabel
    Left = 493
    Top = 269
    Width = 46
    Height = 13
    Caption = #1069#1090#1072#1083#1086#1085' 4'
  end
  object StringGrid1: TStringGrid
    Left = 24
    Top = 32
    Width = 107
    Height = 107
    Constraints.MaxHeight = 107
    Constraints.MaxWidth = 107
    DefaultColWidth = 20
    DefaultRowHeight = 20
    FixedCols = 0
    FixedRows = 0
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    ScrollBars = ssNone
    TabOrder = 0
    ColWidths = (
      20
      20
      21
      20
      20)
  end
  object StringGrid2: TStringGrid
    Left = 160
    Top = 32
    Width = 107
    Height = 107
    DefaultColWidth = 20
    DefaultRowHeight = 20
    FixedCols = 0
    FixedRows = 0
    ScrollBars = ssNone
    TabOrder = 1
    ColWidths = (
      20
      20
      21
      20
      20)
    RowHeights = (
      20
      21
      20
      20
      20)
  end
  object StringGrid3: TStringGrid
    Left = 296
    Top = 32
    Width = 107
    Height = 107
    DefaultColWidth = 20
    DefaultRowHeight = 20
    FixedCols = 0
    FixedRows = 0
    ScrollBars = ssNone
    TabOrder = 2
    ColWidths = (
      20
      20
      21
      20
      20)
    RowHeights = (
      20
      20
      20
      20
      20)
  end
  object StringGrid4: TStringGrid
    Left = 432
    Top = 32
    Width = 107
    Height = 107
    DefaultColWidth = 20
    DefaultRowHeight = 20
    FixedCols = 0
    FixedRows = 0
    ScrollBars = ssNone
    TabOrder = 3
    ColWidths = (
      20
      20
      21
      20
      20)
  end
  object StaticText1: TStaticText
    Left = 56
    Top = 9
    Width = 50
    Height = 17
    Caption = #1069#1090#1072#1083#1086#1085' 1'
    TabOrder = 4
  end
  object StaticText2: TStaticText
    Left = 192
    Top = 9
    Width = 50
    Height = 17
    Caption = #1069#1090#1072#1083#1086#1085' 2'
    TabOrder = 5
  end
  object StaticText3: TStaticText
    Left = 328
    Top = 9
    Width = 50
    Height = 17
    Caption = #1069#1090#1072#1083#1086#1085' 3'
    TabOrder = 6
  end
  object StaticText4: TStaticText
    Left = 464
    Top = 9
    Width = 50
    Height = 17
    Caption = #1069#1090#1072#1083#1086#1085' 4'
    TabOrder = 7
  end
  object StringGrid5: TStringGrid
    Left = 648
    Top = 32
    Width = 107
    Height = 107
    Constraints.MaxHeight = 107
    Constraints.MaxWidth = 107
    DefaultColWidth = 20
    DefaultRowHeight = 20
    FixedCols = 0
    FixedRows = 0
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    ScrollBars = ssNone
    TabOrder = 8
    OnSelectCell = StringGrid5SelectCell
    ColWidths = (
      20
      20
      21
      20
      20)
  end
  object StaticText5: TStaticText
    Left = 632
    Top = 9
    Width = 142
    Height = 17
    Caption = #1057#1080#1084#1074#1086#1083' '#1076#1083#1103' '#1088#1072#1079#1087#1086#1079#1085#1072#1074#1072#1085#1080#1103
    TabOrder = 9
  end
  object RadioGroup1: TRadioGroup
    Left = 24
    Top = 176
    Width = 273
    Height = 169
    Caption = #1052#1077#1090#1086#1076#1099' '#1088#1077#1096#1077#1085#1080#1103
    Items.Strings = (
      #1056#1072#1089#1089#1090#1086#1103#1085#1080#1077' '#1087#1086' '#1045#1074#1082#1083#1080#1076#1091
      #1057#1091#1084#1084#1072' '#1084#1086#1076#1091#1083#1077#1081' '#1088#1072#1079#1085#1086#1089#1090#1077#1081' n-'#1084#1077#1088#1085#1099#1093' '#1074#1077#1082#1090#1086#1088#1086#1074
      #1056#1072#1089#1089#1090#1086#1103#1085#1080#1077' '#1087#1086' '#1045#1074#1082#1083#1080#1076#1091' '#1089' '#1082#1086#1101#1092#1092#1080#1094#1080#1077#1085#1090#1086#1084
      #1056#1072#1089#1089#1090#1086#1103#1085#1080#1077' '#1087#1086' '#1050#1072#1084#1073#1077#1088#1088#1091
      #1055#1086' '#1091#1075#1083#1091' '#1084#1077#1078#1076#1091' '#1074#1077#1082#1090#1086#1088#1072#1084#1080
      #1057#1093#1086#1076#1089#1090#1074#1086' '#1044#1072#1081#1089#1072' '
      #1057#1093#1086#1076#1089#1090#1074#1086' '#1046#1086#1082#1072#1088#1072' '#1080' '#1053#1080#1076#1084#1077#1085#1072
      #1057#1093#1086#1076#1089#1090#1074#1086' '#1056#1072#1089#1089#1077#1083#1072' '#1080' '#1056#1072#1086
      #1057#1093#1086#1076#1089#1090#1074#1086' '#1057#1086#1082#1072#1083#1103' '#1080' '#1057#1085#1080#1092#1072)
    TabOrder = 10
  end
  object Button1: TButton
    Left = 24
    Top = 367
    Width = 75
    Height = 25
    Caption = #1055#1086#1089#1095#1080#1090#1072#1090#1100
    TabOrder = 11
    OnClick = Button1Click
  end
  object ListBox1: TListBox
    Left = 552
    Top = 200
    Width = 89
    Height = 17
    ItemHeight = 13
    TabOrder = 12
  end
  object ListBox2: TListBox
    Left = 552
    Top = 223
    Width = 89
    Height = 17
    ItemHeight = 13
    TabOrder = 13
  end
  object ListBox3: TListBox
    Left = 552
    Top = 246
    Width = 89
    Height = 17
    ItemHeight = 13
    TabOrder = 14
  end
  object ListBox4: TListBox
    Left = 552
    Top = 269
    Width = 89
    Height = 17
    ItemHeight = 13
    TabOrder = 15
  end
end
