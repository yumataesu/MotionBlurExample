#version 410

uniform sampler2D albedoTex;
uniform sampler2D velTex;

uniform float u_velocityScale;

in vec2 v_texcoord;

out vec4 fragColor;

const int MAX_SAMPLES = 64;

void main() {
    
    vec2 texelSize = 1.0 / vec2(textureSize(albedoTex, 0));
    vec2 screenTexCoords = gl_FragCoord.xy * texelSize;
    
    vec2 velocity = texture(velTex, v_texcoord).rg;
    velocity *= u_velocityScale;
    
    float speed = length(velocity / texelSize);
    float nSamples = clamp(int(speed), 1, MAX_SAMPLES);
    
    
    fragColor = texture(albedoTex, v_texcoord);
    
    for (int i = 1; i < nSamples; ++i) {
        vec2 offset = velocity * (float(i) / float(nSamples - 1) - 0.5);
        fragColor += texture(albedoTex, screenTexCoords + offset);
    }
    fragColor /= float(nSamples);
}
