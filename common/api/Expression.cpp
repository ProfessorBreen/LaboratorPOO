#include "EvaluationContext.cpp"
#include <set>

using namespace std;

class Expression
{
public:
    virtual double evaluate(EvaluationContext context);

    virtual void findCellReferences(set<CellLocation> dependencies);
};