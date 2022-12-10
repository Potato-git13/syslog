#include <stdio.h>
#include <string.h>

#include "defs.h"
#include "cmd_args.h"

const char help[] = 
    "Usage: syslog [-h] [-c] [-t] [-f] <filepath>\n"
    "Options:\n"
    "  -h, --help\tshow this message and exit\n"
    "  -c, --console\tlog to console\n"
    "  -t, --test\tdo not log, only test that everything works\n"
    "  -f, --file\tlog to specified file\n";

// -c - log to stdout
FLAG c_flag;
// -f - log to specified file
FLAG f_flag;
// -t - test so that everything works
FLAG t_flag;
// -h - help message
FLAG h_flag;
// -v - version
FLAG v_flag;

// check if the given flag was used
int flag_check(FLAG *flag, char *flag_short, char *flag_long, char *match_text, bool do_used_toggle, bool do_pos_toggle, unsigned int arg_pos){
    if (!(!strcmp(match_text, flag_short) || !strcmp(match_text, flag_long)))
        return -1;
    
    if (do_used_toggle)
        flag->used = true;
    if (do_pos_toggle)
        flag->pos = arg_pos;
    
    return 0;
}

int file_log(log_entry entry, char *path){

    FILE *fp;
    // append to file
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
    c_flag.used = 
    f_flag.used = 
    t_flag.used = 
    h_flag.used = 
    v_flag.used = false;

    // checking for the usage of flags
    for (int i = 0; i < argc; i++){
        flag_check(&c_flag, "-c", "--console", argv[i], true, false, i);
        flag_check(&f_flag, "-f", "--file", argv[i], true, true, i);
        flag_check(&t_flag, "-t", "--test", argv[i], true, false, i);
        flag_check(&h_flag, "-h", "--help", argv[i], true, false, i);
        flag_check(&v_flag, "-v", "--version", argv[i], true, false, i);
    }

    // syslog -c -f path
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

    // syslog -f path
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
    }else if ((argc < 3 || argc > 3) && f_flag.used){ 
        // syslog -f
        if (argc < 3){
            fprintf(stderr, "syslog: not enough arguments\n");
            return -1;
        // syslog -f foo bar
        } else if (argc > 3){
            fprintf(stderr, "syslog: too many arguments\n");
            return -1;
        }
    } // syslog foo bar
    else if (argc > 2 && !f_flag.used){
        fprintf(stderr, "syslog: too many arguments\n");
        return -1;
    }

    // syslog -c
    if ((argc == 2 && c_flag.used) || argc == 1){
        if (console_log(entry) != 0)
            return -1;
        return 0;
    }
    
    // syslog -t
    if (argc == 2 && t_flag.used){
        printf("syslog: data fetched successfuly\n");
        return 0;
    }

    // syslog -h
    if (argc == 2 && h_flag.used){
        printf("%s", help);
        return 0;
    }

    // syslog -v
    if (argc == 2 && v_flag.used){
        #ifndef VERSION
            fprintf(stderr, "syslog: version not defined\n");
            return -1;
        #endif
        printf("syslog %s\n", VERSION);
        return 0;
    }
    
    printf("syslog: unknown arguments\n");
    return -1;
}
