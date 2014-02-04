//matrix representation
//calloc goes to new or use vector
//printf goes to use of "<<"
//struct becomes class
//advanced make_  becomes a constructor

//assignment 2 

#include <iostream>
#include <vector>
#include <queue>
#include <ctime>
#include <cstdlib>
#include <limits> // for numeric_limits
#include <set>
#include <utility> // for pair
#include <algorithm>
#include <iterator>
#include <list>

//to make the print easier
using namespace std;

typedef int vertex_n;
typedef double weight_n;

const weight_n max_weight = numeric_limits<double>::infinity();
//use inline
inline double probability(){ return 1.0*rand()/RAND_MAX;}

struct node 
{
  vertex_n target;
  weight_n weight;
  node(vertex_n temp_target, weight_n temp_weight)
    : target(temp_target), weight(temp_weight) {}
};


//made a class instead of struct
class graph{
public:
  vector<vector<node>> edgeList;
	
  //struct node tempNode;
	//the constructer the 6 and 0.5 is just use as the default
	graph(int s = 6, double d = 0.5){
		//set size to the s input
		size = s;
    
   	//resize the vector
    edgeList.resize(size);
    //cycle through the graph
   	for(auto i = 0; i < size; i++)
   	{
      edgeList.resize(size);
      for(auto j = 0; j < size; j++)
      {
        if(probability()< d)
        {
          auto pred = [j](const node & item) {
            return item.target == j;
          };
          if(find_if(begin(edgeList[i]), end(edgeList[i]), pred) != end(edgeList[i]) )
          {
            continue;
          }
          int randomNum = ((1.0*rand()/RAND_MAX)*100)+1;
          edgeList[i].push_back(node(j,randomNum));
          edgeList[j].push_back(node(i,randomNum));
        } 
      }
    }
	}

  int getSize()
  {
    return size;
  }

private:
  //size of the graph
  int size;


};

void dijkstra(vertex_n beginning, vector<vector<node>> &edgeList, 
              vector<weight_n> &min_distance, vector<vertex_n> &previous){
  int sizeOf = edgeList.size();
  min_distance.clear();
  min_distance.resize(sizeOf, max_weight);
  min_distance[beginning] = 0;
  previous.clear();
  previous.resize(sizeOf, -1);
  set<pair<weight_n, vertex_n>> vertex_queue;
  vertex_queue.insert(make_pair(min_distance[beginning], beginning));
  while (!vertex_queue.empty())
  {
    weight_n dist = vertex_queue.begin()->first;
    vertex_n u = vertex_queue.begin()->second;
    vertex_queue.erase(vertex_queue.begin());
 
        // Visit each edge exiting u
    vector<node> neighbors = edgeList[u];
    for (int j = 0; j<neighbors.size(); j++)
    {
      vertex_n v = neighbors[j].target;
      weight_n weight = neighbors[j].weight;
      weight_n distance_through_u = dist + weight;
      if (distance_through_u < min_distance[v]) {
          vertex_queue.erase(make_pair(min_distance[v], v));
 
          min_distance[v] = distance_through_u;
          previous[v] = u;
          vertex_queue.insert(make_pair(min_distance[v], v));
 
      }
    }
  }
}


void print_edgeList( vector<vector<node>> edgeList )
{
  for(int i = 0; i<edgeList.size(); i++)
  {
    for(int j = 0; j<edgeList[i].size(); j++)
    {
      cout << "\n" << i << " and " << edgeList[i][j].target << " edge= " << edgeList[i][j].weight << endl;
    }
  }
}

void print_distance( vector<weight_n> v)
{
  for(int i = 0; i<v.size(); i++)
  {
    cout << i << " : " << v[i] << endl;
  }
}

int main()
{
   //set the random base on time
   srand(time(0)); 
   cout << "Test simple graph generation" << endl;
   graph test1(5, 0.3);
   print_edgeList(test1.edgeList);
   vector<weight_n> min_distance;
   vector<vertex_n> previous;
   dijkstra(0, test1.edgeList, min_distance, previous);
   print_distance( min_distance );
   cout << "Distance from 0 to 4: " << min_distance[4] << endl;
   cout << endl << "END of TEST 1" << endl << endl;

   return 0;
}


