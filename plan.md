# Sys info logger

This part should be made in C

- log the following stuff:
    - cpu usage(%)
    - ram usage(gb)
    - disk usage(gb)
    - battery(%)
    - uptime(h:m)

log file should look something like:
```
2022-01-01 12:40:00, cpuuse 30, ramuse 5, bat 90, diskuse 33, uptime 5:10
2022-01-01 12:50:00, cpuuse 40, ramuse 4, bat 99, diskuse 33, uptime 5:20
.
.
.
```

This program should be executed by crontab every 10 min(not important though)

# Graph

This part should be made in Python

Read the log file and create a dataset
1. approach:
split by ',' and extract data into a format like this:
```
[["2022-01-01 12:40:00", 30, 5, 90, 33, "5:10"], ["2022-01-01 12:50:00", 40, 4, 99, 33, "5:20"],...]
```

Use this data to create a graph. Date-time on the x axis, other data on the y axis.
