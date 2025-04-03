add_executable(clrender
  main.cc
  common/ObjParser.cc
  common/FrameBuffer.cc
  cxxrender/CXXPipe.cc
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

if(CLRENDER_ASAN)
  message(STATUS "Address santizer enabled")
  target_compile_options(clrender PRIVATE -fsanitize=address)
  target_link_options(clrender PRIVATE -fsanitize=address)
endif()
