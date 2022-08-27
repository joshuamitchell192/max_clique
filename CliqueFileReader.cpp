#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <ctime>

#include "Set.cpp"
#include "CliqueFileConfig.cpp"

set** populateAdjacencyMatrix(FILE *data, int vertexCount)
{
    int i;
    int vertexA, vertexB;
    char line[30];

    set **as = createAdjSet(vertexCount);

    while (fgets(line, 30, data) && vertexA <= 2100) {

        if (line[0] == 'e')
        {
            i = 0;
            vertexA = 0;
            vertexB = 0;
            // Increase index till we're reading vertex numbers
            while (!(line[i] >= 48 && line[i] <= 57)) i++;

            // Convert the vertex number from a string to an int
            while (line[i] != 32) {
                vertexA = vertexA * 10 + line[i++] - 48;
            }

            i++;
            
            // Convert the second vertex to an int
            while (line[i] != 10) {
                vertexB = vertexB * 10 + line[i++] - 48;
            }

            as[vertexA]->add(vertexB);
            as[vertexB]->add(vertexA);
        }
    }

    return as;
}

CliqueFileConfig readFileConfig(FILE *data)
{
    char line[30];
    CliqueFileConfig config;

    while (fgets(line, 30, data))
    {
        std::string lineString(line);
        std::cout << "Line " << lineString << std::endl;
        size_t foundIndex = lineString.find("Graph Size:");
        if (foundIndex != std::string::npos)
        {
            int i = foundIndex;
            while (line[i] != 32) {
                config.graphSize = config.graphSize * 10 + line[i++] - 48;
            }

            return config;
        }
    }

    return config;
}