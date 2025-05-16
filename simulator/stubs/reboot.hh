#pragma once
#include <cstdio>
#include <cstdlib>

inline void reboot_system() {
	printf("Simulator received request to reboot, but will just terminate\n");
	exit(0);
}
