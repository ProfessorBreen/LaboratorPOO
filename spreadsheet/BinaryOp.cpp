#include "../common/api/Expression.cpp"
#include "../common/lexer/Token.cpp"
#include <cmath>
#include <set>
#include <utility>

using namespace std;

class BinaryOp : public Expression
{
private:
    Expression leftOperand;
    Expression rightOperand;
    Kind op;

public:
    BinaryOp(Expression leftOperand, Expression rightOperand, Kind op)
    {
        this->leftOperand = move(leftOperand);
        this->rightOperand = move(rightOperand);
        this->op = op;
    }

    double evaluate(EvaluationContext context) override
    {
        double expr1 = leftOperand.evaluate(context);
        double expr2 = rightOperand.evaluate(context);
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

    void findCellReferences(set<CellLocation> dependencies) override
    {
        leftOperand.findCellReferences(dependencies);
        rightOperand.findCellReferences(dependencies);
    }

    friend ostream &operator<<(std::ostream &strm, const BinaryOp &binaryOp)
    {
        strm << "(" << leftOperand << kindToString(binaryOp.op) << rightOperand << ")";
    }
};

