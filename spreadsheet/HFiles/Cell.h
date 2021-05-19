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

    explicit Cell(const CellLocation& location);

    [[nodiscard]] double getValue() const;

    void setExpression(Spreadsheet &spreadsheet, const string& input);

    void addDependent(const CellLocation& loc);

    void removeDependent(const CellLocation& loc);

    void findCellReferences(set<CellLocation> target);

    void recalculate(Spreadsheet &spreadsheet);
};
