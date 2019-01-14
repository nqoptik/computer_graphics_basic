#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>

#ifdef __linux__
#include <GL/glut.h>
#else
#include <glut.h>
#endif

GLuint texTure[29];

float const PI = 3.14159;

int jetEnable = 1;

float blobX = -50;
float jetSpeed = 1.31;
float zoom = 1;
float eyeX = 4000;
float eyeY = 150;
float eyeZ = 15000;
float centerX = 4000;
float centerY = 150;
float centerZ = 14000;
float upX = 0;
float upY = 1;
float upZ = 0;
float eyeStep = 30;
float angleXZ = 0;
float angleY = 0;
float angleStep = PI / (120 - eyeStep);

GLuint loadTexture(std::string fileName, int width, int height);
void getTextures(void);
void initial(void);
void display(void);
void spinDisplay(void);
void timer(int n);
void reshape(int width, int height);
void special(int key, int x, int y);
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);

void ground(void);
void building(void);
void buildingGround(void);
void buildingTrees(void);
void buildingFloor(void);
void hallFloor(void);
void rooms(void);
void backPorch(void);
void vestibule(void);
void vestibulePanes(void);
void vestibulePillars(void);
void stairSpace();
void buildingCeiling(void);

void upToDownSquareFace(float x, float z, float xrepeat, float zrepeat, int tex);
void downToUpSquareFace(float x, float z, float xrepeat, float zrepeat, int tex);
void frontToBackSquareFace(float x, float y, float xrepeat, float yrepeat, int tex);
void backToFrontSquareFace(float x, float y, float xrepeat, float yrepeat, int tex);
void rightToLeftSquareFace(float y, float z, float yrepeat, float zrepeat, int tex);
void leftToRightSquareFace(float y, float z, float yrepeat, float zrepeat, int tex);
void innerBox(float x, float y, float z, float xrepeat, float yrepeat, float zrepeat, int left, int right, int back, int front, int under, int upper);
void outerBox(float x, float y, float z, float xrepeat, float yrepeat, float zrepeat, int left, int right, int back, int front, int under, int upper);
void verticalCylinder(float baseRadius, float topRadius, float height, float xzrepeat, float yrepeat, int xzsplit, int ysplit, int tex);
void verticalSphere(float radius, float xzrepeat, float yrepeat, int xzsplit, int ysplit, int tex);
void horizonalDisk(float innerRadius, float outerRadius, float xrepeat, float zrepeat, int xzsplit, int ysplit, int tex);
void partialHorizonalDisk(float innerRadius, float outerRadius, float startAngle, float sweepAngle, float xrepeat, float zrepeat, int xzsplit, int ysplit, int tex);

void roomFrame(void);
void eaves(void);
void corridor(void);
void smallPillar(void);
void bigPillar(void);
void roomPillars(void);
void leftFrontHandrail(void);
void rightFrontHandrail(void);
void edgeHandrail(void);
void window(void);
void door(void);
void room(std::string type);
void covered(void);
void backPorchPillars(void);

void centerGround(void);
void centerGrass(void);
void stone(void);
void flags(void);
void centerSmallTrees(void);
void centerBigTrees(void);
void centerTrees(void);
void dam(void);
void waterspout();
void jet(void);
void jets(void);
void center(void);

void flag(void);
void smallTree(float baseRadius, float topRadius, float height, float radius, float rindrepeat, float xzleavesrepeat, float yleavesrepeat);
void bigTree(float baseRadius, float rindheight, float rindrepeat, float rootheight, float radius, int canopy, float xzleavesrepeat, float yleavesrepeat, int tex);

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1360, 700);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("hust_map");
    getTextures();
    initial();
    glutDisplayFunc(display);
    timer(5);
    glutReshapeFunc(reshape);
    glutSpecialFunc(special);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}

GLuint loadTexture(std::string fileName, int width, int height) {
    GLuint texTure;
    unsigned char* data;
    FILE* file = fopen(fileName.c_str(), "rb");

    if (file == NULL) {
        printf("File Not Found : %s.\n", fileName.c_str());
        return 0;
    }

    fseek(file, 54, SEEK_CUR);
    data = (unsigned char*)malloc(width * height * 3);
    if (fread(data, width * height * 3, 1, file) != 1) {
        printf("Faied to read data.\n");
    }
    fclose(file);

    for (int i = 0; i < width * height; ++i) {
        int index = i * 3;
        unsigned char B, R;
        B = data[index];
        R = data[index + 2];
        data[index] = R;
        data[index + 2] = B;
    }

    glGenTextures(1, &texTure);
    glBindTexture(GL_TEXTURE_2D, texTure);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  //clamp: kh�ng ve them
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glEnable(GL_TEXTURE_2D);
    free(data);
    return texTure;
}

void getTextures(void) {
    texTure[0] = loadTexture("textures/grass2.bmp", 1296, 1296);
    texTure[1] = loadTexture("textures/dam.bmp", 479, 144);
    texTure[2] = loadTexture("textures/leaves.bmp", 500, 369);
    texTure[3] = loadTexture("textures/rind.bmp", 259, 194);
    texTure[4] = loadTexture("textures/dambed.bmp", 706, 557);
    texTure[5] = loadTexture("textures/flag.bmp", 1024, 768);
    texTure[6] = loadTexture("textures/lamp.bmp", 200, 200);
    texTure[7] = loadTexture("textures/stair.bmp", 472, 469);
    texTure[8] = loadTexture("textures/roadbed.bmp", 640, 480);
    texTure[9] = loadTexture("textures/lampbed.bmp", 200, 200);
    texTure[10] = loadTexture("textures/stone2.bmp", 503, 334);
    texTure[11] = loadTexture("textures/stone_.bmp", 500, 502);
    texTure[12] = loadTexture("textures/brick.bmp", 604, 606);
    texTure[13] = loadTexture("textures/brick2.bmp", 488, 490);
    texTure[14] = loadTexture("textures/waterdam.bmp", 256, 256);
    texTure[15] = loadTexture("textures/blob.bmp", 69, 69);
    texTure[16] = loadTexture("textures/window.bmp", 520, 319);
    texTure[17] = loadTexture("textures/door.bmp", 254, 367);
    texTure[18] = loadTexture("textures/baluster.bmp", 100, 100);
    texTure[19] = loadTexture("textures/logo.bmp", 183, 275);
    texTure[20] = loadTexture("textures/cloud.bmp", 189, 115);
    texTure[21] = loadTexture("textures/sky.bmp", 387, 195);
    texTure[22] = loadTexture("textures/leaves2.bmp", 960, 720);
    texTure[23] = loadTexture("textures/wall.bmp", 260, 227);
    texTure[24] = loadTexture("textures/dambed2.bmp", 448, 448);
    texTure[25] = loadTexture("textures/pillar2.bmp", 1024, 1024);
    texTure[26] = loadTexture("textures/wall3.bmp", 900, 1234);
    texTure[27] = loadTexture("textures/grass.bmp", 712, 409);
    texTure[28] = loadTexture("textures/leaves3.bmp", 1600, 1600);
}

