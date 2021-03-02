#include "../common/api/Expression.cpp"
#include "../common/lexer/Token.cpp"
#include <cmath>
#include <set>

using namespace std;

class Number : public Expression
{
private:
    double value;

public:
    explicit Number(double value)
    {
        this->value = value;
    }

    double evaluate(EvaluationContext context) override
    {
        return value;
    }

    void findCellReferences(set<CellLocation> dependencies) override
    {
    }

    friend ostream &operator<<(std::ostream &strm, const Number &number)
    {
        strm << to_string(number.value);
        return strm;
    }
};

