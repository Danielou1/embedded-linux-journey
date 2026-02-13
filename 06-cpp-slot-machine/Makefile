# Makefile for the C++ Slot Machine project

PROJECT_NAME = slot_machine
SRC_DIR = .
BUILD_DIR = build
ROOT_DIR = $(CURDIR)
EXTERNAL_DIR = $(ROOT_DIR)/../external
SDL_DIR = $(EXTERNAL_DIR)/SDL
SDL_BUILD_DIR_RPI = $(SDL_DIR)/build-rpi

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/UI/*.cpp)

# Object files
OBJS_NATIVE = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))
OBJS_RPI = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%_rpi.o, $(SRCS))

# Path to the static SDL library
SDL2_LIB_RPI = $(SDL_BUILD_DIR_RPI)/lib/libSDL3.a
SDL2_INCLUDE_DIR_RPI = $(SDL_BUILD_DIR_RPI)/include

# --- Compilers & Flags ---
CXX_NATIVE = g++
CXXFLAGS_NATIVE = -Wall -Wextra -std=c++17 
LDFLAGS_NATIVE = -lSDL3

CXX_RPI = aarch64-linux-gnu-g++
# On ajoute explicitement les includes system arm64 pour éviter les "file not found"
CXXFLAGS_RPI = -Wall -Wextra -std=c++17 -I$(SDL2_INCLUDE_DIR_RPI) -I/usr/include/aarch64-linux-gnu
LDFLAGS_RPI = -L$(SDL_BUILD_DIR_RPI)/lib -L/usr/lib/aarch64-linux-gnu -lSDL3 -lgbm -ldrm -lGLESv2 -lpthread -ldl

.PHONY: all rpi clean build_sdl_rpi

all: $(BUILD_DIR)/$(PROJECT_NAME)_x86

$(BUILD_DIR)/$(PROJECT_NAME)_x86: $(OBJS_NATIVE)
	@mkdir -p $(dir $@)
	$(CXX_NATIVE) $(OBJS_NATIVE) -o $@ $(LDFLAGS_NATIVE)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX_NATIVE) $(CXXFLAGS_NATIVE) -c $< -o $@

rpi: build_sdl_rpi $(BUILD_DIR)/$(PROJECT_NAME)_rpi

$(BUILD_DIR)/$(PROJECT_NAME)_rpi: $(OBJS_RPI)
	@echo "Linking RPi executable..."
	$(CXX_RPI) $(OBJS_RPI) -o $@ $(LDFLAGS_RPI)

$(BUILD_DIR)/%_rpi.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling $< for RPi..."
	$(CXX_RPI) $(CXXFLAGS_RPI) -c $< -o $@

build_sdl_rpi: $(SDL2_LIB_RPI)

$(SDL2_LIB_RPI):
	@echo "Configuring and Building SDL3 for RPi (KMSDRM Meticulous)..."
	@mkdir -p $(SDL_BUILD_DIR_RPI)
	cd $(SDL_BUILD_DIR_RPI) && \
	export PKG_CONFIG_PATH=/usr/lib/aarch64-linux-gnu/pkgconfig:/usr/share/pkgconfig && \
	cmake -S $(SDL_DIR) -B . \
		-DCMAKE_TOOLCHAIN_FILE=$(ROOT_DIR)/aarch64-toolchain.cmake \
		-DCMAKE_INSTALL_PREFIX=. \
		-DSDL_STATIC=ON -DSDL_SHARED=OFF \
		-DSDL_TEST=OFF \
		-DSDL_VIDEO_X11=OFF \
		-DSDL_VIDEO_WAYLAND=OFF \
		-DSDL_VIDEO_KMSDRM=ON \
		-DSDL_OPENGLES=ON \
		-DSDL_UNIX_CONSOLE_BUILD=ON \
		-DGBM_LIBRARY=/usr/lib/aarch64-linux-gnu/libgbm.so \
		-DGBM_INCLUDE_DIR=/usr/include \
		-DLIBDRM_LIBRARY=/usr/lib/aarch64-linux-gnu/libdrm.so \
		-DLIBDRM_INCLUDE_DIR=/usr/include/libdrm
	cmake --build $(SDL_BUILD_DIR_RPI) --target install -- -j$$(nproc)

clean:
	@rm -rf $(BUILD_DIR)
	@rm -rf $(SDL_BUILD_DIR_RPI)
	@echo "Cleaned."
