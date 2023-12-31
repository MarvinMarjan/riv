DEP_PATH = dep

SPECTER_PATH = $(DEP_PATH)/specter
SPECTER_INCLUDE_PATH = $(SPECTER_PATH)/include
SPECTER_LIB_PATH = $(SPECTER_PATH)/lib
SPECTER_LIB_NAME = specter


NAME = riv
BUILD_PATH = build
DEBUG_PATH = $(BUILD_PATH)/debug
RELEASE_PATH = $(BUILD_PATH)/release

LIB_PATH = lib

STDLIB_SOURCE_PATH = src/language/stdlib/src
STDLIB_PATH = $(LIB_PATH)/std
STDLIB_SOURCES = $(shell find $(STDLIB_SOURCE_PATH) -name "*.cpp")
STDLIB_SHARED_LIBS = $(STDLIB_SOURCES:.cpp=.so)


# release building by default

ifdef DEBUG
	OUTPUT_PATH = $(DEBUG_PATH)
	CPP_OPTIMIZATION = -Og -fno-omit-frame-pointer -g
	CPP_WARNINGS = -Wall -Wno-switch
else
	OUTPUT_PATH = $(RELEASE_PATH)
	CPP_OPTIMIZATION = -O3
	CPP_WARNINGS = -w
endif


APP_PATH = $(OUTPUT_PATH)/$(NAME)


CC = g++
CPP_VERSION = --std=c++20
CPP_INCLUDE = -Isrc -I$(SPECTER_INCLUDE_PATH)
CPP_LIBRARIES = -L$(SPECTER_LIB_PATH) -l$(SPECTER_LIB_NAME)
CPP_COMPILER_FLAGS = $(CPP_VERSION) $(CPP_INCLUDE) $(CPP_OPTIMIZATION) $(CPP_WARNINGS)
CPP_LINKING_FLAGS = $(CPP_LIBRARIES)


# finds for every file with ".cpp" extension (ignores "stdlib" folder)
SOURCES = $(shell find src -type d -name "stdlib" -prune -o -type f -name "*.cpp" -print)

# allows make to print the current file being compiled
OBJECTS = $(SOURCES:.cpp=.o)
FINAL_OBJECTS = $(addprefix $(OUTPUT_PATH)/, $(notdir $(OBJECTS)))


.PHONY: all
.PHONY: run
.PHONY: runc
.PHONY: build
.PHONY: build-riv
.PHONY: build-stdlib
.PHONY: clean
.PHONY: clean-build
.PHONY: clean-stdlib



all: build





# runs the application
# define "RIV_SOURCE_FILE" to use a ".riv" file as source instead of using the REPL
run: $(APP_PATH)
	@ echo "Running..."
	@ $(APP_PATH) $(RIV_SOURCE_FILE)


runc: build-riv run





build: build-riv build-stdlib

$(APP_PATH):
	@ $(MAKE) build-riv -s


# links object files
build-riv: $(OUTPUT_PATH) $(OBJECTS)
	@ echo "Linking objects..."
	@ $(CC) $(FINAL_OBJECTS) -o $(APP_PATH) $(CPP_LINKING_FLAGS)
	@ echo "Output created at $(OUTPUT_PATH) as $(NAME)"


# compiles source files
$(OBJECTS): %.o: %.cpp
	@ echo "Compiling source file ($<)..."
	@ $(CC) -c $< -o $(OUTPUT_PATH)/$(notdir $@) $(CPP_COMPILER_FLAGS)


# creates output build path
$(OUTPUT_PATH):
	@ echo "Creating output path ($@)..."
	@ mkdir -p $@





build-stdlib: $(STDLIB_PATH) $(STDLIB_SHARED_LIBS)

# compiles source files
$(STDLIB_SHARED_LIBS): %.so: %.cpp
	@ echo "Compiling stdlib source file ($<)..."
	@ $(CC) $< -o $(STDLIB_PATH)/$(notdir $@) $(CPP_COMPILER_FLAGS) -shared


# creates stdlib path
$(STDLIB_PATH):
	@ echo "Creating stdlib path ($@)..."
	@ mkdir -p $@





# removes all
clean: clean-build clean-stdlib


# only removes riv build files
clean-build:
	@ echo "Removing build directory ($(BUILD_PATH))..."
	@ rm -r -f $(BUILD_PATH)


# only removes riv's stdlib build files
clean-stdlib:
	@ echo "Removing stdlib directory ($(STDLIB_PATH))..."
	@ rm -r -f $(STDLIB_PATH)