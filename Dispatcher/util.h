#pragma once
#include "ClientInfo.h"

#define CIRESPONSE_STR(x) C_STR( ciresponse_str(x) )

std::string ciresponse_str(CI_RESPONSE resp);
