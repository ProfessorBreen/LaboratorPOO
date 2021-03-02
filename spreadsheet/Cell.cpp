#include <utility>

#include "Parser.cpp"
#include "../common/api/BasicSpreadsheet.cpp"

using namespace std;

class Cell
{
private:
    BasicSpreadsheet spreadsheet;
    CellLocation location;
    double value;
    optional<Expression> expr;
    set<CellLocation> dependents;

public:
    Cell(BasicSpreadsheet spreadsheet, CellLocation location) : location(location)
    {
        value = 0;
        expr = nullopt;
        dependents.clear();
        this->spreadsheet = move(spreadsheet);
        this->location = location;
    }

public:
    double getValue()
    {
        return value;
    }

    string getExpression()
    {
        if (expr.has_value())
            return "";
        return expr.value();
    }

    void setExpression(string input)
    {
        removeDependencies();
        if (input.empty())
            expr = nullopt;
        else
        {
            expr = Parser::parse(input);
            addDependencies();
        }
    }

private:
    void removeDependencies()
    {
        if (expr.has_value())
        {
            set<CellLocation> dependencies;
            expr.value().findCellReferences(dependencies);
            for (CellLocation dependency : dependencies)
                spreadsheet.removeDependency(location, dependency);
        }
    }

    void addDependencies()
    {
        if (expr.has_value())
        {
            set<CellLocation> dependencies;
            expr.value().findCellReferences(dependencies);
            for (CellLocation dependency : dependencies)
                spreadsheet.addDependency(location, dependency);
        }
    }

public:

    string toString()
    {
        if (expr.has_value())
            return to_string(value);
        return "";
    }

    void addDependent(CellLocation location)
    {
        dependents.insert(location);
    }

    void removeDependent(CellLocation location)
    {
        dependents.erase(location);
    }

    void findCellReferences(set<CellLocation> target)
    {
        if (expr.has_value())
        {
            set<CellLocation> dependencies;
            expr.value().findCellReferences(dependencies);
            for (auto i : dependencies)
                target.insert(i);
        }
    }

    void recalculate()
    {
        if (!expr.has_value())
            value = 0.0;
        else
            value = expr.value().evaluate(spreadsheet);
        for (CellLocation dependent : dependents)
            spreadsheet.recalculate(dependent);
    }
};
