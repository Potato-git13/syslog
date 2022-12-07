#include <stdio.h>
#include <stdlib.h>

#include "defs.h"
#include "components.h"
#include "cmd_args.h"

int main(int argc, char *argv[]){
    log_entry entry;
    int ret;

    if (get_time(&entry)        ||
        cpu_usage(&entry)       ||
        ram_usage(&entry)       ||
        disk_usage(&entry, "/") ||
        battery_perc(&entry)    ||
        get_uptime(&entry) != 0){
            fprintf(stderr, "syslog: data fetching error\n");
            return -1;
    }

    ret = cmd_arg_handler(argc, argv, entry);
    
    free(entry.date);
    free(entry.time);
    free(entry.uptime);

    return ret;
}
