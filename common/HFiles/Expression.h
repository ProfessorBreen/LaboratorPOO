#pragma once

#include "CellLocation.h"
#include <set>
#include <memory>

using namespace std;

class Spreadsheet;

class Expression{
public:
    virtual double evaluate(Spreadsheet &context) = 0;

    virtual void findCellReferences(set<CellLocation> dependencies) = 0;
};