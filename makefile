# ***************************************
# breif:  a makefile for c/cpp file 
# 	complie & linker tool on 
# 	window system
# create:  dddz
# email : cvchina@163.com
# date: 2016-8-30 
#****************************************

# define VS PATH
# define some command path
VS_DIR = D:/WorkRoot/Program/Microsoft Visual Studio 12.0/VC
VS_SDK = C:/Program Files (x86)/Microsoft SDKs/Windows/v7.1A
DOC_DIR = D:/WorkRoot/Program/doxygen/bin

# include director
INC_DIR = /I ./Resource/BaseStruct \
	      /I ./Resource/BaseStruct/PublicInclude \
	      /I ./Resource/BaseStruct/BaseInclude \
	      /I ./Resource/basetype


# 3rd-party library not use in static library
# and you will figure out debug and release
LIB_3RD =



include ./Resource/public/makecom.mk
