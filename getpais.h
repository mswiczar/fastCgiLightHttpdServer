typedef struct  _IP_PAIS
{
	char pais[4];
	char ip[16];
	int cant;
	unsigned int  desde;
	unsigned int  hasta;
}IP_PAIS , *PIP_PAIS ;

void start();
PIP_PAIS  search (char *ip);
void stop();

