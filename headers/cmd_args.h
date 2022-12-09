#ifndef CMDARGS_HEADER
#define CMDARGS_HEADER

#include <stdbool.h>

#include "defs.h"

typedef struct _flag{
    bool used;
    int pos;
} FLAG;

int flag_check(FLAG *flag, char *flag_short, char *flag_long, char *match_text);
int file_log(log_entry entry, char *path);
int console_log(log_entry entry);
int cmd_arg_handler(int argc, char *argv[], log_entry entry);

#endif
