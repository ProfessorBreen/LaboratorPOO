#include <iostream>
#include "spreadsheet/Spreadsheet.cpp"

using namespace std;
vector<string> res;

void analyzeString(string s)
{
    int i, n = s.size();
    string curStr;
    for (i = 0; i < n; i++)
        if (s[i] == ' ')
        {
            if (!curStr.empty())
                res.push_back(curStr);
        }
        else
            curStr.push_back(s[i]);
    if (!curStr.empty())
        res.push_back(curStr);
}

string joinStrings(vector<string> v)
{
    string s;
    for (auto i : v)
        s += i;
    return s;
}

int main()
{
    Spreadsheet spreadsheet = Spreadsheet();
    string str;
    cout << "> ";
    cin >> str;
    while (!str.empty())
    {
        res.clear();
        analyzeString(str);
        if (res.size() == 1)
        {
            if (isalpha(res[0][0]))
                cout << spreadsheet.getCellValue(CellLocation(res[0]));
            else
                cout << res[0];
        }
        else if (res[1] == "=")
        {
            string firstCell = res[0];
            res.erase(res.begin());
            res.erase(res.begin());
            spreadsheet.setCellExpression(CellLocation(firstCell), joinStrings(res));
        }
        else
            cout << spreadsheet.evaluateExpression(joinStrings(res));

        cout << "\n";
        cout << "> ";
        cin >> str;
    }
    return 0;
}