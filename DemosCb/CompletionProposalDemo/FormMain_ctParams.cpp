#include <vcl.h>
#pragma hdrstop

#include "FormMain_ctParams.h"
#include "SynEditTypes.h"

using namespace std;
using namespace d2c_system;

__fastcall TForm1::TForm1(TComponent* AOwner) : inherited(AOwner) {}


TForm1* Form1 = nullptr;
#pragma resource "*.DFM" 


void __fastcall TForm1::scpParamsExecute(SynCompletionType Kind, TObject* Sender, UnicodeString& AString, int& X, int& Y, bool& CanExecute)
{
	UnicodeString locline;
	UnicodeString Lookup;
	int TmpX = 0;
	int SavePos = 0;
	int startX = 0;
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
			TmpX = (int) locline.Length();
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
						startX = TmpX;
						while((TmpX > 0) && !SynEdit1->IsIdentChar(locline[TmpX]))
							--TmpX;
						if(TmpX > 0)
						{
							SavePos = TmpX;
							while((TmpX > 0) && SynEdit1->IsIdentChar(locline[TmpX]))
								--TmpX;
							++TmpX;
							Lookup = UpperCase(locline.SubString(TmpX, SavePos - TmpX + 1));
							FoundMatch = LookupList->IndexOf(Lookup) >  - 1;
							if(!(FoundMatch))
							{
								TmpX = startX;
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
		if(Lookup != ((TSynCompletionProposal*) Sender)->PreviousToken)
		{
			((TSynCompletionProposal*) Sender)->ItemList->Clear();
			if(Lookup == L"TESTFUNCTION")
			{
				((TSynCompletionProposal*) Sender)->ItemList->Add(L"\"FirstParam: integer\", \"SecondParam: integer\", \"ThirdParam: string\"");
			}
			else
			{
				if(Lookup == L"MIN")
				{
					((TSynCompletionProposal*) Sender)->ItemList->Add(L"\"A: integer\", \"B: integer\"");
				}
				else
				{
					if(Lookup == L"MAX")
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
	SynTest = new TSynEdit(this);
	SynTest->Parent = this;
	SynTest->Left = 416;
	SynTest->Top = 8;
	SynTest->Width = 321;
	SynTest->Height = 497;
	SynTest->Font->Charset = DEFAULT_CHARSET;
	SynTest->Font->Color = clWindowText;
	SynTest->Font->Height-13;
	SynTest->Font->Name = "Courier New";
	//SynTest->Font->Style;
	SynTest->Font->Quality = TFontQuality::fqClearTypeNatural;
	SynTest->TabOrder = 0;
	SynTest->UseCodeFolding = False;
	/* doesn't work in 110 any more
	SynTest->Gutter->Font->Charset = DEFAULT_CHARSET;
	SynTest->Gutter->Font->Color = clWindowText;
	SynTest->Gutter->Font->Height-11;
	SynTest->Gutter->Font->Name = "Terminal";
	//SynTest->Gutter->Font->Style;
	SynTest->Gutter->Visible = False;
	SynTest->Gutter->Width = 0;
	*/
	SynTest->Lines->Add("This is a Demo to show you how the ");
	SynTest->Lines->Add("Code Completion component works ");
	SynTest->Lines->Add("when the default kind is ctParams.");
	SynTest->Lines->Add("");
	SynTest->Lines->Add("Everything really depends on the");
	SynTest->Lines->Add("code you put in the execute event.");
	SynTest->Lines->Add("This determines what the parameters");
	SynTest->Lines->Add("are and what index should be");
	SynTest->Lines->Add("highlighted.");
	SynTest->Lines->Add("");
	SynTest->Lines->Add("See the source file execute event");
	SynTest->Lines->Add("for more information.");
	RemovedKeystroke(SynTest, L"ecContextHelp", 112);
	RemovedKeystroke(SynTest, L"ecContextHelp", 16496);
	SynEdit1 = new TSynEdit(this);
	SynEdit1->Parent = this;
	SynEdit1->Left = 6;
	SynEdit1->Top = 96;
	SynEdit1->Width = 401;
	SynEdit1->Height = 401;
	SynEdit1->Font->Charset = DEFAULT_CHARSET;
	SynEdit1->Font->Color = clWindowText;
	SynEdit1->Font->Height-13;
	SynEdit1->Font->Name = "Courier New";
	//SynEdit1->Font->Style;
	SynEdit1->Font->Quality = TFontQuality::fqClearTypeNatural;
	SynEdit1->TabOrder = 1;
	SynEdit1->UseCodeFolding = False;
	/* doesn't work in 110 any more
	SynEdit1->Gutter->Font->Charset = DEFAULT_CHARSET;
	SynEdit1->Gutter->Font->Color = clWindowText;
	SynEdit1->Gutter->Font->Height-11;
	SynEdit1->Gutter->Font->Name = "Terminal";
    */
	//SynEdit1->Gutter->Font->Style;
	SynEdit1->Lines->Add("Use Shift+Ctrl+Space to activate Parameter");
	SynEdit1->Lines->Add("completion, or type the function name");
	SynEdit1->Lines->Add("and the '(' (open paren) to start it with");
	SynEdit1->Lines->Add("the timer.");
	SynEdit1->Lines->Add("");
	SynEdit1->Lines->Add("The valid functions for this example are");
	SynEdit1->Lines->Add("");
	SynEdit1->Lines->Add("TestFunction");
	SynEdit1->Lines->Add("Min");
	SynEdit1->Lines->Add("Max");
	SynEdit1->Lines->Add("");
	SynEdit1->Lines->Add("Below is an example using paren Counting:");
	SynEdit1->Lines->Add("Max(a + b(1 + 2), (3 + 4) * c)");
	SynEdit1->Lines->Add("");
	SynEdit1->Lines->Add("Here is an example of embeded functions");
	SynEdit1->Lines->Add("");
	SynEdit1->Lines->Add("TestFunction(Min(a, b), SomeVar, Another)");
	RemovedKeystroke(SynEdit1, L"ecContextHelp", 112);
	RemovedKeystroke(SynEdit1, L"ecContextHelp", 16496);
	scpParams = new TSynCompletionProposal(this);
	scpParams->DefaultType = ctParams;
	scpParams->Options = TSynCompletionOptions() << scoLimitToMatchedText << scoUsePrettyText << scoUseBuiltInTimer;
//	scpParams->ClBackground = clInfoBk;
	scpParams->Width = 262;
	scpParams->EndOfTokenChr = "()[]. ";
	scpParams->TriggerChars = "(";
	scpParams->Font->Charset = DEFAULT_CHARSET;
	scpParams->Font->Color = clWindowText;
	scpParams->Font->Height-11;
	scpParams->Font->Name = "MS Sans Serif";
	//scpParams->Font->Style;
	scpParams->TitleFont->Charset = DEFAULT_CHARSET;
	scpParams->TitleFont->Color = clBtnText;
	scpParams->TitleFont->Height-11;
	scpParams->TitleFont->Name = "MS Sans Serif";
	scpParams->TitleFont->Style = TFontStyles() << fsBold;
	//scpParams->Columns;
	scpParams->OnExecute = scpParamsExecute;
	scpParams->ShortCut = 24608;
	scpParams->Editor = SynEdit1;
	scpParams->TimerInterval = 1200;
//	scpParams->Left = 8;

	LookupList = new TStringList();
	LookupList->Add(L"TESTFUNCTION");
	LookupList->Add(L"MAX");
	LookupList->Add(L"MIN");
	scpParams->EndOfTokenChr = L"";
}

void __fastcall TForm1::FormDestroy(TObject* Sender)
{
	delete LookupList;
	TComponent *Temp;
	for (int I = ComponentCount - 1; I >= 0; I--)
	{
		Temp = Components[I];
		if (dynamic_cast<TCustomSynEdit*>(Temp) != NULL) {
			RemoveComponent(Temp);
		}
	}
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
