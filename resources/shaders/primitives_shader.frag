/**
 * - Make the camera move up and down while still pointing at the cube
 * - Make the camera roll (stay looking at the cube, and don't change the eye point)
 * - Make the camera zoom in and out
 */

#define MAX_MARCHING_STEPS = 255
#define MIN_DIST = 0.0
#define MAX_DIST = 100.0
#define EPSILON = 0.0001

// Maximum number of shapes and lights you expect
#define MAX_SHAPES 10
#define MAX_LIGHTS 5

struct Shape {
    int type;       // 0: Cube, 1: Sphere, 2: Ellipsoid, etc.
    vec3 position;
    vec3 size;
    vec3 rotation;  // Inclinaison en radians
    vec4 color;     // Couleur RGBA
};

struct Light {
    vec3 position;
    vec3 intensity; // Couleur et intensité
    float intensityFactor; // Facteur d'intensité
};

uniform Shape shapes[MAX_SHAPES];
uniform int shapeCount;

uniform Light lights[MAX_LIGHTS];
uniform int lightCount;

/**
 * Signed distance function for a cube centered at the origin
 * with width = height = length = 2.0
 */
float cubeSDF(vec3 p, vec3 size, vec3 rotation) {
    p = p * inverse(rotationMatrix(rotation)); // Applique la rotation inverse
    vec3 d = abs(p) - size * 0.5; // Applique la taille
    float insideDistance = min(max(d.x, max(d.y, d.z)), 0.0);
    float outsideDistance = length(max(d, 0.0));
    return insideDistance + outsideDistance;
}

/**
 * Signed distance function for a sphere centered at the origin with radius 1.0;
 */
float sphereSDF(vec3 p, vec3 size) {
    return length(p / size) - 1.0;
}

/**
 * Signed distance function for an ellipsoid centered at the origin with radii 1.0;
*/
float ellipsoidSDF(vec3 p, vec3 size, vec3 rotation) {
    p = p * inverse(rotationMatrix(rotation)); // Applique la rotation
    return length(p / size) - 1.0;
}


/**
 * Signed distance function describing the scene.
 * 
 * Absolute value of the return value indicates the distance to the surface.
 * Sign indicates whether the point is inside or outside the surface,
 * negative indicating inside.
 */
float sceneSDF(vec3 samplePoint) {
    float minDist = MAX_DIST;

    for (int i = 0; i < shapeCount; i++) {
        vec3 pos = shapes[i].position;
        vec3 size = shapes[i].size;
        vec3 rotation = shapes[i].rotation;

        // Calculer la distance en fonction du type de forme
        float dist;
        if (shapes[i].type == 0) {  // Cube
            dist = cubeSDF(samplePoint - pos, size, rotation);
        } else if (shapes[i].type == 1) {  // Sphere
            dist = sphereSDF(samplePoint - pos, size);
        } else if (shapes[i].type == 2) {  // Ellipsoid
            dist = ellipsoidSDF(samplePoint - pos, size, rotation);
        }

        // Prendre la plus petite distance pour le raymarching
        minDist = min(minDist, dist);
    }

    return minDist;
}


/**
 * Return the shortest distance from the eyepoint to the scene surface along
 * the marching direction. If no part of the surface is found between start and end,
 * return end.
 * 
 * eye: the eye point, acting as the origin of the ray
 * marchingDirection: the normalized direction to march in
 * start: the starting distance away from the eye
 * end: the max distance away from the ey to march before giving up
 */
float shortestDistanceToSurface(vec3 eye, vec3 marchingDirection, float start, float end) {
    float depth = start;
    for (int i = 0; i < MAX_MARCHING_STEPS; i++) {
        float dist = sceneSDF(eye + depth * marchingDirection);
        if (dist < EPSILON) {
			return depth;
        }
        depth += dist;
        if (depth >= end) {
            return end;
        }
    }
    return end;
}
            

/**
 * Return the normalized direction to march in from the eye point for a single pixel.
 * 
 * fieldOfView: vertical field of view in degrees
 * size: resolution of the output image
 * fragCoord: the x,y coordinate of the pixel in the output image
 */
vec3 rayDirection(float fieldOfView, vec2 size, vec2 fragCoord) {
    vec2 xy = fragCoord - size / 2.0;
    float z = size.y / tan(radians(fieldOfView) / 2.0);
    return normalize(vec3(xy, -z));
}

/**
 * Using the gradient of the SDF, estimate the normal on the surface at point p.
 */
