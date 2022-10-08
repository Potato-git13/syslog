#include <stdio.h>
#include <stdlib.h>

#include "defs.h"
#include "components.h"

int main(){
    log_entry entry;

    get_time(&entry);
    cpu_usage(&entry);
    ram_usage(&entry);

    printf("%s %s %d%% %d%%\n",
            entry.date, entry.time, entry.cpuuse, entry.ramuse);

    free(entry.date);
    free(entry.time);
}
