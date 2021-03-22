#pragma once
#include <utility>
#include "Spreadsheet.h"

class CycleDetector
{
private:
    Spreadsheet spreadsheet;
    set<CellLocation> visited;
public:
    explicit CycleDetector(Spreadsheet spreadsheet);

    bool hasCycleFrom(const CellLocation &start);
};