vec3 estimateNormal(vec3 p) {
    return normalize(vec3(
        sceneSDF(vec3(p.x + EPSILON, p.y, p.z)) - sceneSDF(vec3(p.x - EPSILON, p.y, p.z)),
        sceneSDF(vec3(p.x, p.y + EPSILON, p.z)) - sceneSDF(vec3(p.x, p.y - EPSILON, p.z)),
        sceneSDF(vec3(p.x, p.y, p.z  + EPSILON)) - sceneSDF(vec3(p.x, p.y, p.z - EPSILON))
    ));
}

/**
 * Lighting contribution of a single point light source via Phong illumination.
 * 
 * The vec3 returned is the RGB color of the light's contribution.
 *
 * k_a: Ambient color
 * k_d: Diffuse color
 * k_s: Specular color
 * alpha: Shininess coefficient
 * p: position of point being lit
 * eye: the position of the camera
 * lightPos: the position of the light
 * lightIntensity: color/intensity of the light
 *
 * See https://en.wikipedia.org/wiki/Phong_reflection_model#Description
 */
vec3 phongContribForLight(vec3 k_d, vec3 k_s, float alpha, vec3 p, vec3 eye,
                          vec3 lightPos, vec3 lightIntensity) {
    vec3 N = estimateNormal(p);
    vec3 L = normalize(lightPos - p);
    vec3 V = normalize(eye - p);
    vec3 R = normalize(reflect(-L, N));
    
    float dotLN = dot(L, N);
    float dotRV = dot(R, V);
    
    if (dotLN < 0.0) {
        // Light not visible from this point on the surface
        return vec3(0.0, 0.0, 0.0);
    } 
    
    if (dotRV < 0.0) {
        // Light reflection in opposite direction as viewer, apply only diffuse
        // component
        return lightIntensity * (k_d * dotLN);
    }
    return lightIntensity * (k_d * dotLN + k_s * pow(dotRV, alpha));
}

/**
 * Lighting via Phong illumination.
 * 
 * The vec3 returned is the RGB color of that point after lighting is applied.
 * k_a: Ambient color
 * k_d: Diffuse color
 * k_s: Specular color
 * alpha: Shininess coefficient
 * p: position of point being lit
 * eye: the position of the camera
 *
 * See https://en.wikipedia.org/wiki/Phong_reflection_model#Description
 */
vec3 phongIllumination(vec3 k_a, vec3 k_d, vec3 k_s, float alpha, vec3 p, vec3 eye) {
    vec3 ambientLight = vec3(0.1, 0.1, 0.1);
    vec3 color = ambientLight * k_a;

    for (int i = 0; i < lightCount; i++) {
        vec3 lightPos = lights[i].position;
        vec3 lightIntensity = lights[i].intensity * lights[i].intensityFactor;

        // Ajoute la contribution de chaque lumière
        color += phongContribForLight(k_d, k_s, alpha, p, eye, lightPos, lightIntensity);
    }

    return color;
}



/**
 * Return a transform matrix that will transform a ray from view space
 * to world coordinates, given the eye point, the camera target, and an up vector.
 *
 * This assumes that the center of the camera is aligned with the negative z axis in
 * view space when calculating the ray marching direction. See rayDirection.
 */
mat4 viewMatrix(vec3 eye, vec3 center, vec3 up) {
    // Based on gluLookAt man page
    vec3 f = normalize(center - eye);
    vec3 s = normalize(cross(f, up));
    vec3 u = cross(s, f);
    return mat4(
        vec4(s, 0.0),
        vec4(u, 0.0),
        vec4(-f, 0.0),
        vec4(0.0, 0.0, 0.0, 1)
    );
}

void mainImage( out vec4 fragColor, in vec2 fragCoord) {
	vec3 viewDir = rayDirection(45.0, iResolution.xy, fragCoord);
    vec3 eye = vec3(8.0, 5.0, 7.0);
    
    mat4 viewToWorld = viewMatrix(eye, vec3(0.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0));
    
    vec3 worldDir = (viewToWorld * vec4(viewDir, 0.0)).xyz;
    
    float dist = shortestDistanceToSurface(eye, worldDir, MIN_DIST, MAX_DIST);
    
    if (dist > MAX_DIST - EPSILON) {
        // Didn't hit anything
        fragColor = vec4(0.0, 0.0, 0.0, 0.0);
		return;
    }
    
    // The closest point on the surface to the eyepoint along the view ray
    vec3 p = eye + dist * worldDir;
    
    vec3 K_a = vec3(0.2, 0.2, 0.2);
    vec3 K_d = vec3(0.7, 0.2, 0.2);
    vec3 K_s = vec3(1.0, 1.0, 1.0);
    float shininess = 10.0;
    
    vec3 color = phongIllumination(K_a, K_d, K_s, shininess, p, eye);
    
    fragColor = vec4(color, 1.0);
}