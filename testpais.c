#include <stdio.h>
#include <stdlib.h>
#include "getpais.h"

int main(int argc, char *argv[])
{
  start();
  PIP_PAIS result;
  int i;
  for (i=0;i<1500000 ;i++ )
  {
	  result =search(argv[1]);
  }

  if (result)
	{
	  printf("searchs: %d\n",i);
			printf("pais = %s , ip = %s , cant = %d   int desde %d , inthasta %d, int result = %d \n", result->pais,result->ip, result->cant,
			result->desde , result->hasta, result->hasta-result->desde);
	}
  else
	{
		printf ("Couldn't find %s.\n", argv[1]);
	}
	stop ();
	return 0;
}
