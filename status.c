#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <jetgpio.h>
#include <signal.h>
#include <stdbool.h>

#include "status.h"
#define LEN(x) (sizeof(x) / sizeof((x)[0]))

void handle_sigint(int sig) {
	printf("Stopping status LEDs...");
	gpioTerminate();
	exit(0);
}


int main(int argc, char *argv[]) {
	// This variable will be used to check the status of initialisation of general GPIO as well as individual pins.
	int Init;
	Init = gpioInitialise();

	// Check if general initialisation has failed
	if (Init < 0) {
		printf("JETGPIO initialisation failed. Error code: %d\n", Init);
		exit(Init);
	} else {
		printf("JETGPIO initialisation OK. Return code %d\n", Init);
	}

	// This list just holds all addresses of GPIO pins on the orin
	int pins[] = {3, 5, 6, 8, 9, 10, 11, 12, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 29, 31, 32, 33, 35, 36, 37, 38, 40};
	
	// Check if all processes exist
	for (int i = 1; i < argc; i++) {
		if (servstat(argv[i]) == -1) {
			printf("Process does not exist or is not found: %s\n", argv[i]);
			exit(-1);
		}
	}

	// Check if more processes are being monitored than GPIO pins
	if (argc >= LEN(pins)) {
		printf("You are trying to initialise more pins than exist on this device.\n");
		exit(-1);
	}

	// Initialise list containing each GPIO pin that we plan to write to
	int *stats[argc];

	for (int i = 1; i < argc; i++) {
		stats[i] = gpioSetMode(pins[i], JET_OUTPUT);
		if (stats[i] < 0) {
			printf("Failed initialising GPIO pin: %d\n", pins[i]);
			exit(-1);
		} else {
			printf("Set up GPIO pin %d for service %s\n", pins[i], argv[i]);
		}
	}

	while (true) {
		for (int i = 1; i < argc; i++) {
			switch (servstat(argv[i])) {
			case 1:
				gpioWrite(pins[i], 1);
			case 0:
				gpioWrite(pins[i], 0);
			case -1:
				printf("Service %s does not exist. Aborting", argv[i]);
				gpioTerminate();
				exit(-1);
			case -2:
				printf("Something went wrong when reading from pipe for service %s. Aborting", argv[i]);
				gpioTerminate();
				exit(-1);
			}
		}
}



