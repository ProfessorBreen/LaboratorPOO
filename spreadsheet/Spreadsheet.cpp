#include "HFiles/Spreadsheet.h"
#include "HFiles/Parser.h"

double Spreadsheet::evaluateExpression(const string &expression)
{
    Expression *expr = Parser::parse(expression);
    visited.clear();
    double result = expr->evaluate(*this);
    delete expr;
    return result;
}

void Spreadsheet::setCellExpression(const CellLocation &location, const string &input)
{
    if (spreadsheet.find(location) != spreadsheet.end())
    {
        Cell curCell = spreadsheet[location];
        curCell.setExpression(*this, input);

        curCell.recalculate(*this);
        spreadsheet[location] = curCell;
    }
    else
    {
        Cell newCell = Cell(location);
        spreadsheet[location] = newCell;
        newCell.setExpression(*this, input);

        newCell.recalculate(*this);
        spreadsheet[location] = newCell;
    }
}

double Spreadsheet::getCellValue(const CellLocation &location)
{
    return getOrCreate(location).getValue();
}

void Spreadsheet::addDependency(const CellLocation &dependent, const CellLocation &dependency)
{
    Cell cell = getOrCreate(dependency);
    cell.addDependent(dependent);
}

void Spreadsheet::removeDependency(const CellLocation &dependent, const CellLocation &dependency)
{
    Cell cell = getOrCreate(dependency);
    cell.removeDependent(dependent);
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

void Spreadsheet::deallocateCells()
{
    for (auto &it : spreadsheet)
        it.second.destroyCell();
    spreadsheet.clear();
}
