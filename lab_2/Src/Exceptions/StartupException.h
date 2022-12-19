#ifndef LAB_2_STARTUPEXCEPTION_H
#define LAB_2_STARTUPEXCEPTION_H
class StartupException : public std::exception {
private:
    std::string m_error;

public:
    explicit StartupException(std::string error) : m_error(std::move(error)) {}

    const char *what() const noexcept override { return m_error.c_str(); }
};
#endif //LAB_2_STARTUPEXCEPTION_H
