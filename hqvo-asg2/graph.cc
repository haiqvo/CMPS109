//matrix representation
//calloc goes to new or use vector
//printf goes to use of "<<"
//struct becomes class
//advanced make_  becomes a constructor

//assignment 2 

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

//to make the print easier
using namespace std;

//use inline
inline double probability(){ return 1.0*rand()/RAND_MAX;}

//made a class instead of struct
class graph{
public:
	//size of the graph
	int size;
	//2D array for the graph
	vector<vector<bool>> g1;
	//the constructer the 6 and 0.5 is just use as the default
	graph(int s = 6, double d = 0.5){
		//set size to the s input
		size = s;
   		//resize the vector
 		this->g1.resize(size);
 		//cycle through the graph
   		for(auto i =g1.begin(); i != g1.end(); ++i)
   		{
   			i->resize(size);
      		for(auto j = i->begin(); j != i->end(); ++j)
      		{
          		if(probability()< d)
              {
          			*j = true;
          		} 
              else 
              {
          			*j = false;
          		}
      		}
      }
	}

};


//function to print the graph
void print_graph( graph g)
{
	cout << "graph size " << g.size << endl;
   	//foreach loop through the graph
   	for(auto i : g.g1)
   	{
   		cout << endl;
      	for (auto j : i)
      		cout << " " << j << "\t";
   	}
}

int main()
{
   //set the random base on time
   srand(time(0)); 
   cout << "Test simple graph generation" << endl;
   graph test1(10, 0.7);
   print_graph(test1);
   cout << endl << "END of TEST 1" << endl << endl;
   graph test2(8, 0.5);
   print_graph(test2);
   cout << endl << "END of TEST 2" << endl << endl;
   return 0;
}


