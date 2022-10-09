#include <stdio.h>
#include <stdlib.h>

#include "defs.h"
#include "components.h"

int main(){
    log_entry entry;

    get_time(&entry);
    cpu_usage(&entry);
    ram_usage(&entry);
    disk_usage(&entry, "/");
    battery_perc(&entry);

    printf("%s %s, cpuuse %d%%, ramuse %d%%, diskuse %d%% bat %d%%\n",
            entry.date, entry.time, entry.cpuuse, entry.ramuse, entry.diskuse, entry.bat);

    free(entry.date);
    free(entry.time);
}
