#include "HFiles/CellRef.h"
#include "HFiles/Spreadsheet.h"

CellRef::CellRef(const CellLocation& cl) : cl(cl)
{
}

double CellRef::evaluate(Spreadsheet &context)
{
    return context.getCellValue(cl);
}

void CellRef::findCellReferences(set<CellLocation> dependencies)
{
    dependencies.insert(cl);
}

ostream &operator<<(ostream &strm, const CellRef &cellRef)
{
    strm << cellRef.cl;
    return strm;
}

CellRef::CellRef(const CellRef &c)
{
    cl = c.cl;
}