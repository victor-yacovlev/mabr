#pragma once
#ifndef AMINO_GROUP_HPP
#define AMINO_GROUP_HPP

#include <cstdint>
#include <string>
#include <utility>
#include <valarray>
#include <vector>

namespace mabr {

struct mask
        : public std::valarray<uint32_t>
{
    explicit mask(size_t sz);
    operator bool();
    mask operator &(const mask & other) const;
    bool operator != (const mask & other) const;
};

class amino_group {
    friend class amino_group_factory;
public:

    const std::string * aminos;
    float probability;
    float R;

    mask meaningful_for(const std::string &s) const;

private:
    mask meaningful_char_for(const char ch, const std::string &s) const;
    explicit amino_group(const std::string &s, float f, float R);
};

class amino_group_factory {
public:
    static std::vector<amino_group> create(float R);
};

}

#endif // AMINO_GROUP_HPP
