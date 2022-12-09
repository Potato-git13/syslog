#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defs.h"
#include "cmd_args.h"

const char help[] = 
    "Usage: syslog [-h] [-c] [-t] [-f] <filepath>\n"
    "Options:\n"
    "  -h\tshow this message and exit\n"
    "  -c\tlog to console\n"
    "  -t\tdo not log, only test that everything works\n"
    "  -f\tlog to specified file\n";

// -c - log to stdout
FLAG c_flag;
// -f - log to specified file
FLAG f_flag;
// -t - test so that everything works
FLAG t_flag;
// -h - help message
FLAG h_flag;

int flag_check(FLAG *flag, char *flag_short, char *flag_long, char *match_text){
    if (!strcmp(match_text, flag_short) || !strcmp(match_text, flag_long))
        flag->used = true;
    return 0;
}

int file_log(log_entry entry, char *path){

    FILE *fp;

    fp = fopen(path, "a");
    if (!fp){
        fprintf(stderr, "syslog: could not open file: %s", path);
        return -1;
    }
    fprintf(fp, "%s %s, cpuuse %d, ramuse %d, diskuse %d, bat %d, uptime %s\n",
            entry.date, entry.time, entry.cpuuse, entry.ramuse, entry.diskuse, entry.bat, entry.uptime);

    fclose(fp);
    return 0;
}

int console_log(log_entry entry){
    printf(
            "%s %s\n"
            "\n"
            "cpu:\t%d%%\n"
            "ram:\t%d%%\n"
            "disk:\t%d%%\n"
            "bat:\t%d%%\n"
            "uptime:\t%s\n",
                entry.date, entry.time, entry.cpuuse, entry.ramuse,
                entry.diskuse, entry.bat, entry.uptime
        );
    return 0;
}



int cmd_arg_handler(int argc, char *argv[], log_entry entry){
    c_flag.used = f_flag.used = t_flag.used = h_flag.used = false;

    for (int i = 0; i < argc; i++){
        flag_check(&c_flag, "-c", "--console", argv[i]);
        // TODO: toggle .pos
        flag_check(&f_flag, "-f", "--file", argv[i]);
        flag_check(&t_flag, "-t", "--test", argv[i]);
        flag_check(&h_flag, "-h", "--help", argv[i]);
    }

    if (argc == 4 && f_flag.used && c_flag.used){
        if (argc == f_flag.pos+1){
            printf("syslog: no path given\n");
            return -1;
        }

        console_log(entry);
        // filepath is after "-f" flag
        if (file_log(entry, argv[f_flag.pos+1]) != 0)
            return -1;
        return 0;
    }

    if (argc == 3 && f_flag.used){
        // no path is given but argc == 3
        // e.g. syslog foo -f
        if (argc == f_flag.pos+1){
            printf("syslog: no path given\n");
            return -1;
        }
        
        // filepath is after "-f" flag
        if (file_log(entry, argv[f_flag.pos+1]) != 0)
            return -1;
        return 0;

    } else if ((argc < 3 || argc > 3) && f_flag.used){
        if (argc < 3){
            fprintf(stderr, "syslog: not enough arguments\n");
            return -1;
        } else if (argc > 3){
            fprintf(stderr, "syslog: too many arguments\n");
            return -1;
        }
    } else if (argc > 2 && !f_flag.used){
        if (argc > 2){
            fprintf(stderr, "syslog: too many arguments\n");
            return -1;
        }
    }

    if ((argc == 2 && c_flag.used) || argc == 1){
        if (console_log(entry) != 0)
            return -1;
        return 0;
    }
    
    if (argc == 2 && t_flag.used){
        printf("syslog: data fetched successfuly\n");
        return 0;
    }

    if (argc == 2 && h_flag.used){
        printf("%s", help);
        return 0;
    }
    
    printf("syslog: unknown arguments\n");
    return -1;
}
