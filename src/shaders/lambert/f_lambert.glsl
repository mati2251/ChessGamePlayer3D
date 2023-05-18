#version 100

void main()
{
    vec2 position = gl_FragCoord.xy;

    float seed = dot(position, vec2(12.9898, 78.233));

    vec3 starColor = vec3(1.0);

    float flicker = fract(sin(seed) * 43758.5453);
    flicker = pow(flicker, 3.0);
    starColor *= mix(0.8, 1.0, flicker);

    float starSize = 1.0 / length(position - vec2(0.5));
    starSize *= 1.5;

    gl_FragColor = vec4(starColor, 1.0) * starSize;
}