// Final Project Milestone 2
// Version 1.0
// Date	
// Author	
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "ErrorMessage.h"
using namespace std;


namespace sict {

    void ErrorMessage::setEmpty()
    {
        message_ = nullptr;
    }

    ErrorMessage::ErrorMessage()
    {
        setEmpty();
    }
    ErrorMessage::ErrorMessage(const char* errorMessage)
    {
        setEmpty();
        message(errorMessage);
    }

    ErrorMessage&  ErrorMessage::operator=(const char* errorMessage)
    {
        clear();
        message(errorMessage);

        return *this;
    }
    void ErrorMessage::clear()
    {
        delete[] message_;
        setEmpty();
    }
    bool ErrorMessage::isClear()const
    {
        return message_ == nullptr;
    }
    void ErrorMessage::message(const char* value)
    {
        delete[] message_;
        message_ = new char[strlen(value) + 1];
        message_[0] = '\0';
        strncpy(message_, value, strlen(value) + 1);
        message_[strlen(value)] = '\0';
    }
    const char* ErrorMessage::message()const
    {
        return message_;
    }
    std::ostream& ErrorMessage::write(std::ostream& ostr)const
    {
        if (!isClear())
        {
            ostr << message_;
        }
        return ostr;
    }

    std::ostream& operator<< (std::ostream& ostr, const ErrorMessage& RO)
    {
        return RO.write(ostr);
    }

}