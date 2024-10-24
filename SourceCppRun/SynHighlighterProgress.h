/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterProgress.pas, released 2000-04-20.
The Initial Author of the Original Code is Bruno Mikkelsen.
Portions written by Bruno Mikkelsen are copyright 2000 Bruno Mikkelsen.
Unicode translation by Maël Hörz.
All Rights Reserved.

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

$Id: SynHighlighterProgress.pas,v 1.16.2.8 2009/09/28 19:16:08 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
/*
@abstract(Provides a Progress Syntax highlighter for SynEdit)
@author(Bruno Mikkelsen <btm@scientist.com>)
@created(2000-04-16)
@lastmod(2000-06-20)
The SynHighlighterProgress provides SynEdit with a syntax highlighter for the
Progress programming language.
Thanks to Michael Hieke for providing a sample highlighter on which this
highlighter is based.
*/
#ifndef SynHighlighterProgressH
#define SynHighlighterProgressH

#include <System.hpp>
#include "d2c_system.h"

#include <Vcl.Graphics.hpp>
#include "SynEditTypes.h"
#include "SynEditHighlighter.h"
#include "SynHighlighterHashEntries.h"
#include "SynUnicode.h"
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>

namespace Synhighlighterprogress
{

/*-------------------------------------------------------------------------------
The contents of this file are subject to the Mozilla Public License
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynHighlighterProgress.pas, released 2000-04-20.
The Initial Author of the Original Code is Bruno Mikkelsen.
Portions written by Bruno Mikkelsen are copyright 2000 Bruno Mikkelsen.
Unicode translation by Maël Hörz.
All Rights Reserved.

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

$Id: SynHighlighterProgress.pas,v 1.16.2.8 2009/09/28 19:16:08 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
/*
@abstract(Provides a Progress Syntax highlighter for SynEdit)
@author(Bruno Mikkelsen <btm@scientist.com>)
@created(2000-04-16)
@lastmod(2000-06-20)
The SynHighlighterProgress provides SynEdit with a syntax highlighter for the
Progress programming language.
Thanks to Michael Hieke for providing a sample highlighter on which this
highlighter is based.
*/

/*------------------------------------------------------------------------------*/
/* Common compiler defines                                                      */
/* (remove the dot in front of a define to enable it)                           */
/*------------------------------------------------------------------------------*/

/*$B-,H+*/ // defaults are short evaluation of boolean values and long strings

/*.$DEFINE SYN_DEVELOPMENT_CHECKS*/ // additional tests for debugging
  

/*------------------------------------------------------------------------------*/
/* Pull in all defines from SynEditJedi.inc (must be done after the common      */
/* compiler defines to  work correctly). Use SynEdit-prefix to avoid problems   */
/* with other versions of jedi.inc in the search-path.                          */
/*------------------------------------------------------------------------------*/

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                

/*------------------------------------------------------------------------------*/
/*  Please change this to suit your needs (to activate an option remove the dot */
/*  in front of a DEFINE)                                                       */
/*------------------------------------------------------------------------------*/

// "Heredoc" syntax highlighting
// If you enable the following statement and use highlighter(s) that have
// support for "Heredoc" strings as scheme(s) in SynMultiSyn, you must
// implement your own SynMultiSyn OnCustomRange event handler in order to
// properly store Range State information
/*.$DEFINE SYN_HEREDOC*/

// Turn this off if you don't need complex script support, since it is slower
/*.$DEFINE SYN_UNISCRIBE*/

// $Id: SynEdit.inc,v 1.16.2.19 2009/06/14 13:41:44 maelh Exp $

  /*Enumerates the different tokens in Progress.*/
enum TtkTokenKind {tkComment,
                   tkEvent,
                   tkIdentifier,
                   tkInclude,
                   tkKey,
                   tkNonReserved,
                   tkNull,
                   tkNumber,
                   tkPreprocessor,
                   tkSpace,
                   tkDataType,
                   tkString,
                   tkSymbol,
                   tkUnknown };


