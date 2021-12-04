//
// Created by Kaleb Smith on 10/23/21.
//

//A tuple is a list of attribute values.

#ifndef DATALOG_TUPLE_H
#define DATALOG_TUPLE_H


#include <vector>
#include <string>
#include "Parameter.h"
#include "Header.h"

class Tuple {
private:
    Tuple(const std::vector<std::string> &parameters);

    std::vector<std::string> values;
public:
    explicit Tuple(std::vector<Parameter> parameters);

    std::vector<std::string> GetValues() { return values; }

    bool operator<(const Tuple &rhs) const;

    bool operator>(const Tuple &rhs) const;

    bool operator<=(const Tuple &rhs) const;

    bool operator>=(const Tuple &rhs) const;

    bool ContainsValueAtIndex(unsigned index, const std::string &value);

    void Project(const std::vector<int> &indexList);

    std::string GetValueAtIndex(unsigned index);

    std::string ToString();

    Tuple NaturalJoin(Header header, Tuple otherTuple, Header otherHeader, Header joinedHeader);
};


#endif //DATALOG_TUPLE_H
