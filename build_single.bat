
@echo off

SET IntermediateDirectory_Release=objects_release
SET IntermediateDirectory_Debug=objects_debug

MKDIR %IntermediateDirectory_Release%
MKDIR %IntermediateDirectory_Debug%

SET /p cppFile=File to update: 

FOR /R "include/" %%f IN (*.cpp) DO (
	IF %%~nf == %cppFile% (
		ECHO Building %cppFile%
		clang++ -c -std=c++14 -O3 %%f -o %IntermediateDirectory_Release%/%%~nf.o
		clang++ -c -std=c++14 -g -Wall -pedantic %%f -o %IntermediateDirectory_Debug%/%%~nf.o
		goto archive
	)
)
SET /p file_not_found=%cppFile%.cpp not found in include/ folder.
goto cleanup

:archive
ECHO Archiving...
llvm-ar rc cc.lib %IntermediateDirectory_Release%/%cppFile%.o
llvm-ar rc cc_dbg.lib %IntermediateDirectory_Debug%/%cppFile%.o

:cleanup
RD /S /Q %IntermediateDirectory_Release%
RD /S /Q %IntermediateDirectory_Debug%

