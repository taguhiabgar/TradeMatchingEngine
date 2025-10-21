cmake_minimum_required(VERSION 3.20)
project(TradeMatchingEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${PROJECT_SOURCE_DIR}/src)

# CONFIGURE_DEPENDS ensures new files are detected without rerunning cmake manually
file(GLOB ENGINE_SOURCES CONFIGURE_DEPENDS "src/engine/*.cpp" "src/engine/*.h")
file(GLOB UTILS_SOURCES CONFIGURE_DEPENDS "src/utils/*.cpp" "src/utils/*.h")

set(MAIN_SOURCE src/main.cpp)

add_executable(trade-matching-engine ${MAIN_SOURCE} ${ENGINE_SOURCES} ${UTILS_SOURCES})


# Compiler warnings and errors
if(MSVC)
    target_compile_options(trade-matching-engine PRIVATE /W4 /WX)
else()
    target_compile_options(trade-matching-engine PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()
