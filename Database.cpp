//
// Created by Kaleb Smith on 10/26/21.
//

#include <sstream>
#include "Database.h"

Database::Database() = default;

Database::~Database() = default;

void Database::AddRelation(const Predicate &scheme) {
    relations.push_back(Relation(scheme));
}

void Database::AddRelationParameters(Predicate fact) {
    for (auto &relation: relations) {
        if (relation.GetName() == fact.GetId()) {
            relation.AddTuple(fact);
            return;
        }
    }
}

std::string Database::ToString() {
    std::stringstream ss;
    for (auto &relation: relations) {
        ss << relation.ToString() << std::endl;
    }
    return ss.str();
}

Relation Database::FindRelation(const std::string& relationName) {
    for (auto &relation: relations) {
        if (relation.GetName() == relationName) {
            return relation;
        }
    }
    throw ("Relation not found");
}