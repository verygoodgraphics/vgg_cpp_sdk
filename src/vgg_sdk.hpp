#pragma once

#include <emscripten.h>

#ifdef __cplusplus
#define EXTERN extern "C"
#else
#define EXTERN
#endif

int jsAdd1(int x) EM_IMPORT(jsAdd1);
double jsAdd2(double x) EM_IMPORT(jsAdd2);
