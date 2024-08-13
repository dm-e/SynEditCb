/*-------------------------------------------------------------------------------
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynEditStrConst.pas, released 2000-04-07.
The Original Code is based on mwLocalStr.pas by Michael Hieke, part of the
mwEdit component suite.
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

$Id: SynEditStrConst.pas,v 1.41.2.5 2009/01/06 16:26:01 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/
#ifndef SynEditStrConstH
#define SynEditStrConstH

#include <System.hpp>
#include "d2c_system.h"


namespace Syneditstrconst
{

/*-------------------------------------------------------------------------------
Version 1.1 (the "License"); you may not use this file except in compliance
with the License. You may obtain a copy of the License at
http://www.mozilla.org/MPL/

Software distributed under the License is distributed on an "AS IS" basis,
WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License for
the specific language governing rights and limitations under the License.

The Original Code is: SynEditStrConst.pas, released 2000-04-07.
The Original Code is based on mwLocalStr.pas by Michael Hieke, part of the
mwEdit component suite.
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

$Id: SynEditStrConst.pas,v 1.41.2.5 2009/01/06 16:26:01 maelh Exp $

You may retrieve the latest version of this file at the SynEdit home page,
located at http://SynEdit.SourceForge.net

Known Issues:
-------------------------------------------------------------------------------*/

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


// NOTE: this is design-time stuff, so no need to have it in stringtables
const System::WideChar SYNS_ComponentsPage[] = L"SynEdit";
const System::WideChar SYNS_HighlightersPage[] = L"SynEdit Highlighters";

// NOTE: the following constants are used to store information to the registry,
//       INI files or XML files. For maximum compatibility only the chars
//       'A'..'Z', 'a'..'z', '0'..'9', '_' and '-' are allowed!
//
//       If you want translated/"pretty"/more detailed descriptions use the
//       resourcestrings, i.e. the "friendly" versions below.

