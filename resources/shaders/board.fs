#version 330 core
out vec4 FragColor;

struct Material{
    sampler2D diffuse;//tekstura
    vec3 specular;
    float shininess;
};

struct Light{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec2 TexCoords;
in vec3 Normal;


uniform Material material;
uniform Light light;
uniform vec3 viewPos;

void main()
{

    //ambijentalna komponenta
    vec3 ambient=light.ambient*texture(material.diffuse, TexCoords).rgb;

    //difuzna
    //za sad samo difuzna mapa
    vec3 norm=normalize(Normal);
    //pravac svetla=pozicija svetla-pozicija fragmenta
    vec3 lightDir=normalize(light.position-FragPos);
    float diff=max(dot(norm, lightDir), 0.0);
    vec3 diffuse=light.diffuse*diff*texture(material.diffuse, TexCoords).rgb;

    //spekularna
    float specStrength=0.5;
    vec3 viewDirection=normalize(viewPos-FragPos);
    vec3 reflectDirection=reflect(-lightDir, norm);
    float spec=pow(max(dot(viewDirection, reflectDirection), 0.0), material.shininess);
    vec3 specular=light.specular*(spec*material.specular);

    //rezultat
    vec3 result=diffuse+specular+ambient;
    FragColor=vec4(result, 1.0);
}

