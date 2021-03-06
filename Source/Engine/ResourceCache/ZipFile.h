#pragma once
/*!
 * \file ZipFile.h
 * \date 2016/05/29 20:00
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

#include <stdio.h>


typedef std::map<std::string, int> FileContentsMap;		// maps path to a zip content id

class ZipFile
   {
   public:
      ZipFile() { m_nEntries = 0; m_pFile = NULL; m_pDirData = NULL; }
      virtual ~ZipFile() { End(); fclose( m_pFile ); }

      bool Init( const std::wstring &resFileName );
      void End();

      int GetNumFiles() const { return m_nEntries; }
      std::string GetFileName( int i ) const; // return file name based one the entry
      int GetFileLen( int i ) const;
      bool ReadFile( int i, void *pBuf );

      bool ReadLargeFile( int i, void *pBuf, void ( *progressCallback )( int, bool & ) );
      int Find( const std::string &path ) const; 

      FileContentsMap m_FileContentsMap;

   private:
      struct TZipDirHeader; // located in the very end of zip file
      struct TZipDirFileHeader; // above TZipDirHeader, one for each file in zip file
      struct TZipLocalHeader; // located in each compressed file

      FILE *m_pFile;    // file pointer of the zip file
      char *m_pDirData; // raw data buffer
      int m_nEntries;

      const TZipDirFileHeader **m_papDir; // pointers to the dir entries in pDirData
   };