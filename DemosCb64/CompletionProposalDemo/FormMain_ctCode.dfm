object Form1: TForm1
  Left = 212
  Top = 100
  Caption = 'SynEdit Code Completion Demo for ctCode'
  ClientHeight = 547
  ClientWidth = 760
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnShow = FormShow
  TextHeight = 13
  object PageControl1: TPageControl
    Left = 8
    Top = 8
    Width = 753
    Height = 537
    ActivePage = CodeCompletion
    TabOrder = 0
    object CodeCompletion: TTabSheet
      Caption = 'CodeCompletion'
      object Label3: TLabel
        Left = 8
        Top = 19
        Width = 64
        Height = 13
        Caption = 'BiggestWord:'
      end
      object Label4: TLabel
        Left = 224
        Top = 19
        Width = 23
        Height = 13
        Caption = 'Title:'
      end
      object edBiggestWord: TEdit
        Left = 80
        Top = 16
        Width = 121
        Height = 21
        TabOrder = 0
        Text = 'constructor'
        OnChange = edBiggestWordChange
      end
      object cbCase: TCheckBox
        Tag = 1
        Left = 8
        Top = 40
        Width = 129
        Height = 17
        Caption = 'Case Sensitive'
        TabOrder = 2
        OnClick = CheckBoxClick
      end
      object cbPrettyText: TCheckBox
        Tag = 3
        Left = 8
        Top = 64
        Width = 129
        Height = 17
        Caption = 'Use Pretty Text'
        Checked = True
        State = cbChecked
        TabOrder = 3
        OnClick = CheckBoxClick
      end
      object cbUseInsertList: TCheckBox
        Tag = 4
        Left = 8
        Top = 88
        Width = 129
        Height = 17
        Caption = 'Use Insert List'
        Checked = True
        State = cbChecked
        TabOrder = 4
        OnClick = CheckBoxClick
      end
      object cbLimitToMatchedText: TCheckBox
        Tag = 5
        Left = 8
        Top = 112
        Width = 129
        Height = 17
        Caption = 'Limit To Matched Text'
        Checked = True
        State = cbChecked
        TabOrder = 5
        OnClick = CheckBoxClick
      end
      object edTitle: TEdit
        Left = 256
        Top = 16
        Width = 145
        Height = 21
        TabOrder = 1
        Text = 'Completion Proposal Demo'
        OnChange = edTitleChange
      end
      object Button3: TButton
        Left = 240
        Top = 112
        Width = 75
        Height = 25
        Caption = 'Font'
        TabOrder = 6
        OnClick = Button3Click
      end
      object Button4: TButton
        Left = 328
        Top = 112
        Width = 75
        Height = 25
        Caption = 'Title Font'
        TabOrder = 7
        OnClick = Button4Click
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Insert and Item Lists'
      ImageIndex = 1
      object Label1: TLabel
        Left = 8
        Top = 8
        Width = 57
        Height = 13
        Caption = 'Insert List'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object Label2: TLabel
        Left = 8
        Top = 240
        Width = 45
        Height = 13
        Caption = 'ItemList'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object mmoInsert: TMemo
        Left = 8
        Top = 24
        Width = 729
        Height = 169
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Courier New'
        Font.Style = []
        Lines.Strings = (
          'mmoInsert')
        ParentFont = False
        TabOrder = 0
      end
      object mmoItem: TMemo
        Left = 8
        Top = 256
        Width = 729
        Height = 209
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Courier New'
        Font.Style = []
        Lines.Strings = (
          'mmoItem')
        ParentFont = False
        TabOrder = 1
        WantTabs = True
      end
      object Button1: TButton
        Left = 8
        Top = 200
        Width = 137
        Height = 25
        Caption = 'Update Insert List'
        TabOrder = 2
        OnClick = Button1Click
      end
      object Button2: TButton
        Left = 8
        Top = 472
        Width = 137
        Height = 25
        Caption = 'Update Item List'
        TabOrder = 3
        OnClick = Button2Click
      end
    end
  end
  object FontDialog1: TFontDialog
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    Left = 348
    Top = 80
  end
end
