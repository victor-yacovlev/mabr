#include "amino_group.hpp"

#include <cassert>
#include <cmath>
#include <algorithm>

namespace mabr {

mask::mask(size_t sz): valarray<unsigned>(0u, sz) {}

mask::operator bool ()
{
    unsigned count = 0u;
    for (size_t i=0u; i<size(); i++) {
        if ((*this)[i])
            count++;
        if (count >= 2)
            return true;
    }
    return false;
}

mask mask::operator &(const mask & other) const
{
    assert(size() == other.size());
    mask result(size());
    for (size_t i=0u; i<size(); i++) {
        result[i] = (*this)[i] && other[i];
    }
    return result;
}

bool mask::operator !=(const mask & other) const
{
    assert(size() == other.size());
    for (size_t i=0u; i<size(); i++) {
        const bool a = (*this)[i] > 0u;
        const bool b = other[i] > 0u;
        if (a != b) {
            return true;
        }
    }
    return false;
}

amino_group::amino_group(const string &s, float f, float R_)
    : aminos(&s), probability(f), R(R_)
{

}

mask amino_group::meaningful_for(const string &s) const
{
    mask result(s.length());
    for (size_t i=0u; i<aminos->length(); i++) {
        result += meaningful_char_for(aminos->at(i), s);
    }
    unsigned count = 0u;
    for (size_t i=0u; i<result.size(); i++) {
        if (result[i])
            count ++;
    }
    float freq = float(count) / float(s.length());
    float sigma = ::sqrtf(float(s.length() * (1.0f - probability) * probability));
    float thereshold = probability * R * sigma;
    bool meaningful = freq > thereshold;
    return meaningful? result : mask(s.length());
}

mask amino_group::meaningful_char_for(const char ch, const string &s) const
{
    mask result(s.length());
    size_t pos = 0u;
    while (true) {
        pos = s.find_first_of(ch, pos);
        if (pos == string::npos) {
            break;
        }
        result[pos] = 1u;
        pos ++;
    }
    return result;
}

static bool operator <(const amino_group &l, const amino_group &r)
{
    // sort in descending order
    return l.probability > r.probability;
}

vector<amino_group> amino_group_factory::create(float R)
{
    vector<amino_group> result;
    static const string s1("ILVM");
    static const string s2("RQK");
    static const string s3("NHSDE");
    static const string s4("C");
    static const string s5("G");
    static const string s6("FY");
    static const string s7("P");
    static const string s8("ST");
    static const string s9("W");
    float p1 = 3.8f + 7.6f + 6.8f + 1.8f;
    float p2 = 4.2f + 3.7f + 7.2f;
    float p3 = 4.4f + 2.9f + 8.1f + 5.9f + 5.8f;
    float p4 = 3.3f;
    float p5 = 7.4f;
    float p6 = 4.0f + 3.3f;
    float p7 = 5.0f;
    float p8 = 8.1f + 6.2f;
    float p9 = 1.3f;
    float sum = p1 + p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9;
    float scale = sum;
    p1 /= scale;
    p2 /= scale;
    p3 /= scale;
    p4 /= scale;
    p5 /= scale;
    p6 /= scale;
    p7 /= scale;
    p8 /= scale;
    p9 /= scale;
    result.push_back(amino_group(s1, p1, R));
    result.push_back(amino_group(s2, p2, R));
    result.push_back(amino_group(s3, p3, R));
    result.push_back(amino_group(s4, p4, R));
    result.push_back(amino_group(s5, p5, R));
    result.push_back(amino_group(s6, p6, R));
    result.push_back(amino_group(s7, p7, R));
    result.push_back(amino_group(s8, p8, R));
    result.push_back(amino_group(s9, p9, R));
    sort(result.begin(), result.end());
    return result;
}

}
