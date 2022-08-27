#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <ctime>

//#include "5055278_maxclique.hpp"
#include "./Set.cpp"
#include "CliqueFileConfig.cpp"
#include "CliqueFileReader.cpp"

using namespace std;

//Algorithm to solve maxmimum clique problem
//Order vertices by degrees



int main(int argc, char **argv) {
    FILE *data = fopen(argv[1], "r");
    char c;
    int found1, found2;
    string word;
    int step;
    int iterator = 0;
    int maxClique = 0;
    int noVertices = 1035;
    int max_steps = 10000;
    int penalty_delay;
    clock_t begin = clock();

    set **as = populateAdjacencyMatrix(data, noVertices);
    // int graphSize = readFileConfig(data);
    // cout << "Graph Size: " << graphSize << endl;
    step = 0;
    set currentClique(noVertices);

    set expanding(noVertices);
    int startingPoint;
    for (int j = 1; j < noVertices; j++) {
        // Choose random vertex to add to the currentClique
        startingPoint = j;
        // Add random node to the clique
        currentClique.init(startingPoint);
        // Add the nodes from the adjacency set for the random vertex to the expanding set
        expanding.init(as[startingPoint]);

        set penalties(noVertices);
        //penalties.zero_clear();

        //set cost(noVertices);


        while (expanding.count() > 0) {
            int maxDegrees = 0;
            int v, degrees;
            for (int i = 0; i < expanding.count(); i++) {
                degrees = as[expanding.getVertex(i)]->count();
                //printf("Degrees: %d\nExpanding Count: %d\n", degrees, expanding.count());

                if (degrees > maxDegrees) {
                    maxDegrees = degrees;
                    v = expanding.getVertex(i);
                    //printf("Max Degrees: %d\n", maxDegrees);
                }


            }
            // Remove it from expanding and add to current clique
            expanding.remove(v);
            currentClique.add(v);
            penalties.update(v);
            // Remove nodes from the expanding that aren't connected to vertex v
            expanding.intersect(as[v]);
            // Increment the number of steps every time the current clique is expanded.
            step++;
        }

        if (currentClique.count() > maxClique) {
            cout << "Max Clique: " << currentClique << endl;
            maxClique = currentClique.count();

        }

    }
    clock_t end = clock();
    double time = double(end - begin) / CLOCKS_PER_SEC;
    cout << "Time: " << time << endl;
    cout << "Number of steps: " << step << endl;
    cout << "Maximum Clique Size is " << maxClique << endl;

    //Hold the command line open
    printf("\nEnter a character to exit:");
    getchar();
    return 0;
}



