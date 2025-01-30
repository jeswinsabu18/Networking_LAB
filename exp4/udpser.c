#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include <unistd.h>

#define PORT 4000

int main()
{
    int n, sockfd, addr = sizeof(struct sockaddr_in);
    char buf[1025];
    struct sockaddr_in x;

    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Error in creating socket");
        return -1;
    }
    printf("Socket successfully created\n");

    // Set up server address
    x.sin_family = AF_INET;
    x.sin_port = htons(PORT);
    x.sin_addr.s_addr = htonl(INADDR_ANY);

    // Bind the socket
    bind(sockfd, (struct sockaddr*)&x, sizeof(x));
    printf("Waiting for messages...\n");

    // Loop to receive and respond to messages
    do {
        n = recvfrom(sockfd, buf, sizeof(buf) - 1, 0, (struct sockaddr*)&x, &addr);
        buf[n] = '\0';  // Null-terminate the received string

        if (n > 1) {
            printf("Received: %s\n", buf);
        }

        // Respond to the client
        printf("Reply: ");
        fgets(buf, sizeof(buf), stdin);  // Allow multi-word input from server
        buf[strcspn(buf, "\n")] = 0;  // Remove the newline character

        sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&x, addr);

    } while (strcmp(buf, "quit") != 0);

    // Close the socket
    close(sockfd);
    return 0;
}

