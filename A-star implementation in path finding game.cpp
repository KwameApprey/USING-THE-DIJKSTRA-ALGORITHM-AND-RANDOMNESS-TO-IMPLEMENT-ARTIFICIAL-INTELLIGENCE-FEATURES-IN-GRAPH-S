/*CSCI 5837: Artificial Intelligence Methods in Game Design

Spring Semester 2019
End of semester Project

Author:
1. Apprey-Hermann Joseph Kwame

*/

#include<iostream>
#include<string>
#include<stdlib.h>
#include<time.h>
#include<vector>
#include<map>
#include<utility>
#include<limits.h>
using namespace std;

void showgraph( int, int*); // function to show graph
pair<string, int> dijkstra(int graph[8][8], int startNode); //AI based on dijkstra's algorithm
void newNewNext(int edgeCosts[], int graph[8][8]); // Function for player to play the game


int main()
{
cout<<"..................................................................................."<<endl;
cout<<"**********************Welcome to play the path finding Game **********************"<<endl;
cout<<"                                                                         "<<endl;
//Base values for edgecosts
int edgeCosts[12]={1,2,3,4,18,6,7,20,8,4,9,2};

//Slightly randomize edgecosts
srand(time(0));
for(int i=0; i<12; i++)
    edgeCosts[i]+=((rand()%10)+1)*2;

//Creating graph for AI to traverse
int map[8][8] = {{0, edgeCosts[1], edgeCosts[0], edgeCosts[10], 0, 0, 0, 0},
                    {edgeCosts[1], 0, 0, 0, 0, 0, 0, edgeCosts[4]},
                    {edgeCosts[0], 0, 0, 0, edgeCosts[2], 0, 0, 0},
                    {edgeCosts[10], 0, 0, 0, edgeCosts[3], 0, edgeCosts[8], 0},
                    {0, 0, edgeCosts[2], edgeCosts[3], 0, edgeCosts[9], 0, 0},
                    {0, 0, 0, 0, edgeCosts[9], 0, edgeCosts[5], edgeCosts[7]},
                    {0, 0, 0, edgeCosts[8], 0, edgeCosts[5], 0, edgeCosts[6]},
                    {0, edgeCosts[4], 0, 0, 0, edgeCosts[7], edgeCosts[6], 0}};

newNewNext(edgeCosts, map);
}



void showgraph(int s, int *edgeCosts){
if( s == 1)
{

cout<<"                          (A)* * * * * * * * * * * * * *(C)             "<<endl;
cout<<"                         *   *                               *            "<<endl;
cout<<"                        *     *                               *            "<<endl;
cout<<"                       *       *                               *       "<<endl;
cout<<"                      *         *                               *           "<<endl;
cout<<"             End--->(B)          *                                *       "<<endl;
cout<<"                     *            (D) * * * * ** * * * ** * * * *(E)    "<<endl;
cout<<"                      *            *                               *    "<<endl;
cout<<"                       *           *                              *     "<<endl;
cout<<"                        *         *                               *       "<<endl;
cout<<"                         *      (G) * * * * * * * * * * *  * * *(F).<--Start    "<<endl;
cout<<"                          *      *                               *             "<<endl;
cout<<"                           *     *                             *       "<<endl;
cout<<"                            *   *                            *            "<<endl;
cout<<"                             *  *                          *             "<<endl;
cout<<"                              * *                        *                 "<<endl;
cout<<"                               *                   *                      "<<endl;
cout<<"                              (H)      *                       "<<endl;
}
else
{
cout<<"                          (A)* * * * * * * "<<edgeCosts[0]<<" * * * * * * *(C)             "<<endl;
cout<<"                         *   *                               *            "<<endl;
cout<<"                        *     *                               *            "<<endl;
cout<<"                     "<<edgeCosts[1]<<"       "<<edgeCosts[10]<<"*                            "<<edgeCosts[2]<<"       "<<endl;
cout<<"                      *         *                               *           "<<endl;
cout<<"             End--->(B)          *                                *       "<<endl;
cout<<"                     *            (D) )* * * * * * * "<<edgeCosts[3]<<"* * * * * *(E)    "<<endl;
cout<<"                      *            *                              *    "<<endl;
cout<<"                       *           "<<edgeCosts[8]<<"                             "<<edgeCosts[9]<<"     "<<endl;
cout<<"                        "<<edgeCosts[4]<<"         *                             *       "<<endl;
cout<<"                         *      (G))* * * * * * * "<<edgeCosts[5]<<" *  * * *(F).<--Start    "<<endl;
cout<<"                          *      *                             *             "<<endl;
cout<<"                           *     "<<edgeCosts[6]<<"                         "<<edgeCosts[7]<<"       "<<endl;
cout<<"                            *   *                            *            "<<endl;
cout<<"                             *  *                          *             "<<endl;
cout<<"                              * *                        *                 "<<endl;
cout<<"                               *                   *                      "<<endl;
cout<<"                              (H)      *                       "<<endl;
    }
}

