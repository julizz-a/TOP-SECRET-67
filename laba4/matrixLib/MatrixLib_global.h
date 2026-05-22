#ifndef MATRIXLIB_GLOBAL_H
#define MATRIXLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MATRIXLIB_LIBRARY)
#define MATRIXLIB_EXPORT Q_DECL_EXPORT
#else
#define MATRIXLIB_EXPORT Q_DECL_IMPORT
#endif

#endif // MATRIXLIB_GLOBAL_H
