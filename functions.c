#include <stdio.h>
#include <stdlib.h>

char * split_string(char * str, char *delimiter, int index){
	char* token;
	char* string;
	char* del;
	char* tofree;
	char * array[100]; 
	string = strdup(str);
	del = strdup(delimiter);
	if (string != NULL) {
	  tofree = string;
	  int i=0;
	  while ((token = strsep(&string, del)) != NULL)
	  {
	    printf("%s\n", token);
	    array[i]=token;
	    i++;
	  }
	  if(index == -1){
	  	index = i-1; 
	  }
	  //free(tofree);
	}
	printf("%s\n", array[index]);
	return array[index];

}
/*
int main(int argc, char *argv[])
{
	char* array[5];
	char * var=split_string("abc,def,ghi", ",", -1);
	printf("Resultado: %s\n", split_string("abc,def,ghi", ",", 0));
	 memmove(var, var+1, strlen(var));
	 printf("Var:%s\n", var);
   
    
    return 0;
}*/
