cmake_minimum_required(VERSION 3.13...3.27)

#init pico sdk (must be the first thing done)
include(lib/pico-sdk/pico_sdk_init.cmake)

project("ArtNetNode")

pico_sdk_init()

add_executable(firmware src/main.cpp)


pico_add_extra_outputs(firmware)