cmake_minimum_required(VERSION 3.7)
project(Arcade)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXE_LINKER_FLAGS "-lSDL_ttf")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "/usr/share/cmake-3.7/Modules/")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "/usr/share/SFML/cmake/Modules/")

FIND_PACKAGE(SFML 2 COMPONENTS graphics window system REQUIRED)
FIND_PACKAGE(SDL2 REQUIRED sdl2)
FIND_PACKAGE(PkgConfig REQUIRED)

INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR} ${GTK3_INCLUDE_DIR})

add_executable(Arcade
            main.cpp
        include/Core.hpp
        src/Core.cpp
        include/Color.hpp
        src/Color.cpp
        fonts/arial.ttf
        include/IGameLib.hpp
        include/IGraphicLib.hpp
        include/Keys.hpp
        include/PixelBox.hpp
        src/PixelBox.cpp
        include/TextBox.hpp
        src/TextBox.cpp
        include/Vect.hpp
        lib/SDL/SDL.cpp
        lib/SDL/SDL.hpp
        lib/SFML/SFML.hpp
        lib/SFML/SFML.cpp
        lib/NCurses/NCursesLib.hpp
        lib/NCurses/NCursesLib.cpp
        games/snake/Snake.cpp
        games/snake/Snake.hpp)

TARGET_LINK_LIBRARIES(Arcade ${SFML_LIBRARIES} ${SFML_DEPENDENCIES}
        ${CMAKE_DL_LIBS} ${SDL2_LIBRARIES} ${SDL2_DEPENDENCIES})