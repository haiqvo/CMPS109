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
          int randomNum = ((1.0*rand()/RAND_MAX)*200)+1;
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

void dijkstra(vertex_n beginning, vector<vector<node>> edgeList, 
              vector<weight_n> &dist, vector<vertex_n> &previous )
{
  int sizeOf = edgeList.size();
  dist.resize(sizeOf, max_weight);
  dist[beginning] = 0;
  previous.resize(sizeOf, -1);
  set<pair<weight_n, vertex_n>> vQueue;
  vQueue.insert(make_pair(dist[beginning], beginning));
  while (!vQueue.empty())
  {
    weight_n distEdge = vQueue.begin()->first;
    vertex_n nextNode = vQueue.begin()->second;
    vQueue.erase(vQueue.begin());

    vector<node> &nEdge = edgeList[nextNode];
    for(int i = 0; i<nEdge.size(); i++)
    {
      vertex_n tempNode = nEdge[i].target;
      weight_n weight = nEdge[i].weight;
      weight_n distance_across = distEdge + weight;
      if (distance_across < dist[tempNode]) {
        vQueue.erase(make_pair(dist[tempNode], tempNode));
 
        dist[tempNode] = distance_across;
        previous[tempNode] = nextNode;
        vQueue.insert(make_pair(dist[tempNode], tempNode));
 
      }
    }
  }

}

void bidirectional (vector<vector<node>> edgeList, int beginning, int end)
{
  int sizeOf = edgeList.size();
  bool inMiddle = false;
  set<pair<weight_n, vertex_n>> vQueueF;
  
  set<pair<weight_n, vertex_n>> vQueueB;

  vector<weight_n> distF;
  distF.resize(sizeOf, max_weight);
  distF[beginning] = 0;
  vector<bool> visitedF(sizeOf, false);

  vector<vertex_n> previousF;
  previousF.resize(sizeOf, -1);

  vector<weight_n> distB;
  distB.resize(sizeOf, max_weight);
  distB[end] = 0;
  vector<bool> visitedB(sizeOf, false);

  vector<vertex_n> previousB;
  previousB.resize(sizeOf, -1);

  vQueueF.insert(make_pair(distF[beginning], beginning));
  vQueueB.insert(make_pair(distB[end], end));
  vertex_n nextNodeF, nextNodeB;
  weight_n distEdgeF, distEdgeB;

  for(int i = 0; i < sizeOf; ++i)
  {
    do
    {
    distEdgeF = vQueueF.begin()->first;
    nextNodeF = vQueueF.begin()->second;
    vQueueF.erase(vQueueF.begin());
    }while(visitedF[nextNodeF] == true);

    visitedF[nextNodeF] = true;

    vector<node> &nEdge = edgeList[nextNodeF];
    for(int i = 0; i<nEdge.size(); i++)
    {
      vertex_n tempNode = nEdge[i].target;
      weight_n weight = nEdge[i].weight;
      weight_n distance_across = distEdgeF + weight;
      if (distance_across < distF[tempNode]) {
        vQueueF.erase(make_pair(distF[tempNode], tempNode));
 
        distF[tempNode] = distance_across;
        previousF[tempNode] = nextNodeF;
        vQueueF.insert(make_pair(distF[tempNode], tempNode));
 
      }
    }


    do
    {
    distEdgeB = vQueueB.begin()->first;
    nextNodeB = vQueueB.begin()->second;
    vQueueB.erase(vQueueB.begin());
    }while(visitedB[nextNodeB] == true);

    visitedB[nextNodeB] = true;

    vector<node> &nEdgeB = edgeList[nextNodeB];
    for(int i = 0; i<nEdgeB.size(); i++)
    {
      vertex_n tempNode = nEdgeB[i].target;
      weight_n weight = nEdgeB[i].weight;
      weight_n distance_across = distEdgeB + weight;
      if (distance_across < distB[tempNode]) {
        vQueueB.erase(make_pair(distB[tempNode], tempNode));
 
        distB[tempNode] = distance_across;
        previousB[tempNode] = nextNodeB;
        vQueueB.insert(make_pair(distB[tempNode], tempNode));
 
      }
    }

    for(int j = 0; j != sizeOf; ++j)
    {
      if(visitedF[j] && visitedB[j])
      {
        inMiddle = true;
      }
    }

    if(inMiddle) break;
  }

  int min = numeric_limits<int>::max();
  for(int i = 0; i < sizeOf; ++i)
  {
    if(visitedF[i] == true)
    {
      if(distF[i] + distB[i] < min)
      {
      min = distF[i] + distB[i]; 
      }
    }
  }
  
  //cout << "the min: " << min << endl;


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

list<vertex_n> DijkstraGetShortestPathTo(
    vertex_n vertex, const std::vector<vertex_n> &previous)
{
    std::list<vertex_n> path;
    for ( ; vertex != -1; vertex = previous[vertex])
        path.push_front(vertex);
    return path;
}

int main()
{
  //set the random base on time
  srand(time(0)); 
  cout << "Test simple graph generation" << endl;

  clock_t t;
  float dijkstraTime = 0;
  float bidirectionalTime = 0;
  for(int i = 0; i < 100; i++)
  {
    int startNode = (1.0*rand()/RAND_MAX)*1000;
    int endNode = (1.0*rand()/RAND_MAX)*1000;
    graph test1(1000, 0.1);
    vector<weight_n> min_distance;
    vector<vertex_n> previous;
    t = clock();
    dijkstra(startNode, test1.edgeList, min_distance, previous);
    t = clock() - t;
    dijkstraTime += t/10000;
    t = clock();
    bidirectional (test1.edgeList, startNode, endNode);
    t = clock() - t;
    bidirectionalTime += t/10000;
  }
   cout << "dijkstra time: " << dijkstraTime << endl;
   cout << "bidirectionalTime: " << bidirectionalTime << endl;
   return 0;
}