void initial(void) {
    glClearColor(0.1, 0.6, 1.0, 0.0);
    glEnable(GL_DEPTH_TEST);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    ground();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1000, 230, 2000);
    building();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(800, 0, 5000);
    center();
    glPopMatrix();

    glutSwapBuffers();
}

void spinDisplay(void) {
    if (jetEnable == 1)
        blobX += jetSpeed;

    if (blobX > 400)
        blobX = -30;
    glutPostRedisplay();
}

void timer(int n) {
    spinDisplay();
    glutTimerFunc(n, timer, n);
}

void reshape(int width, int height) {
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1 / zoom, 1 / zoom, -0.8 / zoom, 0.8 / zoom, 1, 100000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
}

void special(int key, int x, int y) {
    float dxyz = sqrt((centerZ - eyeZ) * (centerZ - eyeZ) + (centerX - eyeX) * (centerX - eyeX) + (centerY - eyeY) * (centerY - eyeY));
    printf("%3.2f\n", dxyz);
    float d0xz = sqrt((centerZ - eyeZ) * (centerZ - eyeZ) + (centerX - eyeX) * (centerX - eyeX));

    switch (key) {
        case GLUT_KEY_F8: {
            eyeX = 4000;
            eyeY = 2500;
            eyeZ = -1000;
            centerX = 4000;
            centerY = 2400;
            centerZ = 0;
            upX = 0;
            upY = 1;
            upZ = 0;
            angleXZ = PI;
        } break;
        case GLUT_KEY_F9: {
            eyeX = 4000;
            eyeY = 150;
            eyeZ = 15000;
            centerX = 4000;
            centerY = 150;
            centerZ = 14000;
            upX = 0;
            upY = 1;
            upZ = 0;
            angleXZ = 0;
        } break;
        case GLUT_KEY_LEFT: {
            angleXZ += angleStep;
            centerX = eyeX - d0xz * sinf(angleXZ);
            centerZ = eyeZ - d0xz * cosf(angleXZ);
        } break;
        case GLUT_KEY_RIGHT: {
            angleXZ -= angleStep;
            centerX = eyeX - d0xz * sinf(angleXZ);
            centerZ = eyeZ - d0xz * cosf(angleXZ);
        } break;
        case GLUT_KEY_DOWN: {
            if (angleY > -PI / 3) {
                angleY -= angleStep;
                float d1xz = dxyz * cosf(angleY);
                centerY = eyeY + dxyz * sinf(angleY);
                centerX = eyeX - d1xz * sinf(angleXZ);
                centerZ = eyeZ - d1xz * cosf(angleXZ);
            }
        } break;
        case GLUT_KEY_UP: {
            if (angleY < PI / 3) {
                angleY += angleStep;
                float d1xz = dxyz * cosf(angleY);
                centerY = eyeY + dxyz * sinf(angleY);
                centerX = eyeX - d1xz * sinf(angleXZ);
                centerZ = eyeZ - d1xz * cosf(angleXZ);
            }
        } break;
        case GLUT_KEY_HOME: {
            if (jetSpeed < 15)
                jetSpeed += 0.1;
        } break;
        case GLUT_KEY_END: {
            if (jetSpeed > 0.5)
                jetSpeed -= 0.1;
        } break;
        default:
            break;
    }

    if (angleXZ > 2 * PI)
        angleXZ = 0;
    if (angleXZ < -2 * PI)
        angleXZ = 0;

    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    float cos = (eyeZ - centerZ) / sqrt((centerZ - eyeZ) * (centerZ - eyeZ) + (centerX - eyeX) * (centerX - eyeX));
    float sin = (centerX - eyeX) / sqrt((centerZ - eyeZ) * (centerZ - eyeZ) + (centerX - eyeX) * (centerX - eyeX));

    switch (key) {
        case 'a': {
            eyeX -= eyeStep * cos;
            eyeZ -= eyeStep * sin;
            centerX -= eyeStep * cos;
            centerZ -= eyeStep * sin;
        } break;
        case 'd': {
            eyeX += eyeStep * cos;
            eyeZ += eyeStep * sin;
            centerX += eyeStep * cos;
            centerZ += eyeStep * sin;
        } break;
        case 'w': {
            eyeX += eyeStep * sin;
            eyeZ -= eyeStep * cos;
            centerX += eyeStep * sin;
            centerZ -= eyeStep * cos;
        } break;
        case 's': {
            eyeX -= eyeStep * sin;
            eyeZ += eyeStep * cos;
            centerX -= eyeStep * sin;
            centerZ += eyeStep * cos;
        } break;
        case 'r': {
            eyeY += eyeStep;
            centerY += eyeStep;
        } break;
        case 'f': {
            eyeY -= eyeStep;
            centerY -= eyeStep;
        } break;
        case '+': {
            if (eyeStep < 100) {
                eyeStep += 5;
                angleStep = PI / (120 - eyeStep);
            }
        } break;
        case '-': {
            if (eyeStep > 5) {
                eyeStep -= 5;
                angleStep = PI / (220 - 2 * eyeStep);
            }
        } break;

        default:
            break;
    }

    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
    glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
    switch (button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN) {
                jetEnable = 1 - jetEnable;
            }
            break;
        case GLUT_RIGHT_BUTTON:
            if (state == GLUT_DOWN) {
                if (zoom < 4) {
                    zoom *= 2;
                } else
                    zoom = 1;

                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                glFrustum(-1 / zoom, 1 / zoom, -0.8 / zoom, 0.8 / zoom, 1, 100000);
                glMatrixMode(GL_MODELVIEW);
            }
            break;
        case GLUT_MIDDLE_BUTTON:
            if (state == GLUT_DOWN) {
                zoom = 1;

                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                glFrustum(-1 / zoom, 1 / zoom, -0.8 / zoom, 0.8 / zoom, 1, 100000);
                glMatrixMode(GL_MODELVIEW);
            }
            break;
        default:
            break;
    }

    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, centerX, centerY, centerZ, upX, upY, upZ);
    glutPostRedisplay();
}

