#ifndef COMP_HEADER
#define COMP_HEADER

#include "defs.h"

int cpu_usage(log_entry *entry);
int get_time(log_entry *entry);
int ram_usage(log_entry *entry);
int disk_usage(log_entry *entry, const char *path);
int battery_perc(log_entry *entry);
int get_uptime(log_entry *entry);

#endif