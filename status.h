#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_CMD_LENGTH 128

bool procstat(const char *service_name) {
	char cmd[MAX_CMD_LENGTH];
	FILE *fp;
	char output[16];

	// Prepare command to run
	snprintf(cmd, sizeof(cmd), "systemctl is-enabled %s", service_name);

	// Open pipe to command
	fp = popen(cmd, "r");
	if (fp == NULL) {
		perror("popen failed");
		return false;
	}

	// Read output and check if it contains enabled
	if ((fgets(output, sizeof(output), fp) != NULL) && (strncmp(output, "enabled", 7)) == 0) {
		fclose(fp);
		return true;
	}

	fclose(fp);
	return false;
	}
