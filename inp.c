#include <stdio.h>
#include <string.h>

static unsigned char memory[127];

void initializemem() {
	memory[0] = 0b11111110;
	int i;
	for (i = 1; i < sizeof(memory); i++)
		memory[i] = 0;
}

void printmem() {
	int i;
	for(i = 0; i < 127; ++i) {
		if (i%10 == 0)
			printf("\n");
		printf("%d: %i\t", i, memory[i]);
		
	}
	printf("\n");
}

int getbestindex(int bytesize) {
	int bestindex;
	int minremainder = 999;
	int index = 0;
	while (index < 126) {
		unsigned int payloadsz = (memory[index] >> 1) - 1; // size of payload at current index
		unsigned int allocated = memory[index] & 1;
		// printf("Payload: %d\n", payloadsz);
		// printf("Index: %d\n", index);
		// printf("Allocated: %d\n", allocated);
		if (!allocated) {
			if (payloadsz >= bytesize) {
				int remainder = payloadsz - bytesize;
				if (remainder < minremainder) {
					bestindex = index;
					minremainder = remainder;
				}
			}
		}
		index += (payloadsz + 1);
	}
	return bestindex;
}

void memmalloc(int bytenum) {
	int bestindex = getbestindex(bytenum);
	int header = ((bytenum + 1) << 1) | 1;
	unsigned int payloadsz = (memory[bestindex] >> 1);
	unsigned int remainder = payloadsz - (bytenum + 1);

	// printf("Payloadsz: %i\n", payloadsz);
	// printf("Remainder: %i\n", remainder);

	memory[bestindex] = header;

	unsigned int currval = memory[bestindex + bytenum + 1];

	if (currval < remainder)
		memory[bestindex + bytenum + 1] = (remainder << 1) | 0;

	printf("%d\n", bestindex + 1);
}
	
void memfree(int memnum) {
	int index = memnum - 1;
	int currval = memory[index] & 0b11111110;
	// printf("%i\n", currval);
	memory[index] = currval;
	// printf("Index: %i\n", index);
	// printf("Memory: %i\n", memory[index]);
}

void mergefreesectors() {
	int index = 0;
	while (index < 126) {
		unsigned int payloadsz = (memory[index] >> 1)-1; // size of payload at current index
		unsigned int allocated = memory[index] & 1;
		if (!allocated) { // free block found
			int nextindex = index + payloadsz + 1;
			if (nextindex >= 127) // reached end of heap
				break;
			unsigned int nextpayloadsz = (memory[nextindex] >> 1) - 1;
			unsigned int nextallocated = memory[nextindex] & 1;
			if (!nextallocated) { // next is lso free : perform merge
				int newpayloadsize = payloadsz + nextpayloadsz + 2;
				int newheader = (newpayloadsize << 1); // shift left
				memory[index] = newheader;
			}
			else
				index += (payloadsz + 1);
		}
		else
			index += (payloadsz + 1);
	}
}

void start() {
	char buffer[100];
	initializemem();
	
	while (1) {
		printf("> ");
		fgets(buffer, 100, stdin); // store user input
		strtok(buffer, "\n"); // remote newline character at end of input
		char* cmd = strtok(buffer, " \t");
		
		if (strcmp(cmd, "quit") == 0) {
			break;
		}
		if (strcmp(cmd, "malloc") == 0) {
			cmd = strtok(NULL,  " \t");
			if (cmd != NULL) {
				int bytenum = atoi(cmd);
				if (bytenum >= 1 && bytenum <= 126)
					memmalloc(bytenum);
			}
		}
		else if (strcmp(cmd, "free") == 0) {
			cmd = strtok(NULL, " ");
			if (cmd != NULL) {
				int memnum = atoi(cmd);
				if (memnum >= 1 && memnum <= 127)
					memfree(memnum);
			}
		}
		else if (strcmp(cmd, "blocklist") == 0) {
			// blocklist();
		}
		else if (strcmp(cmd, "writemem") == 0) {
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
		else if (strcmp(cmd, "printmem") == 0) {
			printmem();
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
		
        mergefreesectors();
		fflush(stdin);
	}
}

int main() {
	start();
	return 0;
}
