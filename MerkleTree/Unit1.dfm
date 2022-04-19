object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Server'
  ClientHeight = 373
  ClientWidth = 660
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
    Left = 112
    Top = 8
    Width = 32
    Height = 13
    Caption = 'Clients'
  end
  object Label2: TLabel
    Left = 440
    Top = 8
    Width = 71
    Height = 13
    Caption = 'Available parts'
  end
  object Panel1: TPanel
    Left = 264
    Top = -8
    Width = 17
    Height = 449
    TabOrder = 0
  end
  object Button1: TButton
    Left = 424
    Top = 255
    Width = 97
    Height = 25
    Caption = 'Request a part'
    TabOrder = 1
    OnClick = Button1Click
  end
  object StringGrid1: TStringGrid
    Left = 48
    Top = 27
    Width = 161
    Height = 214
    ColCount = 1
    DefaultColWidth = 180
    DefaultRowHeight = 20
    FixedCols = 0
    RowCount = 10
    FixedRows = 0
    ScrollBars = ssNone
    TabOrder = 2
  end
  object StringGrid2: TStringGrid
    Left = 320
    Top = 27
    Width = 320
    Height = 214
    ColCount = 15
    DefaultColWidth = 20
    DefaultRowHeight = 20
    FixedCols = 0
    RowCount = 10
    FixedRows = 0
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    ScrollBars = ssNone
    TabOrder = 3
    OnSelectCell = StringGrid2SelectCell
  end
  object Button2: TButton
    Left = 424
    Top = 334
    Width = 97
    Height = 25
    Caption = 'Block verification'
    TabOrder = 4
    OnClick = Button2Click
  end
  object Edit1: TEdit
    Left = 320
    Top = 296
    Width = 320
    Height = 21
    ReadOnly = True
    TabOrder = 5
  end
end
