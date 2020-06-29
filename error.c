#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int	*p;

	p = malloc(sizeof(int) * 2);
	p[0] = 3;
	p[1] = 4;
	if (p[2])
		printf("holo");
	
}