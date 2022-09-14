# Author: Claudio Correa, 2021/05/15

# https://cmake.org/examples
# cmake -S . -B build
# cmake --build build
# cmake --build build --target test
# or
# mkdir build && cd build
# cmake .. && make VERBOSE=1
# make test && doas make install/strip

cmake_minimum_required(VERSION 3.14...3.18)

project(MyProj
  VERSION
    1.0
  DESCRIPTION
    "Very basic image filters"
  LANGUAGES
    C CXX
)

# Minimal STATIC lib
# add_library(libmyimg lib/funcoesarit.c lib/funcoesaux.c)
# add_executable(img src/imguladora.c)
# target_link_libraries(img libmyimg)
# Dependences
# find_library(m_library NAMES m PATHS /usr/local/lib)
# target_link_libraries(cac ${m_library})
# find_path(m_include NAMES math.h PATHS /usr/local/include)
# include_directories(${m_include})

set(CMAKE_BUILD_TYPE Release)
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

include(GNUInstallDirs)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-omit-frame-pointer -DDBG")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wunused -O2 -std=c11 -static")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/lib)

message(${CMAKE_BINARY_DIR})

# ls -1 src/*.c
set(SOURCES src/principal.c)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(img ${SOURCES})
target_link_libraries(img myimg)

# ls -1 lib/*.c
add_library(myimg STATIC lib/showheader.c lib/border.c lib/negative.c lib/gradient.c)
# add_library(myimg SHARED lib/funcoesarit.c lib/funcoesaux.c)

set_target_properties(myimg PROPERTIES
    OUTPUT_NAME myimg
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER include/showheader.h)

target_include_directories(myimg PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)

configure_file(myimg.pc.in myimg.pc @ONLY)

install(TARGETS myimg EXPORT MyImgLibConfig
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(FILES ${CMAKE_BINARY_DIR}/myimg.pc
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)

install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME})

# install(EXPORT MyImgLibConfig DESTINATION share/MyCaclLib/cmake)
# export(TARGETS ${PROJECT_NAME} FILE MyImgLibConfig.cmake)

