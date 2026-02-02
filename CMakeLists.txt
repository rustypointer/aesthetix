cmake_minimum_required(VERSION 3.11)
project(aesthetix LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
    ftxui
    GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui.git
    GIT_TAG v5.0.0
)
FetchContent_MakeAvailable(ftxui)

file(GLOB_RECURSE CPP_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(aesthetix ${CPP_SOURCES})

target_include_directories(aesthetix
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/external
)

target_link_libraries(aesthetix PRIVATE
    ftxui::screen
    ftxui::dom
    ftxui::component
)

include(GNUInstallDirs)

install(
  TARGETS aesthetix
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
