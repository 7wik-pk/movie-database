#include<iostream>
#include<stdio.h>
#include<fstream>

using namespace std;


class movie
{
	
	int nr;
	char name[15],storyline[250],cast[25],date[10];
	int no,nor;
	float rating;
	
	public:
		
		void rate( int a ){
			
			float b = rating*nor;
			nor++;
			rating = (b + a)/nor;
			cout<<"Updated rating: "<<rating<<"\n\n";
			
		}
		
		void input(){
			
			cout<<"Enter the ID of the movie: ";
			cin>>no;
			cout<<"Enter the name of the movie: ";
			cin.ignore();
			gets(name);
			cout<<"Enter the cast of the movie: ";
			gets(cast);
			cout<<"Enter the date of release [DD/MM/YYYY]: ";
			gets(date);
			cout<<"Enter the storyline of the movie: ";
			gets(storyline);
			
		}
		
		void display(){
			
			cout<<"\nMovie ID: "<<no;
			cout<<"\nName of the movie: "<<name<<"\nCast: "<<cast<<"\nDate of release: "<<date<<"\nAverage rating: "<<rating<<"\nStoryline:\n"<<storyline<<"\n\n";
			
		}
		
		int retcertno(){
			
			return no;
			
		}
		
		movie(){
			
			nor=0;
			rating=0;
			
		}
		
};

int isEmpty( istream &f )
{
	if( f.peek() == ifstream::traits_type::eof() )
		return 1;
	return 0;
}

void create(){
	
	movie M;
	ofstream fout;
	fout.open( "DB.dat", ios::binary | ios::out | ios::app );
	M.input();
	fout.write( (char*)&M, sizeof(M) );
	fout.close();
	cout<<"The entry was succesfully created!\n\n";
	M.display();
	
}

void modify(){
	
	fstream f;
	f.open( "DB.dat", ios::in | ios::out | ios::binary  );
	f.seekg(0);

	if( isEmpty(f) )
	{
		cout << "database is empty.\n";
	}

	else
	{
		int n,a;
		cout<<"Enter the movie ID: ";
		cin>>n;
		movie M;
		int z=0;
	
		while( !f.eof() ){
			
			f.read( (char*)&M, sizeof(M) );
			
			if( ( M.retcertno() == n ) && ( !f.eof() ) ){
				
				cout<<"Enter the modified details:\n";
				M.input();
				a = sizeof(M);
				int l = f.tellg();
				f.seekp( l );
				f.seekp( (-a) , ios::cur );
				f.write( (char*)&M, sizeof(M) );
				z=1;
				cout<<"The entry was succesfully modified!\n\n";
				break;
			}
			
		}
		
		if( z=0 )
			cout<<"Movie not found\n";
	
	}
	
	
	f.close();
	
}

void delete_entry(){

	ifstream fin;
	fin.open( "DB.dat", ios::binary );

	if( isEmpty(fin) )
	{
		cout << "database is empty.\n";
		fin.close();
		return;
	}

	int c,z=0;
	cout<<"Enter the ID of the movie you would like to delete:\n";
	cin>>c;
	movie M;

	ofstream fout;
	fout.open( "TEMP.dat", ios::binary );
	fin.seekg(0);
	fout.seekp(0);

	while( !fin.eof() ){
		
		fin.read( (char*)&M, sizeof(M) );
		
		if( M.retcertno() != c )
		{

			if( !fin.eof() )
				fout.write( (char*)&M, sizeof(M) );

		}
		
		else z=1;
		
	}

	fin.close();
	fout.close();

	remove( "DB.dat" );
	rename( "TEMP.dat", "DB.dat" );
	
	if( z == 1 )
		cout<<"The entry was succesfully deleted.\n\n";
		
	else
		cout<<"Movie not found\n";	
	

	
}

void ratemovie(){

	fstream f;
	f.open( "DB.dat", ios::in | ios::out | ios::binary  );
	f.seekg(0);

	if( isEmpty(f) )
	{
		cout << "database is empty.\n";
		f.close();
		return;
	}
	
	int n,z=0;
	int s;
	cout<<"Enter the movie ID: ";
	cin>>n;
	movie M;

	while( !f.eof() ){
		
		f.read( (char*)&M, sizeof(M) );
		
		if( ( M.retcertno() == n ) && ( !f.eof() ) ){
			
			int a;
			cout<<"Enter the rating [1-10]: ";
			cin>>a;
			s = sizeof(M);
			cout<<"The rating was successfully entered!\n";
			M.rate(a);
			f.seekp( f.tellg() );
			f.seekp( (-s) , ios::cur );
			f.write( (char*)&M, sizeof(M) );
			z=1;
			break;
			
		}
	
	
	}
	
	if( z == 0 )
	cout<<"Movie not found\n";
	
	f.close();
	
}


void showev(){

	ifstream fin("DB.dat",ios::binary);
	movie M;
	fin.seekg(0);
	
	if( isEmpty(fin) )
	{
		cout << "database is empty.\n";
	}

	else
	{
		while ( !fin.eof() ){

		fin.read( (char*)&M, sizeof(M) );
		if( !fin.eof() )
			M.display();
		
		}
	}
	
	
	fin.close();

}

void search(){

	movie M;
	fstream f;
	f.open( "DB.dat", ios::in | ios::out | ios::binary );
	
	if( isEmpty(f) )
	{
		cout << "database is empty.\n";
		f.close();
		return;
	}

	int n,z=0;
	cout<<"Enter the movie ID: ";
	cin>>n;
	
	while( !f.eof() ){
		
		f.read( (char*)&M, sizeof(M) );
		
		if( ( M.retcertno() == n ) && ( !f.eof() ) ){
			M.display();	
			z=1;
			break;
		}
	}
	
	if( z == 0 )
		cout<<"Movie not found.\n";
	
	f.close();
	
}

int main(){
	
	cout<<"\nWelcome to the Database of Movies\n";
		
	int a;
	while( a != 7 )
	{
		cout<<"-----------------------------------------------\n";
		cout<<"Enter\n1. create entry\n2. rate a movie\n3. modify an entry\n4. delete an entry\n5. Show details of a particular movie\n6. Show every movie\n7. exit\n";
		cin>>a;
		
		switch(a)
		{

			case 1:
				create();
				continue;
			case 2:
				ratemovie();
				continue;
			case 3:
				modify();
				continue;
			case 4:
				delete_entry();
				continue;
			case 5:
				search();
				continue;
			case 6:
				showev();
				continue;
			case 7:
				break;
			default:
				cout<<"\n\nEnter a valid choice:\n\n\n";
				continue;
				
		}

	}
	
	
	return 0;
	
}
