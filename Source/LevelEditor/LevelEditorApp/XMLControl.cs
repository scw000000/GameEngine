﻿using System;
using System.Xml;
using System.Xml.XPath;
using System.IO;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Text;
using System.Windows.Forms;

namespace LevelEditorApp
   {
   public partial class XMLControl : UserControl
      {
      public XMLControl()
         {
         InitializeComponent();
         SetViewMode( VIEW_MODE.TABLE );
         }
      private bool m_bGridViewModeReadError = false;
      private DataSet m_DataSet;
      private List<System.Windows.Forms.DataGridView> m_XMLGridViews;
      public enum VIEW_MODE {XML, TABLE}       
      public VIEW_MODE ViewMode
         {
            get
            {
                return (webXMLView.Visible ? VIEW_MODE.XML : VIEW_MODE.TABLE);
            }
            set
            {
                SetViewMode(value);
            }
        }

      private string m_sDataFilePath = string.Empty;
      public string DataFilePath
         {
         get
            {
            return m_sDataFilePath;
            }
         set
            {
            m_sDataFilePath = value;
            LoadDataFile();
            }
         }

      private int m_nDataSetTableIndex = 0;
      public int DataSetTableIndex
         {
         get
            {
            return m_nDataSetTableIndex;
            }
         set
            {
            SetDataSetTableIndex(value);                
            }
         }
        
      private int m_nDataTableCount = 0;
      public int DataTableCount
         {
        get { return m_nDataTableCount; }            
         }

      private void SetViewMode(VIEW_MODE mode)
         {
         if( m_bGridViewModeReadError == true )
            {
            mode = VIEW_MODE.XML;                
            }                        

         if( mode == VIEW_MODE.XML )
            {
            webXMLView.Visible = true;
            xmlPanel.Visible = false;
            }
         else
            {
            webXMLView.Visible = false;
            xmlPanel.Visible = true;
            }
        }

      private void LoadDataFile()
         {
         m_bGridViewModeReadError = false;

         // use the webbrowser control to automatically parse the file
         webXMLView.Navigate(m_sDataFilePath);

         if ((m_sDataFilePath != string.Empty) && (File.Exists(m_sDataFilePath) == true))
            {
            // Creates a DataSet and loads it with the xml content
            try
               {
               m_DataSet = new DataSet();
               m_DataSet.ReadXml( m_sDataFilePath, XmlReadMode.Auto );
               m_nDataTableCount = m_DataSet.Tables.Count;
               // write to XML file
               //System.IO.StreamWriter xmlSW = new System.IO.StreamWriter( "Customers.xml" );
               //m_DataSet.WriteXml( xmlSW, XmlWriteMode.IgnoreSchema );
               //xmlSW.Close();
               GenerateXMLGrieView();
               //    grdTableView.DataSource = dsXmlFile.Tables[DataSetTableIndex];                    
               }
            catch( Exception e )
               {
               m_bGridViewModeReadError = true;
               m_nDataTableCount = 0;
               webXMLView.Navigate(m_sDataFilePath);
               SetViewMode(VIEW_MODE.XML);
               MessageBox.Show( "Error: " + e.ToString() );
               }
            }
         else
            {
            //    grdTableView.DataSource = null;
            }
         }

      private void SetDataSetTableIndex(int nTableIndex)
         {
         if( nTableIndex >= m_nDataTableCount ) 
            {
            return;
            }
         m_nDataSetTableIndex = nTableIndex;
         LoadDataFile();
         }

      private void GenerateXMLGrieView() 
         {
         for( int i = 0; i < m_DataSet.Tables.Count; ++i )
            {
            // Each table represents an unique XML node name
            // Rows count represents how many node has the same name
            //
            if( m_DataSet.Tables[ i ].Rows.Count > 0 )
               {
               Console.WriteLine( "table: " + i );
               for( int j = 0; j < m_DataSet.Tables[ i ].Rows.Count; j++ )
                  {
                  
                  int len = m_DataSet.Tables[ i ].Rows[ j ].ItemArray.Length;
                  Console.WriteLine( "row " + j + " " + "coujnt = " + len );
                  }
               
               }
            if( true || ( m_DataSet.Tables[ i ].Rows.Count > 0 && m_DataSet.Tables[ i ].Rows[0].ItemArray.Length > 0 ) )
               {
               System.Windows.Forms.DataGridView dataGridView = new System.Windows.Forms.DataGridView ();
               System.Windows.Forms.Button button = new Button();
               System.Windows.Forms.ToolTip toolTip1 = new System.Windows.Forms.ToolTip();
               toolTip1.SetToolTip( button, "motherfucker" );
               this.xmlPanel.RowCount = this.xmlPanel.RowCount + 1;
               this.xmlPanel.Controls.Add( dataGridView, 1, this.xmlPanel.RowCount - 1 );
               this.xmlPanel.Controls.Add( button, 0, this.xmlPanel.RowCount - 1 );
               button.Text = ( m_DataSet.Tables[ i ].TableName );
               Console.WriteLine( m_DataSet.Tables[ i ].TableName );
               if( m_DataSet.Tables[ i ].Rows[ 0 ].ItemArray.Length > 0 )
                  {
                  int asdasdas = 0;
                  }
               //if( m_DataSet.Tables[ i ].Rows[ 0 ].Table.ParentRelations.Count > 0 )
               //   {

               //   Console.WriteLine( m_DataSet.Tables[ i ].TableName );
               //   Console.WriteLine( m_DataSet.Tables[ i ].Rows[ 0 ].Table.ParentRelations[ 0 ].RelationName );
               //   Console.WriteLine( m_DataSet.Tables[ i ].Rows[ 0 ].Table.ParentRelations[ 0 ].ParentTable.TableName );
               //   foreach( DataRow aaa in m_DataSet.Tables[ i ].Rows )
               //      {
               //      Console.WriteLine( "********************" );
               //      foreach( DataRelation bbb in aaa.Table.ParentRelations )
               //         {
               //         Console.WriteLine( aaa.TableName );
               //         Console.WriteLine( bbb.RelationName );
               //         }
               //      }
               //   Console.WriteLine( "------------------" );
               //   if( m_DataSet.Tables[ i ].Rows[ 0 ].Table.ParentRelations.Count > 1 )
               //      {
               //      int asdasdasd = 0;
               //      }
               //   }
               //else
               //   {
               //   int asdasdasd = 0;
               //   }
              
               dataGridView.DataSource = m_DataSet.Tables[ i ];
               dataGridView.AllowUserToAddRows = false;
               dataGridView.AllowUserToDeleteRows = false;
               dataGridView.AllowUserToResizeRows = false;
               dataGridView.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
               dataGridView.AutoSizeRowsMode = System.Windows.Forms.DataGridViewAutoSizeRowsMode.AllCells;

               dataGridView.BackgroundColor = System.Drawing.Color.FromArgb( ( (int) ( ( (byte) ( 49 ) ) ) ), ( (int) ( ( (byte) ( 49 ) ) ) ), ( (int) ( ( (byte) ( 49 ) ) ) ) );
               
               var totalHeight = dataGridView.Rows.GetRowsHeight( DataGridViewElementStates.None );
               if( dataGridView.Rows.Count > 0 )
                  {
                  totalHeight += dataGridView.ColumnHeadersHeight;
                  }
               else 
                  {
                  int asdasdasdsd = 0;
                  }
               this.xmlPanel.RowStyles.Add( new System.Windows.Forms.RowStyle( System.Windows.Forms.SizeType.Absolute, totalHeight ) );
               this.xmlPanel.ColumnStyles[ 1 ] = new System.Windows.Forms.ColumnStyle( System.Windows.Forms.SizeType.Absolute, 10 );
               }
            }
         
         
         }

      private void button1_MouseClick( object sender, MouseEventArgs e )
         {
         if( ViewMode == VIEW_MODE.XML )
            {
            SetViewMode( VIEW_MODE.TABLE );
            }
         else 
            {
            SetViewMode( VIEW_MODE.XML );
            }
         }
      }
   }
