#ifndef AMINO_GROUP_HPP
#define AMINO_GROUP_HPP

#include <string>
#include <valarray>
#include <vector>
#include <utility>

namespace mabr {

using namespace std;

class mask
        : public valarray<unsigned>
{
public:
    explicit mask(size_t sz);
    operator bool();
    mask operator &(const mask & other) const;
    bool operator != (const mask & other) const;
};

class amino_group {
    friend class amino_group_factory;
public:

    const string * aminos;
    float probability;
    float R;

    mask meaningful_for(const string &s) const;

private:
    mask meaningful_char_for(const char ch, const string &s) const;
    explicit amino_group(const string &s, float f, float R);
};

class amino_group_factory {
public:
    static vector<amino_group> create(float R);
};

}

#endif // AMINO_GROUP_HPP
