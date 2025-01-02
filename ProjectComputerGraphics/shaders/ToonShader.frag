#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec3 fragNorm;
layout(location = 2) in vec2 fragUV;

layout(location = 0) out vec4 outColor;

layout(set = 0, binding = 0) uniform GlobalUniformBufferObject {
	vec3 DlightDir;		// direction of the direct light
	vec3 DlightColor;	// color of the direct light
	vec3 AmbLightColor;	// ambient light
	vec3 eyePos;		// position of the viewer
} gubo;

layout(set = 1, binding = 0) uniform UniformBufferObject {
	float visible;
	float amb;
	float gamma;
	vec3 sColor;
	mat4 mvpMat;
	mat4 mMat;
	mat4 nMat;
} ubo;

layout(set = 1, binding = 1) uniform sampler2D tex;

vec3 BRDF(vec3 V, vec3 N, vec3 L, vec3 Md, vec3 Ms, float gamma) {
	//vec3 V  - direction of the viewer
	//vec3 N  - normal vector to the surface
	//vec3 L  - light vector (from the light model)
	//vec3 Md - main color of the surface
	//vec3 Ms - specular color of the surface
	
	float dGradient = 0; float sGradient = 0;
	
	float cosAlpha = clamp(dot(N, L), 0.0, 1.0);
	float cosBeta = clamp(dot(V, -reflect(L, N)), 0.0, 1.0);

	if (cosAlpha <= 0) {
        dGradient = 0.0;
    } else if (cosAlpha > 0 && cosAlpha <= 0.1) {
        dGradient = 0.15 * (cosAlpha / 0.1);
    } else if (cosAlpha > 0.1 && cosAlpha <= 0.7) {
        dGradient = 0.15;
    } else if (cosAlpha > 0.7 && cosAlpha <= 0.8) {
        dGradient = 0.15 + (0.85 * (cosAlpha - 0.7) / 0.1);
    } else { // cosAlpha > 0.8
        dGradient = 1.0;
    }

	/*if(cosBeta<=0.9){
		sGradient = 0;
	}
	if(cosBeta>0.9 && cosBeta<=0.95){
		sGradient = 0.5 * (cosBeta-0.9)/0.05;
	}
	if(cosBeta>0.95){
		sGradient = 0.5;
	}*/



	vec3 Diffuse = Md * dGradient;
	vec3 Specular = Ms * sGradient;
	
	return (Diffuse + Specular);
}

void main() {
	vec3 Norm = normalize(fragNorm);
	vec3 EyeDir = normalize(gubo.eyePos - fragPos);
	
	vec3 lightDir = gubo.DlightDir;
	vec3 lightColor = gubo.DlightColor.rgb;

	vec3 DiffSpec = BRDF(EyeDir, Norm, lightDir, texture(tex, fragUV).rgb, ubo.sColor, ubo.gamma);
	vec3 Ambient = texture(tex, fragUV).rgb * ubo.amb * gubo.AmbLightColor;
	
	outColor = vec4(clamp(0.95 * (DiffSpec) * lightColor.rgb + Ambient,0.0,1.0), 1.0f);
}