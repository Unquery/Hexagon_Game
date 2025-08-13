cmake_minimum_required(VERSION 3.21)
project(hexagon LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        sfml
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.2
)
FetchContent_MakeAvailable(sfml)

add_executable(hexagon
        src/Config.h
        src/Hexagon.h
        src/Hexagon.cpp
        src/UI.h
        src/UI.cpp
        src/Score.h
        src/Score.cpp
        src/Board.h
        src/Board.cpp
        src/Game.h
        src/Game.cpp
        src/main.cpp)
target_link_libraries(hexagon PRIVATE sfml-graphics)

if (MINGW)
    target_link_options(hexagon PRIVATE -static-libstdc++ -static-libgcc)
endif()

if (WIN32)
    add_custom_command(TARGET hexagon POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_RUNTIME_DLLS:hexagon> $<TARGET_FILE_DIR:hexagon>
            COMMAND_EXPAND_LISTS
    )
    add_custom_command(TARGET hexagon POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:hexagon>/assets
    )

endif()
