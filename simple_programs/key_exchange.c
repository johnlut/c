#include <stdio.h>
#include <stdlib.h> 
#include <math.h>

int main()
{
    // private keys
    unsigned long p = 337016056721;
    unsigned long q = 192837465;

    // a private key
    unsigned long a = 24242424; 

    //a public key
    unsigned long a_pub = ((long int) powl(q, a))%p; 

    // b private key
    unsigned long b = 56565656; 

    // b public key
    unsigned long b_pub = ((long int) powl(q, b))%p;  

    // a verification on b
    unsigned long x_a = ((long int) powl(b_pub, a))%p; 

    // b verification a
    unsigned long x_b = ((long int) powl(a_pub, b))%p; 

    if(x_a == x_b)
    {   
        printf("%ld\t%ld\n", x_a, x_b);
        printf("truee\n");
    }

    //printf("%ld\n", (p%q));

    return 0; 
}