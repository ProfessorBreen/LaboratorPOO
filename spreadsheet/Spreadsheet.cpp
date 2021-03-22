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