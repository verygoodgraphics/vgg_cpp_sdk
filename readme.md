# Prerequisites
* Emscripten
* CMake
* Python, run http server for testing

# Build 

```
$ cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=/path/to/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake -S . -B build.wasm 
$ cmake --build build.wasm -j8 -t demo
```

# Run

```
$ ./test/run_http_server.sh
```

Open [test](http://localhost:8000/test/) page in browser, and check logs in browser's console.