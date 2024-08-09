#ifndef frmMainSDIH
#define frmMainSDIH

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include "frmMain.h"
#include <Vcl.Menus.hpp>
#include "uEditAppIntfs.h"
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ActnList.hpp>

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: frmMainSDI.pas, released 2000-09-08.

The Original Code is part of the EditAppDemos project, written by
Michael Hieke for the SynEdit component suite.
All Rights Reserved.

Contributors to the SynEdit project are listed in the Contributors.txt file.

Alternatively, the contents of this file may be used under the terms of the
GNU General Public License Version 2 or later (the "GPL"), in which case
the provisions of the GPL are applicable instead of those above.
If you wish to allow use of your version of this file only under the terms
of the GPL and not to allow others to use your version of this file
under the MPL, indicate your decision by deleting the provisions above and
replace them with the notice and other provisions required by the GPL.
If you do not delete the provisions above, a recipient may use your version
of this file under either the MPL or the GPL.

$Id: frmMainSDI.pas,v 1.2 2000/11/22 08:34:14 mghie Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/

class TSDIMainForm : public TMainForm
{
__published:
	void __fastcall FormCreate(TObject* Sender);
	void __fastcall FormCloseQuery(TObject* Sender, bool& CanClose);
private:
	IEditor* fEditorForm;
protected:
	virtual IEditor* __fastcall DoCreateEditor(String AFileName);
public:
	typedef TMainForm inherited;	
	__fastcall TSDIMainForm(TComponent* AOwner);
};
extern PACKAGE TSDIMainForm* SDIMainForm;
#endif // frmMainSDIH
