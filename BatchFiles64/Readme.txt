

Synedit
-------

The Delphi source files are converted using UpdateSynedit64.bat. This batch file performs several tasks.

First, it calls Delphi2Cpp to generate the C++ files in the SourceCppRaw64 folder.

TestCpp64 contains a C++Builder project that is used to test the compilation of these generated files. However, the project does not use the files directly from SourceCppRaw64. Instead, it uses the files from the SourceCppRun64 folder.

SourceCppRun64 initially contains the same files as SourceCppRaw64, but some of them are manually corrected afterward. These manually modified files are stored in the SourceCppReworked64 folder.

UpdateSynedit64_dme.bat ensures that only those files in SourceCppRun64 are overwritten that have not been manually modified before.

If changes are made either to the original Delphi source files or to Delphi2Cpp itself, those changes must be manually merged into the files that were previously corrected by hand.


Demos
-----

The following batch files:

CompletionProposalDemoCb.bat
EditAppDemosCb.bat
FoldingCb.bat
SearchReplaceDemoCb.bat

directly write the translated files for the corresponding demos back into the original source directories.

As a result, the small number of required manual modifications must be applied again after each translation run to ensure that the corresponding C++Builder projects continue to compile and work correctly.

The C++Builder projects use the original DFM files from the Delphi projects.



SynGen
------

SynGen.bat converts the Delphi source code from the SynGen directory into C++ files and writes them to the SynGenCppRaw directory.

The files that are actually used by the C++Builder project SynGen.cbproj, as well as the project file itself, are located in the SynGenCppRun directory.

A merge tool such as WinMerge can be used to easily compare and merge the contents of these directories.

While the other demo projects reuse the original DFM files from the Delphi projects, the SynGen code is transformed into an application that works entirely without a DFM file. This is done purely for demonstration purposes.

Avoiding the use of a DFM file makes the application easier to build on other systems.


