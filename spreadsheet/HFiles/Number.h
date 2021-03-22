#pragma once

#include "Spreadsheet.h"
#include <set>

using namespace std;

class Number : public Expression
{
private:
    double value;

public:
    Number(double value);

    double evaluate(Spreadsheet &context);

    void findCellReferences(set<CellLocation> dependencies);

    friend ostream &operator<<(std::ostream &strm, const Number &number);
};

