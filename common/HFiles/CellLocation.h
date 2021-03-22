#pragma once

#include <string>
#include <cassert>

using namespace std;

class CellLocation
{
private:
    string representation;
public:
    explicit operator string();

    CellLocation()
    {
        representation = "";
    }

    explicit CellLocation(const string &input);

    CellLocation(int row, int column);

    static string getColumnName(int column);

    bool operator==(const CellLocation &b) const;

    bool operator<(const CellLocation &b) const;

    friend ostream &operator<<(std::ostream &strm, const CellLocation &cellLocation);
};
