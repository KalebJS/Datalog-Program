//
// Created by Kaleb Smith on 10/26/21.
//

#ifndef DATALOG_DATABASE_H
#define DATALOG_DATABASE_H

#include <vector>
#include "Relation.h"
#include "Predicate.h"

class Database {
private:
    std::vector<Relation *> relations;
public:
    Database();

    ~Database();

    void AddRelation(const Predicate &scheme);

    void AddRelationParameters(Predicate fact);

    Relation *FindRelation(const std::string &relationName);

    std::string ToString();

    bool ContainsRelation(Relation *relation);
};


#endif //DATALOG_DATABASE_H
