#include "alignment.hpp"

#include <cassert>

using namespace std;

namespace mabr {

alignment::alignment(AjPSeqall source)
    : vector<string>()
{
    AjPSeq seq = NULL;
    ajuint seqlen = 0u;
    const AjPStr seqstr;
    while(ajSeqallNext(source, &seq))
    {
        ajSeqTrim(seq);
        seqlen = ajSeqGetLen(seq);
        seqstr = ajSeqGetSeqS(seq);
        push_back(string(seqstr->Ptr));
    }
}

size_t alignment::length() const
{
    assert(size() > 0);
    return at(0).length();
}

string alignment::get_row(size_t index) const
{
    return at(index);
}

string alignment::get_column(size_t index) const
{
    string result(size(), '\0');
    for (size_t i=0; i<size(); i++) {
        const string & seq = at(i);
        result[i] = seq.at(index);
    }
    return result;
}


}
