#include <vcl.h>
#pragma hdrstop

#include "FormMain_ctParams.h"
#include "SynEditTypes.h"
#include "d2c_dfm.h"

using namespace std;
using namespace d2c_system;


TForm1* Form1 = nullptr;

void __fastcall TForm1::scpParamsExecute(SynCompletionType Kind, TObject* Sender, UnicodeString& AString, int& x, int& y, bool& CanExecute)
{
	UnicodeString locline;
	UnicodeString lookup;
	int TmpX = 0;
	int savepos = 0;
	int StartX = 0;
	int ParenCounter = 0;
	int TmpLocation = 0;
	bool FoundMatch = false;
  //Param Completion is different than Code Completion.  We can't just use
  //the string passed to us we have to figure out what they are looking for,
  //which is language dependant For this demo, I assume that it has to be on the
  //*same* line, then do some paren checking.  For the sake of the demo, the
  //function will be the word directly before the paren.  In other languages you
  //would want to do something like grab everything before the last end of
  //statement char (like in ObjectPascal it's the ';' char).  It *does* support
  //embedded functions (Hense the paren checking).  In this case, commas are the
  //delimiter so they are incremented accordingly.

  //Also everything is hard coded in.  You will want to have some kind of
  //structure that you are using instead of hard coding the parameters in
	/*# with TSynCompletionProposal(Sender).Editor do */
	{
		auto with0 = ((TSynCompletionProposal*) Sender)->Editor;
		locline = with0->LineText;

    //go back from the cursor and find the first open paren
		TmpX = with0->CaretX;
		if(TmpX > locline.Length())
			TmpX = locline.Length();
		else
			--TmpX;
		FoundMatch = false;
		TmpLocation = 0;
		while((TmpX > 0) && !(FoundMatch))
		{
			if(locline[TmpX] == L',')
			{
				++TmpLocation;
				--TmpX;
			}
			else
			{
				if(locline[TmpX] == L')')
        //We found a close, go till it's opening paren
				{
					ParenCounter = 1;
					--TmpX;
					while((TmpX > 0) && (ParenCounter > 0))
					{
						if(locline[TmpX] == L')')
							++ParenCounter;
						else
						{
							if(locline[TmpX] == L'(')
								--ParenCounter;
						}
						--TmpX;
					}
					if(TmpX > 0)
						--TmpX;  //eat the open paren
				}
				else
				{
					if(locline[TmpX] == L'(')
        //we have a valid open paren, lets see what the word before it is
					{
						StartX = TmpX;
						while((TmpX > 0) && !SynEdit1->IsIdentChar(locline[TmpX]))
							--TmpX;
						if(TmpX > 0)
						{
							savepos = TmpX;
							while((TmpX > 0) && SynEdit1->IsIdentChar(locline[TmpX]))
								--TmpX;
							++TmpX;
							lookup = UpperCase(locline.SubString(TmpX, savepos - TmpX + 1));
							FoundMatch = LookupList->IndexOf(lookup) > -1;
							if(!(FoundMatch))
							{
								TmpX = StartX;
								--TmpX;
							}
						}
					}
					else
					--TmpX;
				}
			}
		}
	}
	CanExecute = FoundMatch;
	if(CanExecute)
	{
		((TSynCompletionProposal*) Sender)->Form->CurrentIndex = TmpLocation;
		if(lookup != ((TSynCompletionProposal*) Sender)->PreviousToken)
		{
			((TSynCompletionProposal*) Sender)->ItemList->Clear();
			if(lookup == L"TESTFUNCTION")
			{
				((TSynCompletionProposal*) Sender)->ItemList->Add(L"\"FirstParam: integer\", \"SecondParam: integer\", \"ThirdParam: string\"");
			}
			else
			{
				if(lookup == L"MIN")
				{
					((TSynCompletionProposal*) Sender)->ItemList->Add(L"\"A: integer\", \"B: integer\"");
				}
				else
				{
					if(lookup == L"MAX")
					{
						((TSynCompletionProposal*) Sender)->ItemList->Add(L"\"A: integer\", \"B: integer\"");
					}
				}
			}
		}
	}
	else
	((TSynCompletionProposal*) Sender)->ItemList->Clear();
}

