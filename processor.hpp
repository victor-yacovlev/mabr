#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

#include "region.hpp"
#include "alignment.hpp"
#include "matrix.hpp"
#include "block.hpp"

#include <deque>

namespace mabr {

using namespace std;

typedef deque<block> blocklist;

class processor {
public:

    explicit processor(const alignment & al,
                       const matrix & mx,
                       const float thereshold_column,
                       const float thereshold_row);

    void run();
    const blocklist & result() const;

private:

    enum criterion { GoodScore, LowScore, Gap };

    void split_into_vertical_blocks();

    float average_pairwise_score(const string & str) const;
    float column_score(const string & str) const;
    criterion vertical_bound_criterion(size_t column_index) const;

    bool check_for_good_rows(block & bl);

    alignment alignment_;
    matrix matrix_;
    float thereshold_column_;
    float thereshold_row_;
    blocklist data_;
};

}

#endif // PROCESSOR_HPP