void ground(void) {
    glPushMatrix();
    upToDownSquareFace(8000, 16500, 80, 165, 8);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 3960);
    outerBox(200, 10, 12340, 1, 0.05, 61.7, 0, 0, 0, 0, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(7800, 0, 3960);
    outerBox(200, 10, 12340, 1, 0.05, 61.7, 0, 0, 0, 0, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 16300);
    outerBox(8000, 10, 200, 40, 0.05, 1, 0, 0, 0, 0, 0, 0);
    glPopMatrix();
}

void building(void) {
    glPushMatrix();
    buildingGround();
    glPopMatrix();

    glPushMatrix();
    buildingTrees();
    glPopMatrix();

    glPushMatrix();
    buildingFloor();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2300, 0, -500);
    hallFloor();
    glPopMatrix();

    glPushMatrix();
    rooms();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2300, 0, -500);
    backPorch();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2400, 0, 600);
    vestibule();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3600, 0, 600);
    stairSpace();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-50, 1390, -50);
    buildingCeiling();
    glPopMatrix();
}

void buildingGround(void) {
    glPushMatrix();
    glTranslatef(-1000, -230, -2000);
    outerBox(8000, 150, 3800, 160, 2.4, 76, 1, 1, 1, 1, 1, 24);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1000, -80, -2000);
    outerBox(8000, 10, 200, 40, 0.05, 1, 0, 0, 0, 0, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1000, -80, -1800);
    outerBox(200, 10, 3600, 1, 0.05, 18, 0, 0, 0, 0, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6800, -80, -1800);
    outerBox(200, 10, 3600, 1, 0.05, 18, 0, 0, 0, 0, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, -80, 750);
    outerBox(850, 10, 1050, 4.25, 0.05, 5.25, 0, 0, 0, 0, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1550, -80, 750);
    outerBox(600, 10, 1050, 3, 0.05, 5.25, 0, 0, 0, 0, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4150, -80, 750);
    outerBox(600, 10, 1050, 3, 0.05, 5.25, 0, 0, 0, 0, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5450, -80, 750);
    outerBox(550, 10, 1050, 2.75, 0.05, 5.25, 0, 0, 0, 0, 0, 0);
    glPopMatrix();

    glPushMatrix();
    for (int i = 1; i < 5; i++) {
        glPushMatrix();
        glTranslatef(-1000, -110 - 30 * i, 1800);
        outerBox(8000, 30, 40 * i, 160, 0.6, 0.8 * i, 1, 1, 1, 1, 1, 24);
        glPopMatrix();
    }
    glPopMatrix();
}

void buildingTrees(void) {
    glPushMatrix();
    glTranslatef(425, -70, 1275);
    bigTree(35, 800, 4, 200, 300, 6, 5, 2, 28);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1850, -70, 1275);
    smallTree(25, 12, 190, 150, 2, 5, 2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4450, -70, 1275);
    smallTree(25, 12, 190, 150, 2, 5, 2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5725, -70, 1275);
    bigTree(35, 800, 4, 200, 300, 6, 5, 2, 28);
    glPopMatrix();
}

void buildingFloor(void) {
    glPushMatrix();
    glTranslatef(0, -230, 0);
    outerBox(6000, 230, 600, 120, 4.6, 12, 12, 12, 12, 12, 1, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2300, -20, -500);
    outerBox(1400, 20, 500, 28, 0.4, 10, 1, 1, 1, 1, 1, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2300, -20, 600);
    outerBox(1700, 20, 500, 34, 0.4, 10, 1, 1, 1, 1, 1, 20);
    glPopMatrix();

    for (int i = 1; i < 3; i++) {
        glPushMatrix();
        glTranslatef(2300 - 50 * i, -20 - 30 * i, -500 - 40 * i);
        outerBox(1400 + 100 * i, 30, 500 + 40 * i, 28 + 2 * i, 0.6, 10 + 0.8 * i, 1, 1, 1, 1, 1, 24);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(2300 - 50 * i, -20 - 30 * i, 600);
        outerBox(1700 + 100 * i, 30, 500 + 40 * i, 34 + 2 * i, 0.6, 10 + 0.8 * i, 1, 1, 1, 1, 1, 24);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(900, -20 - 30 * i, 600);
        outerBox(600, 30, 40 * i, 12, 0.6, 0.8 * i, 1, 1, 1, 1, 1, 24);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(4800, -20 - 30 * i, 600);
        outerBox(600, 30, 40 * i, 12, 0.6, 0.8 * i, 1, 1, 1, 1, 1, 24);
        glPopMatrix();
    }
}

void hallFloor(void) {
    glPushMatrix();
    outerBox(1400, 10, 1100, 28, 0.2, 22, 1, 1, 1, 1, 1, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 1100);
    outerBox(1700, 10, 500, 34, 0.2, 10, 1, 1, 1, 1, 1, 20);
    glPopMatrix();
}

