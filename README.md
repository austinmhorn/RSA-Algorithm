# RSA-Algorithm
Crypto-text generator using RSA public-key crypto-system

- The first task we hit is to calculate a fairly small number (e) that shares no factors (m)

	- m = (P-1)*(Q-1)
  
- Now, find e such that greatest common divisor (GCD) of e and m is 1.

  - ULONG gcd(ULONG x, ULONG y)

- Next: Find the integer d, such that: (d * e) % m == 1 this is called the "modular congruence" of e and m. To do that, we will use another version of the GCD function known as "Euclid's Extended Algorithm. I could have overloaded the name; however, I don't want them confused, so I will name them differently.

  - ULONG gcdExtended(ULONG a, ULONG b, ULONG* x, ULONG* y)

- Now, the gcdExtended will be used to calculate the modular congruence. (These are a pair.)

  - ULONG modularCongruence(ULONG a, ULONG m)

- Finally, we will need to compute (A^B)%C which is the heart of the RSA algorithm.

  - ULONG computeRsa(ULONG a, ULONG b, ULONG c)
