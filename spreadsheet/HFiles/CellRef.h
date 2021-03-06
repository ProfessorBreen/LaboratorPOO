#pragma once

#include "../../common/HFiles/Expression.h"
#include <set>

using namespace std;

class CellRef : public Expression
{
private:
    CellLocation cl;

public:
    explicit CellRef(const CellLocation &cl);

    CellRef(const CellRef &c);

    double evaluate(Spreadsheet &context) override;

    void findCellReferences(set<CellLocation> dependencies) override;

    friend ostream &operator<<(std::ostream &strm, const CellRef &cellRef);
};