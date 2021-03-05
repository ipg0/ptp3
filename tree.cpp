#include "tree.h"
#include <cstring>
#include <fstream>
#include <vector>
#include <array>

tree::node_data::node_data() {};

tree::node_data::node_data(char *_name, char *_genre, char *_main_actor, short _year, short _rating) {
    strcpy(name, _name);
    strcpy(genre, _genre);
    strcpy(main_actor, _main_actor);
    year = _year;
    rating = _rating;
}

tree::node_data::node_data(char *read) {
    memcpy(this, reinterpret_cast<void*>(read), sizeof(struct node_data));
}

tree::node::node(node_data _data) {
    data = _data;
    l = r = nullptr;
}

char *tree::node::writable() {
    return reinterpret_cast<char*>(&data);
}

tree::tree() {
    root = nullptr;
}

tree::tree(std::istream &f) {
    root = nullptr;
    char *data = new char[sizeof(node_data)];
    while(!f.eof()) {
        f.read(data, block_size());
        if(f.good())
            _insert(data);
    }
    delete[] data;
}

tree::node *tree::merge(node *l, node *r) {
    if(!l)
        return r;
    if(!r)
        return l;
    if(l->p() < r->p()) {                               // change priority order
        l->r = merge(l->r, r);
        return l;
    }
    else {
        r->l = merge(l, r->l);
        return r;
    }
}

std::pair<tree::node*, tree::node*> tree::split(node *rt, char *k) {
    if(!rt)
        return {nullptr, nullptr};
    if(strcmp(rt->k(), k) > 0) {
        std::pair<node*, node*> q = split(rt->r, k);
        rt->r = q.first;
        return {rt, q.second};
    }
    else {
        std::pair<node*, node*> q = split(rt->l, k);
        rt->l = q.second;
        return {q.first, rt};
    }
}

tree::node *tree::_insert(node *rt, node *n) {
    std::pair<node*, node*> q = split(rt, n->k());
    return merge(q.first, merge(n, q.second));
}

tree::node *tree::_remove(node *rt, char *name) {
    if(!rt)
        return rt;
    if(!strcmp(rt->k(), name)) {
        node *temp = merge(rt->l, rt->r);
        delete rt;
        return temp;
    }
    else if(strcmp(rt->k(), name) < 0)
        rt->l = _remove(rt->l, name);
    else
        rt->r = _remove(rt->r, name);
    return rt;
}

void tree::insert(node_data _data) {
    node *n = new node(_data);
    root = _insert(root, n);
}

void tree::_insert(char *read) {
    insert(node_data(read));
}

void tree::remove(char *name) {
    root = _remove(root, name);
}

void tree::_write_subtree(node *rt, std::ostream &f) {
    if(!rt)
        return;
    f.write(rt->writable(), block_size());
    _write_subtree(rt->l, f);
    _write_subtree(rt->r, f);
}

void tree::write(std::ostream &f) {
    _write_subtree(root, f);
}

void tree::_remove_all(node *rt) {
    if(!rt)
        return;
    node *ltemp = rt->l, *rtemp = rt->r;
    delete rt;
    _remove_all(ltemp);
    _remove_all(rtemp);
}

void tree::_best_rated(node *rt, short threshold, std::vector<node_data> &result) {
    if(!rt)
        return;
    _best_rated(rt->r, threshold, result);
    if(rt->data.rating >= threshold)
        result.push_back(rt->data);
    _best_rated(rt->l, threshold, result);
}

void tree::_starring(node *rt, char *actor, std::vector<node_data> &result) {
    if(!rt)
        return;
    _starring(rt->r, actor, result);
    if(!strcmp(rt->data.main_actor, actor))
        result.push_back(rt->data);
    _starring(rt->l, actor, result);
}

void tree::_build_graph(node *rt, short threshold, std::array<size_t, years> &result) {
    if(!rt)
        return;
    if(rt->data.rating >= threshold)
        result[rt->data.year]++;
    _build_graph(rt->r, threshold, result);
    _build_graph(rt->l, threshold, result);
}

std::vector<tree::node_data> tree::best_rated(short threshold) {
    std::vector<node_data> result;
    _best_rated(root, threshold, result);
    return result;
}

std::vector<tree::node_data> tree::starring(char *actor) {
    std::vector<node_data> result;
    _starring(root, actor, result);
    return result;
}

std::array<size_t, tree::years> tree::build_graph(short threshold) {
    std::array<size_t, years> result;
    result.fill(0);
    _build_graph(root, threshold, result);
    return result;
}

tree::~tree() {
    _remove_all(root);
}
