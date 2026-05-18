{-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

Code template generated with SynGen.
The original code is: D:\SynEditCb\SynGen\Sample.pas, released 2026-05-15.
Description: Syntax Parser/Highlighter
The initial author of this file is Meyer.
Copyright (c) 2026, all rights reserved.

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

$Id: $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

-------------------------------------------------------------------------------}

unit Sample;

interface

uses
  Graphics,
  SynEditTypes,
  SynEditHighlighter,
  SynUnicode,
  SysUtils,
  Classes;

type
  TtkTokenKind = (
    tkIdentifier,
    tkKey,
    tkNull,
    tkUnknown);

  TRangeState = (rsUnKnown);

  TProcTableProc = procedure of object;

  PIdentFuncTableFunc = ^TIdentFuncTableFunc;
  TIdentFuncTableFunc = function (Index: Integer): TtkTokenKind of object;

type
  TSynSampleSyn = class(TSynCustomHighlighter)
  private
    fRange: TRangeState;
    fTokenID: TtkTokenKind;
    fIdentFuncTable: array[0..1] of TIdentFuncTableFunc;
    fIdentifierAttri: TSynHighlighterAttributes;
    fKeyAttri: TSynHighlighterAttributes;
    function HashKey(Str: PWideChar): Cardinal;
    function FuncHello(Index: Integer): TtkTokenKind;
    procedure IdentProc;
    procedure UnknownProc;
    function AltFunc(Index: Integer): TtkTokenKind;
    procedure InitIdent;
    function IdentKind(MayBe: PWideChar): TtkTokenKind;
    procedure NullProc;
    procedure CRProc;
    procedure LFProc;
  protected
    function GetSampleSource: string; override;
    function IsFilterStored: Boolean; override;
  public
    constructor Create(AOwner: TComponent); override;
    class function GetFriendlyLanguageName: string; override;
    class function GetLanguageName: string; override;
    function GetRange: Pointer; override;
    procedure ResetRange; override;
    procedure SetRange(Value: Pointer); override;
    function GetDefaultAttribute(Index: Integer): TSynHighlighterAttributes; override;
    function GetEol: Boolean; override;
    function GetKeyWords(TokenKind: Integer): string; override;
    function GetTokenID: TtkTokenKind;
    function GetTokenAttribute: TSynHighlighterAttributes; override;
    function GetTokenKind: Integer; override;
    function IsIdentChar(AChar: WideChar): Boolean; override;
    procedure Next; override;
  published
    property IdentifierAttri: TSynHighlighterAttributes read fIdentifierAttri write fIdentifierAttri;
    property KeyAttri: TSynHighlighterAttributes read fKeyAttri write fKeyAttri;
  end;

implementation

uses
  SynEditStrConst;

resourcestring
  SYNS_FilterSample = 'All files (*.*)|*.*';
  SYNS_LangSample = 'Sample';
  SYNS_FriendlyLangSample = 'Sample';
  SYNS_AttrIdentifier = 'Identifier';
  SYNS_FriendlyAttrIdentifier = 'Identifier';
  SYNS_AttrKey = 'Key';
  SYNS_FriendlyAttrKey = 'Key';
  SYNS_AttrNull = 'Null';
  SYNS_FriendlyAttrNull = 'Null';

const
  // as this language is case-insensitive keywords *must* be in lowercase
  KeyWords: array[0..0] of string = (
    'hello' 
  );

  KeyIndices: array[0..1] of Integer = (
    0, -1 
  );

procedure TSynSampleSyn.InitIdent;
var
  i: Integer;
begin
  for i := Low(fIdentFuncTable) to High(fIdentFuncTable) do
    if KeyIndices[i] = -1 then
      fIdentFuncTable[i] := AltFunc;

  fIdentFuncTable[0] := FuncHello;
end;

{$Q-}
function TSynSampleSyn.HashKey(Str: PWideChar): Cardinal;
begin
  Result := 0;
  while IsIdentChar(Str^) do
  begin
    Result := Result + Ord(Str^);
    inc(Str);
  end;
  Result := Result mod 2;
  fStringLen := Str - fToIdent;
end;
{$Q+}

function TSynSampleSyn.FuncHello(Index: Integer): TtkTokenKind;
begin
  if IsCurrentToken(KeyWords[Index]) then
    Result := tkKey
  else
    Result := tkIdentifier;
end;

function TSynSampleSyn.AltFunc(Index: Integer): TtkTokenKind;
begin
  Result := tkIdentifier;
