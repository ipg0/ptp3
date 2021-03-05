#ifndef TREE_H
#define TREE_H

#include <utility>
#include <iostream>
#include <vector>
#include <array>

typedef unsigned long size_t;

class tree {
public:
    static const size_t strsize = 16;
    static const short years = 3000;
    struct node_data {
        char name[strsize], genre[strsize], main_actor[strsize];
        short year, rating;
        node_data();
        node_data(char *_name, char *_genre, char *_main_actor, short _year, short _rating);
        node_data(char *read);
    };
private:
    struct node {
        node_data data;
        node *l, *r;
        node(node_data _data);
        char *k() {return data.name;}
        short p() {return data.rating;}
        char *writable();
    };
    node *root;
    std::pair<node*, node*> split(node *rt, char *k);
    node *merge(node *l, node *r);
    node *_insert(node *rt, node *n);
    void _insert(char *read);
    node *_remove(node *rt, char *name);
    void _remove_all(node *rt);
    size_t block_size() {return sizeof(node_data);}
    void _write_subtree(node *rt, std::ostream &f);
    void _best_rated(node *rt, short threshold, std::vector<node_data> &result);
    void _starring(node *rt, char *actor, std::vector<node_data> &result);
    void _build_graph(node *rt, short threshold, std::array<size_t, years> &result);
public:
    tree();                                                     // works
    tree(std::istream &f);                                      // works
    void insert(node_data data);                                // works
    void remove(char *name);                                    // works
    void write(std::ostream &f);                                // works
    node_data min_rated() {return root->data;}                  // works
    std::vector<node_data> best_rated(short threshold);         // works
    std::vector<node_data> starring(char *actor);               // works(?)
    std::array<size_t, years> build_graph(short threshold);     // works(?)
    ~tree();                                                    // works
};

#endif // TREE_H