#include "Cell.cpp"
#include "CycleDetector.cpp"
#include <map>

using namespace std;

class Spreadsheet : public BasicSpreadsheet
{
private:
    map<CellLocation, Cell> spreadsheet;
public:
    Spreadsheet()
    {}

    double evaluateExpression(string expression)
    {
        Expression expr = Parser::parse(expression);
        return expr.evaluate(*this);
    }

    void setCellExpression(CellLocation location, string input) override
    {
        CycleDetector cycleDetector = CycleDetector(*this);
        set<CellLocation> vis;

        if (spreadsheet.find(location) != spreadsheet.end())
        {
            Cell curCell = spreadsheet[location];
            curCell.setExpression(input);

            if (cycleDetector.hasCycleFrom(location))
                curCell.setExpression("0.0");

            recalculate(location);
            spreadsheet[location] = curCell;
        }
        else
        {
            Cell newCell = Cell(*this, location);
            spreadsheet[location] = newCell;
            newCell.setExpression(input);

            if (cycleDetector.hasCycleFrom(location))
                newCell.setExpression("0.0");

            recalculate(location);
            spreadsheet[location] = newCell;
        }
    }

    double getCellValue(CellLocation location) override
    {
        return getOrCreate(location).getValue();
    }

    string getCellExpression(CellLocation location) override
    {
        return getOrCreate(location).getExpression();
    }

    string getCellDisplay(CellLocation location) override
    {
        return getOrCreate(location).toString();
    }

    void addDependency(CellLocation dependent, CellLocation dependency) override
    {
        Cell cell = getOrCreate(dependency);
        cell.addDependent(dependent);
    }


    void removeDependency(CellLocation dependent, CellLocation dependency) override
    {
        Cell cell = getOrCreate(dependency);
        cell.removeDependent(dependent);
    }


    void recalculate(CellLocation location) override
    {
        getOrCreate(location).recalculate();
    }

    void findCellReferences(CellLocation subject, set<CellLocation> target) override
    {
        getOrCreate(subject).findCellReferences(target);
    }

public:

    Cell getOrCreate(CellLocation cellLocation)
    {
        if (spreadsheet.find(cellLocation) != spreadsheet.end())
            return spreadsheet[cellLocation];

        Cell newCell = Cell(*this, cellLocation);
        spreadsheet[cellLocation] = newCell;
        return newCell;
    }


};
