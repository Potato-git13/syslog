#include <stdio.h>
#include <stdlib.h>

#include "defs.h"
#include "components.h"
#include "cmd_args.h"

int main(int argc, char *argv[]){
    log_entry entry;
    int ret;

    // gather all of the data
    if (get_time(&entry)        ||
        cpu_usage(&entry)       ||
        ram_usage(&entry)       ||
        disk_usage(&entry, "/") ||
        battery_perc(&entry)    ||
        get_uptime(&entry) != 0){
            fprintf(stderr, "syslog: data fetching error\n");
            return -1;
    }

    // handle all of the arguments and output the data
    ret = cmd_arg_handler(argc, argv, entry);
    
    // free the allocated variables
    free(entry.date);
    free(entry.time);
    free(entry.uptime);

    return ret;
}
