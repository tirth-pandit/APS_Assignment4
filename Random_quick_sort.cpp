#include <bits/stdc++.h>
#include <time.h>  
using namespace std; 

int my_fun(vector<int> v ,int s ,int e ,int k)
{
	int ans = -1;
	srand(time(0));

	clock_t start = clock();

	while( s <= e )
	{
		int pivot = s + ( std::rand() % ( e - s + 1 ) );

		int t = v[pivot];
		v[pivot] = v[e];
		v[e] = t;

		pivot = v[e];

		int left = s;

		for (int j = s; j <= e - 1; j++) 
		{
			if (v[j] <= pivot) 
			{ 
				swap(v[left], v[j]); 
				left++; 
			} 
		} 

		int temp = v[left];
		v[left] = v[e];
		v[e] = temp;

		if( left == k )
		{
			ans = v[left];
			break;
		}
		else if( left > k )
		{
			e = left -1;
		}
		else
		{
			s = left + 1;
		}

	}

	cout << "Ans :"<<ans<<endl; 

	clock_t stop = clock();

	double duration = ((double)(stop - start)/CLOCKS_PER_SEC); 

	cout<<" Quick Select Function Time : "<<duration<<endl;
}

int main() 
{ 
	int n;
	cin>>n;

	int k;
	cin>>k;

	vector<int> v(n,0);

	for(int i=0 ;i<n ;i++)
	{
		cin>>v[i];
	}

	my_fun(v,0,n-1 ,k);

	clock_t start = clock();
	nth_element(v.begin() ,v.begin()+k ,v.end());

	clock_t stop = clock();

	cout<<"Ans :"<<v[k]<<endl;
	double duration = ((double)(stop - start)/CLOCKS_PER_SEC); 

	cout<<"N_th Element Time Taken :"<<duration<<endl;

	return 0; 
} 
