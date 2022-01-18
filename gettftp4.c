#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

const char userinfo[]="Gettftp syntax : gettftp hostname filename.\n";
const char* port ="69";

//Fonction d'ecriture de la requete
int RRQ(char* filename, char* mode, char* cmd){
	int cmdlen = 2+strlen(filename)+1+strlen(mode)+1;
	cmd[0]=0;
	cmd[1]=1;
	strcpy(&cmd[2],filename);
	strcpy(&cmd[strlen(filename)+3],mode);
	return cmdlen;
}	
	
	
int main(int argc,char** argv){
	struct addrinfo hints;
    struct addrinfo *result, *tmp;
    char host[256];
    int skt;
 
    
	//Message si il n'y a pas le bon nb d'argument 
	if(argc<3){
		write(STDOUT_FILENO,userinfo,sizeof(userinfo));
		exit(1); 
	}
	
	else {
		//Récupération de la commande et des arguments 
		char cmd[256];
		char *adress = argv[1];
		char *filename = argv[2];
		
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
			write(STDOUT_FILENO,"\n",strlen("\n"));
		}
		
		//Création du socket 
		skt = socket(result->ai_family,result->ai_socktype, result->ai_protocol);
		//Verification de la création du socket
		if (skt==-1){
			write(STDOUT_FILENO,"erreur_socket\n",sizeof("erreur_socket\n"));
			exit(EXIT_FAILURE);
		}
		
		
		int cmdsize=RRQ(filename,"octet",cmd);
		int t = sendto (skt, cmd, cmdsize, 0, result->ai_addr, result->ai_addrlen);  //Envoie de la requete 
		//Verification de l'envoie
		if (t==-1){
			write(STDOUT_FILENO,"erreur_envoie\n",sizeof("erreur_envoie\n"));
			exit(EXIT_FAILURE);
		}
	}
}