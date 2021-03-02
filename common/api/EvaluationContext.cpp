#include "CellLocation.cpp"

using namespace std;

class EvaluationContext
{
public:
    virtual double getCellValue(CellLocation location);
};