void __fastcall TForm1::FormCreate(TObject* Sender)
{
	LookupList = new TStringList();
	LookupList->Add(L"TESTFUNCTION");
	LookupList->Add(L"MAX");
	LookupList->Add(L"MIN");
	scpParams->EndOfTokenChr = L"";
}

void __fastcall TForm1::FormDestroy(TObject* Sender)
{
	delete LookupList;
}

void __fastcall TForm1::FormShow(TObject* Sender)
{
	SynEdit1->SetFocus();
}

void __fastcall TForm1::Button3Click(TObject* Sender)
{
	FontDialog1->Font->Assign(scpParams->Font);
	if(FontDialog1->Execute())
		scpParams->Font->Assign(FontDialog1->Font);
}

__fastcall TForm1::TForm1(TComponent* AOwner, int Dummy)
	 : inherited(AOwner, Dummy),
	SynTest(nullptr),
	SynEdit1(nullptr),
	Button3(nullptr),
	scpParams(nullptr),
	FontDialog1(nullptr)
{
	//----- start initializations from the dfm-file -----------------------------
	ComponentState << csLoading;
	Left = 256;
	Top = 122;
	Width = 754;
	Height = 541;
	Caption = L"Form1";
	Color = clBtnFace;
	Font->Charset = DEFAULT_CHARSET;
	Font->Color = clWindowText;
	Font->Height = -11;
	Font->Name = L"MS Sans Serif";
	Font->Style = (TFontStyles());
	AssignFormOldCreateOrder(this, false);
	OnCreate = FormCreate;
	OnDestroy = FormDestroy;
	OnShow = FormShow;
	AssignFormPixelsPerInch(this, 96);
	AssignFormTextHeight(this, 13);
	SynTest = new TSynEdit(this);
	SynTest->Parent = this;
	SynTest->Left = 416;
	SynTest->Top = 8;
	SynTest->Width = 321;
	SynTest->Height = 497;
	SynTest->Font->Charset = DEFAULT_CHARSET;
	SynTest->Font->Color = clWindowText;
	SynTest->Font->Height = -13;
	SynTest->Font->Name = L"Courier New";
	SynTest->Font->Style = (TFontStyles());
	SynTest->TabOrder = 0;
	SynTest->Gutter->Font->Charset = DEFAULT_CHARSET;
	SynTest->Gutter->Font->Color = clWindowText;
	SynTest->Gutter->Font->Height = -11;
	SynTest->Gutter->Font->Name = L"Terminal";
	SynTest->Gutter->Font->Style = (TFontStyles());
	SynTest->Gutter->Visible = false;
	SynTest->Lines->Add(L"This is a Demo to show you how the ");
	SynTest->Lines->Add(L"Code Completion component works ");
	SynTest->Lines->Add(L"when the default kind is ctParams.");
	SynTest->Lines->Add(L"");
	SynTest->Lines->Add(L"Everything really depends on the");
	SynTest->Lines->Add(L"code you put in the execute event.");
	SynTest->Lines->Add(L"This determines what the parameters");
	SynTest->Lines->Add(L"are and what index should be");
	SynTest->Lines->Add(L"highlighted.");
	SynTest->Lines->Add(L"");
	SynTest->Lines->Add(L"See the source file execute event");
	SynTest->Lines->Add(L"for more information.");
//	GetTSynEditRemovedKeystrokes(SynTest, 0)->Command = ecContextHelp;
//	GetTSynEditRemovedKeystrokes(SynTest, 0)->ShortCut = 112;
//	SynTest->AddedKeystrokes->Add();
//	SynTest->AddedKeystrokes->AddedKeystrokes[0]->Command = ecContextHelp;
//	SynTest->AddedKeystrokes->AddedKeystrokes[0]->ShortCut = 16496;
	SynEdit1 = new TSynEdit(this);
	SynEdit1->Parent = this;
	SynEdit1->Left = 6;
	SynEdit1->Top = 96;
	SynEdit1->Width = 401;
	SynEdit1->Height = 401;
	SynEdit1->Font->Charset = DEFAULT_CHARSET;
	SynEdit1->Font->Color = clWindowText;
	SynEdit1->Font->Height = -13;
	SynEdit1->Font->Name = L"Courier New";
	SynEdit1->Font->Style = (TFontStyles());
	SynEdit1->TabOrder = 1;
	SynEdit1->Gutter->Font->Charset = DEFAULT_CHARSET;
	SynEdit1->Gutter->Font->Color = clWindowText;
	SynEdit1->Gutter->Font->Height = -11;
	SynEdit1->Gutter->Font->Name = L"Terminal";
	SynEdit1->Gutter->Font->Style = (TFontStyles());
	SynEdit1->Lines->Add(L"Use Shift+Ctrl+Space to activate Parameter");
	SynEdit1->Lines->Add(L"completion, or type the function name");
	SynEdit1->Lines->Add(L"and the \x27" L"(\x27" L" (open paren) to start it with");
	SynEdit1->Lines->Add(L"the timer.");
	SynEdit1->Lines->Add(L"");
	SynEdit1->Lines->Add(L"The valid functions for this example are");
	SynEdit1->Lines->Add(L"");
	SynEdit1->Lines->Add(L"TestFunction");
	SynEdit1->Lines->Add(L"Min");
	SynEdit1->Lines->Add(L"Max");
	SynEdit1->Lines->Add(L"");
	SynEdit1->Lines->Add(L"Below is an example using paren Counting:");
	SynEdit1->Lines->Add(L"Max(a + b(1 + 2), (3 + 4) * c)");
	SynEdit1->Lines->Add(L"");
	SynEdit1->Lines->Add(L"Here is an example of embeded functions");
	SynEdit1->Lines->Add(L"");
	SynEdit1->Lines->Add(L"TestFunction(Min(a, b), SomeVar, Another)");
//	GetTSynEditRemovedKeystrokes(SynEdit1, 0)->Command = ecContextHelp;
//	GetTSynEditRemovedKeystrokes(SynEdit1, 0)->ShortCut = 112;
//	SynEdit1->AddedKeystrokes->Add();
//	SynEdit1->AddedKeystrokes->AddedKeystrokes[0]->Command = ecContextHelp;
//	SynEdit1->AddedKeystrokes->AddedKeystrokes[0]->ShortCut = 16496;
	Button3 = new TButton(this);
	Button3->Parent = this;
	Button3->Left = 8;
	Button3->Top = 40;
	Button3->Width = 75;
	Button3->Height = 25;
	Button3->Caption = L"Font";
	Button3->TabOrder = 2;
	Button3->OnClick = Button3Click;
	scpParams = new TSynCompletionProposal(this);
	scpParams->DefaultType = ctParams;
	scpParams->Options = (TSynCompletionOptions() << scoLimitToMatchedText << scoUsePrettyText << scoUseBuiltInTimer);
	scpParams->ClBackground = clInfoBk;
	scpParams->Width = 262;
	scpParams->EndOfTokenChr = L"()[]. ";
	scpParams->TriggerChars = L"(";
	scpParams->Font->Charset = DEFAULT_CHARSET;
	scpParams->Font->Color = clWindowText;
	scpParams->Font->Height = -11;
	scpParams->Font->Name = L"MS Sans Serif";
	scpParams->Font->Style = (TFontStyles());
	scpParams->TitleFont->Charset = DEFAULT_CHARSET;
	scpParams->TitleFont->Color = clBtnText;
	scpParams->TitleFont->Height = -11;
	scpParams->TitleFont->Name = L"MS Sans Serif";
	scpParams->TitleFont->Style = (TFontStyles() << fsBold);
	// scpParams->Columns =
	scpParams->OnExecute = scpParamsExecute;
	scpParams->ShortCut = 24608;
	scpParams->TimerInterval = 1200;
	// non-visible component: Left
	FontDialog1 = new TFontDialog(this);
	FontDialog1->Font->Charset = DEFAULT_CHARSET;
	FontDialog1->Font->Color = clWindowText;
	FontDialog1->Font->Height = -11;
	FontDialog1->Font->Name = L"MS Sans Serif";
	FontDialog1->Font->Style = (TFontStyles());
	// non-visible component: Left
	ComponentState >> csLoading;
	//----- shifted initializations from the dfm-file ---------------------------
	scpParams->Editor = SynEdit1;
	//----- end of initializations from the dfm-file ----------------------------
}

