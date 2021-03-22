#pragma once

#include <cmath>
#include <set>
#include <variant>
#include "Spreadsheet.h"

using namespace std;

class BinaryOp : public Expression
{
private:
    Expression *leftOperand;
    Expression *rightOperand;
    Kind op;

public:
    BinaryOp(Expression *leftOperand, Expression *rightOperand, Kind op)
    {
        this->leftOperand = leftOperand;
        this->rightOperand = rightOperand;
        this->op = op;
    }

    double evaluate(Spreadsheet &context);

    void findCellReferences(set<CellLocation> dependencies) override;

    friend ostream &operator<<(std::ostream &strm, const BinaryOp &binaryOp);
};

