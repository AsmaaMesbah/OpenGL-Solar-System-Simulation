#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

// Rotation and zoom
float mercury_rev = 0, mercury_rot = 0, mercury_tilt = 0.034;
float venus_rev = 0, venus_rot = 0, venus_tilt = 177.4;
float earth_rev = 0, earth_rot = 0, earth_tilt = 23.4;
float mars_rev = 0, mars_rot = 0, mars_tilt = 25.2; 
float jupiter_rev = 0, jupiter_rot = 0, jupiter_tilt = 3.1; 
float saturn_rev = 0, saturn_rot = 0, saturn_tilt = 26.7; 
float uranus_rev = 0, uranus_rot = 0, uranus_tilt = 97.8; 
float neptune_rev = 0, neptune_rot = 0, neptune_tilt = 28.3; 
float zoom = 20.0f; // camera zoom
int isPaused = 0;   // pause state 

// Texture for planets 
GLuint space_texture; 
GLuint sun_texture;
GLuint mercury_texture; 
GLuint venus_texture; 
GLuint earth_texture; 
GLuint mars_texture; 
GLuint jupiter_texture; 
GLuint saturn_texture; 
GLuint uranus_texture; 
GLuint neptune_texture;  

// Load uncompressed 24-bit BMP
GLuint loadBMP(const char* filename) {

    // -------------- Usage Checks -----------------
    // opening BMP file 
    FILE* file = fopen(filename, "rb");
    if (!file) {
        printf("Could not open BMP file: %s\n", filename);
        return 0;
    }

    // read header & validate
    unsigned char header[54];
    if (fread(header, 1, 54, file) != 54 || header[0] != 'B' || header[1] != 'M') {
        printf("Invalid BMP file: %s\n", filename);
        fclose(file);
        return 0;
    }

    // check compression
    unsigned int compression = *(unsigned int*)&header[0x1E];
    unsigned short bpp = *(unsigned short*)&header[0x1C];
    if (compression != 0 || bpp != 24) {
        printf("Only uncompressed 24-bit BMP supported.\n");
        fclose(file);
        return 0;
    }

    // ------------- Main Logic -----------------
    // read image info 
    unsigned int dataPos = *(unsigned int*)&header[0x0A];
    unsigned int imageSize = *(unsigned int*)&header[0x22];
    unsigned int width = *(unsigned int*)&header[0x12];
    unsigned int height = *(unsigned int*)&header[0x16];
    if (imageSize == 0) imageSize = ((width * 3 + 3) & ~3) * height;
    if (dataPos == 0) dataPos = 54;

    unsigned char* data = (unsigned char*)malloc(imageSize);
    fseek(file, dataPos, SEEK_SET);
    fread(data, 1, imageSize, file);
    fclose(file);

    // generate texture 
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
    free(data);

    return textureID;
}

