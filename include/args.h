#ifndef ARGS_H
#define ARGS_H

#include "string/string.h"
#include "flag/flag.h"
#include "file.h"
#include "vec.h"

vec_t* validate_args(int argc, char** argv);

void validate_flags(vec_t** flags, int* n, file_t** file);

#endif // !ARGS_H
