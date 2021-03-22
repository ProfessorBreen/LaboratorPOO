#include "../common/HFiles/Token.h"
#include "../common/HFiles/Expression.h"
#include "HFiles/Number.h"
#include "HFiles/CellRef.h"
#include "HFiles/BinaryOp.h"
#include <stack>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

class Parser
{
public:
    static Expression *parse(const string &input)
    {
        vector<Token> ls = tokenize(input);
        stack<Expression *> operandSt;
        stack<Kind> operatorSt;
        for (const Token &token : ls)
        {
            if (token.kind == RANGLE || token.kind == LANGLE)
                throw invalid_argument("WRONG Token");
            if (token.kind == NUMBER)
            {
                Number nr = Number(token.numberValue);
                operandSt.push(&nr);
            }
            else if (token.kind == CELL_LOCATION)
            {
                CellRef cellRef = CellRef(token.cellLocationValue.value());
                operandSt.push(&cellRef);
            }
            else
            {
                if (!operatorSt.empty())
                {
                    Kind topOperator = operatorSt.top();
                    while (hasHigherPriority(topOperator, token.kind))
                    {
                        Expression *exp1 = operandSt.top();
                        operandSt.pop();
                        Expression *exp2 = operandSt.top();
                        operandSt.pop();
                        BinaryOp binOP = BinaryOp(exp2, exp1, topOperator);
                        operandSt.push(&binOP);

                        operatorSt.pop();
                        if (operatorSt.empty())
                            break;
                        topOperator = operatorSt.top();
                    }
                }
                operatorSt.push(token.kind);
            }
        }
        while (!operatorSt.empty())
        {
            Expression *exp1 = operandSt.top();
            operandSt.pop();
            Expression *exp2 = operandSt.top();
            operandSt.pop();

            Kind topOperator = operatorSt.top();
            operatorSt.pop();
            BinaryOp binOP = BinaryOp(exp2, exp1, topOperator);
            operandSt.push(&binOP);
        }
        return operandSt.top();
    }

    static bool hasHigherPriority(Kind kind, Kind other)
    {
        if (kind == PLUS || kind == MINUS)
            return other == PLUS || other == MINUS;
        return other != CARET;
    }


};