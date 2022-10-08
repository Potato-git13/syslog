#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>

#define SIZE 64

int asprintf(char **strp, const char *fmt, ...);

typedef struct _log_entry {
    char *date;
    char *time;
    int cpuuse;
    int ramuse;
    int bat;
    char *uptime;
} log_entry;

void get_time(log_entry *entry){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    // Get date yyyy-mm-dd
    char *date_str;
    asprintf(&date_str, "%d-%02d-%02d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
    entry->date = date_str;

    // Get time hh:mm:ss
    char *time_str;
    asprintf(&time_str, "%02d:%02d:%02d", tm.tm_hour, tm.tm_min, tm.tm_sec);
    entry->time = time_str;
}

void cpu_usage(log_entry *entry){
    char *token, *str, *tofree;
    int int_token;
    int count = 0;

    int all_sums[2] = {0x0};
    int work_sums[2] = {0x0};
    float all_over_time, work_over_time;
    int cpuperc;

    // Open the file, read the first line, sum all and work valuesž
    // Repeat 2x 1 sec apart to get different values
    for(int i = 0; i <= 1; i++){
        FILE *fp;
        fp = fopen("/proc/stat", "r");
        char *line;
        size_t len = 0;

        // Check file pointer
        if (!fp){
            return;
        }
        // Get the first line
        getline(&line, &len, fp);

        tofree = str = strdup(line);
        while ((token = strsep(&str, " "))){
            if (!strcmp(token, "cpu") || *token == '\0' || *token == '\n'){
                continue;
            }
            // Convert the token to int
            int_token = strtol(token, NULL, 10);

            all_sums[i] += int_token;
            // Add only the first 3 values
            if (count <= 2){
                work_sums[i] += int_token;
            }     
            count++;
        }
        free(tofree);
        count = 0;
        // Don't sleep on the last loop
        if (i != 1){
            sleep(1);
        }
    }
    // Calculate differences
    all_over_time = all_sums[1] - all_sums[0];
    work_over_time = work_sums[1] - work_sums[0];

    // Calculate the final cpu percentage
    cpuperc = work_over_time / all_over_time * 100;

    entry->cpuuse = cpuperc;
}

int main(){
    log_entry entry;

    get_time(&entry);
    cpu_usage(&entry);
    
    printf("%s %s %d\n",
            entry.date, entry.time, entry.cpuuse);
}
