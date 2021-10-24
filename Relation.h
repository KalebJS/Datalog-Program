//
// Created by Kaleb Smith on 10/23/21.
//

//A relation has a name, a header, and a set of tuples
//Relations are used as operands in relational operations such as select, project, and rename.

#ifndef DATALOG_RELATION_H
#define DATALOG_RELATION_H

#include <set>
#include "Tuple.h"

class Relation {
private:
    std::set <Tuple> tuples;
public:
    Relation Select(Relation relation);

    Relation Project(Relation relation);

    Relation Rename(Relation relation);
};


#endif //DATALOG_RELATION_H
