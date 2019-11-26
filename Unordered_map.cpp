#include<bits/stdc++.h>

using namespace std;

#define SLOTS 1000

template<class A ,class B>
struct return_val
{
	B value;
	int status;
};

template<class A ,class B>
class node
{
	public:
		A key;
		B val;
		node *next;

		node()
		{
			next = NULL;
		}

		node(A k ,B v)
		{
			next = NULL;
			key = k;
			val = v;
		}
};

template<class A ,class B>
class Unordered_map
{
	public:

		node<A,B> *ht[SLOTS];

		Unordered_map()
		{
			for(int i=0 ;i<SLOTS ;i++)
			{
				ht[i] = new node<A,B>();

				ht[i]->key = 0;
				ht[i]->next = NULL;
			}
		}

		long long int h_fun(A k)
		{
			//DJB2
			ostringstream o;
			o<<k;

			string temp = o.str();

			long long int hash_val = 5318;

			for(int i=0 ;i<temp.size() ;i++)
    		{
    			hash_val = ( ((hash_val << 5) + hash_val) + (int)temp[i] )%SLOTS ; 
			}

			return (hash_val)%SLOTS;
		}

		void insert(A k ,B v)
		{
			int pos = h_fun(k);

			node<A,B> *trav = ht[pos];

			while( trav->next != NULL )
			{
				if( trav->val == v && trav->key == k )
				{
					return ;
				}
				else if( trav->key == k )
				{
					trav->val = v;
					return ;
				}

				trav = trav->next;
			}

			node<A,B> *n = new node<A,B>(k,v);
			trav->next = n;
		}

		struct return_val<A,B> find_val(A k)
		{
			int pos = h_fun(k);

			node<A,B> *trav = ht[pos];

			if( trav->next == NULL )
			{
				struct return_val<A,B> temp;
				temp.status = 0;
				//temp.value = NULL;

				return temp;
			}
			else
			{
				while( trav != NULL )
				{
					if( trav->key == k )
					{
						struct return_val<A,B> temp;
						temp.value = trav->val;
						temp.status = 1;
						
						return temp;
					}

					trav = trav->next;
				}

				struct return_val<A,B> temp;
				//temp.value = NULL;
				temp.status = 0;

				return temp;
			}
		}

		void erase(A k)
		{
			int pos = h_fun(k);

			node<A,B> *trav = ht[pos];
			node<A,B> *prev = NULL;

			if( trav->next == NULL )
			{
				return;
			}
			else if( trav->next != NULL && trav->next->key == k )
			{
				node<A,B> *temp = trav->next ;
				trav->next =trav->next->next;
				free(temp);

				return;
			}
			else
			{
				while( trav != NULL )
				{
					if( trav->key == k )
					{
						prev->next = trav->next;
						free(trav);

						return;
					}

					prev = trav;
					trav=trav->next;
				}

				return ;
			}
		}

		void print()
		{
			
		}
};

main()
{
	Unordered_map<int ,string> m;

	m.insert(4,"hi");
	m.insert(10,"tirth");
	m.insert(56,"hello");
	m.insert(100,"ABCD");
	m.insert(1,"YOU");
	m.insert(4,"FUN");
	

	// struct return_val<int,string> temp = m.find_val(1);
	// cout<<temp.value<<endl;

	return 0;
}