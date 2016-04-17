////////////////////////////////////////////////////////////////////////////////
// Filename: Controller.cpp
////////////////////////////////////////////////////////////////////////////////

#include "EngineStd.h"
#include "Controller.h"

MovementController::MovementController( shared_ptr<SceneNode> object, float initialYaw, float initialPitch, bool rotateWhenLButtonDown ) : m_object( object )
   {
	m_object->VGetProperties()->GetRelTransform( &m_matToWorld, &m_matFromWorld );

	m_fTargetYaw = m_fYaw = RADIANS_TO_DEGREES(-initialYaw);
	m_fTargetPitch = m_fPitch = RADIANS_TO_DEGREES(initialPitch);

	m_maxSpeed = 30.0f;			// 30 meters per second
	m_currentSpeed = 0.0f;

	Vec3 pos = m_matToWorld.GetPosition();

	m_matPosition.BuildTranslation(pos);

   POINT ptCursor;
   GetCursorPos( &ptCursor );
	m_lastMousePos = ptCursor;

	memset( m_bKey, 0x00, sizeof( m_bKey ) );

	m_mouseLButtonDown = false;
	m_bRotateWhenLButtonDown = rotateWhenLButtonDown;  
   }


//  MovementController::VOnPointerButtonDown		- Chapter 10, page 282
//  These input update functions are called in OnMsgProc in humanView
bool MovementController::VOnPointerButtonDown( const Point &mousePos, const int radius, const std::string &buttonName )
   {
	if ( buttonName == "PointerLeft" )
	   {
		m_mouseLButtonDown = true;

		// We want mouse movement to be relative to the position
		// the cursor was at when the user first presses down on
		// the left button
		m_lastMousePos = mousePos;
		return true;
	   }
	return false;
   }

bool MovementController::VOnPointerButtonUp(const Point &mousePos, const int radius, const std::string &buttonName)
   {
	if ( buttonName == "PointerLeft" )
	   {
		m_mouseLButtonDown = false;
		return true;
	   }
	return false;
   }


//  class MovementController::VOnMouseMove		- Chapter 10, page 282

bool MovementController::VOnPointerMove(const Point &mousePos, const int radius)
   {
	// There are two modes supported by this controller.

	if ( m_bRotateWhenLButtonDown )
	   {
		// Mode 1 - rotate the view only when the left mouse button is down
		// Only look around if the left button is down
		if( m_lastMousePos != mousePos && m_mouseLButtonDown )
		   {
			m_fTargetYaw = m_fTargetYaw + (m_lastMousePos.x - mousePos.x);
			m_fTargetPitch = m_fTargetPitch + (mousePos.y - m_lastMousePos.y);
			m_lastMousePos = mousePos;
		   }
	   }
	else if( m_lastMousePos != mousePos )
	   {
		// Mode 2 - rotate the controller when the mouse buttons are up
		m_fTargetYaw = m_fTargetYaw + (m_lastMousePos.x - mousePos.x);
      // Invert Pitch
		m_fTargetPitch = m_fTargetPitch + (mousePos.y - m_lastMousePos.y);
		m_lastMousePos = mousePos;
	   }

	return true;
   }

