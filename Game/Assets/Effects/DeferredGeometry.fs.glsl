#version 400

in vec3 vNormalVS;
//in vec2 vUV;
in vec3 vPos;
//uniform sampler2D   uMeshTexture;

//out float depth;
//out vec3 position;
layout(location = 0) out vec3 oNormalVS;
//layout(location = 1) out vec3 textureColor;

void main(){
    oNormalVS = vNormalVS;
    //position = vPos;
    //position = vec3( 1, 0, 0 );
   // textureColor = texture( uMeshTexture, vUV ).rgb;
   //textureColor = vec3( vUV, 1 );
    //normal = vec3( 1, 0, 0 );
	//color = vertexPos; 
    //color = vec4( 1, 0, 0, 1 );
   // depth = gl_FragCoord.z;
}