#include <iostream>
#include "tsp.hpp"
#include "tsp.cpp"

int main(){
    std :: vector < std :: vector <double > > cost_matrix {
            { INF , 10 , 8 , 19 , 12} ,
            {10 , INF , 20 , 6, 3} ,
            {8 , 20 , INF , 4 , 2} ,
            {19 , 6 , 4 , INF , 7} ,
            {12 , 3 , 2 , 7 , INF }
    };

    std :: vector <int > best_path = tsp ( cost_matrix );
        for(int i =0 ; i < best_path.size()-1;i++){
            std:: cout << best_path[i] << ", ";
        }
        std::cout << best_path.back()<< std::endl;
    return 0;
}

