#include <stdio.h>

static unsigned char memory[127];

int printmemory()
{
	for(int i = 0; i < 127; ++i)
	{
		if (i%10 == 0)
		{
			printf("\n");
		}
		printf("%d: %i\t", i, memory[i]);
		
	}
	printf("\n");
}


int searchindex(int bytesize)
{
	int bestindex;
	int minremainder = 999;
	int index = 0;
	while (index < 126)
	{
		unsigned int payloadsz = (memory[index] >> 1)-1; // size of payload at current index
		unsigned int allocated = memory[index] & 1;
		printf("Payload: %d\n", payloadsz);
		printf("Index: %d\n", index);
		printf("Allocated: %d\n", allocated);

		if (!allocated)
		{
			if (payloadsz >= bytesize)
			{
				int remainder = payloadsz - bytesize;
				if (remainder < minremainder) {
					bestindex = index;
					minremainder = remainder;
				}		
			}
		}
		index += (payloadsz+1);
	}
	return bestindex;
}

void initializemem()
{
	memory[0] = 0b11111110;
	for (int i = 1; i < sizeof(memory); i++)
	{
		memory[i] = 0;
	}
}

void memmalloc(int bytenum)
{
	int bestindex = searchindex(bytenum);
	int header = ((bytenum+1) << 1) | 1;
	unsigned int payloadsz = (memory[bestindex] >> 1);
	unsigned int remainder = payloadsz - (bytenum+1);

	printf("Payloadsz: %i\n", payloadsz);
	printf("Remainder: %i\n", remainder);

	memory[bestindex] = header;

	unsigned int currval = memory[bestindex+bytenum+1];

	if (currval < remainder)
		memory[bestindex + bytenum + 1] = (remainder << 1) | 0;

	printf("%d\n", bestindex+1);
	printmemory();
}
	
void memfree(int memnum)
{
	int index = memnum-1;
	int currval = memory[index] & 0b11111110;
	printf("%i\n", currval);
	memory[index] = currval;
	printf("Index: %i\n", index);
	printf("Memory: %i\n", memory[index]);
	printmemory();

}

void memwrite(int addr, char * info)
{

}

void blocklist()
{

}

void printmem(int addr, int length)
{
	for (int i = addr; i < addr+length; i++)
	{
		if (i > 126)
			break;
		printf("%i : %i ", i, memory[i]);
	}
	printf("\n");
}

void parsecmd(char * buf)
{
	char * cmd;

	cmd = strtok(buf, " \n");

	if (cmd != NULL)
	{		
		if (strcmp(cmd, "malloc") == 0)
		{
			cmd = strtok(NULL,  " ");
			if (cmd != NULL)
			{
				int bytenum = atoi(cmd);
				if (bytenum >= 1 && bytenum <= 126)
				{
					memmalloc(bytenum);
				}
			}
		}
		else if (strcmp(cmd, "free") == 0)
		{
			cmd = strtok(NULL, " ");
			if (cmd != NULL)
			{
				int memnum = atoi(cmd);
				if (memnum >= 1 && memnum <= 127)
				{
					memfree(memnum);
				}
			}
		}
		else if (strcmp(cmd, "blocklist") == 0)
		{
			blocklist();
		}
		else if (strcmp(cmd, "writemem") == 0)
		{
			cmd = strtok(NULL, " ");
			if (cmd != NULL)
			{
				int addr = atoi(cmd);
				if (addr >= 1 && addr <= 127)
				{
					cmd = strtok(NULL, " ");
					if (cmd != NULL)
					{
						int info = cmd;
						memwrite(addr, info);
					}					
				}
			}
		}
		else if (strcmp(cmd, "printmem") == 0)
		{
			cmd = strtok(NULL, " ");
			if (cmd != NULL)
			{
				int addr = atoi(cmd);
				if (addr >= 1 && addr <= 127)
				{
					cmd = strtok(NULL, " ");
					if (cmd != NULL)
					{
						int length = atoi(cmd);
						if (length >= 1 && length <= 127)
						{
							printmem(addr, length);
						}
					}
				}
			}
		}
		else if (strcmp(cmd, "quit") == 0)
		{
			printf("quit\n");
			exit(0);
		}
	}

}

int main() {

	char buf[50];

	initializemem();

	while (1)
	{
		printf("> ");

		if (fgets(buf, sizeof(buf), stdin) != NULL)
        { 
            parsecmd(buf);    
        }
	}
	return 0;
}
