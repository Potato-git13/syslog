#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "components.h"

void ram_usage(log_entry *entry){
    uintmax_t total, free, buffers, cached, ret;

    if (pscanf("/proc/meminfo",
                "MemTotal: %ju kB\n"
                "MemFree: %ju kB\n"
                "MemAvailable: %ju kB\n"
                "Buffers: %ju kB\n"
                "Cached: %ju kB\n",
                &total, &free, &buffers, &buffers, &cached) != 5) {
        return;
    }

    if (total == 0) {
        return;
    }

    ret = 100 * ((total - free) - (buffers + cached)) / total;
    
    entry->ramuse = ret;
}