//
// Created by Kaleb Smith on 10/23/21.
//

//A relation has a name, a header, and a set of tuples
//Relations are used as operands in relational operations such as select, project, and rename.

#ifndef DATALOG_RELATION_H
#define DATALOG_RELATION_H

#include <set>
#include <string>
#include "Tuple.h"
#include "Header.h"
#include "Predicate.h"

class Relation {
private:
    std::set<Tuple> tuples;
    std::string name;
    Header header = Header();
    std::set<Tuple> newTuples;

    void UpdateHeader(const std::string &id, std::string value);

    void FilterTuples(int tupleIndex, const std::string &value);

    void FilterTuples(const std::vector<int> &tupleIndex);

    void FilterColumns(const std::vector<std::string> &idList);

    void FilterColumns(const std::vector<int> &indexList);

    Relation(std::string copiedName, Header copiedHeader, std::set<Tuple> copiedTuples);

    explicit Relation(Header header);

public:
    explicit Relation(Predicate scheme);

    ~Relation();

    void AddTuple(Predicate fact);

    std::string GetName() { return name; }

    Header GetHeader() { return this->header; }

    std::set<Tuple> GetTuples() { return tuples; }

    std::set<Tuple> GetNewTuples() { return newTuples; }

    Relation Select(int tupleIndex, const std::string &value);

    Relation Select(const std::vector<int> &tupleIndexes);

    Relation Project(const std::vector<std::string> &idList);

    Relation Project(const std::vector<int> &indexList);

    Relation Rename(const std::string &id, std::string value);

    Relation Rename(const int &index, const std::string &value);

    std::string ToString();

    void UpdateHeader(const int &index, const std::string &value);

    static bool TupleIsJoinable(Tuple tuple1, Header header1, Tuple tuple2, Header header2, Header joinedHeader);

    bool AddTuple(const Tuple& tuple);

    Header GetHeader() const;

    std::vector<int> GetRelatedIndices(Predicate headPredicate);

    Relation NaturalJoin(Relation other);

    bool Union(Relation pRelation);

    void ClearNewTuples();
};


#endif //DATALOG_RELATION_H
