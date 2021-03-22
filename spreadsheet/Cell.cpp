#include "Cell.h"
#include "Parser.h"
#include "HFiles/Spreadsheet.h"
Cell::Cell(CellLocation location)
{
    value = 0;
    expr = nullopt;
    dependents.clear();
    this->location = location;
}

void Cell::setValue(double value)
{
    this->value = value;
}

double Cell::getValue()
{
    return value;
}

string Cell::getExpression()
{
    if (expr.has_value())
        return reinterpret_cast<basic_string<char, char_traits<char>, allocator<char>> &&>(expr.value());
    return "";
}

Expression *Cell::getPureExpression()
{
    if (expr.has_value())
        return expr.value();
    return NULL;
}

void Cell::setExpression(Spreadsheet &spreadsheet, string input)
{
    removeDependencies(spreadsheet);
    if (input.empty())
        expr = nullopt;
    else
    {
        expr = Parser::parse(input);
        addDependencies(spreadsheet);
    }
}

void Cell::removeDependencies(Spreadsheet &spreadsheet)
{
    if (expr.has_value())
    {
        set<CellLocation> dependencies;
        expr.value()->findCellReferences(dependencies);
        for (CellLocation dependency : dependencies)
            spreadsheet.removeDependency(location, dependency);
    }
}

void Cell::addDependencies(Spreadsheet &spreadsheet)
{
    if (expr.has_value())
    {
        set<CellLocation> dependencies;
        expr.value()->findCellReferences(dependencies);
        for (CellLocation dependency : dependencies)
            spreadsheet.addDependency(location, dependency);
    }
}

void Cell::addDependent(CellLocation location)
{
    dependents.insert(location);
}

string Cell::toString()
{
    if (expr.has_value())
        return to_string(value);
    return "";
}

void Cell::findCellReferences(set<CellLocation> target)
{
    if (expr.has_value())
    {
        set<CellLocation> dependencies;
        expr.value()->findCellReferences(dependencies);
        for (auto i : dependencies)
            target.insert(i);
    }
}

void Cell::recalculate(Spreadsheet spreadsheet)
{
    if (!expr.has_value())
        value = 0.0;
    else
        value = expr.value()->evaluate(spreadsheet);
    for (CellLocation dependent : dependents)
        spreadsheet.recalculate(dependent);
}

void Cell::removeDependent(CellLocation location)
{
    dependents.erase(location);
}

set<CellLocation> Cell::getDependents()
{
    return dependents;
}
