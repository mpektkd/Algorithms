#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <utility>
#include <algorithm>

typedef std::pair<long long int, long long int> car;        //we define a nwe type

struct myclass{
    bool operator()(car i, car j){return (i.second < j.second);}    //we define the structs will be used in sort
} compare_object;

struct Myclass{
    bool operator()(long long int  i, long long int  j){return (i < j);}
} compar_object;


long long find_max_c(long long* stations, long long int &size, long long int &Cs){  
    
    long long int  res = 0;
    long long int  temp = 0;
    long long int  prev = 0;
    long long int  i;
    
    for(i = 0; i < size+1; ++i){            //we calcuate the consumption for each distance from the previous station to the next and find the max
        temp = (stations[i] - prev) * Cs;
        if (temp > res) res = temp;
        prev = stations[i];
    }
    return res;
}

long long find_lower(car* candidates, long long int M, long long int &N){       //we take the middle element and we compare if its capacity can is greater than the max consumption

    long long int  l = 0;                                                       //we discard the half elements each time --> logn
    long long int  r = N - 1;
    long long int  m = 0;
    long long int lower_bound = -1;

    while(l <= r){
        m = l + (r - l)/2;
        if (candidates[m].second >= M){

            lower_bound = m;
            r = m - 1;
        }
        else{
            l = m + 1;
        }
    }
    return lower_bound;                                                                             //we find that index of the array(sorted by capacities), where its car is the first with capacity greater than the max
}                                                                                                   //Then and the rightest elements can arrive the Selection city

long long find_res(car* candidates, long long int &lower, long long int &N){                        //find the cheapest
    
    long long int  res = candidates[lower].first;
    long long int  i;

    for(i = lower; i < N; ++i){
        if(candidates[i].first < res) res = candidates[i].first;
    }

    return res;
}

int main () {

    std::ios_base::sync_with_stdio (false);

    long long int  N, K, D, T;

    std::cin >> N >> K >> D >> T;  //we read from stdin the input data
    
    car candidates[N];
    long long int  stations[K+1];

    long long int  i,Cs,Ts,Cf,Tf;

    for(i=0; i<N; ++i) {  
        std::cin >> candidates[i].first >> candidates[i].second ;  
    }
        
    for(i=0; i<K; ++i) {
        std::cin >> stations[i]; 
    }  
    stations[K] = D; //add the final city
    
    std::cin >> Ts >> Cs >> Tf >> Cf;  
    

    long long int  Tmin;
    Tmin = D*Tf;
    
    if(T < Tmin){                   //we suppose that the cars execute motion with Vmin = stable and we suppose that the coefficient of capacity is stable
                                    //we check if there is a solution by comparing the two times
        printf("%d\n", -1);
        return 0;
    }                               //the futrher down analysis checks if there is at least one car that can arrive at each station
    
    std::sort(candidates, candidates+N, compare_object);
    
    std::sort(stations, stations + (K+1), compar_object);

    long long int lower = find_lower(candidates, find_max_c(stations, K, Cs), N);

    if(lower < 0){
        printf("%d\n", -1);
        return 0;
    }
    printf("%lld\n", find_res(candidates, lower, N));
                                                                            //the analysis i have done, seperate the problem to two problems. It check each parameter supposing that the other doesn't affecte the problem
    return 0;                                                               //if the two analysis give positive result we have the min price 
}