#include "components.h"

int battery_perc(log_entry *entry){
    unsigned int bat_perc;

    // Get the battery percentage
    if (pscanf("/sys/class/power_supply/BAT0/capacity",
                "%d", &bat_perc) != 1) {
        return -1;
    }

    entry->bat = bat_perc;
    return -1;
}