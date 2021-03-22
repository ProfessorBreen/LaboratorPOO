#pragma once
#include "../common/HFiles/Token.h"
#include "../common/HFiles/Expression.h"
#include "HFiles/Number.h"
#include "HFiles/CellRef.h"
#include "HFiles/BinaryOp.h"
#include <stack>
#include <string>
#include <vector>
#include <stdexcept>

using namespace std;

class Parser
{
public:
    static Expression *parse(const string &input);

    static bool hasHigherPriority(Kind kind, Kind other);


};