#include "hash.h"

unsigned char* SSHA(const unsigned char* msg, size_t length) {
    unsigned char A, B, C, D, E; //Initial Seed Value
    A = 56;
    B = 99;
    C = 102;
    D = 67;
    E = 76;

    for (int i = 0; i < length; i++) {
        for (int round = 0; round < 8; round++) {
            unsigned char g = (B & C) | (C & D);
            unsigned char old_A = A;
            A = E;
            E = (g + msg[i] + B);
            D = (old_A >> 2)^(B >> 1);
            C = ((old_A>>2) + E);
            B = old_A;
        }
      
    }
    unsigned char* digest = (unsigned char*)malloc(DIGEST_SIZE * sizeof(unsigned char));
    digest[0] = A;
    digest[1] = B;
    digest[2] = C;
    digest[3] = D;
    digest[4] = D;
    return digest;
}

unsigned char* SSHA2(const unsigned char* msg, size_t length)
{
    unsigned char A = 0;
    unsigned char B = 0;
    unsigned char C = 0;
    unsigned char D = 0;
    unsigned char E = 0;

    for (size_t i = 0; i < length; i++)
    {
        /* Save the old state because all operations
           in the diagram use the previous A-E values. */
        unsigned char oldA = A;
        unsigned char oldB = B;
        unsigned char oldC = C;
        unsigned char oldD = D;
        unsigned char oldE = E;

        /* Operations shown in the diagram */
        unsigned char right2 = oldA >> 2;
        unsigned char right1 = oldB >> 1;

        unsigned char and1 = oldB & oldC;
        unsigned char and2 = oldC & oldD;

        unsigned char orValue = and1 | and2;

        unsigned char xorValue = right2 ^ right1;

        unsigned char eValue = orValue + msg[i];
        unsigned char cValue = right2 + eValue;

        /* Bottom row */
        A = oldE;
        B = oldA;
        C = cValue;
        D = xorValue;
        E = eValue;
    }

    /* Return the five final state bytes */
    unsigned char* hash = malloc(5);

    if (hash == NULL)
        return NULL;

    hash[0] = A;
    hash[1] = B;
    hash[2] = C;
    hash[3] = D;
    hash[4] = E;

    return hash;
}
int digest_equal(struct Digest digest1, struct Digest digest2) {
    return ((digest1.hash0 == digest2.hash0) &&
        (digest1.hash1 == digest2.hash1) &&
        (digest1.hash2 == digest2.hash2) &&
        (digest1.hash3 == digest2.hash3) &&
        (digest1.hash4 == digest2.hash4));
    
}

void printDigest(struct Digest digest) {
    printf("%d %d %d %d %d\n", digest.hash0, digest.hash1, digest.hash2, digest.hash3, digest.hash4);
}
