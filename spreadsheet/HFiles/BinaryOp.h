#pragma once

#include "../../common/HFiles/Expression.h"
#include "Parser.h"
#include <cmath>
#include <set>

using namespace std;

class BinaryOp : public Expression
{
private:
    Expression *leftOperand;
    Expression *rightOperand;
    Kind op;

public:
    BinaryOp(Expression *leftOperand, Expression *rightOperand, Kind op);

    double evaluate(Spreadsheet &context) override;

    void findCellReferences(set<CellLocation> dependencies) override;

    friend ostream &operator<<(std::ostream &strm, const BinaryOp &binaryOp);

    ~BinaryOp();
};

