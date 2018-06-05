#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <vector>

//#include "5055278_maxclique.hpp"

using namespace std;

//Algorithm to solve maxmimum clique problem
//Order vertices by degrees

class set
{
    /*
     * A class that creates an adjacency Set from the file of edges
     * l - list of vertices
     * nl - list of vertex indcies
     * len -
     * n - number of vertices
     */
    int *l, *nl, len, n;
    public:
    set(int n);
    void init(int v);
    void init(set *s);
    void add(int v);
    void remove(int v);
    bool in(int v);
    void intersect(set *s);
    int rand_select();
    int count();
    void clear();
    void zero_clear();
    void level_intersect(set *s, set *currentClique);
    void level_init(set *s);
    int getVertex(int v);
    ~set();
    friend ostream& operator << (ostream &os, const set &s);
};

set::set(int n)
{
    this->n = n;
    l = new int[n];
    nl = new int[n + 1];
    clear();
}

void set::init(int v)
{
    clear();
    add(v);
}

void set::init(set *s)
{
    clear();
    for (int i = 0; i < s->len; i++)
        add(s->l[i]);
}

void set::level_init(set *s)
{
    clear();
    for (int i = 0;)
}

void set::add(int v)
{
    l[len] = v;
    nl[v] = len++;
}

void set::remove(int v)
{
    int *ptr0 = l, *ptr1 = &nl[v];
    *(ptr0 + *ptr1) = *(ptr0 + (--len));
    nl[*(ptr0 + len)] = *ptr1;
    *ptr1 = -1;
}

void set::intersect(set *s)
{
    /*
     * Checks if vertices in the expanding list are also connected to the recently added vertex.
     * If a vertex isn't connected, then it is removed from expanding set.
     */
    for (int i = 0, *p = l; len > 0 && i < len; i++, p++)
        if (not s->in(*p))
        {remove(*p);
            i--; // as we have just modified our adjList
            p--; // as we have just modified our adjList
        }
}

void set::level_intersect(set *s, set *currentClique)
{
    int noDisconnectedVertices = 0;
    for (int i = 0, *p = l; len > 0 && i < len; i++, p++)
        if (not s->in(*p))
        {
            noDisconnectedVertices++;
            remove(*p);
            i--; // as we have just modified our adjList
            p--; // as we have just modified our adjList
        }
}

int set::rand_select()
{
    return l[rand() % len];
}

bool set::in(int v)
{
    return nl[v] != -1;
}

int set::getVertex(int v)
{
    return l[v];
}

int set::count()
{
    return len;
}
void set::zero_clear()
{
    for (int i = 1; i <= n; i++)
        nl[i] = 0;
    len = 0;
}
// Sets all vertices in the set to -1
void set::clear()
{
    for (int i = 1; i <= n; i++)
        nl[i] = -1;
    len = 0;
}
// Class destructor
set::~set()
{
    delete l;
    delete nl;
}


ostream &operator<<(ostream &os, const set &s)
{for (int i = 0; i < s.len; i++)
        os << s.l[i] << " ";
    os << endl;
    return os;
}

// create empty adjacency sets
set** createAdjSet(int n)
{set **as = new set* [n + 1];
    for (int i = 1; i <= n; i++)
        as[i] = new set(n);
    return as;
}



int main(int argc, char **argv)
{
    FILE *data = fopen(argv[1], "r");
    char c;
    int a, b;
    int found1, found2;
    char line[25];
    string word;
    int i, step;
    int iterator = 0;
    int maxClique = 0;
    int noVertices = 800;
    int max_steps = 100;
    int penalty_delay;

    set **as = createAdjSet(noVertices);
    //vector<list <int>> adjList(800);

    while (fgets(line, 25, data) && a <= 800) {


        if (line[0] == 'e') {
            i = 0;
            a = 0;
            b = 0;
            //printf("%s", line);
            while (!(line[i] >= 48 && line[i] <= 57)) i++;
            while (line[i] != 32){
                a = a*10 + line[i++]-48;

                //i++;
            }
            //printf("A: %d ", a);

            i++;
            while (line[i] != 10) {
                b = b*10 + line[i++]-48;

                //i++;
            }
            //printf("B: %d", b);
            as[a]->add(b);
            //printf("List: %d\n ");
        }
    }

    set currentClique(noVertices);

    set expanding(noVertices);

    // Choose random vertex to add to the currentClique
    int randStartingPoint = rand() % noVertices + 1;
    // Add random node to the clique
    currentClique.init(randStartingPoint);
    // Add the nodes from the adjacency set for the random vertex to the expanding set
    expanding.init(as[randStartingPoint]);

    set penalties(noVertices);
    penalties.zero_clear();

    set level(noVertices);
    step = 0;
    while (step <= max_steps)
    {
        while (expanding.count() > 0) {
            // Randomly choose vertex from expanding set to add the the current clique
            int v = expanding.rand_select();
            // Remove it from expanding
            expanding.remove(v);
            currentClique.add(v);

            // Remove nodes from the expanding that aren't connected to vertex v
            expanding.intersect(as[v]);
            step++;
        }
        set recordedClique = currentClique;
        int notConnected = 0;
        // Iterate through each vertex in the current clique
        for (int j = 0; j <= currentClique.count(); j++){
            for (int k = 0; k < as[j]->count(); k++){
                notConnected = 0;
                a = as[j]->getVertex(k);
                for (int l = 0; l < currentClique.count(); l++){
                    for (int p = 0; p < as[l]->count(); p++){
                        if (as[j]->in(as[p]->getVertex(p))){
                            notConnected++;
                            a =
                        }
                    }
                }
                if (notConnected == 1){
                    level.add(a);
                }
            }

        }
        while (expanding.count() == 0 && )

        if (currentClique.count() > maxClique) {
            cout << "Max Clique: " << currentClique;
            maxClique = currentClique.count();
        }

    }
    cout << "Maximum Clique Size is " << maxClique << endl;
//Hold the command line open
    printf("\nEnter a character to exit:");
    getchar();
    return 0;
}

void appendEdge(struct Graph* graph, int source, int destination)
{
    
}



