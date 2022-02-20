#ifndef SynEditDataObjectH
#define SynEditDataObjectH

#include <System.hpp>
#include "d2c_system.h"

#include <Winapi.Windows.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Winapi.ActiveX.hpp>
#include <System.Generics.Collections.hpp>

namespace Syneditdataobject
{


/*
  The contents of this file are subject to the Mozilla Public License
  Version 1.1 (the "License"); you may not use this file except in compliance
  with the License. You may obtain a copy of the License at
  http://www.mozilla.org/MPL/

  Software distributed under the License is distributed on an "AS IS" basis,
  WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
  the specific language governing rights and limitations under the License.

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

  This unit implements the IDataObject interface for Clipboard and Drag & Drop
  operations.
  Code based on Grahame Marsh's articles on OLE Drag & Drop
  published in UNDO (www.undo.com)
*/

typedef System::Word TClipFormat;

class TSynEnumFormatEtc : public System::TCppInterfacedObject<IEnumFORMATETC>
{
	#include "SynEditDataObject_friends.inc"
public:
	typedef TInterfacedObject inherited;	
private:
	System::TArray<TClipFormat> FList;
	int FIndex;
protected:
	Winapi::Activex::TFormatEtc __fastcall GetFormatEtc(TClipFormat ClipFormat);
		/*IEnumFORMATETC*/
	HRESULT __stdcall Next(unsigned long celt, tagFORMATETC* elt, unsigned long* pceltFetched);
	HRESULT __stdcall Skip(unsigned long celt);
	HRESULT __stdcall Reset();
	HRESULT __stdcall Clone(IEnumFORMATETC** Enum);
public:
	__fastcall TSynEnumFormatEtc(System::TArray<TClipFormat> FormatList, int Index = 0);
	__fastcall TSynEnumFormatEtc();
};

class TSynEditDataObject : public System::TCppInterfacedObject<IDataObject>
{
	#include "SynEditDataObject_friends.inc"
public:
	typedef TInterfacedObject inherited;	
private:
	String FText;
	TList__1<TClipFormat>* FFormatEtc;
	System::Classes::TMemoryStream* MemoryStream;
	System::Classes::TMemoryStream* HtmlStream;
	void __fastcall StreamHTML(TObject* Editor, System::Classes::TStream* Stream);
protected:
	HRESULT __stdcall GetData(tagFORMATETC* formatetcIn, tagSTGMEDIUM* medium);
	HRESULT __stdcall GetDataHere(tagFORMATETC* formatetcIn, tagSTGMEDIUM* medium);
	HRESULT __stdcall QueryGetData(tagFORMATETC* FORMATETC);
	HRESULT __stdcall GetCanonicalFormatEtc(tagFORMATETC* FORMATETC, tagFORMATETC* formatetcOut);
	HRESULT __stdcall SetData(tagFORMATETC* FORMATETC, tagSTGMEDIUM* medium, BOOL fRelease);
	HRESULT __stdcall EnumFormatEtc(unsigned long dwDirection, IEnumFORMATETC** EnumFormatEtc);
	HRESULT __stdcall DAdvise(tagFORMATETC* FORMATETC, unsigned long advf, IAdviseSink* const advSink, unsigned long* dwConnection);
	HRESULT __stdcall DUnadvise(unsigned long dwConnection);
	HRESULT __stdcall EnumDAdvise(IEnumSTATDATA** enumAdvise);
public:
	__fastcall TSynEditDataObject(TObject* ASynEdit);
	virtual __fastcall ~TSynEditDataObject();
	__fastcall TSynEditDataObject();
};
HGLOBAL __fastcall MakeGlobal(int Value);
HGLOBAL __fastcall MakeGlobal(const String s);
HGLOBAL __fastcall MakeGlobal(void** P, int Size);
bool __fastcall HasFormat(IDataObject* dataObject, TClipFormat Format);
extern UINT SynEditClipboardFormat;
extern UINT HTMLClipboardFormat;

void SynEditDataObject_initialization();
void SynEditDataObject_finalization();


}  // namespace SynEditDataObject

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Syneditdataobject;
#endif


#endif // SynEditDataObjectH

