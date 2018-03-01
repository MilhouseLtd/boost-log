//-----------------------------------------------------------------------------
#pragma once
//-----------------------------------------------------------------------------
#include <boost/log/expressions.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>
//-----------------------------------------------------------------------------

// Define our severity levels
enum severity_level
{
   debug,
   message,
   info,
   warning,
   error,
   fatal
};

void init_console(const severity_level threshold);
void init_logfile(const severity_level threshold, const std::string& logfilename);

//-----------------------------------------------------------------------------
// Register a global logger
BOOST_LOG_GLOBAL_LOGGER(my_logger, boost::log::sources::severity_logger_mt<severity_level>)

//-----------------------------------------------------------------------------
// This operator is used for regular stream formatting
std::ostream& operator<<(std::ostream& strm, severity_level level);

//-----------------------------------------------------------------------------
// This operator is used when putting the severity level to log
boost::log::formatting_ostream& operator<<(
   boost::log::formatting_ostream& strm,
   boost::log::to_log_manip<severity_level> const& manip);

//-----------------------------------------------------------------------------
// Helper macros
#define DEBUG   BOOST_LOG_SEV(my_logger::get(), debug)
#define MESSAGE BOOST_LOG_SEV(my_logger::get(), message)
#define INFO    BOOST_LOG_SEV(my_logger::get(), info)
#define WARNING BOOST_LOG_SEV(my_logger::get(), warning)
#define ERROR   BOOST_LOG_SEV(my_logger::get(), error)
#define FATAL   BOOST_LOG_SEV(my_logger::get(), fatal)

