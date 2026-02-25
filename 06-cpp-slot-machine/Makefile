# Makefile for Slot Machine - Embedded Linux (RPi 4)
# Targeted for KMSDRM / SDL3

PROJECT = slot_machine_rpi
BUILD_DIR = build
SRC_DIR = .
UI_DIR = UI

# --- Paths ---
EXTERNAL_DIR = $(CURDIR)/../external
SDL_DIR = $(EXTERNAL_DIR)/SDL
SDL_BUILD_DIR = $(SDL_DIR)/build-rpi
SDL_TTF_DIR = $(EXTERNAL_DIR)/SDL_ttf
SDL_TTF_BUILD_DIR = $(SDL_TTF_DIR)/build-rpi
STAGING_DIR = $(SDL_BUILD_DIR)/staging

# --- Toolchain ---
CXX = aarch64-linux-gnu-g++
TOOLCHAIN = aarch64-toolchain.cmake

# --- Compilation Flags ---
CXXFLAGS = -Wall -Wextra -std=c++17 -O3 \
           -I$(STAGING_DIR)/include \
           -I$(STAGING_DIR)/include/SDL3 \
           -I$(UI_DIR) \
           -I$(SRC_DIR)

# --- Linker Flags ---
LDFLAGS = -L$(STAGING_DIR)/lib \
          -L/usr/lib/aarch64-linux-gnu \
          -Wl,--start-group \
          -lSDL3 \
          -lSDL3_ttf \
          -lgbm \
          -ldrm \
          -lEGL \
          -lGLESv2 \
          -ludev \
          -lpthread \
          -ldl \
          -lm \
          -Wl,--end-group

# --- Source Files ---
SRCS = main.cpp \
       GameEngine.cpp \
       PayoutCalculator.cpp \
       Reel.cpp \
       RNG.cpp \
       $(UI_DIR)/SdlUi.cpp

OBJS = $(SRCS:%.cpp=$(BUILD_DIR)/%.o)

# --- Rules ---

all: $(PROJECT)

$(PROJECT): $(OBJS)
	@echo "Linking $@..."
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)
	@echo "Build complete for RPi."

$(BUILD_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "Compiling $<..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build SDL3 for RPi with explicit Input support (udev/libinput)
sdl_build:
	@echo "Cleaning and Rebuilding SDL3 for RPi (KMSDRM + INPUT)..."
	rm -rf $(SDL_BUILD_DIR)
	@mkdir -p $(SDL_BUILD_DIR)
	cd $(SDL_BUILD_DIR) && \
	export PKG_CONFIG_LIBDIR=/usr/lib/aarch64-linux-gnu/pkgconfig:/usr/share/pkgconfig && \
	export PKG_CONFIG_SYSROOT_DIR=/ && \
	cmake $(SDL_DIR) -B . \
		-DCMAKE_TOOLCHAIN_FILE=$(CURDIR)/$(TOOLCHAIN) \
		-DCMAKE_INSTALL_PREFIX=$(STAGING_DIR) \
		-DSDL_STATIC=ON \
		-DSDL_SHARED=OFF \
		-DSDL_TEST=OFF \
		-DSDL_X11=OFF \
		-DSDL_WAYLAND=OFF \
		-DSDL_KMSDRM=ON \
		-DSDL_UDEV=ON \
		-DSDL_LIBINPUT=ON \
		-DSDL_OPENGL_EGL=ON \
		-DSDL_OPENGLES=ON \
		-DSDL_UNIX_CONSOLE_BUILD=ON
	cmake --build $(SDL_BUILD_DIR) --target install -j$$(nproc)

# Build SDL3_ttf for RPi
sdl_ttf_build:
	@echo "Building SDL3_ttf for RPi..."
	@mkdir -p $(SDL_TTF_BUILD_DIR)
	cd $(SDL_TTF_BUILD_DIR) && \
	export PKG_CONFIG_LIBDIR=/usr/lib/aarch64-linux-gnu/pkgconfig:/usr/share/pkgconfig && \
	export PKG_CONFIG_SYSROOT_DIR=/ && \
	cmake $(SDL_TTF_DIR) -B . \
		-DCMAKE_TOOLCHAIN_FILE=$(CURDIR)/$(TOOLCHAIN) \
		-DCMAKE_INSTALL_PREFIX=$(STAGING_DIR) \
		-DCMAKE_PREFIX_PATH=$(STAGING_DIR) \
		-DSDL3_DIR=$(STAGING_DIR)/lib/cmake/SDL3 \
		-DSDLTTF_SAMPLES=OFF \
		-DSDLTTF_VENDORED=ON \
		-DBUILD_SHARED_LIBS=OFF
	cmake --build $(SDL_TTF_BUILD_DIR) --target install -j$$(nproc)

clean:
	rm -rf $(BUILD_DIR) $(PROJECT)
	@echo "Cleaned project files."

clean-all: clean
	rm -rf $(SDL_BUILD_DIR) $(SDL_TTF_BUILD_DIR)
	@echo "Cleaned everything (including SDL builds)."

# Build all dependencies
deps: sdl_build sdl_ttf_build

.PHONY: all clean clean-all sdl_build sdl_ttf_build deps
