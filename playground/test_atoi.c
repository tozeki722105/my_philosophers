#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "limits.h"

int	main(int argc, char **argv)
{
	printf("long_max=%ld\n", atol(argv[1]));
	printf("long_max=%d\n", atoi(argv[1]));
}