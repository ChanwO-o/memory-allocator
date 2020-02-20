#include <stdio.h>

void memmalloc(int bytenum)
{

}

void memfree(int memnum)
{

}

void printmem()
{

}

void memwrite(int addr, char * info)
{

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
			printmem();
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
			printf("printmem\n");
			
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

	while (1)
	{
		printf("> ");

		if (fgets(buf, sizeof(buf), stdin) != NULL)
        { 
            // if (strcmp(buf, "quit\n") == 0)
            //     break;
            // 

            parsecmd(buf);    
        }

	}

	return 0;
}
