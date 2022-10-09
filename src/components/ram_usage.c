#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "components.h"

void ram_usage(log_entry *entry){
    uintmax_t total, free, buffers, cached, ram_perc;

    // Scan all of the variables
    if (pscanf("/proc/meminfo",
                "MemTotal: %ju kB\n"
                "MemFree: %ju kB\n"
                "MemAvailable: %ju kB\n"
                "Buffers: %ju kB\n"
                "Cached: %ju kB\n",
                &total, &free, &buffers, &buffers, &cached) != 5) {
        return;
    }

    // If the total is 0 an error has occured
    if (total == 0) {
        return;
    }

    // Calculate the percentage
    ram_perc = 100 * ((total - free) - (buffers + cached)) / total;
    
    entry->ramuse = ram_perc;
}