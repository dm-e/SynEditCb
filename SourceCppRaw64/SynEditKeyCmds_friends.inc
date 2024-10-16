
friend class ESynKeyError;
friend class TSynEditKeyStroke;
friend class TSynEditKeyStrokes;
friend Synedittypes::TSynEditorCommand __fastcall ConvertCodeStringToCommand(String AString);
friend String __fastcall ConvertCodeStringToExtended(String AString);
friend String __fastcall ConvertExtendedToCodeString(String AString);
friend Synedittypes::TSynEditorCommand __fastcall ConvertExtendedToCommand(String AString);
friend String __fastcall EditorCommandToCodeString(Synedittypes::TSynEditorCommand Cmd);
friend String __fastcall EditorCommandToDescrString(Synedittypes::TSynEditorCommand Cmd);
friend bool __fastcall EditorCommandToIdent(int Cmd, String& Ident);
friend void __fastcall GetEditorCommandExtended(TGetStrProc Proc);
friend void __fastcall GetEditorCommandValues(TGetStrProc Proc);
friend bool __fastcall IdentToEditorCommand(const String Ident, int& Cmd);
friend int __fastcall IndexToEditorCommand(int AIndex);
friend void SynEditKeyCmds_initialization();
