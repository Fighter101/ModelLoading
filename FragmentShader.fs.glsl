#version 330 core
out vec4 color;
in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform vec3 viewPos;

struct Material {
    sampler2D       diffuse_0;
    sampler2D       diffuse_1;
    sampler2D       diffuse_2;
    sampler2D       specular_0;
    sampler2D       specular_2;
    sampler2D       specular_1;
    float           shininess;
    int             numDiffuseTextures;
    int             numSpecularTextures;
};
uniform Material material;
vec4 mixTexD()
{
    vec4 result = vec4(0.0f);
    for (int i=0;i<material.numDiffuseTextures;++i)
    {
        switch(i){
        case 0:
        result=mix(texture(material.diffuse_0,TexCoords),result,0.5);
        break;
        case 1:
        result=mix(texture(material.diffuse_1,TexCoords),result,0.5);
        break;
        case 2:
        result=mix(texture(material.diffuse_2,TexCoords),result,0.5);
        break;
        }
    }
    return result;
}

vec4 mixTexS()
{
    vec4 result=vec4(0.0f);
    for (int i=0;i<material.numDiffuseTextures;++i)
    {
        switch(i){
        case 0:
        result=mix(texture(material.specular_0,TexCoords),result,0.5);
        break;
        case 1:
        result=mix(texture(material.specular_1,TexCoords),result,0.5);
        break;
        case 2:
        result=mix(texture(material.specular_2,TexCoords),result,0.5);
        break;
        }
    }
    return result;
}

///////////////////DirectionalLight//////////////////////
struct DirLight {
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirLight dirLight;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{

    vec3 lightDir = normalize(-light.direction);
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // Combine results
    vec3 ambient  = light.ambient  * vec3(mixTexD());
    vec3 diffuse  = light.diffuse  * diff * vec3(mixTexD());
    vec3 specular = light.specular * spec * vec3(mixTexS());
    return (ambient + diffuse + specular);
}
/////////////////////////////////////////////////////////
//////////////////////PointLight////////////////////////
struct PointLight {
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];
// Calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // Specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    // Attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    // Combine results
    vec3 ambient  = light.ambient  * vec3(mixTexD());
    vec3 diffuse  = light.diffuse  * diff * vec3(mixTexD());
    vec3 specular = light.specular * spec * vec3(mixTexS());
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}
/////////////////////////////////////////////////
//////////////SpotLight//////////////////////////
struct SpotLight
{
    vec3 position;
    vec3 direction;
    float innerCutOff;
    float outerCutOff;
    float constant;
    float linear;
    float quadratic;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform SpotLight spotLight;
vec3 CalcSpotLight(SpotLight light, vec3 normal ,vec3 FragPos,vec3 viewDir)
{
     vec3 lightDir   = normalize(light.position-FragPos);
     float theta     = dot(lightDir, normalize(-light.direction));
     float epsilon   = light.innerCutOff - light.outerCutOff;
     float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

     vec3 ambient    = light.ambient * vec3(mixTexD());

     float distance    = length(light.position - FragPos);
     float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
     //Diffuse
     float diff = max(dot(normal, lightDir), 0.0);
     vec3 diffuse  = light.diffuse *diff* vec3(mixTexD());
     diffuse *= attenuation;
     diffuse *= intensity;
     // Specular
     vec3 reflectDir = reflect(-lightDir, normal);
     float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
     vec3 specular = light.specular *spec* vec3(mixTexS());
     specular *= attenuation;
     specular *=intensity;
     return (ambient + diffuse + specular) ;

}
//////////////////////////////////////////////////

void main()
{
    // Properties
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 result = vec3(0.0f);
    // Phase 1: Directional lighting
    result = CalcDirLight(dirLight, norm, viewDir);
    // Phase 2: Point lights
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
    // Phase 3: Spot light
    result += CalcSpotLight(spotLight, norm, FragPos, viewDir);
    color = vec4(result, 1.0);

}