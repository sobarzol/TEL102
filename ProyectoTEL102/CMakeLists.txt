cmake_minimum_required(VERSION 3.16)

project(ProyectoTEL102 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ProyectoTEL102 main.cpp
    metrounit.h metrounit.cpp
    passenger.h passenger.cpp
    station.h station.cpp
    timecontroller.h timecontroller.cpp)

include(GNUInstallDirs)
install(TARGETS ProyectoTEL102
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
