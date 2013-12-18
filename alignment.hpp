#ifndef ALIGNMENT_HPP
#define ALIGNMENT_HPP
extern "C" {
#include <ajseqdata.h>
#include <ajseq.h>
}

#include <vector>
#include <string>

namespace  mabr {

using namespace std;

class alignment
        : public vector<string>
{
public:
    explicit alignment(AjPSeqall source);
    size_t length() const;
    string get_column(size_t index) const;
    string get_row(size_t index) const;
};

}

#endif // ALIGNMENT_HPP
