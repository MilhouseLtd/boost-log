//-----------------------------------------------------------------------------
#include "logger.h"
//-----------------------------------------------------------------------------

int main()
{
   init_console(debug);
   init_logfile(debug, "debug.log");


   DEBUG   << "This is severity level: " << debug;
   MESSAGE << "This is severity level: " << message;
   INFO    << "This is severity level: " << info;
   WARNING << "This is severity level: " << warning;
   ERROR   << "This is severity level: " << error;
   FATAL   << "This is severity level: " << fatal;

   return 0;
}


/*
[2018-03-01 18:42:51.955457] [0x00007fd2aac3d740] [debug]   This is severity level: debug
[2018-03-01 18:42:51.955918] [0x00007fd2aac3d740] [message] This is severity level: message
[2018-03-01 18:42:51.956005] [0x00007fd2aac3d740] [info]    This is severity level: info
[2018-03-01 18:42:51.956061] [0x00007fd2aac3d740] [warning] This is severity level: warning
[2018-03-01 18:42:51.956110] [0x00007fd2aac3d740] [error]   This is severity level: error
[2018-03-01 18:42:51.956158] [0x00007fd2aac3d740] [fatal]   This is severity level: fatal
 */
