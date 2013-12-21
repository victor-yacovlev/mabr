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

void alignment::print_xml(ostream &stream) const
{
    stream << "<alignment>" << endl;
    for (size_t i=0u; i<size(); i++) {
        stream << "<row index='" << i << "'>";
        for (size_t j=0u; j<length(); j++) {
            stream << "<symbol "
                   << "row='" << i << "' "
                   << "column='" << j << "'>";
            stream << at(i).at(j);
            stream << "</symbol>";
        }
        stream << "</row>" << endl;
    }
    stream << "</alignment>" << endl;
}


}