void rooms(void) {
    glPushMatrix();
    room("leftedge");
    glPopMatrix();

    glPushMatrix();
    glTranslatef(600, 0, 0);
    room("righthiden");
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1200, 0, 0);
    room("lefthiden");
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1800, 0, 0);
    room("on");
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3600, 0, 0);
    room("lefthiden");
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4200, 0, 0);
    room("on");
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4800, 0, 0);
    room("allhiden");
    glPopMatrix();

    glPushMatrix();
    glTranslatef(600 * 9, 0, 0);
    room("rightedge");
    glPopMatrix();

    glPushMatrix();
    for (int i = 1; i < 4; i++) {
        glPushMatrix();
        glTranslatef(0, 350 * i, 0);
        room("leftedge");
        glPopMatrix();

        glPushMatrix();
        for (int j = 1; j < 4; j++) {
            glPushMatrix();
            glTranslatef(600 * j, 350 * i, 0);
            room("on");
            glPopMatrix();
        }
        glPopMatrix();

        glPushMatrix();
        for (int j = 4; j < 6; j++) {
            glPushMatrix();
            glTranslatef(600 * j, 350 * i, 0);
            room("allhiden");
            glPopMatrix();
        }
        glPopMatrix();

        glPushMatrix();
        glTranslatef(600 * 6, 350 * i, 0);
        room("lefthiden");
        glPopMatrix();

        glPushMatrix();
        for (int j = 7; j < 9; j++) {
            glPushMatrix();
            glTranslatef(600 * j, 350 * i, 0);
            room("on");
            glPopMatrix();
        }
        glPopMatrix();

        glPushMatrix();
        glTranslatef(600 * 9, 350 * i, 0);
        room("rightedge");
        glPopMatrix();
    }
    glPopMatrix();

    glPushMatrix();
    for (int k = 0; k < 2; k++) {
        glPushMatrix();
        glTranslatef(2400, 0, 570 * k);
        smallPillar();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(2970, 0, 570 * k);
        bigPillar();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(3570, 0, 570 * k);
        smallPillar();
        glPopMatrix();
    }
    glPopMatrix();
}

void backPorch(void) {
    glPushMatrix();
    glTranslatef(0, 340, 0);
    outerBox(1400, 20, 1100, 28, 0.4, 22, 12, 12, 12, 12, 26, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(670, 0, 470);
    backPorchPillars();
    glPopMatrix();
}

void vestibule(void) {
    glPushMatrix();
    glTranslated(0, 350, 0);
    vestibulePanes();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(570, 0, 0);
    vestibulePillars();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-100, 340, 0);
    covered();
    glPopMatrix();
}
void vestibulePanes(void) {
    glPushMatrix();
    outerBox(1200, 1050, 400, 24, 21, 8, 23, 23, 23, 23, 26, 23);
    glPopMatrix();

    glPushMatrix();
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            glPushMatrix();
            glTranslatef(50 + 400 * i, 25 + 350 * j, 405);
            frontToBackSquareFace(300, 300, 1, 1, 18);
            glPopMatrix();
        }
    }
    glPopMatrix();

    glPushMatrix();
    glTranslatef(475, 300, 410);
    frontToBackSquareFace(250, 450, 1, 1, 19);
    glPopMatrix();
}

void vestibulePillars(void) {
    glPushMatrix();
    bigPillar();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-570, 0, 370);
    smallPillar();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(600, 0, 370);
    smallPillar();
    glPopMatrix();
}

void stairSpace() {
    glPushMatrix();
    outerBox(300, 1400, 400, 6, 28, 8, 23, 23, 23, 23, 23, 23);
    glPopMatrix();

    glPushMatrix();
    for (int j = 0; j < 4; j++) {
        glPushMatrix();
        glTranslatef(303, 25 + 350 * j, 50);
        rightToLeftSquareFace(300, 300, 1, 1, 18);
        glPopMatrix();
    }
    glPopMatrix();
}

void buildingCeiling(void) {
    glPushMatrix();
    outerBox(6100, 20, 700, 122, 0.4, 14, 12, 12, 12, 12, 26, 23);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2400, 0, 650);
    outerBox(1600, 20, 450, 32, 0.4, 9, 12, 12, 12, 12, 26, 23);
    glPopMatrix();
}

void upToDownSquareFace(float x, float z, float xrepeat, float zrepeat, int tex) {
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texTure[tex]);
    glBegin(GL_QUADS);
    {
        glTexCoord2f(0, zrepeat);
        glVertex3f(0, 0, 0);
        glTexCoord2f(0, 0);
        glVertex3f(0, 0, z);
        glTexCoord2f(xrepeat, 0);
        glVertex3f(x, 0, z);
        glTexCoord2f(xrepeat, zrepeat);
        glVertex3f(x, 0, 0);
    }
    glEnd();
    glPopMatrix();
}

void downToUpSquareFace(float x, float z, float xrepeat, float zrepeat, int tex) {
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texTure[tex]);
    glBegin(GL_QUADS);
    {
        glTexCoord2f(0, 0);

        glVertex3f(0, 0, 0);
        glTexCoord2f(0, zrepeat);
        glVertex3f(0, 0, z);
        glTexCoord2f(xrepeat, zrepeat);

        glVertex3f(x, 0, z);
        glTexCoord2f(xrepeat, 0);
        glVertex3f(x, 0, 0);
    }
    glEnd();
    glPopMatrix();
}

void frontToBackSquareFace(float x, float y, float xrepeat, float yrepeat, int tex) {
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texTure[tex]);
    glBegin(GL_QUADS);
    {
        glTexCoord2f(0, 0);
        glVertex3f(0, 0, 0);
        glTexCoord2f(xrepeat, 0);
        glVertex3f(x, 0, 0);
        glTexCoord2f(xrepeat, yrepeat);
        glVertex3f(x, y, 0);
        glTexCoord2f(0, yrepeat);
        glVertex3f(0, y, 0);
    }
    glEnd();
    glPopMatrix();
}

void backToFrontSquareFace(float x, float y, float xrepeat, float yrepeat, int tex) {
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texTure[tex]);
    glBegin(GL_QUADS);
    {
        glTexCoord2f(xrepeat, 0);
        glVertex3f(0, 0, 0);
        glTexCoord2f(0, 0);
        glVertex3f(x, 0, 0);
        glTexCoord2f(0, yrepeat);
        glVertex3f(x, y, 0);
        glTexCoord2f(xrepeat, yrepeat);
        glVertex3f(0, y, 0);
    }
    glEnd();
    glPopMatrix();
}

