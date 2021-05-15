#pragma once

#include "../../common/HFiles/Token.h"
#include "../../common/HFiles/Expression.h"
#include "Number.h"
#include "CellRef.h"
#include "BinaryOp.h"
#include <stack>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

class Parser
{
public:
    static Expression *parse(const string &input);

    static bool hasHigherPriority(Kind kind, Kind other);
};