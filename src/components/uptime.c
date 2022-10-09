#include <stdint.h>
#include <time.h>

#include "components.h"

void get_uptime(log_entry *entry){
	uintmax_t h, min;
    char *full_time;
	struct timespec uptime;

    // Get the time since boot
	if(clock_gettime(CLOCK_BOOTTIME, &uptime) < 0){
		return;
	}

    // Calculate the hours and minutes
	h = uptime.tv_sec / 3600;
	min = uptime.tv_sec % 3600 / 60;

    // Assemble the values into a string
    asprintf(&full_time, "%ju:%ju", h, min);

    entry->uptime = full_time;
}