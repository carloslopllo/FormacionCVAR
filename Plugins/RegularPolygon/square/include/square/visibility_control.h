#ifndef SQUARE__VISIBILITY_CONTROL_H_
#define SQUARE__VISIBILITY_CONTROL_H_

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define SQUARE_EXPORT __attribute__ ((dllexport))
    #define SQUARE_IMPORT __attribute__ ((dllimport))
  #else
    #define SQUARE_EXPORT __declspec(dllexport)
    #define SQUARE_IMPORT __declspec(dllimport)
  #endif
  #ifdef SQUARE_BUILDING_LIBRARY
    #define SQUARE_PUBLIC SQUARE_EXPORT
  #else
    #define SQUARE_PUBLIC SQUARE_IMPORT
  #endif
  #define SQUARE_PUBLIC_TYPE SQUARE_PUBLIC
  #define SQUARE_LOCAL
#else
  #define SQUARE_EXPORT __attribute__ ((visibility("default")))
  #define SQUARE_IMPORT
  #if __GNUC__ >= 4
    #define SQUARE_PUBLIC __attribute__ ((visibility("default")))
    #define SQUARE_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define SQUARE_PUBLIC
    #define SQUARE_LOCAL
  #endif
  #define SQUARE_PUBLIC_TYPE
#endif

#endif  // SQUARE__VISIBILITY_CONTROL_H_
