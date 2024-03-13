#ifndef MAXIMUM__VISIBILITY_CONTROL_H_
#define MAXIMUM__VISIBILITY_CONTROL_H_

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define MAXIMUM_EXPORT __attribute__ ((dllexport))
    #define MAXIMUM_IMPORT __attribute__ ((dllimport))
  #else
    #define MAXIMUM_EXPORT __declspec(dllexport)
    #define MAXIMUM_IMPORT __declspec(dllimport)
  #endif
  #ifdef MAXIMUM_BUILDING_LIBRARY
    #define MAXIMUM_PUBLIC MAXIMUM_EXPORT
  #else
    #define MAXIMUM_PUBLIC MAXIMUM_IMPORT
  #endif
  #define MAXIMUM_PUBLIC_TYPE MAXIMUM_PUBLIC
  #define MAXIMUM_LOCAL
#else
  #define MAXIMUM_EXPORT __attribute__ ((visibility("default")))
  #define MAXIMUM_IMPORT
  #if __GNUC__ >= 4
    #define MAXIMUM_PUBLIC __attribute__ ((visibility("default")))
    #define MAXIMUM_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define MAXIMUM_PUBLIC
    #define MAXIMUM_LOCAL
  #endif
  #define MAXIMUM_PUBLIC_TYPE
#endif

#endif  // MAXIMUM__VISIBILITY_CONTROL_H_
