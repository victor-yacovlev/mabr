#ifndef MABR_MATRIX_HPP
#define MABR_MATRIX_HPP

extern "C" {
#include <ajmatrices.h>
#include <ajstr.h>
}

#include <utility>
#include <map>

namespace mabr {

    using namespace std;
    
class matrix
{
public:
    explicit matrix(const AjPMatrixf source);
    float value(char a, char b) const;
private:    
    typedef pair<char,char> sympair;
    typedef map<sympair,float> scoremap;    
    scoremap data_;
};

} // namespace mabr

#endif // MABR_MATRIX_HPP
