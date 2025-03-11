cmake_minimum_required(VERSION 2.6 FATAL_ERROR)

project(fuel_assembly)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)

file(GLOB MACRO_FILES "*.mac")

file(COPY ${MACRO_FILES} DESTINATION  ${PROJECT_BINARY_DIR})

add_executable(f_assem f_assem.cc ${sources} ${headers})
target_link_libraries(f_assem ${Geant4_LIBRARIES})

add_custom_target(fuel_assembly DEPENDS f_assem)
