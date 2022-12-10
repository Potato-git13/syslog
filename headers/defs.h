#ifndef DEFS_HEADER
#define DEFS_HEADER

#define SIZE 64
#define VERSION "1.0"

typedef struct _log_entry {
    char *date;
    char *time;
    unsigned int cpuuse;
    unsigned int ramuse;
    unsigned int diskuse;
    unsigned int bat;
    char *uptime;
} log_entry;

int asprintf(char **strp, const char *fmt, ...);

int pscanf(const char *path, const char *fmt, ...);

#endif