#ifndef GENERAL_H
#define GENERAL_H

#include <QtGlobal>

#ifndef QT_DEBUG
#define DEBUG_ASSERT(X) X;
#else
#define DEBUG_ASSERT(X) Q_ASSERT(X);
#endif

#endif // GENERAL_H
