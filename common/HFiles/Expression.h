#pragma once

#include "CellLocation.h"
#include <set>

using namespace std;

class Spreadsheet;

class Expression
{
public:
    virtual double evaluate(Spreadsheet &context) = 0;

    virtual void findCellReferences(set<CellLocation> dependencies) = 0;

    virtual ~Expression()
    {
    }
};