#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <exception>

class Exception:public std::exception
{
public:
	Exception(int err);
	virtual ~Exception();
	virtual const char* what() const noexcept override;
private:
	char* error;
};

#endif 