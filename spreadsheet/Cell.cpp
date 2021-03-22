#include <utility>

#include "Parser.cpp"

using namespace std;

class Cell
{
private:
    CellLocation location;
    double value;
    optional<Expression *> expr;
    set<CellLocation> dependents;

public:
    Cell(CellLocation location)
    {
        value = 0;
        expr = nullopt;
        dependents.clear();
        this->location = location;
    }

    double getValue()
    {
        return value;
    }

    void setValue(double value)
    {
        this->value = value;
    }

    string getExpression()
    {
        if (expr.has_value())
            return reinterpret_cast<basic_string<char, char_traits<char>, allocator<char>> &&>(expr.value());
        return "";
    }

    Expression *getPureExpression()
    {
        if (expr.has_value())
            return expr.value();
        return NULL;
    }

    set<CellLocation> getDependents()
    {
        return dependents;
    }

    void setExpression(Spreadsheet spreadsheet, string input)
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

private:
    void removeDependencies(Spreadsheet spreadsheet)
    {
        if (expr.has_value())
        {
            set<CellLocation> dependencies;
            expr.value()->findCellReferences(dependencies);
            for (CellLocation dependency : dependencies)
                spreadsheet.removeDependency(location, dependency);
        }
    }

    void addDependencies(Spreadsheet spreadsheet)
    {
        if (expr.has_value())
        {
            set<CellLocation> dependencies;
            expr.value()->findCellReferences(dependencies);
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
            expr.value()->findCellReferences(dependencies);
            for (auto i : dependencies)
                target.insert(i);
        }
    }

    void recalculate(Spreadsheet spreadsheet)
    {
        if (!expr.has_value())
            value = 0.0;
        else
            value = expr.value()->evaluate(spreadsheet);
        for (CellLocation dependent : dependents)
            spreadsheet.recalculate(dependent);
    }
};
