//assignment 3
//compare the differents between normal dijkstra and bidirectional dijkstra
//editing the graph from asg2 and making it in a edge list to make it easier.

#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <limits> // for numeric_limits
#include <set>
#include <utility> // for pair
#include <algorithm>

//to make the print easier
using namespace std;

typedef int vertex_n;
typedef double weight_n;


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
  const weight_n max_weight = numeric_limits<double>::infinity();
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
          //if the node already has a number don't create node
          auto pred = [j](const node & item) {
            return item.target == j;
          };
          if(find_if(begin(edgeList[i]), end(edgeList[i]), pred) != end(edgeList[i]) )
          {
            continue;
          }
          int randomNum = ((1.0*rand()/RAND_MAX)*200)+1;
          //create the edge list.
          edgeList[i].push_back(node(j,randomNum));
          edgeList[j].push_back(node(i,randomNum));
        } 
      }
    }
	}
  //use to get size
  int getSize()
  {
    return size;
  }

  //dijkstra algorithm (not the bidirectional one) 
  void dijkstra(vertex_n beginning, vertex_n end)
  {
    //store the min distance/weight
    vector<weight_n> dist;
    dist.resize(size, max_weight);
    dist[beginning] = 0;
    //store the edge of min
    vector<vertex_n> previous;
    previous.resize(size, -1);
    //vector to see is node is traveled
    vector<bool> visited(size, false);
    //the queue
    set<pair<weight_n, vertex_n>> vQueue;
    vQueue.insert(make_pair(dist[beginning], beginning));

    weight_n distEdge;
    vertex_n nextNode;
    //to store the current shortest path.
    double shortestPath = max_weight;
    //for loop that starts the search
    for(int i = 0; i < size; ++i)
    {
      do
      {
        //went though all of the queue.
        if(vQueue.empty())
        {
          shortestPath = dist[end];
          return;
        }
        distEdge = vQueue.begin()->first;
        nextNode = vQueue.begin()->second;
        vQueue.erase(vQueue.begin());
      }while(visited[nextNode] == true);

      visited[nextNode] = true;
      //when the start reached the end
      if(nextNode == end)
      {
        shortestPath = dist[end];
        return;
      }

      //travel through all edges of a node
      vector<node> &nEdge = edgeList[nextNode];
      for(int i = 0; i<nEdge.size(); i++)
      {
        vertex_n tempNode = nEdge[i].target;
        weight_n weight = nEdge[i].weight;
        weight_n distance_across = distEdge + weight;
        //can the distance if it is shorter than the current one.
        if (distance_across < dist[tempNode]) {
          vQueue.erase(make_pair(dist[tempNode], tempNode));
   
          dist[tempNode] = distance_across;
          previous[tempNode] = nextNode;
          vQueue.insert(make_pair(dist[tempNode], tempNode));
   
        }
      }
    }
  }

  //dijkstra with bidirectional 
  void bidirectional (int beginning, int end)
  {
    //bool to the check if the middle has been reach
    bool inMiddle = false;
    
    //the queue for the front and back (F=front, B=back)
    set<pair<weight_n, vertex_n>> vQueueF;
    set<pair<weight_n, vertex_n>> vQueueB;

    //making a vector of weight and make all of them inf but the start node
    vector<weight_n> distF;
    distF.resize(size, max_weight);
    distF[beginning] = 0;
    vector<bool> visitedF(size, false);

    //making a vector of edge
    vector<vertex_n> previousF;
    previousF.resize(size, -1);

    //making a vector of weight and make all of them inf but the start node
    vector<weight_n> distB;
    distB.resize(size, max_weight);
    distB[end] = 0;
    vector<bool> visitedB(size, false);

    //making a vector of edge
    vector<vertex_n> previousB;
    previousB.resize(size, -1);

    vQueueF.insert(make_pair(distF[beginning], beginning));
    vQueueB.insert(make_pair(distB[end], end));
    vertex_n nextNodeF, nextNodeB;
    weight_n distEdgeF, distEdgeB;

    //start of the search
    for(int i = 0; i < size; ++i)
    {
      //front part
      //get a unvisited node
      do
      {
      distEdgeF = vQueueF.begin()->first;
      nextNodeF = vQueueF.begin()->second;
      vQueueF.erase(vQueueF.begin());
      }while(visitedF[nextNodeF] == true);
      //set visit to true
      visitedF[nextNodeF] = true;
      //go though all paths of the node 
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

      //back part 
      //get a unvisited node
      do
      {
      distEdgeB = vQueueB.begin()->first;
      nextNodeB = vQueueB.begin()->second;
      vQueueB.erase(vQueueB.begin());
      }while(visitedB[nextNodeB] == true);

      //set visit to true
      visitedB[nextNodeB] = true;
      //go though all paths of the node 
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
      //check for when the front and the back meet in the middle
      for(int j = 0; j != size; ++j)
      {
        if(visitedF[j] && visitedB[j])
        {
          inMiddle = true;
        }
      }
      if(inMiddle) break;
    }
    //find the shortest path 
    int min = numeric_limits<int>::max();
    for(int i = 0; i < size; ++i)
    {
      if(visitedF[i] == true)
      {
        if(distF[i] + distB[i] < min)
        {
        min = distF[i] + distB[i]; 
        }
      }
    }
  }


private:
  //size of the graph
  int size;
  vector<vector<node>> edgeList;

};

int main()
{
  //set the random base on time
  srand(time(0)); 
  cout << "This will take awhile creating a lot of graphs... (>'.')>#<(0.0<)" << endl;
  //the clock
  clock_t t;
  //the mean time of the graph
  float dijkstraTime = 0;
  float bidirectionalTime = 0;
  //creating 100 graphs
  for(int i = 0; i < 100; i++)
  {
    //getting a random start and end node
    int startNode = (1.0*rand()/RAND_MAX)*1000;
    int endNode = (1.0*rand()/RAND_MAX)*1000;
    graph test1(1000, 0.1);
    t = clock();
    test1.dijkstra(startNode, endNode);
    t = clock() - t;
    dijkstraTime += t/10000;
    t = clock();
    test1.bidirectional(startNode, endNode);
    t = clock() - t;
    bidirectionalTime += t/10000;
  }
  //print
  cout << "The average time of 100 graph with a density of 0.1" << endl;
  cout << "dijkstra time: " << dijkstraTime/100 << endl;
  cout << "bidirectionalTime: " << bidirectionalTime/100 << endl;
  //reseting the mean time
  dijkstraTime = 0;
  bidirectionalTime = 0;
  //100 graph this time with density 0.01
  for(int i = 0; i < 100; i++)
  {
    //random start and end node
    int startNode = (1.0*rand()/RAND_MAX)*1000;
    int endNode = (1.0*rand()/RAND_MAX)*1000;
    graph test1(1000, 0.01);
    t = clock();
    test1.dijkstra(startNode, endNode);
    t = clock() - t;
    dijkstraTime += t/10000;
    t = clock();
    test1.bidirectional(startNode, endNode);
    t = clock() - t;
    bidirectionalTime += t/10000;
  }
  //print
  cout << "The average time of 100 graph with a density of 0.01" << endl;
  cout << "dijkstra time: " << dijkstraTime/100 << endl;
  cout << "bidirectionalTime: " << bidirectionalTime/100 << endl;
  return 0;
}


