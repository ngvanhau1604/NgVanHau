#include <stdio.h>
#include <thread>

void SaySomething(const char* msg)
{
	printf("MSG = %s\n", msg);
}

int main()
{
	std::thread task(SaySomething, "Hello STDIO");
	task.join();

	return 0;
}