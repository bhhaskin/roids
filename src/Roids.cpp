#include "Roids.h"
#include "util/SimpleLogger/simplog.h"
#include <stdio.h>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

Roids::Roids() {

  targetFPS = 60.0;
  screenWidth = 800;
  screenHeight = 600;
  fontName = "res/fonts/PressStart2P-Regular.ttf";
  showFPS = true;

  simplog.writeLog( SIMPLOG_VERBOSE, "Target FPS: %.2f", targetFPS );
  simplog.writeLog( SIMPLOG_VERBOSE, "Screen Width: %d", screenWidth );
  simplog.writeLog( SIMPLOG_VERBOSE, "Screen Height: %d", screenHeight );
  simplog.writeLog( SIMPLOG_VERBOSE, "Font Name: %s", fontName );
  simplog.writeLog( SIMPLOG_VERBOSE, "Display FPS set to '%s'", showFPS ? "true" : "false" );

  display = NULL;
  main_queue = NULL;
  input_queue = NULL;
  timer = NULL;
  font12 = NULL;
  font18 = NULL;

  // Initialize Allegro
     if( !al_init() ) {
         simplog.writeLog( SIMPLOG_FATAL, "Failed to initialize Allegro!" );
         throw -1;
     } else {
         simplog.writeLog( SIMPLOG_DEBUG, "Allegro successfully initiallized" );
     }

     // Create the display
     display = al_create_display( screenWidth, screenHeight);
     if( !display ) {
         simplog.writeLog( SIMPLOG_FATAL, "Failed to create display!" );
         throw -1;
     } else {
         simplog.writeLog( SIMPLOG_DEBUG, "Display created successfully" );
     }

     // Initialize the keyboard
     if( !al_install_keyboard() ) {
         simplog.writeLog( SIMPLOG_FATAL, "Failed to initialize the keyboard!" );
         throw -1;
     } else {
         simplog.writeLog( SIMPLOG_DEBUG, "Keyboard initialized successfully" );
     }

     // Initialize the mouse
     if( !al_install_mouse() ) {
         simplog.writeLog( SIMPLOG_FATAL, "Failed to initialize the mouse!" );
         throw -1;
     } else {
         simplog.writeLog( SIMPLOG_DEBUG, "Mouse initialized successfully" );
     }

     // Create the main event queue
     main_queue = al_create_event_queue();
     if( !main_queue ) {
         simplog.writeLog( SIMPLOG_FATAL, "Failed to create main event queue!" );
         throw -1;
     } else {
         simplog.writeLog( SIMPLOG_DEBUG, "Main event Queue created susscessfully" );
     }

     // Create the input event queue
     input_queue = al_create_event_queue();
     if( !input_queue ) {
         simplog.writeLog( SIMPLOG_FATAL, "Failed to create input event queue!" );
         throw -1;
     } else {
         simplog.writeLog( SIMPLOG_DEBUG, "Input event Queue created susscessfully" );
     }

     // Register the display with the event queue
     al_register_event_source( main_queue, al_get_display_event_source( display ) );
     simplog.writeLog( SIMPLOG_VERBOSE, "Display event registered" );

     // Register the keyboard with the event queue
     al_register_event_source( input_queue, al_get_keyboard_event_source() );
     simplog.writeLog( SIMPLOG_VERBOSE, "Keyboard event registered" );

     // Register the mouse with the event queue
     al_register_event_source( input_queue, al_get_mouse_event_source() );
     simplog.writeLog( SIMPLOG_VERBOSE, "Mouse event registered" );

     // Initialize Allegro's image addon for handling images
     if( !al_init_image_addon() ) {
         simplog.writeLog( SIMPLOG_FATAL, "Failed to initialize image addon!" );
         throw -1;
     } else {
         simplog.writeLog( SIMPLOG_VERBOSE, "Image addon initialized" );
     }

     // Initialize Allegro's primitives addon for handling images
     if( !al_init_primitives_addon() ) {
         simplog.writeLog( SIMPLOG_FATAL, "Failed to initialize primitives addon!" );
         throw -1;
     } else {
         simplog.writeLog( SIMPLOG_VERBOSE, "Primitives addon initialized" );
     }

     // Initialize Allegro's font addon for handling fonts
     al_init_font_addon();
     simplog.writeLog( SIMPLOG_VERBOSE, "Font addon initialized" );

     // Initialize Allegro's TTF addon for handling TTF fonts
     if( !al_init_ttf_addon() ) {
         simplog.writeLog( SIMPLOG_FATAL, "Failed to initialize TTF addon!" );
         throw -1;
     } else {
         simplog.writeLog( SIMPLOG_VERBOSE, "TTF addon initialized" );
     }

     // Load a size 18 font
     font18 = al_load_font( fontName, 18, 0 );
     if( !font18 ) {
         // simplog.writeLog( SIMPLOG_FATAL, "Failed to load font '%s' at size %d!", fontName, 18 );
         throw -1;
     } else {
         // simplog.writeLog( SIMPLOG_DEBUG, "Font '%s' loaded at size %d", fontName, 18 );
     }

     // Load a size 12 font
     font12 = al_load_font( fontName, 12, 0 );
     if( !font12 ) {
         // simplog.writeLog( SIMPLOG_FATAL, "Failed to load font '%s' at size %d!", fontName, 12 );
         throw -1;
     } else {
         // simplog.writeLog( SIMPLOG_DEBUG, "Font '%s' loaded at size %d", fontName, 12 );
     }

     // Create a timer to cap the game FPS
     timer = al_create_timer( 1.0 / targetFPS );
     if( !timer ) {
         // simplog.writeLog( SIMPLOG_FATAL, "Failed to create timer with resolution of %.2f seconds!", 1.0 / targetFPS );
         throw -1;
     } else {
         // simplog.writeLog( SIMPLOG_VERBOSE, "Timer created with resolution of %.2f seconds", 1.0 / targetFPS );
     }

     // Register the timer with the event queue
     al_register_event_source( main_queue, al_get_timer_event_source( timer ) );
     // simplog.writeLog( SIMPLOG_VERBOSE, "Timer event registered" );

     // Clear the screen to black
 al_clear_to_color( al_map_rgb( 0, 0, 0 ) );


}

