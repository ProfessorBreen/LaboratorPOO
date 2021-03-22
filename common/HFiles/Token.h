#pragma once

#include "CellLocation.h"
#include <optional>
#include <cassert>
#include <vector>
#include <iostream>

using namespace std;

enum Kind
{
    PLUS,
    MINUS,
    STAR,
    SLASH,
    CARET,
    LPARENTHESIS,
    RPARENTHESIS,
    LANGLE,
    RANGLE,
    EQUALS,
    NUMBER,
    CELL_LOCATION
};

static const char *enum_str[] = {"PLUS", "MINUS", "STAR", "SLASH", "CARET", "LPARENTHESIS", "RPARENTHESIS", "LANGLE",
                                 "RANGLE", "EQUALS", "NUMBER", "CELL_LOCATION"};

string kindToString(Kind kind);

class Token
{
public:
    Kind kind;
    optional<CellLocation> cellLocationValue;
    double numberValue;

    explicit Token(Kind kind);

    explicit Token(double value);

    explicit Token(CellLocation cellLocation);

private:
    Token(Kind kind, CellLocation cellLocationValue, double numberValue);

public:
    friend ostream &operator<<(std::ostream &strm, const Token &token);
};

vector<Token> tokenize(string input);

