#pragma once
/*!
 * \file Actor.h
 * \date 2016/05/22 16:34
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

#include "RenderComponent.h"

typedef std::string ActorType; 

class Actor
   {
   friend class ActorFactory;
 //  typedef std::map< ComponentId, StrongActorComponentPtr > ActorComponents;
   typedef std::map< ActorComponentId, StrongActorComponentPtr > ActorComponents;

   public:
      explicit Actor( ActorId id );
      ~Actor( void );

      bool Init( TiXmlElement* pData );
      void PostInit( void );
      // To break out the circular reference strongPtr chain of Actor & actorComponent
      void Destroy( void );
      void Update( unsigned long deltaMs );
      TiXmlElement* BuildXML( StrongActorComponentPtr pComponent );
      TiXmlElement* GenerateXML( void );
      TiXmlElement* GenerateOverridesXML( void );

      ActorId GetId( void ) const { return m_Id; }
      TransformPtr GetTransformPtr( void );
      weak_ptr< IActorComponent > GetComponent( ActorComponentId id );
      //template< class ComponentType > weak_ptr<ComponentType> GetComponent( const char* name );

   public:
     // std::weak_ptr< RenderComponent > m_pRootComponent;

   private:
      void AddComponent( StrongActorComponentPtr pComponent );
      ActorComponentId GetNextActorCompnentId( void ) { ++m_LastActorComponentId; return m_LastActorComponentId; }

   private:
      ActorId m_Id;
      ActorType m_Type;
      ActorComponents m_Components;
      ActorComponentId m_LastActorComponentId;
      std::string m_Resource; // actor XML file name
   };

//template< class ComponentType > weak_ptr<ComponentType> Actor::GetComponent( const char* name )
//   {
//   ComponentId id = ActorComponent::GetIdFromName( name );
//   return GetComponent<ComponentType>( id );
//   }