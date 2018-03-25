#version 410 core

layout ( triangles ) in;
layout ( triangle_strip, max_vertices = 93 ) out;

in PVA
{
	vec3 ecPosition;
	vec3 ecUnitNormal;
	vec2 texCoords;
} pva_in[];

out PVA
{
	vec3 ecPosition;
	vec3 ecUnitNormal;
	vec2 texCoords;
} pvaOut;

uniform int makeALot = 0;

float rand0To1Table[] = float[] (
	0.170828, 0.749902, 0.0963717, 0.870465, 0.577304, 0.785799, 0.692194,
	0.368766, 0.873904, 0.745095, 0.446046, 0.353728, 0.73252, 0.260222,
	0.394294, 0.77679, 0.845035, 0.575788, 0.715539, 0.0830042, 0.455825,
	0.109947, 0.545228, 0.390687, 0.568585, 0.959066, 0.867719, 0.16319,
	0.275509, 0.260361, 0.924095, 0.435923, 0.789461, 0.127617, 0.0822057,
	0.940642, 0.0255749, 0.154211, 0.382182, 0.154737, 0.529333, 0.876849,
	0.430611, 0.263906, 0.313594, 0.770092, 0.107391, 0.771042, 0.705196,
	0.21864, 0.761794, 0.411713, 0.648827, 0.929956, 0.502419, 0.687441,
	0.436091, 0.608301, 0.576559, 0.632622, 0.463426, 0.632244, 0.138295,
	0.960761, 0.144375, 0.446683, 0.324584, 0.952584, 0.358184, 0.398208,
	0.101282, 0.955086, 0.984617, 0.57597, 0.865914, 0.149876, 0.90915,
	0.651253, 0.0638609, 0.954999, 0.966263, 0.785543, 0.805165, 0.571254,
	0.282586, 0.962551, 0.579477, 0.436859, 0.375436, 0.923408, 0.0286994,
	0.76886, 0.723107, 0.590969, 0.425889, 0.642143, 0.746763, 0.0690186,
	0.0532949, 0.774314
);

float rand0to6Table[] = float[] (
	3.03,2.65,3.38,4.51,1.02,4.66,3.82,2.49,5.72,5.16,2.57,3.6,2.8,4.71,2.64,
	4.09,1.54,4.65,2.19,3,4.64,4.65,2.78,1.48,1.25,4.92,2.77,1.81,0.85,1.27,
	5.46,4.67,3.51,0.61,1.39,4.11,2.74,3.63,4.67,2.88,5.06,2.64,5.28,1.98,
	1.96,5.04,3.41,2.06,2.96,2.78,5.21,3.02,4.34,5.03,2.37,1,5.38,0.63,5.56,
	1.88,4.16,5.92,5.4,1.92,5.56,1.69,3.95,4.25,4.87,0.87,2.34,0.83,0.82,1.15,
	4.42,4.51,4.11,4.09,2.55,3.65,1.48,1.6,3.99,1.01,1.43,5.56,3.3,4.19,0.83,
	5.68,1.7,0.51,4.66,3.41,5.66,2.81,5.48,2.57,1.72,2.45
);

int rand0to1Index = 0;
float next0To1Random()
{
	float r = rand0To1Table[rand0to1Index++];
	if (rand0to1Index == rand0To1Table.length())
		rand0to1Index = 0;
	return r;
}

int rand0to6Index = 0;
float next0To6Random()
{
	float r = rand0to6Table[rand0to6Index++];
	if (rand0to6Index == rand0to6Table.length())
		rand0to6Index = 0;
	return r;
}

void makeItOnce(){

	gl_Position = gl_in[0].gl_Position;

	pvaOut.ecPosition = pva_in[0].ecPosition;
	pvaOut.ecUnitNormal = pva_in[0].ecUnitNormal;
	pvaOut.texCoords = pva_in[0].texCoords;
	EmitVertex();

	gl_Position = gl_in[1].gl_Position;

	pvaOut.ecPosition = pva_in[1].ecPosition;
	pvaOut.ecUnitNormal = pva_in[1].ecUnitNormal;
	pvaOut.texCoords = pva_in[1].texCoords;
	EmitVertex();

	gl_Position = gl_in[2].gl_Position;

	pvaOut.ecPosition = pva_in[2].ecPosition;
	pvaOut.ecUnitNormal = pva_in[2].ecUnitNormal;
	pvaOut.texCoords = pva_in[2].texCoords;
	EmitVertex();
}

void repeat(){

	vec4 shift_vec4;
	vec3 shift_vec3;
	vec2 shift_vec2;
	float shift0, shift1, shift2;

	for (int i=0; i<100; i++){
		shift0 = next0To1Random();
		shift1 = next0To1Random();
		shift2 = next0To1Random();

		shift_vec4 = vec4(shift0, -shift1, shift2, 0.0);
		shift_vec3 = vec3(shift0, -shift1, shift2);
		shift_vec2 = vec2(shift0, -shift1);

		gl_Position = gl_in[0].gl_Position + shift_vec4;

		pvaOut.ecPosition = pva_in[0].ecPosition + shift_vec3;
		pvaOut.ecUnitNormal = pva_in[0].ecUnitNormal + shift_vec3;
		pvaOut.texCoords = pva_in[0].texCoords + shift_vec2;
		EmitVertex();

		gl_Position = gl_in[1].gl_Position + shift_vec4;

		pvaOut.ecPosition = pva_in[1].ecPosition + shift_vec3;
		pvaOut.ecUnitNormal = pva_in[1].ecUnitNormal + shift_vec3;
		pvaOut.texCoords = pva_in[1].texCoords + shift_vec2;
		EmitVertex();

		gl_Position = gl_in[2].gl_Position + shift_vec4;

		pvaOut.ecPosition = pva_in[2].ecPosition + shift_vec3;
		pvaOut.ecUnitNormal = pva_in[2].ecUnitNormal + shift_vec3;
		pvaOut.texCoords = pva_in[2].texCoords + shift_vec2;
		EmitVertex();

		EndPrimitive();
	}
}

void main(){

	if (makeALot == 0) {

		makeItOnce();
	}
	else {
		repeat();
	}

}