// constant names for highlighter attributes
//
//
const System::WideChar SYNS_AttrAreaAIdentifier[] = L"Area_A_Identifier";
const System::WideChar SYNS_AttrArrowHead[] = L"ArrowHead";
const System::WideChar SYNS_AttrAsm[] = L"Asm";
const System::WideChar SYNS_AttrAsmComment[] = L"AsmComment";
const System::WideChar SYNS_AttrAsmKey[] = L"AsmKey";
const System::WideChar SYNS_AttrAssembler[] = L"Assembler";
const System::WideChar SYNS_AttrAtRules[] = L"AtRules";
const System::WideChar SYNS_AttrAttribute[] = L"Attribute";
const System::WideChar SYNS_AttrAttributeName[] = L"AttributeName";
const System::WideChar SYNS_AttrAttributeValue[] = L"AttributeValue";
const System::WideChar SYNS_AttrBasicTypes[] = L"BasicTypes";
const System::WideChar SYNS_AttrBlock[] = L"Block";
const System::WideChar SYNS_AttrBoolean[] = L"Booleanvalue";
const System::WideChar SYNS_AttrBrackets[] = L"Brackets";
const System::WideChar SYNS_AttrCDATASection[] = L"CDATA-Section";
const System::WideChar SYNS_AttrCharacter[] = L"Character";
const System::WideChar SYNS_AttrClass[] = L"Class";
const System::WideChar SYNS_AttrColor[] = L"ColorValue";
const System::WideChar SYNS_AttrConstant[] = L"Constant";
const System::WideChar SYNS_AttrComment[] = L"Comment";
const System::WideChar SYNS_AttrCondition[] = L"Condition";
const System::WideChar SYNS_AttrConditionalComment[] = L"ConditionalComment";
const System::WideChar SYNS_AttrConsoleOutput[] = L"ConsoleOutput";
const System::WideChar SYNS_AttrDataType[] = L"DataType";
const System::WideChar SYNS_AttrDebugLines[] = L"DebuggingLines";
const System::WideChar SYNS_AttrDefaultPackage[] = L"DefaultPackages";
const System::WideChar SYNS_AttrDelimitedIdentifier[] = L"DelimitedIdentifier";
const System::WideChar SYNS_AttrDir[] = L"Direction";
const System::WideChar SYNS_AttrDirections[] = L"Directions";
const System::WideChar SYNS_AttrDirective[] = L"Directive";
const System::WideChar SYNS_AttrDOCTYPESection[] = L"DOCTYPE-Section";
const System::WideChar SYNS_AttrDocumentation[] = L"Documentation";
const System::WideChar SYNS_AttrElementName[] = L"ElementName";
const System::WideChar SYNS_AttrEmbedSQL[] = L"EmbeddedSQL";
const System::WideChar SYNS_AttrEmbedText[] = L"EmbeddedText";
const System::WideChar SYNS_AttrEntityReference[] = L"EntityReference";
const System::WideChar SYNS_AttrEscapeAmpersand[] = L"EscapeAmpersand";
const System::WideChar SYNS_AttrEvent[] = L"Event";
const System::WideChar SYNS_AttrException[] = L"Exception";
const System::WideChar SYNS_AttrFirstTri[] = L"FirstTri";
const System::WideChar SYNS_AttrFloat[] = L"Float";
const System::WideChar SYNS_AttrForm[] = L"Form";
const System::WideChar SYNS_AttrFourthTri[] = L"FourthTri";
const System::WideChar SYNS_AttrFunction[] = L"Function";
const System::WideChar SYNS_AttrHexadecimal[] = L"Hexadecimal";
const System::WideChar SYNS_AttrIcon[] = L"IconReference";
const System::WideChar SYNS_AttrIdentifier[] = L"Identifier";
const System::WideChar SYNS_AttrIllegalChar[] = L"IllegalChar";
const System::WideChar SYNS_AttrInclude[] = L"Include";
const System::WideChar SYNS_AttrIndicator[] = L"IndicatorArea";
const System::WideChar SYNS_AttrIndirect[] = L"Indirect";
const System::WideChar SYNS_AttrInstructions[] = L"Instructions";
const System::WideChar SYNS_AttrInvalidSymbol[] = L"InvalidSymbol";
const System::WideChar SYNS_AttrInternalFunction[] = L"InternalFunction";
const System::WideChar SYNS_AttrKey[] = L"Key";
const System::WideChar SYNS_AttrLabel[] = L"Label";
const System::WideChar SYNS_AttrLace[] = L"Lace";
const System::WideChar SYNS_AttrLine[] = L"Line";
const System::WideChar SYNS_AttrMacro[] = L"Macro";
const System::WideChar SYNS_AttrMarker[] = L"Marker";
const System::WideChar SYNS_AttrMathMode[] = L"MathMode";
const System::WideChar SYNS_AttrMessage[] = L"Message";
const System::WideChar SYNS_AttrMiscellaneous[] = L"Miscellaneous";
const System::WideChar SYNS_AttrNamespaceAttrName[] = L"NamespaceAttributeName";
const System::WideChar SYNS_AttrNamespaceAttrValue[] = L"NamespaceAttributeValue";
const System::WideChar SYNS_AttrNonReservedKeyword[] = L"NonreservedKeyword";
const System::WideChar SYNS_AttrNull[] = L"Null";
const System::WideChar SYNS_AttrNumber[] = L"Number";
const System::WideChar SYNS_AttrOctal[] = L"Octal";
const System::WideChar SYNS_AttrOperator[] = L"Operator";
const System::WideChar SYNS_AttrOperatorAndSymbols[] = L"OperatorAndSymbols";
const System::WideChar SYNS_AttrOpLine[] = L"OpLine";
const System::WideChar SYNS_AttrOptions[] = L"Options";
const System::WideChar SYNS_AttrPath[] = L"PathName";
const System::WideChar SYNS_AttrPLSQL[] = L"PLSQL-ReservedWord";
const System::WideChar SYNS_AttrPragma[] = L"Pragma";
const System::WideChar SYNS_AttrPredefined[] = L"Predefined";
const System::WideChar SYNS_AttrPreprocessor[] = L"Preprocessor";
const System::WideChar SYNS_AttrProcessingInstr[] = L"ProcessingInstruction";
const System::WideChar SYNS_AttrProcName[] = L"ProcName";
const System::WideChar SYNS_AttrProperty[] = L"Property";
const System::WideChar SYNS_AttrQuad[] = L"Quad";
const System::WideChar SYNS_AttrQualifier[] = L"Qualifier";
const System::WideChar SYNS_AttrRegister[] = L"Register";
const System::WideChar SYNS_AttrReservedWord[] = L"ReservedWord";
const System::WideChar SYNS_AttrResultValue[] = L"ResultValue";
const System::WideChar SYNS_AttrRoundBracket[] = L"RoundBracket";
const System::WideChar SYNS_AttrRpl[] = L"Rpl";
const System::WideChar SYNS_AttrRplKey[] = L"Rpl-Key";
const System::WideChar SYNS_AttrRplComment[] = L"Rpl-Comment";
const System::WideChar SYNS_AttrSASM[] = L"SASM";
const System::WideChar SYNS_AttrSASMComment[] = L"SASM-Comment";
const System::WideChar SYNS_AttrSASMKey[] = L"SASM-Key";
const System::WideChar SYNS_AttrSecondReservedWord[] = L"SecondReservedWord";
const System::WideChar SYNS_AttrSecondTri[] = L"SecondTri";
const System::WideChar SYNS_AttrSection[] = L"Section";
const System::WideChar SYNS_AttrSequence[] = L"SequenceNumberArea";
const System::WideChar SYNS_AttrShape[] = L"Shape";
const System::WideChar SYNS_AttrSingleString[] = L"SingleQuotedString";
const System::WideChar SYNS_AttrSpace[] = L"Space";
const System::WideChar SYNS_AttrSpecialVariable[] = L"SpecialVariable";
const System::WideChar SYNS_AttrSQLKey[] = L"SQL-Keyword";
const System::WideChar SYNS_AttrSQLPlus[] = L"SQLPlus-Command";
const System::WideChar SYNS_AttrSquareBracket[] = L"SquareBracket";
const System::WideChar SYNS_AttrString[] = L"String";
const System::WideChar SYNS_AttrSymbol[] = L"Symbol";
const System::WideChar SYNS_AttrSyntaxError[] = L"SyntaxError";
const System::WideChar SYNS_AttrSystem[] = L"SystemFunctionsAndVariables";
const System::WideChar SYNS_AttrSystemValue[] = L"SystemValue";
const System::WideChar SYNS_AttrTagArea[] = L"TagArea";
const System::WideChar SYNS_AttrTableName[] = L"TableName";
const System::WideChar SYNS_AttrTemplate[] = L"Template";
const System::WideChar SYNS_AttrTerminator[] = L"Terminator";
const System::WideChar SYNS_AttrTeXCommand[] = L"TeX-Command";
const System::WideChar SYNS_AttrText[] = L"Text";
const System::WideChar SYNS_AttrTextMathMode[] = L"TextInMathMode";
const System::WideChar SYNS_AttrThirdTri[] = L"ThirdTri";
const System::WideChar SYNS_AttrTixKeyWords[] = L"Tix-Keywords";
const System::WideChar SYNS_AttrTriangle[] = L"Triangle";
const System::WideChar SYNS_AttrUndefinedProperty[] = L"UndefinedProperty";
const System::WideChar SYNS_AttrUnknownWord[] = L"UnknownWord";
const System::WideChar SYNS_AttrURI[] = L"URI";
const System::WideChar SYNS_AttrUser[] = L"UserFunctionsAndVariables";
const System::WideChar SYNS_AttrUserFunction[] = L"UserFunctions";
const System::WideChar SYNS_AttrValue[] = L"Value";
const System::WideChar SYNS_AttrVariable[] = L"Variable";
const System::WideChar SYNS_AttrVisitedURI[] = L"VisitedURI";
const System::WideChar SYNS_AttrVrmlAppearance[] = L"Vrml_Appearance";
const System::WideChar SYNS_AttrVrmlAttribute[] = L"Vrml_Attribute";
const System::WideChar SYNS_AttrVrmlDefinition[] = L"Vrml_Definition";
const System::WideChar SYNS_AttrVrmlEvent[] = L"Vrml_Event";
const System::WideChar SYNS_AttrVrmlGrouping[] = L"Vrml_Grouping";
const System::WideChar SYNS_AttrVrmlInterpolator[] = L"Vrml_Interpolator";
const System::WideChar SYNS_AttrVrmlLight[] = L"Vrml_Light";
const System::WideChar SYNS_AttrVrmlNode[] = L"Vrml_Node";
const System::WideChar SYNS_AttrVrmlParameter[] = L"Vrml_Parameter";
const System::WideChar SYNS_AttrVrmlProto[] = L"Vrml_Proto";
const System::WideChar SYNS_AttrVrmlSensor[] = L"Vrml_Sensor";
const System::WideChar SYNS_AttrVrmlShape[] = L"Vrml_Shape";
const System::WideChar SYNS_AttrVrmlShape_Hint[] = L"Vrml_Shape_Hint";
const System::WideChar SYNS_AttrVrmlTime_dependent[] = L"Vrml_Time_dependent";
const System::WideChar SYNS_AttrVrmlViewpoint[] = L"Vrml_Viewpoint";
const System::WideChar SYNS_AttrVrmlWorldInfo[] = L"Vrml_WorldInfo";
const System::WideChar SYNS_AttrWhitespace[] = L"Whitespace";
const System::WideChar SYNS_AttrWidgetWords[] = L"Widget-Keywords";
const System::WideChar SYNS_AttrX3DDocType[] = L"X3DDocType";
const System::WideChar SYNS_AttrX3DHeader[] = L"X3DHeader";

  // constant language names
