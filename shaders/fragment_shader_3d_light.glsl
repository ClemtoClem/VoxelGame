#version 330 core

out vec4 FragColor;

struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float constant;
    float linear;
    float quadratic;
};

struct SpotLight {
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float cutOff;
    float outerCutOff;
    float constant;
    float linear;
    float quadratic;
};

#define MAX_POINT_LIGHTS 10
#define MAX_SPOT_LIGHTS 10

// Model matrices
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

// Lighting properties
uniform vec3 viewPos;
uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform SpotLight spotLights[MAX_SPOT_LIGHTS];

uniform int numPointLights;
uniform int numSpotLights;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;

// Material properties
struct Material {
    int diffuse;
    int specular;
    int emission;
    float shininess;
};

uniform Material material;

uniform sampler2D texture1;

vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir);
vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main() {
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // Total diffuse and specular components
    vec3 totalDiffuse = vec3(0.0);
    vec3 totalSpecular = vec3(0.0);

    // Directional light
    totalDiffuse += directionalLight.diffuse * max(dot(norm, normalize(-directionalLight.direction)), 0.0);
    vec3 reflectDir = reflect(-normalize(directionalLight.direction), norm);
    totalSpecular += directionalLight.specular * pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    // Point lights
    for(int i = 0; i < numPointLights; ++i) {
        totalDiffuse += CalculatePointLight(pointLights[i], norm, FragPos, viewDir);
        totalSpecular += CalculatePointLight(pointLights[i], norm, FragPos, viewDir);
    }

    // Spot lights
    for(int i = 0; i < numSpotLights; ++i) {
        totalDiffuse += CalculateSpotLight(spotLights[i], norm, FragPos, viewDir);
        totalSpecular += CalculateSpotLight(spotLights[i], norm, FragPos, viewDir);
    }

    // Ambient component
    vec3 ambient = vec3(0.1) * directionalLight.ambient;

    // Combine all lighting components
    vec3 result = ambient + totalDiffuse + totalSpecular;

    // Apply texture
    vec4 texColor = texture(texture1, TexCoord);

    // Final color
    FragColor = vec4(result, 1.0) * texColor;
}

// The light calculation functions here
vec3 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir) {
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    return light.ambient + diff * light.diffuse + spec * light.specular;
}

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    return attenuation * (light.ambient + diff * light.diffuse + spec * light.specular);
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
    return attenuation * intensity * (light.ambient + diff * light.diffuse + spec * light.specular);
}
