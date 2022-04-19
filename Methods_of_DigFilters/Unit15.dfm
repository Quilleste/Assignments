object Form15: TForm15
  Left = 0
  Top = 0
  Caption = 'Form15'
  ClientHeight = 551
  ClientWidth = 667
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
    Left = 166
    Top = 392
    Width = 157
    Height = 13
    Caption = #1050#1086#1101#1092#1092#1080#1094#1080#1077#1085#1090' '#1101#1092#1092#1077#1082#1090#1080#1074#1085#1086#1089#1090#1080':'
  end
  object Label2: TLabel
    Left = 202
    Top = 424
    Width = 121
    Height = 13
    Caption = #1044#1080#1089#1087#1077#1088#1089#1080#1103' '#1076#1086' '#1092#1080#1083#1100#1090#1088#1072':'
  end
  object Label3: TLabel
    Left = 186
    Top = 456
    Width = 137
    Height = 13
    Caption = #1044#1080#1089#1087#1077#1088#1089#1080#1103' '#1087#1086#1089#1083#1077' '#1092#1080#1083#1100#1090#1088#1072':'
  end
  object Label4: TLabel
    Left = 181
    Top = 488
    Width = 142
    Height = 13
    Caption = #1052#1072#1090'.'#1086#1078#1080#1076#1072#1085#1080#1077' '#1076#1086' '#1092#1080#1083#1100#1090#1088#1072':'
  end
  object Label5: TLabel
    Left = 165
    Top = 515
    Width = 158
    Height = 13
    Caption = #1052#1072#1090'.'#1086#1078#1080#1076#1072#1085#1080#1077' '#1087#1086#1089#1083#1077' '#1092#1080#1083#1100#1090#1088#1072':'
  end
  object Chart1: TChart
    Left = 8
    Top = 8
    Width = 641
    Height = 313
    AllowPanning = pmNone
    Legend.Visible = False
    Title.Text.Strings = (
      'EKG')
    View3D = False
    TabOrder = 0
    object Series1: TLineSeries
      Marks.Arrow.Visible = True
      Marks.Callout.Brush.Color = clBlack
      Marks.Callout.Arrow.Visible = True
      Marks.Visible = False
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.Visible = False
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
    object Series2: TLineSeries
      Active = False
      Marks.Arrow.Visible = True
      Marks.Callout.Brush.Color = clBlack
      Marks.Callout.Arrow.Visible = True
      Marks.Visible = False
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.Visible = False
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
    object Series3: TLineSeries
      Active = False
      Marks.Arrow.Visible = True
      Marks.Callout.Brush.Color = clBlack
      Marks.Callout.Arrow.Visible = True
      Marks.Visible = False
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.Visible = False
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
    object Series4: TLineSeries
      Active = False
      Marks.Arrow.Visible = True
      Marks.Callout.Brush.Color = clBlack
      Marks.Callout.Arrow.Visible = True
      Marks.Visible = False
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      Pointer.Visible = False
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
  end
  object Button1: TButton
    Left = 128
    Top = 344
    Width = 89
    Height = 25
    Caption = 'Noize chart'
    TabOrder = 1
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 248
    Top = 344
    Width = 75
    Height = 25
    Caption = 'Initial EKG'
    TabOrder = 2
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 352
    Top = 344
    Width = 75
    Height = 25
    Caption = 'Linear filter'
    TabOrder = 3
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 456
    Top = 344
    Width = 75
    Height = 25
    Caption = 'Median filter'
    TabOrder = 4
    OnClick = Button4Click
  end
  object Edit1: TEdit
    Left = 352
    Top = 389
    Width = 121
    Height = 21
    TabOrder = 5
  end
  object Edit2: TEdit
    Left = 352
    Top = 421
    Width = 121
    Height = 21
    TabOrder = 6
  end
  object Edit3: TEdit
    Left = 352
    Top = 453
    Width = 121
    Height = 21
    TabOrder = 7
  end
  object Edit4: TEdit
    Left = 352
    Top = 485
    Width = 121
    Height = 21
    TabOrder = 8
  end
  object Edit5: TEdit
    Left = 352
    Top = 515
    Width = 121
    Height = 21
    TabOrder = 9
  end
end