const System::WideChar SYNS_LangHP48[] = L"HP48";
const System::WideChar SYNS_LangCAClipper[] = L"CA-Clipper";
const System::WideChar SYNS_LangCPM[] = L"COAS_Product_Manager_Report";
const System::WideChar SYNS_LangCPP[] = L"CandCPlusPlus";
const System::WideChar SYNS_LangCS[] = L"CSharp";
const System::WideChar SYNS_LangJava[] = L"Java";
const System::WideChar SYNS_LangPerl[] = L"Perl";
const System::WideChar SYNS_LangBatch[] = L"MS-DOS_Batch";
const System::WideChar SYNS_LangDfm[] = L"BorlandForms";
const System::WideChar SYNS_LangAWK[] = L"AWK";
const System::WideChar SYNS_LangCORBAIDL[] = L"CORBA_IDL";
const System::WideChar SYNS_LangHTML[] = L"HTML";
const System::WideChar SYNS_LangVBSScript[] = L"MS-VBScript";
const System::WideChar SYNS_LangGalaxy[] = L"Galaxy";
const System::WideChar SYNS_LangGeneral[] = L"General";
const System::WideChar SYNS_LangPascal[] = L"ObjectPascal";
const System::WideChar SYNS_LangX86Asm[] = L"x86Assembly";
const System::WideChar SYNS_LangPython[] = L"Python";
const System::WideChar SYNS_LangTclTk[] = L"TclTk";
const System::WideChar SYNS_LangSQL[] = L"SQL";
const System::WideChar SYNS_LangGembase[] = L"Gembase";
const System::WideChar SYNS_LangINI[] = L"INI";
const System::WideChar SYNS_LangSML[] = L"StandardML";
const System::WideChar SYNS_LangVisualBASIC[] = L"VisualBasic";
const System::WideChar SYNS_LangADSP21xx[] = L"ADSP21xx";
const System::WideChar SYNS_LangPHP[] = L"PHP";
const System::WideChar SYNS_LangSybaseSQL[] = L"SybaseSQL";
const System::WideChar SYNS_LangGeneralMulti[] = L"General_Multi-Highlighter";
const System::WideChar SYNS_LangCache[] = L"CacheObjectScript";
const System::WideChar SYNS_LangCSS[] = L"CascadingStyleSheet";
const System::WideChar SYNS_LangJScript[] = L"JavaScript";
const System::WideChar SYNS_LangJSON[] = L"JSON";
const System::WideChar SYNS_LangKIX[] = L"KiXtart";
const System::WideChar SYNS_LangBaan[] = L"Baan_4GL";
const System::WideChar SYNS_LangFoxpro[] = L"Foxpro";
const System::WideChar SYNS_LangFortran[] = L"Fortran";
const System::WideChar SYNS_Lang68HC11[] = L"68HC11_Assembler";
const System::WideChar SYNS_LangProgress[] = L"Progress";
const System::WideChar SYNS_LangInno[] = L"InnoSetupScript";
const System::WideChar SYNS_LangModelica[] = L"Modelica";
const System::WideChar SYNS_LangModula3[] = L"Modula3";
const System::WideChar SYNS_LangSDD[] = L"SemantaDataDictionary";
const System::WideChar SYNS_LangXML[] = L"XML";
const System::WideChar SYNS_LangGWS[] = L"GW-TEL";
const System::WideChar SYNS_LangSynGenMsgfiles[] = L"SynGen_Msg";
const System::WideChar SYNS_LangUnreal[] = L"Unreal";
const System::WideChar SYNS_LangST[] = L"StructuredText";
const System::WideChar SYNS_LangCOBOL[] = L"COBOL";
const System::WideChar SYNS_LangTeX[] = L"TeX";
const System::WideChar SYNS_LangRC[] = L"Resource";
const System::WideChar SYNS_LangRuby[] = L"Ruby";
const System::WideChar SYNS_LangNameUNIXShellScript[] = L"UNIXShellScript";
const System::WideChar SYNS_LangHaskell[] = L"Haskell";
const System::WideChar SYNS_LangDOT[] = L"DOT_Graph_Drawing_Description_language";
const System::WideChar SYNS_LangEiffel[] = L"Eiffel";
const System::WideChar SYNS_LangLDraw[] = L"LEGO_LDraw";
const System::WideChar SYNS_LangLLVMIR[] = L"LLVM IR";
const System::WideChar SYNS_LangUnknown[] = L"<Unknown>";
const System::WideChar SYNS_LangURI[] = L"URI";
const System::WideChar SYNS_LangVrml97[] = L"Vrml97";
const System::Char SYNS_NoSearchEngineError[] = L"No search engine has been assigned";
const System::Char SYNS_Untitled[] = L"Untitled";

  // Friendly names for highlighter attributes
