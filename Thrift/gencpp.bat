@echo off
compiler\thrift-0.9.2.exe -r --gen cpp thrift-src\*.thrift
if ERRORLEVEL 1 (
	echo Cannot compile thrift files
	exit 1
)
del gen-cpp\*.skeleton.cpp
move gen-cpp ..\cpp\src\
