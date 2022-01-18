#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

const char userinfo[]="Gettftp syntax : gettftp hostname filename.\n";
const char* port ="69";

int main(int argc,char** argv){
	struct addrinfo hints;
    struct addrinfo *result, *tmp;
    char host[256];
    
	//Message si il n'y a pas le bon nb d'argument 
	if(argc<3){
		write(STDOUT_FILENO,userinfo,sizeof(userinfo));
		exit(1); 
	}
	
	else {
		//Récupération de la commande et des arguments 
		//char *cmd = argv[0];
		char *adress = argv[1];
		//char *filename = argv[2];
		
		//Parametres de getaddressinfo
		memset(&hints, 0, sizeof(struct addrinfo));
		hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
		hints.ai_socktype = SOCK_DGRAM; /* Datagram socket */
		hints.ai_flags = 0;
		hints.ai_protocol = 0;          /* Any protocol */

		int s = getaddrinfo(adress,port, &hints, &result);
		if (s != 0) {
			fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
			exit(EXIT_FAILURE);
		}
		for (tmp = result; tmp != NULL; tmp = tmp->ai_next) {
			getnameinfo(tmp->ai_addr, tmp->ai_addrlen, host, sizeof(host), NULL, 0, NI_NUMERICHOST);
			write(STDOUT_FILENO,host,strlen(host));  //On affiche l'adresse du serveur
		}
		
		
	}
}
