#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <list>
#include <vector>
#include <ctime>


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
    friend std::ostream& operator << (std::ostream &os, const set &s);
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

std::ostream &operator<<(std::ostream &os, const set &s)
{for (int i = 0; i < s.len; i++)
        os << s.l[i] << " ";
    os << std::endl;
    return os;
}

// create empty adjacency sets
set** createAdjSet(int n)
{set **as = new set* [n + 1];
    for (int i = 1; i <= n; i++)
        as[i] = new set(n);
    return as;
}