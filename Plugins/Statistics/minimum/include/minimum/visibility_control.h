#ifndef MINIMUM__VISIBILITY_CONTROL_H_
#define MINIMUM__VISIBILITY_CONTROL_H_

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define MINIMUM_EXPORT __attribute__ ((dllexport))
    #define MINIMUM_IMPORT __attribute__ ((dllimport))
  #else
    #define MINIMUM_EXPORT __declspec(dllexport)
    #define MINIMUM_IMPORT __declspec(dllimport)
  #endif
  #ifdef MINIMUM_BUILDING_LIBRARY
    #define MINIMUM_PUBLIC MINIMUM_EXPORT
  #else
    #define MINIMUM_PUBLIC MINIMUM_IMPORT
  #endif
  #define MINIMUM_PUBLIC_TYPE MINIMUM_PUBLIC
  #define MINIMUM_LOCAL
#else
  #define MINIMUM_EXPORT __attribute__ ((visibility("default")))
  #define MINIMUM_IMPORT
  #if __GNUC__ >= 4
    #define MINIMUM_PUBLIC __attribute__ ((visibility("default")))
    #define MINIMUM_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define MINIMUM_PUBLIC
    #define MINIMUM_LOCAL
  #endif
  #define MINIMUM_PUBLIC_TYPE
#endif

#endif  // MINIMUM__VISIBILITY_CONTROL_H_
