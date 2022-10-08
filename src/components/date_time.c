#include <time.h>
#include <string.h>

#include "components.h"

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