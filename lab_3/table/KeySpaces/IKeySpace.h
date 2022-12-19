#ifndef LAB_3_IKEYSPACE_H
#define LAB_3_IKEYSPACE_H

#include "KeySpaces/IKey.h"
#include "lib.h"

#include "Node.h"


template<class Data>
class IKeySpace {
protected:
    class KeySpaceException : public std::exception {
    private:
        std::string m_error;

    public:
        explicit KeySpaceException(std::string error) : m_error(std::move(error)) {}

        const char* what() const noexcept override { return m_error.c_str(); }
    };

public:

    virtual const lib::Deq<Node<Data>>* find(const IKey* key) const = 0;

    virtual bool push(const IKey* key, Item<Data>* data) = 0;

    virtual lib::Array<Node<Data>*> getAll() = 0;

    virtual ~IKeySpace() = default;
};

#endif //LAB_3_IKEYSPACE_H
