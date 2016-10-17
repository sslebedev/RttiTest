cmake_minimum_required(VERSION 3.6)
### Project settings
set(PROJECT_NAME Test)
project(${PROJECT_NAME})
message(WARNING "Project: ${PROJECT_NAME}")

### Compiler settings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftemplate-depth=10000000")

if (USE_RTTI_EXE)
    message(WARNING "- Uses rtti")
else()
    message(WARNING "- Uses no rtti")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
endif()

message(WARNING "- Flags: ${CMAKE_CXX_FLAGS}")

### Structure
include_directories(RttiTest)

set(SOURCE_FILES main.cpp)

### Target
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} RttiTest)
target_link_libraries(${PROJECT_NAME} psapi)