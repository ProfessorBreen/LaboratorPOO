#pragma once
#include "../../common/HFiles/Expression.h"
#include <cmath>
#include <set>
#include <memory>

using namespace std;

class BinaryOp : public Expression
{
private:
    shared_ptr<Expression> leftOperand;
    shared_ptr<Expression> rightOperand;
    Kind op;

public:
    BinaryOp(const Expression &leftOperand, const Expression &rightOperand, Kind op);

    [[nodiscard]] shared_ptr<Expression> clone() const override
    {
        return make_shared<BinaryOp>(*this);
    }

    virtual double evaluate(Spreadsheet &context) override;

    void findCellReferences(set<CellLocation> dependencies) override;

    friend ostream &operator<<(std::ostream &strm, const BinaryOp &binaryOp);
};

