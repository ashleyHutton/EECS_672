#version 410 core

// phong.fsh - a fragment shader that implements a Phong Lighting model.

in PVA
{
	vec3 ecPosition;
	vec3 ecUnitNormal;
} pvaIn;

out vec4 fragmentColor;

// Phong material properties 

uniform vec3 ka, kd;
uniform vec3 la;

vec4 evaluateLightingModel()
{
	// NOTES:
	// 1. We assume for now a single directional light source defined in EC (liHat).
	// 2. We assume it will be "full strength" (see liStrength).
	//
	// In project 3, both #1 and #2 will be generalized by introducing uniform
	// arrays ("vec4 p_ecLightSourcePos" and "vec3 ecLightSourceStrength") and
	// using them INSTEAD OF the liHat and liStrength you see here.

	vec3 liHat = vec3(0.0, 0.0, 1.0);
	vec3 liStrength = vec3(1.0, 1.0, 1.0);
	vec3 nHat = pvaIn.ecUnitNormal;
	vec3 vHat = normalize(-pvaIn.ecPosition);

	if (dot(vHat, nHat) < 0){
		nHat = -1.0 * nHat;
	}

	if (dot(liHat, nHat) < 0){
		return vec4(ka * la, 1.0);
	}

	float factor = dot(liHat, nHat);
	return vec4((ka * la) + (factor * kd * liStrength), 1.0);
}

void main ()
{
	fragmentColor = evaluateLightingModel();
}
