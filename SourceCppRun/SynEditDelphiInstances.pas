unit SynEditDelphiInstances;

interface

{$HPPEMIT '#pragma link "SynEditDelphiInstances"'}

uses
  System.Generics.Collections, System.Generics.Defaults, Vcl.Controls;

type

  // A single fold
  // Important: FromLine, ToLine are 1-based
  TSynFoldRange = record
    FromLine: Integer; // Beginning line
    ToLine: Integer; // End line
    FoldType: Integer;  // Could be used by some complex highlighters
    Indent : Integer;   // Only used for Indent based folding (Python)
    Collapsed: Boolean; // Is collapsed?
  private
    function GetLinesCollapsed: Integer;
  public
    procedure Move(Count: Integer);
    property LinesCollapsed: Integer read GetLinesCollapsed;
    constructor Create(AFromLine : Integer; AToLine : Integer = -1;
      AFoldType : Integer = 1; AIndent : Integer = -1;
      ACollapsed : Boolean = False);
  end;

  PSynFoldRange = ^TSynFoldRange;

  TFoldOpenClose = (focOpen, focClose);

  TLineFoldInfo = record
    Line : Integer;
    FoldOpenClose : TFoldOpenClose;
    FoldType : Integer;
    Indent : Integer;
    constructor Create(ALine : Integer;
      AFoldOpenClose : TFoldOpenClose = focOpen;
      AFoldType : Integer = 1; AIndent : Integer = -1);
  end;

  TBufferCoord = record
    Char: integer;
    Line: integer;
    class operator Equal(a, b: TBufferCoord): Boolean;
    class operator NotEqual(a, b: TBufferCoord): Boolean;
    class operator LessThan(a, b: TBufferCoord): Boolean;
    class operator LessThanOrEqual(a, b: TBufferCoord): Boolean;
    class operator GreaterThan(a, b: TBufferCoord): Boolean;
    class operator GreaterThanOrEqual(a, b: TBufferCoord): Boolean;
    class function Min(a, b: TBufferCoord): TBufferCoord; static;
    class function Max(a, b: TBufferCoord): TBufferCoord; static;
  end;

  TSynUndoItem = class abstract(TObject)
    ChangeNumber: Integer;
    FCaret: TBufferCoord;
    GroupBreak: Boolean;
  public
    procedure Undo(Editor: TCustomControl); virtual; abstract;
    procedure Redo(Editor: TCustomControl); virtual; abstract;
  end;


TSynFoldRangesCmp = class(TInterfacedObject, System.Generics.Defaults.IComparer<TSynFoldRange>)
public
  function Compare(const Left, Right: TSynFoldRange): Integer;
end;

TLineFoldInfoCmp = class(TInterfacedObject, System.Generics.Defaults.IComparer<TLineFoldInfo>)
public
  function Compare(const Left, Right: TLineFoldInfo): Integer;
end;

function CreateFoldRangeList: System.Generics.Collections.TList<TSynFoldRange>;
function CreateFoldInfoList: System.Generics.Collections.TList<TLineFoldInfo>;

procedure AddToFoldRangeList(AList: System.Generics.Collections.TList<TSynFoldRange>; ARange: TSynFoldRange);
function BinarySearchInFoldRangeList(AList: System.Generics.Collections.TList<TSynFoldRange>; ARange: TSynFoldRange; var AIndex: Integer): Boolean;

// for SynEditCodeFolding
procedure InsertIntoLineFoldList(AList: System.Generics.Collections.TList<TLineFoldInfo>; AIndex: Integer; AInfo: TLineFoldInfo);
function BinarySearchInLineFoldList(AList: System.Generics.Collections.TList<TLineFoldInfo>; AInfo: TLineFoldInfo; var AIndex: Integer): Boolean;

implementation


function TSynFoldRangesCmp.Compare(const Left, Right: TSynFoldRange): Integer;
begin
  Result := Left.FromLine - Right.FromLine;
end;

function TLineFoldInfoCmp.Compare(const Left, Right: TLineFoldInfo): Integer;
begin
  Result := Left.Line - Right.Line;
end;


function CreateFoldRangeList: System.Generics.Collections.TList<TSynFoldRange>;
begin
  result := System.Generics.Collections.TList<TSynFoldRange>.Create(TSynFoldRangesCmp.Create);
end;

function CreateFoldInfoList: System.Generics.Collections.TList<TLineFoldInfo>;
begin
  result := System.Generics.Collections.TList<TLineFoldInfo>.Create(TLineFoldInfoCmp.Create);
