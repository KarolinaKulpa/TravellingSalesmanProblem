#include "tsp.hpp"
#include <iostream>
#include <vector>
#include<string>
#include<limits>
#include <cmath>
#include<utility>


double get_forbidden_cost(){
    double my_inf = std::numeric_limits<double>::infinity();
    return my_inf;
}

TSP_cost_matrix::TSP_cost_matrix(matrix m){
        cost_matrix = m;
        low_bound = 0;
};


double TSP_cost_matrix:: find_min(int row){
    double min = 300000;
    for(size_t i = 0; i < cost_matrix.size(); i++){
        if (!std::isnan(cost_matrix[row][i])) {
            if (cost_matrix[row][i] != INF) {
                if (min > cost_matrix[row][i]) {
                    min = cost_matrix[row][i];
                }
            }
        }
    }
    return min;
}


void  TSP_cost_matrix:: reduce_all_rows() {
    double min;
    for (int row = 0; row < cost_matrix.size(); row++) {
        if(!isnan_row(row)) {
            min = find_min(row);
            low_bound += min;
            for (int col = 0; col < cost_matrix[row].size(); col++) {
                if (cost_matrix[row][col] != INF) {
                    cost_matrix[row][col] -= min;
                }
            }
        }
    }
}


void TSP_cost_matrix::  transform(){
    matrix pom;
    vector vpom;
    for (int col = 0; col < cost_matrix.size(); col++) {
        for(int row2= 0; row2 < cost_matrix.size();row2++) {
            vpom.push_back(cost_matrix[row2][col]);
        }
        pom.push_back(vpom);
        vpom.clear();
    }

    cost_matrix = pom;
    pom.clear();
    vpom.clear();
}


void  TSP_cost_matrix:: reduce_all_cols() {
    transform();
    int pom1 = 0;
    for (size_t col = 0; col < cost_matrix.size(); col++) {
        for (size_t row = 0; row < cost_matrix[col].size(); row++) {
            if (cost_matrix[col][row] == 0) {
                pom1 += 1;
            }
        }
    }
    if (cost_matrix.size() == pom1) {
        reduce_all_rows();
    }
    transform();
}


void  TSP_cost_matrix:: reduce_row(int row){
    for(int i =0; i < cost_matrix[row].size();i++){
        cost_matrix[row][i] = NAN;
    }
}


void TSP_cost_matrix::  reduce_col(int col){
    transform();
    for(int i =0; i < cost_matrix[col].size();i++){
        cost_matrix[col][i] = NAN;
    }
    transform();
}


void  TSP_cost_matrix:: findBestPath (){
    reduce_all_rows ();
    reduce_all_cols ();
    find_next_path ();
}


bool  TSP_cost_matrix:: summit_not_visited(int row, int col){
    return !std::isnan(cost_matrix[row][col]);
}

bool  TSP_cost_matrix:: isnan_row(int row){
    int pom = 0;
    for(int i = 0; i < cost_matrix.size();i++){
        if(std::isnan(cost_matrix[row][i])){
            pom += 1;
        }
    }
    return pom == cost_matrix.size() ? true : false;
}


void TSP_cost_matrix::  find_next_path(){
    double pom_cost = 0;
    double temp_cost = 0;
    pair next_summit;
    for(int row = 0; row < cost_matrix.size(); row++){
        for (int col = 0 ; col < cost_matrix.size(); col ++) {
            if (cost_matrix[row][col] != INF) {
                if (!std::isnan(cost_matrix[row][col])) {
                    if (summit_not_visited(row, col)) {
                        if (cost_matrix[row][col] == 0) {
                            pom_cost = get_path_cost(row, col);
                        }
                        if (pom_cost > temp_cost) {
                            next_summit = std::make_pair(row, col);
                            temp_cost = pom_cost;
                        }
                    }
                }
            }
        }
    }
    solution .push_back(next_summit);
}


void  TSP_cost_matrix:: forbid_point(int row, int col){
    cost_matrix[row][col] = NAN;
}


double TSP_cost_matrix::  get_path_cost(int path_row, int path_col){
    double pom = cost_matrix[path_row][path_col];
    cost_matrix[path_row][path_col] = INF ;

    double min_row = INFINITY;
    for(int i =0 ; i < cost_matrix[path_row].size(); i++){
        if(cost_matrix[path_row][i]!= INF ) {
            min_row = std::min(min_row, cost_matrix[path_row][i]);
        }
    }
    double min_col = INFINITY;
    transform();
    for(int i =0 ; i < cost_matrix.size(); i++){
        if(cost_matrix[path_col][i]!= INF) {
            if(min_col > cost_matrix[path_col][i]){
                min_col = cost_matrix[path_col][i];
            }
        }
    }
    transform();
    cost_matrix[path_row][path_col] = pom ;
    double sum = min_col + min_row;
    return sum;
}


void TSP_cost_matrix::  find_solution(){
    for(int i=0; i < cost_matrix.size(); i++){
        findBestPath();
        forbid_point(solution[i].second, solution[i].first);
        reduce_col(solution[i].second);
        reduce_row(solution[i].first);
    }
}

void  TSP_cost_matrix:: solution_to_vector(){
    the_end.push_back(solution[0].first+1);
    the_end.push_back(solution[0].second+1);
    int a = 1;
    do{
        for(int i =0 ; i< solution.size();i++){
            if(the_end.back()==solution[i].first+1){
                the_end.push_back(solution[i].second+1);
                a++;
            }
        }
    } while(solution.size() > a);
}


std::vector<int> tsp(matrix m) {
    TSP_cost_matrix mat(m);
    mat.find_solution();
    mat.solution_to_vector();
    return mat.the_end;
}

