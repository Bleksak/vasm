#pragma once

#include <errno.h>

errno_t assemble_file(const char* restrict filename, unsigned char* restrict * restrict output);