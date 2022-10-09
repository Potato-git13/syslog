#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>

#include "defs.h"
#include "components.h"

int log_func(log_entry entry){

    FILE *fp;
    struct passwd *pw = getpwuid(getuid());
    const char *homedir;
    char *log_file;

    if (!pw)
        return -1;

    homedir = pw->pw_dir;
    asprintf(&log_file, "%s/syslog", homedir);

    fp = fopen(log_file, "a");
    if (!fp){
        return -1;
    }
    fprintf(fp, "%s %s, cpuuse %d, ramuse %d, diskuse %d, bat %d, uptime %s\n",
            entry.date, entry.time, entry.cpuuse, entry.ramuse, entry.diskuse, entry.bat, entry.uptime);

    fclose(fp);

    free(log_file);
    return 0;
}

int main(){
    log_entry entry;

    get_time(&entry);
    cpu_usage(&entry);
    ram_usage(&entry);
    disk_usage(&entry, "/");
    battery_perc(&entry);
    get_uptime(&entry);

    if(log_func(entry) != 0){
        fprintf(stderr, "Error");
    }
    
    free(entry.date);
    free(entry.time);
    free(entry.uptime);
}
