#include <vcl.h>
#pragma hdrstop

#include "SynEditHighlighterOptions.h"

using namespace std;
using namespace d2c_system;
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
			with0->FAutoDetectEnabled = with0->AutoDetectEnabled;
			with0->FAutoDetectMatchExpression = with0->AutoDetectMatchExpression;
			with0->FAutoDetectLineLimit = with0->AutoDetectLineLimit;
			with0->FDefaultExtension = with0->DefaultExtension;
			with0->FLineCommentarStart = with0->LineCommentarStart;
			with0->FLineCommentarEnd = with0->LineCommentarEnd;
			with0->FTitle = with0->Title;
			with0->FVisible = with0->Visible;
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
			with0->AutoDetectEnabled = with0->FAutoDetectEnabled;
			with0->AutoDetectMatchExpression = with0->FAutoDetectMatchExpression;
			with0->AutoDetectLineLimit = with0->FAutoDetectLineLimit;
			with0->DefaultExtension = with0->FDefaultExtension;
			with0->LineCommentarStart = with0->FLineCommentarStart;
			with0->LineCommentarEnd = with0->FLineCommentarEnd;
			with0->Title = with0->FTitle;
			with0->Visible = with0->FVisible;
		}
	}
}


}  // namespace SynEditHighlighterOptions

