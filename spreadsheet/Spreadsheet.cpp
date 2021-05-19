#include "HFiles/Spreadsheet.h"
#include "HFiles/Parser.h"

double Spreadsheet::evaluateExpression(const string &expression)
{
    Expression *expr = Parser::parse(expression);
    visited.clear();
    return expr->evaluate(*this);
}

void Spreadsheet::setCellExpression(const CellLocation &location, const string &input)
{
    if (spreadsheet.find(location) != spreadsheet.end())
        initCycleSearch(location);
    set<CellLocation> vis;

    if (spreadsheet.find(location) != spreadsheet.end())
    {
        Cell curCell = spreadsheet[location];
        curCell.setExpression(*this, input);

        if (hasCycleFrom(location))
            curCell.setExpression(*this, "0.0");

        recalculate(location);
        curCell.recalculate(*this);
        spreadsheet[location] = curCell;
    }
    else
    {
        Cell newCell = Cell(location);
        spreadsheet[location] = newCell;
        newCell.setExpression(*this, input);

        if (hasCycleFrom(location))
            newCell.setExpression(*this, "0.0");
        recalculate(location);
        newCell.recalculate(*this);
        spreadsheet[location] = newCell;
    }
}

double Spreadsheet::getCellValue(const CellLocation &location)
{
    return getOrCreate(location).getValue();
}

string Spreadsheet::getCellExpression(const CellLocation &location)
{
    return getOrCreate(location).getExpression();
}

string Spreadsheet::getCellDisplay(const CellLocation &location)
{
    return getOrCreate(location).toString();
}

void Spreadsheet::addDependency(CellLocation dependent, const CellLocation &dependency)
{
    Cell cell = getOrCreate(dependency);
    cell.addDependent(std::move(dependent));
}

void Spreadsheet::removeDependency(CellLocation dependent, const CellLocation &dependency)
{
    Cell cell = getOrCreate(dependency);
    cell.removeDependent(std::move(dependent));
}

void Spreadsheet::recalculate(const CellLocation &location)
{
    getOrCreate(location).recalculate(*this);
}

void Spreadsheet::findCellReferences(const CellLocation &subject, set<CellLocation> target)
{
    if (spreadsheet.find(subject) == spreadsheet.end())
        return;

    getOrCreate(subject).findCellReferences(std::move(target));
}

Cell Spreadsheet::getOrCreate(const CellLocation &cellLocation)
{
    if (spreadsheet.find(cellLocation) != spreadsheet.end())
        return spreadsheet[cellLocation];

    Cell newCell = Cell(CellLocation(cellLocation));
    spreadsheet[cellLocation] = newCell;
    return newCell;
}

bool Spreadsheet::initCycleSearch(const CellLocation &location)
{
    visited.clear();
    return hasCycleFrom(location);
}

bool Spreadsheet::hasCycleFrom(const CellLocation &start)
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