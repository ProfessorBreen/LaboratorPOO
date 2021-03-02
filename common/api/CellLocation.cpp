#include <string>
#include <cassert>

using namespace std;

class CellLocation
{
private:
    static string representation;
public:
    static const string &getRepresentation()
    {
        return representation;
    }

    CellLocation(const string &input)
    {
        assert(!input.empty());
        this->representation = input;
    }

    CellLocation(int row, int column)
    {
        assert(column >= 0 && row >= 0);
        representation = getColumnName(column) + to_string(row + 1);
    }

    static string getColumnName(int column)
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

    bool operator==(const CellLocation &b) const
    {
        return representation == b.getRepresentation();
    }

    friend ostream &operator<<(std::ostream &strm, const CellLocation &cellLocation)
    {
        strm << getRepresentation();
        return strm;
    }
};