end;

function TSynSampleSyn.IdentKind(MayBe: PWideChar): TtkTokenKind;
var
  Key: Cardinal;
begin
  fToIdent := MayBe;
  Key := HashKey(MayBe);
  if Key <= High(fIdentFuncTable) then
    Result := fIdentFuncTable[Key](KeyIndices[Key])
  else
    Result := tkIdentifier;
end;

procedure TSynSampleSyn.NullProc;
begin
  fTokenID := tkNull;
  inc(Run);
end;

procedure TSynSampleSyn.CRProc;
begin
  fTokenID := tkUnknown;
  inc(Run);
  if fLine[Run] = #10 then
    inc(Run);
end;

procedure TSynSampleSyn.LFProc;
begin
  fTokenID := tkUnknown;
  inc(Run);
end;

constructor TSynSampleSyn.Create(AOwner: TComponent);
begin
  inherited Create(AOwner);
  fCaseSensitive := False;

  fIdentifierAttri := TSynHighLighterAttributes.Create(, Friendly);
  AddAttribute(fIdentifierAttri);

  fKeyAttri := TSynHighLighterAttributes.Create(, Friendly);
  fKeyAttri.Style := [fsBold];
  AddAttribute(fKeyAttri);

  SetAttributesOnChange(DefHighlightChange);
  InitIdent;
  fDefaultFilter := SYNS_FilterSample;
  fRange := rsUnknown;
end;

procedure TSynSampleSyn.IdentProc;
begin
  fTokenID := IdentKind((fLine + Run));

inc(Run, fStringLen);

while Identifiers[fLine[Run]] do

Inc(Run);

end;

procedure TSynSampleSyn.UnknownProc;
begin
  inc(Run);
  fTokenID := tkUnknown;
end;

procedure TSynSampleSyn.Next;
begin
  fTokenPos := Run;
  case fLine[Run] of
    #0: NullProc;
    #10: LFProc;
    #13: CRProc;
    'A'..'Z', 'a'..'z', '_': IdentProc;
  else
    UnknownProc;
  end;
  inherited;
end;

function TSynSampleSyn.GetDefaultAttribute(Index: Integer): TSynHighLighterAttributes;
begin
  case Index of
    SYN_ATTR_IDENTIFIER: Result := fIdentifierAttri;
    SYN_ATTR_KEYWORD: Result := fKeyAttri;
  else
    Result := nil;
  end;
end;

function TSynSampleSyn.GetEol: Boolean;
begin
  Result := Run = fLineLen + 1;
end;

function TSynSampleSyn.GetKeyWords(TokenKind: Integer): string;
begin
  Result := 
    'Hello';
end;

function TSynSampleSyn.GetTokenID: TtkTokenKind;
begin
  Result := fTokenId;
end;

function TSynSampleSyn.GetTokenAttribute: TSynHighLighterAttributes;
begin
  case GetTokenID of
    tkIdentifier: Result := fIdentifierAttri;
    tkKey: Result := fKeyAttri;
    tkUnknown: Result := fIdentifierAttri;
  else
    Result := nil;
  end;
end;

function TSynSampleSyn.GetTokenKind: Integer;
begin
  Result := Ord(fTokenId);
end;

function TSynSampleSyn.IsIdentChar(AChar: WideChar): Boolean;
begin
  case AChar of
    '_', '0'..'9', 'a'..'z', 'A'..'Z':
      Result := True;
    else
      Result := False;
  end;
end;

function TSynSampleSyn.GetSampleSource: string;
begin
  Result := 
    'Sample source for: '#13#10 +
    'Syntax Parser/Highlighter';
end;

function TSynSampleSyn.IsFilterStored: Boolean;
begin
  Result := fDefaultFilter <> SYNS_FilterSample;
end;

class function TSynSampleSyn.GetFriendlyLanguageName: string;
begin
  Result := SYNS_FriendlyLangSample;
end;

class function TSynSampleSyn.GetLanguageName: string;
begin
  Result := SYNS_LangSample;
end;

procedure TSynSampleSyn.ResetRange;
begin
  fRange := rsUnknown;
end;

procedure TSynSampleSyn.SetRange(Value: Pointer);
begin
  fRange := TRangeState(Value);
end;

function TSynSampleSyn.GetRange: Pointer;
begin
  Result := Pointer(fRange);
end;

initialization
{$IFNDEF SYN_CPPB_1}
  RegisterPlaceableHighlighter(TSynSampleSyn);
{$ENDIF}
end.
