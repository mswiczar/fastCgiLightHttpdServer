#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include "getpais.h"


#define LONGSWAP(x) (((x&0x0FF)<<24)| ((x&0x0FF00)<<8)| ((x&0x0FF0000)>>8)| ((x&0x0FF000000)>>24))

char* charsdata[7];




#define	TAMANO  100*1024
IP_PAIS inmemroyArray[TAMANO];



int 
critter_cmp (IP_PAIS *c1, IP_PAIS *c2)
{
//  return (c1->desde - c2->desde);

  if ((c1->desde >= c2->desde ) && (c1->hasta <= c2->hasta ))
  {
        return 0;
  }
  else
  {
   if (c1->desde < c2->desde )
   {
         return -1;
   }
        else
        {
         return 1;
        }

  }

}




void start()
{
  struct sockaddr_in antelope;

  int i;
  char c;     /* declare a char variable */
  FILE *file; /* declare a FILE pointer  */
	char line[1024];
	memset(line,0,sizeof(line));
	int pos=0;
  file = fopen("ip.txt", "r"); 
  int cantidad_registros=0;
  int cantidad_ipv4 =0;

  /* open a text file for reading */
	memset(&inmemroyArray,0,sizeof(inmemroyArray));

  if(file==NULL) {
    printf("Error: can't open file.\n");
    /* fclose(file); DON'T PASS A NULL POINTER TO fclose !! */
    return ;
  }
  else {
    //printf("File opened successfully. Contents:\n\n");
    
    while(1) {     /* keep looping... */
      c = fgetc(file);
      if(c!=EOF) {
        if (c!='\n')
        {
			line[pos]=c;
			pos++;
		}
		else
		{
			int adento=0;
			//printf("%s\n", line);  
			charsdata[adento]=line;
			for (i=0; i<pos ;i++ )
			{
				c=line[i];
				if (c=='|')
				{
					line[i]=0x00;
					adento++;
					charsdata[adento] = &line[i+1];
				}
			}
			pos=0;
			/*
				char pais[4];
				char ip[16];
				int cant;
				int  desde;
				int  hasta;
			*/

			if (strcmp("ipv4",charsdata[2])==0)
			{
				//printf("pais = %s , ip = %s , cant = %s\n", charsdata[1],charsdata[3],charsdata[4]);  
				sprintf(inmemroyArray[cantidad_ipv4].pais,"%s",charsdata[1]);
				sprintf(inmemroyArray[cantidad_ipv4].ip,"%s",charsdata[3]);
				inmemroyArray[cantidad_ipv4].cant= atoi(charsdata[4]);
				inet_aton(charsdata[3], &antelope.sin_addr); // store IP in antelope
				inmemroyArray[cantidad_ipv4].desde = LONGSWAP(antelope.sin_addr.s_addr);
				inmemroyArray[cantidad_ipv4].hasta = inmemroyArray[cantidad_ipv4].desde +inmemroyArray[cantidad_ipv4].cant ;
				//printf("pais = %s , ip = %s , cant = %d   int desde %l , inthasta %d, int result = %d \n", inmemroyArray[cantidad_ipv4].pais,inmemroyArray[cantidad_ipv4].ip, 	inmemroyArray[cantidad_ipv4].cant,
				//inmemroyArray[cantidad_ipv4].desde , inmemroyArray[cantidad_ipv4].hasta, inmemroyArray[cantidad_ipv4].hasta-inmemroyArray[cantidad_ipv4].desde);

				cantidad_ipv4++;

			}
			/*
			printf("%s \n",charsdata[0]);
			printf("%s \n",charsdata[1]);
			printf("%s \n",charsdata[2]);
			printf("%s \n",charsdata[3]);
			printf("%s \n",charsdata[4]);
			printf("%s \n",charsdata[5]);
			printf("%s \n",charsdata[6]);
			*/
			

			memset(line,0,sizeof(line));
			cantidad_registros++;
		}
      }
      else {
        break;     /* ...break when EOF is reached */
      }
    }

  //    printf("\n\nNow closing file...\n");
  //  printf("\n\nCatidad de registros... %d \n",cantidad_registros);
  //  printf("\n\nCatidad de cantidad_ipv4... %d \n",cantidad_ipv4);
	qsort (inmemroyArray, TAMANO, sizeof (inmemroyArray[0]), critter_cmp);
	cantidad_ipv4=0;
/*
	for (cantidad_ipv4=0; cantidad_ipv4<TAMANO ;cantidad_ipv4++)
	{
		if (inmemroyArray[cantidad_ipv4].desde !=0)
		{
			printf("pais = %s , ip = %s , cant = %d   int desde %d , inthasta %d, int result = %d \n", inmemroyArray[cantidad_ipv4].pais,inmemroyArray[cantidad_ipv4].ip, 	inmemroyArray[cantidad_ipv4].cant,
			inmemroyArray[cantidad_ipv4].desde , inmemroyArray[cantidad_ipv4].hasta, inmemroyArray[cantidad_ipv4].hasta-inmemroyArray[cantidad_ipv4].desde);
		}
	}
*/

    fclose(file);
    return ;
  }




}

void stop ()
{
	// drop database from memory
}



int 
critter_find (IP_PAIS *c1, IP_PAIS *c2)
{

  if ((c1->desde >= c2->desde ) && (c1->hasta <= c2->hasta ))
  {
	return 0;
  }
  else
  {
   if (c1->desde < c2->desde ) 
   {
	 return -1;
   }
	else
	{
	 return 1;
	}

  }



}


PIP_PAIS  search (char *ip)
{
  struct sockaddr_in antelope;

  IP_PAIS apais;
  memset(&apais,0,sizeof(apais));
  inet_aton(ip, &antelope.sin_addr); // store IP in antelope
  apais.desde = LONGSWAP(antelope.sin_addr.s_addr);
  apais.hasta = LONGSWAP(antelope.sin_addr.s_addr);


  void* results = bsearch (&apais, inmemroyArray, TAMANO,  sizeof (inmemroyArray[0]),
		    critter_find);
  if (results==NULL)
  {
	return NULL;
  }
	else
	{

	PIP_PAIS result = (PIP_PAIS )results;
	return result;
	}
}



/*
int main(int argc, char *argv[])
{
	start();
  PIP_PAIS result =search(argv[1]);
  if (result)
	{
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
*/
