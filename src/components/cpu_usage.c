#include <unistd.h>

#include "components.h"

int cpu_usage(log_entry *entry){
    unsigned int all_sums[2], work_sums[2] = {0x0};
    long double vals[14] = {0x0};
    float all_over_time, work_over_time;
    unsigned int cpuperc;

    // Get two sets of values 1 sec apart
    for(int i = 0; i <= 1; i++){
        if (pscanf("/proc/stat", "%*s %Lf %Lf %Lf %Lf %Lf %Lf %Lf",
		           &vals[0+i*7], &vals[1+i*7], &vals[2+i*7], &vals[3+i*7], &vals[4+i*7], &vals[5+i*7], &vals[6+i*7])
                   != 7){
            return -1;
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
    return 0;
}
