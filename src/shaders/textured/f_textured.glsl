#version 330

uniform sampler2D textureMap0;

out vec4 pixelColor;

in vec2 iTexCoord0;
in vec4 ic;
in vec4 n;
in vec4 l;
in vec4 v;
in vec3 pos;

vec3 lightDirection = normalize(-vec3(0, 2.0, 0));
vec4 lightPosition = vec4(0.0, 2.0, 0.0, 1.0);
float constant = 1.0;
float linear = 0.22;
float quadratic = 0.20;

vec4 spotlight(vec3 lightPosition, vec3 lightDirection, float constant, float linear, float quadratic) {
    vec3 lightDir = normalize(lightPosition - pos);
    float theta = dot(lightDir, normalize(-lightDirection));
    float epsilon = 0.0001;
    float intensity = clamp((theta - 0.9) / (0.95 - 0.9), 0, 1);
    float distance = length(lightPosition.xyz - pos.xyz);
    float attenuation = 1.0 / (constant + linear * distance +
    quadratic * (distance * distance));
    return vec4(intensity * attenuation, intensity * attenuation, intensity * attenuation, 1.0);
}

void main(void) {
    pixelColor = texture(textureMap0, iTexCoord0);
    vec4 lightColor = spotlight(lightPosition.xyz, lightDirection, constant, linear, quadratic);
    pixelColor = pixelColor * lightColor;
    vec4 ml = normalize(l);
    vec4 mn = normalize(n);
    vec4 mv = normalize(v);
    vec4 mr = reflect(-ml, mn);

    vec4 kd = texture(textureMap0, iTexCoord0) * 0.5;
    vec4 ks = kd;
    float nl = clamp(dot(mn, ml), 0, 1);
    float rv = pow(clamp(dot(mr, mv), 0, 1), 100);
    pixelColor += vec4(kd.rgb * nl, kd.a) + vec4(ks.rgb*rv, 0);
}