cmake_minimum_required(VERSION 3.24)
project(LazerAssault CXX) # Replace with the name of your game


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Specify the engine version (via github tag)
set(POTATO_ENGINE_VERSION "v2.0.4-beta") 

# include the engine module
include(FetchContent)
FetchContent_Declare(
    PotatoEngine
    URL "https://github.com/powatos/Potato-Engine/releases/download/${POTATO_ENGINE_VERSION}/PotatoEngine.zip"
)
FetchContent_MakeAvailable(PotatoEngine)

# Ensure all source code is captured under SOURCES
file(GLOB_RECURSE SOURCES 
    "src/*.h"
    "src/*.hpp"
    "src/*.cpp"
)

# Ensure the executable name is consistent
add_executable(LazerAssaultGame ${SOURCES})

target_compile_options(LazerAssaultGame PUBLIC /utf-8)

# Include the source directory for header files
target_include_directories(LazerAssaultGame PRIVATE src/)

# Link engine libraries to the game
target_link_libraries(LazerAssaultGame PRIVATE PotatoEngine::PotatoEngine)

# Copy default engine folders to the root (optional but reccomended)
PotatoEngineDefaults(LazerAssaultGame)