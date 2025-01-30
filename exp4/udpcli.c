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
    struct sockaddr_in y;

    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return -1;
    }

    // Set up server address
    y.sin_family = AF_INET;
    y.sin_port = htons(PORT);
    // Replace with actual server IP address (e.g., "127.0.0.1" for local testing)
    y.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Connecting to the server...\n");

    while (1) {
        printf("Enter message to send: ");
        fgets(buf, sizeof(buf), stdin);  // Read input with spaces
        buf[strcspn(buf, "\n")] = 0;  // Remove the newline character

        // Send message to server
        sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&y, addr);

        if (strcmp(buf, "quit") == 0)
            break;

        printf("Message sent, waiting for response...\n");

        // Receive response from the server
        n = recvfrom(sockfd, buf, sizeof(buf) - 1, 0, (struct sockaddr*)&y, &addr);
        if (n < 0) {
            perror("recvfrom failed");
            break;
        }

        buf[n] = '\0';  // Ensure the buffer is null-terminated
        printf("\nReceived: %s\n", buf);
    }

    // Close the socket
    close(sockfd);
    return 0;
}

