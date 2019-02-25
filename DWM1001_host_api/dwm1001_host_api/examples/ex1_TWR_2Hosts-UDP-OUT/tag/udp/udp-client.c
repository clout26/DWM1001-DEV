/**
 * UDP Client meant to send locally to node-red
 **/
#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "udp-client.h"

void send_message(char *message)
{
  int message_len = strlen(message);
	int sockfd; // Socket ref
	struct sockaddr_in server_addr;

	// clear server_addr
	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_addr.s_addr = inet_addr(ADDRESS);
	server_addr.sin_port = htons(PORT);
	server_addr.sin_family = AF_INET;

	// create datagram socket
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	// connect to server
	if(connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		printf("\n Error : Connect Failed \n");
		exit(0);
	}

	// request to send datagram
	// no need to specify server address in sendto
	// connect stores the peers IP and port
	sendto(sockfd, message, message_len, 0, (struct sockaddr *)&server_addr, sizeof( server_addr));

	// close socket
	close(sockfd);
}
