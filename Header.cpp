//
// Created by Kaleb Smith on 10/23/21.
//

#include <iostream>
#include <algorithm>
#include <utility>
#include "Header.h"

Header::Header() = default;

Header::Header(std::vector<Parameter> parametersList) {
    for (auto &parameter: parametersList) {
        parameters.push_back(parameter.GetValue());
    }
}

void Header::ChangeParameter(const std::string &id, std::string value) {
    int index = GetIndexOfParameter(id);
    parameters.at(index) = std::move(value);
}

void Header::ChangeParameter(const int &index, std::string value) {
    parameters.at(index) = std::move(value);
}

std::string Header::ToLowerCase(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

int Header::GetIndexOfParameter(const std::string &id) {
    for (long unsigned i = 0; i < parameters.size(); i++) {
        if (ToLowerCase(parameters.at(i)) == ToLowerCase(id)) {
            return (int) i;
        }
    }
    return -1;
}

bool Header::IsUniqueParameter(const std::vector<std::string>& parametersList, const std::string& id) {
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

Header Header::NaturalJoin (const Header& otherHeader) {
    Header joinedHeader = Header();
    for (auto &parameter: parameters) {
        joinedHeader.AddParameter(parameter);
    }
    for (auto &parameter: otherHeader.parameters) {
        if (IsUniqueParameter(joinedHeader.GetParameters(), parameter)) {
            joinedHeader.AddParameter(parameter);
        } else {
            joinedHeader.AddCommonParameter(parameter);
        }
    }
    return joinedHeader;
}

void Header::AddParameter(const std::string& parameter) {
    parameters.push_back(parameter);
}

void Header::AddCommonParameter(const std::string& parameter) {
    this->commonParameters.push_back(parameter);
}

std::vector<std::string> Header::GetCommonParameters() {
    return commonParameters;
}

bool Header::DoesContainParameter(const std::string& parameter) {
    for (auto &param: parameters) {
        if (param == parameter) {
            return true;
        }
    }
    return false;
}