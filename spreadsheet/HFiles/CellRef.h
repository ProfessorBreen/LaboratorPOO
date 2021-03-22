#pragma once

#include "Spreadsheet.h"
#include <set>

using namespace std;

class CellRef : public Expression
{
private:
    CellLocation cl;

public:
    explicit CellRef(CellLocation cl);

    double evaluate(Spreadsheet &context);

    void findCellReferences(set<CellLocation> dependencies);

    friend ostream &operator<<(std::ostream &strm, const CellRef &cellRef);
};

