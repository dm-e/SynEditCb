
#include <vcl.h>
#pragma hdrstop

#include "SynEditKeyCmds.h"
#include <Winapi.Windows.hpp>
#include "SynEditKeyConst.h"
#include "SynEditStrConst.h"
#include "d2c_sysrtti.h"

using namespace std;
using namespace d2c_system;
using namespace Syneditkeyconst;
using namespace Syneditstrconst;
using namespace Synedittypes;
using namespace System;
using namespace System::Classes;
using namespace System::Sysutils;

namespace Syneditkeycmds
{
#define Syneditkeycmds__1 TShiftState()
#define Syneditkeycmds__2 (TShiftState() << ssShift)
#define Syneditkeycmds__3 (TShiftState() << ssCtrl)
#define Syneditkeycmds__4 TShiftState()
#define Syneditkeycmds__5 (TShiftState() << ssShift)
#define Syneditkeycmds__6 (TShiftState() << ssCtrl)
#define Syneditkeycmds__7 TShiftState()
#define Syneditkeycmds__8 (TShiftState() << ssShift)
#define Syneditkeycmds__9 (TShiftState() << ssCtrl)
#define Syneditkeycmds__10 (TShiftState() << ssShift << ssCtrl)
#define Syneditkeycmds__11 TShiftState()
#define Syneditkeycmds__12 (TShiftState() << ssShift)
#define Syneditkeycmds__13 (TShiftState() << ssCtrl)
#define Syneditkeycmds__14 (TShiftState() << ssShift << ssCtrl)
#define Syneditkeycmds__15 TShiftState()
#define Syneditkeycmds__16 (TShiftState() << ssShift)
#define Syneditkeycmds__17 (TShiftState() << ssCtrl)
#define Syneditkeycmds__18 (TShiftState() << ssShift << ssCtrl)
#define Syneditkeycmds__19 TShiftState()
#define Syneditkeycmds__20 (TShiftState() << ssShift)
#define Syneditkeycmds__21 (TShiftState() << ssCtrl)
#define Syneditkeycmds__22 (TShiftState() << ssShift << ssCtrl)
#define Syneditkeycmds__23 TShiftState()
#define Syneditkeycmds__24 (TShiftState() << ssShift)
#define Syneditkeycmds__25 (TShiftState() << ssCtrl)
#define Syneditkeycmds__26 (TShiftState() << ssShift << ssCtrl)
#define Syneditkeycmds__27 TShiftState()
#define Syneditkeycmds__28 (TShiftState() << ssShift)
#define Syneditkeycmds__29 (TShiftState() << ssCtrl)
#define Syneditkeycmds__30 (TShiftState() << ssShift << ssCtrl)
#define Syneditkeycmds__31 TShiftState()
#define Syneditkeycmds__32 (TShiftState() << ssCtrl)
#define Syneditkeycmds__33 (TShiftState() << ssShift)
#define Syneditkeycmds__34 (TShiftState() << ssShift)
#define Syneditkeycmds__35 TShiftState()
#define Syneditkeycmds__36 TShiftState()
#define Syneditkeycmds__37 (TShiftState() << ssShift)
#define Syneditkeycmds__38 (TShiftState() << ssCtrl)
#define Syneditkeycmds__39 (TShiftState() << ssAlt)
#define Syneditkeycmds__40 (TShiftState() << ssAlt << ssShift)
#define Syneditkeycmds__41 TShiftState()
#define Syneditkeycmds__42 (TShiftState() << ssShift)
#define Syneditkeycmds__43 TShiftState()
#define Syneditkeycmds__44 (TShiftState() << ssShift)
#define Syneditkeycmds__45 TShiftState()
#define Syneditkeycmds__46 (TShiftState() << ssCtrl)
#define Syneditkeycmds__47 (TShiftState() << ssCtrl)
#define Syneditkeycmds__48 (TShiftState() << ssCtrl)
#define Syneditkeycmds__49 (TShiftState() << ssCtrl)
#define Syneditkeycmds__50 (TShiftState() << ssCtrl << ssShift)
#define Syneditkeycmds__51 (TShiftState() << ssCtrl << ssShift)
#define Syneditkeycmds__52 (TShiftState() << ssCtrl)
#define Syneditkeycmds__53 (TShiftState() << ssCtrl)
#define Syneditkeycmds__54 (TShiftState() << ssCtrl)
#define Syneditkeycmds__55 (TShiftState() << ssCtrl)
#define Syneditkeycmds__56 (TShiftState() << ssCtrl << ssShift)
#define Syneditkeycmds__57 (TShiftState() << ssCtrl)
#define Syneditkeycmds__58 (TShiftState() << ssCtrl << ssShift)
#define Syneditkeycmds__59 (TShiftState() << ssCtrl)
#define Syneditkeycmds__60 (TShiftState() << ssCtrl)
#define Syneditkeycmds__61 (TShiftState() << ssCtrl)
#define Syneditkeycmds__62 (TShiftState() << ssCtrl)
#define Syneditkeycmds__63 (TShiftState() << ssCtrl)
#define Syneditkeycmds__64 (TShiftState() << ssCtrl)
#define Syneditkeycmds__65 (TShiftState() << ssCtrl)
#define Syneditkeycmds__66 (TShiftState() << ssCtrl)
#define Syneditkeycmds__67 (TShiftState() << ssCtrl)
#define Syneditkeycmds__68 (TShiftState() << ssCtrl)
#define Syneditkeycmds__69 (TShiftState() << ssCtrl << ssShift)
#define Syneditkeycmds__70 (TShiftState() << ssCtrl << ssShift)
#define Syneditkeycmds__71 (TShiftState() << ssCtrl << ssShift)
#define Syneditkeycmds__72 (TShiftState() << ssCtrl << ssShift)
#define Syneditkeycmds__73 (TShiftState() << ssCtrl << ssShift)
#define Syneditkeycmds__74 (TShiftState() << ssCtrl << ssShift)
#define Syneditkeycmds__75 (TShiftState() << ssCtrl << ssShift)
#define Syneditkeycmds__76 (TShiftState() << ssCtrl << ssShift)
#define Syneditkeycmds__77 (TShiftState() << ssCtrl << ssShift)
#define Syneditkeycmds__78 (TShiftState() << ssCtrl << ssShift)
#define Syneditkeycmds__79 (TShiftState() << ssCtrl << ssShift)
#define Syneditkeycmds__80 (TShiftState() << ssCtrl << ssShift)
#define Syneditkeycmds__81 (TShiftState() << ssCtrl << ssShift)
#define Syneditkeycmds__82 (TShiftState() << ssCtrl << ssShift)
#define Syneditkeycmds__83 (TShiftState() << ssCtrl)
#define Syneditkeycmds__84 (TShiftState() << ssCtrl)
#define Syneditkeycmds__85 (TShiftState() << ssCtrl)
#define Syneditkeycmds__86 (TShiftState() << ssCtrl)
#define Syneditkeycmds__87 (TShiftState() << ssCtrl)
#define Syneditkeycmds__88 (TShiftState() << ssCtrl)
#define Syneditkeycmds__89 (TShiftState() << ssShift << ssAlt)
#define Syneditkeycmds__90 (TShiftState() << ssShift << ssAlt)
#define Syneditkeycmds__91 (TShiftState() << ssAlt)
#define Syneditkeycmds__92 (TShiftState() << ssAlt)
#define Syneditkeycmds__93 (TShiftState() << ssCtrl << ssShift)
#define Syneditkeycmds__94 (TShiftState() << ssCtrl << ssShift)
#define Syneditkeycmds__95 (TShiftState() << ssCtrl)
#define Syneditkeycmds__96 (TShiftState() << ssCtrl << ssShift)
#define Syneditkeycmds__97 (TShiftState() << ssCtrl)
#define Syneditkeycmds__98 (TShiftState() << ssCtrl)
#define Syneditkeycmds__99 (TShiftState() << ssCtrl)
#define Syneditkeycmds__100 (TShiftState() << ssCtrl)
#define Syneditkeycmds__101 (TShiftState() << ssCtrl)
#define Syneditkeycmds__102 (TShiftState() << ssCtrl)
#define Syneditkeycmds__103 (TShiftState() << ssCtrl << ssShift)
#define Syneditkeycmds__104 (TShiftState() << ssCtrl << ssShift)
#define Syneditkeycmds__105 (TShiftState() << ssCtrl << ssShift)
#define Syneditkeycmds__106 (TShiftState() << ssCtrl << ssShift)
#define Syneditkeycmds__107 (TShiftState() << ssCtrl << ssShift)
#define Syneditkeycmds__108 (TShiftState() << ssCtrl << ssShift)
#define Syneditkeycmds__109 (TSysCharSet() <<  \
          65 << 66 << 67 << 68 << 69 << 70 <<  \
          71 << 72 << 73 << 74 << 75 << 76 <<  \
          77 << 78 << 79 << 80 << 81 << 82 <<  \
          83 << 84 << 85 << 86 << 87 << 88 <<  \
          89 << 90 <<  \
          48 << 49 << 50 << 51 << 52 << 53 <<  \
          54 << 55 << 56 << 57)
