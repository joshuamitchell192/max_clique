#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <ctime>

//#include "5055278_maxclique.hpp"

using namespace std;

//Algorithm to solve maxmimum clique problem
//Order vertices by degrees

class set
{
    /*
     * A class that creates an adjacency Set from the file of edges
     * l - list of vertices
     * nl - list of vertex indices
     * len - size of the set
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
    void update(int v);
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

//void set::level_init(set *s)
//{
//    clear();
//    for (int i = 0;)
//}

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
    /*
     * Clears the set to values of zero instead of -1 for the penalty set.
     */
    for (int i = 1; i <= n; i++)
        nl[i] = 0;
    len = 0;
}

void set::update(int v){
    /*
     * Increments the passed vertex by one.
     * Used for updating the penalty set
     */
    l[v] += 1;
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



int main(int argc, char **argv) {
    FILE *data = fopen(argv[1], "r");
    char c;
    int a, b;
    int found1, found2;
    char line[30];
    string word;
    int i, step;
    int iterator = 0;
    int maxClique = 0;
    int noVertices = 2100;
    int max_steps = 1000;
    int penalty_delay;

    set **as = createAdjSet(noVertices);
    clock_t begin = clock();

    while (fgets(line, 30, data) && a <= 2100) {


        //cout << line[0] << endl;
        if (line[0] == 'e')
        {
            i = 0;
            a = 0;
            b = 0;
            while (!(line[i] >= 48 && line[i] <= 57)) i++;
            while (line[i] != 32) {
                a = a * 10 + line[i++] - 48;
            }

            i++;
            while (line[i] != 10) {
                b = b * 10 + line[i++] - 48;


            }
            as[a]->add(b);
            as[b]->add(a);
        }
    }
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



