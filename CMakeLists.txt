cmake_minimum_required(VERSION 3.16)
project(Game04 LANGUAGES CXX)

# require C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# ensure -std=c++XX instead of -std=g++xx
set(CMAKE_CXX_EXTENSIONS OFF)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wno-reorder")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-reorder")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
#option(SFML_BUILD_AUDIO "Build audio" OFF)
#option(SFML_BUILD_NETWORK "Build network" OFF)
FetchContent_MakeAvailable(SFML)

## Adding imggui and imgui-sfml
FetchContent_Declare(
    imgui
#    URL "https://github.com/ocornut/imgui/archive/v1.89.zip"
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG     v1.91.0)

# Or by tag...
FetchContent_Declare(
    imgui-sfml
    GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
    GIT_TAG        2.6.x
    # GIT_COMMIT 5f54b69b6aee18db846c81633f86f78c2586dded
    # ^ or like this - sometimes it's better because FetchContent won't look
    # into remote to see if branch head was updated or not - good for stable
    # tags like 'vX.X' corresponding to releases
)

## finally, let's build
# Dear ImGui
FetchContent_MakeAvailable(imgui)

# ImGui-SFML
set(IMGUI_DIR ${imgui_SOURCE_DIR})
option(IMGUI_SFML_FIND_SFML "Use find_package to find SFML" OFF)
#option(IMGUI_SFML_IMGUI_DEMO "Build imgui_demo.cpp" ON)

FetchContent_MakeAvailable(imgui-sfml)

include_directories(include)

# -- create a lib imgui_lib --
#file(GLOB_RECURSE IMGUI_SRC imgui/*.cpp) # add src files to var SRC_FILES
#add_library(imgui_lib STATIC ${IMGUI_SRC}) # include src files
#include_directories(imgui) # include header files
# -- end of create a lib

add_executable(main
    src/main.cpp
    src/load_files.cpp
    src/initial_code.cpp
    src/assignment.cpp
    src/experiments.cpp
    src/ui.cpp
    src/entities.cpp
    include/entities.h
    include/experiments.h
    include/initial_code.h
    include/assignment.h
    include/load_files.h
    include/ui.h
    include/img_gui_play.h
    src/img_gui_play.cpp
)


# Yep, that's it!
target_link_libraries(main PUBLIC ImGui-SFML::ImGui-SFML)

#target_link_libraries(main PUBLIC imgui_lib) # add a imgui_lib
target_link_libraries(main PRIVATE sfml-graphics)
target_compile_features(main PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET main
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
        VERBATIM)
endif()