#define Syneditkeycmds__110 (TSysCharSet() <<  \
          65 << 66 << 67 << 68 << 69 << 70 <<  \
          71 << 72 << 73 << 74 << 75 << 76 <<  \
          77 << 78 << 79 << 80 << 81 << 82 <<  \
          83 << 84 << 85 << 86 << 87 << 88 <<  \
          89 << 90 <<  \
          48 << 49 << 50 << 51 << 52 << 53 <<  \
          54 << 55 << 56 << 57)

__fastcall ESynKeyError::ESynKeyError(const String Msg) : inherited(Msg) {}
__fastcall ESynKeyError::ESynKeyError(const String Msg, const TVarRec* Args, int Args_maxidx) : inherited(Msg, Args, Args_maxidx) {}
__fastcall ESynKeyError::ESynKeyError(const String Msg, const TVarRec* Args, int Args_maxidx, int AHelpContext) : inherited(Msg, Args, Args_maxidx, AHelpContext) {}
__fastcall ESynKeyError::ESynKeyError(const String Msg, int AHelpContext) : inherited(Msg, AHelpContext) {}
__fastcall ESynKeyError::ESynKeyError(System::NativeUInt Ident) : inherited(Ident) {}
__fastcall ESynKeyError::ESynKeyError(System::PResStringRec ResStringRec) : inherited(ResStringRec) {}
__fastcall ESynKeyError::ESynKeyError(System::NativeUInt Ident, const TVarRec* Args, int Args_maxidx) : inherited(Ident, Args, Args_maxidx) {}
__fastcall ESynKeyError::ESynKeyError(System::PResStringRec ResStringRec, const TVarRec* Args, int Args_maxidx) : inherited(ResStringRec, Args, Args_maxidx) {}
__fastcall ESynKeyError::ESynKeyError(System::PResStringRec ResStringRec, const TVarRec* Args, int Args_maxidx, int AHelpContext) : inherited(ResStringRec, Args, Args_maxidx, AHelpContext) {}
__fastcall ESynKeyError::ESynKeyError(System::NativeUInt Ident, const TVarRec* Args, int Args_maxidx, int AHelpContext) : inherited(Ident, Args, Args_maxidx, AHelpContext) {}
__fastcall ESynKeyError::ESynKeyError(System::NativeUInt Ident, int AHelpContext) : inherited(Ident, AHelpContext) {}
__fastcall ESynKeyError::ESynKeyError(System::PResStringRec ResStringRec, int AHelpContext) : inherited(ResStringRec, AHelpContext) {}
__fastcall TSynEditKeyStroke::TSynEditKeyStroke(TCollection* Collection) : inherited(Collection) {}
__fastcall TSynEditKeyStrokes::TSynEditKeyStrokes(TCollectionItemClass ItemClass) : inherited(ItemClass) {}