Roids::~Roids() {
  al_destroy_display( display );
      simplog.writeLog( SIMPLOG_VERBOSE, "Display destroyed" );

      al_destroy_event_queue( main_queue );
      simplog.writeLog( SIMPLOG_VERBOSE, "Main event queue destroyed" );

      al_destroy_event_queue( input_queue );
      simplog.writeLog( SIMPLOG_VERBOSE, "Input event queue destroyed" );

      al_destroy_timer( timer );
      simplog.writeLog( SIMPLOG_VERBOSE, "Timer destroyed" );

      al_destroy_font( font18 );
      al_destroy_font( font12 );
      simplog.writeLog( SIMPLOG_VERBOSE, "Font destroyed" );

      simplog.writeLog( SIMPLOG_DEBUG, "All game objects destroyed" );
}

void Roids::play() {
  simplog.writeLog( SIMPLOG_INFO, "Roids started successfully!" );

      // Start the timer
      al_start_timer( timer );
      simplog.writeLog( SIMPLOG_VERBOSE, "Timer started" );

      // Run loop variables
      bool done = false;
      bool redraw = true;
      double lastTime = al_get_time();
      double currentFPS = 0.0;
      int frames_done = 1;
      ALLEGRO_EVENT event;

      // Run loop
      while( !done ) {
          // Wait for an event to occur
          al_wait_for_event( main_queue, &event );

          // Redraw only when the timer event is triggered to cap FPS
          if( event.type == ALLEGRO_EVENT_TIMER ) {
              redraw = true;
          } else if( event.type == ALLEGRO_EVENT_DISPLAY_CLOSE ) {
              done = true;
          }

          // Get current time
          double currentTime = al_get_time();

          // Calculate delta time
          double delta = currentTime - lastTime;

          // Calculate current FPS
          if( delta >= 1.0 ) {
              currentFPS = frames_done / delta;

              frames_done = 0;
              lastTime = currentTime;
          }

          // Redraw if the timer was triggered, and the event queue is empty
          if( redraw && al_is_event_queue_empty( main_queue ) ) {
              redraw = false;




              // Print the FPS in the upper left corner
              if( showFPS ) {
                  al_draw_textf( font12, al_map_rgb( 255, 255, 255 ), 0, 0, ALLEGRO_ALIGN_LEFT, "FPS: %.2f", currentFPS );
              }

              // Flip the display
              al_flip_display();
          }

          // Increment the current frames total
          frames_done++;
  }
}
