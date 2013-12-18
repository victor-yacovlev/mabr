#ifndef BASIC_TREE_HPP
#define BASIC_TREE_HPP

#include <deque>
#include <list>

namespace mabr {

using namespace std;

template<
        typename DataType
>
struct basic_tree {
    const DataType & d;

    typedef list< basic_tree<DataType>* > list_type;
    typedef list< basic_tree<DataType>* >::iterator list_type_iterator;

    list_type children;
    basic_tree<DataType> * parent;

    inline explicit basic_tree(const DataType &data)
        : d(data), parent(0) {}

    inline void add(const DataType & data)
    {
        basic_tree<DataType> * child = new basic_tree<DataType>(data);
        child->parent = this;
        children.push_back(child);
    }

    inline ~basic_tree() {
        for (list_type_iterator<DataType> it = children.begin(); it!=children.end(); ++it) {
            delete *it;
        }
    }

};

}

#endif // BASIC_TREE_HPP
