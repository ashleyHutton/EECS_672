#version 410 core

// phong.fsh - a fragment shader that implements a Phong Lighting model.

in PVA
{
	vec3 ecPosition;
	vec3 ecUnitNormal;
	vec2 texCoords;
} pvaIn;

uniform int sceneHasTranslucentObjects = 0;
uniform int drawingOpaqueObjects = 1;
uniform int isUsingTexture = 0;

out vec4 fragmentColor;

const int MAX_NUM_LIGHTS = 4;
uniform int actualNumLights;

uniform vec3 ka = vec3(0.5, 0.5, 0.5), kd= vec3(0.5, 0.5, 0.5), ks= vec3(0.5, 0.5, 0.5);
uniform vec3 globalAmbient = vec3(0.1, 0.1, 0.1);

uniform float alpha;

uniform vec3 lightStrength[MAX_NUM_LIGHTS];
uniform vec4 p_ecLightSourcePos[MAX_NUM_LIGHTS];

uniform float shininess;

uniform mat4 ec_lds;

uniform sampler2D textureMap;


float atten(vec3 i, vec3 Q) {
	// computes attenuation for light source i at point Q
	vec3 v = (i - Q);
	float d = sqrt((v.x * v.x) + (v.y * v.y) + (v.z * v.z));

	return(4 / sqrt(d));
	// return 1.0;
}

vec4 evaluateLightingModel()
{
	// NOTES:
	// 1. We assume for now a single directional light source defined in EC (liHat).
	// 2. We assume it will be "full strength" (see liStrength).
	//
	// In project 3, both #1 and #2 will be generalized by introducing uniform
	// arrays ("vec4 p_ecLightSourcePos" and "vec3 ecLightSourceStrength") and
	// using them INSTEAD OF the liHat and liStrength you see here.

	// unit vector towards the viewer
	// dependent on type of projection
	vec3 vHat;
	if (ec_lds[2][3] != 0){ // col 2, row 3 != 0 => perspective
		vHat = normalize(-pvaIn.ecPosition);
	}
	else { // oblique or orthogonal
		double dx = -ec_lds[2][0]/ec_lds[0][0];
		double dy = -ec_lds[2][1]/ec_lds[1][1];
		vHat = normalize(vec3(dx, dy, 1));
	}

	vec3 nHat = pvaIn.ecUnitNormal;
	if (dot(vHat, nHat) < 0){
		nHat = -1.0 * nHat;
	}

	vec3 liHat;
	vec3 light = vec3(0, 0, 0);
	vec3 diffuse_factor = vec3(0, 0, 0); 
	vec3 specular_factor = vec3(0, 0, 0); 
	for (int i=0; i<actualNumLights; i++){
		vec3 liXYZ = vec3(p_ecLightSourcePos[i].x, p_ecLightSourcePos[i].y, p_ecLightSourcePos[i].z);
		if (p_ecLightSourcePos[i][3] == 1){ // positional light source
			liHat = normalize(liXYZ - pvaIn.ecPosition);
		}
		else { // directional
			liHat = normalize(liXYZ);
		}

		if (dot(liHat, nHat) < 0){
			// return vec4(ka * globalAmbient, 1.0);
			continue;
		}

		vec3 riHat = reflect(liHat, nHat);
		float dp = dot(riHat, vHat);
		if (dp > 0){
			specular_factor = ks * pow(dp, shininess);
		}

		diffuse_factor = kd * dot(nHat, liHat);

		if (p_ecLightSourcePos[i][3] == 1) {
			light += atten(liXYZ, pvaIn.ecPosition) * lightStrength[i] * (diffuse_factor + specular_factor);
		}
		else {
			light += lightStrength[i] * (diffuse_factor + specular_factor);	
		}
	}

	return vec4(ka * globalAmbient + light, 1.0);


}

void main ()
{
	vec4 textureColor = texture(textureMap, pvaIn.texCoords);
	vec4 lightModelColor = evaluateLightingModel();

	vec4 color;
	if (textureColor == vec4(0,0,0,1) && isUsingTexture == 0){ // no texture
		color = lightModelColor;
	}
	else {
		color = textureColor;
	}
	color[3] = alpha;

	if (sceneHasTranslucentObjects == 1) {
		if (drawingOpaqueObjects == 1){
			if (color[3] < 1.0)
				discard;
			else
				fragmentColor = color;
		}
		else if (color[3] < 1)
			fragmentColor = color;
		else
		 	discard;
	}
	else
		fragmentColor = color;

}


