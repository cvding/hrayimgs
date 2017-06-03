# complile config option
N_FLAG = /c

INC_DIR += /I ./Include /I "$(VS_DIR)/Include" /I "$(VS_SDK)/Include"\

C_FLAG = $(INC_DIR) /GS /analyze- /W3 /Zc:wchar_t /Fd"$(TARGET_PATH)/$(TARGET).pdb"\
		 /sdl /fp:precise /D "WIN32" /D "_LIB" /D "_UNICODE" /D "UNICODE"\
		 /errorReport:prompt /WX- /Zc:forScope /Gd /Oy- /EHsc /nologo

ifeq ($(ver),debug)
C_FLAG += /GS /ZI /Gm /Od /D "_DEBUG" /RTC1 /MDd
else
C_FLAG += /GL /Gy /Zi /Gm- /O2 /D "NDEBUG" /Oi /MD
endif

L_FLAG = /NOLOGO
ifneq ($(ver),debug)
L_FLAG += /LTCG
endif

$(TARGET) : $(POBJ)
	@echo compile the project($(TARGET)) source codes
	@$(LINK) /lib /OUT:"$(TARGET_PATH)\$(TARGET).lib" $^ $(L_FLAG)
	@$(RM) $(TARGET_PATH)/*.obj $(TARGET_PATH)/*.pdb

$(POBJ): $(SRC)
#	@echo $(POBJ)
	@$(CC) $^ $(N_FLAG) $(C_FLAG) /Fo"./$(TARGET_PATH)/"

.phony : clean install depend docxy edocxy

# depend the dll library
depend:
	@echo "depend the dynamic library and debug files..."
	@$(FIND) ./Resource -iname "*.dll" -type f -exec cp {} $(TARGET_PATH) ;
	@$(FIND) ./Resource -iname "*.pdb" -type f -exec cp {} $(TARGET_PATH) ;

# install the dll into system
install:
	@echo "install libray package into $(INSTALL)"
	@if not exist $(INSTALL) (mkdir Export\$(TARGET))
	@$(FIND) ./$(TARGET_PATH) -iname "*.lib" -type f -exec cp {} $(INSTALL) ;
	@$(FIND) ./Doc -iname "*.chm" -type f -exec cp {} $(INSTALL) ;
	@cp -rf ./Include/* $(INSTALL)

# clean the temporary file
clean:
	@echo "clean the temporary files..."
	@$(FIND) ./$(TARGET_PATH) -type f -print |xargs $(RM)
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