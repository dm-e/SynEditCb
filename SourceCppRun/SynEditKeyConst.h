#ifndef SynEditKeyConstH
#define SynEditKeyConstH

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>

namespace Syneditkeyconst
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynEditKeyCmds.pas, released 2000-04-07.
The Original Code is based on the mwKeyCmds.pas file from the
mwEdit component suite by Martin Waldenburg and other developers, the Initial
Author of this file is Brad Stowers.
All Rights Reserved.

Contributors to the SynEdit and mwEdit projects are listed in the
Contributors.txt file.

Alternatively, the contents of this file may be used under the terms of the
GNU General Public License Version 2 or later (the "GPL"), in which case
the provisions of the GPL are applicable instead of those above.
If you wish to allow use of your version of this file only under the terms
of the GPL and not to allow others to use your version of this file
under the MPL, indicate your decision by deleting the provisions above and
replace them with the notice and other provisions required by the GPL.
If you do not delete the provisions above, a recipient may use your version
of this file under either the MPL or the GPL.

$Id: SynEditKeyConst.pas,v 1.4.2.1 2004/08/31 12:55:17 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/

/* This unit provides a translation of DELPHI and CLX key constants to
  more readable SynEdit constants */
const int SYNEDIT_RETURN = VK_RETURN;
const int SYNEDIT_ESCAPE = VK_ESCAPE;
const int SYNEDIT_SPACE = VK_SPACE;
const int SYNEDIT_PRIOR = VK_PRIOR;
const int SYNEDIT_NEXT = VK_NEXT;
const int SYNEDIT_END = VK_END;
const int SYNEDIT_HOME = VK_HOME;
const int SYNEDIT_UP = VK_UP;
const int SYNEDIT_DOWN = VK_DOWN;
const int SYNEDIT_BACK = VK_BACK;
const int SYNEDIT_LEFT = VK_LEFT;
const int SYNEDIT_RIGHT = VK_RIGHT;
const int SYNEDIT_MENU = VK_MENU;
const int SYNEDIT_CONTROL = VK_CONTROL;
const int SYNEDIT_SHIFT = VK_SHIFT;
const int SYNEDIT_F1 = VK_F1;
const int SYNEDIT_F2 = VK_F2;
const int SYNEDIT_F3 = VK_F3;
const int SYNEDIT_F4 = VK_F4;
const int SYNEDIT_F5 = VK_F5;
const int SYNEDIT_F6 = VK_F6;
const int SYNEDIT_F7 = VK_F7;
const int SYNEDIT_F8 = VK_F8;
const int SYNEDIT_F9 = VK_F9;
const int SYNEDIT_F10 = VK_F10;
const int SYNEDIT_F11 = VK_F11;
const int SYNEDIT_F12 = VK_F12;
const int SYNEDIT_F13 = VK_F13;
const int SYNEDIT_F14 = VK_F14;
const int SYNEDIT_F15 = VK_F15;
const int SYNEDIT_F16 = VK_F16;
const int SYNEDIT_F17 = VK_F17;
const int SYNEDIT_F18 = VK_F18;
const int SYNEDIT_F19 = VK_F19;
const int SYNEDIT_F20 = VK_F20;
const int SYNEDIT_F21 = VK_F21;
const int SYNEDIT_F22 = VK_F22;
const int SYNEDIT_F23 = VK_F23;
const int SYNEDIT_F24 = VK_F24;
const int SYNEDIT_PRINT = VK_PRINT;
const int SYNEDIT_INSERT = VK_INSERT;
const int SYNEDIT_DELETE = VK_DELETE;
const int SYNEDIT_NUMPAD0 = VK_NUMPAD0;
const int SYNEDIT_NUMPAD1 = VK_NUMPAD1;
const int SYNEDIT_NUMPAD2 = VK_NUMPAD2;
const int SYNEDIT_NUMPAD3 = VK_NUMPAD3;
const int SYNEDIT_NUMPAD4 = VK_NUMPAD4;
const int SYNEDIT_NUMPAD5 = VK_NUMPAD5;
const int SYNEDIT_NUMPAD6 = VK_NUMPAD6;
const int SYNEDIT_NUMPAD7 = VK_NUMPAD7;
const int SYNEDIT_NUMPAD8 = VK_NUMPAD8;
const int SYNEDIT_NUMPAD9 = VK_NUMPAD9;
const int SYNEDIT_MULTIPLY = VK_MULTIPLY;
const int SYNEDIT_ADD = VK_ADD;
const int SYNEDIT_SEPARATOR = VK_SEPARATOR;
const int SYNEDIT_SUBTRACT = VK_SUBTRACT;
const int SYNEDIT_DECIMAL = VK_DECIMAL;
const int SYNEDIT_DIVIDE = VK_DIVIDE;
const int SYNEDIT_NUMLOCK = VK_NUMLOCK;
const int SYNEDIT_SCROLL = VK_SCROLL;
const int SYNEDIT_TAB = VK_TAB;
const int SYNEDIT_CLEAR = VK_CLEAR;
const int SYNEDIT_PAUSE = VK_PAUSE;
const int SYNEDIT_CAPITAL = VK_CAPITAL;


}  // namespace SynEditKeyConst

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Syneditkeyconst;
#endif

#endif // SynEditKeyConstH

