#!/bin/bash
compiler/thrift -r --gen cpp thrift-src/*.thrift
if [ $? -ne 0 ]; then
	echo "Cannot compile thrift files"
	exit 1
fi
rm gen-cpp/*.skeleton.cpp
if [ -e ../cpp/src/gen-cpp ]; then
	rm -rf ../cpp/src/gen-cpp
fi
mv -f gen-cpp ../cpp/src
