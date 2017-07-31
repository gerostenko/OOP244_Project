// Final Project Milestone 2
// Version 1.0
// Date 2017-07-08
// Author Galina Erostenko
// Description - Milestone 2 of the Project
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////
#ifndef SICT_ERRORMESSAGE_H__
#define SICT_ERRORMESSAGE_H__
#include <iostream>
using namespace std;

namespace sict {
    class ErrorMessage
    {
    private:
        char* message_;
        void setEmpty();

    public:
        ErrorMessage();
        ErrorMessage(const char* errorMessage);
        ErrorMessage(const ErrorMessage& em) = delete;
        virtual ~ErrorMessage() { delete[] message_; }

        ErrorMessage& operator=(const ErrorMessage& em) = delete;
        ErrorMessage& operator=(const char* errorMessage);
        void clear();
        bool isClear()const;
        void message(const char* value);
        const char* message()const;
        std::ostream& write(std::ostream& ostr)const;
    };
    std::ostream& operator<< (std::ostream& ostr, const ErrorMessage& RO);

}
#endif