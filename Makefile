BUILD_PATH = build
DEBUG_PATH = $(BUILD_PATH)/debug
RELEASE_PATH = $(BUILD_PATH)/release



# define RELEASE to build with release configuration, debug will be used otherwise

ifdef RELEASE
	LINKING_MODE = -static
	OPTIMIZATION = -O3
	OUT_PATH = $(RELEASE_PATH)
else
	OPTIMIZATION = -Og
	OUT_PATH = $(DEBUG_PATH)
endif



CC = g++
CPP_VERSION = --std=c++20

OUT_NAME = riv
OUT_APP = $(OUT_PATH)/$(OUT_NAME)

DEP_PATH = dep

# dependencies
SPECTER_PATH = $(DEP_PATH)/specter

SPECTER_INCLUDE = $(SPECTER_PATH)/include
SPECTER_LIB_PATH = $(SPECTER_PATH)/lib
SPECTER_LIB_NAME = specter


INCLUDE_PATH = \
	-I./src \
	-I$(SPECTER_INCLUDE)


LIBRARIES_PATH = \
	-L$(SPECTER_LIB_PATH)


LIBRARIES = \
	-l$(SPECTER_LIB_NAME)


CPP_WANINGS = -Wall -Wno-switch


CPP_FLAGS = $(OPTIMIZATION) $(INCLUDE_PATH) $(CPP_VERSION) $(CPP_WANINGS)
LINK_FLAGS = $(LINKING_MODE) $(LIBRARIES_PATH) $(LIBRARIES)


SOURCES = $(shell find src -name "*.cpp")
OBJECTS = $(SOURCES:.cpp=.o)

FULL_OBJECTS = $(addprefix $(OUT_PATH)/, $(notdir $(OBJECTS)))



runc: $(OUT_APP)
	@ echo Running...
	@ $(OUT_APP) $(SOURCE_FILE)


run:
	@ echo Running...
	@ $(OUT_APP) $(SOURCE_FILE)


# links object files into a executable
.PHONY:
$(OUT_APP) build: $(OBJECTS)
	@ echo Linking objects: $(FULL_OBJECTS)
	@ $(CC) $(FULL_OBJECTS) -o $(OUT_APP) $(LINK_FLAGS)
	@ echo Application created at $(OUT_APP)




# compiles source files into objects
$(OBJECTS): %.o: %.cpp
	@ echo Compiling $<
	@ $(CC) -c $< -o $(addprefix $(OUT_PATH)/, $(notdir $@)) $(CPP_FLAGS)


.PHONY:
analize:
	@ make build -j 10 CC="include-what-you-use -Xiwyu --verbose=1"


# cleans up build folder
.PHONY:
clean:
	@ rm -r $(DEBUG_PATH)/*
	@ rm -r $(RELEASE_PATH)/*