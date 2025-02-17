#include<stdio.h>

void main() {
    int incomingPacket, outgoingRate, bucketSize, numInputs, buffer = 0;
    
    printf("Enter bucket size, outgoing rate and number of inputs: ");
    scanf("%d %d %d", &bucketSize, &outgoingRate, &numInputs);

    while (numInputs != 0) {
        printf("Enter the incoming packet size: ");
        scanf("%d", &incomingPacket);
        printf("Incoming packet size %d\n", incomingPacket);

        if (incomingPacket <= (bucketSize - buffer)) {
            buffer += incomingPacket;
            printf("Bucket buffer size: %d out of %d\n", buffer, bucketSize);
        } else {
            printf("Dropped %d packets\n", incomingPacket - (bucketSize - buffer));
            buffer = bucketSize;
            printf("Bucket buffer size: %d out of %d\n", buffer, bucketSize);
        }

        if (buffer >= outgoingRate) {
            buffer -= outgoingRate;
        }

        if (buffer < 0) {
            buffer =buffer*(-1);
        }

        printf("After outgoing, there are %d out of %d packets left in buffer\n", buffer, bucketSize);
        numInputs--;
    }

}