void rightToLeftSquareFace(float y, float z, float yrepeat, float zrepeat, int tex) {
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texTure[tex]);
    glBegin(GL_QUADS);
    {
        glTexCoord2f(zrepeat, 0);
        glVertex3f(0, 0, 0);
        glTexCoord2f(zrepeat, yrepeat);
        glVertex3f(0, y, 0);
        glTexCoord2f(0, yrepeat);
        glVertex3f(0, y, z);
        glTexCoord2f(0, 0);
        glVertex3f(0, 0, z);
    }
    glEnd();
    glPopMatrix();
}

void leftToRightSquareFace(float y, float z, float yrepeat, float zrepeat, int tex) {
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texTure[tex]);
    glBegin(GL_QUADS);
    {
        glTexCoord2f(0, 0);
        glVertex3f(0, 0, 0);
        glTexCoord2f(0, yrepeat);
        glVertex3f(0, y, 0);
        glTexCoord2f(zrepeat, yrepeat);
        glVertex3f(0, y, z);
        glTexCoord2f(zrepeat, 0);
        glVertex3f(0, 0, z);
    }
    glEnd();
    glPopMatrix();
}

void innerBox(float x, float y, float z, float xrepeat, float yrepeat, float zrepeat, int left, int right, int back, int front, int under, int upper) {
    glPushMatrix();
    rightToLeftSquareFace(y, z, yrepeat, zrepeat, left);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x, 0, 0);
    leftToRightSquareFace(y, z, yrepeat, zrepeat, right);
    glPopMatrix();

    glPushMatrix();
    frontToBackSquareFace(x, y, xrepeat, yrepeat, back);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, z);
    backToFrontSquareFace(x, y, xrepeat, yrepeat, front);
    glPopMatrix();

    glPushMatrix();
    upToDownSquareFace(x, z, xrepeat, zrepeat, under);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, y, 0);
    downToUpSquareFace(x, z, xrepeat, zrepeat, upper);
    glPopMatrix();
}

void outerBox(float x, float y, float z, float xrepeat, float yrepeat, float zrepeat, int left, int right, int back, int front, int under, int upper) {
    glPushMatrix();
    leftToRightSquareFace(y, z, yrepeat, zrepeat, left);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(x, 0, 0);
    rightToLeftSquareFace(y, z, yrepeat, zrepeat, right);
    glPopMatrix();

    glPushMatrix();
    backToFrontSquareFace(x, y, xrepeat, yrepeat, back);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, z);
    frontToBackSquareFace(x, y, xrepeat, yrepeat, front);
    glPopMatrix();

    glPushMatrix();
    downToUpSquareFace(x, z, xrepeat, zrepeat, under);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, y, 0);
    upToDownSquareFace(x, z, xrepeat, zrepeat, upper);
    glPopMatrix();
}

void verticalCylinder(float baseRadius, float topRadius, float height, float xzrepeat, float yrepeat, int xzsplit, int ysplit, int tex) {
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glScalef(xzrepeat, yrepeat, 1);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    GLUquadricObj* obj;
    obj = gluNewQuadric();
    glBindTexture(GL_TEXTURE_2D, texTure[tex]);
    gluQuadricTexture(obj, GL_TRUE);
    gluQuadricDrawStyle(obj, GLU_FILL);
    gluQuadricNormals(obj, GLU_SMOOTH);
    glRotatef(-90, 1, 0, 0);
    glColor3f(0, 0, 1);
    gluCylinder(obj, baseRadius, topRadius, height, xzsplit, ysplit);
    glPopMatrix();

    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glScalef(1, 1, 1);
    glMatrixMode(GL_MODELVIEW);
}

void verticalSphere(float radius, float xzrepeat, float yrepeat, int xzsplit, int ysplit, int tex) {
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glScalef(xzrepeat, yrepeat, 1);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    GLUquadricObj* obj;
    obj = gluNewQuadric();
    glBindTexture(GL_TEXTURE_2D, texTure[tex]);
    gluQuadricTexture(obj, GL_TRUE);
    gluQuadricDrawStyle(obj, GLU_FILL);
    gluQuadricNormals(obj, GLU_SMOOTH);
    glRotatef(-90, 1, 0, 0);
    gluSphere(obj, radius, xzsplit, ysplit);
    glPopMatrix();

    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glScalef(1, 1, 1);
    glMatrixMode(GL_MODELVIEW);
}

void horizonalDisk(float innerRadius, float outerRadius, float xrepeat, float zrepeat, int xzsplit, int ysplit, int tex) {
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glScalef(xrepeat, zrepeat, 1);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    GLUquadricObj* obj;
    obj = gluNewQuadric();
    glBindTexture(GL_TEXTURE_2D, texTure[tex]);
    gluQuadricTexture(obj, GL_TRUE);
    gluQuadricDrawStyle(obj, GLU_FILL);
    gluQuadricNormals(obj, GLU_SMOOTH);
    glRotatef(-90, 1, 0, 0);
    gluDisk(obj, innerRadius, outerRadius, xzsplit, ysplit);
    glPopMatrix();

    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glScalef(1, 1, 1);
    glMatrixMode(GL_MODELVIEW);
}

void partialHorizonalDisk(float innerRadius, float outerRadius, float startAngle, float sweepAngle, float xrepeat, float zrepeat, int xzsplit, int ysplit, int tex) {
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glScalef(xrepeat, zrepeat, 1);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    GLUquadricObj* obj;
    obj = gluNewQuadric();
    glBindTexture(GL_TEXTURE_2D, texTure[tex]);
    gluQuadricTexture(obj, GL_TRUE);
    gluQuadricDrawStyle(obj, GLU_FILL);
    gluQuadricNormals(obj, GLU_SMOOTH);
    glRotatef(-90, 1, 0, 0);
    gluPartialDisk(obj, innerRadius, outerRadius, xzsplit, ysplit, startAngle, sweepAngle);
    glPopMatrix();

    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glScalef(1, 1, 1);
    glMatrixMode(GL_MODELVIEW);
}

