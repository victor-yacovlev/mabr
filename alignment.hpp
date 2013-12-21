#ifndef ALIGNMENT_HPP
#define ALIGNMENT_HPP
extern "C" {
#include <ajseqdata.h>
#include <ajseq.h>
}

#include <vector>
#include <string>
#include <ostream>

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
    void print_xml(ostream & stream) const;
};

}

#endif // ALIGNMENT_HPP
