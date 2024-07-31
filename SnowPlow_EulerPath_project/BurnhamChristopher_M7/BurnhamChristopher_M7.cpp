// BurnhamChristopher_M7.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include<iostream>
#include <list>
#include <fstream>
#include <sstream>
#include <tuple>
#include <vector>
#include <string>

using namespace std;

/*I'm leaving in some code just so you can see my thought processes at times, or things I tried that didnt work as well as I had hoped. Used a few different places to help get the code up and running:
https://www.geeksforgeeks.org/vector-erase-and-clear-in-cpp/
https://www.geeksforgeeks.org/eulerian-path-and-circuit/
https://www.geeksforgeeks.org/connectivity-in-a-directed-graph/
https://www.geeksforgeeks.org/euler-circuit-directed-graph/?ref=lbp
https://stackoverflow.com/questions/66552813/how-to-read-file-into-vector-of-tuple
https://linuxhint.com/array-pairs-cpp/
https://stackoverflow.com/questions/26979236/reading-integers-from-file-and-store-them-in-array-c
https://stackoverflow.com/questions/10750057/how-do-i-print-out-the-contents-of-a-vector
https://www.geeksforgeeks.org/2d-vector-of-pairs-in-c-with-examples/
All above have in some way shape or form helped build the code, with the eulerian cycle/circuit/path code coming from geeks for geeks.  Reading in file help from stackoverflow and text books
*/




class Graph
{
    int V;    // No. of vertices
    list<int>* adj;    // A dynamic array of adjacency lists
public:
    // Constructor and destructor
    Graph(int V) { this->V = V; adj = new list<int>[V]; }
    ~Graph() { delete[] adj; } // To avoid memory leak

     // function to add an edge to graph
    void addEdge(int v, int w);

    // Method to check if this graph is Eulerian or not
    int isEulerian();

    // Method to check if all non-zero degree vertices are connected
    bool isConnected();

    // Function to do DFS starting from v. Used in isConnected();
    void DFSUtil(int v, bool visited[]);
};
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);  // Note: the graph is undirected
}

void Graph::DFSUtil(int v, bool visited[])
{
    // Mark the current node as visited and print it
    visited[v] = true;

    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for (i = adj[v].begin(); i != adj[v].end(); ++i)
        if (!visited[*i])
            DFSUtil(*i, visited);
}

// Method to check if all non-zero degree vertices are connected.
// It mainly does DFS traversal starting from
bool Graph::isConnected()
{
    // Mark all the vertices as not visited
     
    bool visited[10];
    int i;
    for (i = 0; i < V; i++)
        visited[i] = false;

    // Find a vertex with non-zero degree
    for (i = 0; i < V; i++)
        if (adj[i].size() != 0)
            break;

    // If there are no edges in the graph, return true
    if (i == V)
        return true;

    // Start DFS traversal from a vertex with non-zero degree
    DFSUtil(i, visited);

    // Check if all non-zero degree vertices are visited
    for (i = 0; i < V; i++)
        if (visited[i] == false && adj[i].size() > 0)
            return false;

    return true;
}

/* The function returns one of the following values
   0 --> If graph is not Eulerian
   1 --> If graph has an Euler path (Semi-Eulerian)
   2 --> If graph has an Euler Circuit (Eulerian)  */
int Graph::isEulerian()
{
    // Check if all non-zero degree vertices are connected
    if (isConnected() == false)
        return 0;

    // Count vertices with odd degree
    int odd = 0;
    for (int i = 0; i < V; i++)
        if (adj[i].size() & 1)
            odd++;

    // If count is more than 2, then graph is not Eulerian
    if (odd > 2)
        return 0;

    // If odd count is 2, then semi-eulerian.
    // If odd count is 0, then eulerian
    // Note that odd count can never be 1 for undirected graph
    return (odd) ? 1 : 2;
}

// Function to run test cases
void test(Graph& g)
{
    int res = g.isEulerian();
    if (res == 0)
        cout << "\nGraph is not Eulerian. The route is impossible. The snowplow can get from start to finish but will end up plowing multiple streets twice.\n";
    else if (res == 1)
        cout << "\nGraph has a Euler path. The route is impossible. The snowplow can get from start to finish, but will end up plowing at least a street twice.\n";
    else
        cout << "\nGraph has a Euler cycle. The snowplow can get from start to finish without plowing the same street twice.\n";
}

vector<tuple<int, int>> Readfile() 
{
    /*creating filename relative path to access Cities.txt file for runtime*/
    ifstream stream("../Cities.txt");
    vector<tuple<int, int>> data; /*original vector concept for solving problem after restarting*/
    /*vector<tuple<int, int>> data2;*/
    int a;
    int b;
    vector<int> number1;
    vector<int> number2;
    pair<int, int> MyPair;

    while (stream >> a >> b)
    {
        while (!stream.eof())
        {
            stream >> a >> b;
            if (a == -1 && b == -1) /*utilizing -1 -1 as the break in the file*/
            {
                Graph g1(10); /*create graph variable*/
                for (int y = 0; y < number1.size(); y++) /*run loop through as both number1 and number2 are same size*/
                {
                        /*setting pairs*/
                        MyPair.first = number1[y];
                        MyPair.second = number2[y];
                    
                    cout << "\n " << MyPair.first << ", " << MyPair.second << "\n"; /*debug line to make sure they are being assigned correctly*/
                    g1.addEdge(MyPair.first, MyPair.second); /*inputting paired tuples back into graphing function*/
                    
                }
                test(g1); /*testing graph to see if it is Euler*/
                /*clear functions of vectors*/
                number1.clear();
                number2.clear();
                continue;/*continue through the file*/
            }
            else
            {
                /*data.push_back(tuple<int, int>(a, b));*/ /*original concept of feeding into a tuple vector, additional code was deleted this was left over*/
                number1.push_back(a);
                cout << "\nFirst array: ";
                for (int i : number1)
                    cout <<  i << ' ';
                number2.push_back(b);
                cout << "\nSecond Array: ";
                for (int i : number2)
                    cout << i << ' ';
                 
            }
        }
    }
    return data;
    /*this is actually basically worthless and not needed now and can be deleted*/
}

int main()
{
    /*example working not fed from file to show working examples*/
    Graph g2(5);
    g2.addEdge(1, 0);
    g2.addEdge(0, 2);
    g2.addEdge(2, 1);
    g2.addEdge(0, 3);
    g2.addEdge(3, 4);
    g2.addEdge(4, 0);
    test(g2);
    
    /*creating filename relative path to access Cities.txt file for runtime*/
    ifstream stream("../Cities.txt");
    if (stream.fail()) {
        cout << "file doesnt exist. \n";
    }
    else {
        cout << "file exists. \n";
    }
    int x;
    int y;
    int z = 1;
    auto vec = Readfile();

    /*for (const auto& i : vec)
    {
        cout << get<0>(i) << ", " 
             << get<1>(i) << endl;
    }*/
    
    
    /*
        Graph g1(5);
        pair<int, int> PAIR1;
        for (const auto& i : vec)
        {
            
                PAIR1.first = get<0>(i);
                PAIR1.second = get<1>(i);
                g1.addEdge(get<0>(i), get<1>(i));


        }
        test(g1);
    */    
    stream.close();    
    return 0;
}