void roomFrame(void) {
    glPushMatrix();
    outerBox(600, 350, 400, 12, 7, 8, 23, 23, 23, 25, 26, 23);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10, 10, 10);
    innerBox(580, 330, 380, 11.6, 6.6, 7.6, 23, 23, 23, 23, 20, 26);
    glPopMatrix();
}

void eaves(void) {
    glPushMatrix();
    outerBox(600, 10, 200, 12, 0.2, 4, 12, 12, 12, 12, 26, 23);
    glPopMatrix();
}

void corridor(void) {
    glPushMatrix();
    outerBox(600, 10, 200, 12, 0.2, 4, 12, 12, 12, 12, 26, 20);
    glPopMatrix();
}

void smallPillar(void) {
    glPushMatrix();
    outerBox(30, 350, 30, 0.6, 7, 0.6, 12, 12, 12, 12, 12, 12);
    glPopMatrix();
}

void bigPillar(void) {
    glPushMatrix();
    outerBox(60, 350, 30, 1.2, 7, 0.6, 12, 12, 12, 12, 12, 12);
    glPopMatrix();
}

void roomPillars(void) {
    glPushMatrix();
    smallPillar();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(285, 0, 0);
    smallPillar();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(570, 0, 0);
    smallPillar();
    glPopMatrix();
}

void leftFrontHandrail(void) {
    glPushMatrix();
    outerBox(290, 10, 10, 11.6, 0.2, 0.2, 6, 6, 6, 6, 6, 6);
    glPopMatrix();

    glPushMatrix();
    for (int i = 0; i < 16; i++) {
        glPushMatrix();
        glTranslatef(34 + 15 * i, -125, 4);
        outerBox(2, 130, 2, 0.04, 2.6, 0.04, 6, 6, 6, 6, 6, 6);
        glPopMatrix();
    }
    glPopMatrix();
}

void rightFrontHandrail(void) {
    glPushMatrix();
    glTranslatef(290, 0, 0);
    outerBox(290, 10, 10, 11.6, 0.2, 0.2, 6, 6, 6, 6, 6, 6);
    glPopMatrix();

    glPushMatrix();
    for (int i = 19; i < 35; i++) {
        glPushMatrix();
        glTranslatef(34 + 15 * i, -125, 4);
        outerBox(2, 130, 2, 0.04, 2.6, 0.04, 6, 6, 6, 6, 6, 6);
        glPopMatrix();
    }
    glPopMatrix();
}

void edgeHandrail(void) {
    glPushMatrix();
    outerBox(10, 10, 195, 0.2, 0.2, 3.9, 6, 6, 6, 6, 6, 6);
    glPopMatrix();

    for (int i = 0; i < 9; i++) {
        glPushMatrix();
        glTranslatef(4, -125, 21 + 17 * i);
        outerBox(2, 130, 2, 0.04, 2.6, 0.04, 6, 6, 6, 6, 6, 6);
        glPopMatrix();
    }
}

void window(void) {
    glPushMatrix();
    frontToBackSquareFace(460, 180, 2.5, 1, 16);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 14);
    frontToBackSquareFace(460, 180, 2.6, 1, 16);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 392);
    frontToBackSquareFace(360, 180, 2, 1, 16);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 406);
    frontToBackSquareFace(360, 180, 2, 1, 16);
    glPopMatrix();
}

void door(void) {
    glPushMatrix();
    frontToBackSquareFace(120, 280, 1, 1, 17);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, -14);
    frontToBackSquareFace(120, 280, 1, 1, 17);
    glPopMatrix();
}

void room(std::string type) {
    glPushMatrix();
    roomFrame();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 340, 400);
    eaves();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 400);
    corridor();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 570);
    roomPillars();
    glPopMatrix();

    if (type != "allhiden") {
        if (type != "lefthiden") {
            glPushMatrix();
            glTranslatef(10, 130, 580);
            leftFrontHandrail();
            glPopMatrix();
        }

        if (type != "righthiden") {
            glPushMatrix();
            glTranslatef(10, 130, 580);
            rightFrontHandrail();
            glPopMatrix();
        }
    }

    if (type == "leftedge") {
        glPushMatrix();
        glTranslatef(10, 130, 395);
        edgeHandrail();
        glPopMatrix();
    }

    if (type == "rightedge") {
        glPushMatrix();
        glTranslatef(580, 130, 395);
        edgeHandrail();
        glPopMatrix();
    }

    glPushMatrix();
    glTranslatef(30, 110, -3);
    window();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(450, 10, 403);
    door();
    glPopMatrix();
}

void covered(void) {
    glPushMatrix();
    outerBox(1700, 20, 500, 34, 0.4, 10, 12, 12, 12, 12, 26, 20);
    glPopMatrix();
}

void backPorchPillars(void) {
    glPushMatrix();
    bigPillar();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-570, 0, -370);
    smallPillar();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(600, 0, -370);
    smallPillar();
    glPopMatrix();
}

void centerGround(void) {
    glPushMatrix();
    outerBox(6400, 10, 10500, 128, 0.2, 210, 1, 1, 1, 1, 1, 24);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(300, 10, 3300);
    outerBox(2400, 90, 900, 48, 1.8, 18, 1, 1, 1, 1, 1, 24);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3700, 10, 3300);
    outerBox(2400, 90, 900, 48, 1.8, 18, 1, 1, 1, 1, 1, 24);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(300, 10, 6720);
    outerBox(2400, 90, 900, 48, 1.8, 18, 1, 1, 1, 1, 1, 24);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3700, 10, 6720);
    outerBox(2400, 90, 900, 48, 1.8, 18, 1, 1, 1, 1, 1, 24);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(300, 10, 4200);
    outerBox(5800, 90, 2520, 116, 1.8, 50.4, 1, 1, 1, 1, 1, 24);
    glPopMatrix();

    glPushMatrix();
    for (int i = 0; i < 2; i++) {
        glPushMatrix();
        glTranslatef(2700, 10 + 30 * i, 4120 + 30 * i);
        outerBox(1000, 30, 80 - 40 * i, 20, 0.6, 1.6 - 0.8 * i, 1, 1, 1, 1, 1, 7);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(2700, 10 + 30 * i, 6720);
        outerBox(1000, 30, 80 - 40 * i, 20, 0.6, 1.6 - 0.8 * i, 1, 1, 1, 1, 1, 7);
        glPopMatrix();
    }
    glPopMatrix();
}

