/*!
 * \file Controller.cpp
 * \date 2016/06/05 14:10
 *
 * \author SCW
 * Contact: scw000000@gmail.com
 *
 * \brief 
 *
 *  
 *
 * \note
 */

#include "EngineStd.h"
#include "Controller.h"



Controller::Controller( bool isMouseLocked = false ) : m_IsMouseLocked( isMouseLocked )
   {
   int x, y;
   SDL_GetMouseState( &x, &y );
   m_CurMousePos = m_LastMousePos = Point( x, y );
   m_MouseShift = Point( 0, 0 );
   memset( &m_KeyButton[ 0 ], 0x00, sizeof( bool ) * SDL_NUM_SCANCODES );
   memset( &m_MouseButton[ 0 ], 0x00, sizeof( bool ) * 256 );
   }

void Controller::VOnTickUpdate( unsigned long deltaMilliseconds )
   {
   VOnUpdate( deltaMilliseconds );
   if( m_IsMouseLocked )
      {
      SDL_WarpMouseInWindow( g_pApp->GetWindow(), g_pApp->GetScreenSize().GetX() / 2, g_pApp->GetScreenSize().GetY() / 2 );
      }
   m_LastMousePos = m_CurMousePos;
   m_MouseShift = Point( 0, 0 );
   }

bool Controller::VOnMsgProc( const SDL_Event& event )
   {
   switch( event.type )
      {
      case SDL_KEYDOWN:
            {
            return VOnKeyDown( event.key.keysym.scancode );
            }
      case SDL_KEYUP:
            {
            return VOnKeyUp( event.key.keysym.scancode );
            }
      case SDL_MOUSEMOTION:
            {
            return VOnPointerMove( Point( event.motion.x, event.motion.y ) );
            }
      case SDL_MOUSEBUTTONDOWN:
            {
            return VOnPointerButtonDown( event.button.button );
            }
      case SDL_MOUSEBUTTONUP:
            {
            return VOnPointerButtonUp( event.button.button );
            }
      case SDL_MOUSEWHEEL:

      case SDL_JOYAXISMOTION:
      case SDL_JOYBALLMOTION:
      case SDL_JOYHATMOTION:
      case SDL_JOYBUTTONDOWN:
      case SDL_JOYBUTTONUP:
      case SDL_JOYDEVICEADDED:
      case SDL_JOYDEVICEREMOVED:
      case SDL_CONTROLLERAXISMOTION:
      case SDL_CONTROLLERBUTTONDOWN:
      case SDL_CONTROLLERBUTTONUP:
      case SDL_CONTROLLERDEVICEADDED:
      case SDL_CONTROLLERDEVICEREMOVED:
      case SDL_CONTROLLERDEVICEREMAPPED:
         return false;
      }// Switch
   return false;
   }

bool Controller::VOnPointerMove( Point motion )
   {
   m_CurMousePos = motion;
   m_MouseShift = m_CurMousePos - m_LastMousePos;
   return true;
   }