/* Command mapping routines */
//++ CodeFolding
const TIdentMapEntry EditorCommandStrs[113/*# range 0..112*/] = {{ecNone, L"ecNone"}
                    ,                     {ecLeft, L"ecLeft"}
                    ,                     {ecRight, L"ecRight"}
                    ,                     {ecUp, L"ecUp"}
                    ,                     {ecDown, L"ecDown"}
                    ,                     {ecWordLeft, L"ecWordLeft"}
                    ,                     {ecWordRight, L"ecWordRight"}
                    ,                     {ecLineStart, L"ecLineStart"}
                    ,                     {ecLineEnd, L"ecLineEnd"}
                    ,                     {ecPageUp, L"ecPageUp"}
                    ,                     {ecPageDown, L"ecPageDown"}
                    ,                     {ecPageLeft, L"ecPageLeft"}
                    ,                     {ecPageRight, L"ecPageRight"}
                    ,                     {ecPageTop, L"ecPageTop"}
                    ,                     {ecPageBottom, L"ecPageBottom"}
                    ,                     {ecEditorTop, L"ecEditorTop"}
                    ,                     {ecEditorBottom, L"ecEditorBottom"}
                    ,                     {ecGotoXY, L"ecGotoXY"}
                    ,                     {ecSelLeft, L"ecSelLeft"}
                    ,                     {ecSelRight, L"ecSelRight"}
                    ,                     {ecSelUp, L"ecSelUp"}
                    ,                     {ecSelDown, L"ecSelDown"}
                    ,                     {ecSelWordLeft, L"ecSelWordLeft"}
                    ,                     {ecSelWordRight, L"ecSelWordRight"}
                    ,                     {ecSelLineStart, L"ecSelLineStart"}
                    ,                     {ecSelLineEnd, L"ecSelLineEnd"}
                    ,                     {ecSelPageUp, L"ecSelPageUp"}
                    ,                     {ecSelPageDown, L"ecSelPageDown"}
                    ,                     {ecSelPageLeft, L"ecSelPageLeft"}
                    ,                     {ecSelPageRight, L"ecSelPageRight"}
                    ,                     {ecSelPageTop, L"ecSelPageTop"}
                    ,                     {ecSelPageBottom, L"ecSelPageBottom"}
                    ,                     {ecSelEditorTop, L"ecSelEditorTop"}
                    ,                     {ecSelEditorBottom, L"ecSelEditorBottom"}
                    ,                     {ecSelGotoXY, L"ecSelGotoXY"}
                    ,                     {ecSelWord, L"ecSelWord"}
                    ,                     {ecSelectAll, L"ecSelectAll"}
                    ,                     {ecDeleteLastChar, L"ecDeleteLastChar"}
                    ,                     {ecDeleteChar, L"ecDeleteChar"}
                    ,                     {ecDeleteWord, L"ecDeleteWord"}
                    ,                     {ecDeleteLastWord, L"ecDeleteLastWord"}
                    ,                     {ecDeleteBOL, L"ecDeleteBOL"}
                    ,                     {ecDeleteEOL, L"ecDeleteEOL"}
                    ,                     {ecDeleteLine, L"ecDeleteLine"}
                    ,                     {ecClearAll, L"ecClearAll"}
                    ,                     {ecLineBreak, L"ecLineBreak"}
                    ,                     {ecInsertLine, L"ecInsertLine"}
                    ,                     {ecChar, L"ecChar"}
                    ,                     {ecImeStr, L"ecImeStr"}
                    ,                     {ecUndo, L"ecUndo"}
                    ,                     {ecRedo, L"ecRedo"}
                    ,                     {ecCut, L"ecCut"}
                    ,                     {ecCopy, L"ecCopy"}
                    ,                     {ecPaste, L"ecPaste"}
                    ,                     {ecScrollUp, L"ecScrollUp"}
                    ,                     {ecScrollDown, L"ecScrollDown"}
                    ,                     {ecScrollLeft, L"ecScrollLeft"}
                    ,                     {ecScrollRight, L"ecScrollRight"}
                    ,                     {ecInsertMode, L"ecInsertMode"}
                    ,                     {ecOverwriteMode, L"ecOverwriteMode"}
                    ,                     {ecToggleMode, L"ecToggleMode"}
                    ,                     {ecBlockIndent, L"ecBlockIndent"}
                    ,                     {ecBlockUnindent, L"ecBlockUnindent"}
                    ,                     {ecTab, L"ecTab"}
                    ,                     {ecShiftTab, L"ecShiftTab"}
                    ,                     {ecMatchBracket, L"ecMatchBracket"}
                    ,                     {ecCommentBlock, L"ecCommentBlock"}
                    ,                     {ecNormalSelect, L"ecNormalSelect"}
                    ,                     {ecColumnSelect, L"ecColumnSelect"}
                    ,                     {ecLineSelect, L"ecLineSelect"}
                    ,                     {ecAutoCompletion, L"ecAutoCompletion"}
                    ,                     {ecContextHelp, L"ecContextHelp"}
                    ,                     {ecGotoMarker0, L"ecGotoMarker0"}
                    ,                     {ecGotoMarker1, L"ecGotoMarker1"}
                    ,                     {ecGotoMarker2, L"ecGotoMarker2"}
                    ,                     {ecGotoMarker3, L"ecGotoMarker3"}
                    ,                     {ecGotoMarker4, L"ecGotoMarker4"}
                    ,                     {ecGotoMarker5, L"ecGotoMarker5"}
                    ,                     {ecGotoMarker6, L"ecGotoMarker6"}
                    ,                     {ecGotoMarker7, L"ecGotoMarker7"}
                    ,                     {ecGotoMarker8, L"ecGotoMarker8"}
                    ,                     {ecGotoMarker9, L"ecGotoMarker9"}
                    ,                     {ecSetMarker0, L"ecSetMarker0"}
                    ,                     {ecSetMarker1, L"ecSetMarker1"}
                    ,                     {ecSetMarker2, L"ecSetMarker2"}
                    ,                     {ecSetMarker3, L"ecSetMarker3"}
                    ,                     {ecSetMarker4, L"ecSetMarker4"}
                    ,                     {ecSetMarker5, L"ecSetMarker5"}
                    ,                     {ecSetMarker6, L"ecSetMarker6"}
                    ,                     {ecSetMarker7, L"ecSetMarker7"}
                    ,                     {ecSetMarker8, L"ecSetMarker8"}
                    ,                     {ecSetMarker9, L"ecSetMarker9"}
                    ,                     {ecUpperCase, L"ecUpperCase"}
                    ,                     {ecLowerCase, L"ecLowerCase"}
                    ,                     {ecToggleCase, L"ecToggleCase"}
                    ,                     {ecTitleCase, L"ecTitleCase"}
                    ,                     {ecCopyLineUp, L"ecCopyLineUp"}
                    ,                     {ecCopyLineDown, L"ecCopyLineDown"}
                    ,                     {ecMoveLineUp, L"ecMoveLineUp"}
                    ,                     {ecMoveLineDown, L"ecMoveLineDown"}
                    ,                     {ecString, L"ecString"}
//++ CodeFolding
                    ,                     {ecFoldAll, L"ecFoldAll"}
                    ,                     {ecUnfoldAll, L"ecUnfoldAll"}
                    ,                     {ecFoldNearest, L"ecFoldNearest"}
                    ,                     {ecUnfoldNearest, L"ecUnfoldNearest"}
                    ,                     {ecFoldLevel1, L"ecFoldLevel1"}
                    ,                     {ecFoldLevel2, L"ecFoldLevel2"}
                    ,                     {ecFoldLevel3, L"ecFoldLevel3"}
                    ,                     {ecUnfoldLevel1, L"ecUnfoldLevel1"}
                    ,                     {ecUnfoldLevel2, L"ecUnfoldLevel2"}
                    ,                     {ecUnfoldLevel3, L"ecUnfoldLevel3"}
                    ,                     {ecFoldRegions, L"ecFoldRanges"}
                    ,                     {ecUnfoldRegions, L"ecUnfoldRanges"}};
