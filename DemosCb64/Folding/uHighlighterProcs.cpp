#include <vcl.h>
#pragma hdrstop

#include "uHighlighterProcs.h"
#include <System.SysUtils.hpp>

using namespace std;
using namespace d2c_system;



void __fastcall GetHighlighters(TComponent* AOwner, TStringList* AHighlighters, bool AppendToList)
{
	int i = 0;
	TSynCustomHighlighter* Highlighter = nullptr;
	if(ASSIGNED(AOwner) && ASSIGNED(AHighlighters))
	{
		int stop = 0;
		if(!AppendToList)
			AHighlighters->Clear();
		for(stop = 0, i = AOwner->ComponentCount - 1; i >= stop; i--)
		{
			if(!(ObjectIs(AOwner->Components[i], TSynCustomHighlighter*)))
				continue;
			Highlighter = (TSynCustomHighlighter*) AOwner->Components[i];
      // only one highlighter for each language
			if(AHighlighters->IndexOf(Highlighter->GetLanguageName()) == -1)
				AHighlighters->AddObject(Highlighter->GetLanguageName(), Highlighter);
		}
		AHighlighters->Sort();
	}
}

String __fastcall GetHighlightersFilter(TStringList* AHighlighters)
{
	String result;
	int i = 0;
	TSynCustomHighlighter* Highlighter = nullptr;
	result = L"";
	if(ASSIGNED(AHighlighters))
	{
		int stop = 0;
		for(stop = AHighlighters->Count - 1, i = 0; i <= stop; i++)
		{
			if(!(ObjectIs(AHighlighters->Objects[i], TSynCustomHighlighter*)))
				continue;
			Highlighter = ((TSynCustomHighlighter*) AHighlighters->Objects[i]);
			if(Highlighter->DefaultFilter == L"")
				continue;
			result = result + Highlighter->DefaultFilter;
			if(result[result.Length()] != L'|')
				result = result + L"|";
		}
	}
	return result;
}

TSynCustomHighlighter* __fastcall GetHighlighterFromFileExt(TStringList* AHighlighters, String Extension)
{
	TSynCustomHighlighter* result = nullptr;
	int ExtLen = 0;
	int i = 0;
	int j = 0;
	TSynCustomHighlighter* Highlighter = nullptr;
	String Filter;
	Extension = LowerCase(Extension);
	ExtLen = Extension.Length();
	if(ASSIGNED(AHighlighters) && (ExtLen > 0))
	{
		int stop = 0;
		for(stop = AHighlighters->Count - 1, i = 0; i <= stop; i++)
		{
			if(!(ObjectIs(AHighlighters->Objects[i], TSynCustomHighlighter*)))
				continue;
			Highlighter = ((TSynCustomHighlighter*) AHighlighters->Objects[i]);
			Filter = LowerCase(Highlighter->DefaultFilter);
			j = Pos(L"|", Filter);
			if(j > 0)
			{
				Filter.Delete(1, 	j);
				j = Pos(Extension, Filter);
				if((j > 0) && ((j + ExtLen > Filter.Length()) || (Filter[j + ExtLen] == L';')))
				{
					result = Highlighter;
					return result;
				}
			}
		}
	}
	result = nullptr;
	return result;
}
