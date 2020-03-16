#include <bits/stdc++.h>
using namespace std;

bool relprime(int a, int b) {
	int c;
	while (b) {
		c=a;
		a=b;
		b=c%b;
	}
	if (a==1) return true;
	else return false;
}

int sum_up_to(int n) {
	int sum=1;
	for (int i=2; i<=n; ++i) {
		sum+=i;
	}
	return sum;
}

int divisors(int n) {
	bool prime[n+1], primesq[n*n+1];
	int primes_to_n[n];
	
	for (int i = 2; i<=n; ++i) prime[i] = true;
	for (int i = 0; i<=(n*n+1); ++i) primesq[i] = false;
	prime[1] = false;
	
	for (int p = 2; p*p<= n; p++) { 
        if (prime[p] == true) { 
            for (int i = p*2; i <= n; i += p) 
                prime[i] = false; 
        } 
    } 
  
    for (int j=0, p=2; p<=n; p++) { 
        if (prime[p]) { 
            primes_to_n[j] = p; 
  
            primesq[p*p] = true; 
            j++; 
        } 
    }
    
    int ans = 1; 
    for (int i = 0;; i++) { 
        if (primes_to_n[i] * primes_to_n[i] * primes_to_n[i] > n) 
            break; 
  
        int cnt = 1;
        while (n % primes_to_n[i] == 0) { 
            n = n / primes_to_n[i]; 
            ++cnt;
        }
        ans = ans * cnt; 
    } 
  
    if (prime[n]) ans*=2; 
    else if (primesq[n]) ans *= 3; 
    else if (n != 1) ans *= 4; 
    return ans; 
}

int main() {
	int N, P, L;
	scanf("%i", &P);
	for (int p=1; p<=P; ++p) {
		scanf("%i %i", &N, &N);
		L = sum_up_to(N) + 1;
		cout << "1 " << L << endl;
		for (int i=2; i<=N; ++i) {
			
			L-=(divisors(i)-1);
			cout << i << " " << divisors(i) << " " << L << endl;
		}
		printf("%i %i", p, L);
	}
	return 0;
}
