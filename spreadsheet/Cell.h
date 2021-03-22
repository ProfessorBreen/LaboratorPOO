#pragma once

#include <utility>
#include "../common/HFiles/CellLocation.h"
#include "../common/HFiles/Expression.h"
#include <set>

using namespace std;

class Cell
{
private:
    CellLocation location;
    double value;
    optional<Expression *> expr;
    set<CellLocation> dependents;

public:
    Cell()
    {}

    Cell(CellLocation location);

    double getValue();

    void setValue(double value);

    string getExpression();

    Expression *getPureExpression();

    set<CellLocation> getDependents();

    void setExpression(Spreadsheet &spreadsheet, string input);

private:
    void removeDependencies(Spreadsheet &spreadsheet);

    void addDependencies(Spreadsheet &spreadsheet);

public:

    string toString();

    void addDependent(CellLocation location);

    void removeDependent(CellLocation location);

    void findCellReferences(set<CellLocation> target);

    void recalculate(Spreadsheet spreadsheet);
};
