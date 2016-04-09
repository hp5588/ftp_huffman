#**FTP Server & Client**
###With Huffman Encoder

##Author#

	高伯文, EE, NSYSU  (B013012011)

##Requirement
 - CMAKE 3.3 ABOVE
 - c++ compiler with c++11 supported

##Build
following instructions will build the top level CMakeLists

	cd path/to/root
	mkdir build
	cd build
	cmake ../ftp_huffman
	make

after entering the command above, the folder structure suppose to look like this

	root.
	├── build
	│   ├── CMakeCache.txt
	│   ├── CMakeFiles
	│   ├── cmake_install.cmake
	│   ├── Huffman
	│   ├── HW2_FtpClient
	│   ├── HW2_FtpServer
	│   └── Makefile
	└── ftp_huffman
	    ├── CMakeLists.txt
	    ├── Huffman
	    ├── HW2_FtpClient
	    ├── HW2_FtpServer
	    └── README.odt


##Execute
1. **Enter the build folder**
    * cd path/to/build/folder
2. **Execute Server**
	#in build folder
	* $cd HW2_FtpServer/
	* $./ftpClient
3. **Execute Client**
	#in build folder
	* $cd HW2_FtpClient/
	* $./ftpServer

##Usage

####**Server**

After executing the server program, server is not ready yet. However, server will be online with a single command.

	$server> run

Now, the server will be ready to serve client on the default ip 127.0.0.1 and port 8000.



You can also specify the ip and port by providing the extra parameters.

	$server> run 192.168.0.2 6000

For more details, please use “help” in the server command line.

	$server> help



####**Client**
To connect to a ready-to-serve server, simply enter “connect” command.

	$server> connect

or

	$client> connect 192.168.0.2 6000

By default, the “connect” command will connect the local host (127.0.0.1) server with port 8000.

To specify the file to upload, “upload” command will be used.
>You have to connect to the server first before you can upload a file.

	$client> upload file.txt




##Extra knowledge

####**Help**
“help” command is available in both client and server. Take server's help command as example.

	server >
	help
	////////// help //////////
	 run [server ip] [port]--open a new server with ip and port provided
	 stop [pid]--------------stop a server by specifying its pid (status can tell)
	 status------------------the server which are running now
	 quit--------------------end all servers and quit program
	 help--------------------show this help


####**Encoding and Decoding**
While using “upload” command in client, the specified file will be automatically encoded into <file>.enc and <file>.tree. Both file will then sent to server to be decoded.


For encoding feature, it's available independently in client with encode command.
	
	$client> encode file.txt

The file.txt will be encoded into two file then saved (“file.txt.enc” and “file.txt.tree”). 

With these two files, we can obtain the original file by using decode command in client

	$client> decode file.txt





