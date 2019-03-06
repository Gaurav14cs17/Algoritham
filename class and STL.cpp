//https://codeforces.com/contest/913/problem/C



#include"bits/stdc++.h"
using namespace std;

class fraccion{
public :
long long a , b;
fraccion(long long num , long long den ){
this->a = num;
this->b = den;
}
};

bool operator<( const fraccion f1 , const fraccion f2 ){
return ( f1.a * f2.b < f1.b *f2.a);
}


priority_queue<fraccion>pq;
vector<long long >v(40);
int cst[800];
long long n , L ;


long long solve( long long ans ){
if(pq.size()==0 ) return ans;

fraccion f = pq.top();
pq.pop();

long long k = L/f.a;
ans = ans + k*f.b;
L = L - k*f.a;
return min( ans + f.b , solve(ans ));
}


int main( void ){
scanf("%d%lld",&n,&L);
for( int i = 1 ; i<=n ; ++i ) {
        scanf("%d",cst+i);
        pq.push(fraccion(  (1<<(i-1))  , cst[i]  ));
}
cout<<solve(0);
}
