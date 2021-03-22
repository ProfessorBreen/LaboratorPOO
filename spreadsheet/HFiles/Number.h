#pragma once

#include "../../common/HFiles/Expression.h"
#include "Spreadsheet.h"
#include <set>

using namespace std;

class Number : public Expression
{
private:
    double value;

public:
    explicit Number(double value);

    [[nodiscard]] shared_ptr<Expression> clone() const override
    {
        return make_shared<Number>(*this);
    }

    double evaluate(Spreadsheet &context) override;

    void findCellReferences(set<CellLocation> dependencies) override;

    friend ostream &operator<<(std::ostream &strm, const Number &number);
};

