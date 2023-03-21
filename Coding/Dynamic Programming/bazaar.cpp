#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <utility>
#include <vector>

typedef std::pair<int,int> offer;
typedef std::vector<offer> offers;
offers  A1, B1, C1, A2, B2, C2, A3, B3, C3;


void allocate(char &x, char &y, int &q, int &p){ //allocate the input

    std::pair<int, int> off;
    off.first = q;      //make offer
    off.second = p;
    
    switch(x){
        case '1': 
            switch(y){
                case 'A':
                    A1.push_back(off);      //choose among the possible traders
                    break;
                case 'B':
                    B1.push_back(off);
                    break;
                case 'C':
                    C1.push_back(off);
                    break;
            }
            break;

        case '2': 
            switch(y){
                case 'A':
                    A2.push_back(off);
                    break;
                case 'B':
                    B2.push_back(off);
                    break;
                case 'C':
                    C2.push_back(off);
                    break;
            }
            break;
            
        case '3': 
            switch(y){
                case 'A':
                    A3.push_back(off);
                    break;
                case 'B':
                    B3.push_back(off);
                    break;
                case 'C':
                    C3.push_back(off);
                    break;
            }
            break;
    }
}


void print_a(int *arr, int &N){
    printf("[");
    for(int j = 0; j < N+1; j++){
        printf("%d ", arr[j]);
    }
    printf("]");
    printf("\n");
}
void knapsack(int &N, offers &offs, int &inf, int *total){      //DP for find the minimum cost by each trader

    int size = offs.size();
    int P[size+1][N+1];
    int p, diff;

    for(int b = 1; b < (N+1); b++)  //initialize
        P[0][b] = inf;
    
    for(int i = 0; i < (size+1); i++)
        P[i][0] = 0;

    for(int i = 1; i < (size+1); i++){
        for(int b = 1; b < (N+1); b++){
            p = 0;
            P[i][b] = P[i-1][b];
            diff = b-offs[i-1].first;   
            
            if(diff < 0){                //check if bi is negative
                p = offs[i-1].second;
                if(P[i][b] > p || P[i][b] == inf)
                    P[i][b] = p;
            }
            else{
                if(P[i-1][b-offs[i-1].first] == inf)
                    ;
                else{
                    p = P[i-1][b-offs[i-1].first] + offs[i-1].second;
                    if(P[i][b] > p || P[i][b] == inf)
                        P[i][b] = p;
                }
            }
        }
    }
    print_a(P[size], N);
    for(int i = 0; i < N+1; i++){        //return the last row of the matrix
        if(P[size][i] != inf && total[i] != inf)
            total[i] += P[size][i];
        else 
            total[i] = inf;
    }
}

int main(){
    
    std::ios_base::sync_with_stdio (false);

    int N, M, q;
    int p;
    int inf;
    char x, y;
    inf = -1; 
    std::cin >> N >> M;

    for (int i = 0; i < M; i++){
        
        std::cin >> x >> y >> q >> p;
        allocate(x, y, q, p);
    }
    
    int total1[N+1], total2[N+1], total3[N+1];
    
    if(A1.size()*B1.size()*C1.size() != 0){ 
        for(int i = 0; i < N+1; i++)        //initialize the total cost for 1st trader
            total1[i] = 0;                               //if the trader doesn't present offers for all parts, continue
        
        knapsack(N, A1, inf, total1); knapsack(N, B1, inf, total1); knapsack(N, C1, inf, total1);
    }
    else{
        total1[0] = 0;
        for(int i = 1; i < N+1; i++)       //initialize the total cost for 1st trader
            total1[i] = inf;
    }
    if(A2.size()*B2.size()*C2.size() != 0){
        for(int i = 0; i < N+1; i++)        //initialize the total cost for 2nd trader
            total2[i] = 0;

        knapsack(N, A2, inf, total2); knapsack(N, B2, inf, total2); knapsack(N, C2, inf, total2);
    }
    else{    
        total2[0] = 0;
        for(int i = 1; i < N+1; i++)        //initialize the total cost for 2nd trader
            total2[i] = inf;
    }
    if(A3.size()*B3.size()*C3.size() != 0){
        for(int i = 0; i < N+1; i++)        //initialize the total cost for 3rd trader
            total3[i] = 0;

        knapsack(N, A3, inf, total3); knapsack(N, B3, inf, total3); knapsack(N, C3, inf, total3);
        
    }
    else{    
        total3[0] = 0;
        for(int i = 1; i < N+1; i++)        //initialize the total cost for 3rd trader 
            total3[i] = inf;
    }
    int k = 0;
    int cost = inf;

    for (int i = 0; i < N+1; i++){
        if (total1[i] == inf)
            continue;
        for (int j = 0; j < N+1; j++){
            if (total2[j] == inf)
                continue;
            if (i+j <= N ){
                if(total3[N - i - j] == inf)
                    continue;
                k = total1[i] + total2[j] + total3[N - i - j];
            }
            else
                k = total1[i] + total2[j];

            if (k < cost || cost == inf)
                cost = k;
        }
    }
        printf("%d\n", cost);

    return 0;
}
