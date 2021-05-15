#pragma once

#include "../../common/HFiles/CellLocation.h"
#include "../../common/HFiles/Expression.h"
#include <set>
#include <utility>

using namespace std;

class Cell
{
private:
    CellLocation location;
    double value{};
    optional<Expression *> expr;
    set<CellLocation> dependents;

    void removeDependencies(Spreadsheet &spreadsheet);

    void addDependencies(Spreadsheet &spreadsheet);

public:
    Cell()
    = default;

    explicit Cell(CellLocation location);

    [[nodiscard]] double getValue() const;

    void setValue(double value);

    string getExpression();

    Expression *getPureExpression();

    set<CellLocation> getDependents();

    void setExpression(Spreadsheet &spreadsheet, const string& input);

    string toString();

    void addDependent(CellLocation location);

    void removeDependent(CellLocation location);

    void findCellReferences(set<CellLocation> target);

    void recalculate(Spreadsheet &spreadsheet);
};
