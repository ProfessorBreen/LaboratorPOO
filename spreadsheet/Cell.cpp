#include <utility>

#include "Parser.cpp"

using namespace std;

class Cell
{
private:
    Spreadsheet spreadsheet;
    CellLocation location;
    double value;
    optional<shared_ptr<Expression>> expr;
    set<CellLocation> dependents;

public:
    Cell(Spreadsheet spreadsheet, CellLocation location)
    {
        value = 0;
        expr = nullopt;
        dependents.clear();
        this->spreadsheet = move(spreadsheet);
        this->location = location;
    }

    double getValue()
    {
        return value;
    }

    string getExpression()
    {
        if (expr.has_value())
            return reinterpret_cast<basic_string<char, char_traits<char>, allocator<char>> &&>(expr.value());
        return "";
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
