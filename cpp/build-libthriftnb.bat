@echo off

call environment.bat
set INCLUDE=%LIBEVENT_ROOT%;%LIBEVENT_ROOT%\include;%LIBEVENT_ROOT%\WIN32-Code;%LIBEVENT_ROOT%\WIN32-Code\nmake;%THRIFT_ROOT%\lib\cpp\src;%INCLUDE%
set LIB=LIBEVENT_LIB;%LIB%

if not defined THRIFT_ROOT (
	echo The THRIFT_ROOT variable is not defined
	exit 1
)
if not defined BOOST_ROOT (
	echo The BOOST_ROOT variable is not defined
	exit 1
)
if not defined OPENSSL_ROOT_DIR (
	echo The OPENSSL_ROOT_DIR variable is not defined
	exit 1
)
if not defined LIBEVENT_ROOT (
	echo The LIBEVENT_ROOT variable is not defined
	exit 1
)

if not exist %THRIFT_ROOT% (
	echo "%THRIFT_ROOT%" directory does not exist
	exit 1
)
if not exist %BOOST_ROOT% (
	echo "%BOOST_ROOT%" directory does not exist
	exit 1
)
if not exist %OPENSSL_ROOT_DIR% (
	echo "%OPENSSL_ROOT_DIR%" directory does not exist
	exit 1
)
if not exist %LIBEVENT_ROOT% (
	echo "%LIBEVENT_ROOT%" directory does not exist
	exit 1
)

pushd %THRIFT_ROOT%\lib\cpp
if ERRORLEVEL 1 (
	echo %THRIFT_ROOT%\lib\cpp: no such directory
	exit 1
)
msbuild thrift.sln /p:BOOST_ROOT=%BOOST_ROOT%;OPENSSL_ROOT_DIR=%OPENSSL_ROOT_DIR%;LIBEVENT_ROOT=%LIBEVENT_ROOT%;useenv=true /t:libthriftnb
popd
