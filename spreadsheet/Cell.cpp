#include "HFiles/Cell.h"
#include "HFiles/Parser.h"
#include "HFiles/Spreadsheet.h"

void Cell::addDependencies(Spreadsheet &spreadsheet)
{
    if (expr.has_value())
    {
        set<CellLocation> dependencies;
        expr.value()->findCellReferences(dependencies);
        for (const CellLocation &dependency : dependencies)
            spreadsheet.addDependency(location, dependency);
    }
}

void Cell::removeDependencies(Spreadsheet &spreadsheet)
{
    if (expr.has_value())
    {
        set<CellLocation> dependencies;
        expr.value()->findCellReferences(dependencies);
        for (const CellLocation &dependency : dependencies)
            spreadsheet.removeDependency(location, dependency);
    }
}

Cell::Cell(const CellLocation &location)
{
    value = 0;
    expr = nullopt;
    dependents.clear();
    this->location = location;
}

double Cell::getValue() const
{
    return value;
}

void Cell::setExpression(Spreadsheet &spreadsheet, const string &input)
{
    removeDependencies(spreadsheet);
    expr.reset();
    if (input.empty())
        expr = nullopt;
    else
    {
        expr = Parser::parse(input);
        addDependencies(spreadsheet);
    }
}

void Cell::addDependent(const CellLocation &loc)
{
    dependents.insert(loc);
}

void Cell::removeDependent(const CellLocation &loc)
{
    dependents.erase(loc);
}

void Cell::findCellReferences(set<CellLocation> target)
{
    if (expr.has_value())
    {
        set<CellLocation> dependencies;
        expr.value()->findCellReferences(dependencies);
        for (const auto &i : dependencies)
            target.insert(i);
    }
}

void Cell::recalculate(Spreadsheet &spreadsheet)
{
    if (!expr.has_value())
        value = 0.0;
    else
        value = expr.value()->evaluate(spreadsheet);
    for (const CellLocation &dependent : dependents)
        spreadsheet.recalculate(dependent);
}

Cell::~Cell()
{
    expr.reset();
}

void Cell::destroyCell()
{
    expr.reset();
}
