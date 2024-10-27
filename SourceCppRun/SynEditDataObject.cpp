
#include <vcl.h>
#pragma hdrstop

#include "SynEditDataObject.h"
#include "SynEdit.h"
#include "d2c_convert.h"

using namespace std;
using namespace d2c_system;
using namespace Synedit;
using namespace System;
using namespace Winapi::Activex;

namespace Syneditdataobject
{

__fastcall TSynEnumFormatEtc::TSynEnumFormatEtc() {}
__fastcall TSynEditDataObject::TSynEditDataObject() {}


UINT SynEditClipboardFormat = 0;

HGLOBAL __fastcall MakeGlobal(const String s)
{
	HGLOBAL result = 0;
	PChar p = nullptr;
	int Size = 0;
	Size = (int) (ByteLength(s) + sizeof(Char));
	result = GlobalAlloc((UINT) GHND, (size_t) Size);
	if(result == 0)
		OutOfMemoryError();
	p = ((WideChar*) GlobalLock(result));
	try
	{
		Move(ustr2address(s), p, Size);
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

HGLOBAL __fastcall MakeGlobal(void** p, int Size)
{
	HGLOBAL result = 0;
	void* d = nullptr;
	result = GlobalAlloc((UINT) GHND, (size_t) Size);
	if(result == 0)
		OutOfMemoryError();
	d = GlobalLock(result);
	try
	{
		Move(&(*p), d, Size);
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
	unsigned long Returned = 0;
	result = false;
	if(DataObject->EnumFormatEtc(DATADIR_GET, &FormatEnumerator) == S_OK)
	{
		FormatEnumerator->Reset();
		while(FormatEnumerator->Next(1, &FormatEtc, &Returned) == S_OK)
			if(FormatEtc.cfFormat == Format)
				return true;
	}
	return result;
}

__fastcall TSynEditDataObject::TSynEditDataObject(TObject* ASynEdit)
 : FText(((TCustomSynEdit*) ASynEdit)->SelText),
			FFormatEtc(nullptr),
			MemoryStream(nullptr)
{
	//# inherited::Create();
	MemoryStream = new TMemoryStream();
	FFormatEtc = new TList__1<TClipFormat>();
	FFormatEtc->Add(CF_UNICODETEXT);
	FFormatEtc->Add(SynEditClipboardFormat); // InternalFormat
//	MemoryStream->Write(&((TCustomSynEdit*) ASynEdit)->ActiveSelectionMode, sizeof(((TCustomSynEdit*) ASynEdit)->ActiveSelectionMode));
	TCustomSynEdit* pEdit = dynamic_cast<TCustomSynEdit*>(ASynEdit);
	TSynSelectionMode PasteMode = pEdit->ActiveSelectionMode;
	MemoryStream->Write(&PasteMode, (NativeInt)sizeof(PasteMode));
}

__fastcall TSynEditDataObject::~TSynEditDataObject()
{
	delete FFormatEtc;
	delete MemoryStream;
	//# inherited::Destroy();
}


HRESULT __stdcall TSynEditDataObject::GetData(tagFORMATETC* formatetcIn, tagSTGMEDIUM* medium)
{
	HRESULT result = 0;
	try
	{
		result = DV_E_FORMATETC;
		ZeroMemory(medium, (NativeUInt) sizeof(TStgMedium));
		if((formatetcIn->tymed & TYMED_HGLOBAL) == TYMED_HGLOBAL)
		{
			medium->tymed = TYMED_HGLOBAL;
			if(formatetcIn->cfFormat == CF_UNICODETEXT)
				medium->hGlobal = MakeGlobal(FText);
			else
			{
				if(formatetcIn->cfFormat == SynEditClipboardFormat)
					medium->hGlobal = MakeGlobal((void**) MemoryStream->Memory, (int) MemoryStream->Position);
				else
					return result;
			}
			result = S_OK;
		}
	}
	catch(...)
	{
		result = E_UNEXPECTED;
	}
	return result;
}

HRESULT __stdcall TSynEditDataObject::GetDataHere(tagFORMATETC* formatetcIn, tagSTGMEDIUM* medium)
{
	HRESULT result = 0;
	result = E_NOTIMPL;
	return result;
}

HRESULT __stdcall TSynEditDataObject::QueryGetData(tagFORMATETC* FormatEtc)
{
	HRESULT result = 0;
	TClipFormat ClipFormat = 0;
	for(int iFor0 = 0; iFor0 < FFormatEtc->Count; iFor0++)
	{
		TClipFormat ClipFormat = FFormatEtc->Items[iFor0];
		if((FormatEtc->cfFormat == ClipFormat) && ((FormatEtc->tymed & TYMED_HGLOBAL) == TYMED_HGLOBAL))
			return S_OK;
	}
	return DV_E_FORMATETC;
}

HRESULT __stdcall TSynEditDataObject::GetCanonicalFormatEtc(tagFORMATETC* FormatEtc, tagFORMATETC* formatetcOut)
{
	HRESULT result = 0;
	formatetcOut->ptd = nullptr;
	result = DATA_S_SAMEFORMATETC;
	return result;
}

HRESULT __stdcall TSynEditDataObject::SetData(tagFORMATETC* FormatEtc, tagSTGMEDIUM* medium, BOOL fRelease)
{
	HRESULT result = 0;
	result = E_NOTIMPL;
	return result;
}

HRESULT __stdcall TSynEditDataObject::EnumFormatEtc(unsigned long dwDirection, IEnumFORMATETC** EnumFormatEtc)
{
	//*EnumFormatEtc = nullptr; //# clear out parameter
	HRESULT result = 0;
	try
	{
		if(dwDirection == DATADIR_GET)
		{
			*EnumFormatEtc = new TSynEnumFormatEtc(FFormatEtc->ToArray());
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

HRESULT __stdcall TSynEditDataObject::DAdvise(tagFORMATETC* FormatEtc, unsigned long advf, IAdviseSink* const advSink, unsigned long* dwConnection)
{
	//dwConnection = 0; //# clear out parameter
	HRESULT result = 0;
	result = OLE_E_ADVISENOTSUPPORTED;
	return result;
}

HRESULT __stdcall TSynEditDataObject::DUnadvise(unsigned long dwConnection)
{
	HRESULT result = 0;
	result = OLE_E_ADVISENOTSUPPORTED;
	return result;
}

HRESULT __stdcall TSynEditDataObject::EnumDAdvise(IEnumSTATDATA** enumAdvise)
{
	//*enumAdvise = nullptr; //# clear out parameter
	HRESULT result = 0;
	result = OLE_E_ADVISENOTSUPPORTED;
	return result;
}


//=== BASE ENUM FORMATETC CLASS ================================================

__fastcall TSynEnumFormatEtc::TSynEnumFormatEtc(TArray<TClipFormat> FormatList, int Index/*# = 0*/)
 : FList(FormatList),
			FIndex(Index), m_refCount(1)
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

HRESULT __stdcall TSynEnumFormatEtc::Next(unsigned long celt, tagFORMATETC* elt, unsigned long* pceltFetched)
{
	//elt = nullptr; //# clear out parameter
	HRESULT result = 0;
	int i = 0;
	PFormatEtc FormatEtc = nullptr;
	i = 0;
	FormatEtc = ((PFormatEtc) elt);
	while((i < celt) && (FIndex < FList.Length))
	{
		(*FormatEtc) = GetFormatEtc(FList[FIndex]);
		++FormatEtc;
		++FIndex;
		++i;
	}
	if(pceltFetched != nullptr)
		(*pceltFetched) = i;
	if(i == celt)
		result = S_OK;
	else
		result = S_FALSE;
	return result;
}

HRESULT __stdcall TSynEnumFormatEtc::Skip(unsigned long celt)
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

HRESULT __stdcall TSynEnumFormatEtc::Clone(IEnumFORMATETC** Enum)
{
	//*Enum = nullptr; //# clear out parameter
	HRESULT result = 0;
	result = S_OK;
	*Enum = new TSynEnumFormatEtc(FList, FIndex);
	return result;
}
HRESULT __stdcall TSynEnumFormatEtc::QueryInterface(REFIID riid, void **ppvObject)
{
    if (riid == IID_IUnknown || riid == IID_IEnumFORMATETC)
    {
        *ppvObject = static_cast<IEnumFORMATETC *>(this);
        AddRef();
        return S_OK;
    }
    *ppvObject = nullptr;
    return E_NOINTERFACE;
}

ULONG __stdcall TSynEnumFormatEtc::AddRef()
{
    return InterlockedIncrement(&m_refCount);
}

ULONG __stdcall TSynEnumFormatEtc::Release()
{
    ULONG refCount = InterlockedDecrement(&m_refCount);
    if (refCount == 0)
    {
        delete this;
    }
    return refCount;
}
void OleInit(void)
{
    OleInitialize(nullptr);
}

#pragma startup OleInit
#pragma exit OleUninitialize


void InitializeSynEditClipboardFormat()
{
    SynEditClipboardFormat = RegisterClipboardFormatA("Internal SynEdit clipboard format");
}

#pragma startup InitializeSynEditClipboardFormat

static bool SynEditDataObject_Initialized = false;

void SynEditDataObject_initialization()
{
	if(SynEditDataObject_Initialized)
		return;
	
	SynEditDataObject_Initialized = true;
	
	OleInitialize(nullptr);
	SynEditClipboardFormat = RegisterClipboardFormat(const_cast<LPCWSTR>(L"Internal SynEdit clipboard format"));
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



