//
// Created by Kaleb Smith on 10/23/21.
//

#include <iostream>
#include <algorithm>
#include "Header.h"

Header::Header() = default;

Header::Header(std::vector<Parameter> parametersList) {
    for (auto &parameter: parametersList) {
        parameters.push_back(parameter.GetValue());
    }
}

void Header::ChangeParameter(const std::string &id, std::string value) {
    int index = GetIndexOfParameter(id);
    parameters.at(index) = value;
}

void Header::ChangeParameter(const int &index, std::string value) {
    parameters.at(index) = value;
}

int Header::GetIndexOfParameter(const std::string &id) {
    for (long unsigned int i = 0; i < parameters.size(); i++) {
        if (parameters.at(i) == id) {
            return (int) i;
        }
    }
    return -1;
}

bool Header::IsUniqueParameter(std::vector<std::string> parametersList, std::string id) {
    for (auto &parameter: parametersList) {
        if (parameter == id) {
            return false;
        }
    }
    return true;
}

std::vector<int> Header::Project(const std::vector<std::string> &idList) {
    std::vector<int> idIndexList;
    std::vector<std::string> projectedParameters;
    for (auto &id: idList) {
        int idIndex = GetIndexOfParameter(id);
        idIndexList.push_back(idIndex);
    }
    std::sort(idIndexList.begin(), idIndexList.end());
    projectedParameters.reserve(idIndexList.size());
    for (auto &index: idIndexList) {
        projectedParameters.push_back(parameters.at(index));
    }
    parameters = projectedParameters;
    return idIndexList;
}

std::vector<int> Header::Project(const std::vector<int> &indexList) {
    std::vector<std::string> projectedParameters;
    projectedParameters.reserve(indexList.size());
    std::vector<int> projectedIndexList;
    for (auto &index: indexList) {
        if (IsUniqueParameter(projectedParameters, parameters.at(index))) {
            projectedParameters.push_back(parameters.at(index));
            projectedIndexList.push_back(index);
        }
    }
    parameters = projectedParameters;
    return projectedIndexList;
}

std::string Header::ToString() {
    std::string header = "(";
    for (long unsigned int i = 0; i < parameters.size(); i++) {
        header += parameters.at(i);
        if (i != parameters.size() - 1) {
            header += ",";
        }
    }
    header += ")";
    return header;
}

