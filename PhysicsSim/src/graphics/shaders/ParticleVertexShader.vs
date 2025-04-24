#version 330 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec4 instancePos;
layout(location = 2) in vec4 instanceColor;
layout(location = 3) in vec4 instanceScale;

uniform mat4 model;
uniform mat4 projection;

out vec3 outColor;

void main()
{
    // Scale the vertex by the instance scale
    vec3 scaledPosition = position * instanceScale.xyz;
    
    // Calculate final position with model matrix
    vec4 worldPos = model * vec4(scaledPosition, 1.0);
    
    // Apply instance position offset
    worldPos.xyz += instancePos.xyz;
    
    // Apply projection
    gl_Position = projection * worldPos;
    
    // Pass color to fragment shader
    outColor = instanceColor.rgb;
}