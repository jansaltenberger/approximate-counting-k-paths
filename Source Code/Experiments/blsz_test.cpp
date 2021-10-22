// blsz_test.cpp version 1.0; Jan Saltenberger, Oktober 2021.

#include <fstream>
#include <string>
#include <iostream>

#ifdef BLSZ_EXACT
    #include "blsz/blsz_exact.hpp"
#elif  BLSZ
    #include "blsz/blsz.hpp"
#endif

#include "blsz/blsz_graph_reader.hpp"

int main(int argc, char* argv[]) {
    int** G = 0;
    const char* graph;
    unsigned long n = 0;
    unsigned k, t;
    unsigned long long result;
    int seed;

    k = atoi(argv[2]);

#ifndef BLSZ_EXACT

    t = atoi(argv[3]);
    seed = atoi(argv[4]);
    srand(seed);

#endif // !BLSZ_EXACT

    std::ifstream infile(argv[1]);

    if (infile.good()) {
        std::string line;
        getline(infile, line);
        graph = line.c_str();
        G = blsz_g6tograph(graph, line.length(), &n);
    }

    if (G == 0) {
        printf("ERROR: unable to read graph\n");
        return 1;
    }

    #ifdef BLSZ_EXACT
        result = k_paths(G, n, k);
    #elif  BLSZ
        result = k_paths(G, n, k, t);
    #endif

    std::cout << result;

    return 0;
}
