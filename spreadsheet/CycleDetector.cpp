#include "HFiles/CycleDetector.h"

CycleDetector::CycleDetector(Spreadsheet spreadsheet)
{
    this->spreadsheet = move(spreadsheet);
    visited.clear();
}

bool CycleDetector::hasCycleFrom(const CellLocation &start)
{
    visited.insert(start);
    set<CellLocation> nextCells;
    spreadsheet.findCellReferences(start, nextCells);
    for (const CellLocation &cellLocation : nextCells)
    {
        if (visited.find(cellLocation) != visited.end())
            return true;
        if (hasCycleFrom(cellLocation))
            return true;
    }
    visited.erase(start);
    return false;
}
