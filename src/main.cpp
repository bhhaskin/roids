#include <stdio.h>
#include <string>
#include <allegro5/allegro_native_dialog.h>
#include "util/SimpleLogger/simplog.h"

const char* version = "Development Build";

// Logger settings
bool keepLogs       = false;
const char* logFile = "roids.log";
int logLevel        = SIMPLOG_VERBOSE;
bool silent = false;

// Prototypes
void initLogger();

int main(int argc, char **argv){
    initLogger();
    simplog.writeLog( SIMPLOG_INFO, "Starting Roids - Version: %s", version );

    return 0;
}

void initLogger() {
    // Set logfile name
    simplog.setLogFile( logFile );

    // Suppresses log output to stdout when true
    simplog.setLogSilentMode( silent );

    // Flush the logfile
    if( !keepLogs ) {
        simplog.flushLog();
    }

    // Set the level of logger output
    simplog.setLogDebugLevel( logLevel );
}
