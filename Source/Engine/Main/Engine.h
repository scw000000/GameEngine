#pragma once
/*!
 * \file Engine.h
 * \date 2016/05/14 21:58
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
#include "../Mainloop/Initialization.h"
#include "../Main/BaseEngineLogic.h"
#include "../ResourceCache/ResourceCache.h"
#include "../UserInterface/PromptBox.h"

class EventManager;
class HumanView;

const Uint32 g_QuitNoPrompt = -1;

class EngineApp
   {
   public:
      EngineApp( void );
      ~EngineApp( void );

      void AbortGame( void ) { m_bQuitting = true; }
      void MainLoop( void );
      void OnClose( void );
      void SingleLoop( void );

      BaseEngineLogic* GetGameLogic(void) const { return m_pEngineLogic; }
      virtual BaseEngineLogic* VCreateLogic();
      HWND GetHwnd( void );      
      HumanView* GetHumanView( void );
      Point GetScreenSize( void ) const { return m_EngineOptions.GetScreenSize(); }
      SDL_Window* GetWindow() { return m_pWindow; }
      Uint32  GetWindowState( void );
      bool InitInstance( SDL_Window* window, int screenWidth, int screenHeight );
      bool IsRunning() { return m_bIsRunning; }
      bool LoadStrings( std::string language );
      int Modal( shared_ptr<PromptBox> pModalScreen, int defaultAnswer );
      static Renderer GetRendererImpl();
      static Uint32 RegisterEvent( int eventNum );
      std::wstring GetString( std::wstring sID );
      virtual TCHAR *VGetGameAppDirectory( void ){ return _T("Engine\\base\\0.1"); };
      void SetIsMouseCursorEnable( bool isDisplay );
      /**
       * @brief Return x and y coordinate of mouse location, left up = ( 0, 0 )
       *
       * @param   void
       * @return Point
       */
       Point GetMousePosition( void );
       bool IsMouseInsideWindow( void );
       void SetWindowFocus( void );
       void ResetMousePosition( void );
       static int EventFilter( void* userdata, SDL_Event* event );

   public:
      EngineOptions m_EngineOptions;
      TCHAR m_saveGameDirectory[MAX_PATH];
      BaseEngineLogic *m_pEngineLogic;
      ResourceCache *m_pResCache;
      VideoResourceCache *m_pVideoResCache;
      shared_ptr< IRenderManager > m_pRenderManager;
   //   shared_ptr< IMainRenderer > m_pRenderer;
      EventManager *m_pEventManager;

   protected:
      int PumpUntilMessage( Uint32& eventEnd, Sint32& code );
      void FlashWhileMinimized( void );
      int  PushUserEvent( Uint32 eventType, Sint32 code, void* d1 = NULL, void* d2 = NULL );

      void MsgProc( void );
      void OnUpdateGame( double fTime, float fElapsedTime );
      void OnFrameRender( double fTime, float fElapsedTime );
      /* 
      Why use TCHAR? because we may support multiple languages, some of them 
      will take 2 char instead of one for each character, in this case, we set the char class to ANSI (1) or Unicode (2)
      according to the confing in project properities, and the TCHAR means this char size will change automatically according
      to the project setting, also the ## symbol in the macro _T is token pasting operator, which would turn _T("Unicode") into L"Unicode" 
      if we are using Unicode
      http://www.codeproject.com/Articles/76252/What-are-TCHAR-WCHAR-LPSTR-LPWSTR-LPCTSTR-etc
      */
      virtual TCHAR* VGetGameTitle() { return _T("Engine"); };
      
      


   protected:
      bool m_bIsRunning;
      bool m_bQuitting;
      bool m_bQuitRequested;
      Point m_screenSize;					// game screen size
      SDL_Window *m_pWindow;
      Uint32 m_ShutDownEventType;
      std::map< std::wstring, std::wstring > m_textResource;

   private:
 
   };

extern EngineApp *g_pApp;