object Form2: TForm2
  Left = 0
  Top = 0
  Caption = 'Client'
  ClientHeight = 181
  ClientWidth = 465
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 88
    Top = 31
    Width = 11
    Height = 13
    Caption = 'ID'
  end
  object Label2: TLabel
    Left = 24
    Top = 69
    Width = 75
    Height = 13
    Caption = 'Available blocks'
  end
  object Label3: TLabel
    Left = 68
    Top = 108
    Width = 23
    Height = 13
    Caption = 'Data'
  end
  object Button1: TButton
    Left = 177
    Top = 138
    Width = 105
    Height = 25
    Caption = 'Send request'
    TabOrder = 0
    OnClick = Button1Click
  end
  object Edit1: TEdit
    Left = 121
    Top = 23
    Width = 177
    Height = 21
    ReadOnly = True
    TabOrder = 1
  end
  object Edit2: TEdit
    Left = 121
    Top = 100
    Width = 177
    Height = 21
    TabOrder = 2
  end
  object StringGrid1: TStringGrid
    Left = 121
    Top = 59
    Width = 320
    Height = 23
    ColCount = 15
    DefaultColWidth = 20
    DefaultRowHeight = 20
    FixedCols = 0
    RowCount = 1
    FixedRows = 0
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -21
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    OnSelectCell = StringGrid1SelectCell
  end
end
