object EditorForm: TEditorForm
  Left = 338
  Top = 199
  Caption = 'Editor'
  ClientHeight = 287
  ClientWidth = 454
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OnActivate = FormActivate
  OnClose = FormClose
  OnCloseQuery = FormCloseQuery
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnDeactivate = FormDeactivate
  OnShow = FormShow
  TextHeight = 13
  object pmnuEditor: TPopupMenu
    Left = 92
    Top = 28
    object lmiEditUndo: TMenuItem
      Action = CommandsDataModule.actEditUndo
    end
    object lmiEditRedo: TMenuItem
      Action = CommandsDataModule.actEditRedo
    end
    object N2: TMenuItem
      Caption = '-'
    end
    object lmiEditCut: TMenuItem
      Action = CommandsDataModule.actEditCut
    end
    object lmiEditCopy: TMenuItem
      Action = CommandsDataModule.actEditCopy
    end
    object lmiEditPaste: TMenuItem
      Action = CommandsDataModule.actEditPaste
    end
    object lmiEditDelete: TMenuItem
      Action = CommandsDataModule.actEditDelete
    end
    object N1: TMenuItem
      Caption = '-'
    end
    object lmiEditSelectAll: TMenuItem
      Action = CommandsDataModule.actEditSelectAll
    end
  end
end
