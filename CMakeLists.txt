cmake_minimum_required(VERSION 3.24)
project(hexprojektfinal)

set(CMAKE_CXX_STANDARD 20)
set(BUILD_SHARED_LIBS FALSE)

include(FetchContent)
set(SFML_VERSION "2.6.x")

FetchContent_Declare(
        sfml
        URL https://github.com/SFML/SFML/archive/refs/tags/2.5.1.zip
        URL_MD5 2c4438b3e5b2d81a6e626ecf72bf75be
)
FETCHCONTENT_MAKEAVAILABLE(sfml)

add_executable(hexprojektfinal main.cpp Hex.cpp Hex.h DostepnePola.cpp DostepnePola.h Gra.cpp Gra.h Wyniki.cpp Wyniki.h)
target_compile_definitions(hexprojektfinal PRIVATE SFML_STATIC)
target_link_libraries(hexprojektfinal sfml-system sfml-window sfml-graphics)