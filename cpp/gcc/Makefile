.PHONY: all clean

HOME := ../src
ENV := ${HOME}

INC_DIRS := -I${HOME}/gen-cpp
LDADD := libtutorialgencpp.la \
	/usr/local/lib/libthrift.la
CC = gcc
CXX = g++
CXXFLAGS := -Wall -O2 -Os ${INC_DIRS} ${DEFINES}
LDFLAGS := ${LIB_DIRS}
CXXLINK := libtool --tag=CXX --mode=link ${CXX} -Wall -Wextra -pedantic -g -O2 -std=c++11 -L/usr/lib
LIBS := -lssl -lcrypto -lrt -lpthread

SERVER_SOURCES := ${HOME}/server/server.cpp
CLIENT_SOURCES := ${HOME}/client/client.cpp
LIBTUTORIALGENCPP_LA_SOURCES := $(wildcard ${HOME}/gen-cpp/*.cpp)

# expands to list of object files
SERVER_OBJECTS := ${SERVER_SOURCES:.cpp=.o}
CLIENT_OBJECTS := ${CLIENT_SOURCES:.cpp=.o}
LIBTUTORIALGENCPP_LA_OBJECTS := ${LIBTUTORIALGENCPP_LA_SOURCES:.cpp=.o}
LIBTUTORIALGENCPP_LO := ${LIBTUTORIALGENCPP_LA_SOURCES:.cpp=.lo}

all: TutorialServer TutorialClient

libtutorialgencpp.la: ${LIBTUTORIALGENCPP_LO}
	${CXXLINK} ${LIBTUTORIALGENCPP_LO} /usr/local/lib/libthrift.la -o libtutorialgencpp.la
	
TutorialServer: ${SERVER_OBJECTS} libtutorialgencpp.la
	@rm -f TutorialServer
	${CXXLINK} ${LDADD} $< ${STATIC_LIBS} -o $@ 
	
TutorialClient: ${CLIENT_OBJECTS} libtutorialgencpp.la
	@rm -f TutorialClient
	${CXXLINK} ${LDADD} $< ${STATIC_LIBS} -o $@ 

# rule to build cpp files
%.lo: %.cpp
	libtool --mode=compile gcc -c $< -o $@

%.o: %.cpp
	${CC} ${CXXFLAGS} -c $< -o $@

clean:
	${RM} ${SERVER_OBJECTS} ${CLIENT_OBJECTS} ${LIBTUTORIALGENCPP_LA_OBJECTS} ${LIBTUTORIALGENCPP_LO} libtutorialgencpp.la TutorialServer TutorialClient 

