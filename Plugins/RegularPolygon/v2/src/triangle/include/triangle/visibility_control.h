#ifndef TRIANGLE__VISIBILITY_CONTROL_H_
#define TRIANGLE__VISIBILITY_CONTROL_H_

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
#define TRIANGLE_EXPORT __attribute__((dllexport))
#define TRIANGLE_IMPORT __attribute__((dllimport))
#else
#define TRIANGLE_EXPORT __declspec(dllexport)
#define TRIANGLE_IMPORT __declspec(dllimport)
#endif
#ifdef TRIANGLE_BUILDING_LIBRARY
#define TRIANGLE_PUBLIC TRIANGLE_EXPORT
#else
#define TRIANGLE_PUBLIC TRIANGLE_IMPORT
#endif
#define TRIANGLE_PUBLIC_TYPE TRIANGLE_PUBLIC
#define TRIANGLE_LOCAL
#else
#define TRIANGLE_EXPORT __attribute__((visibility("default")))
#define TRIANGLE_IMPORT
#if __GNUC__ >= 4
#define TRIANGLE_PUBLIC __attribute__((visibility("default")))
#define TRIANGLE_LOCAL __attribute__((visibility("hidden")))
#else
#define TRIANGLE_PUBLIC
#define TRIANGLE_LOCAL
#endif
#define TRIANGLE_PUBLIC_TYPE
#endif

#endif  // TRIANGLE__VISIBILITY_CONTROL_H_
