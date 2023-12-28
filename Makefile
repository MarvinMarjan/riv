BUILD_PATH = build
DEBUG_PATH = $(BUILD_PATH)/debug
RELEASE_PATH = $(BUILD_PATH)/release

STDLIB_OUTPATH = lib/std



# define RELEASE to build with release configuration, debug will be used otherwise

ifdef RELEASE
	LINKING_MODE = -static
	OPTIMIZATION = -O3
	OUT_PATH = $(RELEASE_PATH)
else
	OPTIMIZATION = -Og
	OUT_PATH = $(DEBUG_PATH)
	DEBUG_FLAGS = -g3 -fno-omit-frame-pointer
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


STDLIB_INCLUDE_PATH = \
	-I./src \
	-I./src/stdlib


LIBRARIES_PATH = \
	-L$(SPECTER_LIB_PATH)


LIBRARIES = \
	-l$(SPECTER_LIB_NAME)


CPP_WARNINGS = -Wall -Wno-switch


CPP_FLAGS = $(OPTIMIZATION) $(INCLUDE_PATH) $(CPP_VERSION) $(CPP_WARNINGS) $(DEBUG_FLAGS)
LINK_FLAGS = $(LINKING_MODE) $(LIBRARIES_PATH) $(LIBRARIES)

CPP_STDLIB_FLAGS = -shared -O3 $(STDLIB_INCLUDE_PATH) $(CPP_VERSION) -fPIC


SOURCES = $(shell find src -name "*.cpp")
OBJECTS = $(SOURCES:.cpp=.o)

API_SOURCES = $(shell find src/language/api/ -name "*.cpp")
STDLIB_SOURCES = $(shell find src/language/stdlib/src -name "*.cpp")
STDLIB_SHARED = $(STDLIB_SOURCES:.cpp=.so)

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



build-stdlib: $(STDLIB_SHARED)


$(STDLIB_SHARED): %.so: %.cpp
	@ echo Compiling stdlib file $<
	@ $(CC) $< $(API_SOURCES) $(CPP_STDLIB_FLAGS) -o $(addprefix $(STDLIB_OUTPATH)/, $(notdir $@))





# cleans up build folder
.PHONY:
clean:
	@ rm -r $(DEBUG_PATH)/*
	@ rm -r $(RELEASE_PATH)/*