//-----------------------------------------------------------------------------
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <fstream>
#include "logger.h"
//-----------------------------------------------------------------------------

namespace attrs = boost::log::attributes;
namespace expr  = boost::log::expressions;

BOOST_LOG_ATTRIBUTE_KEYWORD(severity, "Severity", severity_level)

BOOST_LOG_GLOBAL_LOGGER_INIT(my_logger, boost::log::sources::severity_logger_mt)
{
   boost::log::sources::severity_logger_mt<severity_level> my_logger;

   boost::log::add_common_attributes();
   return my_logger;
}

//-----------------------------------------------------------------------------
// This operator is used for regular stream formatting
std::ostream& operator<<(std::ostream& strm, severity_level level)
{
   static const char* strings[] =
   {
      "debug",
      "message",
      "info",
      "warning",
      "error",
      "fatal",
   };

   if (static_cast<std::size_t>(level) < sizeof(strings) / sizeof(*strings))
      strm << strings[level];
   else
      strm << static_cast<int>(level);

   return strm;
}

//-----------------------------------------------------------------------------
// This operator is used when putting the severity level to log
boost::log::formatting_ostream& operator<<(
   boost::log::formatting_ostream& strm,
   boost::log::to_log_manip<severity_level> const& manip) {

   static const char* strings[] =
   {
      "[debug]   ",
      "[message] ",
      "[info]    ",
      "[warning] ",
      "[error]   ",
      "[fatal]   "
   };

   severity_level level = manip.get();
   if (static_cast<std::size_t>(level) < sizeof(strings) / sizeof(*strings))
      strm << strings[level];
   else
      strm << static_cast<int>(level);

   return strm;
}

//-----------------------------------------------------------------------------
// Initialize console logger
void init_console(const severity_level threshold)
{
   boost::log::add_console_log(
      std::clog,
      boost::log::keywords::filter = severity >= threshold,
      boost::log::keywords::format = (
              expr::stream << "[" << expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S.%f") << "] "
                           << "[" << expr::attr<attrs::current_thread_id::value_type>("ThreadID") << "] "
                           << expr::attr<severity_level>("Severity")
                           << expr::smessage
      )
   );
}

//-----------------------------------------------------------------------------
// Initialize logfile
void init_logfile(const severity_level threshold, const std::string& logfilename)
{
   boost::log::add_file_log(
      boost::log::keywords::file_name = logfilename,
      boost::log::keywords::filter = severity >= threshold,
      boost::log::keywords::rotation_size = 10 * 1024 * 1024,                                               // rotate files every 1 MiB
      boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0, 0, 0), // ...or at midnight
      boost::log::keywords::auto_flush = true,
      boost::log::keywords::format = (
              expr::stream << "[" << expr::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S.%f") << "] "
                           << "[" << expr::attr<attrs::current_thread_id::value_type>("ThreadID") << "] "
                           << expr::attr<severity_level>("Severity")
                           << expr::smessage
      )
   );
}
