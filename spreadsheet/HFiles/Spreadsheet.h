#pragma once

#include "Cell.h"
#include <map>
#include <utility>

using namespace std;

class Spreadsheet
{
private:
    map<CellLocation, Cell> spreadsheet;
    set<CellLocation> visited;
public:
    Spreadsheet()
    = default;

    double evaluateExpression(const string &expression);

    void setCellExpression(const CellLocation &location, const string &input);

    double getCellValue(const CellLocation& location);

    void addDependency(const CellLocation& dependent, const CellLocation& dependency);

    void removeDependency(const CellLocation& dependent, const CellLocation& dependency);

    void recalculate(const CellLocation& location);

    void findCellReferences(const CellLocation& subject, set<CellLocation> target);

    Cell getOrCreate(const CellLocation& cellLocation);

    void deallocateCells();
};
