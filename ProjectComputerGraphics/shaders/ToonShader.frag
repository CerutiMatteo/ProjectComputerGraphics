#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec3 fragNorm;
layout(location = 2) in vec2 fragUV;

layout(location = 0) out vec4 outColor;

layout(set = 0, binding = 0) uniform GlobalUniformBufferObject {
    vec3 PointlightDir[6];
    vec3 PointlightPos[6];
    vec4 PointlightColor[6];
    vec3 DlightDir;
    vec4 DlightColor;
    vec3 AmbLightColor;
    vec3 eyePos;
    vec3 pointLightsOn; 
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

vec3 compute_point_light_dir(vec3 pos, int i) {
    return normalize(gubo.PointlightPos[i] - pos);
}

vec3 compute_point_light_color(vec3 pos, int i) {
    float distance = length(gubo.PointlightPos[i] - pos);
    float g = gubo.PointlightColor[i].a;                //distance which it the light reduction is 1
    float b = 2.0f;                                     //decay factor
    float attenuation = pow(g / distance, b);
    return gubo.PointlightColor[i].rgb * attenuation;
}

vec3 BRDF(vec3 V, vec3 N, vec3 L, vec3 Md, vec3 Ms, float gamma, bool isLamp) {
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

   

	vec3 Diffuse = Md * dGradient;
	
	return Diffuse;
}

void main() {
    bool isLamp = false;
    vec3 Norm = normalize(fragNorm);
    vec3 EyeDir = normalize(gubo.eyePos - fragPos);
    vec3 FinalColor = vec3(0);

    vec3 dirLightDir = gubo.DlightDir;
    FinalColor += BRDF(EyeDir, Norm, dirLightDir, texture(tex, fragUV).rgb, ubo.sColor, ubo.gamma, isLamp) * gubo.DlightColor.rgb;

    for (int i = 0; i < 6; i++) {
        if(gubo.pointLightsOn.x>0){
            isLamp = true;
            vec3 pointLightDir = compute_point_light_dir(fragPos, i);
            vec3 pointLightColor = compute_point_light_color(fragPos, i);
            FinalColor += BRDF(EyeDir, Norm, pointLightDir, texture(tex, fragUV).rgb, ubo.sColor, ubo.gamma, isLamp) * pointLightColor;
        }
    }

    vec3 ambientLight = texture(tex, fragUV).rgb * ubo.amb * gubo.AmbLightColor;
    FinalColor += ambientLight;

    outColor = vec4(FinalColor, 1.0);
}
