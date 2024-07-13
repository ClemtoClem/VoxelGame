#version 330 core

out vec4 FragColor;

struct DirectionalLight {
    vec3 direction;
    vec3 color;
};

struct PointLight {
    vec3 position;
    vec3 color;
    float constant;
    float linear;
    float quadratic;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    vec3 color;
    float cutOff;
    float outerCutOff;
    float constant;
    float linear;
    float quadratic;
};

#define MAX_POINT_LIGHTS 10
#define MAX_SPOT_LIGHTS 10

uniform vec3 viewPos;
uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

uniform int numPointLights;
uniform int numSpotLights;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D texture1;

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir);
vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main() {
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // Directional light
    vec3 result = CalculateDirectionalLight(directionalLight, norm, viewDir);

    // Point lights
    for(int i = 0; i < numPointLights; ++i) {
        result += CalculatePointLight(pointLights[i], norm, FragPos, viewDir);
    }

    // Spot lights
    for(int i = 0; i < numSpotLights; ++i) {
        result += CalculateSpotLight(spotLights[i], norm, FragPos, viewDir);
    }

    vec4 texColor = texture(texture1, TexCoord);
    FragColor = vec4(result, 1.0) * texColor;
}

// The light calculation functions here
vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec3 ambient = 0.1 * light.color;
    vec3 diffuse = diff * light.color;
    vec3 specular = spec * light.color;
    return (ambient + diffuse + specular);
}

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    vec3 ambient = 0.1 * light.color * attenuation;
    vec3 diffuse = diff * light.color * attenuation;
    vec3 specular = spec * light.color * attenuation;
    return (ambient + diffuse + specular);
}

vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);
    float theta = dot(lightDir, normalize(-light.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    vec3 ambient = 0.1 * light.color * attenuation * intensity;
    vec3 diffuse = diff * light.color * attenuation * intensity;
    vec3 specular = spec * light.color * attenuation * intensity;
    return (ambient + diffuse + specular);
}
