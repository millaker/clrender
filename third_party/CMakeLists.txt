# gmtl
add_library(gmtl INTERFACE)
target_include_directories(gmtl
  INTERFACE ${CMAKE_CURRENT_LIST_DIR})

# stb image loader and writer
add_library(stb INTERFACE)
target_include_directories(stb INTERFACE
  INTERFACE ${CMAKE_CURRENT_LIST_DIR})

# fmt
add_subdirectory(fmt-11.1.4)
