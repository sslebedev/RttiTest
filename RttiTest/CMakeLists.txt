cmake_minimum_required(VERSION 3.6)
### Project settings
set(PROJECT_NAME RttiTest)
project(${PROJECT_NAME})
message(WARNING  "Project: ${PROJECT_NAME}")

### Compiler settings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if (USE_RTTI_LIB)
    message(WARNING "- Uses rtti")
else()
    message(WARNING "- Uses no rtti")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")
endif()

message(WARNING "- Flags: ${CMAKE_CXX_FLAGS}")

### Sources
set(SOURCE_FILES rtti_test.cpp)

### Target
add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})