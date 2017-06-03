# ***************************************
# breif:  a .exe makefile for c/cpp file 
# 	complie & linker tool on 
# 	window system
# create:  dddz
# email : cvchina@163.com
# date: 2016-8-30 
# ****************************************

DEMO_SRC = $(wildcard $(DEMO_DIR)/*.c*)
DEMO_OBJ = $(notdir $(addsuffix .obj, $(basename $(DEMO_SRC))))
DEMO_POBJ = $(addprefix $(TARGET_PATH)/, $(DEMO_OBJ))

# complile config option
N_FLAG = /c

INC_DIR += /I ./Include /I "$(VS_DIR)/Include" /I "$(VS_SDK)/Include"\

# windows system library
ifeq ($(arch),x64)
	LIB_SYS = /LIBPATH:"$(VS_DIR)/lib/amd64" /LIBPATH:"$(VS_SDK)/lib/x64"
else
	LIB_SYS = /LIBPATH:"$(VS_DIR)/lib" /LIBPATH:"$(VS_SDK)/lib"
endif

LIB_SYS += "kernel32.lib" "user32.lib" "gdi32.lib" "winspool.lib"\
		  "comdlg32.lib" "advapi32.lib" "shell32.lib" "ole32.lib"\
		  "oleaut32.lib" "uuid.lib" "odbc32.lib" "odbccp32.lib"

C_FLAG = $(INC_DIR) /GS /analyze- /W3 /Zc:wchar_t /fp:precise /D "WIN32" \
		 /D "_CONSOLE" /D "_LIB" /D "_UNICODE" /D "UNICODE" /errorReport:prompt \
		 /WX- /Zc:forScope /Gd /Oy- /EHsc /nologo /Fd"$(TARGET_PATH)/$(TARGET).pdb"

ifeq ($(ver),debug)
    C_FLAG += /ZI /Gm /Od /sdl /D "_DEBUG" /RTC1 /MDd
else
    C_FLAG += /GL /Gy /Zi /Gm- /O2 /sdl /D "NDEBUG" /Oi /MD
endif

L_FLAG = $(LIB_3RD) $(LIB_SYS) /NXCOMPAT /DYNAMICBASE /MACHINE:$(arch)\
		 /SUBSYSTEM:CONSOLE /OPT:REF /ERRORREPORT:PROMPT /NOLOGO /TLBID:1 

ifeq ($(ver),debug)
    L_FLAG +=/INCREMENTAL /DEBUG
else
    L_FLAG +=/INCREMENTAL:NO /LTCG /OPT:ICF
ifeq ($(arch),x86)
	L_FLAG +=/SAFESEH
endif
endif

$(TARGET): $(POBJ) $(DEMO_POBJ)
	@echo compile the project($(TARGET)) source codes
	@$(LINK) /OUT:"$(TARGET_PATH)/$(TARGET).exe" $^ $(L_FLAG)
	@$(RM) $(TARGET_PATH)\*.obj $(TARGET_PATH)\*.pdb

$(POBJ): $(SRC)
	@$(CC) $^ $(N_FLAG) $(C_FLAG) /Fo"$(TARGET_PATH)/"

$(DEMO_POBJ): $(DEMO_SRC)
	$(CC) $^ $(N_FLAG) $(C_FLAG) /Fo"$(TARGET_PATH)/"

.phony : clean depend install docxy edocxy

# depend the dll library
depend:
	@echo "depend the dynamic library and debug files..."
	@$(FIND) ./Resource -iname "*.dll" -type f -exec cp {} $(TARGET_PATH) ;
	@$(FIND) ./Resource -iname "*.pdb" -type f -exec cp {} $(TARGET_PATH) ;

# install the dll into system
install:
	@echo "install libray package into $(INSTALL)"
	@$(FIND) ./Bin -iname "*.dll" -type f -exec cp {} $(INSTALL) ;
	@$(FIND) ./Bin -iname "*.exe" -type f -exec cp {} $(INSTALL) ;
	@$(FIND) ./Doc -iname "*.chm" -type f -exec cp {} $(INSTALL) ;
	@cp -rf ./Include/* $(INSTALL)

# clean the temporary file
clean:
	@echo "clean the temporary files..."
	@$(FIND) ./Bin -type f -print |xargs $(RM)
	@$(FIND) ./Build -iname "debug" -type d |xargs $(RM)
	@$(FIND) ./Build -iname "release" -type d |xargs $(RM)
	@$(FIND) ./Build -iname "*.opensdf" -type f |xargs $(RM)
	@$(FIND) ./Build -iname "*.sdf" -type f |xargs $(RM)
	
# create a doc
docxy:
	@$(DOCXY) doxyfile
	@$(FIND) ./Doc -iname "html" -type d |xargs $(RM)

# edit doxyfile
edocxy:
	@note doxyfile ./Resource/public/mainpage.md 