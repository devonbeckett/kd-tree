#include <stdio.h>
#include <strings.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <signal.h>
#include "kdtree.h"
#include "cv.h"

int sockfd; // The socket pointer you'll use
KDTreeNode* T; // The tree storing the pictures
void cleanExit() {
	// close sockfd
	close(sockfd);
	exit(0);
}

void loadImageTree(int numImages, char ** fileNames) {
	int i; // used for looping
	// TODO: allocate an array of numImages IplImage* s
	T = NULL;
	// TODO: iterate over each filename
	for(i=0;i<numImages;i++){
		// TODO: load the image via the cvLoadImage function
		IplImage* img = cvLoadImage(fileNames[i], CV_LOAD_IMAGE_UNCHANGED);
		
		// TODO: check if the file could not be loaded.
		if(img->imageData == NULL){
		// if it could not, print an error to stderr and return NULL
			fprintf(stderr, "Could not load file %s\n", fileNames[i]);
			continue;
		}
		T = insert(create(img, fileNames[i]), T);
	}
}

int handle_request(char * req, char* rv) {
	//char * rv; // This will be our return value
	char * res; // This will point to a location in rv where we can write the html to.
	char * ftoken; // this will be a token that we pull out of the 'path' variable indicating the function
	               // for example, if you go to http://localhost:8000/?f=fib&n=10, this will be "f=fib"
	char * ctoken; // A token representing the argument to the function, i.e., "c=10/50/76"
	char * tmp; // used to point to where the arguments start
	char* c1;
	char* c2;
	char* c3;
	int responseLength;

	// TODO: allocate a big chunk of memory for the result. Like 2048 characters
	
	// TODO: write the first line of the HTML header to rv.
	// see http://www.opencalais.com/HTTPexamples for some examples
	// you only need to write the first few lines here.
	sprintf(rv,"%s", "HTTP/1.1 200 OK\n");
	responseLength = strlen("HTTP/1.1 200 OK\n");
	// FREEBEE: set the 'res' pointer to be in the location after the header
	res = &(rv[responseLength]);

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
		ctoken = strtok(NULL, "&");
		// TODO: advance the atoken to remove the "n="
		ctoken = ctoken+2;
		// TODO: see if 'ftoken' is any of our functions
		
		if(ftoken!=NULL && ctoken!=NULL){
			// TODO: if ftoken is "f=fib", call fib and print results to res
			if(strncmp(ftoken, "f=getImageByColor", 17) == 0){
				FILE* f;
				c1 = strtok(ctoken,"/");
				c2 = strtok(NULL,"/");
				c3 = strtok(NULL," ");
				int color[3] = {atoi(ctoken), atoi(c2), atoi(c3)};
				int flen;
				f = fopen(findNearest(color, T, NULL)->path, "r");
				if(f != NULL){
					fseek(f, 0, SEEK_END);
					flen = ftell(f);
					fseek(f, 0, SEEK_SET);
					res = res + sprintf(res, "Content-Length: %d\n", flen);
					res = res + sprintf(res, "Content-Type: image/jpeg\n\n");
					responseLength = strlen(rv);
					char* buff = (char*)malloc(flen+1);
					int flen2 = fread(buff,1,flen,f);
					memcpy(res, buff, flen);
					responseLength += flen;
					fclose(f);				
				} else {
					sprintf(res, "\nNo File");
				}
			}
		}
	}
	return responseLength;
}

#define BUFFSIZE 4096

int main(int argc, char *argv[]) {
	signal(SIGTERM, cleanExit);
	signal(SIGINT, cleanExit);
	int newsockfd; // The socket you get with a connection
	int port; // The port you listen on
	int clilen; // The length of the client's address
	char* res; // stores the result
	int numberOfImages;
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

	// The number of images passed in
	numberOfImages = argc - 2;

	// Load the thumbnail images
	printf("Loading images...");
	loadImageTree(numberOfImages, argv + 2);
	printf("Done\n");
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
			printf("%s\n", buffer);
			res = (char*) malloc(BUFFSIZE * sizeof(char));
			int l = handle_request(buffer, res);
			write(newsockfd, res, l ,0);
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