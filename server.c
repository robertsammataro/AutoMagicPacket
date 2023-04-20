//Robert Sammataro
//April 2023
//
//All this because Xfinity doesn't wanna support static IP lol

#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

#define PORT 5000
#define DEST_IP "XXX.XXX.XXX.XXX"
#define DEST_MAC "AA:BB:CC:DD:EE:FF"

#define SA struct sockaddr

//Receive the client's desired file and send them packets with the data
void processUDPTransfer(int sockid, struct sockaddr_in servaddr)
{

	char receive_buffer[4];

	int addrLen = sizeof(servaddr);
	recvfrom(sockid, receive_buffer, sizeof(receive_buffer), 0, (struct sockaddr *)&servaddr, &addrLen);
	printf("Received message %s\n", receive_buffer);

}


//Establish the connection and run the main program once
//Successfully connected to a client
int main(int argc, char* argv[])
{

	int sockid, connection, addrLen;
	struct sockaddr_in servaddr, clientAddr;

	//Set up UDP connection
	sockid = socket(AF_INET, SOCK_DGRAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	bind(sockid, (SA*)&servaddr, sizeof(servaddr));

	close(sockid);
	return 0;
}