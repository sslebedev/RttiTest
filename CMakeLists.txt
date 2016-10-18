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
#add_definitions(-DMULTY_TYPE) # use multiple time generator

## 1 type:
## Dynamic RTTI:   Cast ~= 0.1634850, Mem ~= 205107200
## Static RTTI:    Cast ~= 0.0135471, Mem ~= 205107200
## Static no RTTI: Cast ~= 0.0137099, Mem ~= 205090816

## 1000 types:
## Dynamic RTTI:   Cast ~= 0.2980080, Mem ~= 205193216
## Static RTTI:    Cast ~= 0.0177365, Mem ~= 205148160
## Static no RTTI: Cast ~= 0.0168343, Mem ~= 205119488

## Targets (exe / lib):
## DYNAMIC with RTTI 63 239 / 2 290
## STATIC  with RTTI 63 129 / 1 430
## STATIC  no   RTTI 62 364 / 1 430

### Structure
include_directories(RttiTest)

add_subdirectory(RttiTest)
add_subdirectory(Test)
