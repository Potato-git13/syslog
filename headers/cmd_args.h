#ifndef CMDARGS_HEADER
#define CMDARGS_HEADER

#include <stdbool.h>

#include "defs.h"

typedef struct _flag{
    bool used;
    int pos;
} flag;

int log_func(log_entry entry, char *path);
int cmd_arg_handler(int argc, char *argv[], log_entry entry);

#endif
