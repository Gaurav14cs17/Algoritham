
// https://codeforces.com/problemset/problem/272/C

#include"bits/stdc++.h"
using namespace std;

const int INF = int(2e9);

#define PlUS_WRAP(index,n) index = (index+1)%n		//index++; if(index>=n) index=0
#define MINUS_WRAP(index,n) index = (index + n -1)%n 	//index--; if(index<0) index=n-1

const int N = 1e6 + 6;

class Segment_Tree{

private:
	std::vector<long long int>segment;
	std::vector<long long int> arr;
	std::vector<long long int> lazy;
	int n;


	void push( int node , int l , int r  ){

		if(lazy[node]){
			segment[node] = lazy[node];
			if( l != r-1 ){
				lazy[node+node] = lazy[node];
				lazy[node+node +1] = lazy[node];
			}
			lazy[node] = 0;
		}
	}

	void build( int node , int l , int r ){

		if( l == r-1 ){
			segment[node] = arr[l];
			return;
		}
		int mid = ( l + r )>>1;
		build( node + node , l , mid );
		build( node+node+1 , mid , r );

		segment[node]= max( segment[node+node] , segment[node+node+1]);
	}

	long long range_query( int node , int l , int r , int ql , int qr ){

		if( l >=qr || r <=ql ) return -INF;

		push( node , l , r );

		if( ql <=l && r <= qr ) return segment[node];
		int mid = ( l + r )>>1;
		long long int left_ans = range_query( node + node , l , mid , ql , qr );
		long long int right_ans = range_query( node + node +1 , mid , r , ql , qr);

		return max( left_ans , right_ans );

	}


	void point_update( int node , int l , int r , int idx , int val ){

		if( r <= idx || l > idx  ) return ;

		if( l == r-1 || l == idx ){
			segment[node] = val;
			arr[l] = val;
			return ;
		}

		int mid = ( l + r )>>1;

		point_update( node + node , l , mid , idx , val );
		point_update( node + node +1 , mid  , r , idx , val );

		segment[node] = max( segment[node + node ] , segment[node+node+1]);

	}


	void range_update( int node , int l , int r , int ql , int qr , long long int val ){

		push( node , l , r );
		if( l>= qr ||  r <= ql ) return ;
		if( ql <=l && r <= qr ){

			segment[node] = val;
			if( l != r-1 ){
				lazy[node + node ] = val;
				lazy[node+ node+ 1 ] = val;
			}
			return ;
		}

		int mid = (  l + r )>>1;
		range_update( node + node , l , mid , ql , qr , val );
		range_update( node + node +1 , mid , r , ql , qr , val );

		segment[node] = max( segment[node+node] , segment[node+node+1]);

	}

public:

	Segment_Tree(){
		segment.clear();
		arr.clear();
		lazy.clear();
		n = 0;
	}

	Segment_Tree( std::vector<long long int>& baseArray ){

		arr = baseArray;
		n  = (int)(arr.size());
		segment = std::vector<long long int>(4*n , 0 );
		lazy = std::vector<long long int>(4*n , 0 );
		build( 1 , 0 , n );
	}


	
	Segment_Tree( int *begin , int *end ){

		arr = std::vector<long long int>( begin , end );
		n  = (int)(arr.size());
		segment = std::vector<long long int> (4*n , 0 );
		lazy = std::vector< long long int> (4*n , 0 );
		build( 1 , 0 , n );
	}

	long long query( int l , int  r ){
		return range_query( 1 , 0 , n , l , r);
	}

	void point_update( int idx , int val ){
		point_update( 1 , 0 , n , idx , val );
	}

	void range_update( int l , int r ,long long  int val ){
		range_update( 1 , 0 , n , l ,  r , val );
	}



};


int main(){
    
    int n ;
    scanf("%d",&n);

    std::vector<long long int> v(n);
    for( int i = 0 ; i<n ; ++i ) scanf("%lld",&v[i]);

	Segment_Tree S(v);
	int q;
	scanf("%d",&q);

	while(q--){
		int w , h ;
		scanf("%d%d",&w,&h);

		long long ans = S.query( 0 , w );
		S.range_update( 0 , w , ans + h );

		printf("%lld\n",ans);
	}
}