//-- CodeFolding

// GetEditorCommandValues and GetEditorCommandExtended for editing key assignments

void __fastcall GetEditorCommandValues(TGetStrProc Proc)
{
	int i = 0;
	int stop = 0;
	for(stop = 112 /*# High(EditorCommandStrs) */, i = 0 /*# Low(EditorCommandStrs) */; i <= stop; i++)
	{
		switch(EditorCommandStrs[i].Value)
		{
			case ecNone:
			case ecChar:
			case ecString:
			case ecImeStr:
			case ecGotoXY:
			case ecSelGotoXY:
			;
			break;// skip commands that cannot be used by the end-user
			default:
			Proc(EditorCommandStrs[i].Name);
			break;
		}
	}
}

void __fastcall GetEditorCommandExtended(TGetStrProc Proc)
{
	int i = 0;
	int stop = 0;
	for(stop = 112 /*# High(EditorCommandStrs) */, i = 0 /*# Low(EditorCommandStrs) */; i <= stop; i++)
	{
		switch(EditorCommandStrs[i].Value)
		{
			case ecNone:
			case ecChar:
			case ecString:
			case ecImeStr:
			case ecGotoXY:
			case ecSelGotoXY:
			;
			break;// skip commands that cannot be used by the end-user
			default:
			Proc(ConvertCodeStringToExtended(EditorCommandStrs[i].Name));
			break;
		}
	}
}

bool __fastcall IdentToEditorCommand(const String Ident, int& Cmd)
{
	bool result = false;
	result = IdentToInt(Ident, Cmd, EditorCommandStrs, 112);
	return result;
}

bool __fastcall EditorCommandToIdent(int Cmd, String& Ident)
{
	bool result = false;
	result = IntToIdent(Cmd, Ident, EditorCommandStrs, 112);
	return result;
}

String __fastcall EditorCommandToDescrString(TSynEditorCommand Cmd)
{
	String result;
  // Doesn't do anything yet.
	result = L"";
	return result;
}

String __fastcall EditorCommandToCodeString(TSynEditorCommand Cmd)
{
	String result;
	if(!EditorCommandToIdent((int) Cmd, result))
		result = IntToStr((int) Cmd);
	return result;
}

/* TSynEditKeyStroke */

void __fastcall TSynEditKeyStroke::Assign(TPersistent* Source)
{
	if(ObjectIs(Source, TSynEditKeyStroke*))
	{
		Command = ((TSynEditKeyStroke*) Source)->Command;
		Key = ((TSynEditKeyStroke*) Source)->Key;
		Key2 = ((TSynEditKeyStroke*) Source)->Key2;
		Shift = ((TSynEditKeyStroke*) Source)->Shift;
		Shift2 = ((TSynEditKeyStroke*) Source)->Shift2;
	}
	else
	inherited::Assign(Source);
}

String __fastcall TSynEditKeyStroke::GetDisplayName()
{
	String result;
	result = EditorCommandToCodeString(Command) + L" - " + ShortCutToText(ShortCut);
	if(ShortCut2 != 0)
		result = result + L" " + ShortCutToText(ShortCut2);
	if(result == L"")
		result = inherited::GetDisplayName();
	return result;
}

TShortCut __fastcall TSynEditKeyStroke::GetShortCut()
{
	TShortCut result = (TShortCut) 0;
	result = Menus::ShortCut(Key, Shift);
	return result;
}

void __fastcall TSynEditKeyStroke::SetCommand(TSynEditorCommand Value)
{
	if(Value != FCommand)
		FCommand = Value;
}

void __fastcall TSynEditKeyStroke::SetKey(WORD Value)
{
	if(Value != FKey)
		FKey = Value;
}

void __fastcall TSynEditKeyStroke::SetShift(const TShiftState Value)
{
	if(Value != FShift)
		FShift = Value;
}

void __fastcall TSynEditKeyStroke::SetShortCut(const TShortCut Value)
{
	WORD NewKey = 0;
	TShiftState NewShift;
	int Dup = 0;
  // Duplicate values of no shortcut are OK.
	if(Value != 0)
    // Check for duplicate shortcut in the collection and disallow if there is.
	{
		Dup = ((TSynEditKeyStrokes*) Collection)->FindShortcut2(Value, ShortCut2);
		if((Dup != -1) && (Dup != this->Index))
		{
			throw new ESynKeyError(SYNS_EDuplicateShortcut);
		}
	}
	Menus::ShortCutToKey(Value, NewKey, NewShift);
	if((NewKey != Key) || (NewShift != Shift))
	{
		Key = NewKey;
		Shift = NewShift;
	}
}

