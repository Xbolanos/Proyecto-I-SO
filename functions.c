#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>


/*This is a function from *George Skoptsov that allows you return a char* */
char* strdup(const char* org)
{
    if(org == NULL) return NULL;

    char* newstr = malloc(strlen(org)+1);
    char* p;

    if(newstr == NULL) return NULL;

    p = newstr;

    while(*org) *p++ = *org++; /* copy the string. */
    return newstr;
}

/*Function that makes little parts from a delimiter and you send 
the index that you need*/
char * getWord(char * text, char * delimiter, int index)
{
	const char *a[100]; 
	char  pch[100];
	char str[] = "";
	strcpy(str, text); 
	strcpy(pch,strtok (NULL, delimiter));
	int i = 0; 
	while (pch != NULL)
	{
		a[i] = pch; 
		i++; 
		strcpy(pch,strtok (NULL, delimiter));
	}
	if(index == -1)
		i = i - 1; 
	printf("1\n");
	strcpy(pch, a[index]);
	printf("3\n");
	printf("pch: %s\n", pch);
	return pch; 
}

int main(int argc, char *argv[])
{
	printf("%s jeje", getWord("GET /holi.html 1,2 . 34", " ", 1));
	printf("2\n");
	
}