end;


{ TSynEditFoldRange }

constructor TSynFoldRange.Create(AFromLine, AToLine, AFoldType: Integer;
  AIndent : Integer; ACollapsed: Boolean);
begin
  FromLine := AFromLine;
  ToLine := AToLine;
  FoldType := AFoldType;
  Indent := AIndent;
  Collapsed := ACollapsed;
end;

function TSynFoldRange.GetLinesCollapsed: Integer;
begin
  if Collapsed then
    Result := ToLine - FromLine
  else
    Result := 0;
end;

procedure TSynFoldRange.Move(Count: Integer);
begin
  Inc(FromLine, Count);
  Inc(ToLine, Count);
end;

constructor TLineFoldInfo.Create(ALine: Integer;
  AFoldOpenClose: TFoldOpenClose; AFoldType: Integer; AIndent : Integer);
begin
    Line := ALine;
    FoldOpenClose := AFoldOpenClose;
    FoldType := AFoldType;
    Indent := AIndent;
end;

procedure AddToFoldRangeList(AList: System.Generics.Collections.TList<TSynFoldRange>; ARange: TSynFoldRange);
begin
  AList.Add(ARange);
end;

function BinarySearchInFoldRangeList(AList: System.Generics.Collections.TList<TSynFoldRange>; ARange: TSynFoldRange; var AIndex: Integer): Boolean;
begin
  result := AList.BinarySearch(ARange, AIndex);
end;

// for SynEditCodeFolding
procedure InsertIntoLineFoldList(AList: System.Generics.Collections.TList<TLineFoldInfo>; AIndex: Integer; AInfo: TLineFoldInfo);
begin
  AList.Insert(AIndex, AInfo);
end;

function BinarySearchInLineFoldList(AList: System.Generics.Collections.TList<TLineFoldInfo>; AInfo: TLineFoldInfo; var AIndex: Integer): Boolean;
begin
  result := AList.BinarySearch(AInfo, AIndex);
end;

{ TBufferCoord }

class operator TBufferCoord.Equal(a, b: TBufferCoord): Boolean;
begin
  Result := (a.Char = b.Char) and (a.Line = b.Line);
end;

class operator TBufferCoord.GreaterThan(a, b: TBufferCoord): Boolean;
begin
  Result :=  (b.Line < a.Line)
    or ((b.Line = a.Line) and (b.Char < a.Char))
end;

class operator TBufferCoord.GreaterThanOrEqual(a, b: TBufferCoord): Boolean;
begin
  Result :=  (b.Line < a.Line)
    or ((b.Line = a.Line) and (b.Char <= a.Char))
end;

class operator TBufferCoord.LessThan(a, b: TBufferCoord): Boolean;
begin
  Result :=  (b.Line > a.Line)
    or ((b.Line = a.Line) and (b.Char > a.Char))
end;

class operator TBufferCoord.LessThanOrEqual(a, b: TBufferCoord): Boolean;
begin
  Result :=  (b.Line > a.Line)
    or ((b.Line = a.Line) and (b.Char >= a.Char))
end;

class function TBufferCoord.Max(a, b: TBufferCoord): TBufferCoord;
begin
  if (b.Line < a.Line)
    or ((b.Line = a.Line) and (b.Char < a.Char))
  then
    Result := a
  else
    Result := b;
end;

class function TBufferCoord.Min(a, b: TBufferCoord): TBufferCoord;
begin
  if (b.Line < a.Line)
    or ((b.Line = a.Line) and (b.Char < a.Char))
  then
    Result := b
  else
    Result := a;
end;

class operator TBufferCoord.NotEqual(a, b: TBufferCoord): Boolean;
begin
  Result := (a.Char <> b.Char) or (a.Line <> b.Line);
end;

var
  rlist : System.Generics.Collections.TList<TSynFoldRange>;
  r : TSynFoldRange;

initialization
  System.Generics.Collections.TList<System.Word>.Create.Free;
  System.Generics.Collections.TList<Integer>.Create.Free;
  System.Generics.Collections.TList<TLineFoldInfo>.Create.Free;
  System.Generics.Collections.TEnumerable<System.Word>.Create.Free;
  rlist := System.Generics.Collections.TList<TSynFoldRange>.Create;
  rlist.Add(r);
  rlist.Free;
  System.Generics.Collections.TObjectStack<TSynUndoItem>.Create.Free;

end.