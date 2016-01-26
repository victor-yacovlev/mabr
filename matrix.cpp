#include "matrix.hpp"
#include <cassert>
#include <string>

namespace mabr {

using namespace std;

matrix::matrix(const AjPMatrixf source)
{
    float ** sub = ajMatrixfGetMatrix(source);
    AjPSeqCvt cvt = ajMatrixfGetCvt(source);
    
    static const string Alphabet("*ARNDCQEGHILKMFPSTWYVBZX");
    
    for (size_t i=0u; i<Alphabet.length(); i++) {
        for (size_t j=0u; j<Alphabet.length(); j++) {
            const sympair key = make_pair(Alphabet[i], Alphabet[j]);
            const float value = sub[ajSeqcvtGetCodeK(cvt, Alphabet[i])][ajSeqcvtGetCodeK(cvt, Alphabet[j])];
            _data[key] = value;
        }
    }
}

float matrix::value(char a, char b) const
{
    if (' ' == a || '.' == a || '-' == a)
        a = '*';
    if (' ' == b || '.' == b || '-' == b)
        b = '*';
    const sympair key = make_pair(a, b);
    float result = _data.at(key);
    return result;
}

} // namespace mabr
