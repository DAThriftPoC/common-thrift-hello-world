set(HOME ${CMAKE_HOME_DIRECTORY})

set(SRC_PATH_SERVER ${HOME}/server)
set(SRC_PATH_CLIENT ${HOME}/client)
set(SRC_PATH_GENCPP ${HOME}/gen-cpp)
set(BOOST_ROOT ${HOME}/../3rdParty/boost_1_58_0)
set(THRIFT_ROOT ${HOME}/../3rdParty/Thrift)

if (UNIX)
	set(OPENSSL_INCLUDE /usr/include/openssl)
elseif (WIN32)
	set(OPENSSL_ROOT D:/development/proof/OpenSSL-Win32)
	set(OPENSSL_INCLUDE ${OPENSSL_ROOT}/include)
	set(LIBEVENT_ROOT D:/libevent)
	set(BOOST_LIB libboost_thread-vc100-mt-gd-1_58)
endif()

