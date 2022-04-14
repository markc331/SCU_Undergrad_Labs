//COEN 146L : Lab2, step 3
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
        if (argc != 2) {  // check correct usage
		fprintf(stderr, "usage: %s <n connections> \n", argv[0]);
		exit(1);
	}
        //Declare and values to n (n connections), np (np parralel connections), RTT0, RTT1, RTT2, RTTHTTP, RTTDNS, .. 
        int RTT0 =3;
        int RTT1 = 20;
        int RTT2 = 26;
        int RTTHTTP = 47;
        
        // a.
        int clientrecv = RTT0 + RTT1 + RTT2 + 2*RTTHTTP;

        //b.
        int objectrecv = clientrecv + (6*2*RTTHTTP);

        printf("One object: %d msec\n", clientrecv);
        printf("Non-Persistent 6 objects: %d msec\n", objectrecv);

        //c. find how many np (parralel connections)
        int n = atoi(argv[1]);
        int packets = 6/n;
        int max;
        if( 6%n == 0 )
                max = packets;
        else
                max = packets + 1;

        int p = clientrecv + (max*RTTHTTP);
        int np = clientrecv + max*(2*RTTHTTP);
        
        printf("%d parallel connection - Persistent: %d msec\n", n, p);
        printf("%d parallel connection - Non-Persistent: %d msec\n", n, np);

return 0;
}