void centerGrass(void) {
    glPushMatrix();
    glTranslatef(300, 10, 660);
    outerBox(2400, 10, 2400, 6, 0.025, 6, 0, 0, 0, 0, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3700, 10, 660);
    outerBox(2400, 10, 2400, 6, 0.025, 6, 0, 0, 0, 0, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(300, 10, 7860);
    outerBox(2400, 10, 2400, 6, 0.025, 6, 0, 0, 0, 0, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3700, 10, 7860);
    outerBox(2400, 10, 2400, 6, 0.025, 6, 0, 0, 0, 0, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2700, 110, 5460);
    partialHorizonalDisk(1260, 2160, 180, 180, 10.8, 10.8, 50, 1, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3700, 110, 5460);
    partialHorizonalDisk(1260, 2160, 0, 180, 10.8, 10.8, 50, 1, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(300, 100, 3300);
    outerBox(2400, 10, 900, 6, 0.025, 2.25, 0, 0, 0, 0, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3700, 100, 3300);
    outerBox(2400, 10, 900, 6, 0.025, 2.25, 0, 0, 0, 0, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(300, 100, 4200);
    outerBox(800, 10, 2520, 2, 0.025, 6.3, 0, 0, 0, 0, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(5300, 100, 4200);
    outerBox(800, 10, 2520, 2, 0.025, 6.3, 0, 0, 0, 0, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(300, 100, 6720);
    outerBox(2400, 10, 900, 6, 0.025, 2.25, 0, 0, 0, 0, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3700, 100, 6720);
    outerBox(2400, 10, 900, 6, 0.025, 2.25, 0, 0, 0, 0, 0, 0);
    glPopMatrix();
}

void stone(void) {
    glPushMatrix();
    outerBox(480, 10, 250, 1.2, 0.025, 0.625, 0, 0, 0, 0, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 390);
    outerBox(480, 10, 250, 1.2, 0.025, 0.625, 0, 0, 0, 0, 0, 0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 250);
    outerBox(480, 200, 140, 1, 1, 1, 11, 11, 11, 10, 11, 11);
    glPopMatrix();
}

void flags(void) {
    glPushMatrix();
    for (int i = 0; i < 15; i++) {
        glPushMatrix();
        glTranslatef(2660 - 130 * i, 20, 700);
        flag();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(3740 + 130 * i, 20, 700);
        flag();
        glPopMatrix();
    }
    glPopMatrix();
}

void centerSmallTrees(void) {
    glPushMatrix();
    for (int i = 0; i < 3; i++) {
        glPushMatrix();
        glTranslatef(400 + 900 * i, 20, 2960);
        smallTree(10, 5, 120, 100, 2, 5, 2);
        glPopMatrix();
    }

    for (int i = 0; i < 3; i++) {
        glPushMatrix();
        glTranslatef(6000 - 900 * i, 20, 2960);
        smallTree(10, 5, 120, 100, 2, 5, 2);
        glPopMatrix();
    }

    for (int i = 0; i < 3; i++) {
        glPushMatrix();
        glTranslatef(400 + 900 * i, 110, 3400);
        smallTree(10, 5, 120, 100, 2, 5, 2);
        glPopMatrix();
    }

    for (int i = 0; i < 3; i++) {
        glPushMatrix();
        glTranslatef(6000 - 900 * i, 110, 3400);
        smallTree(10, 5, 120, 100, 2, 5, 2);
        glPopMatrix();
    }

    for (int i = 0; i < 3; i++) {
        glPushMatrix();
        glTranslatef(400 + 900 * i, 110, 7520);
        smallTree(10, 5, 120, 100, 2, 5, 2);
        glPopMatrix();
    }

    for (int i = 0; i < 3; i++) {
        glPushMatrix();
        glTranslatef(6000 - 900 * i, 110, 7520);
        smallTree(10, 5, 120, 100, 2, 5, 2);
        glPopMatrix();
    }

    for (int i = 0; i < 3; i++) {
        glPushMatrix();
        glTranslatef(400 + 900 * i, 20, 7960);
        smallTree(10, 5, 120, 100, 2, 5, 2);
        glPopMatrix();
    }

    for (int i = 0; i < 3; i++) {
        glPushMatrix();
        glTranslatef(6000 - 900 * i, 20, 7960);
        smallTree(10, 5, 120, 100, 2, 5, 2);
        glPopMatrix();
    }

    for (int i = 0; i < 2; i++) {
        glPushMatrix();
        glTranslatef(400 + 5600 * i, 110, 4300);
        smallTree(10, 5, 120, 100, 2, 5, 2);
        glPopMatrix();
    }

    for (int i = 0; i < 2; i++) {
        glPushMatrix();
        glTranslatef(400 + 5600 * i, 110, 6620);
        smallTree(10, 5, 120, 100, 2, 5, 2);
        glPopMatrix();
    }
    glPopMatrix();
}

void centerBigTrees(void) {
    glPushMatrix();
    for (int i = 0; i < 2; i++) {
        glPushMatrix();
        glTranslatef(400 + 5600 * i, 20, 760);
        bigTree(30, 500, 2.5, 200, 200, 5, 5, 2, 22);
        glPopMatrix();
    }

    for (int i = 0; i < 5; i++) {
        if (i != 2) {
            for (int j = 0; j < 3; j++) {
                glPushMatrix();
                glTranslatef(400 + 1400 * i, 20, 10160 - 900 * j);
                bigTree(20, 1000, 4, 250, 150, 7, 5, 2, 2);
                glPopMatrix();
            }
        }
    }

    for (int i = 0; i < 2; i++) {
        glPushMatrix();
        glTranslatef(400 + 5600 * i, 110, 5460);
        bigTree(30, 500, 2.5, 200, 200, 5, 5, 2, 22);
        glPopMatrix();
    }

    for (int i = 0; i < 2; i++) {
        glPushMatrix();
        glTranslatef(1300, 110, 4560 + 1800 * i);
        bigTree(30, 500, 2.5, 200, 200, 5, 5, 2, 22);
        glPopMatrix();
    }

    for (int i = 0; i < 2; i++) {
        glPushMatrix();
        glTranslatef(5100, 110, 4560 + 1800 * i);
        bigTree(30, 500, 2.5, 200, 200, 5, 5, 2, 22);
        glPopMatrix();
    }
    glPopMatrix();
}

void centerTrees(void) {
    glPushMatrix();
    centerSmallTrees();
    centerBigTrees();
    glPopMatrix();
}

void dam(void) {
    glPushMatrix();
    verticalCylinder(750, 750, 100, 30 * PI, 1, 50, 1, 1);
    glPopMatrix();

    glPushMatrix();
    verticalCylinder(700, 700, 100, 28 * PI, 1, 50, 1, 1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 100, 0);
    horizonalDisk(700, 750, 15, 15, 50, 1, 1);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 50, 0);
    horizonalDisk(0, 700, 15, 15, 50, 1, 14);
    glPopMatrix();
}

void waterspout() {
    glPushMatrix();
    for (int i = 0; i < 360; i += 15) {
        glPushMatrix();
        glRotatef(i, 0, 1, 0);
        {
            glPushMatrix();
            glTranslatef(-100, 0, 0);
            glPushMatrix();
            glRotatef(-17, 0, 0, 1);
            verticalCylinder(3, 3, 20, 1, 1, 20, 1, 1);
            glPopMatrix();
            glPopMatrix();
        }

        {
            glPushMatrix();
            glTranslatef(-683, 0, 0);
            glPushMatrix();
            glRotatef(-30, 0, 0, 1);
            verticalCylinder(3, 3, 20, 1, 1, 20, 1, 1);
            glPopMatrix();
            glPopMatrix();
        }
        glPopMatrix();
    }
    glPopMatrix();
}

void jet(void) {
    glPushMatrix();
    for (int i = 0; i < 360; i += 15) {
        for (int j = 1; j < 500; j++) {
            glPushMatrix();
            glRotatef(i, 0, 1, 0);
            glPushMatrix();
            float x = blobX - 0.6 * j - i / 15;

            if (x > -17.32 && x < 17.32) {
                float jetfunc = 300 - x * x;
                glTranslatef(73.5 + 10 * x, jetfunc, 0);
                verticalSphere(2.5, 1, 1, 6, 4, 20);
            }
            glPopMatrix();
            glPopMatrix();

            glPushMatrix();
            glRotatef(i, 0, 1, 0);
            glPushMatrix();
            x = blobX - 50 - 0.4 * j - i / 15;

            if (x > -12.25 && x < 12.25) {
                float jetfunc = 150 - x * x;
                glTranslatef(-500 + 15 * x, jetfunc, 0);
                verticalSphere(2.5, 1, 1, 5, 3, 20);
            }
            glPopMatrix();
            glPopMatrix();
        }
    }
    glPopMatrix();
}

void jets(void) {
    glPushMatrix();
    jet();
    glPopMatrix();
}

void center(void) {
    glPushMatrix();
    centerGround();
    glPopMatrix();

    glPushMatrix();
    centerGrass();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2960, 10, 8740);
    stone();
    glPopMatrix();

    glPushMatrix();
    flags();
    glPopMatrix();

    glPushMatrix();
    centerTrees();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3200, 100, 5460);
    dam();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3200, 149, 5460);
    waterspout();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3200, 149, 5460);
    jets();
    glPopMatrix();
}

