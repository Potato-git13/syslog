#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

#include "defs.h"

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