add_executable(clrender
  main.cc
  common/ObjParser.cc
  common/FrameBuffer.cc
)

target_include_directories(clrender
  PRIVATE common
  PRIVATE clrender
  PRIVATE cxxrender
)

target_link_libraries(clrender
  PRIVATE stb
  PRIVATE fmt::fmt
)

if(CMAKE_BUILD_TYPE STREQUAL Debug)
  target_compile_options(clrender PRIVATE -fsanitize=address)
  target_link_options(clrender PRIVATE -fsanitize=address)
endif()
