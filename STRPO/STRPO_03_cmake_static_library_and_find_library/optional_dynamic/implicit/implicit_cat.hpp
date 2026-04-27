#pragma once

#if defined(_WIN32)
  #if defined(IMPLICIT_CAT_EXPORTS)
    #define IMPLICIT_CAT_API __declspec(dllexport)
  #else
    #define IMPLICIT_CAT_API __declspec(dllimport)
  #endif
#else
  #define IMPLICIT_CAT_API
#endif

IMPLICIT_CAT_API void implicit_cat_print(const char* text);
