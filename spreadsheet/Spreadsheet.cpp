#include "HFiles/Spreadsheet.h"

#include <utility>

void Spreadsheet::findCellReferences(CellLocation subject, set<CellLocation> target)
{
    getOrCreate(std::move(subject)).findCellReferences(std::move(target));
}

void Spreadsheet::recalculate(CellLocation location)
{
    getOrCreate(std::move(location)).recalculate();
}

void Spreadsheet::removeDependency(CellLocation dependent, CellLocation dependency)
{
    Cell cell = getOrCreate(std::move(dependency));
    cell.removeDependent(std::move(dependent));
}

void Spreadsheet::addDependency(CellLocation dependent, CellLocation dependency)
{
    Cell cell = getOrCreate(std::move(dependency));
    cell.addDependent(std::move(dependent));
}

string Spreadsheet::getCellDisplay(CellLocation location)
{
    return getOrCreate(std::move(location)).toString();
}

string Spreadsheet::getCellExpression(CellLocation location)
{
    return getOrCreate(std::move(location)).getExpression();
}

double Spreadsheet::getCellValue(CellLocation location)
{
    return getOrCreate(std::move(location)).getValue();
}

bool Spreadsheet::hasCycleFrom(CellLocation start)
{
    visited.insert(start);
    set<CellLocation> nextCells;
    findCellReferences(start, nextCells);
    for (const CellLocation &cellLocation : nextCells)
    {
        if (visited.find(cellLocation) != visited.end())
            return true;
        if (hasCycleFrom(cellLocation))
            return true;
    }
    visited.erase(start);
    return false;
}

bool Spreadsheet::initCycleSearch(CellLocation location)
{
    visited.clear();
    return hasCycleFrom(location);
}

void Spreadsheet::setCellExpression(const CellLocation &location, const string &input)
{
    initCycleSearch(location);
    set<CellLocation> vis;

    if (spreadsheet.find(location) != spreadsheet.end())
    {
        Cell curCell = spreadsheet[location];
        curCell.setExpression(input);

        if (hasCycleFrom(location))
            curCell.setExpression("0.0");

        recalculate(location);
        spreadsheet[location] = curCell;
    }
    else
    {
        Cell newCell = Cell(*this, location);
        spreadsheet[location] = static_cast<Cell &&>(newCell);
        newCell.setExpression(input);

        if (hasCycleFrom(location))
            newCell.setExpression("0.0");

        recalculate(location);
        spreadsheet[location] = static_cast<Cell &&>(newCell);
    }
}

Cell Spreadsheet::getOrCreate(CellLocation cellLocation)
{
    if (spreadsheet.find(cellLocation) != spreadsheet.end())
        return spreadsheet[cellLocation];
    Cell newCell = Cell(*this, CellLocation("a1"));
    spreadsheet[cellLocation] = static_cast<Cell &&>(newCell);
    return newCell;
}
