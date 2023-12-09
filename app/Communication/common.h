#ifndef COMMON_H_
#define COMMON_H_

#if defined(_WIN32)
#include "impl\windows\win.h"
#include "impl\windows\win_serial.h"
#elif defined(__GNUC__)
#include "Communication/unix.h"
#include "Communication/unix_serial.h"
#else
#error "unsupported target"
#endif
#include <Communication/thread.h>
#include <Communication/locker.h>
#include <Communication/timer.h>

#endif

