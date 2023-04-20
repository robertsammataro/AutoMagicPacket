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

#define SIZE 816

#define PORT 50000
#define DEST_MAC "AA:BB:CC:DD:EE:FF\0" //Put your target's MAC address here!
#define PARTIAL "sudo etherwake -i eth0 "

#define SA struct sockaddr

//Loop while waiting for a Magic Packet to arrive to the server
void listenForWOL(int sockid, struct sockaddr_in servaddr)
{

	char receive_buffer[SIZE];
	int addrLen = sizeof(servaddr);
	
	while(1){
	
		recvfrom(sockid, receive_buffer, sizeof(receive_buffer), 0, (struct sockaddr *)&servaddr, &addrLen);
		printf("Received WOL Packet -- Waking up target system\n");
		
		char  partial[24] = PARTIAL;
		char* command = strcat(partial, DEST_MAC);
		system(command); //Relay WOL command to target computer via eth0
		
	}
	

}


//Establish the connection and begin waiting for packets
int main(int argc, char* argv[])
{

	int portId = PORT;
	int sockid, connection, addrLen;
	struct sockaddr_in servaddr, clientAddr;

	//Set up UDP connection
	sockid = socket(AF_INET, SOCK_DGRAM, 0);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	bind(sockid, (SA*)&servaddr, sizeof(servaddr));
	
	printf("Now listening for WOL packets on %d\n", portId);
	
	listenForWOL(sockid, servaddr);

	close(sockid);
	return 0;
}
