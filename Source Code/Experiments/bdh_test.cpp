// bdh_test.cpp version 1.0; Jan Saltenberger, August 2021.

#include <fstream>
#include <string>
#include <iostream>

#ifdef BDH_LINKED_LIST
    #include "bdh/bdh_linked_list.hpp"
#elif  BDH_UNORDERED_MAP
    #include "bdh/bdh_unordered_map.hpp"
#endif

#include "bdh/bdh_graph_reader.hpp"

int main(int argc, char* argv[]) {
    int** G = 0;
    const char* graph;
    unsigned long n = 0;
    unsigned k, t;
    unsigned long long result;
    int seed;

    k = atoi(argv[2]);
    t = atoi(argv[3]);
    seed = atoi(argv[4]);

    srand(seed);

    std::ifstream infile(argv[1]);

    if (infile.good()) {
        std::string line;
        getline(infile, line);
        graph = line.c_str();
        G = bdh_g6tograph(graph, line.length(), &n);
    }

    if (G == 0) {
        printf("ERROR: unable to read graph\n");
        return 1;
    }
    result = k_paths(G, n, k, t);

    std::cout << result;

    return 0;
}