  /*Enumerates the ranges in Progress syntax.*/
enum TRangeState {rsNone,
                  rsInclude,
                  rsPreprocessorDef,
                  rsPreprocessor,
                  rsComment };


  /*Used to hold extra rangeinfo in the Lines.Objects pointer.*/
#pragma pack (push, 1)


struct TRangeInfo
{
	union {
		/*# false*/
		struct 
		{
			void* Ptr;
		};		
		/*# true*/
		struct 
		{
			WORD Range;
			WORD Level;
		};		
	};
};
#pragma pack (pop)

typedef TtkTokenKind __fastcall (__closure *TIdentFuncTableFunc) (int);
typedef TIdentFuncTableFunc* PIdentFuncTableFunc;

class TSynProgressSyn : public Synedithighlighter::TSynCustomHighlighter
{
private:
	TRangeState fRange;
	int fCommentLevel;
	int fIncludeLevel;
	int fPreProcessorLevel;
	TtkTokenKind FTokenID;
	Synedithighlighter::TSynHighlighterAttributes* fCommentAttri;
	Synedithighlighter::TSynHighlighterAttributes* fEventAttri;
	Synedithighlighter::TSynHighlighterAttributes* fIdentifierAttri;
	Synedithighlighter::TSynHighlighterAttributes* fIncludeAttri;
	Synedithighlighter::TSynHighlighterAttributes* fKeyAttri;
	Synedithighlighter::TSynHighlighterAttributes* fNonReservedKeyAttri;
	Synedithighlighter::TSynHighlighterAttributes* fNumberAttri;
	Synedithighlighter::TSynHighlighterAttributes* fPreprocessorAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSpaceAttri;
	Synedithighlighter::TSynHighlighterAttributes* fStringAttri;
	Synedithighlighter::TSynHighlighterAttributes* fDataTypeAttri;
	Synedithighlighter::TSynHighlighterAttributes* fSymbolAttri;
	Synhighlighterhashentries::TSynHashEntryList* fHashList;
	void __fastcall DoAddKeyword(String AKeyword, int AKind);
	int __fastcall HashKey(PWideChar Str);
	TtkTokenKind __fastcall IdentKind(PWideChar MayBe);
	void __fastcall AsciiCharProc();
	void __fastcall CommentRangeProc();
	void __fastcall IncludeRangeProc();
	void __fastcall PreprocessorRangeProc();
	void __fastcall PreprocessorDefinitionProc();
	void __fastcall PreprocessorDefinitionRangeProc();
	void __fastcall BraceOpenProc();
	void __fastcall IdentProc();
	void __fastcall NullProc();
	void __fastcall NumberProc();
	void __fastcall SlashProc();
	void __fastcall SpaceProc();
	void __fastcall StringProc();
	void __fastcall UnknownProc();
	void __fastcall SymbolProc();
protected:
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetDefaultAttribute(int Index);
	virtual String __fastcall GetSampleSource();
	virtual bool __fastcall IsFilterStored();
public:
	typedef Synedithighlighter::TSynCustomHighlighter inherited;
	#include "SynHighlighterProgress_friends.inc"
	__classmethod virtual String __fastcall GetLanguageName();
	__classmethod virtual String __fastcall GetFriendlyLanguageName();
	__fastcall TSynProgressSyn(TComponent* AOwner);
	virtual __fastcall ~TSynProgressSyn();
	virtual bool __fastcall GetEol();
	virtual void* __fastcall GetRange();
	TtkTokenKind __fastcall GetTokenID();
	virtual Synedithighlighter::TSynHighlighterAttributes* __fastcall GetTokenAttribute();
	virtual int __fastcall GetTokenKind();
	virtual bool __fastcall IsIdentChar(WideChar AChar);
	virtual void __fastcall Next();
	virtual void __fastcall SetRange(void* Value);
	virtual void __fastcall ResetRange();
__published:
	__property Synedithighlighter::TSynHighlighterAttributes* CommentAttri = { read = fCommentAttri, write = fCommentAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* EventAttri = { read = fEventAttri, write = fEventAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* IdentifierAttri = { read = fIdentifierAttri, write = fIdentifierAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* IncludeAttri = { read = fIncludeAttri, write = fIncludeAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* KeyAttri = { read = fKeyAttri, write = fKeyAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* NonReservedKeyAttri = { read = fNonReservedKeyAttri, write = fNonReservedKeyAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* NumberAttri = { read = fNumberAttri, write = fNumberAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* PreprocessorAttri = { read = fPreprocessorAttri, write = fPreprocessorAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* SpaceAttri = { read = fSpaceAttri, write = fSpaceAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* StringAttri = { read = fStringAttri, write = fStringAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* DataTypeAttri = { read = fDataTypeAttri, write = fDataTypeAttri };
	__property Synedithighlighter::TSynHighlighterAttributes* SymbolAttri = { read = fSymbolAttri, write = fSymbolAttri };
};
const String DefaultKeywords = L"accum accumulate active-window add alias "
	           L"all alter ambig ambiguous analyze "
	           L"analyze-resume analyze-suspend and any apply "
	           L"as asc ascending assign at "
	           L"attr-space authorization auto-return avail available "
	           L"background before-hide begins bell between "
	           L"bin blank break btos by "
	           L"byte call can-do can-find case "
	           L"case-sensitive center centered check chr "
	           L"clear clipboard col colon color "
	           L"column column-label columns compiler control "
	           L"count-of cpstream create ctos current "
	           L"current-changed current-lang current-language current-window cursor "
	           L"database dataservers dbcodepage dbcollation dbname "
	           L"dbparam dbrestrictions dbtaskid dbtype dbversion "
	           L"dde deblank debug-list debugger decimals "
	           L"declare def default default-noxlate default-window "
	           L"define delete delimiter desc descending "
	           L"dict dictionary disable disconnect disp "
	           L"display distinct do dos down "
	           L"drop each editing else "
	           L"elseif enable encode end endif "
	           L"entry error-status escape etime except "
	           L"exclusive exclusive-lock exists export false "
	           L"fetch field fields file-info file-information "
	           L"fill find find-case-sensitive find-global find-next-occurrence "
	           L"find-prev-occurrence find-select find-wrap-around first first-of "
	           L"focus font font-based-grid for form "
	           L"format frame frame-col frame-db frame-down "
	           L"frame-field frame-file frame-index frame-line frame-name "
	           L"frame-row frame-val frame-value from from-chars "
	           L"from-pixels gateways get-byte get-codepages get-collations "
	           L"get-key-value getbyte glob global "
	           L"global-define go-on go-pending grant graphic-edge "
	           L"group having header help hide "
	           L"if import in index "
	           L"indicator input input-output insert into "
	           L"is is-attr-space join kblabel key-code "
	           L"key-function key-label keycode keyfunction keylabel "
	           L"keys keyword label last last-event "
	           L"last-key last-of lastkey ldbname leave "
	           L"library like line-count line-counter line-number "
	           L"listing locked long lookup machine-class "
	           L"map max-button member memptr message "
	           L"message-lines mouse mpe new next "
	           L"next-prompt no no-attr-space no-error no-fill "
	           L"no-help no-hide no-label no-labels no-lobs no-lock "
	           L"no-map no-message no-pause no-prefetch no-undo "
	           L"no-validate no-wait not null num-aliases "
	           L"num-dbs num-entries of off old "
	           L"on open opsys option "
	           L"or os-append os-command os-copy os-create-dir "
	           L"os-delete os-dir os-rename os2 os400 "
	           L"otherwise output overlay page page-bottom "
	           L"page-num page-number page-top param parameter "
	           L"pause pdbname persistent pixels preprocess "
	           L"privileges proc-handle proc-status process program-name "
	           L"progress prompt prompt-for promsgs propath "
	           L"proversion put put-byte put-key-value putbyte "
	           L"query query-tuning quit r-index rcode-information "
	           L"readkey recid record-length rectangle "
	           L"release repeat reposition retain retry "
	           L"return revert revoke run save "
	           L"schema scop scoped scoped-define screen "
	           L"screen-io screen-lines scroll sdbname search "
	           L"seek select self sequence session "
	           L"set setuserid share share-lock shared "
	           L"short show-stats skip some space "
	           L"status stream stream-io string-xref system-dialog "
	           L"table tab-stop term terminal text text-cursor "
	           L"text-height text-seg-growth then this-procedure "
	           L"time title to top-only trans "
	           L"transaction trigger triggers trim true "
	           L"undefine underline undo unformatted union "
	           L"unique unix unless-hidden unsigned-short up "
	           L"update use-index use-revvideo use-underline user "
	           L"userid using v6frame value values "
	           L"view view-as vms wait-for web-context "
	           L"when where while widget-id window window-maximized "
	           L"window-minimized window-normal with work-table workfile "
	           L"write xcode xref yes _actailog "
	           L"_actbilog _actbuffer _actindex _actiofile _actiotype "
	           L"_actlock _actother _actpws _actrecord _actserver "
	           L"_actspace _actsummary _block _buffstatus _cbit "
	           L"_checkpoint _connect _control _db _dbstatus "
	           L"_dcm _field _field-trig _file _file-trig "
	           L"_filelist _index _index-field _license _list "
	           L"_lock _lockreq _logging _memory _msg "
	           L"_mstrblk _pcontrol _segments _sequence _serial-num "
	           L"_servers _startup _trace _trans _user "
	           L"_userio _userlock _view _view-col _view-ref";
const String DefaultNonReservedKeywords = L"abs absolute accelerator across add-events-procedure "
	           L"add-first add-interval add-last advise alert-box allow-replication "
	           L"ansi-only anywhere append appl-alert appl-alert-boxes "
	           L"application as-cursor ask-overwrite attachment auto-endkey "
	           L"auto-end-key auto-go auto-indent auto-resize auto-zap "
	           L"available-formats average avg backwards base-key "
	           L"batch batch-mode bgc bgcolor "
	           L"binary bind-where block-iteration-display border-bottom border-bottom-chars "
	           L"border-bottom-pixels border-left border-left-chars border-left-pixels border-right "
	           L"border-right-chars border-right-pixels border-top border-top-chars border-top-pixels "
	           L"both bottom box box-select box-selectable "
	           L"browse browse-header btn-down-arrow btn-left-arrow btn-right-arrow "
	           L"btn-up-arrow buffer buffer-chars buffer-compare buffer-copy "
	           L"buffer-lines button buttons cache cache-size "
	           L"cancel-break cancel-button can-query can-set caps "
	           L"cdecl character_length charset checked clear-select "
	           L"clear-selection code codepage codepage-convert col-of "
	           L"colon-align colon-aligned color-table column-bgcolor column-dcolor "
	           L"column-fgcolor column-font column-label-bgcolor column-label-dcolor column-label-fgcolor "
	           L"column-label-font column-of column-scrolling com1 com2 "
	           L"com3 com4 com5 com6 com7 "
	           L"com8 com9 combo-box command complete "
	           L"com-self con connect connected "
	           L"constrained contains contents context context-popup "
	           L"control-container convert convert-3d-colors convert-to-offset count copy-lob "
	           L"cpcase cpcoll cpinternal cplog cpprint "
	           L"cprcodein cprcodeout cpterm crc-value create-control "
	           L"create-result-list-entry create-test-file current_date current-column "
	           L"current-iteration current-result-row current-row-modified current-value cursor-char "
	           L"cursor-line cursor-offset data-entry-return data-type date-format "
	           L"day db-references dcolor dde-error dde-id "
	           L"dde-item dde-name dde-topic debug default-button "
	           L"default-extension defined delete-current-row delete-selected-row delete-selected-rows "
	           L"deselect-focused-row deselect-rows deselect-selected-row design-mode dialog-box "
	           L"dialog-help dir disabled display-message display-type "
	           L"drag-enabled drop-down drop-down-list dump dynamic dynamic-function "
	           L"echo edge edge-chars edge-pixels edit-can-undo "
	           L"editor edit-undo empty end-key entered "
	           L"eq error error-col error-column error-row "
	           L"events event-type exp expand extended "
	           L"extent external extract fetch-selected-row fgc "
	           L"fgcolor file filename file-create-date file-create-time file-mod-date file-mod-time file-name "
	           L"file-offset file-size file-type filled fill-in filters "
	           L"first-child first-column first-proc first-procedure first-server "
	           L"first-tab-item fixed-only focused-row font-table force-file "
	           L"foreground forwards frame-spacing frame-x frame-y "
	           L"frequency from-current full-height full-height-chars full-height-pixels "
	           L"full-pathname full-width full-width-chars full-width-pixels function "
	           L"ge get-blue get-blue-value get-char-property get-double "
	           L"get-dynamic get-file get-float get-green get-green-value "
	           L"get-iteration get-license get-long get-message get-number "
	           L"get-pointer-value get-red get-red-value get-repositioned-row get-selected "
	           L"get-selected-widget get-short get-signature get-size get-string "
	           L"get-tab-item get-text-height get-text-height-chars get-text-height-pixels get-text-width "
	           L"get-text-width-chars get-text-width-pixels get-unsigned-short grayed grid-factor-h "
	           L"grid-factor-horizontal grid-factor-v grid-factor-vertical grid-set grid-snap "
	           L"grid-unit-height grid-unit-height-chars grid-unit-height-pixels grid-unit-width grid-unit-width-chars "
	           L"grid-unit-width-pixels grid-visible gt height height-chars "
	           L"height-pixels help-context hidden horizontal hwnd "
	           L"image image-down image-insensitive image-size image-size-chars "
	           L"image-size-pixels image-up immediate-display indexed-reposition index-hint "
	           L"info information init initial initial-dir "
	           L"initial-filter initiate inner inner-chars inner-lines input-value "
	           L"insert-backtab insert-file insert-row insert-string insert-tab instantiating-procedure "
	           L"internal-entries is-lead-byte is-row-selected is-selected item "
	           L"items-per-row join-by-sqldb keep-frame-z-order keep-messages keep-tab-order "
	           L"key keyword-all label-bgc label-bgcolor label-dc "
	           L"label-dcolor label-fgc label-fgcolor label-font label-pfc "
	           L"label-pfcolor labels languages large large-to-small "
	           L"last-child last-proc last-procedure last-server last-tab-item "
	           L"lc le leading left-aligned left-trim "
	           L"length line list-events list-items list-item-pairs list-query-attrs "
	           L"list-set-attrs list-widgets load load-control loadcontrols "
	           L"load-icon load-image load-image-down load-image-insensitive load-image-up "
	           L"load-mouse-pointer load-small-icon log-id lookahead lower "
	           L"lpt0 lpt1 lpt2 lpt3 lpt4 "
	           L"lpt5 lpt6 lpt7 lpt8 lpt9 "
	           L"lt manual-highlight margin-extra margin-height margin-height-chars "
	           L"margin-height-pixels margin-width margin-width-chars margin-width-pixels matches "
	           L"max max-chars max-data-guess max-height "
	           L"max-height-chars max-height-pixels maximize maximum max-rows "
	           L"max-size max-value max-width max-width-chars max-width-pixels "
	           L"memory menu menubar menu-bar menu-item "
	           L"menu-key menu-mouse message-area message-area-font message-line "
	           L"min min-height min-height-chars min-height-pixels minimum "
	           L"min-size min-value min-width min-width-chars min-width-pixels "
	           L"mod modified modulo month mouse-pointer "
	           L"movable move-after move-after-tab-item move-before move-before-tab-item "
	           L"move-column move-to-bottom move-to-eof move-to-top multiple "
	           L"multiple-key multitasking-interval must-exist name native "
	           L"ne new-row next-column next-sibling next-tab-item "
	           L"next-value no-apply no-assign no-bind-where no-box "
	           L"no-column-scrolling no-convert no-current-value no-debug no-drag "
	           L"no-echo no-focus no-index-hint no-join-by-sqldb no-lookahead "
	           L"no-return-value no-row-markers no-scrolling no-separate-connection no-separators "
	           L"no-underline no-word-wrap num-buttons num-columns num-copies "
	           L"numeric numeric-format num-formats num-items num-iterations "
	           L"num-lines num-locked-columns num-messages num-results num-selected "
	           L"num-selected-rows num-selected-widgets num-tabs num-to-retain octet_length "
	           L"ok ok-cancel on-frame on-frame-border ordinal "
	           L"orientation os-drives os-error "
	           L"os-getenv outer outer-join override owner "
	           L"paged page-size page-width parent partial-key "
	           L"pascal password-field pathname pfc pfcolor pinnable "
	           L"pixels-per-col pixels-per-column pixels-per-row popup-menu popup-only "
	           L"position precision preselect prev prev-column "
	           L"prev-sibling prev-tab-item primary printer-control-handle printer-name "
	           L"printer-port printer-setup private private-data prn procedure "
	           L"progress-source proxy put-double put-float put-long "
	           L"put-short put-string put-unsigned-short query-off-end question "
	           L"radio-buttons radio-set random raw-transfer read-file "
	           L"read-only real recursive refresh refreshable "
	           L"remote remove-events-list replace replace-selection-text replication-create "
	           L"replication-delete replication-write request resizable resize "
	           L"retry-cancel return-inserted returns return-to-start-dir return-value "
	           L"right-aligned right-trim round row "
	           L"row-markers row-of rule rule-row rule-y "
	           L"save-file screen-value scrollable scrollbar-h scrollbar-horizontal "
	           L"scroll-bars scrollbar-v scrollbar-vertical scroll-delta scrolled-row-pos "
	           L"scrolled-row-position scroll-horiz-value scrolling scroll-offset scroll-to-current-row "
	           L"scroll-to-item scroll-to-selected-row scroll-vert-value se-check-pools section "
	           L"se-enable-off se-enable-on selectable selected selected-items "
	           L"select-focused-row selection-end selection-list selection-start selection-text "
	           L"select-next-row select-prev-row select-repositioned-row select-row send "
	           L"sensitive se-num-pools separate-connection separators server "
	           L"set-blue set-blue-value set-break set-cell-focus set-contents "
	           L"set-dynamic set-green set-green-value set-leakpoint set-pointer-value "
	           L"set-property set-red set-red-value set-repositioned-row set-selection "
	           L"set-size set-wait-state se-use-message side-label-handle side-labels "
	           L"silent simple single size size-chars "
	           L"size-pixels slider smallint sort source "
	           L"sql sqrt start status-area status-area-font "
	           L"status-bar stdcall stenciled stopped stored-procedure "
	           L"string sub-average sub-count sub-max sub-maximum "
	           L"sub-menu sub-menu-help sub-min sub-minimum substitute "
	           L"substr substring sub-total subtype sum "
	           L"suppress-warnings system-alert-boxes system-help tab-position target "
	           L"temp-dir temp-directory temp-table terminate text-selected "
	           L"three-d through thru tic-marks time-source "
	           L"title-bgc title-bgcolor title-dc title-dcolor title-fgc "
	           L"title-fgcolor title-font today toggle-box "
	           L"tool-bar tooltip tooltips top topic "
	           L"to-rowid total trailing trunc truncate "
	           L"type unbuffered unique-id unload upper "
	           L"use use-dict-exps use-filename use-text v6display "
	           L"validate validate-condition validate-message valid-event valid-handle "
	           L"var variable vertical virtual-height virtual-height-chars "
	           L"virtual-height-pixels virtual-width virtual-width-chars virtual-width-pixels visible "
	           L"wait warning weekday widget-enter widget-leave "
	           L"widget-pool width width-chars width-pixels window-name "
	           L"window-state window-system word-wrap x "
	           L"x-of y year year-offset yes-no "
	           L"yes-no-cancel y-of";
const String DefaultEvents = L"abort any-key any-printable append-line backspace "
	           L"back-tab block blue bottom-column break-line "
	           L"bs cancel cancel-move cancel-pick cancel-resize "
	           L"choices choose close compile container-event "
	           L"copy cr ctrl-alt-del ctrl-break ctrl-g "
	           L"ctrl-j ctrl-l cursor-down cursor-left cursor-right "
	           L"cursor-up cut data-refresh-line data-refresh-page dde-notify "
	           L"default-action default-pop-up del del-char delete-char "
	           L"delete-character delete-column delete-end-line delete-field delete-line "
	           L"delete-word del-line deselect deselect-extend deselection "
	           L"deselection-extend dismiss-menu dos-end down-arrow editor-backtab "
	           L"editor-tab empty-selection end-box-selection end-error endkey "
	           L"end-move end-resize end-search enter enter-menubar "
	           L"erase esc execute exit "
	           L"ff find-next find-previous focus-in formfeed "
	           L"forward get go goto help-key "
	           L"home horiz-end horiz-home horiz-scroll-drag ins "
	           L"ins-char insert-column insert-field insert-field-data insert-field-label "
	           L"insert-here insert-mode ins-line iteration-changed left "
	           L"left-arrow left-end left-mouse-click left-mouse-dblclick left-mouse-down "
	           L"left-mouse-up lf line-del line-down line-erase "
	           L"linefeed line-ins line-left line-right line-up "
	           L"main-menu menu-drop middle-mouse-click middle-mouse-dblclick middle-mouse-down "
	           L"middle-mouse-up mouse-extend-click mouse-extend-dblclick mouse-extend-down mouse-extend-drag "
	           L"mouse-extend-up mouse-menu-click mouse-menu-dblclick mouse-menu-down mouse-menu-drag "
	           L"mouse-menu-up mouse-move mouse-move-click mouse-move-dblclick mouse-move-down "
	           L"mouse-move-drag mouse-move-up mouse-select-click mouse-select-dblclick mouse-select-down "
	           L"mouse-select-drag mouse-select-up move new-line next-error "
	           L"next-frame next-page next-scrn next-word object "
	           L"off-end off-home open-line-above options out-of-data "
	           L"page-down page-erase page-left page-right page-right-text "
	           L"page-up parent-window-close paste pgdn pgup "
	           L"pick pick-area pick-both popup-menu-key prev-frame "
	           L"prev-page prev-scrn prev-word recall red "
	           L"remove reports reset resume-display "
	           L"right right-arrow right-end right-mouse-click "
	           L"right-mouse-dblclick right-mouse-down right-mouse-up row-display row-entry "
	           L"row-leave save-as scrollbar-drag scroll-left "
	           L"scroll-mode scroll-notify scroll-right select-extend selection "
	           L"selection-extend settings shift-tab start-box-selection start-extend-box-selection "
	           L"start-move start-resize start-search stop stop-display "
	           L"tab top-column u1 u10 u2 "
	           L"u3 u4 u5 u6 u7 "
	           L"u8 u9 unix-end up-arrow value-changed "
	           L"white window-close window-resized window-restored";
const String DefaultDataTypes = L"char character com-handle component-handle date datetime datetime-tz dec "
	           L"decimal double float handle int "
	           L"integer int64 log logical longchar raw rowid "
	           L"widget widget-handle";

void SynHighlighterProgress_initialization();


}  // namespace SynHighlighterProgress

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Synhighlighterprogress;
#endif


#endif // SynHighlighterProgressH

