# Translation and modification history

SynEditCb is a C++ translation and adaptation of the Delphi SynEdit and SynGen
sources supplied in `Source` and `SynGen`. SynEdit is derived from mwEdit,
originally developed by Martin Waldenburg. Individual file notices identify
additional initial developers, authors and contributors; see also
`Source/Contributors.txt`. The translation was performed using Delphi2Cpp /
Delphi2CB, followed by manual corrections for C++Builder.

## 2026-10-08: license documentation cleanup

- Repeated existing license/copyright prologues immediately after `implementation`
  in 115 original Pascal units in `Source` and `SynGen`, so the implementation
  translator can retain these comments in regenerated C++ implementation files.
  Only trailing whitespace in the repeated comments was removed. Original
  prologues, file encodings and program logic were retained. No notices were
  invented for `SynSpellCheckMetaphone.pas` or `HashTableGen.pas`, which have no
  existing license/copyright prologue. Translator output still needs validation
  with the configured Delphi2CB version before replacing generated files.
- Added the unmodified official MPL 1.1 text in `licenses/MPL-1.1.txt`.
- Retained the historical license texts in `LICENSE` and clarified their scope.
- Restored existing companion-header license and copyright comments in 219
  translated C++ implementation files across `SourceCpp*` and `SynGenCpp*`.
  Original alternatives and author notices were preserved; no new license was
  assigned to code with unresolved permissions. Program logic was not changed.
- Added `LICENSES.md`, `LEGAL` and the README license/provenance section.
- Exported the available dated repository history below so that source archives
  carry a record of translations and subsequent changes.

## Release milestones recorded in README

- February 2022: original RAD Studio 11 Alexandria release.
- August 2024: RAD Studio 12 Athens update and modern 64-bit compiler projects.
- May 2026: RAD Studio 13 Florence update; 32-bit projects removed.

These are month-level release dates; exact original translation dates are not
established here. Entries below reproduce commit dates and descriptions. They
are historical records, not a claim that every change happened on its commit
date or that every imported file's earlier history is complete.

## Available repository history through 2026-10-08

- 2022-02-02 (b81e16d): Initial commit
- 2022-02-02 (6b6eb6a): Backups and Temporary section added to gitignore
- 2022-02-02 (61a9f2a): Same License as original SynEdit
- 2022-02-06 (2124938): code added
- 2022-02-20 (61d337a): Changes due to Delphi2CB improvements, e.g. not inc-file for units with one class only
- 2024-08-09 (f4fb279): Batch files updated for C++Builder 23.0
- 2024-08-09 (fafc25a): Re-translation
- 2024-08-09 (fda09e3): DemosCb for C++Builder 23.0
- 2024-08-10 (646dbc4): demos in DemosCb recreated with Delphi2Cpp/Delphi2CB 2.4.0
- 2024-08-13 (309bad0): projects for the modern compiler added
- 2024-08-13 (8ea32c2): formatting of folder table
- 2024-08-13 (ff9bf58): folder table formatting
- 2024-08-13 (0fe007d): folder table formatting
- 2024-08-13 (82a5b05): Readme.md formatting
- 2024-08-13 (570ebd3): cModernCBuilder in BatchFiles64/Synedit.prj
- 2024-08-14 (ad7ae0c): 32 bit CREATEINITEXITORDERFILE =true
- 2024-08-14 (88f2c56): ignore DebugDebug
- 2024-08-14 (5fc6737): compined Identifier files
- 2024-08-14 (3e688af): SynEditIdents for 64 bit Synedit.prj
- 2024-08-14 (51dbede): sLinebreak -> sLineBreak
- 2024-08-16 (30adad4): bug fixes
- 2024-08-16 (d8f5f2c): on closing application
- 2024-08-21 (f85b3ae): (TColor) cast in 64 bit code
- 2024-08-21 (28ecd47): update 32 bit code
- 2024-08-22 (cd7eb00): Delegated constructor
- 2024-08-23 (28064d4): casts on procedural types
- 2024-09-17 (a667b1f): buf fix to quotes
- 2024-10-16 (e56ac6f): identifiers fron declaration for 64 bit code
- 2024-10-16 (ff02ff7): forgotten
- 2024-10-20 (1d87ace): SynEditIdents.txt adapted
- 2024-10-24 (5a9b516): SourceCpp 32 bit identifiers updated
- 2024-10-24 (11ac8ba): 32 bit batch filés and EditAppDemo updated
- 2024-10-25 (4bae7ba): demos updated
- 2024-10-25 (8e1505a): ignore Win32 folders
- 2024-10-27 (c95c375): 64 bit batch files for demos corrected
- 2024-10-27 (128cca0): 64 bit demos compiling
- 2024-10-27 (7b01bb2): DemoCb updated
- 2024-12-06 (2b68e7c): Bug fixes for the C++Builder Athens Patch
- 2024-12-06 (0d46221): 32 bit modern compiler code updated
- 2024-12-06 (2052eb9): forgotten file
- 2026-05-18 (2058acb): Removed 32-bit code
- 2026-05-18 (4b2057c): Updated to Delphi2CB 2.7.0
- 2026-07-23 (132153c): minor changes resulting from a restructuring in Delphi2CB
- 2026-08-03 (e0e5d4f): using Studio\37.0\source\ with Delphi2CB 2.8.0
- 2026-08-05 (a841abc): bug fix to Low/High type
- 2026-09-09 (ea8e131): d2c_sysfile copyright
- 2026-10-08 (4c4dd53): four bug fixes 1. missing return value in RemovedKeystroke 2. wrong search pattern in TSynEditSearch::SetPattern 3. missing throw in TSynEditStringList::SetCapacity 4. Memory leak when deleting lines of text in SynEditTextBuffer
