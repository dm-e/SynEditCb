
SynEditCb is a C++ version of the Delphi SynEdit components for C++Builder. SynEdit is a widely used open-source editor component suite with syntax highlighting support. The original project is hosted on GitHub.

The C++ code provided here is based on the Delphi sources that were available when the components were installed via GetIt in RAD Studio 11 Alexandria. The current SynEdit sources may be converted in the future, but for now the older code base is still used to demonstrate the development and capabilities of Delphi2CB, the tool that was used for the translation.

You may download:

v1.0 — Original release matching the video presentation

The current update was generated using Delphi2CB 2.7.0.

While the previous release still supported both 32-bit and 64-bit targets, beginning with this update only the 64-bit version is generated. This decision was made partly to reduce maintenance effort, but primarily because Delphi2CB now only partially supports the generation of 32-bit code.

Directory Structure

The directory layout of the C++ code was designed to simplify code comparisons between the original Delphi sources and the generated C++ sources.


| Folder			|  Content                                                                                                       |
| ------      |  -------                                                                                                       |
| Demos				|  Original Delphi demos and translated C++ demo projects using the installed SynEdit components                 |
| DemosCb64		|  64-bit demo projects using the modern C++Builder compiler and with automatically translated of dfm files      |
| Source			|  Original Delphi source code                                                                                   |
| SourceRaw64	|  Result of the automatic 64-bit conversion using the modern compiler                                           |
| SourceRun64	|  Files containing the manual corrections applied after automatic conversion                                    |
| SynGen			|  Original Delphi SynGen source code                                                                            |
| SynGenRaw		|  Automatically generated 64-bit C++ version of SynGen                                                          |
| SynGenRun		|  Post-processed and buildable 64-bit SynGen C++ sources                                                        |
| TestCpp64		|  Test project used to verify that all files in SourceCppRun64 compile successfully                             |


Notes About the Demos
---------------------

The demo applications have only been tested occasionally. They are published here mainly to receive feedback, bug reports, and suggestions for improvements.

The C++Builder projects mostly reuse the original DFM files from the Delphi projects.


Purpose of This Project
-----------------------

This project is published for several reasons:

- C++Builder users can examine and use the C++ demos without requiring a Delphi license.
- The code can be tested without installing the SynEdit components separately.
- One long-term goal is to revive the old TextTransformer application using appropriately modified SynEdit components. For this   purpose, the editor must support highlighting of specific text positions.
- Finally, this project demonstrates the capabilities of the Delphi2Cpp and Delphi2CB conversion tools.

Video Presentations
-------------------

Several videos describe the conversion process in more detail:

Part 1

Demonstrates the creation of a C++Builder project from the CompletionProposal demo using installed SynEdit components.
https://www.youtube.com/watch?v=olfPJa5Suq0

Part 2

Discusses several challenges encountered while converting the SynEdit component sources to C++.

https://www.youtube.com/watch?v=R6SjB1kiJ5c


Part 3

Demonstrates the creation of a C++Builder project from the more complex EditApp demo using the converted C++ version of the SynEdit components.

https://www.youtube.com/watch?v=fuwcN4g-vgw

A future video may demonstrate the conversion of DFM files into C++ source code and discuss several additional topics.

History
-------

February 2022 — Original release for RAD Studio 11 Alexandria
August 2024 — RAD Studio 12 Athens update with added 64-bit projects for the modern C++Builder compiler
May 2026 — RAD Studio 13 Florence update; 32-bit projects removed

The SynEdit components have continued to evolve since the initial release of SynEditCb. Whether the newer versions will also be translated depends largely on interest and feedback.

"This product includes software developed by the Apache Software Foundation (http://www.apache.org/
)."


--
Detlef Meyer-Eltz
