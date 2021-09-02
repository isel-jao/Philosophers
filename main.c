#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <math.h>


int main()
{

	for (int i = 0; i < 10000000; i++)
	{
		if (ft_isprime(i))
			printf("%d, ", i);
	}
	return (0);
}
