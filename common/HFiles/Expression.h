#pragma once

#include "../../spreadsheet/HFiles/Spreadsheet.h"
#include <set>
#include <memory>

using namespace std;

class Expression
{
public:
    virtual double evaluate(Spreadsheet &context) = 0;

    virtual void findCellReferences(set<CellLocation> dependencies) = 0;
};