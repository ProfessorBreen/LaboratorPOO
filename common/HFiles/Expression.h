#pragma once

#include "../../spreadsheet/HFiles/Spreadsheet.h"
#include <set>
#include <memory>

using namespace std;

class Expression
{
public:
    shared_ptr<Expression> clone() const;

    virtual double evaluate(Spreadsheet &context) =0;

    void findCellReferences(set<CellLocation> dependencies);
};