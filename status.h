#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <jetgpio.h>

#define _GNU_SOURCE

void handle_sigint(int sig) {
	printf("Stopping status LEDs...");
	gpioTerminate();
	exit(0);
}

int procstat(const char pid[]) {
	FILE *fp;
	char file[];
	char loc[] = "/proc/";
	char *ret;

	char statuses[] = {"running", "sleeping", "idle", "zombie"};

	strcat(loc, pid);
	strcat(loc, "/status");

	fp = fopen(loc, "r");
	
	if (fp == NULL) { exit(-1); }
	
	fgets(file, 255, fp);

	for (int i = 0; i < 4; i++) {
		ret = strstr(file, statuses[i]);
		if (ret) {
			return i;
		}
	}

	return -1;
}
