#include <vcl.h>
#pragma hdrstop

#include "SynEditHighlighterOptions.h"

using namespace std;
using namespace d2c_system;
using namespace System::Classes;

namespace Synedithighlighteroptions
{

__fastcall TSynEditHighlighterOptions::TSynEditHighlighterOptions() {}



/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/
Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

Datetime format is dd.MM.yyyy hh:mm:ss.

The Original Code is: SynEditHighlighterOptions.pas, released 12.09.2012.

All Rights Reserved.

Contributors to the SynEdit and mwEdit projects are listed in the
Contributors.txt file.

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Last Changes:
  21.09.2012 08:37:10 - Moved from String to WideString
  25.10.2012 11:16:19 - Added DefaultExtension property

Known Issues:
-------------------------------------------------------------------------------*/

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


}  // namespace Synedithighlighteroptions

