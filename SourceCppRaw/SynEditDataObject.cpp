
#include <vcl.h>
#pragma hdrstop

#include "SynEditDataObject.h"
#include "SynEdit.h"
#include "SynExportHTML.h"
#include "d2c_convert.h"

using namespace std;
using namespace d2c_system;
using namespace Synedit;
using namespace Synexporthtml;
using namespace System;

namespace Syneditdataobject
{

__fastcall TSynEnumFormatEtc::TSynEnumFormatEtc() {}
__fastcall TSynEditDataObject::TSynEditDataObject() {}


UINT SynEditClipboardFormat = 0;
UINT HTMLClipboardFormat = 0;

HGLOBAL __fastcall MakeGlobal(const String S)
{
	HGLOBAL result = 0;
	PChar P = nullptr;
	int Size = 0;
	Size = ByteLength(S) + sizeof(Char);
	result = GlobalAlloc((UINT) GHND, (SIZE_T) Size);
	if(result == 0)
		OutOfMemoryError();
	P = ((WideChar*) GlobalLock(result));
	try
	{
		Move(ustr2address(S), P, Size);
	}
	__finally
	{
		GlobalUnlock(result);
	}
	return result;
}

HGLOBAL __fastcall MakeGlobal(int Value)
{
	HGLOBAL result = 0;
	result = MakeGlobal((void**)&Value, (int) sizeof(int));
	return result;
}

HGLOBAL __fastcall MakeGlobal(void** P, int Size)
{
	HGLOBAL result = 0;
	void* D = nullptr;
	result = GlobalAlloc((UINT) GHND, (SIZE_T) Size);
	if(result == 0)
		OutOfMemoryError();
	D = GlobalLock(result);
	try
	{
		Move(&(*P), D, Size);
	}
	__finally
	{
		GlobalUnlock(result);
	}
	return result;
}

bool __fastcall HasFormat(IDataObject* DataObject, TClipFormat Format)
{
	bool result = false;
	IEnumFORMATETC* FormatEnumerator = nullptr;
	TFormatEtc FormatEtc = {};
	int Returned = 0;
	result = false;
	if(DataObject->EnumFormatEtc(DATADIR_GET, FormatEnumerator) == S_OK)
	{
		FormatEnumerator->Reset();
		while(FormatEnumerator->Next(1, (void**)&FormatEtc, &Returned) == S_OK)
			if(FormatEtc.cfFormat == Format)
				return true;
	}
	return result;
}

__fastcall TSynEditDataObject::TSynEditDataObject(TObject* ASynEdit)
 : fText(((TCustomSynEdit*) ASynEdit)->SelText),
			FFormatEtc(nullptr),
			MemoryStream(nullptr),
			HtmlStream(nullptr)
{
	//# inherited::Create();
	MemoryStream = new TMemoryStream();
	HtmlStream = new TMemoryStream();
	FFormatEtc = new TList__1<TClipFormat>();
	FFormatEtc->Add((T) CF_UNICODETEXT);
	FFormatEtc->Add((T) SynEditClipboardFormat); // InternalFormat
	MemoryStream->Write(&((TCustomSynEdit*) ASynEdit)->ActiveSelectionMode, sizeof(((TCustomSynEdit*) ASynEdit)->ActiveSelectionMode));
	if(!(((TCustomSynEdit*) ASynEdit)->Options.Contains(eoCopyPlainText)) && ASSIGNED(((TCustomSynEdit*) ASynEdit)->Highlighter))
	{
		FFormatEtc->Add((T) HTMLClipboardFormat); // HTMLFormat
		StreamHTML(ASynEdit, HtmlStream);
	}
}

__fastcall TSynEditDataObject::~TSynEditDataObject()
{
	delete FFormatEtc;
	delete MemoryStream;
	delete HtmlStream;
	//# inherited::Destroy();
}

HRESULT __stdcall TSynEditDataObject::GetData(const TFormatEtc& formatetcIn, TStgMedium& medium)
{
	medium = {}; //# clear out parameter
	HRESULT result = 0;
	ZeroMemory(&medium, sizeof(TStgMedium));
	result = QueryGetData(formatetcIn);
	if(result == S_OK)
		try
		{
			medium.tymed = TYMED_HGLOBAL;
			if(formatetcIn.cfFormat == CF_UNICODETEXT)
				medium.hGlobal = MakeGlobal(fText);
			else
			{
				if(formatetcIn.cfFormat == SynEditClipboardFormat)
					medium.hGlobal = MakeGlobal((void**) MemoryStream->Memory, (int) MemoryStream->Position);
				else
				{
					if(formatetcIn.cfFormat == HTMLClipboardFormat)
						medium.hGlobal = MakeGlobal((void**) HtmlStream->Memory, (int) HtmlStream->Position);
				}
			}
		}
		catch(...)
		{
			result = E_UNEXPECTED;
		}
	return result;
}

HRESULT __stdcall TSynEditDataObject::GetDataHere(const TFormatEtc& formatetc, TStgMedium& medium)
{
	medium = {}; //# clear out parameter
	HRESULT result = 0;
	result = E_NOTIMPL;
	return result;
}

void __fastcall TSynEditDataObject::StreamHTML(TObject* Editor, TStream* Stream)
{
	TSynExporterHTML* HTMLExport = nullptr;
	TSynEdit* Ed = nullptr;
	Ed = (TSynEdit*) Editor;
	HTMLExport = new TSynExporterHTML(nullptr);
	try
	{
		HTMLExport->CreateHTMLFragment = true;
		HTMLExport->UseBackground = true;
		HTMLExport->Highlighter = Ed->Highlighter;
		HTMLExport->ExportRange(Ed->Lines, Ed->BlockBegin, Ed->BlockEnd);
		HTMLExport->SaveToStream(Stream);
	}
	__finally
	{
		delete HTMLExport;
	}
}

HRESULT __stdcall TSynEditDataObject::QueryGetData(const TFormatEtc& formatetc)
{
	HRESULT result = 0;
	if(((formatetc.tymed & TYMED_HGLOBAL) == TYMED_HGLOBAL) && FFormatEtc->Contains(formatetc.cfFormat))
		result = S_OK;
	else
		result = DV_E_FORMATETC;
	return result;
}

HRESULT __stdcall TSynEditDataObject::GetCanonicalFormatEtc(const TFormatEtc& formatetc, TFormatEtc& formatetcOut)
{
	formatetcOut = {}; //# clear out parameter
	HRESULT result = 0;
	formatetcOut.ptd = nullptr;
	result = DATA_S_SAMEFORMATETC;
	return result;
}

HRESULT __stdcall TSynEditDataObject::SetData(const TFormatEtc& formatetc, TStgMedium& medium, BOOL fRelease)
{
	HRESULT result = 0;
	result = E_NOTIMPL;
	return result;
}

HRESULT __stdcall TSynEditDataObject::EnumFormatEtc(int dwDirection, IEnumFORMATETC*& enumFormatEtc)
{
	enumFormatEtc = nullptr; //# clear out parameter
	HRESULT result = 0;
	try
	{
		if(dwDirection == DATADIR_GET)
		{
			enumFormatEtc = new TSynEnumFormatEtc(FFormatEtc->ToArray());
			result = S_OK;
		}
		else
		result = E_NOTIMPL;
	}
	catch(...)
	{
		result = E_UNEXPECTED;
	}
	return result;
}

HRESULT __stdcall TSynEditDataObject::DAdvise(const TFormatEtc& formatetc, int advf, IAdviseSink* const advSink, int& dwConnection)
{
	dwConnection = 0; //# clear out parameter
	HRESULT result = 0;
	result = OLE_E_ADVISENOTSUPPORTED;
	return result;
}

HRESULT __stdcall TSynEditDataObject::DUnadvise(int dwConnection)
{
	HRESULT result = 0;
	result = OLE_E_ADVISENOTSUPPORTED;
	return result;
}

HRESULT __stdcall TSynEditDataObject::EnumDAdvise(IEnumSTATDATA*& enumAdvise)
{
	enumAdvise = nullptr; //# clear out parameter
	HRESULT result = 0;
	result = OLE_E_ADVISENOTSUPPORTED;
	return result;
}


//=== BASE ENUM FORMATETC CLASS ================================================

__fastcall TSynEnumFormatEtc::TSynEnumFormatEtc(System::TArray<TClipFormat>& FormatList, int Index/*# = 0*/)
 : FList(FormatList),
			FIndex(Index)
{
	//# inherited::Create();
}

TFormatEtc __fastcall TSynEnumFormatEtc::GetFormatEtc(TClipFormat ClipFormat)
{
	TFormatEtc result = {};
	/*# with result do */
	{
		auto& with0 = result;
		with0.cfFormat = ClipFormat;
		with0.dwAspect = DVASPECT_CONTENT;
		with0.ptd = nullptr;
		with0.tymed = TYMED_HGLOBAL;
		with0.lindex = -1;
	}
	return result;
}

HRESULT __stdcall TSynEnumFormatEtc::Next(int celt, void** elt, PLongInt pceltFetched)
{
	elt = nullptr; //# clear out parameter
	HRESULT result = 0;
	int I = 0;
	PFormatEtc FormatEtc = nullptr;
	I = 0;
	FormatEtc = ((PFormatEtc) elt);
	while((I < celt) && (FIndex < FList.Length))
	{
		(*FormatEtc) = GetFormatEtc(FList[FIndex]);
		++FormatEtc;
		++FIndex;
		++I;
	}
	if(pceltFetched != nullptr)
		(*pceltFetched) = I;
	if(I == celt)
		result = S_OK;
	else
		result = S_FALSE;
	return result;
}

HRESULT __stdcall TSynEnumFormatEtc::Skip(int celt)
{
	HRESULT result = 0;
	result = S_OK;
	if(celt <= FList.Length - FIndex)
		FIndex = FIndex + celt;
	else
	{
		FIndex = FList.Length;
		result = S_FALSE;
	}
	return result;
}

HRESULT __stdcall TSynEnumFormatEtc::Reset()
{
	HRESULT result = 0;
	FIndex = 0;
	result = S_OK;
	return result;
}

HRESULT __stdcall TSynEnumFormatEtc::Clone(IEnumFORMATETC*& Enum)
{
	Enum = nullptr; //# clear out parameter
	HRESULT result = 0;
	result = S_OK;
	Enum = new TSynEnumFormatEtc(FList, FIndex);
	return result;
}
const WideChar CF_HTML[] = L"HTML Format";
static bool SynEditDataObject_Initialized = false;

void SynEditDataObject_initialization()
{
	if(SynEditDataObject_Initialized)
		return;
	
	SynEditDataObject_Initialized = true;
	
	OleInitialize(nullptr);
	SynEditClipboardFormat = RegisterClipboardFormat(const_cast<LPCWSTR>(L"Internal SynEdit clipboard format"));
	HTMLClipboardFormat = RegisterClipboardFormat(const_cast<LPCWSTR>(CF_HTML));
}
static bool SynEditDataObject_Finalized = false;

void SynEditDataObject_finalization()
{
	if(SynEditDataObject_Finalized)
		return;
	
	SynEditDataObject_Finalized = true;
	
	OleFlushClipboard();
	OleUninitialize();
}
// using unit initialization order file, so unit singleton has not been created


}  // namespace SynEditDataObject

