#ifndef BASE_H
#define BASE_H

#include <stdint.h>

#define KiB(n) ((uint64_t)(n) << 10)
#define MiB(n) ((uint64_t)(n) << 20)
#define GiB(n) ((uint64_t)(n) << 30)

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define ALIGN_UP(x, a) (((uint64_t)(x) + ((uint64_t)(a)-1)) & ~((uint64_t)(a)-1))

#endif