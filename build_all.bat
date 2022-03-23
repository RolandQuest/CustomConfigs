
@echo off

SET IntermediateDirectory_Release=objects_release
SET IntermediateDirectory_Debug=objects_debug

MKDIR %IntermediateDirectory_Release%
MKDIR %IntermediateDirectory_Debug%

FOR /R "include/" %%f IN (*.cpp) DO (
	ECHO Building %%~nf.cpp
	clang++ -c -std=c++14 -O3 -Wall -pedantic %%f -o %IntermediateDirectory_Release%/%%~nf.o
	clang++ -c -std=c++14 -g -Wall -pedantic %%f -o %IntermediateDirectory_Debug%/%%~nf.o
)

ECHO Archiving...
FOR /R "%IntermediateDirectory_Release%/" %%f IN (*.o) DO (
	llvm-ar rc cc.lib %%f 
)

FOR /R "%IntermediateDirectory_Debug%/" %%f IN (*.o) DO (
	llvm-ar rc cc_dbg.lib %%f 
)

RD /S /Q %IntermediateDirectory_Release%
RD /S /Q %IntermediateDirectory_Debug%




