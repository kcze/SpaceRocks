cmake_minimum_required(VERSION 3.11)
# Require modern C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(SpaceRocks)

#### Setup Directories ####
#Main output directory
set(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Ouput all DLLs from all libs into main build folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

#### Add External Dependencies ####
# SFML - graphics library
add_subdirectory("lib/sfml" EXCLUDE_FROM_ALL)
#include_directories("lib/sfml/include")
set(SFML_INCS "lib/sfml/include")
link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

# B2D - Box2D phyics library
add_subdirectory("lib/b2d/Box2D" EXCLUDE_FROM_ALL)
#include_directories("lib/b2d/Box2D/")
set(B2D_INCS "lib/b2d/Box2D/")

#### Add Engine and our own library projects####

file(GLOB_RECURSE RESOURCE_FILES "res/*.*")

####
file(GLOB_RECURSE SOURCE_FILES engine/*.cpp engine/*.h)
add_library(lib_engine STATIC ${SOURCE_FILES} ${RESOURCE_FILES})
target_include_directories(lib_engine INTERFACE "${CMAKE_SOURCE_DIR}/engine/" PUBLIC SYSTEM ${B2D_INCS} )
target_link_libraries(lib_engine lib_maths lib_ecm Box2D sfml-graphics sfml-audio)

## Maths lib
add_library(lib_maths INTERFACE)
target_sources(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/lib_maths/maths.h")
target_include_directories(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/lib_maths" SYSTEM INTERFACE ${SFML_INCS})

## ECM lib
file(GLOB_RECURSE SOURCE_FILES lib_ecm/*.cpp lib_ecm/*.h)
add_library(lib_ecm STATIC ${SOURCE_FILES})
target_include_directories(lib_ecm INTERFACE "${CMAKE_SOURCE_DIR}/lib_ecm" )
target_link_libraries(lib_ecm PRIVATE lib_maths)

## SpaceRocks
file(GLOB_RECURSE SOURCES space_rocks/*.cpp space_rocks/*.h)
file(GLOB_RECURSE CMPNTS space_rocks/components/*.cpp space_rocks/components/*.h)
file(GLOB_RECURSE SCENES space_rocks/scenes/*.cpp space_rocks/scenes/*.h)
add_executable(SPACE_ROCKS ${SOURCES} ${RESOURCE_FILES})
source_group("components" FILES ${CMPNTS})
source_group("resources" FILES ${RESOURCE_FILES})
#target_include_directories(SPACE_ROCKS SYSTEM PRIVATE ${SFML_INCS} ${B2D_INCS})
target_link_libraries(SPACE_ROCKS lib_engine)
set(EXECUTABLES ${EXECUTABLES} SPACE_ROCKS)

#### Target for copying resources to build dir####
  add_custom_target(copy_resources ALL 
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/res" ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>/res)
	
#### Link Dependencies ####
foreach (exe ${EXECUTABLES})
  #Set working directory to build dir in visual studio
  set_target_properties(${exe} PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration)
  )

  #Add all SFML libs.
  target_link_libraries(${exe}
    lib_maths
    optimized sfml-audio debug sfml-audio-d
    optimized sfml-window debug sfml-window-d
    optimized sfml-system debug sfml-system-d
    optimized sfml-graphics debug sfml-graphics-d
    optimized sfml-main
  )
  
  if(MSVC) # Hide Console in release builds
  set_target_properties(${exe} PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS")
  endif(MSVC)

  add_dependencies(${exe} sfml-graphics sfml-audio copy_resources)
endforeach ()