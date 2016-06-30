#pragma once
/*!
 * \file CollisionTable.h
 * \date 2016/06/26 16:53
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

typedef short CollisionId;
typedef short CollisionMask;

class CollisionTable : ENG_Noncopyable
   {
   public:
      static CollisionTable& GetSingleton( void );
      bool Init( TiXmlElement* pData );
      CollisionId GetIdFromName( const std::string& typeName );
      bool isCollidable( CollisionId id1, CollisionId id2 );
      CollisionMask GetCollisionMask( CollisionId id );

   private:
      CollisionTable( void ) { m_CurrMaxBit = -1; };
      bool AddCollisionType( const std::string& typeName );

      typedef std::map< CollisionId, CollisionMask > CollisionIdToMaskMap;
      typedef std::map< std::string, CollisionId > CollisionNameToIdMap;
      
      CollisionIdToMaskMap m_CollisionIdToMaskMap;
      CollisionNameToIdMap m_CollisionNameToIdMap;

      int m_CurrMaxBit;
   };



