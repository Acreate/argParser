
#ifndef ARGPARSER_EXPORT_H
#define ARGPARSER_EXPORT_H

#ifdef ARGPARSER_STATIC_DEFINE
#  define ARGPARSER_EXPORT
#  define ARGPARSER_NO_EXPORT
#else
#  ifndef ARGPARSER_EXPORT
#    ifdef argParser_EXPORTS
        /* We are building this library */
#      define ARGPARSER_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define ARGPARSER_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef ARGPARSER_NO_EXPORT
#    define ARGPARSER_NO_EXPORT 
#  endif
#endif

#ifndef ARGPARSER_DEPRECATED
#  define ARGPARSER_DEPRECATED __declspec(deprecated)
#endif

#ifndef ARGPARSER_DEPRECATED_EXPORT
#  define ARGPARSER_DEPRECATED_EXPORT ARGPARSER_EXPORT ARGPARSER_DEPRECATED
#endif

#ifndef ARGPARSER_DEPRECATED_NO_EXPORT
#  define ARGPARSER_DEPRECATED_NO_EXPORT ARGPARSER_NO_EXPORT ARGPARSER_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef ARGPARSER_NO_DEPRECATED
#    define ARGPARSER_NO_DEPRECATED
#  endif
#endif

#endif /* ARGPARSER_EXPORT_H */
