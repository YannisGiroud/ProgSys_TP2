#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


const char userinfo[]="Gettftp syntax : gettftp hostname filename.\n";

int main(int argc,char** argv){
	//Message si il n'y a pas le bon nb d'argument 
	if(argc<3){
		write(STDOUT_FILENO,userinfo,sizeof(userinfo));
		exit(1); 
	}
	
	else {
		//Récupération de la commande et des arguments 
		char *cmd = argv[0];
		char *adress = argv[1];
		char *filename = argv[2];
		write(STDOUT_FILENO,cmd,sizeof(cmd));
		write(STDOUT_FILENO,adress,sizeof(adress));
		write(STDOUT_FILENO,filename,sizeof(filename));
	}
}
