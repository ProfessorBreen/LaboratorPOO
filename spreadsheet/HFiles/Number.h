#pragma once

#include "../../common/HFiles/Expression.h"
#include <set>

using namespace std;

class Number : public Expression
{
private:
    double value;

public:
    explicit Number(double value);

    double evaluate(Spreadsheet &context) override;

    void findCellReferences(set<CellLocation> dependencies) override;

    friend ostream &operator<<(std::ostream &strm, const Number &number);
};

