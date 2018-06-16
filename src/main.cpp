#include <stdio.h>
#include <string>
#include <allegro5/allegro_native_dialog.h>
#include "util/SimpleLogger/simplog.h"
#include "Roids.h"

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
    try {
           Roids *game = new Roids();
           game->play();
           delete game;
       } catch( int err ) {
           // Display error message box
           al_show_native_message_box( al_get_current_display(),
                                       "Roids Error", 
                                       ( "Error Code: " + std::to_string( err ) ).c_str(),
                                       "An unrecoverable error has occured.  See log for details.",
                                       NULL,
                                       ALLEGRO_MESSAGEBOX_ERROR );
           return err;
       }

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
