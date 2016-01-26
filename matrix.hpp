#pragma once
#ifndef MABR_MATRIX_HPP
#define MABR_MATRIX_HPP

extern "C" {
#include <ajmatrices.h>
#include <ajstr.h>
}

#include <map>
#include <utility>

namespace mabr {

class matrix
{
public:
    explicit matrix(const AjPMatrixf source);
    float value(char a, char b) const;
private:    
    using sympair = std::pair<char,char>;
    using scoremap = std::map<sympair,float>;

    scoremap _data;
};

} // namespace mabr

#endif // MABR_MATRIX_HPP