const System::Char SYNS_FriendlyAttrAreaAIdentifier[] = L"Area A Identifier";
const System::Char SYNS_FriendlyAttrArrowHead[] = L"ArrowHead";
const System::Char SYNS_FriendlyAttrAsm[] = L"Asm";
const System::Char SYNS_FriendlyAttrAsmComment[] = L"Asm Comment";
const System::Char SYNS_FriendlyAttrAsmKey[] = L"Asm Key";
const System::Char SYNS_FriendlyAttrAssembler[] = L"Assembler";
const System::Char SYNS_FriendlyAttrAtRules[] = L"@-Rules";
const System::Char SYNS_FriendlyAttrAttribute[] = L"Attribute";
const System::Char SYNS_FriendlyAttrAttributeName[] = L"Attribute Name";
const System::Char SYNS_FriendlyAttrAttributeValue[] = L"Attribute Value";
const System::Char SYNS_FriendlyAttrBasicTypes[] = L"Basic Types";
const System::Char SYNS_FriendlyAttrBlock[] = L"Block";
const System::Char SYNS_FriendlyAttrBoolean[] = L"Boolean value";
const System::Char SYNS_FriendlyAttrBrackets[] = L"Brackets";
const System::Char SYNS_FriendlyAttrCDATASection[] = L"CDATA Section";
const System::Char SYNS_FriendlyAttrCharacter[] = L"Character";
const System::Char SYNS_FriendlyAttrClass[] = L"Class";
const System::Char SYNS_FriendlyAttrColor[] = L"Color Value";
const System::Char SYNS_FriendlyAttrComment[] = L"Comment";
const System::Char SYNS_FriendlyAttrCondition[] = L"Condition";
const System::Char SYNS_FriendlyAttrConditionalComment[] = L"Conditional Comment";
const System::Char SYNS_FriendlyAttrConsoleOutput[] = L"Console output";
const System::Char SYNS_FriendlyAttrConstant[] = L"Constant";
const System::Char SYNS_FriendlyAttrDataType[] = L"Data Type";
const System::Char SYNS_FriendlyAttrDebugLines[] = L"Debugging Lines";
const System::Char SYNS_FriendlyAttrDefaultPackage[] = L"Default Packages";
const System::Char SYNS_FriendlyAttrDelimitedIdentifier[] = L"Delimited Identifier";
const System::Char SYNS_FriendlyAttrDir[] = L"Direction";
const System::Char SYNS_FriendlyAttrDirections[] = L"Directions";
const System::Char SYNS_FriendlyAttrDirective[] = L"Directive";
const System::Char SYNS_FriendlyAttrDOCTYPESection[] = L"DOCTYPE Section";
const System::Char SYNS_FriendlyAttrDocumentation[] = L"Documentation";
const System::Char SYNS_FriendlyAttrElementName[] = L"Element Name";
const System::Char SYNS_FriendlyAttrEmbedSQL[] = L"Embedded SQL";
const System::Char SYNS_FriendlyAttrEmbedText[] = L"Embedded Text";
const System::Char SYNS_FriendlyAttrEntityReference[] = L"Entity Reference";
const System::Char SYNS_FriendlyAttrEscapeAmpersand[] = L"Escape Ampersand";
const System::Char SYNS_FriendlyAttrEvent[] = L"Event";
const System::Char SYNS_FriendlyAttrException[] = L"Exception";
const System::Char SYNS_FriendlyAttrFirstTri[] = L"FirstTri";
const System::Char SYNS_FriendlyAttrFloat[] = L"Float";
const System::Char SYNS_FriendlyAttrForm[] = L"Form";
const System::Char SYNS_FriendlyAttrFourthTri[] = L"FourthTri";
const System::Char SYNS_FriendlyAttrFunction[] = L"Function";
const System::Char SYNS_FriendlyAttrHexadecimal[] = L"Hexadecimal";
const System::Char SYNS_FriendlyAttrIcon[] = L"Icon Reference";
const System::Char SYNS_FriendlyAttrIdentifier[] = L"Identifier";
const System::Char SYNS_FriendlyAttrIllegalChar[] = L"Illegal Char";
const System::Char SYNS_FriendlyAttrInclude[] = L"Include";
const System::Char SYNS_FriendlyAttrIndicator[] = L"Indicator Area";
const System::Char SYNS_FriendlyAttrIndirect[] = L"Indirect";
const System::Char SYNS_FriendlyAttrInstructions[] = L"Instructions";
const System::Char SYNS_FriendlyAttrInternalFunction[] = L"Internal Function";
const System::Char SYNS_FriendlyAttrInvalidSymbol[] = L"Invalid Symbol";
const System::Char SYNS_FriendlyAttrKey[] = L"Key";
const System::Char SYNS_FriendlyAttrLabel[] = L"Label";
const System::Char SYNS_FriendlyAttrLace[] = L"Lace";
const System::Char SYNS_FriendlyAttrLine[] = L"Line";
const System::Char SYNS_FriendlyAttrMacro[] = L"Macro";
const System::Char SYNS_FriendlyAttrMarker[] = L"Marker";
const System::Char SYNS_FriendlyAttrMathMode[] = L"Math Mode";
const System::Char SYNS_FriendlyAttrMessage[] = L"Message";
const System::Char SYNS_FriendlyAttrMiscellaneous[] = L"Miscellaneous";
const System::Char SYNS_FriendlyAttrNamespaceAttrName[] = L"Namespace Attribute Name";
const System::Char SYNS_FriendlyAttrNamespaceAttrValue[] = L"Namespace Attribute Value";
const System::Char SYNS_FriendlyAttrNonReservedKeyword[] = L"Non-reserved Keyword";
const System::Char SYNS_FriendlyAttrNull[] = L"Null";
const System::Char SYNS_FriendlyAttrNumber[] = L"Number";
const System::Char SYNS_FriendlyAttrOctal[] = L"Octal";
const System::Char SYNS_FriendlyAttrOperator[] = L"Operator";
const System::Char SYNS_FriendlyAttrOperatorAndSymbols[] = L"Operator And Symbols";
const System::Char SYNS_FriendlyAttrOpLine[] = L"OpLine";
const System::Char SYNS_FriendlyAttrOptions[] = L"Options";
const System::Char SYNS_FriendlyAttrPath[] = L"Pathname";
const System::Char SYNS_FriendlyAttrPLSQL[] = L"PL/SQL Reserved Word";
const System::Char SYNS_FriendlyAttrPragma[] = L"Pragma";
const System::Char SYNS_FriendlyAttrPredefined[] = L"Predefined";
const System::Char SYNS_FriendlyAttrPreprocessor[] = L"Preprocessor";
const System::Char SYNS_FriendlyAttrProcessingInstr[] = L"Processing Instruction";
const System::Char SYNS_FriendlyAttrProcName[] = L"Procedure name";
const System::Char SYNS_FriendlyAttrProperty[] = L"Property";
const System::Char SYNS_FriendlyAttrQuad[] = L"Quad";
const System::Char SYNS_FriendlyAttrQualifier[] = L"Qualifier";
const System::Char SYNS_FriendlyAttrRegister[] = L"Register";
const System::Char SYNS_FriendlyAttrReservedWord[] = L"Reserved Word";
const System::Char SYNS_FriendlyAttrResultValue[] = L"Result Value";
const System::Char SYNS_FriendlyAttrRoundBracket[] = L"Round Bracket";
const System::Char SYNS_FriendlyAttrRpl[] = L"Rpl";
const System::Char SYNS_FriendlyAttrRplKey[] = L"Rpl Key";
const System::Char SYNS_FriendlyAttrRplComment[] = L"Rpl Comment";
const System::Char SYNS_FriendlyAttrSASM[] = L"SASM";
const System::Char SYNS_FriendlyAttrSASMComment[] = L"SASM Comment";
const System::Char SYNS_FriendlyAttrSASMKey[] = L"SASM Key";
const System::Char SYNS_FriendlyAttrSecondReservedWord[] = L"Second Reserved Word";
const System::Char SYNS_FriendlyAttrSecondTri[] = L"SecondTri";
const System::Char SYNS_FriendlyAttrSection[] = L"Section";
const System::Char SYNS_FriendlyAttrSequence[] = L"Sequence Number Area";
const System::Char SYNS_FriendlyAttrShape[] = L"Shape";
const System::Char SYNS_FriendlyAttrSingleString[] = L"Single Quoted String";
const System::Char SYNS_FriendlyAttrSpace[] = L"Space";
const System::Char SYNS_FriendlyAttrSpecialVariable[] = L"Special Variable";
const System::Char SYNS_FriendlyAttrSQLKey[] = L"SQL Keyword";
const System::Char SYNS_FriendlyAttrSQLPlus[] = L"SQL*Plus Command";
const System::Char SYNS_FriendlyAttrSquareBracket[] = L"Square Bracket";
const System::Char SYNS_FriendlyAttrString[] = L"String";
const System::Char SYNS_FriendlyAttrSymbol[] = L"Symbol";
const System::Char SYNS_FriendlyAttrSyntaxError[] = L"Syntax Error";
const System::Char SYNS_FriendlyAttrSystem[] = L"System Functions and Variables";
const System::Char SYNS_FriendlyAttrSystemValue[] = L"System Value";
const System::Char SYNS_FriendlyAttrTagArea[] = L"Tag Area";
const System::Char SYNS_FriendlyAttrTableName[] = L"Table Name";
const System::Char SYNS_FriendlyAttrTemplate[] = L"Template";
const System::Char SYNS_FriendlyAttrTerminator[] = L"Terminator";
const System::Char SYNS_FriendlyAttrTeXCommand[] = L"TeX Command";
const System::Char SYNS_FriendlyAttrText[] = L"Text";
const System::Char SYNS_FriendlyAttrTextMathMode[] = L"Text in Math Mode";
const System::Char SYNS_FriendlyAttrThirdTri[] = L"ThirdTri";
const System::Char SYNS_FriendlyAttrTixKeyWords[] = L"Tix Keywords";
const System::Char SYNS_FriendlyAttrTriangle[] = L"Triangle";
const System::Char SYNS_FriendlyAttrUndefinedProperty[] = L"Undefined Property";
const System::Char SYNS_FriendlyAttrUnknownWord[] = L"Unknown Word";
const System::Char SYNS_FriendlyAttrURI[] = L"URI";
const System::Char SYNS_FriendlyAttrUser[] = L"User Functions and Variables";
const System::Char SYNS_FriendlyAttrUserFunction[] = L"User Functions";
const System::Char SYNS_FriendlyAttrValue[] = L"Value";
const System::Char SYNS_FriendlyAttrVariable[] = L"Variable";
const System::Char SYNS_FriendlyAttrVisitedURI[] = L"Visited URI";
const System::Char SYNS_FriendlyAttrVrmlAppearance[] = L"Vrml_Appearance";
const System::Char SYNS_FriendlyAttrVrmlAttribute[] = L"Vrml_Attribute";
const System::Char SYNS_FriendlyAttrVrmlDefinition[] = L"Vrml_Definition";
const System::Char SYNS_FriendlyAttrVrmlEvent[] = L"Vrml_Event";
const System::Char SYNS_FriendlyAttrVrmlGrouping[] = L"Vrml_Grouping";
const System::Char SYNS_FriendlyAttrVrmlInterpolator[] = L"Vrml_Interpolator";
const System::Char SYNS_FriendlyAttrVrmlLight[] = L"Vrml_Light";
const System::Char SYNS_FriendlyAttrVrmlNode[] = L"Vrml_Node";
const System::Char SYNS_FriendlyAttrVrmlParameter[] = L"Vrml_Parameter";
const System::Char SYNS_FriendlyAttrVrmlProto[] = L"Vrml_Proto";
const System::Char SYNS_FriendlyAttrVrmlSensor[] = L"Vrml_Sensor";
const System::Char SYNS_FriendlyAttrVrmlShape[] = L"Vrml_Shape";
const System::Char SYNS_FriendlyAttrVrmlShape_Hint[] = L"Vrml_Shape_Hint";
const System::Char SYNS_FriendlyAttrVrmlTime_dependent[] = L"Vrml_Time_dependent";
const System::Char SYNS_FriendlyAttrVrmlViewpoint[] = L"Vrml_Viewpoint";
const System::Char SYNS_FriendlyAttrVrmlWorldInfo[] = L"Vrml_WorldInfo";
const System::Char SYNS_FriendlyAttrWhitespace[] = L"Whitespace";
const System::Char SYNS_FriendlyAttrWidgetWords[] = L"Widget Keywords";
const System::Char SYNS_FriendlyAttrX3DDocType[] = L"X3DDocType";
const System::Char SYNS_FriendlyAttrX3DHeader[] = L"X3DHeader";

  // names of exporter output formats
