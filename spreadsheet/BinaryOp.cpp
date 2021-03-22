#include "HFiles/BinaryOp.h"

double BinaryOp::evaluate(Spreadsheet &context)
{
    double expr1 = leftOperand->evaluate(context);
    double expr2 = rightOperand->evaluate(context);
    if (op == PLUS)
        return expr1 + expr2;
    else if (op == MINUS)
        return expr1 - expr2;
    else if (op == STAR)
        return expr1 * expr2;
    else if (op == SLASH)
        return expr1 / expr2;
    else if (op == CARET)
        return pow(expr1, expr2);
    return 0.0;
}

void BinaryOp::findCellReferences(set<CellLocation> dependencies)
{
    leftOperand->findCellReferences(dependencies);
    rightOperand->findCellReferences(dependencies);
}

ostream &operator<<(ostream &strm, const BinaryOp &binaryOp)
{
    strm << "(" << binaryOp.leftOperand << kindToString(binaryOp.op) << binaryOp.rightOperand << ")";
    return strm;
}
