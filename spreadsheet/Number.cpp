#include "HFiles/Number.h"

Number::Number(double value)
{
    this->value = value;
}

double Number::evaluate(Spreadsheet &context)
{
    return value;
}

ostream &operator<<(std::ostream &strm, const Number &number)
{
    strm << to_string(number.value);
    return strm;
}

void Number::findCellReferences(set<CellLocation> dependencies)
{
}
