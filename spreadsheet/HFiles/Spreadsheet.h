#pragma once

#include "../Cell.cpp"
#include "CycleDetector.h"
#include <map>

using namespace std;

class Spreadsheet
{
private:
    map<CellLocation, Cell> spreadsheet;
public:
    Spreadsheet()
    = default;

    static double evaluateExpression(const string &expression)
    {
        Expression expr = Parser::parse(expression);
        return expr.evaluate(*this);
    }

    void setCellExpression(const CellLocation &location, const string &input)
    {
        CycleDetector cycleDetector = CycleDetector(*this);
        set<CellLocation> vis;

        if (spreadsheet.find(location) != spreadsheet.end())
        {
            Cell curCell = spreadsheet[location];
            curCell.setExpression(input);

            if (cycleDetector.hasCycleFrom(location))
                curCell.setExpression("0.0");

            recalculate(location);
            spreadsheet[location] = curCell;
        }
        else
        {
            Cell newCell = Cell(*this, location);
            spreadsheet[location] = newCell;
            newCell.setExpression(input);

            if (cycleDetector.hasCycleFrom(location))
                newCell.setExpression("0.0");

            recalculate(location);
            spreadsheet[location] = newCell;
        }
    }

    double getCellValue(CellLocation location);

    string getCellExpression(CellLocation location);

    string getCellDisplay(CellLocation location);

    void addDependency(CellLocation dependent, CellLocation dependency);

    void removeDependency(CellLocation dependent, CellLocation dependency);

    void recalculate(CellLocation location);

    void findCellReferences(CellLocation subject, set<CellLocation> target);

    Cell getOrCreate(CellLocation cellLocation)
    {
        if (spreadsheet.find(cellLocation) != spreadsheet.end())
            return spreadsheet[cellLocation];
        Cell newCell = Cell(*this,CellLocation("a1"));
        spreadsheet[cellLocation] = static_cast<Cell &&>(newCell);
        return newCell;
    }
};
