 - README - 

=====================	     [Usage notes]		======================

(compile and run):

$ make
$ ./bbbserver [-c] <config file> [-v] <terminal log level>


(remove object files):

$ make clean


(config file notes):

1. config files should be put in “config” folder, inside program directory.

(terminal log notes):

1. Verbosity level (between 0 - 2) indicating whether user wants:
	0 - silent terminal log
	1 - regular terminal log
	2 - heavy terminal log (for debugging) 


===================	     [Program Files]		=====================

1. Included config file(s) useful info:
	- master1.conf
		name 		= “master1”
		front-end port 	= 9001
		back-end port 	= 9002

	- slave1.conf
		name 		= “slave1”
		front-end port 	= 9010
		back-end port 	= 9002

	- slave2.conf
		name 		= “slave2”
		front-end port 	= 9011
		back-end port 	= 9004

	- master1.conf
		name 		= “slave3”
		front-end port 	= 9012
		back-end port 	= 9002
	


===================	     [External Libraries]	=====================

1. SPCUUID : { https://github.com/spc476/SPCUUID }
	- general use UUID generation library
	- source files: 
		p2/spcuuid/src
	- object files:
		p2/spcuuid/obj

*  Using this because we were having trouble with linker finding and using the default UUID lib on the ECE cluster machines
** Not including “uuidlib_v3.o” and “uuidlib_v5.o” object files due to linker issues 



===================		[Known Issues]		=====================


1. /peer/map Requests not implemented

2. /peer/rank/<content_path> Requests not implemented


===================		   [Other]		=====================

Authors: Malcolm Fitts (mfitts) and Sam Adams (sjadams)

