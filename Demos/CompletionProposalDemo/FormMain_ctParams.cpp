#include <vcl.h>
#pragma hdrstop

#include "FormMain_ctParams.h"
#include "SynEditTypes.hpp"

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
