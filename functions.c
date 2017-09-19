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
lo que hace es tener un string con un separador = delimiter, que 
cuando encuentra el inicio (start) empieza a copiar lo que tenga 
en array y termina cuando encuentra el final (stop)
*//*
char * split_string_str(char * str, char *delimiter, char * start, char * stop){
	char* token;
	char* string;
	char* del;
	char* tofree;
	char* init; // este va a copiar lo de start con strdup, en la mayoria de los casos le pido que sea GET
	char* stahp; // copia lo de stop, y probablemente sea HTTP1.1 algo asi
	int foundInit = 0 ; // bandera para cuando encuentra el inicio, asi sabe que tiene que copiar lo q sigue en el array
	int afterInit = 0;  //caso especial porque no quiero que se copie con un " " al inicio. 
	char array[1000];
	char * a[1]; // solo lo hice para devolver la respuesta sino daba segfault D: 
	string = strdup(str);
	init = strdup(start); 
	stahp = strdup(stop); 
	del = strdup(delimiter);
	bzero(array,1000);
	if (string != NULL) {
	  tofree = string;
	  while ((token = strsep(&string, del)) != NULL)
	  {
	  	

	  	if(!strcmp(token, stahp)){
	  		foundInit = 0; 
	  		break; 
	  	}
	  	

	  	else if(foundInit == 1 && afterInit == 0){
	  		strcat(array," "); 
	  		strcat(array, token); 
	  	}
	  	else if(foundInit == 1 && afterInit == 1){
	  		strcat(array, token); 	
	  		afterInit = 0; 
	  	} 
	  	else if (!strcmp(token, init)){
	  		foundInit = 1 ; 
	  		afterInit = 1 ; 
	  	}
	 
	  }
	 
	}
	printf("JEJE: @%s@\n", array);
	a[1] = array; 
	return a[1];

}*/

char * makeSpaceHTTP(char * str, char *delimiter){
	char* token;
	char* string;
	char* del;
	char* tofree;
	char array[1000];
	char * a[1]; // solo lo hice para devolver la respuesta sino daba segfault D: 
	string = strdup(str);
	del = strdup(delimiter);
	bzero(array,1000);
	if (string != NULL) {
	  tofree = string;
	  int first = 1; 
	  int counter = 1; 
	  while ((token = strsep(&string, del)) != NULL)
	  {
	  	
		if(first==1){
			strcat(array, token); 
			first = 0; 
		}	  	
		else if(counter == 3){
			strcat(array," "); 
			strcat(array, token); 
			counter = 1; 
		}
	  	else{
	  		strcat(array, token); 
	  		counter++; 
	  		
	  	}
	 
	  }
	 
	}
	a[1] = array; 
	return a[1];

}



