#include <vcl.h>
#pragma hdrstop

#include "SynEditHighlighterOptions.h"

using namespace std;
using namespace d2c_system;
using namespace System;
using namespace System::Classes;

namespace Synedithighlighteroptions
{

__fastcall TSynEditHighlighterOptions::TSynEditHighlighterOptions() {}



void __fastcall TSynEditHighlighterOptions::Assign(TPersistent* Source)
{
	if(Source->InheritsFrom(__classid(TSynEditHighlighterOptions)))
	{
		/*# with TSynEditHighlighterOptions(Source) do */
		{
			auto with0 = ((TSynEditHighlighterOptions*) Source);
			FAutoDetectEnabled = with0->AutoDetectEnabled;
			FAutoDetectMatchExpression = with0->AutoDetectMatchExpression;
			FAutoDetectLineLimit = with0->AutoDetectLineLimit;
			FDefaultExtension = with0->DefaultExtension;
			FLineCommentarStart = with0->LineCommentarStart;
			FLineCommentarEnd = with0->LineCommentarEnd;
			FTitle = with0->Title;
			fVisible = with0->Visible;
		}
	}
}

void __fastcall TSynEditHighlighterOptions::AssignTo(TPersistent* Dest)
{
	if(Dest->InheritsFrom(__classid(TSynEditHighlighterOptions)))
	{
		/*# with TSynEditHighlighterOptions(Dest) do */
		{
			auto with0 = ((TSynEditHighlighterOptions*) Dest);
			with0->AutoDetectEnabled = FAutoDetectEnabled;
			with0->AutoDetectMatchExpression = FAutoDetectMatchExpression;
			with0->AutoDetectLineLimit = FAutoDetectLineLimit;
			with0->DefaultExtension = FDefaultExtension;
			with0->LineCommentarStart = FLineCommentarStart;
			with0->LineCommentarEnd = FLineCommentarEnd;
			with0->Title = FTitle;
			with0->Visible = fVisible;
		}
	}
}


}  // namespace SynEditHighlighterOptions