void __fastcall TSynEditKeyStroke::SetKey2(WORD Value)
{
	if(Value != FKey2)
		FKey2 = Value;
}

void __fastcall TSynEditKeyStroke::SetShift2(const TShiftState Value)
{
	if(Value != FShift2)
		FShift2 = Value;
}

void __fastcall TSynEditKeyStroke::SetShortCut2(const TShortCut Value)
{
	WORD NewKey = 0;
	TShiftState NewShift;
	int Dup = 0;
  // Duplicate values of no shortcut are OK.
	if(Value != 0)
    // Check for duplicate shortcut in the collection and disallow if there is.
	{
		Dup = ((TSynEditKeyStrokes*) Collection)->FindShortcut2(ShortCut, Value);
		if((Dup != -1) && (Dup != this->Index))
			throw new ESynKeyError(SYNS_EDuplicateShortcut);
	}
	Menus::ShortCutToKey(Value, NewKey, NewShift);
	if((NewKey != Key2) || (NewShift != Shift2))
	{
		Key2 = NewKey;
		Shift2 = NewShift;
	}
}

TShortCut __fastcall TSynEditKeyStroke::GetShortCut2()
{
	TShortCut result = (TShortCut) 0;
	result = Menus::ShortCut(Key2, Shift2);
	return result;
}

void __fastcall TSynEditKeyStroke::LoadFromStream(TStream* AStream)
{
	/*# with AStream do */
	{
		auto with0 = AStream;
		with0->Read((void**)&FKey, sizeof(FKey));
		with0->Read((void**)&FShift, sizeof(FShift));
		with0->Read((void**)&FKey2, sizeof(FKey2));
		with0->Read((void**)&FShift2, sizeof(FShift2));
		with0->Read((void**)&FCommand, sizeof(FCommand));
	}
}

void __fastcall TSynEditKeyStroke::SaveToStream(TStream* AStream)
{
	/*# with AStream do */
	{
		auto with0 = AStream;
		with0->Write(&FKey, sizeof(FKey));
		with0->Write(&FShift, sizeof(FShift));
		with0->Write(&FKey2, sizeof(FKey2));
		with0->Write(&FShift2, sizeof(FShift2));
		with0->Write(&FCommand, sizeof(FCommand));
	}
}


/* TSynEditKeyStrokes */

TSynEditKeyStroke* __fastcall TSynEditKeyStrokes::Add()
{
	TSynEditKeyStroke* result = nullptr;
	result = ((TSynEditKeyStroke*) inherited::Add());
	return result;
}

//++ CodeFolding

void __fastcall TSynEditKeyStrokes::AddKey(TSynEditorCommand ACmd, WORD AKey, const TShiftState AShift, WORD AKey2/*# = 0*/, const TShiftState AShift2/*# = []*/)
{
	TSynEditKeyStroke* NewKeystroke = nullptr;
	NewKeystroke = Add();
	try
	{
		NewKeystroke->Key = AKey;
		NewKeystroke->Shift = AShift;
		NewKeystroke->Key2 = AKey2;
		NewKeystroke->Shift2 = AShift2;
		NewKeystroke->Command = ACmd;
	}
	catch(...)
	{
		delete NewKeystroke;
		throw ;
	}
}
//-- CodeFolding

void __fastcall TSynEditKeyStrokes::Assign(TPersistent* Source)
{
	int x = 0;
	if(ObjectIs(Source, TSynEditKeyStrokes*))
	{
		int stop = 0;
		Clear();
		for(stop = ((TSynEditKeyStrokes*) Source)->Count - 1, x = 0; x <= stop; x++)
		{
			/*# with Add do */
			{
				auto with0 = Add();
				with0->Assign(((TSynEditKeyStrokes*) Source)->Items[x]);
			}
		}
	}
	else
	inherited::Assign(Source);
}

__fastcall TSynEditKeyStrokes::TSynEditKeyStrokes(TPersistent* AOwner)
 : inherited(__classid(TSynEditKeyStroke)),
			FOwner(AOwner)
{
}

int __fastcall TSynEditKeyStrokes::FindCommand(TSynEditorCommand Cmd)
{
	int result = 0;
	int x = 0;
	int stop = 0;
	result = -1;
	for(stop = Count - 1, x = 0; x <= stop; x++)
	{
		if(Items[x]->Command == Cmd)
		{
			result = x;
			break;
		}
	}
	return result;
}

int __fastcall TSynEditKeyStrokes::FindKeycode(WORD Code, TShiftState SS)
{
	int result = 0;
	int x = 0;
	int stop = 0;
	result = -1;
	for(stop = Count - 1, x = 0; x <= stop; x++)
	{
		if((Items[x]->Key == Code) && (Items[x]->Shift == SS) && (Items[x]->Key2 == 0))
		{
			result = x;
			break;
		}
	}
	return result;
}

int __fastcall TSynEditKeyStrokes::FindKeycode2(WORD Code1, TShiftState SS1, WORD Code2, TShiftState SS2)
{
	int result = 0;
	int x = 0;
	int stop = 0;
	result = -1;
	for(stop = Count - 1, x = 0; x <= stop; x++)
	{
		if((Items[x]->Key == Code1) && (Items[x]->Shift == SS1) && (Items[x]->Key2 == Code2) && (Items[x]->Shift2 == SS2))
		{
			result = x;
			break;
		}
	}
	return result;
}

int __fastcall TSynEditKeyStrokes::FindShortcut(TShortCut SC)
{
	int result = 0;
	int x = 0;
	int stop = 0;
	result = -1;
	for(stop = Count - 1, x = 0; x <= stop; x++)
	{
		if(Items[x]->ShortCut == SC)
		{
			result = x;
			break;
		}
	}
	return result;
}

int __fastcall TSynEditKeyStrokes::FindShortcut2(TShortCut SC, TShortCut SC2)
{
	int result = 0;
	int x = 0;
	int stop = 0;
	result = -1;
	for(stop = Count - 1, x = 0; x <= stop; x++)
	{
		if((Items[x]->ShortCut == SC) && (Items[x]->ShortCut2 == SC2))
		{
			result = x;
			break;
		}
	}
	return result;
}

