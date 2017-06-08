#include "main.h"

int main(void)
{

	while(1)
	{
		IO_Init();

		IO_readString(command.buff,command.type);

		command.error = LL_EXEC(command.buff,command.type);

		if (command.error > 0)
			IO_WRITE_ERROR(command.error);
    }
}
