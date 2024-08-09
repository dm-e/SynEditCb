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
#ifndef SynEditHighlighterOptionsH
#define SynEditHighlighterOptionsH

#include <System.hpp>
#include "d2c_system.h"

#include <System.Classes.hpp>

namespace Synedithighlighteroptions
{

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

class TSynEditHighlighterOptions : public System::Classes::TPersistent
{
private:
	bool FAutoDetectEnabled;
	unsigned int FAutoDetectLineLimit;
	WideString FAutoDetectMatchExpression;
	WideString FDefaultExtension;
	WideString FLineCommentarEnd;
	WideString FLineCommentarStart;
	WideString FTitle;
	bool fVisible;
public:
	typedef System::Classes::TPersistent inherited;
	virtual void __fastcall Assign(TPersistent* Source);
	virtual void __fastcall AssignTo(TPersistent* Dest);
__published:
	__property bool AutoDetectEnabled = { read = FAutoDetectEnabled, write = FAutoDetectEnabled };
	__property unsigned int AutoDetectLineLimit = { read = FAutoDetectLineLimit, write = FAutoDetectLineLimit };
	__property WideString AutoDetectMatchExpression = { read = FAutoDetectMatchExpression, write = FAutoDetectMatchExpression };
	__property WideString DefaultExtension = { read = FDefaultExtension, write = FDefaultExtension };
	__property WideString LineCommentarEnd = { read = FLineCommentarEnd, write = FLineCommentarEnd };
	__property WideString LineCommentarStart = { read = FLineCommentarStart, write = FLineCommentarStart };
	__property WideString Title = { read = FTitle, write = FTitle };
	__property bool Visible = { read = fVisible, write = fVisible };
public:
	__fastcall TSynEditHighlighterOptions();
};


}  // namespace SynEditHighlighterOptions

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synedithighlighteroptions;
#endif

#endif // SynEditHighlighterOptionsH

