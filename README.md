## Introduction
This repository contains implementations of FPT algorithms for approximately counting the number of k-paths in a graph. One algorithm is by Brand, Dell and Husfeldt (BDH), the other by Björklund, Lokshtanov, Saurabh and Zehavi (BLSZ). 

The problem of counting exactly all paths of length k is proven to be #W[1]-hard. This implies that it cannot be solved in f(k)n<sup>O(1)</sup> for any computable function f and constant c. The problem of approximately counting k-paths, on the other hand, is fixed-parameter tractable and can be solved in f(k)n<sup>O(1)</sup>-time.

<table>
    <tr>
        <th>Algorithm</th>
        <th>Technique</th>
        <th>Time</th>
        <th>ε<sup>-1</sup></th>
        <th>Space</th>
    </tr>
    <tr>
        <td>BDH</td>
        <td>Extensor Coding</td>
        <td>4<sup>k+o(k)</sup>n<sup>O(k)</sup>m</td>
        <td>2<sup>O(k)</sup></td>
        <td>exponential</td>
    </tr>
        <td>BLSZ</td>
        <td>Divide & Color</td>
        <td>4<sup>k+o(k)</sup>n<sup>O(k)</sup>m log n</td>
        <td>2<sup>O(k/log k)</sup></td>
        <td>polynomial</td>
  </tr>
</table>

The repository contains a total of four different implementations, two for each algorithm. 

```.
└── Source Code
    ├── BDH (Extensor-Coding)
    │   ├── include
    |   │   ├── bdh_linked_list.hpp
    |   │   ├── bdh_unordered_map.hpp
    |   |   └── bdh_graph_reader.hpp
    └── BLSZ (Divide-And-Color)
        └── include
            ├── blsz_exact.hpp
            ├── blsz.hpp
            └── blsz_graph_reader.hpp
```

## Example 
```.
int main() {
    int** G = 0;
    const char* graph;
    unsigned long n = 0;
    unsigned k, t;
    unsigned long long result;
    int seed;

    k = 4;
    t = 1000;

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
    
    result = k_paths(G, n, k, t);

    return 0;
}

```
## Experiments

All experimental results were obtained on a dedicated server with an Intel® Core™ i7-8700 hexa-core processor based on Coffee Lake architecture with 128GB DDR4 RAM, running Ubuntu 20.04.2 LTS. 
In each case, the algorithm was compiled using g++ from the GNU Compiler Collection (GCC).

## Required tools

In order to to replicate the experiments 

```bash
> sudo apt install git
```

```bash
> sudo apt install cmake
```

```bash
> sudo apt install gcc g++ build-essential
```

```bash
> sudo apt install install linux-tools-$(uname -r) linux-tools-generic -y
```

## Generating the project files

```bash
> mkdir approximate-k-paths
```

```bash
> git clone https://github.com/jansaltenberger/approximate-counting-k-paths.git approximate-k-paths
```

```bash
> cmake -DCMAKE_BUILD_TYPE=Release -S "Source Code" -B Release
```

## Build

```bash
> cd approximate-k-paths
```

```bash
> cmake -DCMAKE_BUILD_TYPE=Release -S "Source Code" -B Release
```

```bash
> cmake --build Release
```

```bash
> cmake -DCMAKE_BUILD_TYPE=Debug -S "Source Code" -B Debug
```

```bash
> cmake --build Debug
```
## Run

```bash
> cd Experiments/Release
```

```bash
> chmod +x blsz
```
```bash
> ./blsz
```      
                     
