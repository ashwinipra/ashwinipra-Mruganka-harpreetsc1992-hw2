#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <inttypes.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>
#include <getopt.h>
#include <string.h>
#include <sys/socket.h>


static char* port;
static char* server_ip;


/*
 * Print a usage message
 */
static void
usage(const char* progname) 
{
	printf("Usage:  ./conv_server portnum\n");
}

/*
 *If connection is established then send out welcome message
 */

//--TODO: add your converting functions here

void
process(int sock)
{
	int n;
	int i=0;
	int BUFSIZE = 1024;
    	char buf[BUFSIZE];
    	char* msg = "Welcome, you are connected to a C-based server\n";
    	char* userInput;
	char* token;
	char* values[3];

	int j = 0;
	for(; j < 3; j ++) {
		values[i] = NULL;
	}
	const char s[2]=" ";
	float num = 0.0f,output = 0.0f;
	char op[BUFSIZE];
	bzero(op, BUFSIZE);
    /* Write a welcome message to the client */
	n = write(sock, msg, strlen(msg));
	
    	if (n < 0)
	{
        	perror("ERROR writing to socket");
	        exit(1);
	}
	

    /* read and print the client's request */
    	bzero(buf, BUFSIZE);
    	n = read(sock, buf, BUFSIZE);
    	if (n < 0)
	{
	        perror("ERROR reading from socket");
	        exit(1);
	}
    	userInput = buf;
    	printf("Received message: %s\n", userInput);

#if 1
	token=strtok(userInput,s);
	while(token!=NULL)
	{
		if(i > 3) break;
		values[i]=malloc(strlen(token)+1);
		strcpy(values[i],token);
		values[i][strlen(token)] = '\0';
		printf("%s\n",values[i]);
		if(i == 2) num = atof(values[i]);
		token=strtok(NULL, s);
		i++;
	}
	if(i != 3) {
		printf("invalid input\n");
		return;
	}
	if((strcmp(values[0], "kg")==0) && (strcmp(values[1], "lbs")==0))		//kg<->lbs
	{
		output=num*2.2f;
	}
	else if ((strcmp(values[0], "lbs")==0) && (strcmp(values[1], "kg")==0))		//lbs<->kg
	{
		output=num/2.2f;
	}
	sprintf(op,"%f\n",output);
	send(sock,op,strlen(op),0);
	j = 0;
	for(; j < 3; j ++) {
		if(values[j]) free(values[j]);
		values[j] = NULL;
	}
#endif
    	close(sock);
}

/*
 * Server
 */
int
server( void )
{
    int optval = 1;
    int sockfd, newsockfd;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    int  n;

    /* First call to socket() function */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);

    if (sockfd < 0){
        perror("ERROR opening socket");
        exit(1);
    }
    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(atoi(port));
    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0){
        perror("ERROR on binding");
        exit(1);
    }
    /* Listening for the client */
    listen(sockfd,5);
    clilen = sizeof(cli_addr);

    /* Loop forever receiving client connections */
    while(1) {
        /* Accept connection from the client */
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
        if (newsockfd < 0){
            perror("ERROR on accept");
            exit(1);
        }
        printf("Accepted connection from client\n");
        /* Process a client request on new socket */
        process(newsockfd);
    }

    /*clean up*/
    close(sockfd);

    return 0;
}

int main(int argc, char ** argv){

    const char* progname = argv[0];

    //--TODO: add arguments exception handling here
    if (argc != 2){
        usage(progname);
        exit(1);
    }
    port = argv[1];
    if (server() != 0){
        printf("server in trouble\n");
        exit(1);
    }
}
