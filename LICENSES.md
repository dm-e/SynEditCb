# License and provenance overview

This repository contains components with different licenses. The presence of a
license text in `LICENSE` does not license every file under that license. The
notices of each original file govern that file and its translated derivatives.
This overview does not replace those notices or grant rights held by third parties.

## SynEdit and SynGen

`Source` and `SynGen` contain the original Delphi sources. The corresponding
`SourceCpp*` and `SynGenCpp*` directories contain translations and adaptations.
SynEdit derives from the mwEdit project started by Martin Waldenburg. Additional
original authors and contributors are identified in the individual files and
`Source/Contributors.txt`.

Most of these files offer a choice of MPL 1.1 or GPL version 2 or later. Some
files, including SynUsp10, have different alternatives; consult their notices.
The C++ translation does not remove the original license obligations.

The complete MPL 1.1 text is in `licenses/MPL-1.1.txt`. The existing `LICENSE`
also contains Apache 1.1, GPL 2 and historical MPL 1.0 texts. MPL 1.0 is not a
substitute for MPL 1.1. No blanket Apache license is asserted for this repository.

Changes and their recorded dates are documented in `CHANGES.md`. Preserve that
file, this overview, the applicable license texts and original notices when
redistributing sources. Source archives should include the referenced files.
When distributing executables containing MPL-covered code, include the required
notice explaining how recipients can obtain the corresponding covered source
under its applicable license. Retain source availability for the required period.

## Delphi2Cpp / Delphi2CB support files

`d2c_cb` contains support code with file-specific terms. Files such as
`d2c_system.h` permit use without restriction in projects generated with
Delphi2Cpp or Delphi2CB. This wording is not a general-purpose open-source license
for arbitrary unrelated projects and is not extended by this overview.

`d2c_sysfile.h` and `d2c_sysfile.cpp` identify portions derived from the Free
Pascal 2.2.4 runtime library and are licensed under LGPL 2.1 or later with the
independent-modules exception. See `d2c_cb/COPYING` and `d2c_cb/COPYING.FPC`.
The exception concerns linking independent modules; it does not remove the
obligations for redistribution or modification of the library itself.
`BatchFiles64/System.pas` also contains Free Pascal provenance and license terms.
Consult each file before reusing or distributing it.

## Unresolved provenance and permissions

See `LEGAL` for unresolved permissions concerning SynSpellCheck and related
algorithms. These files are not assigned a new license by this overview.
The notices for code do not establish the rights to every image, icon, resource,
dictionary or external dependency. Preserve their provenance and verify the
applicable terms before distributing them separately or in release packages.

## References

- MPL 1.1: https://www.mozilla.org/en-US/MPL/1.1/
- SynEdit upstream: https://github.com/SynEdit/SynEdit
- Free Pascal licensing: https://www.freepascal.org/faq.html

Review date: 2026-10-08. This document records the repository's notices and known
gaps; it is not a certification that all third-party rights have been cleared.
