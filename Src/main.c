#define F_CPU  16000000UL
#include "app.h"



int main()
{
	initialize_drivers();

	while(1)
	{
		app_run();
	}
}
