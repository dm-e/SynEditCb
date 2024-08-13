
friend struct TFormatChunk;
friend class TFormatChunkList;
friend struct TFormatStyleData;
friend class TProposalColumn;
friend class TProposalColumns;
friend class TSynAutoComplete;
friend class TSynBaseCompletionProposal;
friend class TSynBaseCompletionProposalForm;
friend class TSynCompletionProposal;
// friend void __fastcall FormattedTextOut(TCanvas* TargetCanvas, const TRect& Rect, int PPI, const String Text, bool Selected, TProposalColumns* Columns, TCustomImageList* Images);
// friend int __fastcall FormattedTextWidth(TCanvas* TargetCanvas, const String Text, int PPI, TProposalColumns* Columns, TCustomImageList* Images);
friend String __fastcall PrettyTextToFormattedString(const String APrettyText, bool AlternateBoldStyle/*# = false*/);
friend String __fastcall FormatParamList(const String s, int CurrentIndex);
friend TSynForm* __fastcall GetMDIParent(TSynForm* const Form);
// friend int __fastcall PaintChunks(TCanvas* TargetCanvas, const TRect& Rect, int PPI, TFormatChunkList* ChunkList, TProposalColumns* Columns, TCustomImageList* Images, bool Invisible);
// friend bool __fastcall ParseFormatChunks(const String FormattedString, TFormatChunkList* ChunkList, const TFormatCommands StripCommands);
friend String __fastcall StripFormatCommands(const String FormattedString);
