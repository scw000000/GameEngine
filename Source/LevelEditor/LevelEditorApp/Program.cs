﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;

namespace LevelEditorApp
   {
   static class Program
      {
      public static SDLThreadObject s_SDLThreadObject;
      public static DllRedirectThreadObject s_DllRedirectThreadObject;
      public static Editor s_Editor;
      public static Thread s_SDLThread;
      public static Thread s_DllRedirectThread;
      /// <summary>
      /// The main entry point for the application.
      /// </summary>
      [STAThread]
      static void Main()
         {
         Application.EnableVisualStyles();
         Application.SetCompatibleTextRenderingDefault( false );

         s_DllRedirectThreadObject = new DllRedirectThreadObject();
         s_DllRedirectThread = new Thread( s_DllRedirectThreadObject.Run );

         s_Editor = new Editor();

        // Application.AddMessageFilter( s_Editor.GetMessageHandler() );
        // s_Editor.FormClosing += new FormClosingEventHandler( s_EventHandler.Application_Closing );
         Application.Run( s_Editor );
         Program.s_SDLThread.Join();
         s_DllRedirectThread.Join();
         Program.s_Editor.ShutDownSDLWindow();
         
         }
      }
   }
