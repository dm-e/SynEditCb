
SynEditCb is a C++ version for C++Builder of the Delphi SynEdit components. The SynEdit components are wide spread free components for an editor with syntax highlighting. They are hosted at GitHub:

https://github.com/SynEdit/SynEdit


However, the C++ code here is based on the Delphi code that you get when you fetch the components via GetIt in RAD Studio 11 Alexandria. The code was converted with the program Delphi2CB. 

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


The code has hardly been tested so far. I'm posting it here in hopes of getting feedback on bugs and suggestions for improvments.


    "This product includes software developed by the Apache Software Foundation 
    (http://www.apache.org/)."

