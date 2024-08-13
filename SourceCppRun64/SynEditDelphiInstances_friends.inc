
friend struct TBufferCoord;
friend struct TLineFoldInfo;
friend class TLineFoldInfoCmp;
friend struct TSynFoldRange;
friend class TSynFoldRangesCmp;
friend class TSynUndoItem;
// friend void __fastcall AddToFoldRangeList(System::Generics::Collections::TList__1<TSynFoldRange>* AList, const TSynFoldRange& ARange);
// friend bool __fastcall BinarySearchInFoldRangeList(System::Generics::Collections::TList__1<TSynFoldRange>* AList, const TSynFoldRange& ARange, int& AIndex);
// friend bool __fastcall BinarySearchInLineFoldList(System::Generics::Collections::TList__1<TLineFoldInfo>* AList, const TLineFoldInfo& AInfo, int& AIndex);
friend System::Generics::Collections::TList__1<TLineFoldInfo>* __fastcall CreateFoldInfoList();
friend System::Generics::Collections::TList__1<TSynFoldRange>* __fastcall CreateFoldRangeList();
// friend void __fastcall InsertIntoFoldRangeList(System::Generics::Collections::TList__1<TSynFoldRange>* AList, int AIndex, const TSynFoldRange& ARange);
// friend void __fastcall InsertIntoLineFoldList(System::Generics::Collections::TList__1<TLineFoldInfo>* AList, int AIndex, const TLineFoldInfo& AInfo);
friend void SynEditDelphiInstances_initialization();
