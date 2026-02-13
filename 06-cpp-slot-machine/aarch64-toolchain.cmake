# aarch64-toolchain.cmake
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR aarch64)

# Compilateurs
set(CMAKE_C_COMPILER aarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER aarch64-linux-gnu-g++)

# Forcer pkg-config Linux
set(PKG_CONFIG_EXECUTABLE "/usr/bin/pkg-config")

# Configuration Multi-arch Ubuntu
set(CMAKE_LIBRARY_ARCHITECTURE aarch64-linux-gnu)
set(CMAKE_FIND_ROOT_PATH /usr/lib/aarch64-linux-gnu /usr/include/aarch64-linux-gnu /usr/aarch64-linux-gnu)

# On autorise la recherche dans les dossiers système de l'hôte pour les libs de la cible
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
