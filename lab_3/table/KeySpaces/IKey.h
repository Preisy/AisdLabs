#ifndef LAB_3_IKEY_H
#define LAB_3_IKEY_H

#include "string"

class IKey {
public:
    virtual bool isEqual(const IKey* key) const = 0;

    virtual std::string toString() const = 0;

public:
    virtual ~IKey() = default;

protected:
    class KeyException : public std::exception {
    private:
        std::string m_error;

    public:
        explicit KeyException(std::string error) : m_error(std::move(error)) {}

        const char* what() const noexcept override { return m_error.c_str(); }
    };
};

#endif //LAB_3_IKEY_H
