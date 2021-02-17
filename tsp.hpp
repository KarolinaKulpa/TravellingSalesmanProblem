// Karolina Kulpa 303024
#ifndef TSP_HPP
#define TSP_HPP

#include <iostream>
#include <vector>
#include<string>
#include<limits>
#include <cmath>
#include<utility>

double get_forbidden_cost();
const double INF = get_forbidden_cost();
using matrix = std::vector<std::vector<double>>;
using vector = std :: vector<double>;
using pair = std:: pair<int , int>;
using pair_vec = std::vector<std::pair<int,int>>;



class TSP_cost_matrix {
public:
    matrix cost_matrix;
    double low_bound;
    pair_vec solution;
    std::vector<int> the_end;

    TSP_cost_matrix(matrix m);
    double find_min(int row);
    void reduce_all_rows();
    void transform();
    void reduce_all_cols();
    void reduce_row(int row);
    void reduce_col(int col);
    void findBestPath ();
    bool summit_not_visited(int row, int col);
    bool isnan_row(int row);
    void find_next_path();
    void forbid_point(int row, int col);
    double get_path_cost(int path_row, int path_col);
    void find_solution();
    void solution_to_vector();
};

std::vector<int> tsp(matrix m);
#endif //TSP_HPP
