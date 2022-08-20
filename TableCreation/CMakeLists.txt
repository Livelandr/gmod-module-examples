cmake_minimum_required (VERSION 3.8)



add_library(${MODULE_NAME} SHARED "gmod_tables.cpp") 
target_link_libraries(${MODULE_NAME} "example_module")  
