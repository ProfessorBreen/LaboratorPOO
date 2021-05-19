#include "HFiles/CellLocation.h"

CellLocation::CellLocation()
{
    representation = "";
}

CellLocation::CellLocation(const string &input)
{
    assert(!input.empty());
    CellLocation::representation = input;
}

CellLocation::CellLocation(int row, int column)
{
    assert(column >= 0 && row >= 0);
    representation = getColumnName(column) + to_string(row + 1);
}

string CellLocation::getColumnName(int column)
{
    string str;
    do
    {
        str.push_back((char) ('a' + column % 26));
        column /= 26;
    }
    while (column);
    return str;
}

bool CellLocation::operator==(const CellLocation &b) const
{
    return representation == b.representation;
}

bool CellLocation::operator<(const CellLocation &b) const
{
    return representation < b.representation;
}

CellLocation &CellLocation::operator=(const CellLocation &b)
{
    representation = b.representation;
    return *this;
}

CellLocation::operator string()
{
    return representation;
}

ostream &operator<<(ostream &strm, const CellLocation &cellLocation)
{
    strm << cellLocation.representation;
    return strm;
}