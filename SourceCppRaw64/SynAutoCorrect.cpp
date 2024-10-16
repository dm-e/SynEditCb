#include <vcl.h>
#pragma hdrstop

#include "SynAutoCorrect.h"
#include "d2c_convert.h"
#include "SynEditDelphiInstances.hpp"

using namespace std;
using namespace d2c_system;
using namespace Synedit;
using namespace Syneditkeycmds;
using namespace Syneditmiscclasses;
using namespace Synedittypes;
using namespace System;
using namespace System::Classes;

namespace Synautocorrect
{
#define Synautocorrect__0 (TAsSynAutoCorrectOptions() << ascoIgnoreCase << ascoMaintainCase)

__fastcall TSynAutoCorrect::TSynAutoCorrect(TComponent* AOwner) : inherited(AOwner) {}




/* TCustomSynAutoCorrect */

__fastcall TCustomSynAutoCorrect::TCustomSynAutoCorrect(TComponent* AOwner)
 : inherited(AOwner),
			FEditor(nullptr),
			FEnabled(false),
			FItems(nullptr),
			FItemSepChar(L'\0'),
			FPrevLine(0)
{
	FEnabled = true;
	FItems = new TStringList();
	FItemSepChar = L'\x09';
	FOptions = Synautocorrect__0;
	FPrevLine = -1;
//  FEditor := nil; initialized by Delphi
}

__fastcall TCustomSynAutoCorrect::~TCustomSynAutoCorrect()
{
	Editor = nullptr;
	// inherited;
	delete FItems;
}


/* Utility functions */

String __fastcall TCustomSynAutoCorrect::HalfString(String Str, bool GetFirstHalf)
{
	String result;
	int i = 0;
	i = LastDelimiter(String(FItemSepChar), Str);
	if(i == 0)
		i = Pred(MaxInt);
	if(GetFirstHalf)
		result = Str.SubString(1, Pred(i));
	else
		result = Str.SubString(Succ(i), MaxInt);
	return result;
}

void __fastcall TCustomSynAutoCorrect::LoadFromINI(String AFileName, String ASection)
{
	int i = 0;
	String Original;
	String Correction;
	TMemIniFile* Reg = nullptr;
	Reg = new TMemIniFile(AFileName);
	try
	{
		FItems->Clear();
		/*# with Reg do */
		{
			auto with0 = Reg;
			int stop = 0;
			for(stop = Pred(with0->ReadInteger(ASection, L"Count", 0)), i = 0; i <= stop; i++)
			{
				Original = with0->ReadString(ASection, String(L"Original") + IntToStr(i), L"");
				Correction = with0->ReadString(ASection, String(L"Correction") + IntToStr(i), L"");
				if(!((Original == L"") && (Correction == L"")))
					FItems->Add(Original + String(FItemSepChar) + Correction);
			}
		}
	}
	__finally
	{
		delete Reg;
	}
}

void __fastcall TCustomSynAutoCorrect::SaveToINI(String AFileName, String ASection)
{
	int i = 0;
	TMemIniFile* Reg = nullptr;
	Reg = new TMemIniFile(AFileName);
	try
	{
		/*# with Reg do */
		{
			auto with0 = Reg;
			int stop = 0;
			with0->WriteInteger(ASection, L"Count", FItems->Count);
			for(stop = Pred(FItems->Count), i = 0; i <= stop; i++)
			{
				with0->WriteString(ASection, String(L"Original") + IntToStr(i), HalfString(FItems->Strings[i], true));
				with0->WriteString(ASection, String(L"Correction") + IntToStr(i), HalfString(FItems->Strings[i], false));
			}
		}
	}
	__finally
	{
		Reg->UpdateFile();
		delete Reg;
	}
}

bool __fastcall TCustomSynAutoCorrect::LoadFromList(String AFileName)
{
	bool result = false;
	result = false;
	if(FileExists(AFileName))
	{
		FItems->LoadFromFile(AFileName);
		result = true;
	}
	return result;
}

void __fastcall TCustomSynAutoCorrect::SaveToList(String AFileName)
{
	FItems->SaveToFile(AFileName);
}

void __fastcall TCustomSynAutoCorrect::LoadFromRegistry(DWORD ARoot, String AKey)
{
	int i = 0;
	String Original;
	String Correction;
	TRegIniFile* Reg = nullptr;
	Reg = new TRegIniFile(L"");
	try
	{
		/*# with Reg do */
		{
			auto with0 = Reg;
			int stop = 0;
			with0->RootKey = (HKEY) ARoot;
			((TBetterRegistry*) Reg)->OpenKeyReadOnly(AKey);
			FItems->Clear();
			for(stop = Pred(with0->ReadInteger(L"", L"Count", 0)), i = 0; i <= stop; i++)
			{
				Original = with0->ReadString(L"", String(L"Original") + IntToStr(i), L"");
				Correction = with0->ReadString(L"", String(L"Correction") + IntToStr(i), L"");
				if(!((Original == L"") && (Correction == L"")))
					FItems->Add(Original + String(FItemSepChar) + Correction);
			}
		}
	}
	__finally
	{
		delete Reg;
	}
}

void __fastcall TCustomSynAutoCorrect::SaveToRegistry(DWORD ARoot, String AKey)
{
	int i = 0;
	TRegIniFile* Reg = nullptr;
	Reg = new TRegIniFile(L"");
	try
	{
		/*# with Reg do */
		{
			auto with0 = Reg;
			int stop = 0;
			with0->RootKey = (HKEY) ARoot;
			with0->OpenKey(AKey, true);
			with0->WriteInteger(L"", L"Count", FItems->Count);
			for(stop = Pred(FItems->Count), i = 0; i <= stop; i++)
			{
				with0->WriteString(L"", String(L"Original") + IntToStr(i), HalfString(FItems->Strings[i], true));
				with0->WriteString(L"", String(L"Correction") + IntToStr(i), HalfString(FItems->Strings[i], false));
			}
		}
	}
	__finally
	{
		delete Reg;
	}
}

void __fastcall TCustomSynAutoCorrect::Add(String AOriginal, String ACorrection)
{
	FItems->Add(AOriginal + String(FItemSepChar) + ACorrection);
}

bool __fastcall TCustomSynAutoCorrect::AutoCorrectAll()
{
	bool result = false;
	int i = 0;
	int cx = 0;
	String s;
	String Original;
	String Correction;
	String CurrText;
	result = false;
	if(ASSIGNED(Editor))
	{
		int stop = 0;
		s = Editor->Lines->Text;
		cx = -1;
		for(stop = Pred(FItems->Count), i = 0; i <= stop; i++)
		{
			CurrText = FItems->Strings[i];
			Original = HalfString(CurrText, true);
			Correction = HalfString(CurrText, false);
			FindAndCorrect(s, Original, Correction, cx);
		}
		Editor->Lines->Text = s;
	}
	return result;
}

int __fastcall TCustomSynAutoCorrect::CorrectItemStart(String EditLine, String SearchString, int StartPos, bool MatchCase, bool WholeWord)
{
	int result = 0;
	int SearchCount = 0;
	int I = 0;
	PWideChar CurBuf = nullptr;
	PWideChar Buf = nullptr;
	int BufLen = 0;

	auto FindNextWordStart = [&](PWideChar& BufPtr) -> bool 
	{
		bool result = false;
		while((SearchCount > 0) && !Editor->IsWordBreakChar((*BufPtr)))
		{
			BufPtr += 1;
			--SearchCount;
		}
		while((SearchCount > 0) && Editor->IsWordBreakChar((*BufPtr)))
		{
			BufPtr += 1;
			--SearchCount;
		}
		result = SearchCount >= 0;
		return result;
	};

	auto ScanText = [&](PWideChar& BufPtr) -> bool 
	{
		bool result = false;
		bool FirstWord = false;
		result = false;
		FirstWord = true;
		if(WholeWord)
		{
			while((SearchCount > 0) && Editor->IsWordBreakChar((*BufPtr)))
			{
				BufPtr += 1;
				--SearchCount;
			}
		}
		while(SearchCount >= 0)
		{
			if(WholeWord && (FirstWord == false))
			{
				if(!FindNextWordStart(BufPtr))
					break;
			}
			I = 0;
			while((BufPtr[I] == SearchString[I + 1]))
			{
				++I;
				if(I >= SearchString.Length())
				{
					if(!WholeWord || (SearchCount == 0) || Editor->IsWordBreakChar(BufPtr[I]))
					{
						result = true;
						return result;
					}
					break;
				}
			}
			FirstWord = false;
			++BufPtr;
			--SearchCount;
		}
		return result;
	};
	result = -1;
	if(!MatchCase)
	{
		EditLine = Sysutils::AnsiUpperCase(EditLine);
		SearchString = Sysutils::AnsiUpperCase(SearchString);
	}
	BufLen = EditLine.Length();
	Buf = ustr2pwchar(EditLine);
	if(BufLen > 0)
	{
		SearchCount = Succ(BufLen - StartPos - SearchString.Length());
		if((SearchCount >= 0) && (SearchCount <= BufLen) && (StartPos + SearchCount <= BufLen))
		{
			CurBuf = &Buf[StartPos];
			if(!ScanText(CurBuf))
				CurBuf = nullptr;
			else
			{
				if(CurBuf != nullptr)
					result = CurBuf - Buf;
			}
		}
	}
	CurBuf = nullptr;
	return result;
}

void __fastcall TCustomSynAutoCorrect::DefineProperties(TFiler* Filer)
{
	inherited::DefineProperties(Filer);
}

void __fastcall TCustomSynAutoCorrect::Delete(int AIndex)
{
	FItems->Delete(AIndex);
}

void __fastcall TCustomSynAutoCorrect::Edit(int AIndex, String ANewOriginal, String ANewCorrection)
{
	if(AIndex > -1)
		FItems->Strings[AIndex] = ANewOriginal + String(FItemSepChar) + ANewCorrection;
}

void __fastcall TCustomSynAutoCorrect::KeyboardHandler(TObject* Sender, bool AfterProcessing, bool& Handled, TSynEditorCommand& Command, WideChar& AChar, void* Data, void* HandlerData)
{
	bool b = false;
	int i = 0;
	int cx = 0;
	String s;
	String Original;
	String Correction;
	String CurrText;
	if(Enabled && !AfterProcessing && !Handled)
	{
		FPrevLine = Editor->CaretY;
		switch(Command)
		{
			case ecLineBreak:
			case ecTab:
			case ecChar:
			{
				if((Command == ecChar) && !Editor->IsWordBreakChar(AChar))
					return;
				b = false;
				s = PreviousToken();
				if(s != L"")
				{
					int stop = 0;
					cx = Editor->CaretX;
					for(stop = Pred(FItems->Count), i = 0; i <= stop; i++)
					{
						CurrText = FItems->Strings[i];
						Original = HalfString(CurrText, true);
						Correction = HalfString(CurrText, false);
						b = b || FindAndCorrect(s, Original, Correction, cx);
					}
					if(ASSIGNED(OnCorrected))
						OnCorrected(this);
				}
			}
			break;
			default:
			  ;
			break;
		} /*endcase*/
	}
}

void __fastcall TCustomSynAutoCorrect::MouseDownHandler(TObject* Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
	TAutoCorrectAction Action = aaCorrect;
	bool b = false;
	int i = 0;
	int cx = 0;
	String s;
	String Original;
	String Correction;
	String CurrText;
	if(FOptions.Contains(ascoCorrectOnMouseDown))
	{
		if(ASSIGNED(Editor) && Enabled && (FPrevLine != -1))
		{
			int stop = 0;
			b = false;
			s = Editor->Lines->Strings[Pred(FPrevLine)];
			cx = -1;
			for(stop = Pred(FItems->Count), i = 0; i <= stop; i++)
			{
				CurrText = FItems->Strings[i];
				Original = HalfString(CurrText, true);
				Correction = HalfString(CurrText, false);
				b = b || FindAndCorrect(s, Original, Correction, cx);
			}
			if(b)
			{
				if(ASSIGNED(FOnAutoCorrect))
				{
					Action = aaCorrect;
					FOnAutoCorrect(this, Editor->Lines->Strings[Pred(FPrevLine)], s, Editor->CaretY, 0, Action);
					if(Action == aaAbort)
						return;
				}
				Editor->Lines->Strings[Pred(FPrevLine)] = s;
				if(ASSIGNED(OnCorrected))
					OnCorrected(this);
			}
		}
	}
}

bool __fastcall TCustomSynAutoCorrect::FindAndCorrect(String& EditLine, String Original, String Correction, int& CurrentX)
{
	bool result = false;
	int StartPos = 0;
	int EndPos = 0;
	String FoundText;
	String ReplaceDefText;
	TBufferCoord p = {};
	TAutoCorrectAction Action = aaCorrect;

	auto FirstCapCase = [&](String s) -> String 
	{
		String result;
		if(s != L"")
		{
			s = Sysutils::AnsiLowerCase(s);
			s[1] = Sysutils::AnsiUpperCase(String(s[1]))[1];
		}
		result = s;
		return result;
	};
	result = false;
	ReplaceDefText = Correction;
	StartPos = 0;
	EndPos = Original.Length();
	if((Editor != nullptr) && !(Editor->ReadOnly))
	{
		StartPos = CorrectItemStart(EditLine, Original, StartPos, !(FOptions.Contains(ascoIgnoreCase)), true);
		while(StartPos > -1)
		{
			if(FOptions.Contains(ascoMaintainCase))
			{
				Correction = ReplaceDefText;
				FoundText = EditLine.SubString(StartPos + 1, EndPos);
				if(FoundText == Sysutils::AnsiUpperCase(FoundText))
					Correction = Sysutils::AnsiUpperCase(Correction);
				else
				{
					if(FoundText == Sysutils::AnsiLowerCase(FoundText))
						Correction = Sysutils::AnsiLowerCase(Correction);
					else
					{
						if(FoundText == FirstCapCase(FoundText))
							Correction = FirstCapCase(Correction);
					}
				}
			}
			if(CurrentX > -1)
			{
				p = Editor->CaretXY;
				if(ASSIGNED(FOnAutoCorrect))
				{
					Action = aaCorrect;
					FOnAutoCorrect(this, Original, Correction, p.Line, p.Char, Action);
					if(Action == aaAbort)
						break;
				}
				Editor->BeginUpdate();
				try
				{
					if(p.Char == 0)
						Editor->BlockBegin = BufferCoord(p.Char - 1 - EndPos, p.Line);
					else
						Editor->BlockBegin = BufferCoord(p.Char - EndPos, p.Line);
					Editor->BlockEnd = p;
					p = Editor->BlockBegin;
					Editor->SelText = Correction;
					result = true;
				}
				__finally
				{
					Editor->EndUpdate();
				}
				break;
			}
			else
			{
				result = true;
				EditLine = EditLine.SubString(1, StartPos) + Correction + EditLine.SubString(StartPos + EndPos + 1, MaxInt);
				StartPos += EndPos;
				StartPos = CorrectItemStart(EditLine, Original, StartPos, !(FOptions.Contains(ascoIgnoreCase)), true);
			}
		}
	}
	return result;
}

TStrings* __fastcall TCustomSynAutoCorrect::GetItems()
{
	TStrings* result = nullptr;
	result = FItems;
	return result;
}

void __fastcall TCustomSynAutoCorrect::Notification(TComponent* AComponent, TOperation Operation)
{
	inherited::Notification(AComponent, Operation);
	if((Operation == opRemove) && (AComponent == FEditor))
	{
		Editor = nullptr;
	}
}

String __fastcall TCustomSynAutoCorrect::PreviousToken()
{
	String result;
	int i = 0;
	int cx = 0;
	result = Editor->LineText;
	cx = Editor->CaretX;
	i = Pred(cx);
	if(i <= result.Length())
	{
		while((i > 0) && !Editor->IsWordBreakChar(result[i]))
			--i;
		++i;
		result = result.SubString(i, cx - i);
	}
	else
	result = L"";
	return result;
}

void __fastcall TCustomSynAutoCorrect::SetEditor(TCustomSynEdit* Value)
{
	if(FEditor != Value)
	{
		if(ASSIGNED(FEditor))
		{
			Editor->RemoveMouseDownHandler(MouseDownHandler);
			Editor->UnregisterCommandHandler(KeyboardHandler);
			Editor->RemoveFreeNotification(this);
		}
		FEditor = Value;
		if(ASSIGNED(FEditor))
		{
			Editor->FreeNotification(this);
			Editor->RegisterCommandHandler(KeyboardHandler, nullptr);
			Editor->AddMouseDownHandler(MouseDownHandler);
		}
	}
}

void __fastcall TCustomSynAutoCorrect::SetItems(TStrings* const Value)
{
	FItems->Assign((TPersistent*) Value);
}


}  // namespace SynAutoCorrect

