# cpp-thrift-hello-world

# License

cpp-thrift-hello-world is built by [DataArt](http://dataart.com) and distributed
 under [MIT License](http://en.wikipedia.org/wiki/MIT_License).

# Building for Windows

1. Download Boost from <http://sourceforge.net/projects/boost/files/boost/1.58.0>
 and extract the files from the archive to the cpp\\3rdParty subdirectory of the
 base directory.

2. Launch the Visual Studio Command Prompt. Change your current directory to the
 Boost root directory and invoke bootstrap.bat. To build Boost.Thread library
 invoke b2.exe as follows:  
  ```
> b2.exe --with-thread --with-date_time --build-type=complete --link=static --runtime-link=static --runtime-debugging=on`
  ```
Boost library binaries will be placed in the stage\\lib subdirectory of your
 build directory.

3. Download "Win32 OpenSSL v1.0.2a" file from
 <http://slproweb.com/products/Win32OpenSSL.html> and install OpenSSL.

4. Download cmake from <http://www.cmake.org/download/> and install it.

5. Open the environment.cmake file in a text editor and edit values of the listed
 environment variables.

6. If you want to build the libthriftnb library and the Threaded Server
 application you need to build the libevent library previously.  
Download libevent from <https://github.com/libevent/libevent.git>.  
Change your current directory to the libevent root directory and type:  
  ```
> mkdir build && cd build  
> cmake -G "Visual Studio 10" ..  
> start libevent.sln  
  ```
Build the solution.

7. You need to provide the information about the 3rd party components for MSBuild.
 Open the environment.bat file in a text editor and edit values of the listed
 environment variables.

8. Download Thrift from <https://github.com/apache/thrift/tree/0.9.2>.  
Launch the Visual Studio Command Prompt and change your current directory to the
 cpp subdirectory of the base directory. To build the libthrift library run:  
  ```
> build-libthrift.bat
  ```
The libthrift library will be created in the lib\\cpp\\Debug subdirectory of the
 Thrift root directory.

If you want to build the Threaded Server application you need to link it with
 the libthriftnb library. To build the libthriftnb library run:  
  ```
> build-libthriftnb.bat
  ```
The libthriftnb library will be created in the lib\\cpp\\Debug subdirectory of the
 Thrift root directory.

9. Change your current directory to the thrift subdirectory of the base directory.
 Create a thrift file in the thrift-src subdirectory and run:  
  ```
> gencpp.bat  
  ```
The Thrift compiler will create the cpp\\src\\gen-cpp subdirectory of the base
 directory and place source code files there.

10. Change your current directory to the cpp subdirectory of the base directory
 and run:  
  ```
> cmake .
  ```
You will obtain the files needed to build the server and client projects via
 Visual Studio.  
Open the Visual Studio solution file and build the solution.

# Building for Linux

1. Download Boost from <http://sourceforge.net/projects/boost/files/boost/1.58.0>
 and extract the files from the archive. Add read permission for all users to the
 Boost root directory:  
  ```
$ chmod a+r boost_1_58_0
  ```

2. Change your current directory to the Boost root directory and invoke
 bootstrap.sh. To build Boost.Thread library invoke b2 as follows:  
  ```
$ sudo ./b2 --with-thread --with-date_time --build-type=complete --link=static --runtime-link=static --runtime-debugging=on --layout=tagged install
  ```
Boost library binaries will be placed in the stage/lib subdirectory of your
 build directory.

3. Install libtool:  
  ```
$ sudo aptitude install libtool
  ```

4. Install autoconf:  
  ```
$ sudo aptitude install autoconf
  ```

5. Install automake:  
  ```
$ wget http://http.us.debian.org/debian/pool/main/a/automake-1.14/automake_1.14.1-4_all.deb
$ sudo dpkg -i automake_1.14.1-4_all.deb
  ```

6. Install yacc and lex:  
  ```
$ sudo aptitude install byacc flex
  ```

7. Install libevent:  
  ```
$ sudo aptitude install libevent-dev
  ```

8. Install cmake:  
  ```
$ sudo aptitude install cmake
  ```

9. Download Thrift from <https://github.com/apache/thrift/tree/0.9.2>.  
Change your current directory to the Thrift root directory.  
Run bootstrap.sh:  
  ```
$ ./bootstrap.sh
  ```
Configure Thrift:  
  ```
$ ./configure --with-cpp --with-boost=../boost_1_58_0 --without-qt4 --without-csharp --without-java --without-erlang --without-nodejs --without-lua --without-python --without-perl --without-php --without-php_extension --without-ruby --without-haskell --without-go --without-d
  ```
Build Thrift:  
  ```
$ make
  ```
Install Thrift:  
  ```
$ sudo make install
  ```
Add shared libraries directories to the dynamic linker cache:  
  ```
$ sudo ldconfig
  ```

10. Change your current directory to the Thrift subdirectory of the base directory.
 Create a Thrift file in the thrift-src subdirectory and run:  
  ```
$ sh gencpp.sh
  ```
The Thrift compiler will create the cpp/src/gen-cpp subdirectory of the base
 directory and place source code files there.

11. Change your current directory to the cpp subdirectory of the base directory
 and run:  
  ```
$ cmake .
  ```
You will obtain the Makefile. Run make to build the server and client projects:  
  ```
$ make
  ```

