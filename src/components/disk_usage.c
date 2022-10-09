#include <stdlib.h>
#include <sys/statvfs.h>

#include "components.h"

void disk_usage(log_entry *entry, const char *path){
	struct statvfs fs;
    unsigned int disk_perc;

    // Initialise the fs struct
	if (statvfs(path, &fs) < 0) {
		return;
	}

    // Calculate the percentage
    disk_perc = (unsigned int)(100 * (1.0f - ((float)fs.f_bavail / (float)fs.f_blocks)));
    entry->diskuse = disk_perc;
}
