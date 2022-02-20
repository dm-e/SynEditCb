
SynEditCb is a C++ version for C++Builder of the Delphi SynEdit components. The SynEdit components are wide spread free components for an editor with syntax highlighting. They are hosted at GitHub:

https://github.com/SynEdit/SynEdit

However, the C++ code here is based on the Delphi code that you get when you fetch the components via GetIt in RAD Studio 11 Alexandria. The code was converted with the commercial program Delphi2CB. 

https://www.texttransformer.com/Delphi2CB_en.html

The Delphi2CB project files used for this are located in the "BatchFiles" folder. 

The directories of the C++ code are designed in such a way that simple code comparisons are possible. In the following, the directories of the original code and the converted code are shown and explained:

Demos				<-  using the installed components
DemosCb			<-  using the translated code
Source			<-  original Delphi code
SourceRaw		<-  result of the automatic conversion
SourceRun		<-  post-processed, compiing code
SynGen			<-  original Delphi code
SynGenRaw		<-  result of the automatic conversion
SynGenRun		<-  post-processed, compiing code
TestCpp			<-  project to assert that all files compile 

The code has hardly been tested so far. I'm presentig it here in hopes of getting feedback on bugs and suggestions for improvments.


I present the code here for several reasons:

- C++Builder users can view the C++ demos without having a Delphi license.
- You can even try the code without installing the components
- My long-term intention is to get my old TextTransformer program working again using appropriately modified components. (the editor must be able to highlight specific text positions therefore.)
- last but not least this is a demonstration of the capabilities of my Delphi2CP program

For this purpose there are also three videos in which the conversion of the Delphi code is described in more detail

- The first part demonstrates the creation of a C++Builder project from the CompletionProposal Demo using the installed SynEdit components.

https://www.youtube.com/watch?v=olfPJa5Suq0


- The second part discusses some problems in converting the code of SynEdit components to C++.

https://www.youtube.com/watch?v=R6SjB1kiJ5c


- The third part demonstrates the creation of a C++Builder project from the more complex EditApp demo using the C++ converted code of the SynEdit components.

https://www.youtube.com/watch?v=fuwcN4g-vgw


As soon as I published the code here, there is already a new version of the Synedit components. Whether I will also convert this code depends on whether there will be any interst and feedback at all.


    "This product includes software developed by the Apache Software Foundation 
    (http://www.apache.org/)."


--
Detlef Meyer-Eltz

