#include<bits/stdc++.h>

using namespace std;

template<class A ,class B>
class an
{
	public:
		A key;
		B val;
		int h;

		an *left;
		an *right;

		an(A k ,B v)
		{
			left = NULL;
			right = NULL;

			h=1;
			key=k;
			val=v;
		}
};

template<class A ,class B>
int get_h(an<A,B> *root)
{
	if(root == NULL) 
	{
		return 0;
	}	
	else
	{
		return root->h;
	}
}

template<class A ,class B>
an<A,B>* l_rot(an<A,B> *n)
{
	an<A,B> *pare = n;

	an<A,B> *child = pare->right;
	an<A,B> *subtree = child->left;

	child->left = pare;
	pare->right = subtree;

	int hl = get_h(pare->left);
	int hr = get_h(pare->right);

	if( hl > hr )
	{
		pare->h = hl;
	}
	else
	{
		pare->h = hr;
	}
	pare->h += 1;

	hl = get_h(child->left);
	hr = get_h(child->right);

	if( hl > hr )
	{
		child->h = hl;
	}
	else
	{
		child->h = hr;
	}
	child->h += 1;

	return child;
}

template<class A ,class B>
an<A,B>* r_rot(an<A,B> *n)
{
	an<A,B> *y = n;
	
	an<A,B> *pare = y->left;
	an<A,B> *subtree = pare->right;

	pare->right = y;
	y->left = subtree;

	int hl = get_h(y->left);
	int hr = get_h(y->right);

	if( hl > hr )
	{
		y->h = hl;
	}
	else
	{
		y->h = hr;
	}
	y->h += 1;

	hl = get_h(pare->left);
	hr = get_h(pare->right);

	if( hl > hr )
	{
		pare->h = hl;
	}
	else
	{
		pare->h = hr;
	}
	pare->h += 1;

	return pare;
}

template<class A ,class B>
an<A,B>* ins( an<A,B> *r ,A k ,B v)
{	
	if( r == NULL)
	{
		return ( new an<A,B>(k,v) );
	}
	else if( k > r->key )
	{
		r->right = ins(r->right ,k ,v);
	}
	else if( k == r->key )
	{
		if( v == r->val )
		{
			return r;
		}
		else
		{
			r->val = v;
			return r;
		}
	}
	else
	{
		r->left = ins(r->left ,k ,v);
	}

	int hl = get_h(r->left);
	int hr = get_h(r->right);

	if( hl > hr )
	{
		r->h = hl;
	}
	else
	{
		r->h = hr;
	}

	int bf;
	if( r == NULL )
	{
		bf = 0;
	}
	else
	{
		bf = get_h(r->left) - get_h(r->right);
	}
	
	if( (bf>1) )
	{
		if((k < (r->left->key)))
		{
			return r_rot(r);
		}
		else
		{
			r->left = l_rot(r->left);
			return r_rot(r);
		}
	}
	if( (bf<-1) )
	{
		if(k >= (r->right->key))
		{
			return l_rot(r);
		}
		else
		{
			r->right = r_rot(r->right);
			return l_rot(r);
		}
	}

	return r;
}

template<class A ,class B>
an<A,B>* find_succ(an<A,B> *root)
{
	an<A,B> *trav = root;

	while( trav->left !=NULL)
	{
		trav = trav->left;
	}

	return trav;
}

template<class A ,class B>
void inorder(an<A,B> *root)
{ 
	if(root == NULL) 
	{
		return;
	}
	else
	{
		inorder(root->left);
		cout << root->key << " " ;
		inorder(root->right);
	}
}

template<class A ,class B>
void search(an<A,B> *root ,A key)
{
	if( root == NULL )
	{
		cout<<"Not Availbale"<<endl;
		return ;
	}

	if( root->key == key)
	{
		cout<<"Availbale :"<< root->val<<endl;
		return;
	}

	if( key > root->key )
	{
		search(root->right ,key);
	}
	else if( key < root->key )
	{
		search(root->left ,key);
	}
}

template<class A ,class B>
int bal(an<A,B> *root)
{
	if (root == NULL)  
	{
        return 0;  
	}
    return get_h(root->left) - get_h(root->right);  
}

template<class A ,class B>
void update_height(an<A,B> *root)
{
	root->h = 1 + max(get_h(root->left), get_h(root->right));  
}

template<class A ,class B>
an<A,B>* rotate(an<A,B> *root)
{
	int balance = bal(root);  

	int l_bal = bal(root->left);
	int r_bal = bal(root->right);
  
    if (balance > 1 && l_bal >= 0)  
    {
		return r_rot(root);  
  	}

    if (balance > 1 && l_bal < 0)  
    {  
        root->left = l_rot(root->left);  
        return r_rot(root);  
    }  
  
    if (balance < -1 && r_bal <= 0)
    {  
        return l_rot(root);  
  	}

    if (balance < -1 && r_bal > 0)  
    {  
        root->right = r_rot(root->right);  
        return l_rot(root);  
    }  

     return root;
}

template<class A ,class B>
an<A,B>* del(an<A,B>* root, A k);

template<class A ,class B>
an<A,B>* del_node(an<A,B> *root )
{
		if( (root->left == NULL) || (root->right == NULL) )  
        {  
        	an<A,B> *temp = NULL ;   	
 
   			if( root->left != NULL )
   			{
   				temp = root->left;
   			}
   			else
   			{
   				temp = root->right;
   			}

            if (temp == NULL)  
            {  
                temp = root;  
                root = NULL;  
            }  
            else
            {   
            	*root = *temp;   
            }

            free(temp);  
        }  
        else
        {  
       
            an<A,B> *temp = find_succ(root->right);  
  
            root->key = temp->key; 
  
            root->right = del(root->right,temp->key);  
        }  

        return root;
}

template<class A ,class B>
an<A,B>* del(an<A,B>* root, A k)  
{  
      
    if (root == NULL) 
    { 
        return root;  
    }

    if( k < root->key )
    {  
        root->left = del(root->left, k);  
    }
    else if( k > root->key )
    {  
        root->right = del(root->right, k);  
  	}
    else
    {  
    	root = del_node(root);
    }  
  
    if (root == NULL)  
    {
    	return root;  
  	}
 	
 	update_height(root); 
  
   	return rotate(root);
}  

template<class A ,class B>
class ordered_map
{
	public:

		an<A,B> *root;

		ordered_map()
		{
			root = NULL;
		}

		void insert(A k ,B v)
		{
			root = ins(root ,k ,v);
		}

		void erase(A k)
		{
			root = del(root,k);
		}

		void find(A k)
		{
			search(root ,k);
		}
};

main()
{
	
	int t;
	cin>>t;

	ordered_map<int ,string> om;
	
	while(t--)
	{
	
		cout<<"1.Insert"<<endl;
		cout<<"2.Search"<<endl;
		cout<<"3.Delete"<<endl;

		cout<<endl<<endl;

		int q;
		cout<<"Enter Query :";
		cin>>q;

		int a;
		string b;

		switch(q)
		{
			case 1:
				cin>>a>>b;
				om.insert(a,b);
				//inorder(root);
				cout<<endl;
				break;

			case 2:
				cin>>a;
				om.find(a);
				break;

			case 3:
				cin>>a;
				om.erase(a);
				//inorder(root);
				break;
		}

	}

	return 0;
}