TSynEditKeyStroke* __fastcall TSynEditKeyStrokes::GetItem(int Index)
{
	TSynEditKeyStroke* result = nullptr;
	result = ((TSynEditKeyStroke*) inherited::GetItem(Index));
	return result;
}

TPersistent* __fastcall TSynEditKeyStrokes::GetOwner()
{
	TPersistent* result = nullptr;
	result = FOwner;
	return result;
}

void __fastcall TSynEditKeyStrokes::LoadFromStream(TStream* AStream)
{
	int Num = 0;
	Clear();
	AStream->Read((void**)&Num, sizeof(Num));
	while(Num > 0)
	{
		/*# with Add do */
		{
			auto with0 = Add();
			with0->LoadFromStream(AStream);
		}
		--Num;
	}
}

void __fastcall TSynEditKeyStrokes::ResetDefaults()
{
	Clear();
	AddKey((TSynEditorCommand) ecUp, SYNEDIT_UP, Syneditkeycmds__1);
	AddKey((TSynEditorCommand) ecSelUp, SYNEDIT_UP, Syneditkeycmds__2);
	AddKey((TSynEditorCommand) ecScrollUp, SYNEDIT_UP, Syneditkeycmds__3);
	AddKey((TSynEditorCommand) ecDown, SYNEDIT_DOWN, Syneditkeycmds__4);
	AddKey((TSynEditorCommand) ecSelDown, SYNEDIT_DOWN, Syneditkeycmds__5);
	AddKey((TSynEditorCommand) ecScrollDown, SYNEDIT_DOWN, Syneditkeycmds__6);
	AddKey((TSynEditorCommand) ecLeft, SYNEDIT_LEFT, Syneditkeycmds__7);
	AddKey((TSynEditorCommand) ecSelLeft, SYNEDIT_LEFT, Syneditkeycmds__8);
	AddKey((TSynEditorCommand) ecWordLeft, SYNEDIT_LEFT, Syneditkeycmds__9);
	AddKey((TSynEditorCommand) ecSelWordLeft, SYNEDIT_LEFT, Syneditkeycmds__10);
	AddKey((TSynEditorCommand) ecRight, SYNEDIT_RIGHT, Syneditkeycmds__11);
	AddKey((TSynEditorCommand) ecSelRight, SYNEDIT_RIGHT, Syneditkeycmds__12);
	AddKey((TSynEditorCommand) ecWordRight, SYNEDIT_RIGHT, Syneditkeycmds__13);
	AddKey((TSynEditorCommand) ecSelWordRight, SYNEDIT_RIGHT, Syneditkeycmds__14);
	AddKey((TSynEditorCommand) ecPageDown, SYNEDIT_NEXT, Syneditkeycmds__15);
	AddKey((TSynEditorCommand) ecSelPageDown, SYNEDIT_NEXT, Syneditkeycmds__16);
	AddKey((TSynEditorCommand) ecPageBottom, SYNEDIT_NEXT, Syneditkeycmds__17);
	AddKey((TSynEditorCommand) ecSelPageBottom, SYNEDIT_NEXT, Syneditkeycmds__18);
	AddKey((TSynEditorCommand) ecPageUp, SYNEDIT_PRIOR, Syneditkeycmds__19);
	AddKey((TSynEditorCommand) ecSelPageUp, SYNEDIT_PRIOR, Syneditkeycmds__20);
	AddKey((TSynEditorCommand) ecPageTop, SYNEDIT_PRIOR, Syneditkeycmds__21);
	AddKey((TSynEditorCommand) ecSelPageTop, SYNEDIT_PRIOR, Syneditkeycmds__22);
	AddKey((TSynEditorCommand) ecLineStart, SYNEDIT_HOME, Syneditkeycmds__23);
	AddKey((TSynEditorCommand) ecSelLineStart, SYNEDIT_HOME, Syneditkeycmds__24);
	AddKey((TSynEditorCommand) ecEditorTop, SYNEDIT_HOME, Syneditkeycmds__25);
	AddKey((TSynEditorCommand) ecSelEditorTop, SYNEDIT_HOME, Syneditkeycmds__26);
	AddKey((TSynEditorCommand) ecLineEnd, SYNEDIT_END, Syneditkeycmds__27);
	AddKey((TSynEditorCommand) ecSelLineEnd, SYNEDIT_END, Syneditkeycmds__28);
	AddKey((TSynEditorCommand) ecEditorBottom, SYNEDIT_END, Syneditkeycmds__29);
	AddKey((TSynEditorCommand) ecSelEditorBottom, SYNEDIT_END, Syneditkeycmds__30);
	AddKey((TSynEditorCommand) ecToggleMode, SYNEDIT_INSERT, Syneditkeycmds__31);
	AddKey((TSynEditorCommand) ecCopy, SYNEDIT_INSERT, Syneditkeycmds__32);
	AddKey((TSynEditorCommand) ecCut, SYNEDIT_DELETE, Syneditkeycmds__33);
	AddKey((TSynEditorCommand) ecPaste, SYNEDIT_INSERT, Syneditkeycmds__34);
	AddKey((TSynEditorCommand) ecDeleteChar, SYNEDIT_DELETE, Syneditkeycmds__35);
	AddKey((TSynEditorCommand) ecDeleteLastChar, SYNEDIT_BACK, Syneditkeycmds__36);
	AddKey((TSynEditorCommand) ecDeleteBOL, SYNEDIT_BACK, Syneditkeycmds__37);
	AddKey((TSynEditorCommand) ecDeleteLastWord, SYNEDIT_BACK, Syneditkeycmds__38);
	AddKey((TSynEditorCommand) ecUndo, SYNEDIT_BACK, Syneditkeycmds__39);
	AddKey((TSynEditorCommand) ecRedo, SYNEDIT_BACK, Syneditkeycmds__40);
	AddKey((TSynEditorCommand) ecLineBreak, SYNEDIT_RETURN, Syneditkeycmds__41);
	AddKey((TSynEditorCommand) ecLineBreak, SYNEDIT_RETURN, Syneditkeycmds__42);
	AddKey((TSynEditorCommand) ecTab, SYNEDIT_TAB, Syneditkeycmds__43);
	AddKey((TSynEditorCommand) ecShiftTab, SYNEDIT_TAB, Syneditkeycmds__44);
	AddKey((TSynEditorCommand) ecContextHelp, SYNEDIT_F1, Syneditkeycmds__45);
	AddKey((TSynEditorCommand) ecSelectAll, (WORD) int(L'A'), Syneditkeycmds__46);
	AddKey((TSynEditorCommand) ecCopy, (WORD) int(L'C'), Syneditkeycmds__47);
	AddKey((TSynEditorCommand) ecPaste, (WORD) int(L'V'), Syneditkeycmds__48);
	AddKey((TSynEditorCommand) ecCut, (WORD) int(L'X'), Syneditkeycmds__49);
	AddKey((TSynEditorCommand) ecBlockIndent, (WORD) int(L'I'), Syneditkeycmds__50);
	AddKey((TSynEditorCommand) ecBlockUnindent, (WORD) int(L'U'), Syneditkeycmds__51);
	AddKey((TSynEditorCommand) ecLineBreak, (WORD) int(L'M'), Syneditkeycmds__52);
	AddKey((TSynEditorCommand) ecInsertLine, (WORD) int(L'N'), Syneditkeycmds__53);
	AddKey((TSynEditorCommand) ecDeleteWord, (WORD) int(L'T'), Syneditkeycmds__54);
	AddKey((TSynEditorCommand) ecDeleteLine, (WORD) int(L'Y'), Syneditkeycmds__55);
	AddKey((TSynEditorCommand) ecDeleteEOL, (WORD) int(L'Y'), Syneditkeycmds__56);
	AddKey((TSynEditorCommand) ecUndo, (WORD) int(L'Z'), Syneditkeycmds__57);
	AddKey((TSynEditorCommand) ecRedo, (WORD) int(L'Z'), Syneditkeycmds__58);
	AddKey((TSynEditorCommand) ecGotoMarker0, (WORD) int(L'0'), Syneditkeycmds__59);
	AddKey((TSynEditorCommand) ecGotoMarker1, (WORD) int(L'1'), Syneditkeycmds__60);
	AddKey((TSynEditorCommand) ecGotoMarker2, (WORD) int(L'2'), Syneditkeycmds__61);
	AddKey((TSynEditorCommand) ecGotoMarker3, (WORD) int(L'3'), Syneditkeycmds__62);
	AddKey((TSynEditorCommand) ecGotoMarker4, (WORD) int(L'4'), Syneditkeycmds__63);
	AddKey((TSynEditorCommand) ecGotoMarker5, (WORD) int(L'5'), Syneditkeycmds__64);
	AddKey((TSynEditorCommand) ecGotoMarker6, (WORD) int(L'6'), Syneditkeycmds__65);
	AddKey((TSynEditorCommand) ecGotoMarker7, (WORD) int(L'7'), Syneditkeycmds__66);
	AddKey((TSynEditorCommand) ecGotoMarker8, (WORD) int(L'8'), Syneditkeycmds__67);
	AddKey((TSynEditorCommand) ecGotoMarker9, (WORD) int(L'9'), Syneditkeycmds__68);
	AddKey((TSynEditorCommand) ecSetMarker0, (WORD) int(L'0'), Syneditkeycmds__69);
	AddKey((TSynEditorCommand) ecSetMarker1, (WORD) int(L'1'), Syneditkeycmds__70);
	AddKey((TSynEditorCommand) ecSetMarker2, (WORD) int(L'2'), Syneditkeycmds__71);
	AddKey((TSynEditorCommand) ecSetMarker3, (WORD) int(L'3'), Syneditkeycmds__72);
	AddKey((TSynEditorCommand) ecSetMarker4, (WORD) int(L'4'), Syneditkeycmds__73);
	AddKey((TSynEditorCommand) ecSetMarker5, (WORD) int(L'5'), Syneditkeycmds__74);
	AddKey((TSynEditorCommand) ecSetMarker6, (WORD) int(L'6'), Syneditkeycmds__75);
	AddKey((TSynEditorCommand) ecSetMarker7, (WORD) int(L'7'), Syneditkeycmds__76);
	AddKey((TSynEditorCommand) ecSetMarker8, (WORD) int(L'8'), Syneditkeycmds__77);
	AddKey((TSynEditorCommand) ecSetMarker9, (WORD) int(L'9'), Syneditkeycmds__78);
	AddKey((TSynEditorCommand) ecNormalSelect, (WORD) int(L'N'), Syneditkeycmds__79);
	AddKey((TSynEditorCommand) ecColumnSelect, (WORD) int(L'C'), Syneditkeycmds__80);
	AddKey((TSynEditorCommand) ecLineSelect, (WORD) int(L'L'), Syneditkeycmds__81);
	AddKey((TSynEditorCommand) ecMatchBracket, (WORD) int(L'B'), Syneditkeycmds__82);
	AddKey((TSynEditorCommand) ecLowerCase, (WORD) int(L'K'), Syneditkeycmds__83, (WORD) int(L'L'), Syneditkeycmds__84);
	AddKey((TSynEditorCommand) ecUpperCase, (WORD) int(L'K'), Syneditkeycmds__85, (WORD) int(L'U'), Syneditkeycmds__86);
	AddKey((TSynEditorCommand) ecTitleCase, (WORD) int(L'K'), Syneditkeycmds__87, (WORD) int(L'T'), Syneditkeycmds__88);
	AddKey((TSynEditorCommand) ecCopyLineUp, SYNEDIT_UP, Syneditkeycmds__89);
	AddKey((TSynEditorCommand) ecCopyLineDown, SYNEDIT_DOWN, Syneditkeycmds__90);
	AddKey((TSynEditorCommand) ecMoveLineUp, SYNEDIT_UP, Syneditkeycmds__91);
	AddKey((TSynEditorCommand) ecMoveLineDown, SYNEDIT_DOWN, Syneditkeycmds__92);
//++ CodeFolding
	AddKey((TSynEditorCommand) ecFoldAll, (WORD) VK_OEM_MINUS, Syneditkeycmds__93);   /*- _*/
	AddKey((TSynEditorCommand) ecUnfoldAll, (WORD) VK_OEM_PLUS, Syneditkeycmds__94); /*= +*/
	AddKey((TSynEditorCommand) ecFoldNearest, (WORD) VK_OEM_2, Syneditkeycmds__95);  // Divide {'/'}
	AddKey((TSynEditorCommand) ecUnfoldNearest, (WORD) VK_OEM_2, Syneditkeycmds__96);
	AddKey((TSynEditorCommand) ecFoldLevel1, (WORD) int(L'K'), Syneditkeycmds__97, (WORD) int(L'1'), Syneditkeycmds__98);
	AddKey((TSynEditorCommand) ecFoldLevel2, (WORD) int(L'K'), Syneditkeycmds__99, (WORD) int(L'2'), Syneditkeycmds__100);
	AddKey((TSynEditorCommand) ecFoldLevel3, (WORD) int(L'K'), Syneditkeycmds__101, (WORD) int(L'3'), Syneditkeycmds__102);
	AddKey((TSynEditorCommand) ecUnfoldLevel1, (WORD) int(L'K'), Syneditkeycmds__103, (WORD) int(L'1'), Syneditkeycmds__104);
	AddKey((TSynEditorCommand) ecUnfoldLevel2, (WORD) int(L'K'), Syneditkeycmds__105, (WORD) int(L'2'), Syneditkeycmds__106);
	AddKey((TSynEditorCommand) ecUnfoldLevel3, (WORD) int(L'K'), Syneditkeycmds__107, (WORD) int(L'3'), Syneditkeycmds__108);
//-- CodeFolding
}

