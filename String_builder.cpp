#include<bits/stdc++.h>

using namespace std;

class string_Node
{
	public:
	
	const char *pointer;
	string_Node *next;

	string_Node()
	{
		pointer = NULL;
		next = NULL;
	}
};

class string_Builder
{
	public:

	string_Node *head;
	string_Node *last;

	int list_len;

	string_Builder()
	{
		head = last = NULL;
		list_len = 0;
	}

	string_Builder(const char *n)
	{
		head = new string_Node();
		last = new string_Node();

		head->pointer = n;
		head->next = NULL;

		last = head;

		list_len = 1;
	}

	void print_string()
	{
		string_Node *trav= head;

		while( trav != last )
		{
			cout<<trav->pointer;
			trav = trav->next;
		}

		cout<<trav->pointer;
	}

};

string_Builder append( string_Builder n1 ,string_Builder n2)
{
	string_Builder temp;

	n1.last->next = n2.head;
	//n1.last = n2.last;

	temp.head = n1.head;
	temp.last = n2.last;

	temp.list_len = n1.list_len + n2.list_len;
	temp.last->next = NULL;

	return temp;
}

char *make_string(string_Builder n, char *s )
{
	int total = 0;

	string_Node *trav = n.head;

	while( trav != n.last)
	{
		total += strlen(trav->pointer);
		trav = trav->next;
	}

	total += strlen(trav->pointer);

	s = new char[total+1];
	
	///////////////////////////////
	
	trav = n.head;
	int c=0;

	while( trav != n.last )
	{
		for(int i=0 ;i<strlen(trav->pointer) ;i++)
		{
			s[c++] = trav->pointer[i];	
		}

		trav = trav->next;
	}


	for(int i=0 ;i<strlen(trav->pointer) ;i++)
	{
		s[c++] = trav->pointer[i];
	}

	return s;
}


int substr(string_Builder n ,const char *str)
{
	char *s = make_string(n ,s);

	vector<int> l(strlen(str));

	l[0] = 0;

	int i=0;

	for(int j=1 ;j<strlen(str) ;)
	{
		if( str[i] == str[j] )
		{	
			i++;
			l[j] = i;
			j++;
		}
		else
		{
			while( str[i] != str[j] )
			{
				if( i == 0 )
				{
					break;
				}

				i = l[i-1];
			}

			if( i==0 )
			{
				l[j] = 0;
				j++;
			}
			else
			{
				l[j++] = ++i;
			}			
		}
	}

	int pat=0,text=0;

	for(text = 0 ;text<strlen(s) ;)
	{
		if( str[pat] == s[text] )
		{
			pat++;
			text++;
		}

		if( pat == strlen(str) )
		{
			return (text - pat);
		}

		if( str[pat] != s[text] )
		{
			if( pat != 0 )
			{
				pat = l[pat-1];
			}
			else
			{
				text++;
			}
		}
	}

	return -1;
}

main()
{
	string_Builder a("Hello");

	string_Builder b("World");

	string_Builder c = append(a,b);

	c.print_string();

	int ans = substr(c ,"lo");

	cout<<endl;
	
	cout<<"Substring present at :"<<ans<<endl;
	//c.print_string();

}