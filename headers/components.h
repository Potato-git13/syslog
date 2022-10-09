#ifndef COMP_HEADER
#define COMP_HEADER

#include "defs.h"

void cpu_usage(log_entry *entry);
void get_time(log_entry *entry);
void ram_usage(log_entry *entry);
void disk_usage(log_entry *entry, const char *path);
void battery_perc(log_entry *entry);

#endif