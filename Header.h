//
// Created by Kaleb Smith on 10/23/21.
//

//A header is a list of attribute names.

#ifndef DATALOG_HEADER_H
#define DATALOG_HEADER_H


#include <vector>
#include <string>
#include "Parameter.h"

class Header {
private:
    std::vector<std::string> parameters;
public:
    Header();

    explicit Header(std::vector<Parameter> parametersList);

    std::vector<std::string> GetParameters() { return parameters; }

    void ChangeParameter(const std::string &id, std::string value);

    int GetIndexOfParameter(const std::string &id);

    std::vector<int> Project(const std::vector<std::string>& idList);

    std::string ToString();

    void ChangeParameter(const int &index, std::string value);

    std::vector<int> Project(const std::vector<int> &indexList);

    bool IsUniqueParameter(std::vector<std::string> parametersList, std::string id);
};


#endif //DATALOG_HEADER_H
