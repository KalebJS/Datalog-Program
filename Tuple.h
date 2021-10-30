//
// Created by Kaleb Smith on 10/23/21.
//

//A tuple is a list of attribute values.

#ifndef DATALOG_TUPLE_H
#define DATALOG_TUPLE_H


#include <vector>
#include <string>
#include "Parameter.h"

class Tuple {
private:
    std::vector<std::string> values;
public:
    Tuple(std::vector<Parameter> parameters);

    std::vector<std::string> GetValues() { return values; }

    bool operator<(const Tuple &rhs) const;

    bool operator>(const Tuple &rhs) const;

    bool operator<=(const Tuple &rhs) const;

    bool operator>=(const Tuple &rhs) const;

    bool ContainsValueAtIndex(int index, const std::string &value);

    void Project(const std::vector<int>& indexList);

    std::string GetValueAtIndex(int index) { return values.at(index); }

    std::string ToString();
};


#endif //DATALOG_TUPLE_H