void __fastcall TSynEditKeyStrokes::SetItem(int Index, TSynEditKeyStroke* Value)
{
	inherited::SetItem(Index, Value);
}

void __fastcall TSynEditKeyStrokes::SaveToStream(TStream* AStream)
{
	int i = 0;
	int Num = 0;
	int stop = 0;
	Num = Count;
	AStream->Write(&Num, sizeof(Num));
	for(stop = Num - 1, i = 0; i <= stop; i++)
	{
		Items[i]->SaveToStream(AStream);
	}
}

String __fastcall ConvertCodeStringToExtended(String AString)
{
	String result;
	int i = 0;
	String WorkStr;
	if(Pos(L"ec", AString) == 1)
	{
		int stop = 0;
		AString.Delete(1, 	2);
		WorkStr = L"";
		for(stop = 1, i = AString.Length(); i >= stop; i--)
		{
			if(CharInSet(AString[i], Syneditkeycmds__109) && (i > 1) && !CharInSet(AString[i - 1], Syneditkeycmds__110))
			{
				WorkStr = String(L" ") + AString[i] + WorkStr;
			}
			else
			WorkStr = String(AString[i]) + WorkStr;
		}
		Trim(WorkStr);
		i = Pos(L"Sel ", WorkStr);
		while(i != 0)
		{
			WorkStr.Delete(i, wcslen(	L"Sel "));
			WorkStr.Insert(L"Select ",	i);
			i = Pos(L"Sel ", WorkStr);
		}
		i = Pos(L"Marker ", WorkStr);
		while(i != 0)
		{
			WorkStr.Delete(i, wcslen(	L"Marker "));
			WorkStr.Insert(L"Bookmark ",	i);
			i = Pos(L"Marker ", WorkStr);
		}
		result = Trim(WorkStr);
	}
	else
	result = AString;
	return result;
}

