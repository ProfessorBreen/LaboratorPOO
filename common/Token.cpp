#include "HFiles/Token.h"

Token::Token(Kind kind)
{
    this->kind = kind;
    cellLocationValue = nullopt;
    numberValue = 0;
    assert(kind != NUMBER && kind != CELL_LOCATION);
}

Token::Token(CellLocation cellLocation)
{
    this->kind = CELL_LOCATION;
    cellLocationValue = cellLocation;
    numberValue = 0;
}

Token::Token(double value)
{
    this->kind = NUMBER;
    cellLocationValue = nullopt;
    numberValue = value;
}

Token::Token(Kind kind, CellLocation cellLocationValue, double numberValue)
{
    this->kind = kind;
    this->cellLocationValue = cellLocationValue;
    this->numberValue = numberValue;
}

ostream &operator<<(ostream &strm, const Token &token)
{
    switch (token.kind)
    {
        case CELL_LOCATION:
            strm << "CELL(" << token.cellLocationValue.value() << ")";
            break;
        case NUMBER:
            strm << "NUMBER(" + to_string(token.numberValue) + ")";
            break;
        default:
            strm << enum_str[token.kind];
    }
    return strm;
}

string kindToString(Kind kind)
{
    switch (kind)
    {
        case PLUS:
            return "+";
        case MINUS:
            return "-";
        case STAR:
            return "*";
        case SLASH:
            return "/";
        case CARET:
            return "^";
        case LPARENTHESIS:
            return "(";
        case RPARENTHESIS:
            return ")";
        case LANGLE:
            return "<";
        case RANGLE:
            return ">";
        case EQUALS:
            return "=";
        default:
            return "";
    }
}

vector<Token> tokenize(string input)
{
    vector<Token> result;
    string cellString;
    int intNumber = 0, realNumber = 0;
    int haveIntNumber = 0;
    bool haveCellRef = false;
    int n = input.size(), i;
    for (i = 0; i < n; i++)
    {
        if (isalpha(input[i]))
        {
            if (haveIntNumber)
                throw invalid_argument("Illegal symbol");
            haveCellRef = true;
            cellString.push_back(input[i]);
        }
        else if (isdigit(input[i]))
        {
            if (haveIntNumber == 2)
                realNumber = realNumber * 10 + (input[i] - '0');
            else if (!haveCellRef)
            {
                intNumber = intNumber * 10 + (input[i] - '0');
                haveIntNumber = 1;
            }
            else
                cellString.push_back(input[i]);
        }
        else if (input[i] == ' ')
        {
            if (haveCellRef)
            {
                result.emplace_back(CellLocation(cellString));
                cellString.clear();
            }
            else if (haveIntNumber == 2)
            {
                result.emplace_back(stod(to_string(intNumber) + "." + to_string(realNumber)));
            }
            else if (haveIntNumber)
            {
                result.emplace_back(intNumber);
            }
            intNumber = realNumber = haveIntNumber = 0;
            haveCellRef = false;
            cellString.clear();
        }
        else if (input[i] == '.')
        {
            if (haveIntNumber)
                haveIntNumber = 2;
            else
                throw invalid_argument("Illegal symbol");
        }
        else
        {
            if (i >= 1 && (input[i - 1] == '.' || input[i - 1] == ' '))
                throw invalid_argument("Illegal symbol");
            else
            {
                if (haveCellRef)
                {
                    result.emplace_back(CellLocation(cellString));
                    cellString.clear();
                }
                else if (haveIntNumber == 2)
                    result.emplace_back(stod(to_string(intNumber) + "." + to_string(realNumber)));
                else if (haveIntNumber)
                    result.emplace_back(intNumber);
                intNumber = realNumber = haveIntNumber = 0;
                haveCellRef = false;
                cellString.clear();
            }
            if (input[i] == '+')
                result.emplace_back(PLUS);
            else if (input[i] == '-')
                result.emplace_back(MINUS);
            else if (input[i] == '*')
                result.emplace_back(STAR);
            else if (input[i] == '/')
                result.emplace_back(SLASH);
            else if (input[i] == '^')
                result.emplace_back(CARET);
            else if (input[i] == '(')
                result.emplace_back(LPARENTHESIS);
            else if (input[i] == ')')
                result.emplace_back(RPARENTHESIS);
            else if (input[i] == '<')
                result.emplace_back(LANGLE);
            else if (input[i] == '>')
                result.emplace_back(RANGLE);
            else if (input[i] == '=')
                result.emplace_back(EQUALS);
            else
                throw invalid_argument("Unknown symbol");
        }
    }

    if (haveCellRef)
        result.emplace_back(CellLocation(cellString));
    else if (haveIntNumber == 2)
        result.emplace_back(stod(to_string(intNumber) + "." + to_string(realNumber)));
    else if (haveIntNumber)
        result.emplace_back(intNumber);
    return result;
}
