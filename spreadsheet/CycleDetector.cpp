#include <utility>

#include "../common/api/BasicSpreadsheet.cpp"


class CycleDetector
{
private:
    BasicSpreadsheet spreadsheet;
    set<CellLocation> visited;
public:
    explicit CycleDetector(BasicSpreadsheet spreadsheet)
    {
        this->spreadsheet = move(spreadsheet);
        visited.clear();
    }

    bool hasCycleFrom(CellLocation start)
    {
        visited.insert(start);
        set<CellLocation> nextCells;
        spreadsheet.findCellReferences(start, nextCells);
        for (CellLocation cellLocation : nextCells)
        {
            if (visited.find(cellLocation) != visited.end())
                return true;
            if (hasCycleFrom(cellLocation))
                return true;
        }
        visited.erase(start);
        return false;
    }
};