String __fastcall ConvertExtendedToCodeString(String AString)
{
	String result;
	int i = 0;
	String WorkStr;
	if(Pos(L"ec", AString) == 1)
	{
		result = AString;
		return result;
	}
	WorkStr = AString;
	i = Pos(L"Select All", WorkStr);
	if(i == 0)
	{
		i = Pos(L"Select ", WorkStr);
		while(i != 0)
		{
			WorkStr.Delete(i, wcslen(	L"Select "));
			WorkStr.Insert(L"Sel ",	i);
			i = Pos(L"Select ", WorkStr);
		}
	}
	i = Pos(L"Bookmark ", WorkStr);
	while(i != 0)
	{
		WorkStr.Delete(i, wcslen(	L"Bookmark "));
		WorkStr.Insert(L"Marker ",	i);
		i = Pos(L"Bookmark ", WorkStr);
	}
	i = Pos(L" ", WorkStr);
	while(i != 0)
	{
		WorkStr.Delete(i, 	1);
		i = Pos(L" ", WorkStr);
	}
	result = String(L"ec") + WorkStr;
	return result;
}

int __fastcall IndexToEditorCommand(int AIndex)
{
	int result = 0;
	result = EditorCommandStrs[AIndex].Value;
	return result;
}

TSynEditorCommand __fastcall ConvertExtendedToCommand(String AString)
{
	TSynEditorCommand result = 0;
	result = ConvertCodeStringToCommand(ConvertExtendedToCodeString(AString));
	return result;
}

TSynEditorCommand __fastcall ConvertCodeStringToCommand(String AString)
{
	TSynEditorCommand result = 0;
	int I = 0;
	int stop = 0;
	result = (TSynEditorCommand) ecNone;
	AString = UpperCase(AString);
	for(stop = 112 /*# High(EditorCommandStrs) */, I = 0 /*# Low(EditorCommandStrs) */; I <= stop; I++)
	{
		if(UpperCase(EditorCommandStrs[I].Name) == AString)
		{
			result = (TSynEditorCommand) EditorCommandStrs[I].Value;
			break;
		}
	}
	return result;
}

	static bool SynEditKeyCmds_Initialized = false;
	
	void SynEditKeyCmds_initialization()
	{
		if(SynEditKeyCmds_Initialized)
			return;
		
		SynEditKeyCmds_Initialized = true;
		
		RegisterIntegerConsts(TypeInfo<TSynEditorCommand>(), IdentToEditorCommand, EditorCommandToIdent);
	}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynEditKeyCmds

