
type = lib
ver = release
arch = x86

# 设置编译器命令
ifeq ($(arch),x64)
    CC = "$(VS_DIR)/bin/amd64/cl"
    LINK = "$(VS_DIR)/bin/amd64/link"
else
    CC = "$(VS_DIR)/bin/cl"
    LINK = "$(VS_DIR)/bin/link"
endif

# 设置其他命令
DOCXY = "$(DOC_DIR)/doxygen"
FIND = gfind
RM = rm -rf
MKDIR = mkdir

# 获取工程名称
PROJECT_PATH = $(shell pwd)
PROJECT_NAME = $(notdir $(PROJECT_PATH))

# 设置根据工程类型设置工程名
ifeq ($(type),demo)
    PROJECT_NAME_A = $(PROJECT_NAME)_demo
endif

ifeq ($(type),lib)
    PROJECT_NAME_A = lib$(PROJECT_NAME)
endif

ifeq ($(type),dll)
    PROJECT_NAME_A = $(PROJECT_NAME)
endif

# 判断是否为64位程序
ifeq ($(arch),x64)
    PROJECT_NAME_B = $(PROJECT_NAME_A)$(arch)
else
    PROJECT_NAME_B = $(PROJECT_NAME_A)
endif

# 设置版本设置工程名
ifeq ($(ver),debug)
    TARGET = $(PROJECT_NAME_B)d
else
    TARGET = $(PROJECT_NAME_B)
endif

# 设置目录结构
TARGET_PATH = ./Bin
SRC_DIR = ./Source
INSTALL = ./Export/$(TARGET)
DEMO_DIR = ./Build/vs2013_demo

# 搜索源文件并设置目标文件
SRC = $(wildcard $(SRC_DIR)/*.c*)
OBJ = $(notdir $(addsuffix .obj, $(basename $(SRC))))
POBJ = $(addprefix $(TARGET_PATH)/, $(OBJ))

# make dynamic library
ifeq (dll,$(type))
	include ./Resource/public/makedll.mk
endif

# make static library
ifeq (lib,$(type))
	include ./Resource/public/makelib.mk
endif

# make exe
ifeq (demo,$(type))
	include ./Resource/public/makeexe.mk
endif