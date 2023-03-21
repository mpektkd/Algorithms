#include <iostream>
#include <utility>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>

typedef std::pair<std::pair<long long int, long long int> , long long int> portal;

// A union by rank and path compression based program 

struct subset {
    long long int parent;
    long long int rank;
};
 
// A utility function to find set of an element i
// (uses path compression technique)
long long find(struct subset subsets[], long long int i)
{
    // find root and make root as parent of i (path                                                     the implementation of union-find is inspired by geeksforgeeks site
    // compression)
    if (subsets[i].parent != i)
        subsets[i].parent
            = find(subsets, subsets[i].parent);
 
    return subsets[i].parent;
}
 
// A function that does union of two sets of x and y
// (uses union by rank)
void Union(struct subset subsets[], long long int xroot, long long int yroot)
{
 
    // Attach smaller rank tree under root of high rank tree
    // (Union by Rank)
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
 
    // If ranks are same, then make one as root and
    // increment its rank by one
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

bool satisfy(long long int* set, portal* portals, long long int &m, long long int &N, long long int &M){
    
    long long int i, x, y;
    struct subset* subsets = (struct subset*)malloc(N * sizeof(struct subset));
    
    for (i = 0; i < N; ++i){
        subsets[i].parent = i;                                                      //we start with N seperating worlds 
        subsets[i].rank = 0;
    }

    for(i = m; i < M; ++i){

        x = find(subsets, portals[i].first.first - 1 );                             //we are going to unify them only if they have different parents
        y = find(subsets, portals[i].first.second - 1 );

        if(x != y)
            Union(subsets, x, y);
    }

    for(i = 0; i < N; ++i){
        
        if(set[i] - 1 != i ){                                                       //the subsequent satifies if and only if for each Morty, 
            if(find(subsets, set[i] - 1 ) != find(subsets, i))                      //the previous and the recent world belongs to the same universe(connective set)
                return false;
        }
    }
    
    return true;

}
struct myclass{
    bool operator()(portal i, portal j){return (i.second < j.second);}
} compare_object;

int main() {
    std::ios_base::sync_with_stdio (false);

    long long int N, M; 

    std::cin >> N >> M;
    
    long long int set[N];
    portal portals[M];

    long long int i;

    for(i = 0; i < N; ++i){
        std::cin >> set[i];
    }
    

    for(i = 0; i < M; ++i){
        std::cin >> portals[i].first.first >> portals[i].first.second >> portals[i].second;
    }

    std::sort(portals, portals+M, compare_object);                      //we are sorting with respect to the wights

    long long int l, r, m, max;
    max = 0;
    l = 0;
    r = M-1;

    while (l <= r){                                                      //binary search
    
        m = l + (r-l)/2;

        if (satisfy(set, portals, m, N, M)) {                              //we check for each subsequent with start m and end M, and if "satisfy" we take m as max and we go right to find greater max
            max = portals[m].second;
            l = m + 1 ;
        }
        else{
            r = m - 1 ;
        }
    }

    printf("%lld\n", max);
    
    return 0;
}