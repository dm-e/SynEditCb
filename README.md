
SynEditCb is a C++ version for C++Builder of the Delphi SynEdit components. The SynEdit components are wide spread free components for an editor with syntax highlighting. They are hosted at GitHub:

https://github.com/SynEdit/SynEdit

However, the C++ code here is based on the Delphi code that you get when you fetch the components via GetIt in RAD Studio 11 Alexandria. The code was converted with the commercial program Delphi2CB. 

https://www.texttransformer.com/Delphi2CB_en.html


The Delphi2CB project files used for this are located in the “BatchFiles” folder for the classic 32 bit compiler or in “BatchFiles64” for the modern 64 bit compiler.. 

The directories of the C++ code are designed in such a way that simple code comparisons are possible. In the following, the directories of the original code and the converted code are shown and explained:

| Folder			|  Content                                                                                                       |
| ------      |  -------                                                                                                     |
| Demos				|  original Delphi code and translated C++ code using the installed SynEdit components                           |
| DemosCb			|  using the code translated for 32 bit with the classic compiler and with manually created dfm replacement code |
| DemosCb64		|  using the code translated for 64 bit with the modern compiler and with automatic translation of the dfm files |
| Source			|  original Delphi code                                                                                          |
| SourceRaw		|  result of the automatic conversion for 32 bit with the classic compiler                                       |
| SourceRaw64	|  result of the automatic conversion for 64 bit with the modern compiler                                        |
| SourceRun		|  post-processed, compiing code for 32 bit with the classic compiler                                            |
| SourceRun64	|  post-processed, compiing code for 64 bit with the modern compiler                                             |
| SynGen			|  original Delphi code                                                                                          |
| SynGenRaw		|  result of the automatic conversion for 32 bit with the classic compiler                                       |
| SynGenRun		|  post-processed, compiing code for 32 bit with the classic compiler                                            |
| TestCpp			|  project to assert that all files in SourceRun compile with the classic 32 bit compiler                        |
| TestCpp64		|  project to assert that all files in SourceRun64 compile with the modern 64 bit compiler                   |


The demos were only tested sporadically. I'm presentig it here in hopes of getting feedback on bugs and suggestions for improvments.


I present the code here for several reasons:

- C++Builder users can view the C++ demos without having a Delphi license.
- You can even try the code without installing the components
- My long-term intention is to get my old TextTransformer program working again using appropriately modified components. (the editor must be able to highlight specific text positions therefore.)
- last but not least this is a demonstration of the capabilities of my Delphi2Cpp/Delphi2CB programs.

For this purpose there are also three videos in which the conversion of the Delphi code is described in more detail

- The first part demonstrates the creation of a C++Builder project from the CompletionProposal Demo using the installed SynEdit components.

https://www.youtube.com/watch?v=olfPJa5Suq0


- The second part discusses some problems in converting the code of SynEdit components to C++.

https://www.youtube.com/watch?v=R6SjB1kiJ5c


- The third part demonstrates the creation of a C++Builder project from the more complex EditApp demo using the C++ converted code of the SynEdit components.

https://www.youtube.com/watch?v=fuwcN4g-vgw


- I hope that I will find time to present the conversion of the dfm files into C++ source code along with a few other small topics in another demo.

History:

- Februar 2022: original version made for RAD Studio 11 Alexandria
. August 2024: version for RAD Studio 12 Athens: 64 bit  projects for the modern C++Builder compiler added

The Synedit components have been further developed since SynEditCb was first released. Whether I will translate the new code depends on whether there is any interest and feedback.


    "This product includes software developed by the Apache Software Foundation 
    (http://www.apache.org/)."


--
Detlef Meyer-Eltz

