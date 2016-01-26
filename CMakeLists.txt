project(mabr)
cmake_minimum_required(VERSION 3.0)

set(SOURCES
    main.c
    mabr.cpp
    matrix.cpp
    alignment.cpp
    processor.cpp
    block.cpp
    blocktree.cpp
    linear_processor.cpp
    amino_group.cpp
)

set(CMAKE_C_FLAGS "-ansi -Wreturn-type")
set(CMAKE_CXX_FLAGS "-std=c++11 -Wreturn-type")
if(NOT WIN32)
    set(CMAKE_INSTALL_PREFIX "/usr")
endif()


find_library(EMBOSS_ACD NAMES acd HINTS ${EMBOSS_LIBDIR})
find_library(EMBOSS_AJAX NAMES ajax HINTS ${EMBOSS_LIBDIR})
find_library(EMBOSS_PCRE NAMES epcre HINTS ${EMBOSS_LIBDIR})
find_library(EMBOSS_NUCLEUS NAMES nucleus HINTS ${EMBOSS_LIBDIR})
find_library(EMBOSS_AJAXG NAMES ajaxg HINTS ${EMBOSS_LIBDIR})
find_library(EMBOSS_AJAXDB NAMES ajaxdb HINTS ${EMBOSS_LIBDIR})
find_library(EMBOSS_PLPLOT NAMES eplplot HINTS ${EMBOSS_LIBDIR})
find_library(EMBOSS_ENSEMBL NAMES ensembl HINTS ${EMBOSS_LIBDIR})
# find_library(EMBOSS_ZLIB NAMES ezlib HINTS ${EMBOSS_LIBDIR})
# find_library(EMBOSS_EXPAT NAMES eexpat HINTS ${EMBOSS_LIBDIR})

set(EMBOSS_LIBS 
    ${EMBOSS_NUCLEUS} 
    ${EMBOSS_ACD} 
    ${EMBOSS_AJAX} 
    ${EMBOSS_AJAXDB} 
    ${EMBOSS_AJAXG} 
    ${EMBOSS_PCRE} 
    ${EMBOSS_ENSEMBL} 
    ${EMBOSS_PLPLOT} 
#     ${EMBOSS_EXPAT} 
#     ${EMBOSS_ZLIB}
)

find_path(EMBOSS_INCLUDE_DIR emboss.h HINTS ${EMBOSS_INCLUDEDIR} PATH_SUFFIXES EMBOSS)
find_path(EMBOSS_PCRE_INCLUDE_DIR pcre_config.h HINTS ${EMBOSS_INCLUDEDIR} PATH_SUFFIXES EMBOSS/epcre)
find_path(EMBOSS_PLPLOT_INCLUDE_DR plplot.h HINTS ${EMBOSS_INCLUDEDIR} PATH_SUFFIXES EMBOSS/eplplot)



include_directories(${EMBOSS_INCLUDE_DIR})
include_directories(${EMBOSS_PCRE_INCLUDE_DIR})
include_directories(${EMBOSS_PLPLOT_INCLUDE_DIR})

add_executable(mabr ${SOURCES})
target_link_libraries(mabr ${EMBOSS_LIBS})

install(TARGETS mabr RUNTIME DESTINATION bin)
install(FILES mabr.acd DESTINATION share/EMBOSS/acd)
