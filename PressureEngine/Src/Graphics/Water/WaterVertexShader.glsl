#version 400
//#line 1 "WaterVertexShader.glsl"

in vec3 position;

out vec3 surfaceNormal;
out vec3 toLightVector;
out vec3 toCameraVector;
out vec4 clipSpace;

uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform vec3 lightPosition;

uniform float waveModifier;

vec4 permute(vec4 x){return mod(((x*34.0)+1.0)*x, 289.0);}
float permute(float x){return floor(mod(((x*34.0)+1.0)*x, 289.0));}
vec4 taylorInvSqrt(vec4 r){return 1.79284291400159 - 0.85373472095314 * r;}
float taylorInvSqrt(float r){return 1.79284291400159 - 0.85373472095314 * r;}

vec4 grad4(float j, vec4 ip){
  const vec4 ones = vec4(1.0, 1.0, 1.0, -1.0);
  vec4 p,s;

  p.xyz = floor( fract (vec3(j) * ip.xyz) * 7.0) * ip.z - 1.0;
  p.w = 1.5 - dot(abs(p.xyz), ones.xyz);
  s = vec4(lessThan(p, vec4(0.0)));
  p.xyz = p.xyz + (s.xyz*2.0 - 1.0) * s.www; 

  return p;
}

float snoise(vec4 v){
  const vec2  C = vec2( 0.138196601125010504,  // (5 - sqrt(5))/20  G4
                        0.309016994374947451); // (sqrt(5) - 1)/4   F4
// First corner
  vec4 i  = floor(v + dot(v, C.yyyy) );
  vec4 x0 = v -   i + dot(i, C.xxxx);

// Other corners

// Rank sorting originally contributed by Bill Licea-Kane, AMD (formerly ATI)
  vec4 i0;

  vec3 isX = step( x0.yzw, x0.xxx );
  vec3 isYZ = step( x0.zww, x0.yyz );
//  i0.x = dot( isX, vec3( 1.0 ) );
  i0.x = isX.x + isX.y + isX.z;
  i0.yzw = 1.0 - isX;

//  i0.y += dot( isYZ.xy, vec2( 1.0 ) );
  i0.y += isYZ.x + isYZ.y;
  i0.zw += 1.0 - isYZ.xy;

  i0.z += isYZ.z;
  i0.w += 1.0 - isYZ.z;

  // i0 now contains the unique values 0,1,2,3 in each channel
  vec4 i3 = clamp( i0, 0.0, 1.0 );
  vec4 i2 = clamp( i0-1.0, 0.0, 1.0 );
  vec4 i1 = clamp( i0-2.0, 0.0, 1.0 );

  //  x0 = x0 - 0.0 + 0.0 * C 
  vec4 x1 = x0 - i1 + 1.0 * C.xxxx;
  vec4 x2 = x0 - i2 + 2.0 * C.xxxx;
  vec4 x3 = x0 - i3 + 3.0 * C.xxxx;
  vec4 x4 = x0 - 1.0 + 4.0 * C.xxxx;

// Permutations
  i = mod(i, 289.0); 
  float j0 = permute( permute( permute( permute(i.w) + i.z) + i.y) + i.x);
  vec4 j1 = permute( permute( permute( permute (
             i.w + vec4(i1.w, i2.w, i3.w, 1.0 ))
           + i.z + vec4(i1.z, i2.z, i3.z, 1.0 ))
           + i.y + vec4(i1.y, i2.y, i3.y, 1.0 ))
           + i.x + vec4(i1.x, i2.x, i3.x, 1.0 ));
// Gradients
// ( 7*7*6 points uniformly over a cube, mapped onto a 4-octahedron.)
// 7*7*6 = 294, which is close to the ring size 17*17 = 289.

  vec4 ip = vec4(1.0/294.0, 1.0/49.0, 1.0/7.0, 0.0);

  vec4 p0 = grad4(j0,   ip);
  vec4 p1 = grad4(j1.x, ip);
  vec4 p2 = grad4(j1.y, ip);
  vec4 p3 = grad4(j1.z, ip);
  vec4 p4 = grad4(j1.w, ip);

// Normalise gradients
  vec4 norm = taylorInvSqrt(vec4(dot(p0,p0), dot(p1,p1), dot(p2, p2), dot(p3,p3)));
  p0 *= norm.x;
  p1 *= norm.y;
  p2 *= norm.z;
  p3 *= norm.w;
  p4 *= taylorInvSqrt(dot(p4,p4));

// Mix contributions from the five corners
  vec3 m0 = max(0.6 - vec3(dot(x0,x0), dot(x1,x1), dot(x2,x2)), 0.0);
  vec2 m1 = max(0.6 - vec2(dot(x3,x3), dot(x4,x4)            ), 0.0);
  m0 = m0 * m0;
  m1 = m1 * m1;
  return 49.0 * ( dot(m0*m0, vec3( dot( p0, x0 ), dot( p1, x1 ), dot( p2, x2 )))
               + dot(m1*m1, vec2( dot( p3, x3 ), dot( p4, x4 ) ) ) ) ;

}

float waveHeight(float x, float z) {
	//return sin(degrees(x * 4) + waveModifier) + sin(degrees(z * 4) + waveModifier);
	//return perlin(vec2(x, z) + waveModifier, 0.2, 1) / 2;
	return snoise(vec4(x / 4, z / 4, sin(waveModifier), cos(waveModifier))) / 6;
}

float waveHeight(vec3 position) {
	return waveHeight(position.x, position.z);
}

void main(void) {

	vec3 wavePos = (transformationMatrix * vec4(position.x, 0.0, position.z, 1.0)).xyz;

	wavePos.y = waveHeight(wavePos);

	vec3 normal_0 = cross(vec3(wavePos.x, waveHeight(wavePos.x, wavePos.z + 1), wavePos.z + 1), vec3(wavePos.x + 1, waveHeight(wavePos.x + 1, wavePos.z), wavePos.z));
	vec3 normal_1 = cross(vec3(wavePos.x, waveHeight(wavePos.x, wavePos.z - 1), wavePos.z - 1), vec3(wavePos.x - 1, waveHeight(wavePos.x - 1, wavePos.z), wavePos.z));
	
	vec3 normal_2 = cross(vec3(wavePos.x + 1, waveHeight(wavePos.x + 1, wavePos.z), wavePos.z), vec3(wavePos.x, waveHeight(wavePos.x, wavePos.z - 1), wavePos.z - 1));
	vec3 normal_3 = cross(vec3(wavePos.x - 1, waveHeight(wavePos.x - 1, wavePos.z), wavePos.z), vec3(wavePos.x, waveHeight(wavePos.x, wavePos.z + 1), wavePos.z + 1));

	vec3 normal = normalize(normal_0 + normal_1 + normal_2 + normal_3);
	
	// Don't know why this is needed => this is a bug.
	normal = reflect(-normal, vec3(0.0, 1.0, 0.0));

	surfaceNormal = (transformationMatrix * vec4(normal, 0.0)).xyz;

	toLightVector = normalize(lightPosition - wavePos.xyz);
	toCameraVector = normalize((inverse(viewMatrix) * vec4(0.0, 0.0, 0.0, 1.0)).xyz - wavePos.xyz);
	
	clipSpace = projectionMatrix * viewMatrix * vec4(wavePos, 1.0);
	gl_Position = clipSpace;

}