void flag(void) {
    glPushMatrix();
    verticalCylinder(10, 5, 50, 1, 1, 30, 1, 7);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 50, 0);
    verticalCylinder(5, 3, 50, 1, 1, 30, 1, 7);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 100, 0);
    verticalCylinder(3, 3, 500, 1, 1, 30, 1, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 450, 0);
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texTure[5]);
    glBegin(GL_QUADS);
    {
        glTexCoord2f(0, 0);
        glVertex3f(0, 0, 0);
        glTexCoord2f(1, 0);
        glVertex3f(100, -25, 130);
        glTexCoord2f(1, 1);
        glVertex3f(100, 75, 130);
        glTexCoord2f(0, 1);
        glVertex3f(0, 100, 0);
    }
    glEnd();
    glPopMatrix();
    glPopMatrix();
}

void smallTree(float baseRadius, float topRadius, float height, float radius, float rindrepeat, float xzleavesrepeat, float yleavesrepeat) {
    glPushMatrix();
    verticalCylinder(baseRadius, topRadius, height, 1, rindrepeat, 40, 1, 3);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, height, 0);
    verticalSphere(radius, xzleavesrepeat, yleavesrepeat, 50, 10, 28);
    glPopMatrix();
}

void bigTree(float baseRadius, float rindheight, float rindrepeat, float rootheight, float radius, int canopy, float xzleavesrepeat, float yleavesrepeat, int tex) {
    glPushMatrix();
    verticalCylinder(baseRadius, 0, rindheight + rootheight, 1, rindrepeat, 40, 1, 3);
    glPopMatrix();

    glPushMatrix();
    for (int i = 0; i < canopy; i++) {
        glPushMatrix();
        glTranslatef(0, rootheight + rindheight * i / canopy, 0);
        verticalCylinder(radius * (canopy - i) / canopy, 0, rindheight / (canopy - 1), xzleavesrepeat, yleavesrepeat, 50, 1, tex);
        verticalCylinder(radius * (canopy - i) / canopy, 0, rindheight / (2 * canopy), xzleavesrepeat, yleavesrepeat, 50, 1, 22);
        glPopMatrix();
    }
    glPopMatrix();
}
