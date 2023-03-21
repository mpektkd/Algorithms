#include <iostream>
#include <cstdio>
#include <stdlib.h>

void find_the_cost(int **A, int **c, int &N){

    for (int i = 0; i < N; i++){
        for(int j = 0; j < N-i; j++){

            if(i == 0){
                c[j][j+i] = 0;
            }
            else if(i == 1){
                c[j][j+i] = A[j][j+i];
            }
            else{
                c[j][j+i] = c[j][j+i-1] + c[j+1][j+i] - c[j+1][j+i-1] + A[j][j+i];
            }
        }
    }
    
    
}

int find_j(int **c, int &N, int *now, int *past, int &i, int &lbarr, int rbarr){
    
    int minj = 0;
    int nrg = 0;
    int p = 0;
    
    for(int j = lbarr; j <= rbarr; j++){
        if(j+1 >= N)
            p = past[j];
        else    
            p = past[j] + c[j+1][i];
        
        if(j == lbarr){
            nrg = p;
            minj = j;
        }
        else if(p < nrg){
            nrg = p;
            minj = j;
        }
    }
    now[i] = nrg;
    return minj;
}

void merge(int **c, int &N, int *now, int *past, int l, int r, int lbarr, int rbarr){

    if(l <= r){
        int mid = l + (r - l)/2;

        int j = 0;
        j = find_j(c, N, now, past, mid, lbarr, std::min(rbarr, mid));                                
        merge(c, N, now, past, l, mid - 1, lbarr, j);           //take the left half of now array with l1, m1 and the left half of past array with l2, j 
        merge(c, N, now, past, mid + 1, r, j, rbarr);      //take the right half of now array with m1 + 1, r1 and the right half of past array with j, m2 
        }
}

int find_energy(int **c, int &N, int &K){
    int *now, *past, *middle;        //past == (l-1)th stack, now == lth stack 
    now = new int [N];
    past = new int [N];
    int l = 0;
    int r = N-1;

    for(int i = 0; i < N; i++){    //for the case K = 1
        past[i] = c[0][i];
        now[i] = 0;
    }

    for(int j = 1; j < K; j++){

        merge(c, N, now, past, l, r, l, r);
        middle = past;
        past = now;
        now = middle; 

    }
        
    return past[N-1];
}

int main(){

    std::ios_base::sync_with_stdio (false);

    int N, K;
    
    if(N <= K){
        printf("%d\n", 0);
        return 0;
    }
    std::cin >> N >> K;
    
    int **A;
    A = new int *[N];
    for(int i = 0; i < N; i++){
        A[i] = new int [N];
    }
    for (int i = 0; i< N; i++){
        for (int j = 0; j< N; j++){
            A[i][j] = 0;
        }
    }
   
    for(int i = 0; i < N; i++){
        for(int j = 1; j < N-i; j++){
            std::cin >> A[i][i+j];
        }
    }
    
    int **c;
    c = new int *[N];
    for(int i = 0; i < N; i++){
        c[i] = new int [N];
    }
    
    find_the_cost(A, c, N);

    if(K == 1){
        printf("%d\n", c[0][N-1]);
        return 0;
    }
    int nrg = 0;
    nrg = find_energy(c, N, K);
    printf("%d\n", nrg);

    return 0;
}
