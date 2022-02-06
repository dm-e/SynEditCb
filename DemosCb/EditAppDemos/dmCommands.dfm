object CommandsDataModule: TCommandsDataModule
  OnCreate = DataModuleCreate
  OnDestroy = DataModuleDestroy
  Height = 276
  Width = 420
  PixelsPerInch = 96
  object dlgFileOpen: TOpenDialog
    Options = [ofHideReadOnly, ofPathMustExist, ofEnableSizing]
    Left = 20
    Top = 16
  end
  object actlMain: TActionList
    Left = 20
    Top = 168
    object actFileSave: TAction
      Category = 'File'
      Caption = '&Save'
      Enabled = False
      ShortCut = 16467
      OnExecute = actFileSaveExecute
      OnUpdate = actFileSaveUpdate
    end
    object actFileSaveAs: TAction
      Category = 'File'
      Caption = 'Save &As...'
      Enabled = False
      OnExecute = actFileSaveAsExecute
      OnUpdate = actFileSaveAsUpdate
    end
    object actFileClose: TAction
      Category = 'File'
      Caption = '&Close'
      Enabled = False
      ShortCut = 16499
      OnExecute = actFileCloseExecute
      OnUpdate = actFileCloseUpdate
    end
    object actFilePrint: TAction
      Category = 'File'
      Caption = '&Print...'
      Enabled = False
      OnExecute = actFilePrintExecute
      OnUpdate = actFilePrintUpdate
    end
    object actEditCut: TAction
      Category = 'Edit'
      Caption = 'Cu&t'
      Enabled = False
      ShortCut = 16472
      OnExecute = actEditCutExecute
      OnUpdate = actEditCutUpdate
    end
    object actEditCopy: TAction
      Category = 'Edit'
      Caption = '&Copy'
      Enabled = False
      ShortCut = 16451
      OnExecute = actEditCopyExecute
      OnUpdate = actEditCopyUpdate
    end
    object actEditPaste: TAction
      Category = 'Edit'
      Caption = '&Paste'
      Enabled = False
      ShortCut = 16470
      OnExecute = actEditPasteExecute
      OnUpdate = actEditPasteUpdate
    end
    object actEditDelete: TAction
      Category = 'Edit'
      Caption = 'De&lete'
      Enabled = False
      OnExecute = actEditDeleteExecute
      OnUpdate = actEditDeleteUpdate
    end
    object actEditUndo: TAction
      Category = 'Edit'
      Caption = '&Undo'
      Enabled = False
      ShortCut = 16474
      OnExecute = actEditUndoExecute
      OnUpdate = actEditUndoUpdate
    end
    object actEditRedo: TAction
      Category = 'Edit'
      Caption = '&Redo'
      Enabled = False
      ShortCut = 24666
      OnExecute = actEditRedoExecute
      OnUpdate = actEditRedoUpdate
    end
    object actEditSelectAll: TAction
      Category = 'Edit'
      Caption = 'Select &All'
      Enabled = False
      ShortCut = 16449
      OnExecute = actEditSelectAllExecute
      OnUpdate = actEditSelectAllUpdate
    end
    object actSearchFind: TAction
      Category = 'Search'
      Caption = '&Find...'
      Enabled = False
      ShortCut = 16454
      OnExecute = actSearchFindExecute
      OnUpdate = actSearchFindUpdate
    end
    object actSearchFindNext: TAction
      Category = 'Search'
      Caption = 'Find &Next'
      Enabled = False
      ShortCut = 114
      OnExecute = actSearchFindNextExecute
      OnUpdate = actSearchFindNextUpdate
    end
    object actSearchFindPrev: TAction
      Category = 'Search'
      Caption = 'Find &Previous'
      Enabled = False
      ShortCut = 8306
      OnExecute = actSearchFindPrevExecute
      OnUpdate = actSearchFindPrevUpdate
    end
    object actSearchReplace: TAction
      Category = 'Search'
      Caption = '&Replace...'
      Enabled = False
      ShortCut = 16456
      OnExecute = actSearchReplaceExecute
      OnUpdate = actSearchReplaceUpdate
    end
  end
  object dlgFileSave: TSaveDialog
    Options = [ofHideReadOnly, ofPathMustExist, ofEnableSizing]
    Left = 20
    Top = 68
  end
end
