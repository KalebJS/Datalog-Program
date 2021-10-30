//
// Created by Kaleb Smith on 10/23/21.
//

#include <sstream>
#include <iostream>
#include "Relation.h"


Relation::Relation(Predicate scheme) {
    name = scheme.GetId();
    header = Header(scheme.GetParameters());
}

Relation::Relation(std::string copiedName, Header copiedHeader, std::set<Tuple> copiedTuples) {
    name = copiedName;
    header = copiedHeader;
    tuples = copiedTuples;
}

Relation::~Relation() = default;

void Relation::AddTuple(Predicate fact) {
    tuples.insert(Tuple(fact.GetParameters()));
}

Relation Relation::Select(int tupleIndex, const std::string &value) {
    Relation selectedRelation = Relation(name, header, tuples);
    selectedRelation.FilterTuples(tupleIndex, value);
    return selectedRelation;
}

Relation Relation::Select(std::vector<int> tupleIndexes) {
    Relation selectedRelation = Relation(name, header, tuples);
    selectedRelation.FilterTuples(tupleIndexes);
    return selectedRelation;
}

Relation Relation::Project(const std::vector<std::string> &idList) {
    Relation projectedRelation = Relation(name, header, tuples);
    projectedRelation.FilterColumns(idList);
    return projectedRelation;
}


Relation Relation::Project(const std::vector<int> &indexList) {
    Relation projectedRelation = Relation(name, header, tuples);
    projectedRelation.FilterColumns(indexList);
    return projectedRelation;
}

Relation Relation::Rename(const std::string &id, std::string value) {
    Relation renamedRelation = Relation(name, header, tuples);
    renamedRelation.UpdateHeader(id, value);
    return renamedRelation;
}

Relation Relation::Rename(const int &index, const std::string &value) {
    Relation renamedRelation = Relation(name, header, tuples);
    renamedRelation.UpdateHeader(index, value);
    return renamedRelation;
}

void Relation::UpdateHeader(const std::string &id, std::string value) {
    header.ChangeParameter(id, value);
}

void Relation::UpdateHeader(const int &index, const std::string &value) {
    header.ChangeParameter(index, value);
}

void Relation::FilterTuples(int tupleIndex, const std::string &value) {
    std::set<Tuple> filteredTuples;
    for (Tuple tuple: tuples) {
        if (tuple.ContainsValueAtIndex(tupleIndex, value)) {
            filteredTuples.insert(tuple);
        }
    }
    tuples = filteredTuples;
}

void Relation::FilterTuples(const std::vector<int> &tupleIndexes) {
    std::set<Tuple> filteredTuples;
    for (Tuple tuple: tuples) {
        std::string value;
        bool appendToFilteredTuples = true;
        for (int tupleIndex: tupleIndexes) {
            if (value.empty()) {
                value = tuple.GetValueAtIndex(tupleIndex);
            }
            if (tuple.GetValueAtIndex(tupleIndex) != value) {
                appendToFilteredTuples = false;
                break;
            }
        }
        if (appendToFilteredTuples) {
            filteredTuples.insert(tuple);
        }
    }
    tuples = filteredTuples;
}

void Relation::FilterColumns(const std::vector<std::string> &idList) {
    std::vector<int> indexList = header.Project(idList);
    for (Tuple tuple: tuples) {
        tuple.Project(indexList);
    }
}

void Relation::FilterColumns(const std::vector<int> &indexList) {
    std::vector<int> projectedIndexList = header.Project(indexList);
    std::set<Tuple> updatedTuples;
    for (Tuple tuple: tuples) {
        tuple.Project(projectedIndexList);
        updatedTuples.insert(tuple);
    }
    tuples = updatedTuples;
}

std::string Relation::ToString() {
    std::stringstream ss;
    ss << name;
    ss << header.ToString() << "\n";
    for (Tuple tuple: tuples) {
        ss << tuple.ToString() << "\n";
    }
    return ss.str();
}


