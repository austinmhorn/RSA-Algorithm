#include <iostream>
#include <cmath>
#include <string>
using namespace std;

#define ULONG unsigned long int

/*
	The first task we hit is to calculate a fairly small
	number (e) that shares no factors (m)

	m = (P-1)*(Q-1)
	now, find e such that greatest common divisor (GCD) of
	e and m is 1.
*/

ULONG gcd(ULONG x, ULONG y)
// Calculates the greatest common divisor of x and y
{
	if(!x)
		return y;
	return gcd(y%x, x);
}

/*
	Next: Find the integer d, such that: (d * e) % m == 1
	this is called the "modular congruence" of e and m.  To
	do that, we will use another version of the GCD function
	known as "Euclid's Extended Algorithm.  I could have
	overloaded the name; however, I don't want them confused,
	so I will name them differently.
*/

// Function for extended Euclidean Algorithm
ULONG gcdExtended(ULONG a, ULONG b, ULONG* x, ULONG* y)
{
    // Base Case
    if (a == 0)
    {
        *x = 0, *y = 1;
        return b;
    }

    // To store results of recursive call
    ULONG x1, y1;
    ULONG gcd = gcdExtended(b % a, a, &x1, &y1);

    // Update x and y using results of recursive
    // call
    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}
/*
	Now, the gcdExtended will be used to calculate the
	modular congruence. (These are a pair.)
*/
ULONG modularCongruence(ULONG a, ULONG m)
{
    ULONG x, y;

    //ULONG g =
	gcdExtended(a, m, &x, &y);
	return (x % m + m) % m;
}

/*
	Finally, we will need to compute (A^B)%C
	which is the heart of the RSA algorithm.
*/
ULONG computeRsa(ULONG a, ULONG b, ULONG c)
// Calculates (a^b)%c
{
	ULONG y, z, i, j, k;
    y=a; z=(ULONG)1;

	j=ceil(log(b+1)/log(2))*8;

	for(i=1,k=1; k<=j; k++,i=i<<1)
    {
		if(b&i)
		{
        	z = z * y % c;
		}
		y = y * y % c;
	}
	return z;
}

int main(void)
{
    ULONG p = 71;          // First prime
    ULONG q = 73;          // Second prime
    ULONG n = p * q;       // Greatest value THIS code can encrypt
    ULONG m = (p-1)*(q-1); // Value used for finding greatest common divisor
    ULONG e = 2;           // Derived number (may increase inside the following loop)
    ULONG d = 2;
    
    // Find Public Key / Derived Number (e)
    while( gcd(e, m)!=1 )
        e++;
    
    // Calculate Private key (d) such that (d * e) % m == 1
    d = modularCongruence(e,m);
    
    // Print values to terminal
    cout<<'\n'<<"p = "<<p<<", "<<"q = "<<q<<'\t'<<" are SECRET!"<<'\n'<<endl;
    cout<<"n = "<<n<<endl;
    cout<<"m = "<<m<<endl;
    cout<<"e = "<<e<<endl;
    cout<<"d = "<<d<<'\n'<<endl;
    
    // Print public and private key values
    cout<<"public key:"<<'\t'<<e<<'\t'<<n<<endl;
    cout<<"private key:"<<'\t'<<d<<'\t'<<n<<'\n'<<endl;
    
    string str = ""; // Stores line from terminal
    ULONG ch;        // Stores a character read from the terminal
    ULONG c;         // Stores RSA Encrypted Ciphertext
    ULONG dc;        // Stores Decrypted Ciphertext
    
    // Loop continues until the user enters an empty line
    while (true)
    {
        // Prompt user for char
        cout<<"Enter a character: ";
        // Read line of input from terminal
        getline(cin, str);
        
        // If user enters an empty line, exit loop
        if ( str.empty() )
            break;
        
        // Assign (ch) the first character in stream buffer
        ch = (ULONG) str[0];
        // Fetch encrypted ciphertext using RSA algorithm
        c = computeRsa(ch,e,n);
        // Decrypt the output  RSA algorithm
        dc = computeRsa(c,d,n);
        
        // Print values to terminal
        cout<<"Plain text:        "<<static_cast<int>(ch)<<endl;
        cout<<"Cryptotext:        "<<c<<endl;
        cout<<"Decrypted Output:  "<<dc<<'\t'<<static_cast<unsigned char>(dc)<<'\n'<<endl;
    }
    
	return 0;
}
