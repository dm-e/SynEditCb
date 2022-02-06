#include <vcl.h>
#pragma hdrstop

#include "SynEditAutoComplete.h"
#include <System.SysUtils.hpp>
#include "SynEditDelphiInstances.hpp"

using namespace std;
using namespace d2c_system;
using namespace Synedit;
using namespace Syneditkeycmds;
using namespace Synedittypes;
using namespace System;
using namespace System::Classes;
using namespace System::Sysutils;

namespace Syneditautocomplete
{

__fastcall TSynAutoComplete::TSynAutoComplete(System::Classes::TComponent* AOwner) : inherited(AOwner) {}



/* TCustomSynAutoComplete */

void __fastcall TCustomSynAutoComplete::AddCompletion(const String AToken, const String AValue, const String AComment)
{
	if(AToken != L"")
	{
		if((fAutoCompleteList->Count == 0) && (fCompletions->Count == 0))
			fParsed = true;
		fCompletions->Add(AToken);
		fCompletionComments->Add(AComment);
		fCompletionValues->Add(AValue);
	}
}

bool __fastcall TCustomSynAutoComplete::AddEditor(TCustomSynEdit* AEditor)
{
	bool result = false;
	int i = 0;
	if(AEditor != nullptr)
	{
		i = fEditors->IndexOf(AEditor);
		if(i ==  - 1)
		{
			AEditor->FreeNotification(this);
			fEditors->Add(AEditor);
			AEditor->RegisterCommandHandler(SynEditCommandHandler, nullptr);
		}
		result = true;
	}
	else
	result = false;
	return result;
}

void __fastcall TCustomSynAutoComplete::CompletionListChanged(TObject* Sender)
{
	fParsed = false;
}

__fastcall TCustomSynAutoComplete::TCustomSynAutoComplete(TComponent* AOwner)
 : inherited(AOwner),
			fAutoCompleteList(new TStringList()),
			fCompletions(new TStringList()),
			fCompletionComments(new TStringList()),
			fCompletionValues(new TStringList()),
			FEditor(nullptr),
			fEditors(nullptr),
			FCaseSensitive(false),
			fParsed(false)
{
	((TStringList*) fAutoCompleteList)->OnChange = CompletionListChanged;
	fEditors = new System::Classes::TList();
	fEOTokenChars = L"()[]{}.";
}

__fastcall TCustomSynAutoComplete::~TCustomSynAutoComplete()
{
	Editor = nullptr;
	while(EditorCount > 0)
		RemoveEditor(((TCustomSynEdit*) fEditors->Last()));
	//# inherited::Destroy();
	delete fEditors;
	delete fCompletions;
	delete fCompletionComments;
	delete fCompletionValues;
	delete fAutoCompleteList;
}


void __fastcall TCustomSynAutoComplete::DefineProperties(TFiler* Filer)
{
	inherited::DefineProperties(Filer);
}

void __fastcall TCustomSynAutoComplete::Execute(TCustomSynEdit* AEditor)
{
	String s;
	int i = 0;
	int j = 0;
	if(AEditor != nullptr)
    // get token
	{
		s = AEditor->LineText;
		j = AEditor->CaretX;
		i = j - 1;
		if(i <= s.Length())
		{
			while((i > 0) && (s[i] > L' ') && (Pos(s[i], fEOTokenChars) == 0))
				--i;
			++i;
			s = s.SubString(i, j - i);
			ExecuteCompletion(s, AEditor);
		}
	}
}

void __fastcall TCustomSynAutoComplete::ExecuteCompletion(const String AToken, TCustomSynEdit* AEditor)
{
	int i = 0;
	int j = 0;
	int Len = 0;
	int IndentLen = 0;
	String s;
	int IdxMaybe = 0;
	int NumMaybe = 0;
	TBufferCoord P = {};
	bool NewCaretPos = false;
	TStringList* Temp = nullptr;
	if(!fParsed)
		ParseCompletionList();
	Len = (int) AToken.Length();
	if((Len > 0) && (AEditor != nullptr) && !AEditor->ReadOnly && (fCompletions->Count > 0))
    // find completion for this token - not all chars necessary if unambiguous
	{
		i = fCompletions->Count - 1;
		IdxMaybe = -1;
		NumMaybe = 0;
		if(FCaseSensitive)
		{
			while(i >  - 1)
			{
				s = fCompletions->Strings[i];
				if(CompareStr(s, AToken) == 0)
					break;
				else
				{
					if(CompareStr(s.SubString(1, Len), AToken) == 0)
					{
						++NumMaybe;
						IdxMaybe = i;
					}
				}
				--i;
			}
		}
		else
		{
			while(i >  - 1)
			{
				s = fCompletions->Strings[i];
				if(CompareText(s, AToken) == 0)
					break;
				else
				{
					if(CompareText(s.SubString(1, Len), AToken) == 0)
					{
						++NumMaybe;
						IdxMaybe = i;
					}
				}
				--i;
			}
		}
		if((i ==  - 1) && (NumMaybe == 1))
			i = IdxMaybe;
		if(i >  - 1)
      // select token in editor
		{
			P = AEditor->CaretXY;
			AEditor->BeginUpdate();
			try
			{
				AEditor->BlockBegin = BufferCoord(P.Char - Len, P.Line);
				AEditor->BlockEnd = P;
        // indent the completion string if necessary, determine the caret pos
				IndentLen = P.Char - Len - 1;
				P = AEditor->BlockBegin;
				NewCaretPos = false;
				Temp = new TStringList();
				try
				{
					int stop = 0;
					Temp->Text = fCompletionValues->Strings[i];
          // indent lines
					if((IndentLen > 0) && (Temp->Count > 1))
					{
						int stop = 0;
						s = StringOfChar(L' ', IndentLen);
						for(stop = Temp->Count - 1, i = 1; i <= stop; i++)
						{
							Temp->Strings[i] = s + Temp->Strings[i];
						}
					}
          // find first '|' and use it as caret position
					for(stop = Temp->Count - 1, i = 0; i <= stop; i++)
					{
						s = Temp->Strings[i];
						j = Pos(L"|", s);
						if(j > 0)
						{
							s.Delete(j, 	1);
							Temp->Strings[i] = s;
//              if j > 1 then
//                Dec(j);
							NewCaretPos = true;
							P.Line += i;
							if(i == 0)
//                Inc(p.x, j)
								P.Char += j - 1;
							else
								P.Char = j;
							break;
						}
					}
					s = Temp->Text;
          // strip the trailing #13#10 that was appended by the stringlist
					i = (int) s.Length();
					if((i >= 2) && (s[i - 1] == L'\x0d') && (s[i] == L'\x0a'))
						s.SetLength(i - 2);
				}
				__finally
				{
					delete Temp;
				}
        // replace the selected text and position the caret
				AEditor->SelText = s;
				if(NewCaretPos)
					AEditor->CaretXY = P;
			}
			__finally
			{
				AEditor->EndUpdate();
			}
		}
	}
}

TStrings* __fastcall TCustomSynAutoComplete::GetCompletions()
{
	TStrings* result = nullptr;
	if(!fParsed)
		ParseCompletionList();
	result = fCompletions;
	return result;
}

TStrings* __fastcall TCustomSynAutoComplete::GetCompletionComments()
{
	TStrings* result = nullptr;
	if(!fParsed)
		ParseCompletionList();
	result = fCompletionComments;
	return result;
}

TStrings* __fastcall TCustomSynAutoComplete::GetCompletionValues()
{
	TStrings* result = nullptr;
	if(!fParsed)
		ParseCompletionList();
	result = fCompletionValues;
	return result;
}

int __fastcall TCustomSynAutoComplete::GetEditorCount()
{
	int result = 0;
	result = fEditors->Count;
	return result;
}

TCustomSynEdit* __fastcall TCustomSynAutoComplete::GetNthEditor(int Index)
{
	TCustomSynEdit* result = nullptr;
	if((Index >= 0) && (Index < fEditors->Count))
		result = ((TCustomSynEdit*) fEditors->Items[Index]);
	else
		result = nullptr;
	return result;
}

void __fastcall TCustomSynAutoComplete::Notification(TComponent* AComponent, TOperation Operation)
{
	inherited::Notification(AComponent, Operation);
	if(Operation == opRemove)
	{
		if(AComponent == Editor)
			Editor = nullptr;
		else
		{
			if(ObjectIs(AComponent, TCustomSynEdit*))
				RemoveEditor(((TCustomSynEdit*) AComponent));
		}
	}
}

void __fastcall TCustomSynAutoComplete::ParseCompletionList()
{
	bool BorlandDCI = false;
	int i = 0;
	int j = 0;
	int Len = 0;
	String s;
	String sCompl;
	String sComment;
	String sComplValue;

	auto SaveEntry = [&]() -> void 
	{
		fCompletions->Add(sCompl);
		sCompl = L"";
		fCompletionComments->Add(sComment);
		sComment = L"";
		fCompletionValues->Add(sComplValue);
		sComplValue = L"";
	};
	fCompletions->Clear();
	fCompletionComments->Clear();
	fCompletionValues->Clear();
	if(fAutoCompleteList->Count > 0)
	{
		int stop = 0;
		s = fAutoCompleteList->Strings[0];
		BorlandDCI = (s != L"") && (s[1] == L'[');
		sCompl = L"";
		sComment = L"";
		sComplValue = L"";
		for(stop = fAutoCompleteList->Count - 1, i = 0; i <= stop; i++)
		{
			s = fAutoCompleteList->Strings[i];
			Len = (int) s.Length();
			if(BorlandDCI)
        // the style of the Delphi32.dci file
			{
				if((Len > 0) && (s[1] == L'['))
          // save last entry
				{
					if(sCompl != L"")
						SaveEntry();
          // new completion entry
					j = 2;
					while((j <= Len) && (s[j] > L' '))
						++j;
					sCompl = s.SubString(2, j - 2);
          // start of comment in DCI file
					while((j <= Len) && (s[j] <= L' '))
						++j;
					if((j <= Len) && (s[j] == L'|'))
						++j;
					while((j <= Len) && (s[j] <= L' '))
						++j;
					sComment = s.SubString(j, Len);
					if(sComment[sComment.Length()] == L']')
						sComment.SetLength((int) (sComment.Length() - 1));
				}
				else
				{
					if(sComplValue != L"")
						sComplValue = sComplValue + L"\x0d\x0a";
					sComplValue = sComplValue + s;
				}
			}
			else

        // the original style
			{
				if((Len > 0) && (s[1] != L'='))
          // save last entry
				{
					if(sCompl != L"")
						SaveEntry();
          // new completion entry
					sCompl = s;
				}
				else
				{
					if((Len > 0) && (s[1] == L'='))
					{
						if(sComplValue != L"")
							sComplValue = sComplValue + L"\x0d\x0a";
						sComplValue = sComplValue + s.SubString(2, Len);
					}
				}
			}
		}
		if(sCompl != L"")                                                        //mg 2000-11-07
			SaveEntry();
	}
	fParsed = true;
}

bool __fastcall TCustomSynAutoComplete::RemoveEditor(TCustomSynEdit* AEditor)
{
	bool result = false;
	int i = 0;
	if(AEditor != nullptr)
	{
		i = fEditors->IndexOf(AEditor);
		if(i >  - 1)
		{
			if(FEditor == AEditor)
				FEditor = nullptr;
			fEditors->Delete(i);
			AEditor->UnregisterCommandHandler(SynEditCommandHandler);
			RemoveFreeNotification(AEditor);
		}
	}
	result = false;
	return result;
}

void __fastcall TCustomSynAutoComplete::SetAutoCompleteList(TStrings* Value)
{
	fAutoCompleteList->Assign(Value);
	fParsed = false;
}

void __fastcall TCustomSynAutoComplete::SetEditor(TCustomSynEdit* Value)
{
	if(Value != FEditor)
	{
		if(FEditor != nullptr)
			RemoveEditor(FEditor);
		FEditor = Value;
		if(Value != nullptr)
			AddEditor(Value);
	}
}

void __fastcall TCustomSynAutoComplete::SynEditCommandHandler(TObject* Sender, bool AfterProcessing, bool& Handled, TSynEditorCommand& Command, WideChar& AChar, void* Data, void* HandlerData)
{
	if(!AfterProcessing && !Handled && (Command == ecAutoCompletion))
	{
		Handled = true;
		Execute((TCustomSynEdit*) Sender);
	}
}


}  // namespace SynEditAutoComplete