const System::Char SYNS_ExporterFormatHTML[] = L"HTML";
const System::Char SYNS_ExporterFormatRTF[] = L"RTF";
const System::Char SYNS_ExporterFormatTeX[] = L"TeX";

  // TCustomSynEdit scroll hint window caption
const System::Char SYNS_ScrollInfoFmt[] = L"%d - %d";
const System::Char SYNS_ScrollInfoFmtTop[] = L"Top Line: %d";
  // TSynEditPrintPreview page number
const System::Char SYNS_PreviewScrollInfoFmt[] = L"Page: %d";

  // strings for property editors etc
const System::Char SYNS_EDuplicateShortcut[] = L"Shortcut already exists";
const System::Char SYNS_ShortcutNone[] = L"<none>";
const System::Char SYNS_DuplicateShortcutMsg[] = L"The keystroke \"%s\" is already assigned to another editor command. (%s)";
const System::Char SYNS_DuplicateShortcutMsg2[] = L"The keystroke \"%s\" is already assigned to another editor command.\x0d\x0a" L"The shortcut for this item has not been changed.";

  // Filters used for open/save dialog
const System::Char SYNS_FilterPascal[] = L"Pascal Files (*.pas;*.pp;*.dpr;*.dpk;*.inc)|*.pas;*.pp;*.dpr;*.dpk;*.inc";
const System::Char SYNS_FilterHP48[] = L"HP48 Files (*.s;*.sou;*.a;*.hp)|*.s;*.sou;*.a;*.hp";
const System::Char SYNS_FilterCAClipper[] = L"CA-Clipper Files (*.prg;*.ch;*.inc)|*.prg;*.ch;*.inc";
const System::Char SYNS_FilterCORBAIDL[] = L"CORBA IDL Files (*.idl)|*.idl";
const System::Char SYNS_FilterCPM[] = L"CPM Reports (*.rdf;*.rif;*.rmf;*.rxf)|*.rdf;*.rif;*.rmf;*.rxf";
const System::Char SYNS_FilterCPP[] = L"C/C++ Files (*.c;*.cpp;*.cc;*.h;*.hpp;*.hh;*.cxx;*.hxx;*.cu)|*.c;*.cpp;*.cc;*.h;*.hpp;*.hh;*.cxx;*.hxx;*.cu";
const System::Char SYNS_FilterCS[] = L"C# Files (*.cs)|*.cs";
const System::Char SYNS_FilterDWS[] = L"DWScript Files (*.dws;*.pas;*.inc)|*.dws;*.pas;*.inc";
const System::Char SYNS_FilterJava[] = L"Java Files (*.java)|*.java";
const System::Char SYNS_FilterPerl[] = L"Perl Files (*.pl;*.pm;*.cgi)|*.pl;*.pm;*.cgi";
const System::Char SYNS_FilterAWK[] = L"AWK Scripts (*.awk)|*.awk";
const System::Char SYNS_FilterHTML[] = L"HTML Documents (*.htm;*.html)|*.htm;*.html";
const System::Char SYNS_FilterVBScript[] = L"VBScript Files (*.vbs)|*.vbs";
const System::Char SYNS_FilterGalaxy[] = L"Galaxy Files (*.gtv;*.galrep;*.txt)|*.gtv;*.galrep;*.txt";
const System::Char SYNS_FilterPython[] = L"Python Files (*.py)|*.py";
const System::Char SYNS_FilterSQL[] = L"SQL Files (*.sql)|*.sql";
const System::Char SYNS_FilterTclTk[] = L"Tcl/Tk Files (*.tcl)|*.tcl";
const System::Char SYNS_FilterRTF[] = L"Rich Text Format Documents (*.rtf)|*.rtf";
const System::Char SYNS_FilterBatch[] = L"MS-DOS Batch Files (*.bat;*.cmd)|*.bat;*.cmd";
const System::Char SYNS_FilterDFM[] = L"Borland Form Files (*.dfm;*.xfm)|*.dfm;*.xfm";
const System::Char SYNS_FilterX86Assembly[] = L"x86 Assembly Files (*.asm)|*.asm";
const System::Char SYNS_FilterGembase[] = L"GEMBASE Files (*.dml;*.gem)|*.dml;*.gem";
const System::Char SYNS_FilterINI[] = L"INI Files (*.ini)|*.ini";
const System::Char SYNS_FilterSML[] = L"Standard ML Files (*.sml)|*.sml";
const System::Char SYNS_FilterVisualBASIC[] = L"Visual Basic Files (*.bas)|*.bas";
const System::Char SYNS_FilterADSP21xx[] = L"DSP Files (*.dsp;*.inc)|*.dsp;*.inc";
const System::Char SYNS_FilterPHP[] = L"PHP Files (*.php;*.php3;*.phtml;*.inc)|*.php;*.php3;*.phtml;*.inc";
const System::Char SYNS_FilterCache[] = L"Cache Files (*.mac;*.inc;*.int)|*.mac;*.inc;*.int";
const System::Char SYNS_FilterCSS[] = L"Cascading Stylesheets (*.css)|*.css";
const System::Char SYNS_FilterJScript[] = L"Javascript Files (*.js)|*.js";
const System::Char SYNS_FilterJSON[] = L"JSON Files (*.json)|*.json";
const System::Char SYNS_FilterKIX[] = L"KiXtart Scripts (*.kix)|*.kix";
const System::Char SYNS_FilterBaan[] = L"Baan 4GL Files (*.cln)|*.cln";
const System::Char SYNS_FilterFoxpro[] = L"Foxpro Files (*.prg)|*.prg";
const System::Char SYNS_FilterFortran[] = L"Fortran Files (*.for)|*.for";
const System::Char SYNS_FilterAsm68HC11[] = L"68HC11 Assembler Files (*.hc11;*.asm;*.asc)|*.hc11;*.asm;*.asc";
const System::Char SYNS_FilterProgress[] = L"Progress Files (*.w;*.p;*.i)|*.w;*.p;*.i";
const System::Char SYNS_FilterInno[] = L"Inno Setup Scripts (*.iss)|*.iss";
const System::Char SYNS_FilterModelica[] = L"Modelica Files (*.mo)|*.mo";
const System::Char SYNS_FilterModula3[] = L"Modula-3 Files (*.m3)|*.m3";
const System::Char SYNS_FilterSDD[] = L"Semanta DD Files (*.sdd)|*.sdd";
const System::Char SYNS_FilterXML[] = L"XML Files (*.xml;*.xsd;*.xsl;*.xslt;*.dtd)|*.xml;*.xsd;*.xsl;*.xslt;*.dtd";
const System::Char SYNS_FilterGWS[] = L"GW-TEL Scripts (*.gws)|*.gws";
const System::Char SYNS_FilterSynGenMsgfiles[] = L"Msg Files (*.msg)|*.msg";
const System::Char SYNS_FilterST[] = L"Structured Text Files (*.st)|*.st";
const System::Char SYNS_FilterCOBOL[] = L"COBOL Files (*.cbl;*.cob)|*.cbl;*.cob";
const System::Char SYNS_FilterTeX[] = L"TeX Files (*.tex)|*.tex";
const System::Char SYNS_FilterRC[] = L"Resource Files (*.rc)|*.rc";
const System::Char SYNS_FilterRuby[] = L"Ruby Files (*.rb;*.rbw)|*.rb;*.rbw";
const System::Char SYNS_FilterUNIXShellScript[] = L"UNIX Shell Scripts (*.sh)|*.sh";
const System::Char SYNS_FilterHaskell[] = L"Haskell Files (*.hs;*.lhs)|*.hs;*.lhs";
const System::Char SYNS_FilterDOT[] = L"DOT Graph Drawing Description (*.dot)|*.dot";
const System::Char SYNS_FilterEiffel[] = L"Eiffel (*.e;*.ace)|*.e;*.ace";
const System::Char SYNS_FilterLDraw[] = L"LEGO LDraw Files (*.ldr)|*.ldr";
const System::Char SYNS_FilterLLVMIR[] = L"LLVM IR files (*.ll)|*.ll";
const System::Char SYNS_FilterURI[] = L"All Files (*.*)|*.*";
const System::Char SYNS_FilterVrml97[] = L"Vrml97/X3D World (*.wrl;*.wrml;*.vrl;*.vrml;*.x3d)|*.wrl;*.wrml;*.vrl;*.vrml;*.x3d";

  // friendly language names
