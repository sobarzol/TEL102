cmake_minimum_required(VERSION 3.31)
project(TEL102_main)

set(CMAKE_CXX_STANDARD 20)

add_executable(TEL102_main main.cpp
        station.cpp
        station.h
        dia.cpp
        dia.h
        metrounit.cpp
        metrounit.h
        passenger.cpp
        passenger.h
        schedule.cpp
        schedule.h
        timecontroller.cpp
        timecontroller.h)
