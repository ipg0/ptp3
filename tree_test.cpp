#include <iostream>
#include "tree.h"
#include "tree.cpp"
#include <fstream>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    std::string name, genre, main_actor;
    short year, rating;
    tree *t = new tree();
    char q = ' ';
    while(q != 'q') {
        std::cin >> q;
        if(q == 'a') {
            std::cin >> name >> genre >> main_actor >> year >> rating;
            t->insert(tree::node_data(const_cast<char*>(name.c_str()), const_cast<char*>(genre.c_str()), const_cast<char*>(main_actor.c_str()), year, rating));
        }
        if(q == 'd') {
            std::cin >> name;
            t->remove(const_cast<char*>(name.c_str()));
        }
        if(q == 'l') {
            std::cin >> rating;
            std::vector<tree::node_data> res = t->best_rated(rating);
            for(auto it : res)
                std::cout << it.name;
        }
        if(q == 'w') {
            std::cin >> name;
            std::ofstream f("/home/pyro/problems/" + name, std::ios::binary);
            t->write(f);
            f.close();
        }
        if(q == 'r') {
            std::cin >> name;
            std::ifstream f("/home/pyro/problems/" + name, std::ios::binary);
            t = new tree(f);
            f.close();
        }
    }
    delete t;
}