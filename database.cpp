#include "database.h"
#include <filesystem>

DatabaseNode::DatabaseNode(char *_name, size_t _year, char *_genre, char *_mainActor, char _rating) {
    strcpy(name, _name);
    strcpy(genre, _genre);
    strcpy(mainActor, _mainActor);
    year = _year;
    rating = _rating;
}

DatabaseNode::DatabaseNode(std::istream &input) {
    input.read(reinterpret_cast<char *>(this), sizeof(DatabaseNode));
}

DatabaseNode::DatabaseNode(DatabaseNode &other) {
    strcpy(name, other.name);
    strcpy(genre, other.genre);
    strcpy(mainActor, other.mainActor);
    year = other.year;
    rating = other.rating;
}

Database::Database(char const *filename) {
    file.open(filename, std::ios::in | std::ios::binary);
    if(!file.is_open())
        file.open(filename, std::ios::out | std::ios::trunc | std::ios::binary);
    file.close();
    strcpy(this->filename, filename);
}

void DatabaseNode::write(std::ostream &output) {
    output.write(reinterpret_cast<char *>(this), sizeof(DatabaseNode));
}

size_t Database::update(DatabaseNode *&nodes) {
    file.open(filename, std::ios::in | std::ios::binary);
    DatabaseNode buffer = DatabaseNode(file);
    nodes = nullptr;
    quantity = 0;
    while(!file.eof()) {
        nodes = reinterpret_cast<DatabaseNode *>(realloc(nodes, ++quantity * sizeof(DatabaseNode)));
        nodes[quantity - 1] = buffer;
        buffer = DatabaseNode(file);
    }
    file.close();
    return quantity;
}

void Database::add(DatabaseNode newNode) {
    ++quantity;
    file.open(filename, std::ios::in | std::ios::out | std::ios::binary);
    DatabaseNode buffer = DatabaseNode(file);
    while(!file.eof() && buffer < newNode) {
        buffer = DatabaseNode(file);
    }
    buffer = newNode;
    if(!file.eof()) {
        file.seekg(-sizeof(DatabaseNode), std::ios::cur);
        while(!file.eof()) {
            DatabaseNode temp = DatabaseNode(file);
            file.seekp(-sizeof(DatabaseNode), std::ios::cur);
            buffer.write(file);
            buffer = temp;
        }
    }
    file.clear();
    file.seekp(0, std::ios::end);
    buffer.write(file);
    file.close();
}

void Database::remove(size_t index) {
    file.open(filename, std::ios::in | std::ios::out | std::ios::binary);
    file.seekg((index + 1) * sizeof(DatabaseNode), std::ios::beg);
    while(!file.eof()) { 
        DatabaseNode temp = DatabaseNode(file);
        file.seekp(-2 * sizeof(DatabaseNode), std::ios::cur);
        temp.write(file);
        file.seekp(sizeof(DatabaseNode), std::ios::cur);
    }
    file.close();
    std::filesystem::resize_file(filename, --quantity * sizeof(DatabaseNode));
}

size_t Database::filter(DatabaseNode *&nodes, char *filter, char margin, FilterOption option) {
    file.open(filename, std::ios::in | std::ios::binary);
    DatabaseNode buffer = DatabaseNode(file);
    nodes = nullptr;
    size_t localQuantity = 0;
    while(!file.eof()) {
        if(((option == FilterOption::actorFilter
                && strcmp(filter, buffer.mainActor) == 0)
                || (option == FilterOption::genreFilter
                && strcmp(filter, buffer.genre) == 0))
                && buffer.rating >= margin) {
            nodes = reinterpret_cast<DatabaseNode *>(realloc(nodes, ++localQuantity * sizeof(DatabaseNode)));
            nodes[localQuantity - 1] = buffer;
        }
        buffer = DatabaseNode(file);
    }
    file.close();
    return localQuantity;
}
/*
size_t Database::starring(DatabaseNode *&nodes, char *actor) {
    file.open(filename, std::ios::in | std::ios::binary);
    DatabaseNode buffer = DatabaseNode(file);
    nodes = nullptr;
    size_t localQuantity = 0;
    while(!file.eof()) {
        if(!strcmp(buffer.mainActor, actor)) {
            nodes = reinterpret_cast<DatabaseNode *>(realloc(nodes, ++localQuantity * sizeof(DatabaseNode)));
            nodes[localQuantity - 1] = buffer;
            buffer = DatabaseNode(file);
        }
    }
    file.close();
    return localQuantity;
}*/

DatabaseNode Database::leastPopular() {
    file.open(filename, std::ios::in | std::ios::binary);
    DatabaseNode buffer = DatabaseNode(file);
    DatabaseNode currentLeastRated = buffer; 
    while(!file.eof()) {
        if(buffer.rating < currentLeastRated.rating)
            currentLeastRated = buffer;
        buffer = DatabaseNode(file);
    }
    if(buffer.rating < currentLeastRated.rating)
        currentLeastRated = buffer;
    file.close();
    return currentLeastRated;
}
