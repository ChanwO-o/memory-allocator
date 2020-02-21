#include <stdio.h>
#include <string.h>

static unsigned char memory[127];

void initializemem() {
	memory[0] = 0b11111110;
	int i;
	for (i = 1; i < sizeof(memory); i++)
		memory[i] = 0;
}

void start() {
	char buffer[100];
	initializemem();
	
	while (1) {
		printf("> ");
		fgets(buffer, 100, stdin); // store user input
		strtok(buffer, "\n"); // remote newline character at end of input
		char* firstcmd = strtok(buffer, " \t");
		
		if (strcmp(firstcmd, "quit") == 0) {
			break;
		}
		if (strcmp(firstcmd, "malloc") == 0) {
			printf("malloc\n");
			// cmd = strtok(NULL,  " ");
			// if (cmd != NULL) {
				// int bytenum = atoi(cmd);
				// if (bytenum >= 1 && bytenum <= 126)
					// memmalloc(bytenum);
			// }
		}
		else if (strcmp(firstcmd, "free") == 0) {
			printf("free\n");
			// cmd = strtok(NULL, " ");
			// if (cmd != NULL) {
				// int memnum = atoi(cmd);
				// if (memnum >= 1 && memnum <= 127)
					// memfree(memnum);
			// }
		}
		else if (strcmp(firstcmd, "blocklist") == 0) {
			// blocklist();
		}
		else if (strcmp(firstcmd, "writemem") == 0) {
			printf("writemem\n");
			// cmd = strtok(NULL, " ");
			// if (cmd != NULL) {
				// int addr = atoi(cmd);
				// if (addr >= 1 && addr <= 127) {
					// cmd = strtok(NULL, " ");
					// if (cmd != NULL) {
						// int info = cmd;
						// memwrite(addr, info);
					// }					
				// }
			// }
		}
		else if (strcmp(firstcmd, "printmem") == 0) {
			printf("printmem\n");
			// cmd = strtok(NULL, " ");
			// if (cmd != NULL) {
				// int addr = atoi(cmd);
				// if (addr >= 1 && addr <= 127) {
					// cmd = strtok(NULL, " ");
					// if (cmd != NULL) {
						// int length = atoi(cmd);
						// if (length >= 1 && length <= 127)
							// printmem(addr, length);
					// }
				// }
			// }
		}
		else if (strcmp(firstcmd, "loaddungeon") == 0) {
			char* filename = strtok(NULL, " \t");
		}
		fflush(stdin);
	}
}

int main() {
	start();
	return 0;
}
