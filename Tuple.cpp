//
// Created by Kaleb Smith on 10/23/21.
//

#include <iostream>
#include "Tuple.h"

Tuple::Tuple(std::vector<Parameter> parameters) {
    for (auto &parameter: parameters) {
        values.push_back(parameter.GetValue());
    }
}

Tuple::Tuple(const std::vector<std::string>& parameters) {
    for (auto &parameter: parameters) {
        values.push_back(parameter);
    }
}

bool Tuple::ContainsValueAtIndex(unsigned index, const std::string &value) {
    if (values.at(index) == value) {
        return true;
    } else {
        return false;
    }
}

bool Tuple::operator<(const Tuple &rhs) const {
    return values < rhs.values;
}

bool Tuple::operator>(const Tuple &rhs) const {
    return rhs < *this;
}

bool Tuple::operator<=(const Tuple &rhs) const {
    return !(rhs < *this);
}

bool Tuple::operator>=(const Tuple &rhs) const {
    return !(*this < rhs);
}

void Tuple::Project(const std::vector<int> &indexList) {
    std::vector<std::string> projectedValues;
    projectedValues.reserve(indexList.size());
    for (int index: indexList) {
        projectedValues.push_back(values.at(index));
    }
    values = projectedValues;
}

std::string Tuple::ToString() {
    std::string tupleString = "( ";
    for (auto &value: values) {
        tupleString += value + " ";
    }
    tupleString += ")";
    return tupleString;
}

std::string Tuple::GetValueAtIndex(unsigned int index) {
    return values.at(index);
}

Tuple Tuple::NaturalJoin(Header header, Tuple otherTuple, Header otherHeader, Header joinedHeader) {
    std::vector <std::string> joinedValues;
    for (const auto& parameter : joinedHeader.GetParameters()) {
        if (header.DoesContainParameter(parameter)) {
            unsigned index = header.GetIndexOfParameter(parameter);
            joinedValues.push_back(this->GetValueAtIndex(index));
        } else if (otherHeader.DoesContainParameter(parameter)) {
            unsigned index = otherHeader.GetIndexOfParameter(parameter);
            joinedValues.push_back(otherTuple.GetValueAtIndex(index));
        }
    }
    return Tuple(joinedValues);
}