/*!
 * \file RenderComponent.cpp
 * \date 2016/05/05 15:43
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
#include "RenderComponent.h"
#include "..\Event\EventManager.h"
#include "..\Event\Events.h"
#include "..\Graphics\MeshSceneNode.h"
#include "TransformComponent.h"
#include "..\Physics\PhysicsAttributes.h"
#include "..\ResourceCache\MeshResource.h"

//
//RenderComponent::RenderComponent( void )
//   {
//   m_pTransform = TransformPtr( ENG_NEW Transform( Transform::g_Identity ) );
//   }
//
//void RenderComponent::Destory( void )
//   {
//   m_pSceneNode.reset();
//   m_pTransform.reset();
//   }
//
//bool RenderComponent::VInit( TiXmlElement* pData )
//   {
//   ENG_ASSERT( pData );
//   Transform transform( Transform::g_Identity );
//   XMLParser::ReadTransform( pData->FirstChildElement( "Transform" ), &transform );
//   *m_pTransform = transform;
//   return VDelegateInit( pData );
//   }
//
//void RenderComponent::VPostInit( void )
//   {
//   if( m_pParentComponent.expired() )
//      {
//      shared_ptr<SceneNode> pSceneNode( VGetSceneNode() );
//      shared_ptr<Event_New_Render_Component_Root> pEvent( ENG_NEW Event_New_Render_Component_Root( m_pOwner->GetId(), pSceneNode ) );
//      IEventManager::GetSingleton()->VTriggerEvent( pEvent ); // process this event immediately
//      }
//   }
//
//TiXmlElement* RenderComponent::VGenerateXML( void )
//   {
//   TiXmlElement* pBaseElement = ENG_NEW TiXmlElement( VGetName().c_str() );
//   
//   TiXmlElement* pTransform = m_pTransform->GenerateXML();
//   pBaseElement->LinkEndChild( pTransform );
//
//   //// initial transform -> position
//   //TiXmlElement* pPosition = ENG_NEW TiXmlElement( "Position" );
//   //Vec3 pos( m_pTransform->GetToWorldPosition() );
//   //pPosition->SetAttribute( "x", ToStr( pos.x ).c_str() );
//   //pPosition->SetAttribute( "y", ToStr( pos.y ).c_str() );
//   //pPosition->SetAttribute( "z", ToStr( pos.z ).c_str() );
//   //pBaseElement->LinkEndChild( pPosition );
//
//   //// initial transform -> LookAt
//   //TiXmlElement* pDirection = ENG_NEW TiXmlElement( "PitchYawRoll" );
//   //Vec3 orient( m_pTransform->GetPitchYawRollDeg() );
//   //pDirection->SetAttribute( "x", ToStr( orient.x ).c_str() );
//   //pDirection->SetAttribute( "y", ToStr( orient.y ).c_str() );
//   //pDirection->SetAttribute( "z", ToStr( orient.z ).c_str() );
//   //pBaseElement->LinkEndChild( pDirection );
//   //
//   //// This is not supported yet
//   //// initial transform -> position
//   //TiXmlElement* pScale = ENG_NEW TiXmlElement( "Scale" );
//   //Vec3 scale( m_pTransform->GetScale() );
//   //pPosition->SetAttribute( "x", ToStr( scale.x ).c_str() );
//   //pPosition->SetAttribute( "y", ToStr( scale.y ).c_str() );
//   //pPosition->SetAttribute( "z", ToStr( scale.z ).c_str() );
//   //pBaseElement->LinkEndChild( pScale );
//
//   // create XML for inherited classes
//   VCreateInheritedXmlElements( pBaseElement );
//
//   return pBaseElement;
//   }
//
//void RenderComponent::BuildSceneNode( SceneNode* pParentNode )
//   {
//   m_pSceneNode = VCreateSceneNode();
//   m_pSceneNode->m_pParent = pParentNode;
//   for( auto pChildComponent : m_ChildComponents )
//      {
//      shared_ptr<RenderComponent> pChildRenderComponent = dynamic_pointer_cast< RenderComponent >( pChildComponent.lock() );
//      if( pChildRenderComponent )
//         {
//         m_pSceneNode->VAddChild( pChildRenderComponent->VGetSceneNode() );
//         }
//      }
//   shared_ptr< IEvent > pEvent( ENG_NEW Event_New_Scene_Node( m_pSceneNode ) );
//   EventManager::GetSingleton()->VTriggerEvent( pEvent );
//   }
//
///*
//void BaseRenderComponent::VOnChanged( void )
//   {
//   shared_ptr<EvtData_Modified_Render_Component> pEvent( ENG_NEW EvtData_Modified_Render_Component( m_pOwner->GetId() ) );
//   IEventManager::GetSingleton()->VTriggerEvent( pEvent );
//   }*/
//
//shared_ptr<SceneNode> RenderComponent::VGetSceneNode( void )
//   {
//   if( !m_pSceneNode )
//      {
//      SceneNode* pParentSceneNode = NULL;
//      if( !m_pParentComponent.expired() )
//         {
//         shared_ptr<RenderComponent> pParentRenderComponent = dynamic_pointer_cast< RenderComponent >( m_pParentComponent.lock() );
//         if( pParentRenderComponent )
//            {
//            pParentSceneNode = &*( pParentRenderComponent->m_pSceneNode );
//            }
//         }
//      BuildSceneNode( pParentSceneNode );
//      }
//   return m_pSceneNode;
//   }

