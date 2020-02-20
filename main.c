#include <stdio.h>

static char memory[127];

void initializemem()
{
	memory[0] = 0b1111110;
	for (int i = 1; i < sizeof(memory); i++)
	{
		memory[i] = 0;
	}
}

void memmalloc(int bytenum)
{

}

void memfree(int memnum)
{

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
				if (bytenum >= 1 && bytenum <= 127)
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
