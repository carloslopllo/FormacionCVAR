#ifndef MOVINGAVERAGE__VISIBILITY_CONTROL_H_
#define MOVINGAVERAGE__VISIBILITY_CONTROL_H_

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define MOVINGAVERAGE_EXPORT __attribute__ ((dllexport))
    #define MOVINGAVERAGE_IMPORT __attribute__ ((dllimport))
  #else
    #define MOVINGAVERAGE_EXPORT __declspec(dllexport)
    #define MOVINGAVERAGE_IMPORT __declspec(dllimport)
  #endif
  #ifdef MOVINGAVERAGE_BUILDING_LIBRARY
    #define MOVINGAVERAGE_PUBLIC MOVINGAVERAGE_EXPORT
  #else
    #define MOVINGAVERAGE_PUBLIC MOVINGAVERAGE_IMPORT
  #endif
  #define MOVINGAVERAGE_PUBLIC_TYPE MOVINGAVERAGE_PUBLIC
  #define MOVINGAVERAGE_LOCAL
#else
  #define MOVINGAVERAGE_EXPORT __attribute__ ((visibility("default")))
  #define MOVINGAVERAGE_IMPORT
  #if __GNUC__ >= 4
    #define MOVINGAVERAGE_PUBLIC __attribute__ ((visibility("default")))
    #define MOVINGAVERAGE_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define MOVINGAVERAGE_PUBLIC
    #define MOVINGAVERAGE_LOCAL
  #endif
  #define MOVINGAVERAGE_PUBLIC_TYPE
#endif

#endif  // MOVINGAVERAGE__VISIBILITY_CONTROL_H_
