#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CMD_LENGTH 128

int servstat(const char *service_name) {
	char cmd[MAX_CMD_LENGTH];
	FILE *fp;
	char output[16];

	// Prepare command to run
	snprintf(cmd, sizeof(cmd), "systemctl is-enabled %s", service_name);

	// Open pipe to command
	fp = popen(cmd, "r");
	if (fp == NULL) {
		perror("popen failed");
		return -2;
	}

	// Read output 
	if ((fgets(output, sizeof(output), fp) != NULL)) {
		// Check if service is enabled
		if ((strncmp(output, "enabled", 7)) == 0) { 
			fclose(fp);
			return 1;
		}
		// If service is not enabled, check if it doesn't exist
		if ((strncmp(output, "not-found", 7)) == 0) {
			fclose(fp);
			return -1;
		}
	}

	fclose(fp);
	return 0;
}