//---------------------------------------------------------------------------------------------------------------------
// MeshRenderComponent
//---------------------------------------------------------------------------------------------------------------------

const ComponentRegisterId BaseActorComponent<MeshRenderComponent>::s_ComponentId = 0x7a02ca99;
const std::string BaseActorComponent<MeshRenderComponent>::s_Name = "MeshRenderComponent";

void MeshRenderComponent::Destory( void ) 
   {
   BaseRenderComponent::Destory();
   m_pMaterial.reset();
   m_pMeshResource.reset();
   }

MeshRenderComponent::MeshRenderComponent( void ) : m_pMeshResource( ENG_NEW Resource( "" ) ), m_pMaterial( ENG_NEW Material )
   {
   m_pPhysicsAttributes.reset( ENG_NEW BulletSpherePhysicsAttributes );
   }

// This function is called by  ActorFactory Actor::PostInit->BaseRenderCompoenent::PostInit->VGetSceneNode->VCreateSceneNode
shared_ptr<SceneNode> MeshRenderComponent::VCreateSceneNode( void )
   {
   shared_ptr< SceneNode > pMeshSceneNode( ENG_NEW MeshSceneNode( m_pOwner->GetId(), this, m_pMeshResource, m_pMaterial, RenderPass::RenderPass_Actor, m_pTransform ) );
      //// get the transform component
   //shared_ptr<TransformComponent> pTransformComponent = MakeStrongPtr( m_pOwner->GetComponent<TransformComponent>( TransformComponent::s_ComponentId ) );
   //if ( !pTransformComponent )
   //   {
   //   // can't render without a transform
   //   return shared_ptr<SceneNode>();
   //   }

   //WeakBaseRenderComponentPtr wbrcp(this);
   //shared_ptr< SceneNode > pMeshSceneNode( ENG_NEW MeshSceneNode( m_pOwner->GetId(), wbrcp, m_pMeshResource, m_pMaterial, RenderPass::RenderPass_Actor, pTransformComponent->GetTransform() ) );
   //
   return pMeshSceneNode;
   }

bool MeshRenderComponent::VDelegateInit( TiXmlElement* pData )
   {
   if( !pData )
      {
      return false;
      }

   // Set mesh file path
   m_pMeshResource->Init( pData->FirstChildElement( "Mesh" ) );
      
   m_pMaterial->Init( pData->FirstChildElement( "Material" ) );
   
   TiXmlElement* pPhysicsAttributes = pData->FirstChildElement( "PhysicsAttributes" );
   if( pPhysicsAttributes && m_pPhysicsAttributes )
      {
      m_pPhysicsAttributes->VInit( pPhysicsAttributes );
      }
   
   m_pPhysicsAttributes->VSetTransform( *m_pTransform );

   return true;
   }

void MeshRenderComponent::VDelegatePostInit( void )
   {
   auto pAiScene = MeshResourceLoader::LoadAndReturnScene( *m_pMeshResource );
   auto pMesh = pAiScene->mMeshes[ 0 ];
   /*IGamePhysics::GetSingleton().VAddPointCloud( ( Vec3* ) &( pMesh->mVertices[ 0 ] ),
                                                pMesh->mNumVertices,
                                                pRenderComp,
                                                m_pPhysicsAttributes->VGetDensity(),
                                                m_pPhysicsAttributes->VGetMaterial(),
                                                m_pPhysicsAttributes->VGetCollisionId(),
                                                btCollisionObject::CF_STATIC_OBJECT | btCollisionObject::CF_KINEMATIC_OBJECT );*/
   auto pShpereAttr = static_pointer_cast< BulletSpherePhysicsAttributes >( m_pPhysicsAttributes );
   pShpereAttr->SetRadius( this->m_pSceneNode->VGetProperties().GetRadius() );
   m_pPhysicsAttributes->VAddRigidBody( VGetSelfStrongRenderCompPtr() );
   }

void MeshRenderComponent::VDelegateGenerateXML( TiXmlElement* pBaseElement )
   {
   TiXmlElement* pMesh = m_pMeshResource->GenerateXML();
   pMesh->SetValue( "Mesh" );
   pBaseElement->LinkEndChild( pMesh );

   TiXmlElement* pMaterial = m_pMaterial->GenerateXML();
   pBaseElement->LinkEndChild( pMaterial );
   }

void MeshRenderComponent::VDelegateGenerateOverridesXML( TiXmlElement* pBaseElement, TiXmlElement* pResourceNode )
   {
   TiXmlElement* pMesh = m_pMeshResource->GenerateOverridesXML( pResourceNode->FirstChildElement( "Mesh" ) );
   pMesh->SetValue( "Mesh" );
   pBaseElement->LinkEndChild( pMesh );

   TiXmlElement* pMaterial = m_pMaterial->GenerateOverridesXML( pResourceNode->FirstChildElement( "Material" ) );
   pBaseElement->LinkEndChild( pMaterial );
   }


