#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <utility>
#include <vector>
#include <map>
#include<bits/stdc++.h> 
  
// Creating shortcut for an integer pair 
typedef  std::pair<long long, long long> iPair; 
  
// Structure to represent a graph 
struct Graph 
{ 
    long long V, E; 
    std::vector< std::pair<long long, iPair> > edges; 
  
    // Constructor 
    Graph(long long V, long long E) 
    { 
        this->V = V; 
        this->E = E; 
    } 
  
    // Utility function to add an edge 
    void addEdge(long long u, long long v, long long w) 
    { 
        edges.push_back({w, {u, v}}); 
    } 
  
    // Function to find MST using Kruskal's 
    // MST algorithm 
    void kruskalMST(struct MST &mst); 
}; 
  
struct MST  //struct for MST
{
    long long V,E;
    std::vector< iPair > *adjacents;    //adjacensy list
    long long *visited;
    std::map< long long,long long > freqs;  //map for the tuples

    MST(long long V, long long E)
    {
        this->V = V+1;
        this->E = E;
        adjacents = new std::vector< iPair > [this->V]; //dynamic memory allocation
        visited = new long long [this->V];
        for(long long i=0; i<this->V; i++)  
        {
            visited[i] = 0;
        }
    }
    ~MST()
    {
        delete [] adjacents;
        delete [] visited;
    }
    void addEdge(long long u, long long v, long long w) 
    { 
        adjacents[u].push_back({v, w}); 
        adjacents[v].push_back({u, w}); 
    }

    void DFS();
    long long DFSutil(long long u, long long cnt);
    void print_cost(long long &E);
};
// To represent Disjoint Sets 
struct DisjointSets 
{ 
    long long *parent, *rnk; 
    long long n; 
  
    // Constructor. 
    DisjointSets(long long n) 
    { 
        // Allocate memory 
        this->n = n; 
        parent = new long long[n+1]; 
        rnk = new long long[n+1]; 
  
        // Initially, all vertices are in 
        // different sets and have rank 0. 
        for (long long i = 0; i <= n; i++) 
        { 
            rnk[i] = 0; 
  
            //every element is parent of itself 
            parent[i] = i; 
        } 
    } 
  
    // Find the parent of a node 'u' 
    // Path Compression 
    long long find(long long u) 
    { 
        /* Make the parent of the nodes in the path 
           from u--> parent[u] point to parent[u] */
        if (u != parent[u]) 
            parent[u] = find(parent[u]); 
        return parent[u]; 
    } 
  
    // Union by rank 
    void Union(long long x, long long y) 
    { 
        x = find(x), y = find(y); 
  
        /* Make tree with smaller height 
           a subtree of the other tree  */
        if (rnk[x] > rnk[y]) 
            parent[y] = x; 
        else // If rnk[x] <= rnk[y] 
            parent[x] = y; 
  
        if (rnk[x] == rnk[y]) 
            rnk[y]++; 
    } 
}; 
  
 /* Functions returns weight of the MST*/ 
  
void Graph::kruskalMST(struct MST &mst) 
{ 
  
    // Sort edges in increasing order on basis of cost 
    sort(edges.begin(), edges.end()); 
  
    // Create disjoint sets 
    DisjointSets ds(V); 
  
    // Iterate through all sorted edges 
    std::vector< std::pair<long long, iPair> >::iterator it; 
    for (it=edges.begin(); it!=edges.end(); it++)
    { 
        long long u = it->second.first; 
        long long v = it->second.second; 
        long long w = it->first;
  
        long long set_u = ds.find(u); 
        long long set_v = ds.find(v); 
  
        // Check if the selected edge is creating 
        // a cycle or not (Cycle is created if u 
        // and v belong to same set) 

        if (set_u != set_v) 
        { 
            // Current edge will be in the MST 
            // so print it 
            mst.addEdge(u, v, w);
            // Union two sets 
            ds.Union(set_u, set_v); 
        } 
    } 
  
} 

long long MST::DFSutil(long long u, long long cnt)
{
    visited[u] = 1;
    
    long long childs = 1;
    long long gchilds = 0;
    std::vector< iPair >::iterator it;
    for(it=adjacents[u].begin(); it!=adjacents[u].end(); it++)
    {
        if (visited[it->first] == 0){
            gchilds = DFSutil(it->first,cnt+1);
            freqs[it->second] = gchilds*(V-gchilds-1);  //calculation of freq
            childs += gchilds;

        }
    }
    return childs;
}  

void MST::DFS()
{
    for(long long i=1; i<V; i++)
    {
        if(visited[i] == 0)
            DFSutil(i,1);
    }
}

void MST::print_cost(long long &E)
{
    long long i = 0;
    unsigned long long k = 0, j = E;
    while(k < freqs.size())
    {
        if(k > j && freqs[k] == 0)  //at least M bits
        {
            break;
        }
        auto search = freqs.find(k+1);
        if(search == freqs.end())
           freqs[k+1] = 0;
        freqs[k+1] += freqs[k]/2;
        freqs[k] = freqs[k] & 1;
        k++;
    }
    
    i = freqs.size()-1;
    while(i >= 0 && freqs[i] == 0)
        i--;

    while(i >= 0)
    {
        printf("%lld", freqs[i]);
        i--;
    }
    printf("\n");
}
// Driver program to test above functions 
int main() 
{ 
    std::ios_base::sync_with_stdio (false);
    /* Let us create above shown weighted 
       and unidrected graph */
    long long V, E, u, v, w; 

    std::cin >> V >> E;
    Graph g(V, E); 
    //Construct MST
    MST mst(V, V-1);
    
    //  making above shown graph 
    for(long long i = 0; i<E; i++){
        
        std::cin >> u >> v >> w;
        g.addEdge(u, v, w); 
    }
  
    g.kruskalMST(mst); //find MST
    
    //Call DFS
    mst.DFS();
    mst.print_cost(E);  //print the cost

    return 0; 
} 