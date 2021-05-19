#include <iostream>
#include <vector>
#include <cmath>
#include "spreadsheet/HFiles/Spreadsheet.h"

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
            curStr.clear();
        }
        else
            curStr.push_back(s[i]);
    if (!curStr.empty())
        res.push_back(curStr);
}

string joinStrings(const vector<string> &v)
{
    string s;
    for (const auto &i : v)
        s += i;
    return s;
}

void autoTesting()
{
    cout << "-------------------- Starting Auto Testing --------------------" << "\n";
    Spreadsheet testSp = Spreadsheet();

    cout << "Testing arithmetic expression evaluation: \n";
    assert(testSp.evaluateExpression("3+5") == 8);
    assert(testSp.evaluateExpression("2-1") == 1);
    assert(testSp.evaluateExpression("7*8") == 56);
    assert(testSp.evaluateExpression("8*9") == 72);
    assert(testSp.evaluateExpression("6-8") == -2);
    assert(testSp.evaluateExpression("2/1") == 2);
    assert(testSp.evaluateExpression("5/2") == 2.5);
    assert(testSp.evaluateExpression("2^2") == 4);
    assert(testSp.evaluateExpression("3^2") == 9);
    assert(testSp.evaluateExpression("2+3*6") == 20);
    assert(testSp.evaluateExpression("3^2^2") == 81);
    assert(testSp.evaluateExpression("3*7-1") == 20);
    assert(testSp.evaluateExpression("4*3^1") == 12);
    assert(testSp.evaluateExpression("7+6-7-8+9") == 7);
    double val = testSp.evaluateExpression("1.1+2.2");
    assert(fabs(val - 3.3) < 1e-9);
    assert(testSp.evaluateExpression("2*1.1") == 2.2);
    assert(testSp.evaluateExpression("2*6-6*2+8") == 8);
    cout << "Tests passed" << "\n";

    cout << "Testing cell assignment (without dependencies): \n";
    testSp.setCellExpression(CellLocation("a1"), "7");
    assert(testSp.getCellValue(CellLocation("a1")) == 7);
    testSp.setCellExpression(CellLocation("a2"), "14");
    assert(testSp.getCellValue(CellLocation("a2")) == 14);
    testSp.setCellExpression(CellLocation("b1"), "3*2");
    assert(testSp.getCellValue(CellLocation("b1")) == 6);
    testSp.setCellExpression(CellLocation("b2"), "4+7+1");
    assert(testSp.getCellValue(CellLocation("b2")) == 12);
    cout << "Tests passed" << "\n";

    cout << "Testing cell reassignment (without dependencies): \n";
    testSp.setCellExpression(CellLocation("a1"), "21");
    assert(testSp.getCellValue(CellLocation("a1")) == 21);
    testSp.setCellExpression(CellLocation("a2"), "2+1");
    assert(testSp.getCellValue(CellLocation("a2")) == 3);
    testSp.setCellExpression(CellLocation("b1"), "7^2");
    assert(testSp.getCellValue(CellLocation("b1")) == 49);
    cout << "Tests passed" << "\n";

    cout << "Testing cell assignment with dependencies: \n";
    testSp.setCellExpression(CellLocation("a1"), "a2+3");
    assert(testSp.getCellValue(CellLocation("a1")) == 6);
    testSp.setCellExpression(CellLocation("a2"), "a3+19");
    assert(testSp.getCellValue(CellLocation("a2")) == 19);
    testSp.setCellExpression(CellLocation("b1"), "a2*7");
    assert(testSp.getCellValue(CellLocation("b1")) == 133);
    cout << "Tests passed" << "\n";

    cout << "Testing cell arithmetic: \n";
    assert(testSp.evaluateExpression("a1+7") == 13);
    assert(testSp.evaluateExpression("a2*8+a1+3") == 161);
    assert(testSp.evaluateExpression("a4") == 0);
    cout << "Tests passed" << "\n";
}

int main()
{
    autoTesting();

    cout << "-------------------- Auto Testing OK --------------------\n";
    cout << "-------------------- Manual Input Mode --------------------\n";
    cout << "Please don't use negative numbers or parenthesis. Please separate inputs with spaces. \n";
    cout << "Examples:\n";
    cout << "5 + 3 * 7\n";
    cout << "a1 = 3\n";
    cout << "a1 = a2 + 4\n";
    cout << "a1 + 7\n";
    cout << "Have fun! Press ENTER to exit\n";

    Spreadsheet spreadsheet = Spreadsheet();
    string str;
    cout << "> ";
    getline(cin, str);
    while (!str.empty())
    {
        res.clear();
        analyzeString(str);
        try
        {
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
        }
        catch (invalid_argument &e)
        {
            cout << "You entered an illegal character or a malformed expression\n";
        }
        catch (overflow_error &e)
        {
            cout << "Division by zero is forbidden\n";
        }

        cout << "\n";
        cout << "> ";
        getline(cin, str);
    }
    return 0;
}