const System::Char SYNS_FriendlyLangHP48[] = L"HP48";
const System::Char SYNS_FriendlyLangCAClipper[] = L"CA-Clipper";
const System::Char SYNS_FriendlyLangCPM[] = L"COAS Product Manager Report";
const System::Char SYNS_FriendlyLangCPP[] = L"C/C++";
const System::Char SYNS_FriendlyLangCS[] = L"C#";
const System::Char SYNS_FriendlyLangJava[] = L"Java";
const System::Char SYNS_FriendlyLangPerl[] = L"Perl";
const System::Char SYNS_FriendlyLangBatch[] = L"MS-DOS Batch";
const System::Char SYNS_FriendlyLangDfm[] = L"Borland Forms";
const System::Char SYNS_FriendlyLangAWK[] = L"AWK";
const System::Char SYNS_FriendlyLangCORBAIDL[] = L"CORBA IDL";
const System::Char SYNS_FriendlyLangHTML[] = L"HTML";
const System::Char SYNS_FriendlyLangVBSScript[] = L"MS VBScript";
const System::Char SYNS_FriendlyLangGalaxy[] = L"Galaxy";
const System::Char SYNS_FriendlyLangGeneral[] = L"General";
const System::Char SYNS_FriendlyLangPascal[] = L"Object Pascal";
const System::Char SYNS_FriendlyLangX86Asm[] = L"x86 Assembly";
const System::Char SYNS_FriendlyLangPython[] = L"Python";
const System::Char SYNS_FriendlyLangTclTk[] = L"Tcl/Tk";
const System::Char SYNS_FriendlyLangSQL[] = L"SQL";
const System::Char SYNS_FriendlyLangGembase[] = L"Gembase";
const System::Char SYNS_FriendlyLangINI[] = L"INI";
const System::Char SYNS_FriendlyLangSML[] = L"Standard ML";
const System::Char SYNS_FriendlyLangVisualBASIC[] = L"Visual Basic";
const System::Char SYNS_FriendlyLangADSP21xx[] = L"ADSP21xx";
const System::Char SYNS_FriendlyLangPHP[] = L"PHP";
const System::Char SYNS_FriendlyLangSybaseSQL[] = L"Sybase SQL";
const System::Char SYNS_FriendlyLangGeneralMulti[] = L"General Multi-Highlighter";
const System::Char SYNS_FriendlyLangCache[] = L"Cache Object Script";
const System::Char SYNS_FriendlyLangCSS[] = L"Cascading Style Sheet";
const System::Char SYNS_FriendlyLangJScript[] = L"JavaScript";
const System::Char SYNS_FriendlyLangJSON[] = L"JSON";
const System::Char SYNS_FriendlyLangKIX[] = L"KiXtart";
const System::Char SYNS_FriendlyLangBaan[] = L"Baan 4GL";
const System::Char SYNS_FriendlyLangFoxpro[] = L"Foxpro";
const System::Char SYNS_FriendlyLangFortran[] = L"Fortran";
const System::Char SYNS_FriendlyLang68HC11[] = L"68HC11 Assembler";
const System::Char SYNS_FriendlyLangProgress[] = L"Progress";
const System::Char SYNS_FriendlyLangInno[] = L"Inno Setup Script";
const System::Char SYNS_FriendlyLangModelica[] = L"Modelica";
const System::Char SYNS_FriendlyLangModula3[] = L"Modula 3";
const System::Char SYNS_FriendlyLangSDD[] = L"Semanta Data Dictionary";
const System::Char SYNS_FriendlyLangXML[] = L"XML";
const System::Char SYNS_FriendlyLangGWS[] = L"GW-TEL";
const System::Char SYNS_FriendlyLangSynGenMsgfiles[] = L"SynGen Msg";
const System::Char SYNS_FriendlyLangUnreal[] = L"Unreal";
const System::Char SYNS_FriendlyLangST[] = L"Structured Text";
const System::Char SYNS_FriendlyLangCOBOL[] = L"COBOL";
const System::Char SYNS_FriendlyLangTeX[] = L"TeX";
const System::Char SYNS_FriendlyLangRC[] = L"Resource";
const System::Char SYNS_FriendlyLangRuby[] = L"Ruby";
const System::Char SYNS_FriendlyLangNameUNIXShellScript[] = L"UNIX Shell Script";
const System::Char SYNS_FriendlyLangHaskell[] = L"Haskell";
const System::Char SYNS_FriendlyLangDOT[] = L"DOT Graph Drawing Description language";
const System::Char SYNS_FriendlyLangEiffel[] = L"Eiffel";
const System::Char SYNS_FriendlyLangLDraw[] = L"LEGO LDraw";
const System::Char SYNS_FriendlyLangLLVMIR[] = L"LLVM Intermediate Representation";
const System::Char SYNS_FriendlyLangUnknown[] = L"<Unknown>";
const System::Char SYNS_FriendlyLangURI[] = L"URI";
const System::Char SYNS_FriendlyLangVrml97[] = L"Vrml97";


}  // namespace SynEditStrConst

#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE)
using namespace Syneditstrconst;
#endif

#endif // SynEditStrConstH

