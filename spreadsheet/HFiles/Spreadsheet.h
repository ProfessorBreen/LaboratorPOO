#pragma once

#include "../Cell.cpp"
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

    double evaluateExpression(const string &expression)
    {
        Expression *expr = Parser::parse(expression);
        visited.clear();
        return expr->evaluate(*this);
    }

    void setCellExpression(const CellLocation &location, const string &input);

    double getCellValue(CellLocation location);

    string getCellExpression(CellLocation location);

    string getCellDisplay(CellLocation location);

    void addDependency(CellLocation dependent, CellLocation dependency);

    void removeDependency(CellLocation dependent, CellLocation dependency);

    void recalculate(CellLocation location);

    void findCellReferences(CellLocation subject, set<CellLocation> target);

    Cell getOrCreate(CellLocation cellLocation);

    bool initCycleSearch(CellLocation location);

    bool hasCycleFrom(CellLocation start);
};
