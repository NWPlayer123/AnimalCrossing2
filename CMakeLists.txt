cmake_minimum_required(VERSION 3.8)

include(cmake/CodeWarrior.cmake)
set(CMAKE_USER_MAKE_RULES_OVERRIDE "cmake/FixExtension.cmake")

project(GAEJ01)

#note to self: __declspec(section ".sdata")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}") #-w all -w nonotused
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG}") #TODO: add more?
#set(CMAKE_C_FLAGS_RELEASE "-O0 -opt nodead -sdata 48 -sdata2 4 -w off")
set(CMAKE_C_FLAGS_RELEASE "-once -O4,p -opt nodeadcode -sdata 48 -sdata2 6 -multibyte -rostr -use_lmw_stmw on -w all -w nonotused -w nounusedarg -w nopadding")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}") # -w all
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}") #TODO: add more?
#set(CMAKE_CXX_FLAGS_RELEASE "-O0 -opt nodead -sdata 48 -sdata2 4 -w off")
set(CMAKE_CXX_FLAGS_RELEASE "-once -O4,p -opt nodeadcode -sdata 48 -sdata2 6 -multibyte -rostr -use_lmw_stmw on -w all -w nonotused -w nounusedarg -w nopadding") #sdata 0x30 based on memory.c size_table, TODO: update
set(CMAKE_C_LINK_FLAGS "${CMAKE_C_LINK_FLAGS} -lcf ${PROJECT_SOURCE_DIR}/linker/linker.lcf -map ${PROJECT_NAME}.map")
set(CMAKE_CXX_LINK_FLAGS "${CMAKE_CXX_LINK_FLAGS} -lcf ${PROJECT_SOURCE_DIR}/linker/linker.lcf -map ${PROJECT_NAME}.map")

include_directories(${SDK_INC_PATH})
include_directories(${MW_INC_PATH})
include_directories(${MUSYX_INC_PATH})
include_directories(include)

add_executable(${PROJECT_NAME}.elf
	source/boot.c
	 "source/libforest/ReconfigBATs.c" "include/libforest/ReconfigBATs.h" "source/libultra/gettime.c" "include/libultra/gettime.h" "source/libultra/ultra.c" "include/libultra/ultra.h")