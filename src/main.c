#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>

#define SIZE 64

int asprintf(char **strp, const char *fmt, ...);

typedef struct _log_entry {
    char *date;
    char *time;
    unsigned int cpuuse;
    unsigned int ramuse;
    unsigned int bat;
    char *uptime;
} log_entry;

int pscanf(const char *path, const char *fmt, ...){
	FILE *fp;
	va_list ap;
	int n;

    // Open file and check pointer
    fp = fopen(path, "r");
	if (!fp) {
		return -1;
	}

    // Scan the file
	va_start(ap, fmt);
	n = vfscanf(fp, fmt, ap);
	va_end(ap);
	fclose(fp);

	return (n == EOF) ? -1 : n;
}

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
    unsigned int count = 0;

    unsigned int all_sums[2], work_sums[2] = {0x0};
    long double vals[14] = {0x0};
    float all_over_time, work_over_time;
    unsigned int cpuperc;

    // Get two sets of values 1 sec apart
    for(int i = 0; i <= 1; i++){
        if (pscanf("/proc/stat", "%*s %Lf %Lf %Lf %Lf %Lf %Lf %Lf",
		           &vals[0+i*7], &vals[1+i*7], &vals[2+i*7], &vals[3+i*7], &vals[4+i*7], &vals[5+i*7], &vals[6+i*7])
                   != 7){
            return;
        };

        all_sums[i] = vals[0+i*7] + vals[1+i*7] + vals[2+i*7] + vals[3+i*7] + vals[4+i*7] + vals[5+i*7] + vals[6+i*7];
        work_sums[i] = vals[0+i*7] + vals[1+i*7] + vals[2+i*7];

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

    printf("%s %s %d%%\n",
            entry.date, entry.time, entry.cpuuse);
}
