const char* vertexShaderCode =
"#version 430\r\n"
""
"in layout(location=0) vec3 position;"
"in layout(location=1) vec3 vertexColor;"
"in layout(location=2) mat4 fullTransform;"
"in layout(location=6) vec3 normal;"
//"uniform vec3 mainColor;"
//"uniform float yFlip;"
"uniform mat4 TransformMatrix;"
"uniform mat4 ModelToWorldTransformMatrix;"

"out vec3 fragColor;"
"out vec3 theNormal;"
"out vec3 thePosition;"

"void main()"
""
"{"
"vec4 v = vec4(position,1.0f);"
"gl_Position = fullTransform * v;"
//"gl_Position.y *= yFlip;"
"fragColor = vertexColor;"
"theNormal = vec3(ModelToWorldTransformMatrix * vec4(normal,0));"
"thePosition = vec3(ModelToWorldTransformMatrix * v);"
"}";

const char* fragmentShaderCode =
"#version 430\r\n"
""
"in vec3 fragColor;"
"in vec3 theNormal;"
"in vec3 thePosition;"
"uniform vec3 cameraEyePosition;"
"uniform vec3 lightPosition;"
"uniform vec3 ambientLight;"
"out vec4 myColor;"
"void main()"
""
"{"
//difuse light
"vec3 lightVector = normalize(lightPosition - thePosition);"
"float brightness = dot(lightVector, normalize(theNormal));"
"vec4 difuselight = vec4(brightness,brightness,brightness,1);"
//specular light
"vec3 reflectedLightVector = reflect(-lightVector, normalize(theNormal));"
"vec3 cameraEyeVector = normalize(cameraEyePosition - thePosition);"
"float s = clamp(dot(reflectedLightVector,cameraEyeVector),0,1);"
"s = pow(s,3);"
"vec4 specularLight = vec4(s,s,s,1);"
//light attenuation = 1.0f/(Kc + Kl * d + Kq * d^2)
"float Kc = 1.0f;"//constant
"float Kl = 0.07f;"//linear
"float Kq = 0.017f;"//quadratic
"float distance = length(lightPosition - thePosition);"
"float attenuation = 1.0f/(Kc + Kl * distance + Kq * (distance*distance));"
//add ambient difuse and specular light together with attenuation
"specularLight *= attenuation;"
"myColor = vec4(ambientLight*fragColor,1) + clamp(difuselight*vec4(fragColor,1),0.0f,1.0f) + specularLight;"
"}";