#include <string>

#ifndef HW2_SECURITY_H
#define HW2_SECURITY_H

#include "Password.h"

bool is_password(const std::string& user_psw) {
    return user_psw == PASSWORD;
}

#endif //HW2_SECURITY_H
