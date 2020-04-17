/*
 * echo.c --
 *
 *	Produce a page containing all FastCGI inputs
 *
 *
 * Copyright (c) 1996 Open Market, Inc.
 *
 * See the file "LICENSE.TERMS" for information on usage and redistribution
 * of this file, and for a DISCLAIMER OF ALL WARRANTIES.
 *
 */
#ifndef lint
static const char rcsid[] = "$Id: echo.c,v 1.5 1999/07/28 00:29:37 roberts Exp $";
#endif /* not lint */

#include "fcgi_config.h"
#include <stdlib.h>
#ifdef HAVE_UNISTD_H
#include <unistd.h>
#endif

#ifdef _WIN32
#include <process.h>
#else
extern char **environ;

#endif

#include "fcgi_stdio.h"
#include "getpais.h"


static void PrintEnv(char *label, char **envp)
{
    printf("%s:<br>\n<pre>\n", label);
    for ( ; *envp != NULL; envp++) {
        printf("%s\n", *envp);
    }
    printf("</pre><p>\n");
}

int main ()
{
    char **initialEnv = environ;
    int count = 0;
	start();
    while (FCGI_Accept() >= 0) 
	{
		 char *contentLength = getenv("CONTENT_LENGTH");
		/////////////////
		char *ip = getenv("REMOTE_ADDR");
		char *cookie = getenv("HTTP_COOKIE");
		char *aget = getenv("QUERY_STRING");

		char *acharpais;

		int len;
			PIP_PAIS  ar =  search (ip);
			if (ar)
			{
				acharpais =	ar->pais;
			}
			else
			{
				
				acharpais = "XX";
			}

		printf("Content-type: text/html\r\n"
			   "Set-Cookie:geo=%s;\r\n"
			   "\r\n", acharpais);
			if (contentLength != NULL) {
				len = strtol(contentLength, NULL, 10);
			}
			else 
			{
				len = 0;
			}

			if (len <= 0) 
			{
				//printf("Post: No Post<br>");
			}
			else 
			{
				int i, ch;
				//printf("Post:");
				for (i = 0; i < len; i++) 
				{
						if ((ch = getchar()) < 0) 
						{
							//printf("Error: Not enough bytes received on standard input<p>\n");
							break;
						}
						putchar(ch);
				}
				//printf("<br>");
			}
			//PrintEnv("Request environment", environ);
			//printf("IP: %s <br>",ip);
			/*
			if (ar)
			{
				printf("Pais ip: %s , %s <br>\n", ip, ar->pais);
			}
			*/
			if (cookie!=NULL)
			{
			//	printf("Cookie: %s<br>\n",cookie);
			}
			PIP_PAIS dar=NULL;
			if (aget!=NULL)
			{
				if (strlen(aget)!=0)
				{
					//printf("Pais Get: %s  <br>\n", aget );
					dar =  search (aget);
					if (dar!=NULL)
					{
						printf("Pais Get: %s  ->%s <br>\n", aget , dar->pais);
					}
				}

			}
    } /* while */

    return 0;
}
