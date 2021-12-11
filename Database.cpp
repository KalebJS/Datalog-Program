//
// Created by Kaleb Smith on 10/26/21.
//

#include <sstream>
#include "Database.h"

Database::Database() = default;

Database::~Database() {
    for (auto relation : relations) {
        delete relation;
    }
}

void Database::AddRelation(const Predicate &scheme) {
    relations.emplace_back(new Relation(scheme));
}

bool Database::ContainsRelation(Relation *relation) {
    for (auto &r: relations) {
        if (r->GetName() == relation->GetName()) {
            return true;
        }
    }
    return false;
}

void Database::AddRelationParameters(Predicate fact) {
    for (auto &relation: relations) {
        if (relation->GetName() == fact.GetId()) {
            relation->AddTuple(fact);
            return;
        }
    }
}

std::string Database::ToString() {
    std::stringstream ss;
    for (auto &relation: relations) {
        ss << relation->ToString() << std::endl;
    }
    return ss.str();
}

Relation Database::GetDereferencedRelation(const std::string &relationName) {
    for (auto &relation: relations) {
        if (relation->GetName() == relationName) {
            return *relation;
        }
    }
    throw ("Relation not found");
}
Relation* Database::GetRelation(const std::string &relationName) {
    for (auto &relation: relations) {
        if (relation->GetName() == relationName) {
            return relation;
        }
    }
    throw ("Relation not found");
}