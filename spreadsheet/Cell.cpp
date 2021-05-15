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

Cell::Cell(CellLocation location)
{
    value = 0;
    expr = nullopt;
    dependents.clear();
    this->location = std::move(location);
}

void Cell::setValue(double val)
{
    this->value = val;
}

double Cell::getValue() const
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
    return nullptr;
}

set<CellLocation> Cell::getDependents()
{
    return dependents;
}

void Cell::setExpression(Spreadsheet &spreadsheet, const string &input)
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

string Cell::toString()
{
    if (expr.has_value())
        return to_string(value);
    return "";
}

void Cell::addDependent(CellLocation location)
{
    dependents.insert(location);
}

void Cell::removeDependent(CellLocation location)
{
    dependents.erase(location);
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