void drawPlanet(float rev_angle, float rot_angle, float tilt_angle, float distance, float radius, GLuint textureID) {
    glPushMatrix();

    glRotatef(rev_angle, 0.0, 1.0, 0.0);        // orbit around sun
    glTranslatef(distance, 0.0, 0.0);           // distance from sun
    glRotatef(tilt_angle, 0.0, 0.0, 1.0);       // axial tilt
    glRotatef(rot_angle, 0.0, 1.0, 0.0);        // rotation on tilted axis

    glEnable(GL_TEXTURE_2D); 
    glBindTexture(GL_TEXTURE_2D, textureID); 

    float specular[] = { 0.1, 0.1, 0.1, 1.0 };
    float emission[] = { 0.0, 0.0, 0.0, 1.0 };
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, emission);
    glMaterialf(GL_FRONT, GL_SHININESS, 30.0);


    GLUquadric* quad = gluNewQuadric(); 
    gluQuadricTexture(quad, GL_TRUE); 
    gluQuadricNormals(quad, GLU_SMOOTH); 
    gluSphere(quad, radius, 30, 30); 
    gluDeleteQuadric(quad); 

    glDisable(GL_TEXTURE_2D); 
    glPopMatrix();
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, zoom, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    // Space
    glDisable(GL_LIGHTING); 
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, space_texture); 

    GLUquadric* sky = gluNewQuadric(); 
    gluQuadricTexture(sky, GL_TRUE); 
    gluQuadricNormals(sky, GLU_SMOOTH);

    glPushMatrix(); 
    glScalef(-1, 1, 1); // flip normals
    gluSphere(sky, 90.0, 50, 50); // huge sphere
    glPopMatrix(); 

    gluDeleteQuadric(sky); 
    glEnable(GL_LIGHTING); 

    // Draw textured sun
    glBindTexture(GL_TEXTURE_2D, sun_texture);
    GLUquadric* quad = gluNewQuadric();
    gluQuadricTexture(quad, GL_TRUE);
    gluQuadricNormals(quad, GLU_SMOOTH);

    float sun_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    float sun_specular[] = { 1.0, 1.0, 0.0, 1.0 };
    float sun_emission[] = { 0.6, 0.6, 0.6, 1.0 };
    glMaterialfv(GL_FRONT, GL_DIFFUSE, sun_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, sun_specular);
    glMaterialfv(GL_FRONT, GL_EMISSION, sun_emission);
    glMaterialf(GL_FRONT, GL_SHININESS, 10.0);

    gluSphere(quad, 1, 50, 50);
    gluDeleteQuadric(quad);
    glDisable(GL_TEXTURE_2D);

    drawPlanet(mercury_rev, mercury_rot, mercury_tilt, 2.0f, 0.19f, mercury_texture);
    drawPlanet(venus_rev  , venus_rot  , venus_tilt  , 4.0f, 0.47f, venus_texture);
    drawPlanet(earth_rev  , earth_rot  , earth_tilt  , 6.0f, 0.50f, earth_texture);
    drawPlanet(mars_rev   , mars_rot   , mars_tilt   , 8.0f, 0.27f, mars_texture);
    drawPlanet(jupiter_rev, jupiter_rot, jupiter_tilt, 11.0f, 0.9f, jupiter_texture); 
    drawPlanet(saturn_rev , saturn_rot , saturn_tilt , 13.0f, 0.7f, saturn_texture); 
    drawPlanet(uranus_rev , uranus_rot , uranus_tilt , 15.0f, 0.65f, uranus_texture); 
    drawPlanet(neptune_rev, neptune_rot, neptune_tilt, 17.0f, 0.6f, neptune_texture); 

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int value) {
    if (!isPaused) {
        mercury_rev += 1.59f; if (mercury_rev >= 360) mercury_rev -= 360;
        mercury_rot += 58.8f; if (mercury_rot >= 360) mercury_rot -= 360;
        venus_rev += 1.18f; if (venus_rev >= 360) venus_rev -= 360;
        venus_rot += 244.0f; if (venus_rot >= 360) venus_rot -= 360;
        earth_rev += 1.0f; if (earth_rev >= 360) earth_rev -= 360; 
        earth_rot += 1.0f; if (earth_rot >= 360) earth_rot -= 360; 
        mars_rev += 0.808f; if (mars_rev >= 360) mars_rev -= 360; 
        mars_rot += 1.03f; if (mars_rot >= 360) mars_rot -= 360; 
        jupiter_rev += 0.439f; if (jupiter_rev >= 360) jupiter_rev -= 360;
        jupiter_rot += 0.415f; if (jupiter_rot >= 360) jupiter_rot -= 360;
        saturn_rev += 0.325f; if (saturn_rev >= 360) saturn_rev -= 360;
        saturn_rot += 0.445f; if (saturn_rot >= 360) saturn_rot -= 360;
        uranus_rev += 0.228f; if (uranus_rev >= 360) uranus_rev -= 360;
        uranus_rot += 0.720f; if (uranus_rot >= 360) uranus_rot -= 360;
        neptune_rev += 0.182f; if (neptune_rev >= 360) neptune_rev -= 360;
        neptune_rot += 0.673f; if (neptune_rot >= 360) neptune_rot -= 360;
    }
    glutPostRedisplay();
    glutTimerFunc(33, timer, 0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case '+': case '=':
        zoom -= 1.0f; if (zoom < 5.0f) zoom = 5.0f; 
        break;
    case '-': case '_':
        zoom += 1.0f; if (zoom > 100.0f) zoom = 100.0f; break;
    case ' ':
        isPaused = !isPaused; break;
    case 27:
        exit(0);
    }
    glutPostRedisplay();
}

void init(void) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    float light_pos[] = { 0.0, 0.0, 0.0, 1.0 };
    float ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    float diffuse[] = { 0.6, 0.6, 0.6, 1.0 };
    float specular[] = { 1.0, 1.0, 0.5, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glEnable(GL_NORMALIZE);

    glEnable(GL_TEXTURE_2D);
    sun_texture = loadBMP("../img/sunTexture.bmp");
    mercury_texture = loadBMP("../img/mercuryTexture.bmp"); 
    earth_texture = loadBMP("../img/earthTexture.bmp"); 
    venus_texture = loadBMP("../img/venusTexture.bmp"); 
    mars_texture = loadBMP("../img/marsTexture.bmp"); 
    jupiter_texture = loadBMP("../img/jupiterTexture.bmp"); 
    saturn_texture = loadBMP("../img/saturnTexture.bmp");
    uranus_texture = loadBMP("../img/uranusTexture.bmp"); 
    neptune_texture = loadBMP("../img/neptuneTexture.bmp"); 
    space_texture = loadBMP("../img/space.bmp"); 

    printf("Controls:\n");
    printf("  [+] or [=] : Zoom in\n");
    printf("  [-] or [_] : Zoom out\n");
    printf("  [Space]    : Pause / Resume animation\n");
    printf("  [ESC]      : Exit program\n");
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(1600, 900);
    glutCreateWindow("Solar System Simulation");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