int minDistance(int distanceToNode[], bool hasShortestPath[]){
   // Initialize min value
   int min = INT_MAX;
   int min_index;

   for (int v = 0; v < 8; v++)
     if (hasShortestPath[v] == false && distanceToNode[v] <= min)
         min = distanceToNode[v], min_index = v;

   return min_index;
}

pair<string, int> dijkstra(int graph[8][8], int startNode){
    int distanceToNode[8];
    //This describes whether the node at index i has a shortest path.
    bool hasShortestPath[8];
    int parent[8];
    string shortestPath = "";
    map<int, string> intToNode;
    intToNode[0] = "A";
    intToNode[1] = "B";
    intToNode[2] = "C";
    intToNode[3] = "D";
    intToNode[4] = "E";
    intToNode[5] = "F";
    intToNode[6] = "G";
    intToNode[7] = "H";


    parent[startNode] = -1;

    for (int i = 0; i < 8; i++)
        distanceToNode[i] = INT_MAX, hasShortestPath[i] = false;

    distanceToNode[startNode] = 0;

     // Find shortest path for all vertices
    for (int count = 0; count < 8-1; count++)
    {
       // Pick the minimum distance vertex from the set of vertices not
       // yet processed. u is always equal to startNode in the first iteration.
       int u = minDistance(distanceToNode, hasShortestPath);

       // Mark the picked vertex as processed
       hasShortestPath[u] = true;

       // Update distanceToNode value of the adjacent vertices of the picked vertex.
       for (int v = 0; v < 8; v++)

         // Update distanceToNode[v] only if is not in hasShortestPath, there is an edge from
         // u to v, and total weight of path from startNode to  v through u is
         // smaller than current value of distanceToNode[v]
         if (!hasShortestPath[v] && graph[u][v] && distanceToNode[u] != INT_MAX
                                       && distanceToNode[u]+graph[u][v] < distanceToNode[v]){
            distanceToNode[v] = distanceToNode[u] + graph[u][v];
            parent[v] = u;
            }
     }

    int childNodeIndex = 1;
    while(childNodeIndex > -1){
        shortestPath =  intToNode[childNodeIndex] + shortestPath;
        childNodeIndex = parent[childNodeIndex];
    }

    return make_pair(shortestPath, distanceToNode[1]);
}

void newNewNext(int edgeCosts[], int graph[8][8]){
    string currentNode = "F";
    string goalNode = "B";
    string playersPath = "F";
    int playersPathCost = 0;
    int status = 1;
    map<string, vector<pair<string, int>> > adjacentNodes;

    adjacentNodes["F"] = {make_pair("E", edgeCosts[9]), make_pair("H",edgeCosts[7]),make_pair("G", edgeCosts[5])};
    adjacentNodes["E"] = {make_pair("C", edgeCosts[2]), make_pair("D", edgeCosts[3])};
    adjacentNodes["G"] = {make_pair("D", edgeCosts[8]), make_pair("H", edgeCosts[6])};
    adjacentNodes["H"] = {make_pair("B", edgeCosts[4]),make_pair("G", edgeCosts[6])};
    adjacentNodes["C"] = {make_pair("E", edgeCosts[2]), make_pair("A", edgeCosts[0])};
    adjacentNodes["A"] = {make_pair("B", edgeCosts[1]), make_pair("C", edgeCosts[0] ), make_pair("D ", edgeCosts[10])};
    adjacentNodes["D"] = {make_pair("A", edgeCosts[10]) , make_pair("G", edgeCosts[8]), make_pair("E", edgeCosts[3])};



    while(currentNode != goalNode){
        string nextNode;
        showgraph(status, edgeCosts);
        cout << "You are currently at: " << currentNode << endl;
        cout << "Choose from the following: " << endl;

        for(int i = 0; i < adjacentNodes[currentNode].size(); i++)
            cout << adjacentNodes[currentNode][i].first << endl;

        cin>> nextNode;

        //Check if the player's node is valid
        bool isValidNode = false;
        int tempEdgeCost;
        for(int i = 0; i < adjacentNodes[currentNode].size(); i++)
            if(adjacentNodes[currentNode][i].first == nextNode){
                isValidNode = true;
                tempEdgeCost = adjacentNodes[currentNode][i].second;
                break;
            }

        //If it is valid, we are good to travel to it
        if(isValidNode == true){
            //The player has traveled to the next node.
            currentNode = nextNode;
            //Add the node to the players path
            playersPath = playersPath + currentNode;
            //Add the edgecost to the total cost of the path
            playersPathCost = playersPathCost + tempEdgeCost;
        }
        else{
            cout << "That is not a valid node! Please select again!";
        }
    }
    status = 2;
    showgraph(status, edgeCosts);
    string shortestPath = dijkstra(graph, 5).first;
    int shortestPathCost = dijkstra(graph, 5).second;
    if(playersPath == shortestPath){
        cout << "Congratulations, you found the shortest path!" << endl;
    }
    else{
        cout << "Sorry that wasn't the shortest path!" << endl;
    }

    cout << "Your path was: " << playersPath << " and it cost: " << playersPathCost << endl;
    cout << "The shortest path was: " << shortestPath << " and it cost: " << shortestPathCost;
}
