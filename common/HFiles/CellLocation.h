#pragma once

#include <cassert>
#include <string>

using namespace std;

class CellLocation
{
private:
    string representation;
public:
    CellLocation();

    explicit CellLocation(const string &input);

    CellLocation(int row, int column);

    CellLocation(const CellLocation &c);

    static string getColumnName(int column);

    bool operator==(const CellLocation &b) const;

    bool operator<(const CellLocation &b) const;

    CellLocation &operator=(const CellLocation &b);

    explicit operator string();

    friend ostream &operator<<(std::ostream &strm, const CellLocation &cellLocation);
};