//  class MovementController::OnUpdate			- Chapter 10, page 283
//  Update object movement in this function
//  This function is updated in human view
void MovementController::OnUpdate( const unsigned long deltaMilliseconds )
   {
	//if (m_bKey['Q'])
	//{
	//	// This code is a cheat to position the camera exactly in a given
	//	// spot so I can take screen shots!

	//	Mat4x4 camTranslate;
	//	D3DXMatrixTranslation(&m_matPosition, 8.847f, 7.055f, 11.618f);

	//	m_fTargetYaw = m_fYaw += -64.35f;
	//	m_fTargetPitch = m_fPitch = 28.57f;

	//	// Calculate the new rotation matrix from the camera
	//	// yaw and pitch.
	//	Mat4x4 matRot;
	//	D3DXMatrixRotationYawPitchRoll(&matRot, DEGREES_TO_RADIANS(m_fYaw), DEGREES_TO_RADIANS(m_fPitch), 0);

	//	// Create the new object-to-world matrix, and the
	//	// new world-to-object matrix. 
	//	D3DXMatrixMultiply(&m_matToWorld, &matRot, &m_matPosition);
	//	D3DXMatrixInverse(&m_matFromWorld, NULL, &m_matToWorld);

	//	m_object->VSetTransform(&m_matToWorld, &m_matFromWorld);
	//	return;
	//}

	bool bTranslating = false;
	Vec4 atWorld( 0.f, 0.f, 0.f,0.f );
	Vec4 rightWorld( 0.f, 0.f, 0.f, 0.f );
	Vec4 upWorld( 0.f, 0.f, 0.f, 0.f );

	if ( m_bKey['W'] || m_bKey['S'] )
	   {
		// In D3D, the "look at" default is always
		// the positive Z axis.
		Vec4 at = g_Forward4; 
		if (m_bKey['S'])
			at *= -1;

		// This will give us the "look at" vector 
		// in world space - we'll use that to move
		// the camera.
		atWorld = m_matToWorld.Xform( at );
		bTranslating = true;
	   }

	if (m_bKey['A'] || m_bKey['D'])
	   {
		// In D3D, the "right" default is always
		// the positive X axis.
		Vec4 right = g_Right4; 
		if (m_bKey['A'])
			right *= -1;

		// This will give us the "right" vector 
		// in world space - we'll use that to move
		// the camera
		rightWorld = m_matToWorld.Xform(right);
		bTranslating = true;
	   }

	if (m_bKey[' '] || m_bKey['C'] || m_bKey['X'])
	   {
		// In D3D, the "up" default is always
		// the positive Y axis.
		Vec4 up = g_Right4; 
		if ( !m_bKey[' '] )
			up *= -1;

		//Unlike strafing, Up is always up no matter
		//which way you are looking
		upWorld = up;
		bTranslating = true;
	   }

	//Handling rotation as a result of mouse position
	   {
		// The secret formula!!! Don't give it away!
		//If you are seeing this now, then you must be some kind of elite hacker!
		m_fYaw += ( m_fTargetYaw - m_fYaw ) * ( .35f );
		m_fTargetPitch = std::max( -90.f, std::min( 90.f, m_fTargetPitch ) );
		m_fPitch += ( m_fTargetPitch - m_fPitch ) * ( .35f );

		// Calculate the new rotation matrix from the camera
		// yaw and pitch.
		Mat4x4 matRot;
		matRot.BuildYawPitchRoll( DEGREES_TO_RADIANS( -m_fYaw ), DEGREES_TO_RADIANS( m_fPitch ), 0 );

		// Create the new object-to-world matrix, and the
		// new world-to-object matrix. 

		m_matToWorld = matRot * m_matPosition;
		m_matFromWorld = m_matToWorld.Inverse(); 
		m_object->VSetRelTransform( &m_matToWorld, &m_matFromWorld );
	   }

	if (bTranslating)
	   {
		float elapsedTime = (float)deltaMilliseconds / 1000.0f;

		Vec3 direction = atWorld + rightWorld + upWorld;
		direction.Normalize(); 

		// Ramp the acceleration by the elapsed time.
		float numberOfSeconds = 5.f;
		m_currentSpeed += m_maxSpeed * ( (elapsedTime*elapsedTime) / numberOfSeconds);
		if (m_currentSpeed > m_maxSpeed)
			m_currentSpeed = m_maxSpeed;

		direction *= m_currentSpeed;

		Vec3 pos = m_matPosition.GetPosition() + direction;
		m_matPosition.SetPosition(pos);
		m_matToWorld.SetPosition(pos);

		m_matFromWorld = m_matToWorld.Inverse();
		m_object->VSetRelTransform( &m_matToWorld, &m_matFromWorld );
	   }
	else
	   {
		m_currentSpeed = 0.0f;
	   }
   }