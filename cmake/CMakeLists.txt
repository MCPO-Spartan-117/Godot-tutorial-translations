cmake_minimum_required(VERSION 3.10)
project(example LANGUAGES CXX)

# Fetch godot-sandbox C++ API
include(FetchContent)
FetchContent_Declare(
	godot-sandbox
	GIT_REPOSITORY https://github.com/libriscv/godot-sandbox.git
	GIT_TAG        main
	GIT_SHALLOW    TRUE
	GIT_SUBMODULES ""
	SOURCE_SUBDIR  "program/cpp/cmake"
)
FetchContent_MakeAvailable(godot-sandbox)

# Find all .cpp files in the CPP directory and compile them
file(GLOB_RECURSE SOURCES ../CPP/*.cpp)
message("${SOURCES}")
foreach(loopvar ${SOURCES})
message("temp ${loopvar}")
get_filename_component(namevar ${loopvar} NAME)
get_filename_component(dirvar ${loopvar} DIRECTORY)
message("${namevar} ${dirvar}")
string(REGEX REPLACE cpp$ elf elfvar ${namevar})
message("${elfvar}")
add_sandbox_program_at(${elfvar} ${dirvar}
	${loopvar}
)
endforeach()
