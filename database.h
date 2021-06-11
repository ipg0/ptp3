#ifndef DATABASE_H
#define DATABASE_H

#include <fstream>
#include <cstring>

#define STRSIZE 64

enum class FilterOption {genreFilter, actorFilter};

class DatabaseNode {
public:
    char name[STRSIZE], genre[STRSIZE], mainActor[STRSIZE], rating;
    size_t year;
    DatabaseNode() { }
    DatabaseNode(char *_name, size_t _year, char *_genre, char *_mainActor, char _rating);
    DatabaseNode(std::istream &input);
    DatabaseNode(DatabaseNode &other);
    void write(std::ostream &output);
    bool operator<(DatabaseNode &other) { return strcmp(name, other.name) < 0; }
};

class Database {
private:
    std::fstream file;
    size_t quantity;
    char filename[STRSIZE];
public:
    Database(char const *filename);
    size_t update(DatabaseNode *&nodes);
    void add(DatabaseNode newNode);
    void remove(size_t index);
    size_t filter(DatabaseNode *&nodes, char *filter, char margin = -1, FilterOption option = FilterOption::actorFilter);
    size_t graphingData(size_t *&values, size_t minYear, size_t maxYear);
    DatabaseNode leastPopular();
};

#endif
