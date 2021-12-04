//
// Created by Kaleb Smith on 10/23/21.
//

#include <sstream>
#include <utility>
#include <iostream>
#include "Relation.h"

Relation::Relation(Header header) {
    this->header = std::move(header);
}

Relation::Relation(Predicate scheme) {
    name = scheme.GetId();
    header = Header(scheme.GetParameters());
}

Relation::Relation(std::string copiedName, Header copiedHeader, std::set<Tuple> copiedTuples) {
    name = std::move(copiedName);
    header = std::move(copiedHeader);
    tuples = std::move(copiedTuples);
}

Relation::~Relation() = default;

void Relation::AddTuple(Predicate fact) {
    tuples.insert(Tuple(fact.GetParameters()));
}

void Relation::ClearNewTuples() {
    newTuples.clear();
}

bool Relation::AddTuple(const Tuple& tuple) {
    if (tuples.insert(Tuple(tuple)).second) {
        newTuples.insert(tuple);
        return true;
    }
    return false;
}

Relation *Relation::Select(int tupleIndex, const std::string &value) {
    auto *selectedRelation = new Relation(name, header, tuples);
    selectedRelation->FilterTuples(tupleIndex, value);
    return selectedRelation;
}

Relation *Relation::Select(const std::vector<int> &tupleIndexes) {
    auto *selectedRelation = new Relation(name, header, tuples);
    selectedRelation->FilterTuples(tupleIndexes);
    return selectedRelation;
}

Relation *Relation::Project(const std::vector<std::string> &idList) {
    auto *projectedRelation = new Relation(name, header, tuples);
    projectedRelation->FilterColumns(idList);
    return projectedRelation;
}


Relation *Relation::Project(const std::vector<int> &indexList) {
    auto *projectedRelation = new Relation(name, header, tuples);
    projectedRelation->FilterColumns(indexList);
    return projectedRelation;
}

std::vector<int> Relation::GetRelatedIndices(Predicate headPredicate) {
    std::vector<int> indexList;
    for (const auto &parameter: Header(headPredicate.GetParameters()).GetParameters()) {
        indexList.push_back(header.GetIndexOfParameter(parameter));
    }
    return indexList;
}

Relation *Relation::Rename(const std::string &id, std::string value) {
    auto *renamedRelation = new Relation(name, header, tuples);
    renamedRelation->UpdateHeader(id, std::move(value));
    return renamedRelation;
}

Relation *Relation::Rename(const int &index, const std::string &value) {
    auto *renamedRelation = new Relation(name, header, tuples);
    renamedRelation->UpdateHeader(index, value);
    return renamedRelation;
}

void Relation::UpdateHeader(const std::string &id, std::string value) {
    header.ChangeParameter(id, std::move(value));
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

bool Relation::TupleIsJoinable(Tuple tuple1, Header header1, Tuple tuple2, Header header2, Header joinedHeader) {
    for (const auto &parameter: joinedHeader.GetCommonParameters()) {
        unsigned tuple1_idx = header1.GetIndexOfParameter(parameter);
        unsigned tuple2_idx = header2.GetIndexOfParameter(parameter);
        if (tuple1.GetValueAtIndex(tuple1_idx) != tuple2.GetValueAtIndex(tuple2_idx)) {
            return false;
        }
    }
    return true;
}

Relation *Relation::NaturalJoin(Relation *other) {
    Header joinedHeader = header.NaturalJoin(other->GetHeader());
    auto *joinedRelation = new Relation(joinedHeader);
    for (auto tuple: tuples) {
        for (const Tuple &otherTuple: other->GetTuples()) {
            if (this->TupleIsJoinable(tuple, this->header, otherTuple, other->GetHeader(), joinedHeader)) {
                Tuple joinedTuple = tuple.NaturalJoin(this->header, otherTuple, other->GetHeader(), joinedHeader);
                joinedRelation->AddTuple(joinedTuple);
            }
        }
    }
    return joinedRelation;
}

Header Relation::GetHeader() const {
    return header;
}

bool Relation::Union(Relation *pRelation) {
    bool hasNewTuples = false;
    for (const auto &tuple: pRelation->GetTuples()) {
        if (this->AddTuple(tuple)) {
            hasNewTuples = true;
        }
    }
    return hasNewTuples;
}
