#pragma once

#include "../../common/HFiles/Expression.h"
#include "Spreadsheet.h"
#include <set>
#include <utility>
#include <memory>

using namespace std;

class CellRef : public Expression
{
private:
    CellLocation cl;

public:
    explicit CellRef(CellLocation cl);

    [[nodiscard]] shared_ptr<Expression> clone() const override
    {
        return make_shared<CellRef>(*this);
    }

    double evaluate(Spreadsheet &context) override;

    void findCellReferences(set<CellLocation> dependencies) override;

    friend ostream &operator<<(std::ostream &strm, const CellRef &cellRef);
};

