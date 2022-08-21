cmake_minimum_required (VERSION 3.8)

project ("gmod_example_module")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/builded)
set(CMAKE_DEBUG_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/builded) 


set(MODULE_NAME "example") # Setting module name
# require("example")


add_subdirectory("include") # Including GMod files


# Choose ONLY ONE example 

 add_subdirectory("FunctionsCreation")
# add_subdirectory("CallingLuaFunctions")
# add_subdirectory("TableCreation")
# add_subdirectory("CallingCustomHook")
# add_subdirectory("Userdata")

set_gmod_suffix_prefix(${MODULE_NAME}) # Setting module name