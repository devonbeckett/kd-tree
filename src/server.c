#include <stdio.h>
#include <strings.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <signal.h>
#include "kdtree.h"

int sockfd; // The socket pointer you'll use
void cleanExit() {
	// close sockfd
	close(sockfd);
	exit(0);
}

char* handle_request(char * req) {
	char * rv; // This will be our return value
	char * res; // This will point to a location in rv where we can write the html to.
	char * ftoken; // this will be a token that we pull out of the 'path' variable indicating the function
	               // for example, if you go to http://localhost:8000/?f=fib&n=10, this will be "f=fib"
	char * atoken; // A token representing the argument to the function, i.e., "n=10"
	char * tmp; // used to point to where the arguments start

	// TODO: allocate a big chunk of memory for the result. Like 2048 characters
	rv = (char*) malloc(2048 * sizeof(char));
	// TODO: write the first line of the HTML header to rv.
	// see http://www.opencalais.com/HTTPexamples for some examples
	// you only need to write the first few lines here.
	sprintf(rv,"%s", "HTTP/1.1 200 OK\n\n");
	// FREEBEE: set the 'res' pointer to be in the location after the header
	res = &(rv[strlen("HTTP/1.1 200 OK\n\n")]);

	// TODO: check if the request is a GET request.
	if(strncmp(req,"GET", 3) == 0){
	// Use strncmp, see http://www.cplusplus.com/reference/cstring/strncmp/

		// FREEBEE: set the tmp pointer to where the "path" variable begins
		tmp = req+4;
		// TODO: increment tmp point if it points to a '/'
		if(*tmp == '/')
			tmp = tmp+1;
		// TODO: increment tmp point if it points to a '?'
		if(*tmp == '?')
			tmp = tmp+1;
		// TODO: Set the 'ftoken' variable to the first argument of the path variable.
		// Use the strtok function to do this
		// For an example, see http://www.cplusplus.com/reference/cstring/strtok/
		ftoken = strtok((char *)tmp, "&");
		// TODO: set atoken to the n= argument
		//tmp = tmp + strlen(ftoken);
		atoken = strtok(NULL, " ");
		// TODO: advance the atoken to remove the "n="
		atoken = atoken+2;
		// TODO: see if 'ftoken' is any of our functions
		if(ftoken!=NULL && atoken!=NULL){
			// TODO: if ftoken is "f=fib", call fib and print results to res
			if(strncmp(ftoken, "f=fib", 5) == 0)
				sprintf(res, "%d", fib(atoi(atoken)));
			// TODO: if numFiles, call function and print result
			else if(strncmp(ftoken, "f=numFiles", 10) == 0)
				sprintf(res, "%d", numFiles(atoken));
			// TODO: if getFileSize, call function and print result
			else if(strncmp(ftoken, "f=getFileSize", 11) == 0)
				sprintf(res, "%ld", getFileSize(atoken));
			// TODO: if getEnvValue, call function and print result
			else if(strncmp(ftoken, "f=getEnvValue", 11) == 0)
				sprintf(res, "%s", getEnvValue(atoken));
		}
	}
	return rv;
}

#define BUFFSIZE 2048

int main(int argc, char *argv[]) {
	signal(SIGTERM, cleanExit);
	signal(SIGINT, cleanExit);
	int newsockfd; // The socket you get with a connection
	int port; // The port you listen on
	int clilen; // The length of the client's address
	char* res; // stores the result
	int yes = 1;

	struct sockaddr_in serv_addr; // The server's address
	struct sockaddr_in cli_addr; // The client's address

	char buffer[BUFFSIZE]; // a buffer to read results to.
	int n; // number of bytes read

	// set clilent to size of client address struct
	clilen = sizeof(cli_addr);

	// allocate sockfd by calling 'socket'
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Could not open socket");
		return EXIT_FAILURE;
	}

	// You should look up what this does if you don't know.
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const void*)&yes, sizeof(int) );

	// Set the port number based on the first command line argument
	port = (argc > 1) ? atoi(argv[1]) : 8000;

	// Zero-out the server address
	bzero((void*) &serv_addr, sizeof(serv_addr));

	// initialize the socket structure (i.e., set the values of serv_addr)
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(port);

	// bind the host address
	if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		perror("ERROR on binding");
		return EXIT_FAILURE;
	}

	// Listen for a client.
	listen(sockfd, 1);

	while (1) { // go forever!
		// Accept actual connection from the client
		if ((newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen)) < 0) {
			perror("ERROR on accept");
			return EXIT_FAILURE;
		}

		// read from the socket
		if ((n = read(newsockfd, buffer, BUFFSIZE, 0)) > 0) {
			printf("%s", buffer);
			res = handle_request(buffer);
			write(newsockfd, res, strlen(res),0);
			bzero(buffer, BUFFSIZE);
			free(res);
		}

		// close newsockfd
		close(newsockfd);
	}
	// close sockfd
	close(sockfd);

	exit(0);
}