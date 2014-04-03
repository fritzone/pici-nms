#pragma once

#define BOOST_RXREPLACE(str,lookfor,changefor) boost::regex_replace( str, boost::regex(lookfor),changefor,boost::match_default )
#define BOOST_RXSPLIT(str,sepexp,matches) boost::regex_split( std::back_inserter(matches),str, boost::regex(sepexp))

