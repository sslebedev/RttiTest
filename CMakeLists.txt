cmake_minimum_required(VERSION 3.6)
### Project settings
set(PROJECT_NAME Rtti)
project(${PROJECT_NAME})
message(WARNING "Project: ${PROJECT_NAME}")

### Options
option(USE_RTTI_EXE "Exe with RTTI" ON)
option(USE_RTTI_LIB "Lib with RTTI" ON)
## (ON, ON) - OK
## (OFF, ON) - compile error
## (ON, OFF) - segmentation fault
## (OFF, OFF) - compile error

#add_definitions(-DCOMPILE_CHECK) # compile or performance
add_definitions(-DPERFORMANCE_DYNAMIC) # for performance dynamyc or static

## DYNAMIC with RTTI 63 239 / 2 290
## STATIC  with RTTI 63 129 / 1 430
## STATIC  no   RTTI 62 364 / 1 430

### Structure
include_directories(RttiTest)

add_subdirectory(RttiTest)
add_subdirectory(Test)