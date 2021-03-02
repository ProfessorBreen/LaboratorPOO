#include "../common/api/Expression.cpp"
#include "../common/lexer/Token.cpp"
#include <set>

using namespace std;

class CellRef : public Expression
{
private:
    CellLocation cl;

public:
    explicit CellRef(CellLocation cl) : cl(cl)
    {
        this->cl = cl;
    }

    double evaluate(EvaluationContext context) override
    {
        return context.getCellValue(cl);
    }

    void findCellReferences(set<CellLocation> dependencies) override
    {
        dependencies.insert(cl);
    }

    friend ostream &operator<<(std::ostream &strm, const CellRef &cellRef)
    {
        strm << cellRef.cl;
        return strm;
    }
};

