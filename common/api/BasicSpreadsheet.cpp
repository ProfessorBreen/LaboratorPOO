#include "EvaluationContext.cpp"
#include <string>
#include <set>

using namespace std;

class BasicSpreadsheet : public EvaluationContext
{
public:
    virtual string getCellDisplay(CellLocation location);

    virtual string getCellExpression(CellLocation location);

    virtual void setCellExpression(CellLocation location, string expression);

    virtual void addDependency(CellLocation dependent, CellLocation dependency);

    virtual void removeDependency(CellLocation dependent, CellLocation dependency);

    virtual void findCellReferences(CellLocation subject, set<CellLocation> target);

    virtual void recalculate(CellLocation location);
};
