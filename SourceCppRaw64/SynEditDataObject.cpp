
#include <vcl.h>
#pragma hdrstop

#include "SynEditDataObject.h"
#include "SynEdit.h"
#include "SynExportHTML.h"
#include "d2c_convert.h"
#include "d2c_sysinterface.h"

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
	Size = static_cast<int>(ByteLength(S) + sizeof(Char));
	result = GlobalAlloc(static_cast<UINT>(GHND), static_cast<SIZE_T>(Size));
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
	result = MakeGlobal(&Value, static_cast<int>(sizeof(int)));
	return result;
}

HGLOBAL __fastcall MakeGlobal(void* P, int Size)
{
	HGLOBAL result = 0;
	void* D = nullptr;
	result = GlobalAlloc(static_cast<UINT>(GHND), static_cast<SIZE_T>(Size));
	if(result == 0)
		OutOfMemoryError();
	D = GlobalLock(result);
	try
	{
		Move(P, D, Size);
	}
	__finally
	{
		GlobalUnlock(result);
	}
	return result;
}

bool __fastcall HasFormat(const _di_IDataObject& DataObject, TClipFormat Format)
{
	bool result = false;
	_di_IEnumFORMATETC FormatEnumerator;
	TFormatEtc FormatEtc = {};
	int Returned = 0;
	result = false;
	if(DataObject->EnumFormatEtc(DATADIR_GET, DiOut<IEnumFORMATETC>(FormatEnumerator)) == S_OK)
	{
		FormatEnumerator->Reset();
		while(FormatEnumerator->Next(1, &FormatEtc, &Returned) == S_OK)
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
	FFormatEtc->Add(static_cast<WORD>(CF_UNICODETEXT));
	FFormatEtc->Add(static_cast<WORD>(SynEditClipboardFormat)); // InternalFormat
	MemoryStream->Write(&((TCustomSynEdit*) ASynEdit)->ActiveSelectionMode, static_cast<TNativeCount>(sizeof(((TCustomSynEdit*) ASynEdit)->ActiveSelectionMode)));
	if(!(((TCustomSynEdit*) ASynEdit)->Options.Contains(eoCopyPlainText)) && ASSIGNED(((TCustomSynEdit*) ASynEdit)->Highlighter))
	{
		FFormatEtc->Add(static_cast<WORD>(HTMLClipboardFormat)); // HTMLFormat
		StreamHTML(ASynEdit, HtmlStream);
	}
	// AddRef(); //# Ensure COM contract: returned interface must have RefCount >= 1
}

__fastcall TSynEditDataObject::~TSynEditDataObject()
{
	delete FFormatEtc;
	delete MemoryStream;
	delete HtmlStream;
	//# inherited::Destroy();
}

HRESULT STDMETHODCALLTYPE TSynEditDataObject::GetData(TFormatEtc* formatetcIn, TStgMedium* medium)
{
	if (formatetcIn == nullptr)
		return E_POINTER;
	*medium = {}; //# clear out parameter
	HRESULT result = 0;
	ZeroMemory(medium, sizeof(TStgMedium));
	result = QueryGetData(formatetcIn);
	if(result == S_OK)
		try
		{
			medium->tymed = TYMED_HGLOBAL;
			if(formatetcIn->cfFormat == CF_UNICODETEXT)
				medium->hGlobal = MakeGlobal(fText);
			else
			{
				if(formatetcIn->cfFormat == SynEditClipboardFormat)
					medium->hGlobal = MakeGlobal(MemoryStream->Memory, static_cast<LONG>(MemoryStream->Position));
				else
				{
					if(formatetcIn->cfFormat == HTMLClipboardFormat)
						medium->hGlobal = MakeGlobal(HtmlStream->Memory, static_cast<LONG>(HtmlStream->Position));
				}
			}
		}
		catch(...)
		{
			result = E_UNEXPECTED;
		}
	return result;
}

HRESULT STDMETHODCALLTYPE TSynEditDataObject::GetDataHere(TFormatEtc* formatetc, TStgMedium* medium)
{
	if (formatetc == nullptr)
		return E_POINTER;
	*medium = {}; //# clear out parameter
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

HRESULT STDMETHODCALLTYPE TSynEditDataObject::QueryGetData(TFormatEtc* formatetc)
{
	if (formatetc == nullptr)
		return E_POINTER;
	HRESULT result = 0;
	if(((formatetc->tymed & TYMED_HGLOBAL) == TYMED_HGLOBAL) && FFormatEtc->Contains(formatetc->cfFormat))
		result = S_OK;
	else
		result = DV_E_FORMATETC;
	return result;
}

HRESULT STDMETHODCALLTYPE TSynEditDataObject::GetCanonicalFormatEtc(TFormatEtc* formatetc, TFormatEtc* formatetcOut)
{
	if (formatetc == nullptr)
		return E_POINTER;
	*formatetcOut = {}; //# clear out parameter
	HRESULT result = 0;
	formatetcOut->ptd = nullptr;
	result = DATA_S_SAMEFORMATETC;
	return result;
}

HRESULT STDMETHODCALLTYPE TSynEditDataObject::SetData(TFormatEtc* formatetc, TStgMedium* medium, BOOL fRelease)
{
	if (formatetc == nullptr)
		return E_POINTER;
	if(medium == nullptr)
		return E_POINTER;
	HRESULT result = 0;
	result = E_NOTIMPL;
	return result;
}

HRESULT STDMETHODCALLTYPE TSynEditDataObject::EnumFormatEtc(DWORD dwDirection, IEnumFORMATETC** enumFormatEtc)
{
	if(enumFormatEtc == nullptr)
		return E_POINTER;
	*enumFormatEtc = nullptr; //# clear out parameter
	HRESULT result = 0;
	try
	{
		if(dwDirection == DATADIR_GET)
		{
			*enumFormatEtc = new TSynEnumFormatEtc(FFormatEtc->ToArray());
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

HRESULT STDMETHODCALLTYPE TSynEditDataObject::DAdvise(TFormatEtc* formatetc, LONG advf, IAdviseSink* advSink, DWORD* dwConnection)
{
	if (formatetc == nullptr)
		return E_POINTER;
	*dwConnection = 0; //# clear out parameter
	HRESULT result = 0;
	result = OLE_E_ADVISENOTSUPPORTED;
	return result;
}

HRESULT STDMETHODCALLTYPE TSynEditDataObject::DUnadvise(DWORD dwConnection)
{
	HRESULT result = 0;
	result = OLE_E_ADVISENOTSUPPORTED;
	return result;
}

HRESULT STDMETHODCALLTYPE TSynEditDataObject::EnumDAdvise(IEnumSTATDATA** enumAdvise)
{
	if(enumAdvise == nullptr)
		return E_POINTER;
	*enumAdvise = nullptr; //# clear out parameter
	HRESULT result = 0;
	result = OLE_E_ADVISENOTSUPPORTED;
	return result;
}


//=== BASE ENUM FORMATETC CLASS ================================================

__fastcall TSynEnumFormatEtc::TSynEnumFormatEtc(const D2CArray<TClipFormat>& FormatList, int Index/*# = 0*/)
 : FList(FormatList),
			FIndex(Index)
{
	//# inherited::Create();
	// AddRef(); //# Ensure COM contract: returned interface must have RefCount >= 1
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

HRESULT STDMETHODCALLTYPE TSynEnumFormatEtc::Next(LONG celt, LPVOID* elt, LONG pceltFetched)
{
	if(elt == nullptr)
		return E_POINTER;
	*elt = nullptr; //# clear out parameter
	HRESULT result = 0;
	LONG I = 0;
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

HRESULT STDMETHODCALLTYPE TSynEnumFormatEtc::Skip(LONG celt)
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

HRESULT STDMETHODCALLTYPE TSynEnumFormatEtc::Reset()
{
	HRESULT result = 0;
	FIndex = 0;
	result = S_OK;
	return result;
}

HRESULT STDMETHODCALLTYPE TSynEnumFormatEtc::Clone(IEnumFORMATETC** Enum)
{
	if(Enum == nullptr)
		return E_POINTER;
	*Enum = nullptr; //# clear out parameter
	HRESULT result = 0;
	result = S_OK;
	*Enum = new TSynEnumFormatEtc(FList, FIndex);
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


}  // namespace Syneditdataobject

