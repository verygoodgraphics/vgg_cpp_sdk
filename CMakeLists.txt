cmake_minimum_required(VERSION 3.8)
project(vgg_sdk_example)
set(CMAKE_CXX_STANDARD 17)


add_executable(demo
  example/main.cpp
)

target_include_directories(demo PRIVATE
  src
)

if (EMSCRIPTEN)
  target_compile_options(demo PRIVATE 
    -fexceptions
  )

  target_link_options(demo PRIVATE
    -fexceptions
    -lembind
    -sSTANDALONE_WASM
    -sMODULARIZE=1
    -sEXPORT_NAME=createDemoModule 
    --no-entry
    --js-library ${CMAKE_SOURCE_DIR}/src/vgg_sdk.js
    --pre-js ${CMAKE_SOURCE_DIR}/src/vgg_sdk_bridge.js
  )
endif()