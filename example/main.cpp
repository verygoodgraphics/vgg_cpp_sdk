#include "vgg_sdk.hpp"

#include <emscripten.h>

#include <iostream>

#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN
#endif

EXTERN EMSCRIPTEN_KEEPALIVE int update(int x) {
  std::cout << "cpp: update, in, parameter x: " << x << std::endl;

  auto ret1 = jsAdd1(x);
  std::cout << "cpp: update, jsAdd1 result: " << ret1 << std::endl;

  auto ret2 = jsAdd2(x);
  std::cout << "cpp: update, jsAdd2 result: " << ret2 << std::endl;

  std::cout << "cpp: update, jsAdd11 result: " << jsAdd11(1) << std::endl;

  auto ret = ret1 + ret2;
  std::cout << "cpp: update, out, return: " << ret << std::endl;
  return ret;
}