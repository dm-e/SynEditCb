#include <vcl.h>
#pragma hdrstop

#include "SynCompletionProposal.h"
#include <System.Math.hpp>
#include <Vcl.Themes.hpp>
#include <System.Types.hpp>
#include <System.UITypes.hpp>
#include "SynEditTextBuffer.h"
#include "SynEditMiscProcs.h"
#include "SynEditKeyConst.h"
#include "d2c_graphics.h"
#include "SynEditDelphiInstances.hpp"

using namespace std;
using namespace d2c_system;
using namespace Synedit;
using namespace Syneditkeycmds;
using namespace Syneditkeyconst;
using namespace Syneditmiscprocs;
using namespace Synedittextbuffer;
using namespace Synedittypes;
using namespace System;
using namespace System::Classes;
using namespace System::Math;
using namespace System::Types;
using namespace System::Uitypes;
using namespace Vcl::Controls;
using namespace Vcl::Forms;
using namespace Vcl::Graphics;
using namespace Vcl::Themes;

namespace Syncompletionproposal
{
#define Syncompletionproposal__0 (TSysCharSet() << '+' << '-' << '~')
#define Syncompletionproposal__1 (TSysCharSet() << 'B' << 'I' << 'U' << 'S')
#define Syncompletionproposal__2 (TFontStyles() << TFontStyle::fsItalic)
#define Syncompletionproposal__3 (TFontStyles() << TFontStyle::fsBold)
#define Syncompletionproposal__4 (TFontStyles() << TFontStyle::fsUnderline)
#define Syncompletionproposal__5 (TFontStyles() << TFontStyle::fsStrikeOut)
#define Syncompletionproposal__6 TFontStyles()
#define Syncompletionproposal__7 (TFormatCommands() << fcColor)
#define Syncompletionproposal__8 TFormatCommands()
#define Syncompletionproposal__9 (TFormatCommands() << fcColor)
#define Syncompletionproposal__10 (TSysCharSet() << 'B' << 'I' << 'U')
#define Syncompletionproposal__11 TFontStyles()
#define Syncompletionproposal__12 (TFontStyles() << TFontStyle::fsBold)
#define Syncompletionproposal__13 (TStyleElements() << seClient)
#define Syncompletionproposal__14 TShiftState()
#define Syncompletionproposal__15 TShiftState()
#define Syncompletionproposal__16 TShiftState()
#define Syncompletionproposal__17 TShiftState()
#define Syncompletionproposal__18 (TElementEdges() << eeRaisedOuter)
#define Syncompletionproposal__19 (TElementEdgeFlags() << efRect << efFlat)
#define Syncompletionproposal__20 TShiftState()
#define Syncompletionproposal__21 (TShiftState() << ssCtrl)
#define Syncompletionproposal__22 TShiftState()
#define Syncompletionproposal__23 (TShiftState() << ssShift)
#define Syncompletionproposal__24 (System::Set<TSynCompletionOption, TSynCompletionOption::scoCaseSensitive, TSynCompletionOption::scoCompleteWithEnter>() << scoUsePrettyText)
#define Syncompletionproposal__25 (System::Set<TSynCompletionOption, TSynCompletionOption::scoCaseSensitive, TSynCompletionOption::scoCompleteWithEnter>() << scoUseBuiltInTimer)
#define Syncompletionproposal__26 (TSynCompletionOptions() << scoUsePrettyText)
#define Syncompletionproposal__27 (TSynCompletionOptions() << scoUseBuiltInTimer)

__fastcall TProposalColumns::TProposalColumns(TCollectionItemClass ItemClass) : inherited(ItemClass) {}


const WideChar TextHeightString[] = L"CompletionProposal";

//------------------------- Formatted painting stuff ---------------------------
enum TFormatCommand {fcNoCommand,
                     fcColor,
                     fcStyle,
                     fcColumn,
                     fcHSpace,
                     fcImage };
typedef System::Set<TFormatCommand, TFormatCommand::fcNoCommand, TFormatCommand::fcImage> TFormatCommands;
struct TFormatChunk;
typedef TFormatChunk* PFormatChunk;

struct TFormatChunk
{
	String Str;
	TFormatCommand Command;
	void* Data;
};
struct TFormatStyleData;
typedef TFormatStyleData* PFormatStyleData;

struct TFormatStyleData
{
	WideChar Style;
	int Action;    // -1 = Reset, +1 = Set, 0 = Toggle
};

class TFormatChunkList : public TObject
{
	#include "SynCompletionProposal_friends.inc"
public:
	typedef TObject inherited;	
private:
	TList* FChunks;
	int __fastcall GetCount();
	PFormatChunk __fastcall GetChunk(int Index);
public:
	__fastcall TFormatChunkList();
	virtual __fastcall ~TFormatChunkList();
	void __fastcall Clear();
	void __fastcall Add(PFormatChunk AChunk);
	__property int Count = { read = GetCount };
	__property PFormatChunk Chunks[int Index] = { read = GetChunk/*# default */ };
};
const System::Set<TFormatCommand, TFormatCommand::fcNoCommand, TFormatCommand::fcImage> AllCommands = System::Set<TFormatCommand, TFormatCommand::fcNoCommand, TFormatCommand::fcImage>() <<  \
										fcColor << fcStyle << fcColumn << fcHSpace << fcImage;

int __fastcall TFormatChunkList::GetCount()
{
	int result = 0;
	result = FChunks->Count;
	return result;
}

PFormatChunk __fastcall TFormatChunkList::GetChunk(int Index)
{
	PFormatChunk result = nullptr;
	result = ((TFormatChunk*) FChunks->Items[Index]);
	return result;
}

void __fastcall TFormatChunkList::Clear()
{
	PFormatChunk C = nullptr;
	PFormatStyleData StyleFormatData = nullptr;
	while(FChunks->Count > 0)
	{
		C = ((TFormatChunk*) FChunks->Last());
		FChunks->Delete(FChunks->Count - 1);
		switch((*C).Command)
		{
			case fcStyle:
			{
				StyleFormatData = ((TFormatStyleData*) (*C).Data);
				delete StyleFormatData;
			}
			break;
			default:
			  ;
			break;
		}
		delete C;
	}
}

__fastcall TFormatChunkList::TFormatChunkList()
 : FChunks(new TList())
{
	//# inherited::Create();
}

__fastcall TFormatChunkList::~TFormatChunkList()
{
	Clear();
	delete FChunks;
	//# inherited::Destroy();
}

void __fastcall TFormatChunkList::Add(PFormatChunk AChunk)
{
	FChunks->Add(AChunk);
}

bool __fastcall ParseFormatChunks(const String FormattedString, TFormatChunkList* ChunkList, const TFormatCommands StripCommands)
{
	bool result = false;
	WideChar CurChar = L'\0';
	int CurPos = 0;
	String CurrentChunk;
	int PossibleErrorPos = 0;
	bool ErrorFound = false;

	auto NextChar = [&]() -> void 
	{
		++CurPos;
		if(CurPos <= FormattedString.Length()) // dme
			CurChar = FormattedString[CurPos];
		 else
			CurChar = L'\0';
	};

	auto AddStringChunk = [&]() -> void 
	{
		PFormatChunk C = nullptr;
		C = new TFormatChunk;
		(*C).Str = CurrentChunk;
		(*C).Command = fcNoCommand;
		(*C).Data = nullptr;
		ChunkList->Add(C);
		CurrentChunk = L"";
	};

	auto AddCommandChunk = [&](TFormatCommand ACommand, void* Data) -> void 
	{
		PFormatChunk C = nullptr;
		C = new TFormatChunk;
		(*C).Str = L"";
		(*C).Command = ACommand;
		(*C).Data = Data;
		ChunkList->Add(C);
	};

	auto ParseEscapeSequence = [&]() -> void 
	{
		String Command;
		String Parameter;
		TFormatCommand CommandType = fcNoCommand;
		void* Data = nullptr;
		Assert(CurChar == L'\\');
		NextChar();
		if(CurChar == L'\\')
		{
			CurrentChunk = CurrentChunk + L"\\";
			NextChar();
			return;
		}
		if(CurrentChunk != L"")
			AddStringChunk();
		Command = L"";
		while((CurChar != L'{') && (CurPos <= FormattedString.Length()))
		{
			Command = Command + String(CurChar);
			NextChar();
		}
		if(CurChar == L'{')
		{
			PossibleErrorPos = CurPos;
			NextChar();
			Parameter = L"";
			while((CurChar != L'}') && (CurPos <= FormattedString.Length()))
			{
				Parameter = Parameter + String(CurChar);
				NextChar();
			}
			if(CurChar == L'}')
			{
				Command = System::Sysutils::AnsiUpperCase(Command);
				Data = nullptr;
				CommandType = fcNoCommand;
				if(Command == L"COLOR")
				{
					try
					{
						Data = ((void*) StringToColor(Parameter));
						CommandType = fcColor;
					}
					catch(...)
					{
						CommandType = fcNoCommand;
						ErrorFound = true;
					}
				}
				else
				{
					if(Command == L"COLUMN")
					{
						if(Parameter != L"")
						{
							CommandType = fcNoCommand;
							ErrorFound = true;
						}
						else
						CommandType = fcColumn;
					}
					else
					{
						if(Command == L"HSPACE")
						{
							try
							{
								Data = ((void*) StrToInt(Parameter));
								CommandType = fcHSpace;
							}
							catch(...)
							{
								CommandType = fcNoCommand;
								ErrorFound = true;
							}
						}
						else
						{
							if(Command == L"IMAGE")
							{
								try
								{
									Data = ((void*) StrToInt(Parameter));
									CommandType = fcImage;
								}
								catch(...)
								{
									CommandType = fcNoCommand;
									ErrorFound = true;
								}
							}
							else
							{
								if(Command == L"STYLE")
								{
									if((Parameter.Length() == 2) && CharInSet(Parameter[1], Syncompletionproposal__0) && CharInSet(System::Sysutils::AnsiUpperCase(String(Parameter[2]))[1], Syncompletionproposal__1))
									{
										CommandType = fcStyle;
										if(!(StripCommands.Contains(fcStyle)))
										{
											Data = new TFormatStyleData;
											(*((PFormatStyleData) Data)).Style = System::Sysutils::AnsiUpperCase(String(Parameter[2]))[1];
											switch(Parameter[1])
											{
												case L'+':
												(*((PFormatStyleData) Data)).Action = 1;
												break;
												case L'-':
												(*((PFormatStyleData) Data)).Action = -1;
												break;
												case L'~':
												(*((PFormatStyleData) Data)).Action = 0;
												break;
												default:
												  ;
												break;
											}
										}
									}
									else
									{
										CommandType = fcNoCommand;
										ErrorFound = true;
									}
								}
								else
								ErrorFound = true;
							}
						}
					}
				}
				if((CommandType != fcNoCommand) && (!(StripCommands.Contains(CommandType))))
					AddCommandChunk(CommandType, Data);
				NextChar();
			}
		}
		result = !ErrorFound;
	};

	auto ParseString = [&]() -> void 
	{
		Assert(CurChar != L'\\');
		while((CurChar != L'\\') && (CurPos <= FormattedString.Length()))
		{
			CurrentChunk = CurrentChunk + String(CurChar);
			NextChar();
		}
	};
	Assert(ASSIGNED(ChunkList));
	if(FormattedString == L"")
		return result;
	ErrorFound = false;
	CurrentChunk = L"";
	CurPos = 1;
	CurChar = FormattedString[1];
	while(CurPos <= FormattedString.Length())
	{
		if(CurChar == L'\\')
			ParseEscapeSequence();
		else
			ParseString();
	}
	if(CurrentChunk != L"")
		AddStringChunk();
	return result;
}

String __fastcall StripFormatCommands(const String FormattedString)
{
	String result;
	TFormatChunkList* Chunks = nullptr;
	int i = 0;
	Chunks = new TFormatChunkList();
	try
	{
		int stop = 0;
		ParseFormatChunks(FormattedString, Chunks, AllCommands);
		result = L"";
		for(stop = Chunks->Count - 1, i = 0; i <= stop; i++)
		{
			result = result + (*Chunks->Chunks[i]).Str;
		}
	}
	__finally
	{
		delete Chunks;
	}
	return result;
}

int __fastcall PaintChunks(TCanvas* TargetCanvas, const TRect& Rect, int PPI, TFormatChunkList* ChunkList, TProposalColumns* Columns, TCustomImageList* Images, bool Invisible)
{
	int result = 0;
	int i = 0;
	int X = 0;
	PFormatChunk C = nullptr;
	TProposalColumn* CurrentColumn = nullptr;
	int CurrentColumnIndex = 0;
	int LastColumnStart = 0;
	TFontStyles Style;
	TFont* OldFont = nullptr;
	OldFont = new TFont();
	try
	{
		int stop = 0;
		OldFont->Assign(TargetCanvas->Font);
		if(ASSIGNED(Columns) && (Columns->Count > 0))
		{
			CurrentColumnIndex = 0;
			CurrentColumn = Columns->Items[0];
			TargetCanvas->Font->Style = CurrentColumn->DefaultFontStyle;
		}
		else
		{
			CurrentColumnIndex = -1;
			CurrentColumn = nullptr;
		}
		LastColumnStart = Rect.Left;
		X = Rect.Left;
		TargetCanvas->Brush->Style = bsClear;
		for(stop = ChunkList->Count - 1, i = 0; i <= stop; i++)
		{
			C = ChunkList->Chunks[i];
			switch((*C).Command)
			{
				case fcNoCommand:
				{
					if(!Invisible)
						TargetCanvas->TextOut(X, Rect.Top, (*C).Str);
					X += TargetCanvas->TextWidth((*C).Str);
					if(X > Rect.Right)
						goto label0;
				}
				break;
				case fcColor:
				if(!Invisible)
					TargetCanvas->Font->Color = StyleServices()->GetSystemColor((TColor) (NativeInt) (*C).Data);
				break;
				case fcStyle:
				{
					switch((*((PFormatStyleData) (*C).Data)).Style)
					{
						case L'I':
						Style = Syncompletionproposal__2;
						break;
						case L'B':
						Style = Syncompletionproposal__3;
						break;
						case L'U':
						Style = Syncompletionproposal__4;
						break;
						case L'S':
						Style = Syncompletionproposal__5;
						break;
						default:
						Assert(false);
						break;
					}
					switch((*((PFormatStyleData) (*C).Data)).Action)
					{
						case -1:
						TargetCanvas->Font->Style = TargetCanvas->Font->Style - Style;
						break;
						case 0:
						if(TargetCanvas->Font->Style * Style == Syncompletionproposal__6)
							TargetCanvas->Font->Style = TargetCanvas->Font->Style + Style;
						else
							TargetCanvas->Font->Style = TargetCanvas->Font->Style - Style;
						break;
						case 1:
						TargetCanvas->Font->Style = TargetCanvas->Font->Style + Style;
						break;
						default:
						Assert(false);
						break;
					}
				}
				break;
				case fcColumn:
				if(ASSIGNED(Columns) && (Columns->Count > 0))
				{
					if(CurrentColumnIndex <= Columns->Count - 1)
					{
						LastColumnStart += MulDiv(CurrentColumn->ColumnWidth, PPI, 96);
						X = LastColumnStart;
						++CurrentColumnIndex;
						if(CurrentColumnIndex <= Columns->Count - 1)
						{
							CurrentColumn = Columns->Items[CurrentColumnIndex];
							TargetCanvas->Font->Style = CurrentColumn->DefaultFontStyle;
						}
						else
						CurrentColumn = nullptr;
					}
				}
				break;
				case fcHSpace:
				{
					X += MulDiv((NativeInt)(*C).Data, PPI, 96);
					if(X > Rect.Right)
						goto label1;
				}
				break;
				case fcImage:
				{
					Assert(ASSIGNED(Images));
					Images->Draw(TargetCanvas, X, Rect.Top, (NativeInt)(*C).Data);
					X += Images->Width;
					if(X > Rect.Right)
						goto label2;
				}
				break;
				default:
				  ;
				break;
			}
		}
		label0:;
		label1:;
		label2:;
		result = X;
		TargetCanvas->Font->Assign(OldFont);
	}
	__finally
	{
		delete OldFont;
		TargetCanvas->Brush->Style = bsSolid;
	}
	return result;
}

void __fastcall FormattedTextOut(TCanvas* TargetCanvas, const TRect& Rect, int PPI, const String Text, bool Selected, TProposalColumns* Columns, TCustomImageList* Images)
{
	TFormatChunkList* Chunks = nullptr;
	TFormatCommands StripCommands;
	Chunks = new TFormatChunkList();
	try
	{
		if(Selected)
			StripCommands = Syncompletionproposal__7;
		else
			StripCommands = Syncompletionproposal__8;
		ParseFormatChunks(Text, Chunks, StripCommands);
		PaintChunks(TargetCanvas, Rect, PPI, Chunks, Columns, Images, false);
	}
	__finally
	{
		delete Chunks;
	}
}

int __fastcall FormattedTextWidth(TCanvas* TargetCanvas, const String Text, int PPI, TProposalColumns* Columns, TCustomImageList* Images)
{
	int result = 0;
	TFormatChunkList* Chunks = nullptr;
	TRect tmpRect = {};
	Chunks = new TFormatChunkList();
	try
	{
		tmpRect = Rect(0, 0, MaxInt, MaxInt);
		ParseFormatChunks(Text, Chunks, Syncompletionproposal__9);
		result = PaintChunks(TargetCanvas, tmpRect, PPI, Chunks, Columns, Images, true);
	}
	__finally
	{
		delete Chunks;
	}
	return result;
}

String __fastcall PrettyTextToFormattedString(const String APrettyText, bool AlternateBoldStyle/*# = false*/)
{
	String result;
	int i = 0;
	TColor Color = (TColor) 0;
	result = L"";
	i = 1;
	while(i <= APrettyText.Length())
		switch(APrettyText[i])
		{
			case L'\x01':
			case L'\x02':
			{
				Color = (TColor) ((((int(APrettyText[i + 3]) << 8) + int(APrettyText[i + 2])) << 8) + int(APrettyText[i + 1]));
				result = result + L"\\color{" + ColorToString(Color) + L"}";
				i += 4;
			}
			break;
			case L'\x03':
			{
				if(CharInSet(System::Sysutils::AnsiUpperCase(String(APrettyText[i + 1]))[1], Syncompletionproposal__10))
				{
					result = result + L"\\style{";
					switch(APrettyText[i + 1])
					{
						case L'B':
						result = result + L"+B";
						break;
						case L'b':
						result = result + L"-B";
						break;
						case L'I':
						result = result + L"+I";
						break;
						case L'i':
						result = result + L"-I";
						break;
						case L'U':
						result = result + L"+U";
						break;
						case L'u':
						result = result + L"-U";
						break;
						default:
						  ;
						break;
					}
					result = result + L"}";
				}
				i += 2;
			}
			break;
			case L'\x09':
			{
				result = result + L"\\column{}";
				if(AlternateBoldStyle)
					result = result + L"\\style{~B}";
				++i;
			}
			break;
			default:
			result = result + String(APrettyText[i]);
			++i;
			break;
		}
	return result;
}


// TProposalColumn

__fastcall TProposalColumn::TProposalColumn(TCollection* Collection)
 : inherited(Collection),
			FColumnWidth(100),
			FInternalWidth(-1),
			FFontStyle(Syncompletionproposal__11)
{
}

__fastcall TProposalColumn::~TProposalColumn()
{
	// inherited;
}

void __fastcall TProposalColumn::Assign(TPersistent* Source)
{
	if(ObjectIs(Source, TProposalColumn*))
	{
		FColumnWidth = ((TProposalColumn*) Source)->FColumnWidth;
		FInternalWidth = ((TProposalColumn*) Source)->FInternalWidth;
		FFontStyle = ((TProposalColumn*) Source)->FFontStyle;
	}
	else
	inherited::Assign(Source);
}

void __fastcall TProposalColumn::DefineProperties(TFiler* Filer)
{
	inherited::DefineProperties(Filer);
}

__fastcall TProposalColumns::TProposalColumns(TPersistent* AOwner, TCollectionItemClass ItemClass)
 : inherited(ItemClass),
			FOwner(AOwner)
{
}

TPersistent* __fastcall TProposalColumns::GetOwner()
{
	TPersistent* result = nullptr;
	result = FOwner;
	return result;
}

TProposalColumn* __fastcall TProposalColumns::GetItem(int Index)
{
	TProposalColumn* result = nullptr;
	result = (TProposalColumn*) inherited::GetItem(Index);
	return result;
}

void __fastcall TProposalColumns::SetItem(int Index, TProposalColumn* Value)
{
	inherited::SetItem(Index, Value);
}

TProposalColumn* __fastcall TProposalColumns::Add()
{
	TProposalColumn* result = nullptr;
	result = (TProposalColumn*) inherited::Add();
	return result;
}

TProposalColumn* __fastcall TProposalColumns::FindItemID(int id)
{
	TProposalColumn* result = nullptr;
	result = (TProposalColumn*) inherited::FindItemID(id);
	return result;
}

TProposalColumn* __fastcall TProposalColumns::Insert(int Index)
{
	TProposalColumn* result = nullptr;
	result = (TProposalColumn*) inherited::Insert(Index);
	return result;
}



//============================================================================

String __fastcall FormatParamList(const String s, int CurrentIndex)
{
	String result;
	int i = 0;
	TStrings* List = nullptr;
	result = L"";
	List = new TStringList();
	try
	{
		int stop = 0;
		List->CommaText = s;
		for(stop = List->Count - 1, i = 0; i <= stop; i++)
		{
			if(i == CurrentIndex)
				result = result + L"\\style{~B}" + List->Strings[i] + L"\\style{~B}";
			else
				result = result + List->Strings[i];
			if(i < List->Count - 1)
//        Result := Result + ', ';
				result = result + L" ";
		}
	}
	__finally
	{
		delete List;
	}
	return result;
}

/* TSynBaseCompletionProposalForm */

__fastcall TSynBaseCompletionProposalForm::TSynBaseCompletionProposalForm(TComponent* AOwner)
 : /*#CreateNew*/ inherited(AOwner, 0), 
			FItemList(nullptr),
			FInsertList(nullptr),
			FAssignedList(nullptr),
			FPosition(0),
			fLinesInWindow(0),
			FTitleFontHeight(0),
			FFontHeight(0),
			FScrollbar(nullptr),
			FClSelect((TColor) 0),
			fClSelectText((TColor) 0),
			FClTitleBackground((TColor) 0),
			fClBackGround((TColor) 0),
			BITMAP(nullptr),
			TitleBitmap(nullptr),
			FCurrentEditor(nullptr),
			FTitleFont(nullptr),
			FFont(nullptr),
			FResizeable(false),
			FItemHeight(0),
			FMargin(0),
			FEffectiveItemHeight(0),
			FImages(nullptr),
			FCase(false),
			FMatchText(false),
			FFormattedText(false),
			FCenterTitle(false),
			FUseInsertList(false),
			FCompleteWithTab(false),
			FCompleteWithEnter(false),
			fMouseWheelAccumulator(0),
			FDisplayKind(ctCode),
			FCurrentIndex(0),
			FCurrentLevel(0),
			FDefaultKind(ctCode),
			OldShowCaret(false),
			FHeightBuffer(0),
			FColumns(nullptr)
{
	BITMAP = new TBitmap();
	TitleBitmap = new TBitmap();
	FItemList = new TStringList();
	FInsertList = new TStringList();
	FAssignedList = new TStringList();
	FMatchText = false;
	BorderStyle = bsNone;
	FScrollbar = new TScrollBar(this);
	FScrollbar->Kind = sbVertical;
	FScrollbar->ParentCtl3D = false;
	FScrollbar->OnChange = ScrollbarOnChange;
	FScrollbar->OnScroll = ScrollbarOnScroll;
	FScrollbar->OnEnter = ScrollbarOnEnter;
	FScrollbar->Parent = this;
	FTitleFont = new TFont();
	FTitleFont->Name = L"MS Shell Dlg 2";
	FTitleFont->Size = 8;
	FTitleFont->Style = Syncompletionproposal__12;
	FTitleFont->Color = clBtnText;
	FFont = new TFont();
	FFont->Name = L"MS Shell Dlg 2";
	FFont->Size = 8;
	ClSelect = clHighlight;
	ClSelectedText = clHighlightText;
	clBackground = clWindow;
	ClTitleBackground = clBtnFace;
	((TStringList*) FItemList)->OnChange = StringListChange;  // Really necessary? It seems to work
	FTitle = L"";                                             // fine without it
	FUseInsertList = false;
	FFormattedText = false;
	FCenterTitle = true;
	FCase = false;
	FColumns = new TProposalColumns(AOwner, __classid(TProposalColumn));
	FItemHeight = 0;
	FMargin = 2;
	FEffectiveItemHeight = 0;
	RecalcItemHeight();
	Canvas->Font->Assign(FTitleFont);
	FTitleFontHeight = Canvas->TextHeight(TextHeightString);
	FHeightBuffer = 0;
	FTitleFont->OnChange = TitleFontChange;
	FFont->OnChange = FontChange;
	OnDblClick = DoDoubleClick;
	OnShow = DoFormShow;
	OnHide = DoFormHide;
	StyleElements = Syncompletionproposal__13;
	Resizeable = false;
	Visible = false;
}

void __fastcall TSynBaseCompletionProposalForm::CreateParams(TCreateParams& Params)
{
	inherited::CreateParams(Params);
	/*# with Params do */
	{
		auto& with0 = Params;
		with0.Style = WS_POPUP;
		with0.ExStyle = (DWORD) WS_EX_TOOLWINDOW;
		Params.WindowClass.style = Params.WindowClass.style | CS_DROPSHADOW;

    /*
      WS_THICKFRAME causes Windows 10 to display a 6 pixel title bar
      Also with VCL Styles the window is not resizable
      So we use WS_DLGFRAME (could instead use WS_SBORDER)
      and make the window sizeable by handling WM_NCHITTEST
    */
		if(DisplayType == ctCode)
      //if FResizeable then
      //  Style := Style or WS_THICKFRAME
      //else
			with0.Style = with0.Style | WS_DLGFRAME;
	}
}

void __fastcall TSynBaseCompletionProposalForm::Activate()
{
	Visible = true;
	if((DisplayType == ctCode) && ASSIGNED(CurrentEditor))  //KV
		((TCustomSynEdit*) CurrentEditor)->AddFocusControl(this);
}

void __fastcall TSynBaseCompletionProposalForm::Deactivate()
{
	if((DisplayType == ctCode) && ASSIGNED(CurrentEditor))  //KV
	{
		((TCustomSynEdit*) CurrentEditor)->RemoveFocusControl(this);
		Visible = false;
	}
}

__fastcall TSynBaseCompletionProposalForm::~TSynBaseCompletionProposalForm()
{
	//# inherited::TCustomForm::Destroy();
	inherited::RemoveFreeNotifications();
	delete FColumns;
	delete BITMAP;
	delete TitleBitmap;
	delete FItemList;
	delete FInsertList;
	delete FAssignedList;
	delete FTitleFont;
	delete FFont;
}

void __fastcall TSynBaseCompletionProposalForm::KeyDown(WORD& key, TShiftState Shift)
{
	WideChar C = L'\0';
	TSynEditorCommand cmd = 0;
	int i = 0;

	auto ExecuteCmdAndCancel = [&]() -> void 
	{
		if(cmd != ecNone)
		{
			if(ASSIGNED(CurrentEditor))
				((TCustomSynEdit*) CurrentEditor)->CommandProcessor(cmd, L'\x00', nullptr);
			if(ASSIGNED(OnCancel))
				OnCancel(this);
		}
	};
	if(DisplayType == ctCode)
	{
		i = ((TCustomSynEdit*) CurrentEditor)->Keystrokes->FindKeycode(key, Shift);
		if(i >= 0)
			cmd = CurrentEditor->Keystrokes->Items[i]->Command;
		else
			cmd = (TSynEditorCommand) ecNone;
		switch(key)
		{
			case SYNEDIT_RETURN:
			if((FCompleteWithEnter) && ASSIGNED(OnValidate))
				OnValidate(this, Shift, L'\x00');
			break;
			case SYNEDIT_TAB:
			if((FCompleteWithTab) && ASSIGNED(OnValidate))
				OnValidate(this, Shift, L'\x00');
			break;
			case SYNEDIT_ESCAPE:
			{
				if(ASSIGNED(OnCancel))
					OnCancel(this);
			}
			break;
			case SYNEDIT_LEFT:
			if(Shift == Syncompletionproposal__14)
			{
				if(FCurrentString.Length() > 0)
				{
					CurrentString = CurrentString.SubString(1, CurrentString.Length() - 1);
					if(ASSIGNED(CurrentEditor))
						((TCustomSynEdit*) CurrentEditor)->CommandProcessor((TSynEditorCommand) ecLeft, L'\x00', nullptr);
				}
				else

            //Since we have control, we need to re-send the key to
            //the editor so that the cursor behaves properly
				{
					if(ASSIGNED(CurrentEditor))
						((TCustomSynEdit*) CurrentEditor)->CommandProcessor((TSynEditorCommand) ecLeft, L'\x00', nullptr);
					if(ASSIGNED(OnCancel))
						OnCancel(this);
				}
			}
			else
			ExecuteCmdAndCancel();
			break;
			case SYNEDIT_RIGHT:
			if(Shift == Syncompletionproposal__15)
			{
				if(ASSIGNED(CurrentEditor))
					/*# with CurrentEditor as TCustomSynEdit do */
					{
						auto with0 = (TCustomSynEdit*) CurrentEditor;
						if(with0->CaretX <= with0->LineText.Length())
							C = with0->LineText[with0->CaretX];
						else
							C = L'\x20';
						if(this->IsWordBreakChar(C))
						{
							if(ASSIGNED(OnCancel))
								OnCancel(this);
							else
								;
						}
						else
						CurrentString = CurrentString + String(C);
						with0->CommandProcessor((TSynEditorCommand) ecRight, L'\x00', nullptr);
					}
			}
			else
			ExecuteCmdAndCancel();
			break;
			case SYNEDIT_PRIOR:
			MoveLine(-fLinesInWindow);
			break;
			case SYNEDIT_NEXT:
			MoveLine(fLinesInWindow);
			break;
			case SYNEDIT_END:
			Position = FAssignedList->Count - 1;
			break;
			case SYNEDIT_HOME:
			Position = 0;
			break;
			case SYNEDIT_UP:
			if(Shift.Contains(ssCtrl))
				Position = 0;
			else
				MoveLine(-1);
			break;
			case SYNEDIT_DOWN:
			if(Shift.Contains(ssCtrl))
				Position = FAssignedList->Count - 1;
			else
				MoveLine(1);
			break;
			case SYNEDIT_BACK:
			if(Shift == Syncompletionproposal__16)
			{
				if(FCurrentString.Length() > 0)
				{
					CurrentString = CurrentString.SubString(1, CurrentString.Length() - 1);
					if(ASSIGNED(CurrentEditor))
						((TCustomSynEdit*) CurrentEditor)->CommandProcessor((TSynEditorCommand) ecDeleteLastChar, L'\x00', nullptr);
				}
				else

            //Since we have control, we need to re-send the key to
            //the editor so that the cursor behaves properly
				{
					if(ASSIGNED(CurrentEditor))
						((TCustomSynEdit*) CurrentEditor)->CommandProcessor((TSynEditorCommand) ecDeleteLastChar, L'\x00', nullptr);
					if(ASSIGNED(OnCancel))
						OnCancel(this);
				}
			}
			else
			ExecuteCmdAndCancel();
			break;
			case SYNEDIT_DELETE:
			if(ASSIGNED(CurrentEditor))
				((TCustomSynEdit*) CurrentEditor)->CommandProcessor((TSynEditorCommand) ecDeleteChar, L'\x00', nullptr);
			break;
			default:
			ExecuteCmdAndCancel();
			break;
		}
	}
}

void __fastcall TSynBaseCompletionProposalForm::KeyPress(Char& key)
{
	if(key == L'\x00')
		return;
	if(DisplayType == ctCode)
	{
		switch(key)
		{
			case L'\x0d':
			case L'\x1b':
			;
			break; // These keys are already handled by KeyDown
			case L'\x08':
			if(ASSIGNED(OnKeyPress))
				OnKeyPress(this, key);
			break;
			default:
			if(key >= L'\x20' && key <= High<WideChar>())
			{
				if(IsWordBreakChar(key) && ASSIGNED(OnValidate))
            //if Key = #32 then
            //  OnValidate(Self, [], #0)
            //else
				{
					OnValidate(this, Syncompletionproposal__17, key);
				}
				CurrentString = CurrentString + String(key);
				if(ASSIGNED(OnKeyPress))
					OnKeyPress(this, key);
			}
			else
			{
			/*# with CurrentEditor as TCustomSynEdit do */
			{
				auto with0 = (TCustomSynEdit*) CurrentEditor;
				with0->CommandProcessor((TSynEditorCommand) ecChar, key, nullptr);
			}
			if(ASSIGNED(OnCancel))
				OnCancel(this);
			}
			break;
		}
	}
	Invalidate();
}

void __fastcall TSynBaseCompletionProposalForm::MouseDown(TMouseButton Button, TShiftState Shift, int X, int Y)
{
	Y = (int)((Y - FHeightBuffer) / /*div*/ FEffectiveItemHeight);
	Position = FScrollbar->Position + Y;
//  (CurrentEditor as TCustomSynEdit).UpdateCaret;
}

void __fastcall TSynBaseCompletionProposalForm::Resize()
{
	inherited::Resize();
	if(FEffectiveItemHeight != 0)
		fLinesInWindow = (int)((ClientHeight - FHeightBuffer) / /*div*/ FEffectiveItemHeight);
	if(!(ControlState.Contains(csCreating)))
		AdjustMetrics();
	AdjustScrollBarPosition();
	Invalidate();
}

void __fastcall TSynBaseCompletionProposalForm::Paint()
{

	auto ResetCanvas = [&]() -> void 
	{
		/*# with BITMAP.Canvas do */
		{
			auto with0 = BITMAP->Canvas;
			with0->Pen->Color = StyleServices()->GetSystemColor(fClBackGround);
			with0->Brush->Color = StyleServices()->GetSystemColor(fClBackGround);
			with0->Font->Assign(FFont);
			with0->Font->Color = StyleServices()->GetSystemColor(clWindowText);
		}
	};
	TRect tmpRect = {};
	int TmpX = 0;
	bool AlreadyDrawn = false;
	String TmpString;
	int i = 0;
	int ScaledMargin = 0;
	ScaledMargin = MulDiv(((TSynBaseCompletionProposal*) Owner)->Margin, CurrentPPI, 96);
	if(FDisplayKind == ctCode)
	{
		/*# with BITMAP do */
		{
			auto with1 = BITMAP;
			int stop = 0;
			ResetCanvas();
			with1->Canvas->Pen->Color = StyleServices()->GetSystemColor(clBtnFace);
			with1->Canvas->Rectangle(0, 0, ClientWidth - FScrollbar->Width, ClientHeight);
			for(stop = Min(fLinesInWindow - 1, FAssignedList->Count - 1), i = 0; i <= stop; i++)
			{
				if(i + FScrollbar->Position == Position)
				{
					with1->Canvas->Brush->Color = StyleServices()->GetSystemColor(FClSelect);
					with1->Canvas->Pen->Color = StyleServices()->GetSystemColor(FClSelect);
					with1->Canvas->Rectangle(0, FEffectiveItemHeight * i, ClientWidth - FScrollbar->Width, FEffectiveItemHeight * (i + 1));
					with1->Canvas->Pen->Color = StyleServices()->GetSystemColor(fClSelectText);
					with1->Canvas->Font->Assign(FFont);
					with1->Canvas->Font->Color = StyleServices()->GetSystemColor(fClSelectText);
				}
				AlreadyDrawn = false;
				if(ASSIGNED(OnPaintItem))
					OnPaintItem(this, LogicalToPhysicalIndex(FScrollbar->Position + i), with1->Canvas, Rect(0, FEffectiveItemHeight * i, ClientWidth - FScrollbar->Width, FEffectiveItemHeight * (i + 1)), AlreadyDrawn);
				if(AlreadyDrawn)
					ResetCanvas();
				else
				{
					if(FFormattedText)
					{
						FormattedTextOut(with1->Canvas, Rect(ScaledMargin, FEffectiveItemHeight * i + ((int)((FEffectiveItemHeight - FFontHeight) / /*div*/ 2)), BITMAP->Width, FEffectiveItemHeight * (i + 1)), CurrentPPI, FAssignedList->Strings[FScrollbar->Position + i], (i + FScrollbar->Position == Position), FColumns, FImages);
					}
					else
					{
						with1->Canvas->TextOut(ScaledMargin, FEffectiveItemHeight * i, FAssignedList->Strings[FScrollbar->Position + i]);
					}
					if(i + FScrollbar->Position == Position)
						ResetCanvas();
				}
			}
			if(TStyleManager::IsCustomStyleActive)
			{
				tmpRect = ClientRect;
				DrawStyleEdge(with1->Canvas, tmpRect, Syncompletionproposal__18, Syncompletionproposal__19);
			}
		}
		Canvas->Draw(0, FHeightBuffer, BITMAP);
		if(FTitle != L"")
		{
			/*# with TitleBitmap do */
			{
				auto with2 = TitleBitmap;
				with2->Canvas->Brush->Color = StyleServices()->GetSystemColor(FClTitleBackground);
				tmpRect = Rect(0, 0, ClientWidth + 1, FHeightBuffer);                        //GBN
				with2->Canvas->FillRect(tmpRect);
				with2->Canvas->Pen->Color = StyleServices()->GetSystemColor(clBtnShadow);
				tmpRect.Bottom -= 1;
				with2->Canvas->PenPos = tmpRect.BottomRight();
				with2->Canvas->LineTo(tmpRect.Left - 1, tmpRect.Bottom);
				with2->Canvas->Pen->Color = StyleServices()->GetSystemColor(clBtnFace);
				with2->Canvas->Font->Assign(FTitleFont);
				with2->Canvas->Font->Color = StyleServices()->GetSystemColor(FTitleFont->Color);
				if(CenterTitle)
				{
					TmpX = (int)((with2->Width - with2->Canvas->TextWidth(Title)) / /*div*/ 2);
					if(TmpX < ScaledMargin)
						TmpX = ScaledMargin;  //We still want to be able to read it, even if it does go over the edge
				}
				else
				{
					TmpX = ScaledMargin;
				}
				with2->Canvas->TextRect(tmpRect, TmpX, ScaledMargin - 1, FTitle); // -1 because TmpRect.Top is already 1
			}
			Canvas->Draw(0, 0, TitleBitmap);
		}
	}
	else
	{
		if((FDisplayKind == ctHint) || (FDisplayKind == ctParams))
		{
			/*# with BITMAP do */
			{
				auto with3 = BITMAP;
				int stop = 0;
				ResetCanvas();
				tmpRect = Rect(0, 0, ClientWidth, ClientHeight);
				with3->Canvas->FillRect(tmpRect);
				if(StyleServices()->IsSystemStyle)
					Frame3D(with3->Canvas, tmpRect, cl3DLight, cl3DDkShadow, 1);
				for(stop = FAssignedList->Count - 1, i = 0; i <= stop; i++)
				{
					AlreadyDrawn = false;
					if(ASSIGNED(OnPaintItem))
						OnPaintItem(this, i, with3->Canvas, Rect(0, FEffectiveItemHeight * i + ScaledMargin, ClientWidth, FEffectiveItemHeight * (i + 1) + ScaledMargin), AlreadyDrawn);
					if(AlreadyDrawn)
						ResetCanvas();
					else
					{
						if(FDisplayKind == ctParams)
							TmpString = FormatParamList(FAssignedList->Strings[i], CurrentIndex);
						else
							TmpString = FAssignedList->Strings[i];
						FormattedTextOut(with3->Canvas, Rect(ScaledMargin + 1, FEffectiveItemHeight * i + ((int)((FEffectiveItemHeight - FFontHeight) / /*div*/ 2)) + ScaledMargin, BITMAP->Width - 1, FEffectiveItemHeight * (i + 1) + ScaledMargin), CurrentPPI, TmpString, false, nullptr, FImages);
					}
				}
			}
			Canvas->Draw(0, 0, BITMAP);
		}
	}
}

void __fastcall TSynBaseCompletionProposalForm::ScrollbarOnChange(TObject* Sender)
{
	if(Position < FScrollbar->Position)
		Position = FScrollbar->Position;
	else
	{
		if(Position > FScrollbar->Position + fLinesInWindow - 1)
			Position = FScrollbar->Position + fLinesInWindow - 1;
		else
			Invalidate();
	}
}

void __fastcall TSynBaseCompletionProposalForm::ScrollbarOnScroll(TObject* Sender, TScrollCode ScrollCode, int& ScrollPos)
{
	/*# with CurrentEditor as TCustomSynEdit do */
	{
		auto with0 = (TCustomSynEdit*) CurrentEditor;
		with0->SetFocus();
    //This tricks the caret into showing itself again.
		with0->AlwaysShowCaret = false;
		with0->AlwaysShowCaret = true;
//    UpdateCaret;
	}
}

void __fastcall TSynBaseCompletionProposalForm::ScrollbarOnEnter(TObject* Sender)
{
	ActiveControl = nullptr;
}

void __fastcall TSynBaseCompletionProposalForm::MoveLine(int cnt)
{
	int NewPos = 0;
	NewPos = EnsureRange(Position + cnt, 0, FAssignedList->Count - 1);
	if(NewPos != Position)
		Position = NewPos;
}

int __fastcall TSynBaseCompletionProposalForm::LogicalToPhysicalIndex(int Index)
{
	int result = 0;
	if(FMatchText && (Index >= 0) && (Index < FAssignedList->Count))
		result = (NativeInt) FAssignedList->Objects[Index];
	else
		result = -1;
	return result;
}

int __fastcall TSynBaseCompletionProposalForm::PhysicalToLogicalIndex(int Index)
{
	int result = 0;
	int i = 0;
	if(FMatchText)
	{
		int stop = 0;
		result = -1;
		for(stop = FAssignedList->Count - 1, i = 0; i <= stop; i++)
		{
			if((NativeInt) FAssignedList->Objects[i] == Index)
			{
				result = i;
				break;
			}
		}
	}
	else
	result = Index;
	return result;
}

void __fastcall TSynBaseCompletionProposalForm::SetCurrentString(const String Value)
{

	auto MatchItem = [&](int AIndex, bool UseItemList) -> bool 
	{
		bool result = false;
		String CompareString;
/*    if UseInsertList then
      CompareString := FInsertList[AIndex]
    else
    begin
      CompareString := FItemList[AIndex];

      if UsePrettyText then
        CompareString := StripFormatCommands(CompareString);
    end;*/
		if(UseInsertList)
			CompareString = FInsertList->Strings[AIndex];
		else
		{
			if((FMatchText) && (!UseItemList))
				CompareString = FAssignedList->Strings[AIndex];
			else
				CompareString = FItemList->Strings[AIndex];   //GBN 29/08/2002 Fix for when match text is not active
			if(UsePrettyText)
				CompareString = StripFormatCommands(CompareString);
		}
		CompareString = CompareString.SubString(1, Value.Length());
		if(FCase)
			result = AnsiCompareStr(CompareString, Value) == 0;
		else
			result = AnsiCompareText(CompareString, Value) == 0;
		return result;
	};

	auto RecalcList = [&]() -> void 
	{
		int i = 0;
		int stop = 0;
		FAssignedList->Clear();
		for(stop = FItemList->Count - 1, i = 0; i <= stop; i++)
		{
			if(MatchItem(i, true))
				FAssignedList->AddObject(FItemList->Strings[i], ((TObject*) i));
		}
	};
	int i = 0;
	FCurrentString = Value;
	if(DisplayType != ctCode)
		return;
	if(FMatchText)
	{
		RecalcList();
		AdjustScrollBarPosition();
		Position = 0;
		if(Visible && ASSIGNED(FOnChangePosition) && (DisplayType == ctCode))
			FOnChangePosition((TSynBaseCompletionProposal*) Owner, LogicalToPhysicalIndex(FPosition));
		Invalidate();
	}
	else
	{
		i = 0;
		while((i < ItemList->Count) && (!MatchItem(i, true)))
			++i;
		if(i < ItemList->Count)
			Position = i;
		else
			Position = 0;
	}
}

void __fastcall TSynBaseCompletionProposalForm::SetItemList(TStrings* const Value)
{
	FItemList->Assign((TPersistent*) Value);
	FAssignedList->Assign((TPersistent*) Value);
	CurrentString = CurrentString;
}

void __fastcall TSynBaseCompletionProposalForm::SetInsertList(TStrings* const Value)
{
	FInsertList->Assign((TPersistent*) Value);
}

void __fastcall TSynBaseCompletionProposalForm::DoDoubleClick(TObject* Sender)
{

//we need to do the same as the enter key;
	if(DisplayType == ctCode)
	{
		if(ASSIGNED(OnValidate))
			OnValidate(this, Syncompletionproposal__20, L'\x00');                      //GBN 15/11/2001
	}
}

void __fastcall TSynBaseCompletionProposalForm::SetPosition(int Value)
{
	if(((Value <= 0) && (FPosition == 0)) || (FPosition == Value))
		return;
	if(Value <= FAssignedList->Count - 1)
	{
		FPosition = Value;
		if(Position < FScrollbar->Position)
			FScrollbar->Position = Position;
		else
		{
			if(FScrollbar->Position < (Position - fLinesInWindow + 1))
				FScrollbar->Position = Position - fLinesInWindow + 1;
		}
		if(Visible && ASSIGNED(FOnChangePosition) && (DisplayType == ctCode))
			FOnChangePosition((TSynBaseCompletionProposal*) Owner, LogicalToPhysicalIndex(FPosition));
		Invalidate();
	}
}

void __fastcall TSynBaseCompletionProposalForm::SetResizeable(bool Value)
{
	FResizeable = Value;
	RecreateWnd();
}

void __fastcall TSynBaseCompletionProposalForm::SetItemHeight(int Value)
{
	if(Value != FItemHeight)
	{
		FItemHeight = Value;
		RecalcItemHeight();
	}
}

void __fastcall TSynBaseCompletionProposalForm::SetImages(TCustomImageList* const Value)
{
	if(FImages != Value)
	{
		if(ASSIGNED(FImages))
			FImages->RemoveFreeNotification(this);
		FImages = const_cast<TCustomImageList*>(Value);
		if(ASSIGNED(FImages))
			FImages->FreeNotification(this);
	}
}

void __fastcall TSynBaseCompletionProposalForm::RecalcItemHeight()
{
	Canvas->Font->Assign(FFont);
	FFontHeight = Canvas->TextHeight(TextHeightString);
	if(FItemHeight > 0)
		FEffectiveItemHeight = FItemHeight;
	else
	{
		FEffectiveItemHeight = FFontHeight;
	}
}

void __fastcall TSynBaseCompletionProposalForm::StringListChange(TObject* Sender)
{
	FScrollbar->Position = Position;
}

bool __fastcall TSynBaseCompletionProposalForm::IsWordBreakChar(WideChar AChar)
{
	bool result = false;
	result = ((TSynBaseCompletionProposal*) Owner)->IsWordBreakChar(AChar);
	return result;
}

void __fastcall TSynBaseCompletionProposalForm::WMMouseWheel(::TMessage& Msg)
{
	int nDelta = 0;
	int nWheelClicks = 0;
	if(ComponentState.Contains(csDesigning))
		return;
	if(GetKeyState(VK_CONTROL) >= 0)
		nDelta = Mouse->WheelScrollLines;
	else
		nDelta = fLinesInWindow;
	fMouseWheelAccumulator += ((short int) Msg.WParamHi);
	nWheelClicks = (int)(fMouseWheelAccumulator / /*div*/ WHEEL_DELTA);
	fMouseWheelAccumulator = fMouseWheelAccumulator % WHEEL_DELTA;
	if((nDelta == ((int) WHEEL_PAGESCROLL)) || (nDelta > fLinesInWindow))
		nDelta = fLinesInWindow;
	Position = Position - (nDelta * nWheelClicks);
//  (CurrentEditor as TCustomSynEdit).UpdateCaret;
}

void __fastcall TSynBaseCompletionProposalForm::WMNCHitTest(TWMNCHitTest& Message)
{
	int D = 0;
	TPoint P = {};
	if(!(FResizeable && (DisplayType == ctCode)))
	{
		inherited::Dispatch(&Message);  //#inherited method "WMNCHitTest" not not accessible;
		return;
	}
	D = GetSystemMetrics(SM_CXSIZEFRAME);
	P = this->ScreenToClient(SmallPointToPoint(Message.Pos));
	if(P.Y < D)
	{
		if(P.X < D)
			Message.Result = HTTOPLEFT;
		else
		{
			if(P.X > ClientWidth - D)
				Message.Result = HTTOPRIGHT;
			else
				Message.Result = HTTOP;
		}
	}
	else
	{
		if(P.Y > ClientHeight - D)
		{
			if(P.X < D)
				Message.Result = HTBOTTOMLEFT;
			else
			{
				if(P.X > ClientWidth - D)
					Message.Result = HTBOTTOMRIGHT;
				else
					Message.Result = HTBOTTOM;
			}
		}
		else
		{
			if(P.X < D)
				Message.Result = HTLEFT;
			else
			{
				if(P.X > ClientWidth - D)
					Message.Result = HTRIGHT;
			}
		}
	}
	if(Message.Result == 0)
		inherited::Dispatch(&Message);  //#inherited method "WMNCHitTest" not not accessible;
}

TSynForm* __fastcall GetMDIParent(TSynForm* const Form)
{
	TSynForm* result = nullptr;
	int i = 0;
	int j = 0;
	result = const_cast<TSynForm*>(Form);
	if(Form == nullptr)
		return result;
	if((ObjectIs(Form, TSynForm*)) && (((TForm*) Form)->FormStyle == fsMDIChild))
	{
		int stop = 0;
		for(stop = Screen->FormCount - 1, i = 0; i <= stop; i++)
		{
			/*# with Screen.Forms[i] do */
			{
				
				int stop1 = 0;
				if(Screen->Forms[i]->FormStyle != fsMDIForm)
					continue;
				for(stop1 = Screen->Forms[i]->MDIChildCount - 1, j = 0; j <= stop1; j++)
				{
					if(Screen->Forms[i]->MDIChildren[j] == Form)
					{
						result = Screen->Forms[i];
						return result;
					}
				}
			}
		}
	}
	return result;
}
/* Returns the parent of the specified MDI child form. But, if Form isn't a
  MDI child, it simply returns Form. */

void __fastcall TSynBaseCompletionProposalForm::WMActivate(TWMActivate& Message)
{
	TSynForm* ParentForm = nullptr;
	if(ComponentState.Contains(csDesigning))
	{
		inherited::Dispatch(&Message);  //#inherited method "WMActivate" not not accessible;
		return;
	}
     /*Owner of the component that created me*/
	if(ObjectIs(Owner->Owner, TSynForm*))
		ParentForm = GetMDIParent((TSynForm*) Owner->Owner);
	else
		ParentForm = nullptr;
	if(ASSIGNED(ParentForm) && ParentForm->HandleAllocated())
		SendMessage(ParentForm->Handle, (UINT) WM_NCACTIVATE, int(Message.Active != WA_INACTIVE), 0);
}

void __fastcall TSynBaseCompletionProposalForm::DoFormHide(TObject* Sender)
{
	if(CurrentEditor != nullptr)
	{
		((TCustomSynEdit*) CurrentEditor)->AlwaysShowCaret = OldShowCaret;
//    (CurrentEditor as TCustomSynEdit).UpdateCaret;
		if(((TSynBaseCompletionProposal*) Owner)->FontsAreScaled)
		{
			TitleFont->Height = MulDiv(TitleFont->Height, 96, CurrentEditor->CurrentPPI);
			Font->Height = MulDiv(Font->Height, 96, CurrentEditor->CurrentPPI);
			((TSynBaseCompletionProposal*) Owner)->FontsAreScaled = false;
		}
		if(DisplayType == ctCode)
      // Save after removing the PPI scaling
		{
			((TSynBaseCompletionProposal*) Owner)->FWidth = MulDiv(ClientWidth, 96, CurrentPPI);
			((TSynBaseCompletionProposal*) Owner)->FNbLinesInWindow = fLinesInWindow;
		}
	}
  //GBN 28/08/2002
	if(ASSIGNED(((TSynBaseCompletionProposal*) Owner)->OnClose))
		((TSynBaseCompletionProposal*) Owner)->OnClose(this);
}

void __fastcall TSynBaseCompletionProposalForm::DoFormShow(TObject* Sender)
{
	if(ASSIGNED(CurrentEditor))
	{
		/*# with CurrentEditor as TCustomSynEdit do */
		{
			auto with0 = (TCustomSynEdit*) CurrentEditor;
			OldShowCaret = with0->AlwaysShowCaret;
			with0->AlwaysShowCaret = with0->Focused();
//      UpdateCaret;
		}
	}
  //GBN 28/08/2002
	if(ASSIGNED(((TSynBaseCompletionProposal*) Owner)->OnShow))
		((TSynBaseCompletionProposal*) Owner)->OnShow(this);
}

void __fastcall TSynBaseCompletionProposalForm::WMEraseBackgrnd(::TMessage& Message)
{
	Message.Result = 1;
}

//GBN 24/02/2002

void __fastcall TSynBaseCompletionProposalForm::WMGetDlgCode(TWMGetDlgCode& Message)
{
	inherited::Dispatch(&Message);  //#inherited method "WMGetDlgCode" not not accessible;
	Message.Result = Message.Result | DLGC_WANTTAB;
}

void __fastcall TSynBaseCompletionProposalForm::AdjustMetrics()
{
	if(DisplayType == ctCode)
	{
		if(FTitle != L"")
			FHeightBuffer = FTitleFontHeight + MulDiv(2 * FMargin, CurrentPPI, 96);
		else
			FHeightBuffer = 0;
		if((ClientWidth >= FScrollbar->Width) && (ClientHeight >= FHeightBuffer))
			BITMAP->SetSize(ClientWidth - FScrollbar->Width, ClientHeight - FHeightBuffer);
		if((ClientWidth > 0) && (FHeightBuffer > 0))
			TitleBitmap->SetSize(ClientWidth, FHeightBuffer);
	}
	else
	{
		if((ClientWidth > 0) && (ClientHeight > 0))
			BITMAP->SetSize(ClientWidth, ClientHeight);
	}
}

void __fastcall TSynBaseCompletionProposalForm::AdjustScrollBarPosition()
{
	if(FDisplayKind == ctCode)
	{
		if(ASSIGNED(FScrollbar))
		{
			FScrollbar->Top = FHeightBuffer;
			FScrollbar->Height = ClientHeight - FHeightBuffer;
			FScrollbar->Left = ClientWidth - FScrollbar->Width;
			if(FAssignedList->Count - fLinesInWindow < 0)
			{
				FScrollbar->PageSize = 0;
				FScrollbar->Max = 0;
				FScrollbar->Enabled = false;
			}
			else
			{
				FScrollbar->PageSize = 0;
				FScrollbar->Max = FAssignedList->Count - fLinesInWindow;
				if(FScrollbar->Max != 0)
				{
					FScrollbar->LargeChange = (TScrollBarInc) fLinesInWindow;
					FScrollbar->PageSize = 1;
					FScrollbar->Enabled = true;
				}
				else
				FScrollbar->Enabled = false;
			}
		}
	}
}

void __fastcall TSynBaseCompletionProposalForm::SetTitle(const String Value)
{
	FTitle = Value;
	AdjustMetrics();
}

void __fastcall TSynBaseCompletionProposalForm::SetFont(TFont* const Value)
{
	FFont->Assign((TPersistent*) Value);
	RecalcItemHeight();
	AdjustMetrics();
}

void __fastcall TSynBaseCompletionProposalForm::SetTitleFont(TFont* const Value)
{
	FTitleFont->Assign((TPersistent*) Value);
	FTitleFontHeight = Canvas->TextHeight(TextHeightString);
	AdjustMetrics();
}

void __fastcall TSynBaseCompletionProposalForm::SetColumns(TProposalColumns* Value)
{
	FColumns->Assign(Value);
}

void __fastcall TSynBaseCompletionProposalForm::TitleFontChange(TObject* Sender)
{
	Canvas->Font->Assign(FTitleFont);
	FTitleFontHeight = Canvas->TextHeight(TextHeightString);
	AdjustMetrics();
}

void __fastcall TSynBaseCompletionProposalForm::FontChange(TObject* Sender)
{
	RecalcItemHeight();
	AdjustMetrics();
}

int __fastcall TSynBaseCompletionProposalForm::GetCurrentPPI()
{
	int result = 0;
	if(ASSIGNED(FCurrentEditor))
		result = FCurrentEditor->CurrentPPI;
	else
		result = Screen->PixelsPerInch;
	return result;
}

void __fastcall TSynBaseCompletionProposalForm::Notification(TComponent* AComponent, TOperation Operation)
{
	if(Operation == opRemove)
	{
		if(AComponent == FImages)
			Images = nullptr;
	}
	inherited::Notification(AComponent, Operation);
}


/* TSynBaseCompletionProposal */

__fastcall TSynBaseCompletionProposal::TSynBaseCompletionProposal(TComponent* AOwner)
 : inherited(AOwner),
			FForm(new TSynBaseCompletionProposalForm(this)),
			FWidth(0),
			FDotOffset(0),
			FNbLinesInWindow(0),
			FFontsAreScaled(false),
			FCanExecute(false)
{
	FWidth = 260;
	FNbLinesInWindow = 8;
	EndOfTokenChr = DefaultEndOfTokenChr;
	FDotOffset = 0;
	DefaultType = ctCode;
}

void __fastcall TSynBaseCompletionProposal::Execute(String s, int X, int Y)
{
	ExecuteEx(s, X, Y, DefaultType);
}

void __fastcall TSynBaseCompletionProposal::ExecuteEx(String s, int X, int Y, SynCompletionType Kind/*# = ctCode*/)
{
	TRect WorkArea = {};
	Vcl::Forms::TMonitor* Monitor = nullptr;

	auto GetWorkAreaWidth = [&]() -> int 
	{
		int result = 0;
		result = WorkArea.Right;
		return result;
	};

	auto GetWorkAreaHeight = [&]() -> int 
	{
		int result = 0;
		result = WorkArea.Bottom;
		return result;
	};

	auto GetParamWidth = [&](const String s) -> int 
	{
		int result = 0;
		int i = 0;
		TStringList* List = nullptr;
		int NewWidth = 0;
		List = new TStringList();
		try
		{
			int stop = 0;
			List->CommaText = s;
			result = 0;
			for(stop = List->Count - 1, i = -1; i <= stop; i++)
			{
				NewWidth = FormattedTextWidth(Form->Canvas, FormatParamList(s, i), Form->CurrentPPI, Columns, FForm->Images);
				if(NewWidth > result)
					result = NewWidth;
			}
		}
		__finally
		{
			delete List;
		}
		return result;
	};

	auto RecalcFormPlacement = [&]() -> void 
	{
		int i = 0;
		int TmpWidth = 0;
		int tmpHeight = 0;
		int TmpX = 0;
		int tmpY = 0;
		String TmpStr;
		int NewWidth = 0;
		int ScaledMargin = 0;
		int ActivePPI = 0;
		if(ASSIGNED(FForm->CurrentEditor))
			ActivePPI = FForm->CurrentEditor->CurrentPPI;
		else
			ActivePPI = 96;
		ScaledMargin = MulDiv(Form->Margin, ActivePPI, 96);
		if(!FFontsAreScaled)
		{
			TitleFont->Height = MulDiv(TitleFont->Height, ActivePPI, 96);
			Font->Height = MulDiv(Font->Height, ActivePPI, 96);
			FFontsAreScaled = true;
		}
		TmpX = X;
		tmpY = Y + 2;
		TmpWidth = 0;
		tmpHeight = 0;
		switch(Kind)
		{
			case ctCode:
			{
				TmpWidth = MulDiv(FWidth, ActivePPI, 96);
				tmpHeight = Form->FHeightBuffer + Form->FEffectiveItemHeight * FNbLinesInWindow;
			}
			break;
			case ctHint:
			{
				int stop = 0;
				tmpHeight = Form->FEffectiveItemHeight * ItemList->Count + 2 * ScaledMargin;
				Form->Canvas->Font->Assign(Font);
				for(stop = ItemList->Count - 1, i = 0; i <= stop; i++)
				{
					TmpStr = ItemList->Strings[i];
					NewWidth = FormattedTextWidth(Form->Canvas, TmpStr, Form->CurrentPPI, nullptr, FForm->Images);
					if(NewWidth > TmpWidth)
						TmpWidth = NewWidth;
				}
				TmpWidth += 2 * ScaledMargin;
			}
			break;
			case ctParams:
			{
				int stop = 0;
				tmpHeight = Form->FEffectiveItemHeight * ItemList->Count + 2 * ScaledMargin;
				Form->Canvas->Font->Assign(Font);
				for(stop = ItemList->Count - 1, i = 0; i <= stop; i++)
				{
					NewWidth = GetParamWidth(StripFormatCommands(ItemList->Strings[i]));
					if(ASSIGNED(Form->OnMeasureItem))
						Form->OnMeasureItem(this, i, Form->Canvas, NewWidth);
					if(NewWidth > TmpWidth)
						TmpWidth = NewWidth;
				}
				TmpWidth += 2 * ScaledMargin;
			}
			break;
			default:
			  ;
			break;
		}
		if(TmpX + TmpWidth > GetWorkAreaWidth())
		{
			TmpX = GetWorkAreaWidth() - TmpWidth - MulDiv(5, FForm->CurrentPPI, 96);  //small space buffer
			if(TmpX < 0)
				TmpX = 0;
		}
		if(tmpY + tmpHeight > GetWorkAreaHeight())
		{
			tmpY = tmpY - tmpHeight - ((TCustomSynEdit*) Form->CurrentEditor)->LineHeight - MulDiv(4, FForm->CurrentPPI, 96);
			if(tmpY < 0)
				tmpY = 0;
		}
		Form->ClientWidth = TmpWidth;
		Form->ClientHeight = tmpHeight;
		Form->SetBounds(TmpX, tmpY, Form->Width, Form->Height);
	};
	int TmpOffset = 0;
	Monitor = Screen->MonitorFromPoint(Point(X, Y));
	WorkArea = Monitor->WorkareaRect;
	DisplayType = Kind;
	FCanExecute = true;
	if(ASSIGNED(OnExecute))
		OnExecute(Kind, this, s, X, Y, FCanExecute);
	if((!FCanExecute) || (ItemList->Count == 0))
	{
		if(Form->Visible && (Kind == ctParams))
			Form->Visible = false;
		return;
	}
	Form->PopupMode = pmExplicit;
	if(Kind == ctCode)
		Form->FormStyle = fsStayOnTop;
	if(ASSIGNED(Form->CurrentEditor))
	{
		TmpOffset = ((TCustomSynEdit*) Form->CurrentEditor)->Canvas->TextWidth(s.SubString(1, DotOffset));
		if(DotOffset > 1)
			TmpOffset = TmpOffset + (3 * (DotOffset - 1));
		Form->PopupParent = GetParentForm(Form->CurrentEditor);
	}
	else
	TmpOffset = 0;
	X = X - TmpOffset;
	ResetAssignedList();
	switch(Kind)
	{
		case ctCode:
		if(Form->AssignedList->Count > 0)
      //This may seem redundant, but it fixes scrolling bugs for the first time
      //That is the only time these occur
		{
			Position = 0;
			Form->AdjustScrollBarPosition();
			Form->FScrollbar->Position = Form->Position;
			Form->FScrollbar->Visible = true;
			RecalcFormPlacement();
			Form->Show();
			CurrentString = s;  // bug id 1496148
		}
		break;
		case ctParams:
		case ctHint:
		{
			Form->FScrollbar->Visible = false;
			RecalcFormPlacement();

      //ShowWindow(Form.Handle, SW_SHOWNOACTIVATE);
			ShowWindow(Form->Handle, SW_SHOWNA);
			Form->Visible = true;
			Form->Invalidate();
		}
		break;
		default:
		  ;
		break;
	}
}

String __fastcall TSynBaseCompletionProposal::GetCurrentString()
{
	String result;
	result = Form->CurrentString;
	return result;
}

TStrings* __fastcall TSynBaseCompletionProposal::GetItemList()
{
	TStrings* result = nullptr;
	result = Form->ItemList;
	return result;
}

TStrings* __fastcall TSynBaseCompletionProposal::GetInsertList()
{
	TStrings* result = nullptr;
	result = Form->InsertList;
	return result;
}

TNotifyEvent __fastcall TSynBaseCompletionProposal::GetOnCancel()
{
	TNotifyEvent result;
	result = Form->OnCancel;
	return result;
}

TKeyPressEvent __fastcall TSynBaseCompletionProposal::GetOnKeyPress()
{
	TKeyPressEvent result;
	result = Form->OnKeyPress;
	return result;
}

TSynBaseCompletionProposalPaintItem __fastcall TSynBaseCompletionProposal::GetOnPaintItem()
{
	TSynBaseCompletionProposalPaintItem result;
	result = Form->OnPaintItem;
	return result;
}

TSynBaseCompletionProposalMeasureItem __fastcall TSynBaseCompletionProposal::GetOnMeasureItem()
{
	TSynBaseCompletionProposalMeasureItem result;
	result = Form->OnMeasureItem;
	return result;
}

TValidateEvent __fastcall TSynBaseCompletionProposal::GetOnValidate()
{
	TValidateEvent result;
	result = Form->OnValidate;
	return result;
}

int __fastcall TSynBaseCompletionProposal::GetPosition()
{
	int result = 0;
	result = Form->Position;
	return result;
}

void __fastcall TSynBaseCompletionProposal::SetCurrentString(const String Value)
{
	Form->CurrentString = Value;
}

void __fastcall TSynBaseCompletionProposal::SetItemList(TStrings* const Value)
{
	Form->ItemList = const_cast<TStrings*>(Value);
}

void __fastcall TSynBaseCompletionProposal::SetInsertList(TStrings* const Value)
{
	Form->InsertList = const_cast<TStrings*>(Value);
}

void __fastcall TSynBaseCompletionProposal::SetNbLinesInWindow(int Value)
{
	FNbLinesInWindow = Value;
}

void __fastcall TSynBaseCompletionProposal::SetOnCancel(const TNotifyEvent Value)
{
	Form->OnCancel = Value;
}

void __fastcall TSynBaseCompletionProposal::SetOnKeyPress(const TKeyPressEvent Value)
{
	Form->OnKeyPress = Value;
}

void __fastcall TSynBaseCompletionProposal::SetOnPaintItem(const TSynBaseCompletionProposalPaintItem Value)
{
	Form->OnPaintItem = Value;
}

void __fastcall TSynBaseCompletionProposal::SetOnMeasureItem(const TSynBaseCompletionProposalMeasureItem Value)
{
	Form->OnMeasureItem = Value;
}

void __fastcall TSynBaseCompletionProposal::SetPosition(int Value)
{
	Form->Position = Value;
}

void __fastcall TSynBaseCompletionProposal::SetOnValidate(const TValidateEvent Value)
{
	Form->OnValidate = Value;
}

TColor __fastcall TSynBaseCompletionProposal::GetClSelect()
{
	TColor result = (TColor) 0;
	result = Form->ClSelect;
	return result;
}

void __fastcall TSynBaseCompletionProposal::SetClSelect(const TColor Value)
{
	Form->ClSelect = Value;
}

void __fastcall TSynBaseCompletionProposal::SetWidth(int Value)
{
	FWidth = Value;
}

void __fastcall TSynBaseCompletionProposal::Activate()
{
	if(ASSIGNED(Form))
		Form->Activate();
}

void __fastcall TSynBaseCompletionProposal::Deactivate()
{
	if(ASSIGNED(Form))
		Form->Deactivate();
}

void __fastcall TSynBaseCompletionProposal::DefineProperties(TFiler* Filer)
{
	inherited::DefineProperties(Filer);
}

TColor __fastcall TSynBaseCompletionProposal::GetClBack()
{
	TColor result = (TColor) 0;
	result = Form->clBackground;
	return result;
}

void __fastcall TSynBaseCompletionProposal::SetClBack(const TColor Value)
{
	Form->clBackground = Value;
}

TColor __fastcall TSynBaseCompletionProposal::GetClSelectedText()
{
	TColor result = (TColor) 0;
	result = Form->ClSelectedText;
	return result;
}

void __fastcall TSynBaseCompletionProposal::SetClSelectedText(const TColor Value)
{
	Form->ClSelectedText = Value;
}

void __fastcall TSynBaseCompletionProposal::AddItem(String ADisplayText, String AInsertText)
{
	GetInsertList()->Add(AInsertText);
	GetItemList()->Add(ADisplayText);
}

void __fastcall TSynBaseCompletionProposal::AddItemAt(int Where, String ADisplayText, String AInsertText)
{
	try
	{
		GetInsertList()->Insert(Where, AInsertText);
		GetItemList()->Insert(Where, ADisplayText);
	}
	catch(...)
	{
		throw new Exception(String(L"Cannot insert item at position ") + IntToStr(Where)
	           + L".");
	}
}

void __fastcall TSynBaseCompletionProposal::ClearList()
{
	GetInsertList()->Clear();
	GetItemList()->Clear();
}

String __fastcall TSynBaseCompletionProposal::DisplayItem(int AIndex)
{
	String result;
	result = GetItemList()->Strings[AIndex];
	return result;
}

String __fastcall TSynBaseCompletionProposal::InsertItem(int AIndex)
{
	String result;
	result = GetInsertList()->Strings[AIndex];
	return result;
}

bool __fastcall TSynBaseCompletionProposal::IsWordBreakChar(WideChar AChar)
{
	bool result = false;
	result = false;
	if((Options.Contains(scoConsiderWordBreakChars)) && ASSIGNED(Form) && ASSIGNED(Form->CurrentEditor))
		result = Form->CurrentEditor->IsWordBreakChar(AChar);
	result = result || (Pos(AChar, EndOfTokenChr) > 0);
	return result;
}

SynCompletionType __fastcall TSynBaseCompletionProposal::GetDisplayKind()
{
	SynCompletionType result = ctCode;
	result = Form->DisplayType;
	return result;
}

void __fastcall TSynBaseCompletionProposal::SetDisplayKind(SynCompletionType Value)
{
	Form->DisplayType = Value;
}

TCompletionParameter __fastcall TSynBaseCompletionProposal::GetParameterToken()
{
	TCompletionParameter result;
	result = Form->OnParameterToken;
	return result;
}

void __fastcall TSynBaseCompletionProposal::SetParameterToken(const TCompletionParameter Value)
{
	Form->OnParameterToken = Value;
}

void __fastcall TSynBaseCompletionProposal::SetColumns(TProposalColumns* const Value)
{
	FForm->Columns = const_cast<TProposalColumns*>(Value);
}

TProposalColumns* __fastcall TSynBaseCompletionProposal::GetColumns()
{
	TProposalColumns* result = nullptr;
	result = FForm->Columns;
	return result;
}

bool __fastcall TSynBaseCompletionProposal::GetResizeable()
{
	bool result = false;
	result = FForm->Resizeable;
	return result;
}

void __fastcall TSynBaseCompletionProposal::SetResizeable(bool Value)
{
	if(FForm->Resizeable != Value)
		FForm->Resizeable = Value;
}

int __fastcall TSynBaseCompletionProposal::GetItemHeight()
{
	int result = 0;
	result = FForm->ItemHeight;
	return result;
}

void __fastcall TSynBaseCompletionProposal::SetItemHeight(int Value)
{
	if(FForm->ItemHeight != Value)
		FForm->ItemHeight = Value;
}

void __fastcall TSynBaseCompletionProposal::SetImages(TCustomImageList* const Value)
{
	FForm->Images = const_cast<TCustomImageList*>(Value);
}

TCustomImageList* __fastcall TSynBaseCompletionProposal::GetImages()
{
	TCustomImageList* result = nullptr;
	result = FForm->Images;
	return result;
}

int __fastcall TSynBaseCompletionProposal::GetMargin()
{
	int result = 0;
	result = FForm->Margin;
	return result;
}

void __fastcall TSynBaseCompletionProposal::SetMargin(int Value)
{
	if(Value != FForm->Margin)
		FForm->Margin = Value;
}

SynCompletionType __fastcall TSynBaseCompletionProposal::GetDefaultKind()
{
	SynCompletionType result = ctCode;
	result = Form->DefaultType;
	return result;
}

void __fastcall TSynBaseCompletionProposal::SetDefaultKind(SynCompletionType Value)
{
	Form->DefaultType = Value;
	Form->DisplayType = Value;
	Form->RecreateWnd();
}

void __fastcall TSynBaseCompletionProposal::SetEndOfTokenChar(const String Value)
{
	if(Form->FEndOfTokenChr != Value)
	{
		Form->FEndOfTokenChr = Value;
	}
}

TColor __fastcall TSynBaseCompletionProposal::GetClTitleBackground()
{
	TColor result = (TColor) 0;
	result = Form->ClTitleBackground;
	return result;
}

void __fastcall TSynBaseCompletionProposal::SetClTitleBackground(const TColor Value)
{
	Form->ClTitleBackground = Value;
}

String __fastcall TSynBaseCompletionProposal::GetTitle()
{
	String result;
	result = Form->Title;
	return result;
}

void __fastcall TSynBaseCompletionProposal::SetTitle(const String Value)
{
	Form->Title = Value;
}

TFont* __fastcall TSynBaseCompletionProposal::GetFont()
{
	TFont* result = nullptr;
	result = Form->Font;
	return result;
}

TFont* __fastcall TSynBaseCompletionProposal::GetTitleFont()
{
	TFont* result = nullptr;
	result = Form->TitleFont;
	return result;
}

void __fastcall TSynBaseCompletionProposal::SetFont(TFont* const Value)
{
	Form->Font = const_cast<TFont*>(Value);
}

void __fastcall TSynBaseCompletionProposal::SetTitleFont(TFont* const Value)
{
	Form->TitleFont = const_cast<TFont*>(Value);
}

String __fastcall TSynBaseCompletionProposal::GetEndOfTokenChar()
{
	String result;
	result = Form->EndOfTokenChr;
	return result;
}

TSynCompletionOptions __fastcall TSynBaseCompletionProposal::GetOptions()
{
	TSynCompletionOptions result;
	result = fOptions;
	return result;
}

void __fastcall TSynBaseCompletionProposal::SetOptions(const TSynCompletionOptions Value)
{
	if(fOptions != Value)
	{
		fOptions = Value;
		Form->CenterTitle = Value.Contains(scoTitleIsCentered);
		Form->CaseSensitive = Value.Contains(scoCaseSensitive);
		Form->UsePrettyText = Value.Contains(scoUsePrettyText);
		Form->UseInsertList = Value.Contains(scoUseInsertList);
		Form->MatchText = Value.Contains(scoLimitToMatchedText);
		Form->CompleteWithTab = Value.Contains(scoCompleteWithTab);
		Form->CompleteWithEnter = Value.Contains(scoCompleteWithEnter);
	}
}

String __fastcall TSynBaseCompletionProposal::GetTriggerChars()
{
	String result;
	result = Form->TriggerChars;
	return result;
}

void __fastcall TSynBaseCompletionProposal::SetTriggerChars(const String Value)
{
	Form->TriggerChars = Value;
}

void __fastcall TSynBaseCompletionProposal::EditorCancelMode(TObject* Sender)
{

  //Do nothing here, used in TSynCompletionProposal
}

void __fastcall TSynBaseCompletionProposal::HookedEditorCommand(TObject* Sender, bool AfterProcessing, bool& Handled, TSynEditorCommand& Command, WideChar& AChar, void* Data, void* HandlerData)
{

  // Do nothing here, used in TSynCompletionProposal
}

TCompletionChange __fastcall TSynBaseCompletionProposal::GetOnChange()
{
	TCompletionChange result;
	result = Form->FOnChangePosition;
	return result;
}

void __fastcall TSynBaseCompletionProposal::SetOnChange(const TCompletionChange Value)
{
	Form->FOnChangePosition = Value;
}

void __fastcall TSynBaseCompletionProposal::ResetAssignedList()
{
	Form->AssignedList->Assign(ItemList);
}

/* ----------------  TSynCompletionProposal -------------- */

void __fastcall TSynCompletionProposal::HandleOnCancel(TObject* Sender)
{
	TSynBaseCompletionProposalForm* f = nullptr;
	TCustomSynEdit* CurrentEditor = nullptr;
	f = (TSynBaseCompletionProposalForm*) Sender;
	FNoNextKey = false;
	CurrentEditor = f->CurrentEditor;
	if(CurrentEditor != nullptr)
	{
		if(ASSIGNED(FTimer))
			FTimer->Enabled = false;
		f->Hide();
		if((ObjectIs(((TCustomSynEdit*) CurrentEditor)->Owner, TWinControl*)) && (((TWinControl*) ((TCustomSynEdit*) CurrentEditor)->Owner)->Visible))
		{
			((TWinControl*) ((TCustomSynEdit*) CurrentEditor)->Owner)->SetFocus();
		}
		if(((TCustomSynEdit*) CurrentEditor)->CanFocus())
			((TCustomSynEdit*) CurrentEditor)->SetFocus();
		if(ASSIGNED(OnCancelled))
			OnCancelled(this);
	}
}

void __fastcall TSynCompletionProposal::HandleOnValidate(TObject* Sender, TShiftState Shift, WideChar EndToken)
{
	TSynBaseCompletionProposalForm* f = nullptr;
	String Value;
	int Index = 0;
	f = (TSynBaseCompletionProposalForm*) Sender;
	if(ASSIGNED(f->CurrentEditor))
		/*# with f.CurrentEditor as TCustomSynEdit do */
		{
			auto with0 = (TCustomSynEdit*) f->CurrentEditor;
      //Treat entire completion as a single undo operation
			with0->BeginUpdate();
			with0->BeginUndoBlock();
			try
			{
				if(FAdjustCompletionStart)
					FCompletionStart = BufferCoord(FCompletionStart, with0->CaretY).Char;
				with0->BlockBegin = BufferCoord(FCompletionStart, with0->CaretY);
				if(EndToken == L'\x00')
					with0->BlockEnd = BufferCoord(with0->WordEnd().Char, with0->CaretY);
				else
					with0->BlockEnd = BufferCoord(with0->CaretX, with0->CaretY);
				if(fOptions.Contains(scoUseInsertList))
				{
					if(fOptions.Contains(scoLimitToMatchedText))
					{
						if(Form->FAssignedList->Count > Position)
						{
							if((InsertList->Count > (NativeInt) Form->FAssignedList->Objects[Position]) && ((fOptions.Contains(scoEndCharCompletion)) || (EndToken == L'\x00')))
              // Added check to make sure item is only used when no EndChar
								Value = InsertList->Strings[(NativeInt) Form->FAssignedList->Objects[Position]];
							else
								Value = with0->SelText;
						}
						else
						Value = with0->SelText;
					}
					else

			// Added check to make sure item is only used when no EndChar
					{
						if((InsertList->Count > Position) && ((fOptions.Contains(scoEndCharCompletion)) || (EndToken == L'\x00')))
							Value = InsertList->Strings[Position];
						else
							Value = with0->SelText;
					}
				}
				else

          // Added check to make sure item is only used when no EndChar
				{
					if((Form->FAssignedList->Count > Position) && ((fOptions.Contains(scoEndCharCompletion)) || (EndToken == L'\x00')))
						Value = Form->FAssignedList->Strings[Position];
					else
						Value = with0->SelText;
				}
				Index = Position; // Need to assign position to temp var since it changes later
				if(ASSIGNED(FOnCodeCompletion))
					FOnCodeCompletion(this, Value, Shift, f->LogicalToPhysicalIndex(Index), EndToken); //GBN 15/11/2001
				if(with0->SelText != Value)
					with0->SelText = Value;
				/*# with (f.CurrentEditor as TCustomSynEdit) do */
				{
					auto with1 = ((TCustomSynEdit*) f->CurrentEditor);
          //This replaces the previous way of cancelling the completion by
          //sending a WM_MOUSEDOWN message. The problem with the mouse down is
          //that the editor would bounce back to the left margin, very irritating
					InternalCancelCompletion();
					if(with1->CanFocus())
						with1->SetFocus();
					with1->EnsureCursorPosVisible();
					with1->CaretXY = with1->BlockEnd;
					with1->BlockBegin = with1->CaretXY;
				}
				if(ASSIGNED(FOnAfterCodeCompletion))
					FOnAfterCodeCompletion(this, Value, Shift, f->LogicalToPhysicalIndex(Index), EndToken);
			}
			__finally
			{
				with0->EndUndoBlock();
				with0->EndUpdate();
			}
		}
}

void __fastcall TSynCompletionProposal::HandleOnKeyPress(TObject* Sender, WideChar& key)
{
	TSynBaseCompletionProposalForm* f = nullptr;
	f = (TSynBaseCompletionProposalForm*) Sender;
	if(f->CurrentEditor != nullptr)
	{
		/*# with f.CurrentEditor as TCustomSynEdit do */
		{
			auto with0 = (TCustomSynEdit*) f->CurrentEditor;
			with0->CommandProcessor((TSynEditorCommand) ecChar, key, nullptr);
		}
    //Daisy chain completions
		Application->ProcessMessages();
		if((System::Pos(key, TriggerChars) > 0) && !f->Visible)
		{
			if(ObjectIs(Sender, TCustomSynEdit*))
				DoExecute((TCustomSynEdit*) Sender);
			else
			{
				if(ASSIGNED(Form->CurrentEditor))
					DoExecute((TCustomSynEdit*) Form->CurrentEditor);
			}
		}
	}
}

void __fastcall TSynCompletionProposal::SetEditor(TCustomSynEdit* const Value)
{
	if(Editor != Value)
	{
		if(ASSIGNED(Editor))
			RemoveEditor(Editor);
		FEditor = const_cast<TCustomSynEdit*>(Value);
		if(ASSIGNED(Value))
			AddEditor(const_cast<TCustomSynEdit*>(Value));
	}
}

void __fastcall TSynCompletionProposal::Notification(TComponent* AComponent, TOperation Operation)
{
	if(Operation == opRemove)
	{
		if(Editor == AComponent)
			Editor = nullptr;
		else
		{
			if(ObjectIs(AComponent, TCustomSynEdit*))
				RemoveEditor(((TCustomSynEdit*) AComponent));
		}
	}
	inherited::Notification(AComponent, Operation);
}

__fastcall TSynCompletionProposal::TSynCompletionProposal(TComponent* AOwner)
 : inherited(AOwner),
			fEditors(new TList()),
			FShortCut((TShortCut) 0),
			FNoNextKey(false),
			FCompletionStart(0),
			FAdjustCompletionStart(false),
			FTimer(nullptr),
			FTimerInterval(0),
			FEditor(nullptr)
{
	Form->OnKeyPress = HandleOnKeyPress;
	Form->OnValidate = HandleOnValidate;
	Form->OnCancel = HandleOnCancel;
	Form->OnDblClick = HandleDblClick;
	EndOfTokenChr = DefaultEndOfTokenChr;
	TriggerChars = L".";
	FTimerInterval = 1000;
	FNoNextKey = false;
	FShortCut = Vcl::Menus::ShortCut((WORD) int(L' '), Syncompletionproposal__21);
	Options = DefaultProposalOptions;
}

void __fastcall TSynCompletionProposal::SetShortCut(TShortCut Value)
{
	FShortCut = Value;
}

void __fastcall TSynCompletionProposal::EditorKeyDown(TObject* Sender, WORD& key, TShiftState Shift)
{
	WORD ShortCutKey = 0;
	TShiftState ShortCutShift;
	ShortCutToKey(FShortCut, ShortCutKey, ShortCutShift);
	/*# with Sender as TCustomSynEdit do */
	{
		auto with0 = (TCustomSynEdit*) Sender;
		if(((DefaultType != ctCode) || !(with0->ReadOnly)) && (Shift == ShortCutShift) && (key == ShortCutKey))
		{
			Form->CurrentEditor = (TCustomSynEdit*) Sender;
			key = 0;
			DoExecute((TCustomSynEdit*) Sender);
		}
	}
}

String __fastcall TSynCompletionProposal::GetCurrentInput(TCustomSynEdit* AEditor)
{
	String result;
	String s;
	int i = 0;
	result = L"";
	if(AEditor != nullptr)
	{
		s = AEditor->LineText;
		i = AEditor->CaretX - 1;
		if(i <= s.Length())
		{
			FAdjustCompletionStart = false;
			while((i > 0) && (s[i] > L'\x20') && !this->IsWordBreakChar(s[i]))
				--i;
			FCompletionStart = i + 1;
			result = s.SubString(i + 1, AEditor->CaretX - i - 1);
		}
		else
		FAdjustCompletionStart = true;
		FCompletionStart = i + 1;
	}
	return result;
}

String __fastcall TSynCompletionProposal::GetPreviousToken(TCustomSynEdit* AEditor)
{
	String result;
	String Line;
	int X = 0;
	result = L"";
	if(!ASSIGNED(AEditor))
		return result;
	Line = AEditor->Lines->Strings[AEditor->CaretXY.Line - 1];
	X = AEditor->CaretXY.Char - 1;
	if((X == 0) || (X > Line.Length()) || (Line.Length() == 0))
		return result;
	if(this->IsWordBreakChar(Line[X]))
		--X;
	while((X > 0) && !(this->IsWordBreakChar(Line[X])))
	{
		result = String(Line[X]) + result;
		--X;
	}
	return result;
}

void __fastcall TSynCompletionProposal::EditorKeyPress(TObject* Sender, WideChar& key)
{
	if(FNoNextKey)
	{
		FNoNextKey = false;
		key = L'\x00';
	}
	else
	{
		if(ASSIGNED(FTimer))
		{
			DeactivateTimer();
			if(Pos(key, TriggerChars) != 0)
				ActivateTimer((TCustomSynEdit*) Sender);
		}
	}
}

void __fastcall TSynCompletionProposal::ActivateTimer(TCustomSynEdit* ACurrentEditor)
{
	if(ASSIGNED(FTimer))
	{
		Form->CurrentEditor = ACurrentEditor;
		FTimer->Enabled = true;
	}
}

void __fastcall TSynCompletionProposal::DeactivateTimer()
{
	if(ASSIGNED(FTimer))
	{
		FTimer->Enabled = false;
	}
}

void __fastcall TSynCompletionProposal::HandleDblClick(TObject* Sender)
{
	HandleOnValidate(Sender, Syncompletionproposal__22, L'\x00');
}

__fastcall TSynCompletionProposal::~TSynCompletionProposal()
{
	if(Form->Visible)
		CancelCompletion();
	Editor = nullptr;
	while(fEditors->Count != 0)
		RemoveEditor(((TCustomSynEdit*) fEditors->Last()));
	// inherited;
	delete fEditors;
}

void __fastcall TSynCompletionProposal::TimerExecute(TObject* Sender)
{
	if(!ASSIGNED(FTimer))
		return;
	FTimer->Enabled = false;
	if(Application->Active)
	{
		DoExecute((TCustomSynEdit*) Form->CurrentEditor);
		FNoNextKey = false;
	}
	else
	{
		if(Form->Visible)
		{
			Form->Hide();
			Form->PopupParent = nullptr;
		}
	}
}

int __fastcall TSynCompletionProposal::GetTimerInterval()
{
	int result = 0;
	result = FTimerInterval;
	return result;
}

void __fastcall TSynCompletionProposal::SetTimerInterval(int Value)
{
	FTimerInterval = Value;
	if(ASSIGNED(FTimer))
		FTimer->Interval = (unsigned int) Value;
}

void __fastcall TSynCompletionProposal::SetOptions(const TSynCompletionOptions Value)
{
	inherited::SetOptions(Value);
	if(Value.Contains(scoUseBuiltInTimer))
	{
		if(!(ASSIGNED(FTimer)))
		{
			FTimer = new TTimer(this);
			FTimer->Enabled = false;
			FTimer->Interval = (unsigned int) FTimerInterval;
			FTimer->OnTimer = TimerExecute;
		}
	}
	else
	{
		if(ASSIGNED(FTimer))
		{
			FreeAndNil(&FTimer);
		}
	}
}

void __fastcall TSynCompletionProposal::ExecuteEx(String s, int X, int Y, SynCompletionType Kind/*# = ctCode*/)
{
	inherited::ExecuteEx(s, X, Y, Kind);
	if(ASSIGNED(FTimer))
		FTimer->Enabled = false;
}

void __fastcall TSynCompletionProposal::AddEditor(TCustomSynEdit* AEditor)
{
	int i = 0;
	i = fEditors->IndexOf(AEditor);
	if(i ==  - 1)
	{
		AEditor->FreeNotification(this);
		fEditors->Add(AEditor);
		AEditor->AddKeyDownHandler(EditorKeyDown);
		AEditor->AddKeyPressHandler(EditorKeyPress);
		AEditor->RegisterCommandHandler(HookedEditorCommand, this);
	}
}

int __fastcall TSynCompletionProposal::EditorsCount()
{
	int result = 0;
	result = fEditors->Count;
	return result;
}

TCustomSynEdit* __fastcall TSynCompletionProposal::GetEditor(int i)
{
	TCustomSynEdit* result = nullptr;
	if((i < 0) || (i >= EditorsCount()))
		result = nullptr;
	else
		result = ((TCustomSynEdit*) fEditors->Items[i]);
	return result;
}

bool __fastcall TSynCompletionProposal::RemoveEditor(TCustomSynEdit* AEditor)
{
	bool result = false;
	int i = 0;
	i = fEditors->Remove(AEditor);
	result = i !=  - 1;
	if(result)
	{
		if(Form->CurrentEditor == AEditor)
		{
			if(Form->Visible)
				CancelCompletion();
			Form->CurrentEditor = nullptr;
		}
		AEditor->RemoveKeyDownHandler(EditorKeyDown);
		AEditor->RemoveKeyPressHandler(EditorKeyPress);
		AEditor->UnregisterCommandHandler(HookedEditorCommand);
		RemoveFreeNotification(AEditor);
		if(FEditor == AEditor)
			FEditor = nullptr;
	}
	return result;
}

void __fastcall TSynCompletionProposal::DoExecute(TCustomSynEdit* AEditor)
{
	TPoint P = {};
	int i = 0;
	i = fEditors->IndexOf(AEditor);
	if(i !=  - 1)
		/*# with AEditor do */
		{
			auto with0 = AEditor;
			if((DefaultType != ctCode) || !with0->ReadOnly)
			{
				if(DefaultType == ctHint)
					GetCursorPos(&P);
				else
				{
					P = with0->ClientToScreen(with0->RowColumnToPixels(with0->DisplayXY));
					P.Y += with0->LineHeight;
				}
				Form->CurrentEditor = AEditor;
				FPreviousToken = GetPreviousToken((TCustomSynEdit*) Form->CurrentEditor);
				ExecuteEx(GetCurrentInput(AEditor), P.X, P.Y, DefaultType);
				FNoNextKey = (DefaultType == ctCode) && FCanExecute && Form->Visible;
			}
		}
}

void __fastcall TSynCompletionProposal::InternalCancelCompletion()
{
	if(ASSIGNED(FTimer))
		FTimer->Enabled = false;
	FNoNextKey = false;
	if(Form->Visible)
	{
		Deactivate();
		Form->Hide();
		Form->PopupParent = nullptr;
	}
}

void __fastcall TSynCompletionProposal::CancelCompletion()
{
	InternalCancelCompletion();
	if(ASSIGNED(OnCancelled))
		OnCancelled(this);
}

void __fastcall TSynCompletionProposal::EditorCancelMode(TObject* Sender)
{
	if(DisplayType == ctParams)
		CancelCompletion();
}

void __fastcall TSynCompletionProposal::HookedEditorCommand(TObject* Sender, bool AfterProcessing, bool& Handled, TSynEditorCommand& Command, WideChar& AChar, void* Data, void* HandlerData)
{
	inherited::HookedEditorCommand(Sender, AfterProcessing, Handled, Command, AChar, Data, HandlerData);
	if(AfterProcessing && Form->Visible)
	{
		switch(DisplayType)
		{
			case ctCode:
			break;
			case ctHint:
			{
				CancelCompletion();
			}
			break;
			case ctParams:
			{
				switch(Command)
				{
					case ecLineBreak:
        // So that param completion is not hidden when you display code completion
        //ecGotFocus, ecLostFocus:
        //  CancelCompletion;
					DoExecute((TCustomSynEdit*) Sender);
					break;
					case ecChar:
					{
						switch(AChar)
						{
							case L'\x1b':
							CancelCompletion();
							break;
							case 32: case 33: case 34: case 35: case 36: case 37: case 38: case 39: case 40: case 41:
							 case 42: case 43: case 44: case 45: case 46: case 47: case 48: case 49: case 50: case 51:
							 case 52: case 53: case 54: case 55: case 56: case 57: case 58: case 59: case 60: case 61:
							 case 62: case 63: case 64: case 65: case 66: case 67: case 68: case 69: case 70: case 71:
							 case 72: case 73: case 74: case 75: case 76: case 77: case 78: case 79: case 80: case 81:
							 case 82: case 83: case 84: case 85: case 86: case 87: case 88: case 89: case 90: case 91:
							 case 92: case 93: case 94: case 95: case 96: case 97: case 98: case 99: case 100: case 101:
							 case 102: case 103: case 104: case 105: case 106: case 107: case 108: case 109: case 110: case 111:
							 case 112: case 113: case 114: case 115: case 116: case 117: case 118: case 119: case 120: case 121:
							 case 122:
							/*# with Form do */
							{
								auto with0 = Form;
/*                if Pos(AChar, FTriggerChars) > 0 then
                begin
                  if Assigned(FParameterToken) then
                  begin
                    TmpIndex := CurrentIndex;
                    TmpLevel := CurrentLevel;
                    TmpStr := CurrentString;
                    OnParameterToken(Self, CurrentIndex, TmpLevel, TmpIndex, AChar, TmpStr);
                    CurrentIndex := TmpIndex;
                    CurrentLevel := TmpLevel;
                    CurrentString := TmpStr;
                  end;
                end;*/
								DoExecute((TCustomSynEdit*) Sender);
							}
							break;
							default:
							DoExecute((TCustomSynEdit*) Sender);
							break;
						}
					}
					break;
					default:
					DoExecute((TCustomSynEdit*) Sender);
					break;
				}
			}
			break;
			default:
			  ;
			break;
		}
	}
	else
	{
		if((!Form->Visible) && ASSIGNED(FTimer))
		{
			if(Command == ecChar)
			{
				if(Pos(AChar, TriggerChars) == 0)
					FTimer->Enabled = false;
				else
					;
			}
			else
			FTimer->Enabled = false;
		}
	}
}

void __fastcall TSynCompletionProposal::ActivateCompletion()
{
	DoExecute(Editor);
	FNoNextKey = false;   //  Synedit bug report 1496151
}



/* TSynAutoComplete */

__fastcall TSynAutoComplete::TSynAutoComplete(TComponent* AOwner)
 : inherited(AOwner),
			FShortCut(Vcl::Menus::ShortCut((WORD) int(L' '), Syncompletionproposal__23)),
			FEditor(nullptr),
			fAutoCompleteList(nullptr),
			FNoNextKey(false),
			FInternalCompletion(nullptr),
			FDoLookup(false)
{
	FDoLookup = true;
	CreateInternalCompletion();
	FEndOfTokenChr = DefaultEndOfTokenChr;
	fAutoCompleteList = new TStringList();
	FNoNextKey = false;
}

void __fastcall TSynAutoComplete::SetShortCut(TShortCut Value)
{
	FShortCut = Value;
}

__fastcall TSynAutoComplete::~TSynAutoComplete()
{
	Editor = nullptr;
	if(ASSIGNED(FInternalCompletion))
	{
		delete FInternalCompletion;
		FInternalCompletion = nullptr;
	}
	// inherited;
	delete fAutoCompleteList;
}

void __fastcall TSynAutoComplete::EditorKeyDown(TObject* Sender, WORD& key, TShiftState Shift)
{
	WORD ShortCutKey = 0;
	TShiftState ShortCutShift;
	ShortCutToKey(FShortCut, ShortCutKey, ShortCutShift);
	if(!((TCustomSynEdit*) Sender)->ReadOnly && (Shift == ShortCutShift) && (key == ShortCutKey))
	{
		Execute(GetPreviousToken((TCustomSynEdit*) Sender), (TCustomSynEdit*) Sender);
		FNoNextKey = true;
		key = 0;
	}
}

void __fastcall TSynAutoComplete::EditorKeyPress(TObject* Sender, WideChar& key)
{
	if(FNoNextKey)
	{
		FNoNextKey = false;
		key = L'\x00';
	}
}

void __fastcall TSynAutoComplete::Execute(String Token, TCustomSynEdit* Editor)
{
	ExecuteEx(Token, Editor, FDoLookup);
}

void __fastcall TSynAutoComplete::ExecuteEx(String Token, TCustomSynEdit* Editor, bool LookupIfNotExact)
{
	String Temp;
	int i = 0;
	int j = 0;
	TBufferCoord StartOfBlock = {};
	bool ChangedIndent = false;
	bool ChangedTrailing = false;
	TSynEditorOptions TmpOptions;
	TSynEditorOptions OrigOptions;
	int BeginningSpaceCount = 0;
	String Spacing;
	if(ASSIGNED(OnBeforeExecute))
		OnBeforeExecute(this);
	try
	{
		i = AutoCompleteList->IndexOf(Token);
		if((Token.Length() > 0) && (i !=  - 1))
		{
			Editor->Lines->BeginUpdate();
			Editor->BeginUndoBlock();
			try
			{
				int stop = 0;
				TmpOptions = Editor->Options;
				OrigOptions = Editor->Options;
				ChangedIndent = TmpOptions.Contains(eoAutoIndent);
				ChangedTrailing = TmpOptions.Contains(eoTrimTrailingSpaces);
				if(ChangedIndent)
					TmpOptions >> eoAutoIndent;
				if(ChangedTrailing)
					TmpOptions >> eoTrimTrailingSpaces;
				if(ChangedIndent || ChangedTrailing)
					Editor->Options = TmpOptions;
				FNoNextKey = true;
				for(stop = Token.Length(), j = 1; j <= stop; j++)
				{
					Editor->CommandProcessor((TSynEditorCommand) ecDeleteLastChar, L' ', nullptr);
				}
				BeginningSpaceCount = Editor->DisplayX - 1;
				if(!(Editor->Options.Contains(eoTabsToSpaces)) && (BeginningSpaceCount >= Editor->TabWidth))
					Spacing = StringOfChar(L'\x09', (int)(BeginningSpaceCount / /*div*/ Editor->TabWidth))
	           + StringOfChar(L' ', BeginningSpaceCount % Editor->TabWidth);
				else
					Spacing = StringOfChar(L' ', BeginningSpaceCount);
				++i;
				if((i < AutoCompleteList->Count) && (AutoCompleteList->Strings[i].Length() > 0) && (((String)AutoCompleteList->Strings[i])[1] == L'|'))
				{
					++i;
				}
				StartOfBlock.Char = -1;
				StartOfBlock.Line = -1;
				while((i < AutoCompleteList->Count) && (AutoCompleteList->Strings[i].Length() > 0) && (((String)AutoCompleteList->Strings[i])[1] == L'='))

    /*      for j := 0 to PrevSpace - 1 do
            Editor.CommandProcessor(ecDeleteLastChar, ' ', nil);*/
				{
					int stop = 0;
					Temp = AutoCompleteList->Strings[i];
					for(stop = Temp.Length(), j = 2; j <= stop; j++)
					{
						if(Temp[j] == L'\x09')
							Editor->CommandProcessor((TSynEditorCommand) ecTab, Temp[j], nullptr);
						else
							Editor->CommandProcessor((TSynEditorCommand) ecChar, Temp[j], nullptr);
						if(Temp[j] == L'|')
							StartOfBlock = Editor->CaretXY;
					}
					++i;
					if((i < AutoCompleteList->Count) && (AutoCompleteList->Strings[i].Length() > 0) && (((String)AutoCompleteList->Strings[i])[1] == L'='))
					{
						int stop = 0;
						Editor->CommandProcessor((TSynEditorCommand) ecLineBreak, L' ', nullptr);
						for(stop = Spacing.Length(), j = 1; j <= stop; j++)
						{
							if(Spacing[j] == L'\x09')
								Editor->CommandProcessor((TSynEditorCommand) ecTab, L'\x09', nullptr);
							else
								Editor->CommandProcessor((TSynEditorCommand) ecChar, L' ', nullptr);
						}
					}
				}
				if((StartOfBlock.Char !=  - 1) && (StartOfBlock.Line !=  - 1))
				{
					Editor->CaretXY = StartOfBlock;
					Editor->CommandProcessor((TSynEditorCommand) ecDeleteLastChar, L' ', nullptr);
				}
				if(ChangedIndent || ChangedTrailing)
					Editor->Options = OrigOptions;
				FNoNextKey = false;
			}
			__finally
			{
				Editor->EndUndoBlock();
				Editor->Lines->EndUpdate();
			}
		}
		else
		{
			if(LookupIfNotExact && ASSIGNED(FInternalCompletion))
			{
				int stop = 0;
				FInternalCompletion->AddEditor(Editor);
				FInternalCompletion->ClearList();
				for(stop = AutoCompleteList->Count - 1, i = 0; i <= stop; i++)
				{
					if((AutoCompleteList->Strings[i].Length() > 0) && (((String)AutoCompleteList->Strings[i])[1] != L'=') && (((String)AutoCompleteList->Strings[i])[1] != L'|'))
					{
						if((i + 1 < AutoCompleteList->Count) && (AutoCompleteList->Strings[i + 1].Length() > 0) && (((String)AutoCompleteList->Strings[i + 1])[1] == L'|'))
						{
							Temp = AutoCompleteList->Strings[i + 1];
							Temp.Delete(1, 	1);
						}
						else
						Temp = AutoCompleteList->Strings[i];
						Temp = String(L"\\style{+B}") + AutoCompleteList->Strings[i]
						           + L"\\style{-B}\\column{}"
						           + Temp;
						FInternalCompletion->ItemList->Add(Temp);
						FInternalCompletion->InsertList->Add(AutoCompleteList->Strings[i]);
					}
				}
				FInternalCompletion->DoExecute(Editor);
			}
		}
	}
	__finally
	{
		if(ASSIGNED(OnAfterExecute))
			OnAfterExecute(this);
	}
}

void __fastcall TSynAutoComplete::DoInternalAutoCompletion(TObject* Sender, const String Value, TShiftState Shift, int Index, WideChar EndToken)
{
	ExecuteEx(GetPreviousToken(Editor), Editor, false);
	FInternalCompletion->Editor = nullptr;
}

String __fastcall TSynAutoComplete::GetPreviousToken(TCustomSynEdit* Editor)
{
	String result;
	String s;
	int i = 0;
	result = L"";
	if(Editor != nullptr)
	{
		s = Editor->LineText;
		i = Editor->CaretX - 1;
		if(i <= s.Length())
		{
			while((i > 0) && (s[i] > L' ') && (Pos(s[i], FEndOfTokenChr) == 0))
				--i;
			result = s.SubString(i + 1, Editor->CaretX - i - 1);
		}
	}
	return result;
}

void __fastcall TSynAutoComplete::Notification(TComponent* AComponent, TOperation Operation)
{
	if((Operation == opRemove) && (Editor == AComponent))
		Editor = nullptr;
	inherited::Notification(AComponent, Operation);
}

void __fastcall TSynAutoComplete::SetAutoCompleteList(TStrings* List)
{
	fAutoCompleteList->Assign(List);
}

void __fastcall TSynAutoComplete::SetEditor(TCustomSynEdit* const Value)
{
	if(Editor != Value)
	{
		if(Editor != nullptr)
		{
			Editor->RemoveKeyDownHandler(EditorKeyDown);
			Editor->RemoveKeyPressHandler(EditorKeyPress);
			RemoveFreeNotification(Editor);
		}
		FEditor = const_cast<TCustomSynEdit*>(Value);
		if(Editor != nullptr)
		{
			Editor->AddKeyDownHandler(EditorKeyDown);
			Editor->AddKeyPressHandler(EditorKeyPress);
			FreeNotification(Editor);
		}
	}
}

String __fastcall TSynAutoComplete::GetTokenList()
{
	String result;
	TStringList* List = nullptr;
	int i = 0;
	result = L"";
	if(AutoCompleteList->Count < 1)
		return result;
	List = new TStringList();
	i = 0;
	while((i < AutoCompleteList->Count))
	{
		if((AutoCompleteList->Strings[i].Length() > 0) && (((String)AutoCompleteList->Strings[i])[1] != L'='))
			List->Add(Trim(AutoCompleteList->Strings[i]));
		++i;
	}
	result = List->Text;
	delete List;
	return result;
}

String __fastcall TSynAutoComplete::GetTokenValue(String Token)
{
	String result;
	int i = 0;
	TStringList* List = nullptr;
	result = L"";
	i = AutoCompleteList->IndexOf(Token);
	if(i !=  - 1)
	{
		List = new TStringList();
		++i;
		while((i < AutoCompleteList->Count) && (AutoCompleteList->Strings[i].Length() > 0) && (((String)AutoCompleteList->Strings[i])[1] == L'='))
		{
			if(AutoCompleteList->Strings[i].Length() == 1)
				List->Add(L"");
			else
				List->Add(AutoCompleteList->Strings[i].SubString(2, AutoCompleteList->Strings[i].Length()));
			++i;
		}
		result = List->Text;
		delete List;
	}
	return result;
}

void __fastcall TSynAutoComplete::SetDoLookup(bool Value)
{
	FDoLookup = Value;
	if(FDoLookup && !ASSIGNED(FInternalCompletion))
		CreateInternalCompletion();
	else
	{
		if(!FDoLookup && ASSIGNED(FInternalCompletion))
		{
			delete FInternalCompletion;
			FInternalCompletion = nullptr;
		}
	}
}

void __fastcall TSynAutoComplete::CreateInternalCompletion()
{
	FInternalCompletion = new TSynCompletionProposal(this);
	FInternalCompletion->Options = DefaultProposalOptions + Syncompletionproposal__24 - Syncompletionproposal__25;
	FInternalCompletion->EndOfTokenChr = FEndOfTokenChr;
	FInternalCompletion->ShortCut = (TShortCut) 0;
	FInternalCompletion->OnAfterCodeCompletion = DoInternalAutoCompletion;
	FInternalCompletion->Columns->Add();
	FInternalCompletion->Width = 350;
}

TSynCompletionOptions __fastcall TSynAutoComplete::GetOptions()
{
	TSynCompletionOptions result;
	result = fOptions;
	return result;
}

void __fastcall TSynAutoComplete::SetOptions(const TSynCompletionOptions Value)
{
	fOptions = Value;
	if(ASSIGNED(FInternalCompletion))
		FInternalCompletion->Options = fOptions + Syncompletionproposal__26 - Syncompletionproposal__27;
}

void __fastcall TSynAutoComplete::CancelCompletion()
{
	if(ASSIGNED(FInternalCompletion))
		FInternalCompletion->CancelCompletion();
}

TSynCompletionProposal* __fastcall TSynAutoComplete::GetCompletionProposal()
{
	TSynCompletionProposal* result = nullptr;
	result = FInternalCompletion;
	return result;
}

bool __fastcall TSynAutoComplete::GetExecuting()
{
	bool result = false;
	if(ASSIGNED(FInternalCompletion))
		result = FInternalCompletion->Form->Visible;
	else
		result = false;
	return result;
}


}  // namespace SynCompletionProposal

