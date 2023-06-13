cmake_minimum_required(VERSION 3.8)
project(vgg_sdk_example)
set(CMAKE_CXX_STANDARD 17)


add_executable(demo
  example/main.cpp
  src/vgg_sdk.cpp
)

target_include_directories(demo PRIVATE
  src
)

if (EMSCRIPTEN)
  set(CMAKE_EXECUTABLE_SUFFIX ".mjs") # to export es6 module

  target_compile_options(demo PRIVATE 
    -fexceptions
  )

  target_link_options(demo PRIVATE
    -fexceptions
    -lembind
    -sMODULARIZE=1
    -sEXPORT_NAME=createDemoModule 
    -O3 
    -sASYNCIFY
    --no-entry
  )
endif()