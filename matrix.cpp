#include "matrix.hpp"
#include <cassert>

namespace mabr {

matrix::matrix(const AjPMatrixf source)
{
    float ** sub = ajMatrixfGetMatrix(source);
    AjPSeqCvt cvt = ajMatrixfGetCvt(source);
    
    static const string Alphabet("ARNDCQEGHILKMFPSTWYVBZX");
    
    for (size_t i=0u; i<Alphabet.length(); i++) {
        for (size_t j=0u; j<Alphabet.length(); j++) {
            const sympair key = make_pair(Alphabet[i], Alphabet[j]);
            const float value = sub[ajSeqcvtGetCodeK(cvt, Alphabet[i])][ajSeqcvtGetCodeK(cvt, Alphabet[j])];
            data_[key] = value;
        }
    }
}

float matrix::value(const char a, const char b) const
{
    const sympair key = make_pair(a, b);
    float result = data_.at(key);
    return result;
}

} // namespace mabr
