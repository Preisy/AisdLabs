#ifndef LAB_2_CONVERTEXCEPTION_H
#define LAB_2_CONVERTEXCEPTION_H
class ConvertException : public std::exception {
private:
    std::string m_error;

public:
    explicit ConvertException(std::string error) : m_error(std::move(error)) {}

    const char *what() const noexcept override { return m_error.c_str(); }
};
#endif //LAB_2_CONVERTEXCEPTION_H
