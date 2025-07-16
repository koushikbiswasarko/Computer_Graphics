#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#define PI 3.14159265358979323846

#include <time.h>
#include <stdlib.h>

#define NUM_SNOW_DROPS 1000
#define DEG_TO_RAD 0.0174533  // Conversion factor for degrees to radians

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

bool start = false;
bool displayArko = false;
bool displaySadia = true;

int numDrops = 200;
float raindropX[200], raindropY[200], raindropSpeed[200];
float angle1 = 10.0f; // Angle in degrees
float radAngle;
bool backgroundChanged = false;
bool sunDisappeared = false;
bool cloudsAppeared = false;
bool carStarted = false;

float red = 0.95f, green = 0.95f, blue = 0.95f; // Initial light gray background color

float rotationAngle1 = 0.0f;
float _moveCar = 0.0f;
float _movePlane1 = 0.0f;
float _movePlane2 = 0.0f;

float snowX[NUM_SNOW_DROPS];
float snowY[NUM_SNOW_DROPS];
float angle = 25.0; // Rotation angle in degrees
bool startSnow = false;

float _cloudMove = 0.0f;

float sunAngle = -25.0;
float sunRadius = 8.0;
bool startSun = false;

float moonAngle = 160.0;
float moonRadius = 8.0;
bool startMoon = false;

bool moveJeep = false;
float rotationAngle = 0.0f;
float _move = -15.0f;

float fireTime = 0.0f;
bool startFire = false;

float ringTime = 0.0f;
bool startRing = false;

float _Heli = 4.0f;
float _Truck = 4.0f;
float moveC = 0.0f;
float moveC2 = 0.0f;

bool startC = false;
bool startC2 = false;

bool changeSkyColor = false;

bool startScene = false;
bool startScene2 = false;
bool startScene3 = false;
bool startScene4 = false;
bool startScene5 = false;
bool startScene6 = false;

bool msg1 = false;
bool msg2 = false;

bool text = false;
bool startWaterTrack = false;

float wingRotate = 12.0;

GLuint texture1, texture2, texture3, texture4, texture5, texture6, texture7, texture8, texture9, texture10, texture11, texture12, grass, ttp, ct, p1, t1, t2, t3;

void loadTexture(const char* filename, GLuint* texture)
{
    int width, height, channels;
    unsigned char* image = stbi_load(filename, &width, &height, &channels, STBI_rgb_alpha);
    if (!image)
    {
        printf("Failed to load image: %s\n", filename);
        exit(1);
    }

    glGenTextures(1, texture);
    glBindTexture(GL_TEXTURE_2D, *texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    stbi_image_free(image);
}

///1
void greenlayer()
{
    //green base
    glBegin(GL_POLYGON);
    glColor3f(0.39f, 0.69f, 0.09f);
    glVertex2f(-10, -6);
    glVertex2f(10, -6);
    glVertex2f(10, -1.44);
    glVertex2f(-10, -1.44);
    glEnd();
}

///2
void road()
{
    //glClear(GL_COLOR_BUFFER_BIT);


    ///Road
    //outside
    glBegin(GL_POLYGON);
    glColor3f(0.80f, 0.82f, 0.82f);
    glVertex2f(-10, -6);
    glVertex2f(10, -6);
    glVertex2f(10, -4.64);
    glVertex2f(-10, -4.64);
    glEnd();
    //upper
    glBegin(GL_POLYGON);
    glColor3f(0.51f, 0.55f, 0.61f);
    glVertex2f(-10, -5.88);
    glVertex2f(10, -5.88);
    glVertex2f(10, -4.74);
    glVertex2f(-10, -4.74);
    glEnd();

}

///3
void cBuilding()
{
    ///C circle
    // Center and distance point
    float centerX = 0.4856679737055f;
    float centerY = -0.1288384559122f;
    float pointX = 0.434184040026f;
    float pointY = 2.226847310097f;

    // Calculate radius
    float radius = sqrt(pow(pointX - centerX, 2) + pow(pointY - centerY, 2));

    // Define gradient tilt
    float startAngle = 0.0f; // Starting tilt

    glBegin(GL_TRIANGLE_FAN);

    // Center vertex color (light blue #00b8e3)
    glColor3f(0.0f, 0.72f, 0.89f);
    glVertex2f(centerX, centerY);

    // Define colors for the perimeter vertices with the tilted gradient
    for (int i = 0; i <= 100; i++) {
        float angle1 = 2.0f * M_PI * i / 100; // Angle in radians
        float x = radius * cos(angle1) + centerX;
        float y = radius * sin(angle1) + centerY;

        // Adjust the gradient's tilt
        float gradientAngle = atan2(y - centerY, x - centerX); // Angle of this vertex
        float normalizedGradient = (cos(gradientAngle - startAngle) + 1.0f) / 2.0f; // Map angle to [0, 1]

        // Interpolate between #00b8e3 (start) and #0e2145 (end)
        float r = (1.0f - normalizedGradient) * 0.0f + normalizedGradient * 0.05f; // Red
        float g = (1.0f - normalizedGradient) * 0.72f + normalizedGradient * 0.13f; // Green
        float b = (1.0f - normalizedGradient) * 0.89f + normalizedGradient * 0.27f; // Blue
        glColor3f(r, g, b);

        glVertex2f(x, y);
    }

    glEnd();

    ///C lower
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.72f, 0.89f);
    glVertex2f(-0.949486, -1.985);
    glVertex2f(-0.949486, -3.083);
    glColor3f(0.05f, 0.13f, 0.27f);
    glVertex2f(1.9368646, -3.083);
    glVertex2f(1.9368646, -1.985);
    glEnd();



    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ct);
    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-10.0f, -6.0f);   // Bottom-left
    glTexCoord2f(1.0f, 1.0f); glVertex2f(10.0f, -6.0f);    // Bottom-right
    glTexCoord2f(1.0f, 0.0f); glVertex2f(10.0f, 5.25f);    // Top-right
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-10.0f, 5.25f);   // Top-left
    glEnd();
    glDisable(GL_TEXTURE_2D);

}

///4
void anex1()
{
    glBegin(GL_POLYGON);
    glColor3f(0.486f, 0.349f, 0.216f);
    glVertex2f(-10, -3.34);
    glVertex2f(-10, 0.26);
    glVertex2f(-5.2, -1.2);
    glVertex2f(-5.2, -1.82);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.25f, 0.15f, 0.12f);
    glVertex2f(-10, -3.34);
    glVertex2f(-10, -4.64);
    glVertex2f(-9.2, -4.64);
    glVertex2f(-4.94, -1.82);
    glVertex2f(-5.22, -1.82);
    glEnd();

    glLineWidth(10);
    glBegin(GL_LINES);
    glColor3f(0.098f, 0.078f, 0.053f);
    glVertex2f(-9.64, -4.64);
    glVertex2f(-9.64, 0.18);
    glEnd();
    glLineWidth(8.5);
    glBegin(GL_LINES);
    glColor3f(0.098f, 0.078f, 0.053f);
    glVertex2f(-8.08, -0.32);
    glVertex2f(-8.08, -4.0);
    glEnd();
    glLineWidth(6.5);
    glBegin(GL_LINES);
    glColor3f(0.098f, 0.078f, 0.053f);
    glVertex2f(-6.978, -3.199);
    glVertex2f(-6.978, -0.63);
    glEnd();
    glLineWidth(5);
    glBegin(GL_LINES);
    glColor3f(0.098f, 0.078f, 0.053f);
    glVertex2f(-6.24, -0.86);
    glVertex2f(-6.24, -2.7);
    glEnd();
    glLineWidth(4);
    glBegin(GL_LINES);
    glColor3f(0.098f, 0.078f, 0.053f);
    glVertex2f(-5.68, -2.33);
    glVertex2f(-5.68, -1.04);
    glEnd();
    glLineWidth(3);
    glBegin(GL_LINES);
    glColor3f(0.098f, 0.078f, 0.053f);
    glVertex2f(-5.32, -1.14);
    glVertex2f(-5.32, -2.1);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.188f, 0.063f, 0.000f);
    glVertex2f(-4.94, -1.86);
    glVertex2f(-8.66, -4.64);
    glVertex2f(-9.2, -4.64);
    glVertex2f(-4.94, -1.82);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.098f, 0.078f, 0.053f);
    glVertex2f(-10, 0.26);
    glVertex2f(-10, 0.62);
    glVertex2f(-5.2, -1.14);
    glVertex2f(-5.2, -1.2);
    glEnd();

    //door
    glBegin(GL_POLYGON);
    glColor3f(0.177f, 0.105f, 0.000f);
    glVertex2f(-9.18, -3.08);
    glVertex2f(-8.4569, -2.853356742636);
    glVertex2f(-8.4569, -1.1673266988343);
    glVertex2f(-9.18, -1.1187825302596);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.177f, 0.105f, 0.000f);
    glVertex2f(-7.733, -2.6249392950117);
    glVertex2f(-7.733, -1.2412197789802);
    glVertex2f(-7.22, -1.291921295292);
    glVertex2f(-7.22, -2.4661904245451);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.177f, 0.105f, 0.000f);
    glVertex2f(-6.78, -2.3189627300079);
    glVertex2f(-6.78, -1.3296758908995);
    glVertex2f(-6.4, -1.3528434816115);
    glVertex2f(-6.4, -2.2);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.177f, 0.105f, 0.000f);
    glVertex2f(-6.088, -2.0954253620117);
    glVertex2f(-6.088, -1.375);
    glVertex2f(-5.825, -1.4);
    glVertex2f(-5.825, -2.0171226171148);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.177f, 0.105f, 0.000f);
    glVertex2f(-5.587, -1.9363094560443);
    glVertex2f(-5.587, -1.41);
    glVertex2f(-5.404, -1.43);
    glVertex2f(-5.404, -1.8789994908464);
    glEnd();



}

///5
void building()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ///building1
    glBegin(GL_POLYGON);
    glColor3f(0.95f, 0.98f, 1.0f);
    glVertex2f(-5.2, -1.82);
    glVertex2f(-5.2, 1);
    glVertex2f(-3, 1);
    glVertex2f(-3, -1.82);
    glEnd();

    //grey lines
    glBegin(GL_POLYGON);
    glColor3f(0.7f, 0.8f, 0.9f);
    glVertex2f(-5.2, 0.9);
    glVertex2f(-5.2, 1);
    glVertex2f(-3, 1);
    glVertex2f(-3, 0.9);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.7f, 0.8f, 0.9f);
    glVertex2f(-5.2, 0.3);
    glVertex2f(-5.2, 0.4);
    glVertex2f(-3, 0.4);
    glVertex2f(-3, 0.3);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.7f, 0.8f, 0.9f);
    glVertex2f(-5.2, -0.6);
    glVertex2f(-5.2, -0.5);
    glVertex2f(-3, -0.5);
    glVertex2f(-3, -0.6);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.7f, 0.8f, 0.9f);
    glVertex2f(-5.2, -1.82);
    glVertex2f(-5.2, -1.74);
    glVertex2f(-3, -1.74);
    glVertex2f(-3, -1.82);
    glEnd();

    //window
    glBegin(GL_POLYGON);
    glColor3f(0.2f, 0.3f, 0.6f);
    glVertex2f(-5, -0.16);
    glVertex2f(-4.62, -0.16);
    glVertex2f(-4.46, -0.04);
    glVertex2f(-4.46, 0.3);
    glVertex2f(-5, 0.3);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.2f, 0.3f, 0.6f);
    glVertex2f(-4.46, -0.04);
    glVertex2f(-4.46, 0.3);
    glVertex2f(-3.32, 0.3);
    glVertex2f(-3.32, -0.04);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.2f, 0.3f, 0.6f);
    glVertex2f(-5, -1.08);
    glVertex2f(-4.62, -1.08);
    glVertex2f(-4.46, -0.96);
    glVertex2f(-4.46, -0.6);
    glVertex2f(-5, -0.6);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.2f, 0.3f, 0.6f);
    glVertex2f(-4.46, -0.96);
    glVertex2f(-4.46, -0.6);
    glVertex2f(-3.32, -0.6);
    glVertex2f(-3.32, -0.96);
    glEnd();

    //door
    glBegin(GL_POLYGON);
    glColor3f(0.2f, 0.3f, 0.6f);
    glVertex2f(-5, -1.74);
    glVertex2f(-5, -1.4);
    glVertex2f(-4.57, -1.4);
    glVertex2f(-4.57, -1.74);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.3f, 0.4f, 0.7f);
    glVertex2f(-4.7, -1.74);
    glVertex2f(-4.7, -1.4);
    glVertex2f(-4.57, -1.4);
    glVertex2f(-4.57, -1.74);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.2f, 0.3f, 0.6f);
    glVertex2f(-4.52, -1.74);
    glVertex2f(-4.52, -1.4);
    glVertex2f(-4.1, -1.4);
    glVertex2f(-4.1, -1.74);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.3f, 0.4f, 0.7f);
    glVertex2f(-4.52, -1.74);
    glVertex2f(-4.52, -1.4);
    glVertex2f(-4.39, -1.4);
    glVertex2f(-4.39, -1.74);
    glEnd();

    //shadow
    glBegin(GL_POLYGON);
    glColor4f(0.1, 0.1, 0.2, 0.1);
    glVertex2f(-5.2, -1.82);
    glVertex2f(-5.2, 1);
    glVertex2f(-3.9, 1);
    glVertex2f(-3.9, -1.82);
    glEnd();

    ///building2
    glBegin(GL_POLYGON);
    glColor3f(0.8f, 0.9f, 1.0f);
    glVertex2f(-3.36, -1.82);
    glVertex2f(-3.36, 0.6);
    glVertex2f(-2.182, 1.47);
    glVertex2f(-1.01, 0.6);
    glVertex2f(-1.01, -1.82);
    glEnd();
    glLineWidth(10);
    glBegin(GL_LINES);
    glColor3f(0.2f, 0.3f, 0.6f);
    //glVertex2f(-3.36, 0.6);
    glVertex2f(-2.182, 1.47);
    glVertex2f(-1.01, 0.6);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.2f, 0.3f, 0.6f);
    glVertex2f(-3.44, 0.54);
    glVertex2f(-2.182, 1.47);
    //glVertex2f(-1.01, 0.6);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.2f, 0.3f, 0.6f);
    glVertex2f(-3.2, -0.9);
    glVertex2f(-3.2, 0.4);
    glVertex2f(-1.2, 0.4);
    glVertex2f(-1.2, -0.9);
    glEnd();
    glLineWidth(1);
    glBegin(GL_LINES);
    glColor3f(0.8f, 0.9f, 1.0f);
    glVertex2f(-3.0, -0.9);
    glVertex2f(-3.0, 0.4);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.8f, 0.9f, 1.0f);
    glVertex2f(-2.80, -0.9);
    glVertex2f(-2.80, 0.4);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.8f, 0.9f, 1.0f);
    glVertex2f(-2.60, -0.9);
    glVertex2f(-2.60, 0.4);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.8f, 0.9f, 1.0f);
    glVertex2f(-2.40, -0.9);
    glVertex2f(-2.40, 0.4);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.8f, 0.9f, 1.0f);
    glVertex2f(-2.20, -0.9);
    glVertex2f(-2.20, 0.4);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.8f, 0.9f, 1.0f);
    glVertex2f(-2.0, -0.9);
    glVertex2f(-2.0, 0.4);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.8f, 0.9f, 1.0f);
    glVertex2f(-1.80, -0.9);
    glVertex2f(-1.80, 0.4);
    glEnd();

    //door
    glBegin(GL_POLYGON);
    glColor3f(0.2f, 0.3f, 0.6f);
    glVertex2f(-2.75, -1.82);
    glVertex2f(-2.75, -1.37);
    glVertex2f(-1.57, -1.37);
    glVertex2f(-1.57, -1.82);
    glEnd();

}

///6
void airplane()
{

    glPushMatrix();
    glTranslatef(_movePlane1, _movePlane2, 0.0);

    //upper wings
    glBegin(GL_POLYGON);
    glColor3f(0.75f, 0.75f, 0.75f);
    glVertex2f(6.82913020032, 2.6478812766988);
    glVertex2f(7.2920116557968, 2.5557763230301);
    glVertex2f(7.6937926298678, 2.6641480537576);
    glVertex2f(7.6892782619757, 2.6786748645899);
    glVertex2f(7.506339747917, 2.7114519456942);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.6f, 0.6f, 0.6f);
    glVertex2f(7.2920116557968, 2.5557763230301);
    glVertex2f(7.3270877196031, 2.547437692959);
    glVertex2f(7.6924758229829, 2.6456105631108);
    glVertex2f(7.6937926298678, 2.6641480537576);
    glEnd();

    //back wings
    glBegin(GL_POLYGON);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(8.2818714291657, 2.3552427483947);
    glVertex2f(8.8076137528447, 2.2232624910973);
    glVertex2f(9.220794238503, 2.7841922677996);
    glVertex2f(9.2, 2.8);
    glVertex2f(8.9717652192752, 2.8318533255112);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.1f, 0.3f, 0.8f);
    glVertex2f(8.3228, 2.3834); //G12
    glVertex2f(8.335, 2.391949); //G10
    glVertex2f(8.349944933284, 2.3919849872112);
    glVertex2f(8.3711587641597, 2.3944094250968);
    glVertex2f(8.3920695403086, 2.3983491366609);
    glVertex2f(8.4123742070039, 2.4010766292822);
    glVertex2f(8.4341941473332, 2.4050163408463);
    glVertex2f(8.459650744384, 2.4116835450316);
    glVertex2f(8.4863195603421, 2.4189568586884);
    glVertex2f(8.5096547743053, 2.4262301723451);
    glVertex2f(8.5311716599078, 2.4341095954733);
    glVertex2f(8.5520824360567, 2.4407767996587);
    glVertex2f(8.5817370574585, 2.4528297460688);
    glVertex2f(8.6167116826749, 2.465384740105);
    glVertex2f(8.6543766636772, 2.4824236605828);
    glVertex2f(8.6920416446795, 2.5012561516372);
    glVertex2f(8.7261194846339, 2.5218822132682); //V10
    glVertex2f(8.7628876803743, 2.5443018454758);
    glVertex2f(8.7996558761146, 2.5622375512418);
    glVertex2f(8.8400112129028, 2.586450754026);
    glVertex2f(8.8857472612627, 2.6124575273869);
    glVertex2f(8.9162379601693, 2.6303932331529);
    glVertex2f(8.9578914533861, 2.6548818974879);
    glVertex2f(9.0014325600554, 2.6770260681447);
    glVertex2f(9.0512577007835, 2.6961147084635);
    glVertex2f(9.0981777946533, 2.7098589787887);
    glVertex2f(9.1390434590903, 2.7215226211945);
    glVertex2f(9.18, 2.73); //I11
    glVertex2f(9.05, 2.55);
    glVertex2f(9.0101005949611, 2.5363243624853);
    glVertex2f(8.9680790410071, 2.5224572492732);
    glVertex2f(8.924376624895, 2.5081699205091);
    glVertex2f(8.8861370107969, 2.4926219450894);
    glVertex2f(8.8501536907247, 2.4803467462981);
    glVertex2f(8.7409526751579, 2.4379183249907);
    glVertex2f(8.7033930901859, 2.4253984629656);
    glVertex2f(8.6581824786455, 2.4114875051599);
    glVertex2f(8.6129272208466, 2.3976350669938);
    glVertex2f(8.5786752712151, 2.3883584970294);
    glVertex2f(8.5437097392997, 2.37979550937);
    glVertex2f(8.519447941644, 2.3776547624551);
    glVertex2f(8.4823416628766, 2.3726596863204);
    glVertex2f(8.454511953801, 2.3712325217105);
    glVertex2f(8.4195464218855, 2.3712325217105);
    glVertex2f(8.388862383674, 2.3712325217105);
    glVertex2f(8.3617462568824, 2.3726596863204);
    glVertex2f(8.3367708769427, 2.3776547624551);
    glEnd();
    glBegin(GL_POLYGON);
    glColor4f(1.0f, 1.0f, 1.0f, 0.3f);
    glVertex2f(8.3042227303842, 2.3536718226123);
    glVertex2f(8.5984425921693, 2.2842061965852);
    glVertex2f(9.17666, 2.80326);
    glVertex2f(8.9891577774263, 2.8298272984033);
    glEnd();




    //body outer
    glBegin(GL_POLYGON);
    glColor3f(0.8f, 0.8f, 0.8f);
    glVertex2f(5.1, 2.45);
    glVertex2f(5.0610246468637, 2.4576272205584);
    glVertex2f(5.0258156850867, 2.4707442847499);
    glVertex2f(5.0063295600941, 2.4891260443298);
    glVertex2f(4.9978858701868, 2.5125271277872);
    glVertex2f(5, 2.54);
    glVertex2f(5.0121195188877, 2.5653605017786);
    glVertex2f(5.0404827674238, 2.5943361460764);
    glVertex2f(5.0760509540616, 2.6174554673909);
    glVertex2f(5.124056319744, 2.6357971298618); //j8
    glVertex2f(5.1805744745658, 2.6488184694531);
    glVertex2f(5.22, 2.66);
    glVertex2f(5.2555152474518, 2.6718182794864);
    glVertex2f(5.34, 2.72);
    glVertex2f(5.4059189419074, 2.7529571146532);
    glVertex2f(5.6022553010936, 2.8163479796326);
    glVertex2f(5.6536427996057, 2.8256911614547); //B8
    glVertex2f(5.6989696404602, 2.8292317540388);
    glVertex2f(5.7586705299438, 2.8311176409321);
    glVertex2f(5.8009527330585, 2.8311176409321);
    glVertex2f(5.8634150785689, 2.8311176409321);
    glVertex2f(5.9186702303665, 2.8272738041724);
    glVertex2f(6.0089280192622, 2.8131494428059);//Z8
    glVertex2f(6.6763340872483, 2.6856491572924);//A9
    glVertex2f(8.6154544473385, 2.2937016844358);//B9
    glVertex2f(8.7401839784985, 2.2598465249835);
    glVertex2f(8.8225484406479, 2.2238361642346);
    glVertex2f(8.85, 2.2);
    glVertex2f(8.8686454719194, 2.1709601577762);
    glVertex2f(8.8686454719194, 2.1709601577762);
    glVertex2f(8.8645780868072, 2.1248631265047);
    glVertex2f(8.836890478669, 2.0996388630359);
    glVertex2f(8.7981718710938, 2.0823390596512);
    glVertex2f(8.7388582594893, 2.0600964552995);
    glVertex2f(8.6342356390201, 2.0370300507867);
    glVertex2f(8.5098418146828, 2.0213778477244);
    glVertex2f(8.3673243867997, 2.0073732449844);
    glVertex2f(8.1832999623405, 2.0035234564978);
    glVertex2f(7.3820066264291, 2.0647362066867); //p9
    glEnd();


    //color on body
    glBegin(GL_POLYGON);
    glColor3f(0.1f, 0.3f, 0.8f);
    glVertex2f(7.315, 2.555);
    glVertex2f(8.7401839784985, 2.2598465249835);
    glVertex2f(8.8225484406479, 2.2238361642346);
    glVertex2f(8.85, 2.2);
    glVertex2f(8.8686454719194, 2.1709601577762);
    glVertex2f(8.8686454719194, 2.1709601577762);
    glVertex2f(8.8645780868072, 2.1248631265047);
    glVertex2f(8.836890478669, 2.0996388630359);
    glVertex2f(8.7981718710938, 2.0823390596512);
    glVertex2f(8.7388582594893, 2.0600964552995);
    glVertex2f(8.6342356390201, 2.0370300507867);
    glVertex2f(8.5098418146828, 2.0213778477244);
    glVertex2f(8.3673243867997, 2.0073732449844);
    glVertex2f(8.1832999623405, 2.0035234564978);
    glVertex2f(7.82, 2.032);
    glEnd();

    //white line
    glLineWidth(6);
    glBegin(GL_LINES);
    glColor3f(0.8f, 0.8f, 0.85f);
    glVertex2f(8.1275738895119, 2.1905125663114);
    glVertex2f(8.9556833295314, 2.0704918453901);
    glEnd();

    //body upper
    glBegin(GL_POLYGON);
    glColor4f(1.0f, 1.0f, 1.0f, 0.3f);
    glVertex2f(5.0996535949452, 2.4905585641322); //P1
    glVertex2f(5.06, 2.5);
    glVertex2f(5.045, 2.515);
    glVertex2f(5.036, 2.54);
    glVertex2f(5.04, 2.56);
    glVertex2f(5.06, 2.58);
    glVertex2f(5.08, 2.595);
    glVertex2f(5.14, 2.624); //Q7
    glVertex2f(5.2, 2.635);
    glVertex2f(5.216, 2.636);
    glVertex2f(5.26, 2.652);
    glVertex2f(5.458, 2.746);//U7
    glVertex2f(5.52, 2.77);
    glVertex2f(5.566, 2.784);
    glVertex2f(5.61, 2.793);
    glVertex2f(5.66, 2.801);
    glVertex2f(5.704, 2.8062);
    glVertex2f(5.75, 2.8065);
    glVertex2f(5.798, 2.8055);
    glVertex2f(5.86, 2.8045);
    glVertex2f(5.9, 2.802);
    glVertex2f(8.5006764902077, 2.287262062123); //I7
    glVertex2f(8.65, 2.25);
    glVertex2f(8.7500989478541, 2.216395514268);
    glVertex2f(8.7910903823977, 2.1906890214187);
    glVertex2f(8.7959537729367, 2.1622034482613);
    glVertex2f(8.7660786596253, 2.1316335648729);
    glVertex2f(8.6507468268418, 2.0913369004064);
    glVertex2f(8.5506999357524, 2.0711885681731);
    glVertex2f(8.35, 2.05);
    glVertex2f(8.1996929583984, 2.0482267361728);
    glVertex2f(7.3964983604723, 2.1088199602001);
    glEnd();

    //front glass
    glBegin(GL_POLYGON);
    glColor3f(0.25f, 0.3f, 0.4f);
    glVertex2f(5.22, 2.66);
    glVertex2f(5.4932696514331, 2.6113010850978);
    glVertex2f(5.5945358932654, 2.7212619064665);
    glVertex2f(5.4059189419074, 2.7529571146532);
    glEnd();

    //lower wings
    glBegin(GL_POLYGON);
    glColor3f(0.82f, 0.82f, 0.82f);
    glVertex2f(6.284238634536, 2.1724406095743);
    glVertex2f(6.2465091969235, 2.1840946799536);
    glVertex2f(6.2438110951859, 2.2204340054917);
    glVertex2f(6.2431815100662, 2.2455256951937);
    glVertex2f(6.2462511580566, 2.27973034523);
    glVertex2f(6.2541445386033, 2.3143735164207);
    glVertex2f(6.2681989138854, 2.3527730282718);
    glVertex2f(6.2844165047132, 2.3935785805809);
    glVertex2f(6.3285713839913, 2.3937817140681);
    glVertex2f(6.3701577796127, 2.3902797017028);
    glVertex2f(6.4139329328983, 2.3828379254265);
    glVertex2f(6.4511418131912, 2.3749583976045);
    glVertex2f(6.4909772026811, 2.3635768574172);
    glVertex2f(6.5299370891054, 2.3478178017732);
    glVertex2f(6.5640817086682, 2.3233037152159);
    glVertex2f(6.5670686068083, 2.2933623381014);
    glVertex2f(6.56624505324, 2.2620673015884);
    glVertex2f(6.5605316498261, 2.2222386513376);
    glVertex2f(6.5465136984138, 2.189027670929);
    glVertex2f(6.5321454393942, 2.1548213995892);
    glVertex2f(6.4990996586991, 2.1503910953454);
    glVertex2f(6.4582374009948, 2.1479062282501);
    glVertex2f(6.4150651807204, 2.1500664727551);
    glVertex2f(6.3743566829765, 2.1537954955583);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.7f, 0.7f, 0.7f);
    glVertex2f(6.284238634536, 2.1724406095743);
    glVertex2f(6.2465091969235, 2.1840946799536);
    glVertex2f(6.2438110951859, 2.2204340054917);
    glVertex2f(6.2431815100662, 2.2455256951937);
    glVertex2f(6.2462511580566, 2.27973034523);
    glVertex2f(6.2541445386033, 2.3143735164207);
    glVertex2f(6.2681989138854, 2.3527730282718);
    glVertex2f(6.2844165047132, 2.3935785805809);
    glVertex2f(6.3285713839913, 2.3937817140681);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.78f, 0.78f, 0.78f);
    glVertex2f(6.5321454393942, 2.1548213995892);
    glVertex2f(7.5073970247488, 1.6653211768043);
    glVertex2f(7.721404581956, 1.6308786965853);
    glVertex2f(7.724383302023, 1.6530719511159);
    glVertex2f(7.7252582466895, 1.686757321759);
    glVertex2f(7.0292388215842, 2.2654287612338);
    glVertex2f(6.5299370891054, 2.3478178017732);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.65f, 0.65f, 0.65f);
    glVertex2f(6.5321454393942, 2.1548213995892);
    glVertex2f(7.5073970247488, 1.6653211768043);
    glVertex2f(6.5465136984138, 2.189027670929);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.65f, 0.65f, 0.65f);
    glVertex2f(7.724383302023, 1.6530719511159);
    glVertex2f(7.7252582466895, 1.686757321759);
    glVertex2f(7.0292388215842, 2.2654287612338);
    glEnd();


    //door
    glLineWidth(1);
    glBegin(GL_LINE_LOOP);
    glColor3f(0.7f, 0.7f, 0.7f);
    glVertex2f(5.6478721111228, 2.4431844048205);
    glVertex2f(5.6348364066745, 2.4645186816555);
    glVertex2f(5.6658528550327, 2.6406290291813);
    glVertex2f(5.6810982279545, 2.6579772126689);
    glVertex2f(5.7437808015388, 2.6461847598576);
    glVertex2f(5.7589693499394, 2.6242457448593);
    glVertex2f(5.73, 2.45);
    glVertex2f(5.7139491179391, 2.4349868811786);
    glEnd();
    //windows
    glBegin(GL_POLYGON);
    glColor3f(0.3f, 0.4f, 0.5f);
    glVertex2f(5.8362197439932, 2.6337421665693);
    glVertex2f(5.8249734467132, 2.5670141340893);
    glVertex2f(7.2637218992992, 2.330426334252);
    glVertex2f(7.269851894643, 2.393258788364);
    glEnd();

    glPopMatrix();
}

///7
void drawCar()
{
    //uuper body black
    glBegin(GL_POLYGON);
    glColor3f(0.2f, 0.25f, 0.3f);
    glVertex2f(6.9688144567173, -4.894173271706);
    glVertex2f(7.3775162497739, -4.5765003074551);
    glVertex2f(7.4077603130543, -4.5536129075462);
    glVertex2f(7.4366863320757, -4.5361400276633);
    glVertex2f(7.4765662119275, -4.5160956895597);
    glVertex2f(7.529600188275, -4.496051351456);
    glVertex2f(7.5941382906569, -4.4815378850361);
    glVertex2f(7.6533720114368, -4.4724459493275);
    glVertex2f(8.8086862345736, -4.4724459493275);//M18
    glVertex2f(8.8397196998496, -4.4727472451157);
    glVertex2f(8.9219456223297, -4.4860146710312);
    glVertex2f(8.967048217762, -4.5023375155701);
    glVertex2f(9.007855327915, -4.5225262969733);
    glVertex2f(9.0622959666233, -4.5608353163415);
    glVertex2f(9.1141873990359, -4.6089755622775);
    glVertex2f(9.16, -4.66);
    glVertex2f(9.3468935002749, -4.8868610166245);
    glEnd();
    //upper body colored
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.63f, 0.71f);
    glVertex2f(7.0759013764075, -4.8943433891398);
    glVertex2f(7.4912500232466, -4.5540556656621);
    glVertex2f(7.5212376734376, -4.5349726149821);
    glVertex2f(7.5553145486547, -4.5163439226517);
    glVertex2f(7.5925719322255, -4.4999870220688);
    glVertex2f(7.6289205991237, -4.4877193466317);
    glVertex2f(7.6813562416821,-4.4724459493275);
    glVertex2f(8.8086862345736, -4.4724459493275);//M18
    glVertex2f(8.8397196998496, -4.4727472451157);
    glVertex2f(8.9219456223297, -4.4860146710312);
    glVertex2f(8.967048217762, -4.5023375155701);
    glVertex2f(9.007855327915, -4.5225262969733);
    glVertex2f(9.0622959666233, -4.5608353163415);
    glVertex2f(9.1141873990359, -4.6089755622775);
    glVertex2f(9.16, -4.66);
    glVertex2f(9.3468935002749, -4.8868610166245);
    glEnd();
    //inner upper body for windows
    glBegin(GL_POLYGON);
    glColor3f(0.2f, 0.25f, 0.3f);
    glVertex2f(7.1676526784264, -4.8936621192003);
    glVertex2f(7.5416632288393, -4.5677618299632);
    glVertex2f(7.5685626193764, -4.5464832069754);
    glVertex2f(7.5978709105587, -4.526810517798);
    glVertex2f(7.6327999699129, -4.5083422789783);
    glVertex2f(7.6669260623853, -4.4942903581373);
    glVertex2f(7.6984721630422, -4.485250138019);
    glVertex2f(7.7237336884545, -4.4789347564811);
    glVertex2f(7.7437624693171, -4.4724459493275);//V19
    glVertex2f(8.8086862345736, -4.4724459493275);
    glVertex2f(8.8449779932109, -4.4829783459559);
    glVertex2f(8.8712777684136, -4.4911793513666);
    glVertex2f(8.8961635772076, -4.5007943232275);
    glVertex2f(8.9252912852278, -4.518893093789);
    glVertex2f(8.9607580263626, -4.5424667984602);
    glVertex2f(8.9956451910407, -4.5719867078977);
    glVertex2f(9.0439504959795, -4.6256592705113);
    glVertex2f(9.2478473351996, -4.886761964904);
    glEnd();

    //window line
    glLineWidth(5);
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.63f, 0.71f);
    glVertex2f(8.1029037408464, -4.4724459493275);
    glVertex2f(8.1029037408464, -4.8936621192003);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.63f, 0.71f);
    glVertex2f(8.8334209563704, -4.8936621192003);
    glVertex2f(8.8334209563704, -4.4788325564581);
    glVertex2f(8.8801391263173, -4.4879615659417);
    glVertex2f(8.9062, -4.5036699306569);
    glVertex2f(8.9062, -4.8936621192003);
    glEnd();


    ///body
    //body outer
    glBegin(GL_POLYGON);
    glColor3f(0.2f, 0.25f, 0.3f);
    glVertex2f(6.37, -5.46);
    glVertex2f(6.3555214212048,-5.4636769799489);
    glVertex2f(6.3453522908283, -5.4460575342875);
    glVertex2f(6.3438925289953, -5.4308760107807);
    glVertex2f(6.3455269303444, -5.1425960161115);
    glVertex2f(6.3503372117387, -5.1175825521293);
    glVertex2f(6.3623629152244, -5.0968983415286);
    glVertex2f(6.3777558156861, -5.0771761872349);
    glVertex2f(6.3957231002109, -5.0572458897891);
    glVertex2f(6.4136519066779, -5.0405123365969);
    glVertex2f(6.4363617282028, -5.0225835296053);
    glVertex2f(6.4632549379033, -4.9992760805162);
    glVertex2f(6.4889528938393, -4.978359139026);
    glVertex2f(6.5176389841866, -4.9562469437363);
    glVertex2f(6.5445321938871, -4.9389157636444);
    glVertex2f(6.5834374005449, -4.9173241066728);
    glVertex2f(6.6172740043096, -4.903183436029);
    glVertex2f(6.6531011860216, -4.8957997721381);
    glVertex2f(6.6989885224385, -4.8919202052497);
    glVertex2f(9.4756159842871, -4.8919202052497);
    glVertex2f(9.49026620182, -4.8876961978632);
    glVertex2f(9.5013585093806, -4.8935562850478);
    glVertex2f(9.5074327515184, -4.9043943121657);
    glVertex2f(9.5074004600418, -4.9149636335797);
    glVertex2f(9.5081565194396, -5.4454231146117);
    glVertex2f(9.5036493923277, -5.4582684272564);
    glVertex2f(9.4914801491257, -5.4643530490354);
    glVertex2f(9.4790855495681, -5.4636769799489);
    glVertex2f(6.3867152193776, -5.4610316581685);
    glEnd();

    //body inner
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.63f, 0.71f);
    glVertex2f(6.3861654585169, -5.4382735747624);
    glVertex2f(6.3756116262426, -5.437181798978);
    glVertex2f(6.3734280747376, -5.4266279663949);
    glVertex2f(6.38, -5.14);
    glVertex2f(6.383675765991, -5.1235049496866);
    glVertex2f(6.3942832717999, -5.1072401069704);
    glVertex2f(6.4073336440125, -5.091980852908);
    glVertex2f(6.4248943585049, -5.075276758146);
    glVertex2f(6.4475947943121, -5.0517197014303);
    glVertex2f(6.4732934008863, -5.0285909548368);
    glVertex2f(6.5088431399807, -5.000322486778);
    glVertex2f(6.5519723797425, -4.9678489818959);
    glVertex2f(6.5826608464807, -4.9499473757748);
    glVertex2f(6.6144453298882, -4.9364298364589);
    glVertex2f(6.6494863580076, -4.9250124246943);
    glVertex2f(6.6915019334674, -4.9208429399846);
    glVertex2f(9.4660675237434, -4.9208429399846);
    glVertex2f(9.4762473741756, -4.9137694391819);
    glVertex2f(9.4809059497971, -4.916530076668);
    glVertex2f(9.4819411888241, -4.9225689711689);
    glVertex2f(9.4819411888241, -5.4314777986638);
    glVertex2f(9.475732624747, -5.4396534477437);
    glVertex2f(9.4641151272927, -5.4382735747624);
    glEnd();

    //door handel
    glLineWidth(4);
    glBegin(GL_LINES);
    glColor3f(0.25f, 0.3f, 0.4f);
    glVertex2f(7.8, -5.0267297314447);
    glVertex2f(8.0, -5.0267297314447);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.25f, 0.3f, 0.4f);
    glVertex2f(8.55, -5.0267297314447);
    glVertex2f(8.75, -5.0267297314447);
    glEnd();

    //door lines
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3f(0.25f, 0.3f, 0.4f);
    glVertex2f(7.1203, -4.9141927409667);
    glVertex2f(7.1203, -5.5141751374083);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.25f, 0.3f, 0.4f);
    glVertex2f(8.1006998992614, -4.9133289705148);
    glVertex2f(8.1021853257039, -5.452538784896);
    glEnd();
    glBegin(GL_LINES);
    glColor3f(0.25f, 0.3f, 0.4f);
    glVertex2f(8.87, -4.9058369163901);
    glVertex2f(8.87, -5.4639699926414);
    glEnd();


    //bottom line after body
    glLineWidth(5.5);
    glBegin(GL_LINES);
    glColor3f(0.15f, 0.2f, 0.3f);
    glVertex2f(6.36, -5.5);
    glVertex2f(9.4977164881537, -5.5);
    glEnd();


    //light
    glBegin(GL_POLYGON);
    glColor3f(0.968f, 0.702f, 0.078f);
    glVertex2f(6.3455269303444, -5.1425960161115);
    glVertex2f(6.45, -5.1425960161115);
    glVertex2f(6.45, -5.3242681679123);
    glVertex2f(6.3449609124142, -5.3242681679123);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.968f, 0.702f, 0.078f);
    glVertex2f(9.5086641763682, -4.9678740944998);
    glVertex2f(9.4421694917116, -4.9678740944998);
    glVertex2f(9.4421694917116, -5.1314721329657);
    glVertex2f(9.5086641763682, -5.1314721329657);
    glEnd();

    //looking glass
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(7.181398755201, -5.0548007741726);
    glVertex2f(7.2500747439487, -5.0548007741726);
    glVertex2f(7.2500747439487, -4.9864197306622);
    glVertex2f(7.181398755201, -4.9864197306622);
    glEnd();
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(7.2153, -4.9862863166613);
    glVertex2f(7.2153, -4.9258104280952);
    glEnd();
    glBegin(GL_POLYGON);
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(7.1895782276203, -4.9273759896126);
    glVertex2f(7.2900924862201, -4.8035264542084);
    glVertex2f(7.3843604692456, -4.8134093882018);
    glVertex2f(7.2917890195152, -4.9285136412202);
    glEnd();


}

///8
void leftWheel()
{
    // Common center coordinates
    float cx = 6.9143095282631; // Center x-coordinate
    float cy = -5.4814124140302; // Center y-coordinate

    // Draw the larger circle
    float outerRadius = 0.2925369798579; // Radius of the larger circle
    int num_segments = 100; // Number of segments for smoothness

    glBegin(GL_POLYGON);
    glColor3f(0.08f, 0.1f, 0.15f); // Color #14181d
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * PI * (float)i / (float)num_segments;
        float x = outerRadius * cosf(theta);
        float y = outerRadius * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();

    // Draw the lines on the larger circle
    glLineWidth(2.5);
    glColor3f(0.225f, 0.225f, 0.27f); // Color of the lines

    glBegin(GL_LINES);
    // Vertical line (top to bottom)
    glVertex2f(cx, cy + outerRadius); // Top
    glVertex2f(cx, cy - outerRadius); // Bottom

    // Horizontal line (left to right)
    glVertex2f(cx - outerRadius, cy); // Left
    glVertex2f(cx + outerRadius, cy); // Right

    // Diagonal line (upper-left to lower-right)
    glVertex2f(cx - outerRadius / 1.414f, cy + outerRadius / 1.414f); // Upper left
    glVertex2f(cx + outerRadius / 1.414f, cy - outerRadius / 1.414f); // Lower right

    // Diagonal line (upper-right to lower-left)
    glVertex2f(cx + outerRadius / 1.414f, cy + outerRadius / 1.414f); // Upper right
    glVertex2f(cx - outerRadius / 1.414f, cy - outerRadius / 1.414f); // Lower left
    glEnd();

    // Draw the smaller circle (on top of the larger circle)
    float innerRadius = 0.1434671749118; // Radius of the smaller circle

    glBegin(GL_POLYGON);
    glColor3f(0.31f, 0.33f, 0.36f); // Color #535961
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * PI * (float)i / (float)num_segments;
        float x = innerRadius * cosf(theta);
        float y = innerRadius * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

///9
void rightWheel()
{
    // Common center coordinates
    float cx = 8.9105434751588; // Center x-coordinate for the right wheel
    float cy = -5.4813860810583; // Center y-coordinate for the right wheel

    // Draw the larger circle
    float outerRadius = 0.2925369798579; // Radius of the larger circle
    int num_segments = 100; // Number of segments for smoothness

    glBegin(GL_POLYGON);
    glColor3f(0.08f, 0.1f, 0.15f); // Color #14181d
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * PI * (float)i / (float)num_segments;
        float x = outerRadius * cosf(theta);
        float y = outerRadius * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();

    // Draw the lines on the larger circle
    glLineWidth(2.5);
    glColor3f(0.225f, 0.225f, 0.27f); // Color of the lines

    glBegin(GL_LINES);
    // Vertical line (top to bottom)
    glVertex2f(cx, cy + outerRadius); // Top
    glVertex2f(cx, cy - outerRadius); // Bottom

    // Horizontal line (left to right)
    glVertex2f(cx - outerRadius, cy); // Left
    glVertex2f(cx + outerRadius, cy); // Right

    // Diagonal line (upper-left to lower-right)
    glVertex2f(cx - outerRadius / 1.414f, cy + outerRadius / 1.414f); // Upper left
    glVertex2f(cx + outerRadius / 1.414f, cy - outerRadius / 1.414f); // Lower right

    // Diagonal line (upper-right to lower-left)
    glVertex2f(cx + outerRadius / 1.414f, cy + outerRadius / 1.414f); // Upper right
    glVertex2f(cx - outerRadius / 1.414f, cy - outerRadius / 1.414f); // Lower left
    glEnd();

    // Draw the smaller circle (on top of the larger circle)
    float innerRadius = 0.1434671749118; // Radius of the smaller circle

    glBegin(GL_POLYGON);
    glColor3f(0.31f, 0.33f, 0.36f); // Color #535961
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * PI * (float)i / (float)num_segments;
        float x = innerRadius * cosf(theta);
        float y = innerRadius * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();
}

///10
void car()
{
    glPushMatrix();

    glTranslatef(_moveCar, 0.0f, 0.0f);

    drawCar();

    glPushMatrix();
    glTranslatef(6.9143095282631f, -5.4814124140302f, 0.0f);
    glRotatef(rotationAngle1, 0.0f, 0.0f, 1.0f); // Rotate around Z-axis
    glTranslatef(-6.9143095282631f, 5.4814124140302f, 0.0f);
    leftWheel();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8.9105434751588f, -5.4813860810583f, 0.0f);
    glRotatef(rotationAngle1, 0.0f, 0.0f, 1.0f); // Rotate around Z-axis
    glTranslatef(-8.9105434751588f, 5.4813860810583f, 0.0f);
    rightWheel();
    glPopMatrix();

    glPopMatrix();
}

///11
void sun() {

    //sky
    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-10, -6);
    glVertex2f(10, -6);
    glColor3f(1.0f, 1.0f, 0.8f);
    glVertex2f(10, 5.25);
    glVertex2f(-10, 5.25);
    glEnd();

    float centerX = -5.6962419710145f;
    float centerY = 2.7503445625565f;
    float pointX = -5.7970276268865f;
    float pointY = 2.2640137786659f;

    // Calculate radius and increase it by 0.10
    float radius = sqrt(pow(pointX - centerX, 2) + pow(pointY - centerY, 2)) + 0.10f;

    glBegin(GL_TRIANGLE_FAN);

    // Apply plain deep yellow color (#FFAA00)
    glColor3f(1, 0.8, 0); // RGB for #FFAA00
    glVertex2f(centerX, centerY);

    // Draw perimeter vertices with the same deep yellow color
    for (int i = 0; i <= 100; ++i) {
        float angle1 = 2.0f * M_PI * i / 100; // Angle in radians
        float x = radius * cos(angle1) + centerX;
        float y = radius * sin(angle1) + centerY;

        glVertex2f(x, y);
    }

    glEnd();
}

///12
void cloud1()
{
    glPushMatrix();  // Save the current transformation matrix
    glTranslatef(-9.00 + 8.6324562544849, 3.84 - 3.2888936790942, 0.0f); // Adjust based on old leftmost point
    glScalef(0.9f, 0.9f, 1.0f);

    const float centerX = -7.5953f, centerY = 2.914f;
    const float radius = 0.3535f;

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 1.0f, 1.0f);
    int numSegments = 100; // More segments for a smoother circle

    for (int i = 0; i < numSegments; i++) {
        float theta = 2.0f * PI * float(i) / float(numSegments);
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        glVertex2f(centerX + x, centerY + y);
    }
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-7.782331057721, 2.8200435957381); //T1
    glVertex2f(-7.907222512193, 2.7426626418646);//U1
    glVertex2f(-8.0352952523352, 2.7321154747208); //V1
    glVertex2f(-8.1483006112843, 2.7562232853353);
    glVertex2f(-8.2477453271594, 2.8210130263619);
    glVertex2f(-8.3080148519322, 2.9129240543298);
    glVertex2f(-8.3245889712447, 3.0515439653634);
    glVertex2f(-8.3865893687159, 3.0592973893417);
    glVertex2f(-8.4787894508793, 3.0954542853657);
    glVertex2f(-8.5673738435461, 3.1623445430101);
    glVertex2f(-8.6324562544849, 3.2888936790942);
    glVertex2f(-8.6342640992332, 3.4371369527927);
    glVertex2f(-8.5818366015325, 3.5528390200695);
    glVertex2f(-8.4932522088657, 3.6359998809248);
    glVertex2f(-8.3612795422396, 3.6848116905572);
    glVertex2f(-8.2708873048245, 3.6848116905572);
    glVertex2f(-8.184110756906, 3.6504626393344); //F22
    glVertex2f(-8.1636459746823, 3.7772468641007);
    glVertex2f(-8.1141506955437, 3.8870645179028);
    glVertex2f(-8.0213470471588, 3.9845083515583);
    glVertex2f(-7.8651275723775, 4.0572045449203);
    glVertex2f(-7.6996277327577, 4.0556578174019);
    glVertex2f(-7.5789829898573, 4.0061625368151);
    glVertex2f(-7.4923662513647, 3.928826160898);
    glVertex2f(-7.4165766051837, 3.8190085070958);
    glVertex2f(-7.3140176701459, 3.900846929518);
    glVertex2f(-7.2015926400386, 3.9250243560549);
    glVertex2f(-7.1000474515545, 3.9141445141133);
    glVertex2f(-6.9900401640302, 3.8537009477708);
    glVertex2f(-6.9445276591897, 3.9251879711408);
    glVertex2f(-6.8821934066571, 3.9895659715419);
    glVertex2f(-6.8116841701858, 4.0406596226538);
    glVertex2f(-6.7227812198524, 4.0794907974989);
    glVertex2f(-6.6134408096723, 4.088687654699);
    glVertex2f(-6.5092097644538, 4.0774470514544);
    glVertex2f(-6.4192849411281, 4.0386158766093);
    glVertex2f(-6.3426444667027, 3.9844566064307);
    glVertex2f(-6.2905289440935, 3.9211004790519);
    glVertex2f(-6.2506758973923, 3.8495693674952);
    glVertex2f(-6.2312603105379, 3.7657757796716);
    glVertex2f(-6.2251290725839, 3.66461035047);//F23
    glVertex2f(-6.0948194846746, 3.6793237962297);
    glVertex2f(-5.9901751670644, 3.651115327179);
    glVertex2f(-5.9146492682675, 3.5974282409211);
    glVertex2f(-5.8545925294652, 3.5291819448306);
    glVertex2f(-5.814554703597, 3.4381868833766);
    glVertex2f(-5.8090950000695, 3.3080639454973);
    glVertex2f(-5.8471739132494, 3.2054226572304);
    glVertex2f(-5.9045060809866, 3.133452487114);
    glVertex2f(-5.9837952491337, 3.0785599844828);
    glVertex2f(-6.064304250637, 3.0480641496878);
    glVertex2f(-6.1350545852914, 3.0492839830796);//Q23
    glVertex2f(-6.1546217226534, 2.9647288416334);
    glVertex2f(-6.1947648710781, 2.8883781453367);
    glVertex2f(-6.2498633100924, 2.8269827400671);
    glVertex2f(-6.3475306752189, 2.7649694276161);
    glVertex2f(-6.4675262670093, 2.7540607371341);
    glVertex2f(-6.5588865471225, 2.7745145317878);
    glVertex2f(-6.6257022743695, 2.8113313621644);
    glVertex2f(-6.7109416346694, 2.7032319651989);//A24
    glVertex2f(-6.827028329735, 2.6258408328907);
    glVertex2f(-6.9704295412867, 2.5803166374152);//C24
    glVertex2f(-7.1115545431313, 2.5894214765103);
    glVertex2f(-7.2299174479041, 2.6349456719857);
    glVertex2f(-7.3209658361909, 2.7032319651989);
    glVertex2f(-7.4, 2.8);//G24
    glVertex2f(-7.505685587383, 2.7683746274572);
    glVertex2f(-7.6639019197956, 2.771814113045);//I24
    glEnd();

    glPopMatrix();


}

///13
void cloud2()
{

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-3.2510391774401, 3.1299843676039);//G25
    glVertex2f(-3.2144071871764, 3.2136227646783);
    glVertex2f(-3.1659853272069, 3.2857175360757);
    glVertex2f(-3.1046509712456, 3.3470518938317);
    glVertex2f(-3.0250239126292, 3.3836373002125);
    glVertex2f(-2.9271041513576, 3.3890175070332);
    glVertex2f(-2.8431729274106, 3.3664206383862);//M25


    glVertex2f(-2.0860305483494, 3.4015842029066);//Z25
    glVertex2f(-1.9987745202565, 3.4691849910191);
    glVertex2f(-1.9035049817774, 3.5123259153663);
    glVertex2f(-1.8082354432984, 3.5329976082827);
    glVertex2f(-1.6824077509675, 3.5240099157104);
    glVertex2f(-1.5853406740266, 3.488059145421);
    glVertex2f(-1.5089452893972, 3.434132989987);
    glVertex2f(-1.4451850379705, 3.3577907850739);
    glVertex2f(-1.4012980888746, 3.2723679709412);
    glVertex2f(-1.3793546143266, 3.190863634521);
    glVertex2f(-1.384056787444, 3.0819299541133);//J26
    glVertex2f(-1.2743294366478, 3.0707326112405);
    glVertex2f(-1.1829576461811, 3.0270330579994);
    glVertex2f(-1.1, 2.95);
    glVertex2f(-1.05, 2.85);
    glVertex2f(-1.0508658186586, 2.731067901958);//O26
    glVertex2f(-1.093672738414, 2.6250075399999);
    glVertex2f(-1.1618474222246, 2.5474294492557);
    glVertex2f(-1.2488289153623, 2.499236998945);
    glVertex2f(-1.3416875364147, 2.4780793378329);
    glVertex2f(-1.4098622202253, 2.4839564659196);//T26
    glVertex2f(-1.4376199446041, 2.3875949702247);
    glVertex2f(-1.5067322848102, 2.2864861732609);
    glVertex2f(-1.5784043413203, 2.2263328383584);
    glVertex2f(-1.6679944119579, 2.1904968090548);
    glVertex2f(-1.7767823548749, 2.1853773762971);
    glVertex2f(-1.8625328510566, 2.2071349655172);
    glVertex2f(-1.9354847657186, 2.2455307111996);
    glVertex2f(-1.9789999428855, 2.2890458896397);
    glVertex2f(-2.0301942689641, 2.2135342564642);
    glVertex2f(-2.0993066091702, 2.1495413469935);
    glVertex2f(-2.1735383819842, 2.1098657431216);
    glVertex2f(-2.2887256156611, 2.0791491465757);
    glVertex2f(-2.4077524237939, 2.0817088629545);
    glVertex2f(-2.4908665582469, 2.1081463754708);
    glVertex2f(-2.5609684949462, 2.1459645266389);
    glVertex2f(-2.6190793108943, 2.1930066171162);
    glVertex2f(-2.6688885817069, 2.2548070104884);//M27
    glVertex2f(-2.7288441854629, 2.2243680107678);
    glVertex2f(-2.7878773953149, 2.2022305564255);
    glVertex2f(-2.8496777868788, 2.1883946474616);
    glVertex2f(-2.9287959612636, 2.1892825584058);
    glVertex2f(-3.0138950338932, 2.2179572467614);
    glVertex2f(-3.0814192980449, 2.2595817943743);
    glVertex2f(-3.1276687940393, 2.3123062213506);
    glVertex2f(-3.1600434412354, 2.3733555578495);
    glVertex2f(-3.1822571175342, 2.4355350703216);//P24
    glVertex2f(-3.2945807690399, 2.410878658294);
    glVertex2f(-3.4142779056399, 2.4180433754078);
    glVertex2f(-3.4928295564334, 2.4494866995973);
    glVertex2f(-3.5600907958861, 2.4940838270611);
    glVertex2f(-3.613461127191, 2.5503785617285);
    glVertex2f(-3.6667585494413, 2.6343724315915);
    glVertex2f(-3.6910142069645, 2.7325500958677);
    glVertex2f(-3.6910142069645, 2.8376579482104);//Z24
    glVertex2f(-3.6667585494413, 2.9219752363535);
    glVertex2f(-3.6063345967906, 3.0091010273308);
    glVertex2f(-3.5388973619423, 3.0678973063848);
    glVertex2f(-3.4649573184721, 3.1057139709456);
    glVertex2f(-3.397790408755, 3.1249045171406);
    glVertex2f(-3.3306234990378, 3.1328065067503);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-2.8431729274106, 3.3664206383862);
    glVertex2f(-2.8233719867067, 3.4550003597724);
    glVertex2f(-2.778054373157, 3.5375106373133);
    glVertex2f(-2.7036115172287, 3.6305642099465);
    glVertex2f(-2.6, 3.7);
    glVertex2f(-2.4935763165738, 3.7183004355721);
    glVertex2f(-2.3579839718473, 3.7050070680531);
    glVertex2f(-2.2649304019369, 3.6611389552403);
    glVertex2f(-2.1971941759914, 3.603649725071);
    glVertex2f(-2.15, 3.55);
    glVertex2f(-2.1119750655754, 3.4872614483458);
    glVertex2f(-2.0860305483494, 3.4015842029066);//Z25
    glEnd();
}

///14
void cloud3()
{

    glPushMatrix();  // Save the current transformation matrix
    glTranslatef(0.0 + 8.6324562544849, 4.5 - 3.2888936790942, 0.0f); // Adjust based on old leftmost point
    glScalef(0.8f, 0.8f, 1.0f);

    const float centerX = -7.5953f, centerY = 2.914f;
    const float radius = 0.3535f;

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0f, 1.0f, 1.0f);
    int numSegments = 100; // More segments for a smoother circle

    for (int i = 0; i < numSegments; i++) {
        float theta = 2.0f * PI * float(i) / float(numSegments);
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        glVertex2f(centerX + x, centerY + y);
    }
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-7.782331057721, 2.8200435957381); //T1
    glVertex2f(-7.907222512193, 2.7426626418646);//U1
    glVertex2f(-8.0352952523352, 2.7321154747208); //V1
    glVertex2f(-8.1483006112843, 2.7562232853353);
    glVertex2f(-8.2477453271594, 2.8210130263619);
    glVertex2f(-8.3080148519322, 2.9129240543298);
    glVertex2f(-8.3245889712447, 3.0515439653634);
    glVertex2f(-8.3865893687159, 3.0592973893417);
    glVertex2f(-8.4787894508793, 3.0954542853657);
    glVertex2f(-8.5673738435461, 3.1623445430101);
    glVertex2f(-8.6324562544849, 3.2888936790942);
    glVertex2f(-8.6342640992332, 3.4371369527927);
    glVertex2f(-8.5818366015325, 3.5528390200695);
    glVertex2f(-8.4932522088657, 3.6359998809248);
    glVertex2f(-8.3612795422396, 3.6848116905572);
    glVertex2f(-8.2708873048245, 3.6848116905572);
    glVertex2f(-8.184110756906, 3.6504626393344); //F22
    glVertex2f(-8.1636459746823, 3.7772468641007);
    glVertex2f(-8.1141506955437, 3.8870645179028);
    glVertex2f(-8.0213470471588, 3.9845083515583);
    glVertex2f(-7.8651275723775, 4.0572045449203);
    glVertex2f(-7.6996277327577, 4.0556578174019);
    glVertex2f(-7.5789829898573, 4.0061625368151);
    glVertex2f(-7.4923662513647, 3.928826160898);
    glVertex2f(-7.4165766051837, 3.8190085070958);
    glVertex2f(-7.3140176701459, 3.900846929518);
    glVertex2f(-7.2015926400386, 3.9250243560549);
    glVertex2f(-7.1000474515545, 3.9141445141133);
    glVertex2f(-6.9900401640302, 3.8537009477708);
    glVertex2f(-6.9445276591897, 3.9251879711408);
    glVertex2f(-6.8821934066571, 3.9895659715419);
    glVertex2f(-6.8116841701858, 4.0406596226538);
    glVertex2f(-6.7227812198524, 4.0794907974989);
    glVertex2f(-6.6134408096723, 4.088687654699);
    glVertex2f(-6.5092097644538, 4.0774470514544);
    glVertex2f(-6.4192849411281, 4.0386158766093);
    glVertex2f(-6.3426444667027, 3.9844566064307);
    glVertex2f(-6.2905289440935, 3.9211004790519);
    glVertex2f(-6.2506758973923, 3.8495693674952);
    glVertex2f(-6.2312603105379, 3.7657757796716);
    glVertex2f(-6.2251290725839, 3.66461035047);//F23
    glVertex2f(-6.0948194846746, 3.6793237962297);
    glVertex2f(-5.9901751670644, 3.651115327179);
    glVertex2f(-5.9146492682675, 3.5974282409211);
    glVertex2f(-5.8545925294652, 3.5291819448306);
    glVertex2f(-5.814554703597, 3.4381868833766);
    glVertex2f(-5.8090950000695, 3.3080639454973);
    glVertex2f(-5.8471739132494, 3.2054226572304);
    glVertex2f(-5.9045060809866, 3.133452487114);
    glVertex2f(-5.9837952491337, 3.0785599844828);
    glVertex2f(-6.064304250637, 3.0480641496878);
    glVertex2f(-6.1350545852914, 3.0492839830796);//Q23
    glVertex2f(-6.1546217226534, 2.9647288416334);
    glVertex2f(-6.1947648710781, 2.8883781453367);
    glVertex2f(-6.2498633100924, 2.8269827400671);
    glVertex2f(-6.3475306752189, 2.7649694276161);
    glVertex2f(-6.4675262670093, 2.7540607371341);
    glVertex2f(-6.5588865471225, 2.7745145317878);
    glVertex2f(-6.6257022743695, 2.8113313621644);
    glVertex2f(-6.7109416346694, 2.7032319651989);//A24
    glVertex2f(-6.827028329735, 2.6258408328907);
    glVertex2f(-6.9704295412867, 2.5803166374152);//C24
    glVertex2f(-7.1115545431313, 2.5894214765103);
    glVertex2f(-7.2299174479041, 2.6349456719857);
    glVertex2f(-7.3209658361909, 2.7032319651989);
    glVertex2f(-7.4, 2.8);//G24
    glVertex2f(-7.505685587383, 2.7683746274572);
    glVertex2f(-7.6639019197956, 2.771814113045);//I24
    glEnd();

    glPopMatrix();


}

///15
void cloud4()
{

    glPushMatrix();  // Save the current transformation matrix

    // Translate the cloud to (5.1251, 2.9605)
    glTranslatef(6.5 + 3.2510, 3.38 - 3.1299, 0.0f); // Adjust based on old leftmost point

    // Scale down the cloud by 10% (reduce to 90% of original size)
    glScalef(0.9f, 0.9f, 1.0f);




    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-3.2510391774401, 3.1299843676039);//G25
    glVertex2f(-3.2144071871764, 3.2136227646783);
    glVertex2f(-3.1659853272069, 3.2857175360757);
    glVertex2f(-3.1046509712456, 3.3470518938317);
    glVertex2f(-3.0250239126292, 3.3836373002125);
    glVertex2f(-2.9271041513576, 3.3890175070332);
    glVertex2f(-2.8431729274106, 3.3664206383862);//M25


    glVertex2f(-2.0860305483494, 3.4015842029066);//Z25
    glVertex2f(-1.9987745202565, 3.4691849910191);
    glVertex2f(-1.9035049817774, 3.5123259153663);
    glVertex2f(-1.8082354432984, 3.5329976082827);
    glVertex2f(-1.6824077509675, 3.5240099157104);
    glVertex2f(-1.5853406740266, 3.488059145421);
    glVertex2f(-1.5089452893972, 3.434132989987);
    glVertex2f(-1.4451850379705, 3.3577907850739);
    glVertex2f(-1.4012980888746, 3.2723679709412);
    glVertex2f(-1.3793546143266, 3.190863634521);
    glVertex2f(-1.384056787444, 3.0819299541133);//J26
    glVertex2f(-1.2743294366478, 3.0707326112405);
    glVertex2f(-1.1829576461811, 3.0270330579994);
    glVertex2f(-1.1, 2.95);
    glVertex2f(-1.05, 2.85);
    glVertex2f(-1.0508658186586, 2.731067901958);//O26
    glVertex2f(-1.093672738414, 2.6250075399999);
    glVertex2f(-1.1618474222246, 2.5474294492557);
    glVertex2f(-1.2488289153623, 2.499236998945);
    glVertex2f(-1.3416875364147, 2.4780793378329);
    glVertex2f(-1.4098622202253, 2.4839564659196);//T26
    glVertex2f(-1.4376199446041, 2.3875949702247);
    glVertex2f(-1.5067322848102, 2.2864861732609);
    glVertex2f(-1.5784043413203, 2.2263328383584);
    glVertex2f(-1.6679944119579, 2.1904968090548);
    glVertex2f(-1.7767823548749, 2.1853773762971);
    glVertex2f(-1.8625328510566, 2.2071349655172);
    glVertex2f(-1.9354847657186, 2.2455307111996);
    glVertex2f(-1.9789999428855, 2.2890458896397);
    glVertex2f(-2.0301942689641, 2.2135342564642);
    glVertex2f(-2.0993066091702, 2.1495413469935);
    glVertex2f(-2.1735383819842, 2.1098657431216);
    glVertex2f(-2.2887256156611, 2.0791491465757);
    glVertex2f(-2.4077524237939, 2.0817088629545);
    glVertex2f(-2.4908665582469, 2.1081463754708);
    glVertex2f(-2.5609684949462, 2.1459645266389);
    glVertex2f(-2.6190793108943, 2.1930066171162);
    glVertex2f(-2.6688885817069, 2.2548070104884);//M27
    glVertex2f(-2.7288441854629, 2.2243680107678);
    glVertex2f(-2.7878773953149, 2.2022305564255);
    glVertex2f(-2.8496777868788, 2.1883946474616);
    glVertex2f(-2.9287959612636, 2.1892825584058);
    glVertex2f(-3.0138950338932, 2.2179572467614);
    glVertex2f(-3.0814192980449, 2.2595817943743);
    glVertex2f(-3.1276687940393, 2.3123062213506);
    glVertex2f(-3.1600434412354, 2.3733555578495);
    glVertex2f(-3.1822571175342, 2.4355350703216);//P24
    glVertex2f(-3.2945807690399, 2.410878658294);
    glVertex2f(-3.4142779056399, 2.4180433754078);
    glVertex2f(-3.4928295564334, 2.4494866995973);
    glVertex2f(-3.5600907958861, 2.4940838270611);
    glVertex2f(-3.613461127191, 2.5503785617285);
    glVertex2f(-3.6667585494413, 2.6343724315915);
    glVertex2f(-3.6910142069645, 2.7325500958677);
    glVertex2f(-3.6910142069645, 2.8376579482104);//Z24
    glVertex2f(-3.6667585494413, 2.9219752363535);
    glVertex2f(-3.6063345967906, 3.0091010273308);
    glVertex2f(-3.5388973619423, 3.0678973063848);
    glVertex2f(-3.4649573184721, 3.1057139709456);
    glVertex2f(-3.397790408755, 3.1249045171406);
    glVertex2f(-3.3306234990378, 3.1328065067503);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex2f(-2.8431729274106, 3.3664206383862);
    glVertex2f(-2.8233719867067, 3.4550003597724);
    glVertex2f(-2.778054373157, 3.5375106373133);
    glVertex2f(-2.7036115172287, 3.6305642099465);
    glVertex2f(-2.6, 3.7);
    glVertex2f(-2.4935763165738, 3.7183004355721);
    glVertex2f(-2.3579839718473, 3.7050070680531);
    glVertex2f(-2.2649304019369, 3.6611389552403);
    glVertex2f(-2.1971941759914, 3.603649725071);
    glVertex2f(-2.15, 3.55);
    glVertex2f(-2.1119750655754, 3.4872614483458);
    glVertex2f(-2.0860305483494, 3.4015842029066);//Z25
    glEnd();

    glPopMatrix();
}

///16
void flower()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, grass);

    glBegin(GL_QUADS);
    glColor3f(1.0f, 1.0f, 1.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-10.0f, -6.0f);   // Bottom-left
    glTexCoord2f(1.0f, 1.0f); glVertex2f(10.0f, -6.0f);    // Bottom-right
    glTexCoord2f(1.0f, 0.0f); glVertex2f(10.0f, 5.25f);    // Top-right
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-10.0f, 5.25f);   // Top-left
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

///17
void tree()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, ttp);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-10.0f, -6.0f);   // Bottom-left
    glTexCoord2f(1.0f, 1.0f); glVertex2f(10.0f, -6.0f);    // Bottom-right
    glTexCoord2f(1.0f, 0.0f); glVertex2f(10.0f, 5.25f);    // Top-right
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-10.0f, 5.25f);   // Top-left
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

///18
void text1()
{
    if (moveJeep) return;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, t1);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-10.0f, -6.0f);   // Bottom-left
    glTexCoord2f(1.0f, 1.0f); glVertex2f(10.0f, -6.0f);    // Bottom-right
    glTexCoord2f(1.0f, 0.0f); glVertex2f(10.0f, 5.25f);    // Top-right
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-10.0f, 5.25f);   // Top-left
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

///19
void text2()
{
    if (moveJeep) return;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, t2);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-10.0f, -6.0f);   // Bottom-left
    glTexCoord2f(1.0f, 1.0f); glVertex2f(10.0f, -6.0f);    // Bottom-right
    glTexCoord2f(1.0f, 0.0f); glVertex2f(10.0f, 5.25f);    // Top-right
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-10.0f, 5.25f);   // Top-left
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

///20
void text3()
{
    if (moveJeep) return;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, t3);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-10.0f, -6.0f);   // Bottom-left
    glTexCoord2f(1.0f, 1.0f); glVertex2f(10.0f, -6.0f);    // Bottom-right
    glTexCoord2f(1.0f, 0.0f); glVertex2f(10.0f, 5.25f);    // Top-right
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-10.0f, 5.25f);   // Top-left
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

///21
void people()
{
    if (moveJeep) return;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, p1);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-10.0f, -6.0f);   // Bottom-left
    glTexCoord2f(1.0f, 1.0f); glVertex2f(10.0f, -6.0f);    // Bottom-right
    glTexCoord2f(1.0f, 0.0f); glVertex2f(10.0f, 5.25f);    // Top-right
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-10.0f, 5.25f);   // Top-left
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

///22
void update01(int value)
{
    if (carStarted == true)
    {
        rotationAngle1 +=5.0f; // Increment rotation angle
        if (rotationAngle1 > 360.0f)
            rotationAngle1 -= 360.0f; // Keep angle in range [0, 360]
    }
        glutPostRedisplay(); // Request display update
        glutTimerFunc(16, update01, 0); // Schedule next update after ~16ms (60 FPS)
}

///23
void update02(int value)
{
    if (start == true)
    {
        carStarted = true;

        _moveCar -= .1;

        if (_moveCar <= -20.0)
        {
            _moveCar = -20.0;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, update02, 0);
}

///24
void update03(int value)
{
    if (start == true)
    {

        _movePlane1 -= .05;

        if (_movePlane1 <= -20.0)
        {
            _movePlane1 = -20.0;
        }

        _movePlane2 += .001;

        if (_movePlane2 <= 2.0)
        {
            _movePlane2 = 2.0;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, update03, 0);
}

///25
void Hill_Texture1()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-10.0f, -6.0f);   // Bottom-left
    glTexCoord2f(1.0f, 1.0f); glVertex2f(10.0f, -6.0f);    // Bottom-right
    glTexCoord2f(1.0f, 0.0f); glVertex2f(10.0f, 5.25f);    // Top-right
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-10.0f, 5.25f);   // Top-left
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

///26
void Hill_Texture2()
{
    if (msg1 || msg2 == true)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture4);

        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-10.0f, -6.0f);   // Bottom-left
        glTexCoord2f(1.0f, 1.0f); glVertex2f(10.0f, -6.0f);    // Bottom-right
        glTexCoord2f(1.0f, 0.0f); glVertex2f(10.0f, 5.25f);    // Top-right
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-10.0f, 5.25f);   // Top-left
        glEnd();

        glDisable(GL_TEXTURE_2D);
    }
}

///27
void Hill_Texture3()
{
    if (moveJeep == true)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture5);

        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-10.0f, -6.0f);   // Bottom-left
        glTexCoord2f(1.0f, 1.0f); glVertex2f(10.0f, -6.0f);    // Bottom-right
        glTexCoord2f(1.0f, 0.0f); glVertex2f(10.0f, 5.25f);    // Top-right
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-10.0f, 5.25f);   // Top-left
        glEnd();

        glDisable(GL_TEXTURE_2D);
    }
}

///28
void Msg_Texture1()
{
    if (!msg1) return;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-10.0f, -6.0f);   // Bottom-left
    glTexCoord2f(1.0f, 1.0f); glVertex2f(10.0f, -6.0f);    // Bottom-right
    glTexCoord2f(1.0f, 0.0f); glVertex2f(10.0f, 5.25f);    // Top-right
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-10.0f, 5.25f);   // Top-left
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

///29
void Msg_Texture2()
{
    if (!msg2) return;

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture3);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-10.0f, -6.0f);   // Bottom-left
    glTexCoord2f(1.0f, 1.0f); glVertex2f(10.0f, -6.0f);    // Bottom-right
    glTexCoord2f(1.0f, 0.0f); glVertex2f(10.0f, 5.25f);    // Top-right
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-10.0f, 5.25f);   // Top-left
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

///30
void Destroy_Texture1()
{
    if (startScene4 == true)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture6);

        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-10.0f, -6.0f);   // Bottom-left
        glTexCoord2f(1.0f, 1.0f); glVertex2f(10.0f, -6.0f);    // Bottom-right
        glTexCoord2f(1.0f, 0.0f); glVertex2f(10.0f, 5.25f);    // Top-right
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-10.0f, 5.25f);   // Top-left
        glEnd();

        glDisable(GL_TEXTURE_2D);
    }
}

///31
void Destroy_Texture2()
{
    if (startScene5 == true)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture7);

        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-10.0f, -6.0f);   // Bottom-left
        glTexCoord2f(1.0f, 1.0f); glVertex2f(10.0f, -6.0f);    // Bottom-right
        glTexCoord2f(1.0f, 0.0f); glVertex2f(10.0f, 5.25f);    // Top-right
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-10.0f, 5.25f);   // Top-left
        glEnd();

        glDisable(GL_TEXTURE_2D);
    }
}

///32
void Destroy_Texture3()
{
    if (startScene6 == true)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture8);

        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-10.0f, -6.0f);   // Bottom-left
        glTexCoord2f(1.0f, 1.0f); glVertex2f(10.0f, -6.0f);    // Bottom-right
        glTexCoord2f(1.0f, 0.0f); glVertex2f(10.0f, 5.25f);    // Top-right
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-10.0f, 5.25f);   // Top-left
        glEnd();

        glDisable(GL_TEXTURE_2D);
    }
}

///33
void C1()
{
    if (startScene5 == true)
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        //glScalef(4.0, 4.0, 1.0);
        glTranslatef(0.0, moveC, 0.0);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture9);

        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-10.0f, -6.0f);   // Bottom-left
        glTexCoord2f(1.0f, 1.0f); glVertex2f(10.0f, -6.0f);    // Bottom-right
        glTexCoord2f(1.0f, 0.0f); glVertex2f(10.0f, 5.25f);    // Top-right
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-10.0f, 5.25f);   // Top-left
        glEnd();

        glDisable(GL_TEXTURE_2D);

        glPopMatrix();
    }
}

///34
void C2()
{
    if (startC2 == true)
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glScalef(10.0, 10.0, 1.0);
        glTranslatef(-3.0, moveC2, 0.0);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture9);

        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-10.0f, -6.0f);   // Bottom-left
        glTexCoord2f(1.0f, 1.0f); glVertex2f(10.0f, -6.0f);    // Bottom-right
        glTexCoord2f(1.0f, 0.0f); glVertex2f(10.0f, 5.25f);    // Top-right
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-10.0f, 5.25f);   // Top-left
        glEnd();

        glDisable(GL_TEXTURE_2D);

        glPopMatrix();
    }
}

///35
void C_Front()
{
    if (startScene5 == true)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture10);

        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-10.0f, -6.0f);   // Bottom-left
        glTexCoord2f(1.0f, 1.0f); glVertex2f(10.0f, -6.0f);    // Bottom-right
        glTexCoord2f(1.0f, 0.0f); glVertex2f(10.0f, 5.25f);    // Top-right
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-10.0f, 5.25f);   // Top-left
        glEnd();

        glDisable(GL_TEXTURE_2D);

    }
}

///35
void waterTrack()
{
    if (startWaterTrack == true)
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture11);

        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-10.0f, -6.0f);   // Bottom-left
        glTexCoord2f(1.0f, 1.0f); glVertex2f(10.0f, -6.0f);    // Bottom-right
        glTexCoord2f(1.0f, 0.0f); glVertex2f(10.0f, 5.25f);    // Top-right
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-10.0f, 5.25f);   // Top-left
        glEnd();

        glDisable(GL_TEXTURE_2D);

    }
}

///37
void Sun()
{
    glColor3f(1.0f, 1.0f, 0.0f);

    // Calculate the sun's current position on the circular path
    float sunX = sunRadius * cos(-sunAngle * DEG_TO_RAD);
    float sunY = sunRadius * sin(-sunAngle * DEG_TO_RAD);

    glBegin(GL_POLYGON);
    int num = 100;
    float radius = sqrt(0.8457385144174f);
    for (int i = 0; i < num; i++) {
        float theta = 2.0f * 3.1415926f * i / num;
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        glVertex2f(x + sunX, y + sunY);
    }

    glEnd();
}

///38
void updateSun()
{
    if (startSun == true)
    {
        if (sunAngle >= 10.0)
        {
            sunAngle = 10.0;
        }
    }


}

///39
void Moon()
{
    glColor3f(1.0f, 1.0f, 1.0f);

    // Calculate the moon's current position on the circular path
    float moonX = moonRadius * cos(-moonAngle * DEG_TO_RAD);
    float moonY = moonRadius * sin(-moonAngle * DEG_TO_RAD);

    glBegin(GL_POLYGON);
    int num = 100;
    float radius = sqrt(0.8457385144174f);
    for (int i = 0; i < num; i++) {
        float theta = 2.0f * 3.1415926f * i / num;
        float x = radius * cosf(theta);
        float y = radius * sinf(theta);
        glVertex2f(x + moonX, y + moonY);
    }

    glEnd();
}

///40
void updateMoon()
{
    if (startMoon == true)
    {
         if (moonAngle >= 200.0 && startScene == true)
        {
            startSnow = true;
        }

        else
        {
            startSnow = false;
        }
    }
}

///41
void Sky()
{
   if (changeSkyColor == true)
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_POLYGON);

        // Top color (RGB: 0, 0, 0)
        glColor3ub(0, 0, 0);
        glVertex2f(-10.0f, 5.25f);  // Top-left
        glVertex2f(10.0f, 5.25f);   // Top-right

        // Middle color (RGB: 12, 46, 61) at 66.0781%
        glColor3ub(12, 46, 61);
        glVertex2f(10.0f, 1.434f); // Bottom-right of top segment
        glVertex2f(-10.0f, 1.434f);// Bottom-left of top segment
        glEnd();

        glBegin(GL_POLYGON);

        // Middle color (RGB: 12, 46, 61) at 66.0781%
        glColor3ub(12, 46, 61);
        glVertex2f(10.0f, 1.434f); // Bottom-right of top segment
        glVertex2f(-10.0f, 1.434f);// Bottom-left of top segment

        // Third color (RGB: 134, 116, 181) at 7.4854%
        glColor3ub(134, 116, 181);
        glVertex2f(-10.0f, -5.161f);// Bottom-left of middle segment
        glVertex2f(10.0f, -5.161f); // Bottom-right of middle segment

        glEnd();

        glBegin(GL_POLYGON);

        // Third color (RGB: 134, 116, 181) at 7.4854%
        glColor3ub(134, 116, 181);
        glVertex2f(10.0f, -5.161f); // Bottom-right of middle segment
        glVertex2f(10.0f, -6.0f);   // Bottom-right
        glVertex2f(-10.0f, -6.0f);  // Bottom-left
        glVertex2f(-10.0f, -5.161f);// Bottom-left of middle segment

        glEnd();
    }

    else
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_POLYGON);

        // Top color (RGB: 255, 255, 255)
        glColor3ub(255, 255, 255);
        glVertex2f(-10.0f, 5.25f);  // Top-left
        glVertex2f(10.0f, 5.25f);   // Top-right

        // Middle color (RGB: 243, 209, 194) at 66.0781%
        glColor3ub(243, 209, 194);
        glVertex2f(10.0f, 1.434f); // Bottom-right of top segment
        glVertex2f(-10.0f, 1.434f);// Bottom-left of top segment
        glEnd();

        glBegin(GL_POLYGON);

        // Middle color (RGB: 243, 209, 194) at 66.0781%
        glColor3ub(243, 209, 194);
        glVertex2f(10.0f, 1.434f); // Bottom-right of top segment
        glVertex2f(-10.0f, 1.434f);// Bottom-left of top segment

        // Third color (RGB: 121, 139, 74) at 7.4854%
        glColor3ub(121, 139, 74);
        glVertex2f(-10.0f, -5.161f);// Bottom-left of middle segment
        glVertex2f(10.0f, -5.161f); // Bottom-right of middle segment

        glEnd();

        glBegin(GL_POLYGON);

        // Third color (RGB: 121, 139, 74) at 7.4854%
        glColor3ub(121, 139, 74);
        glVertex2f(10.0f, -5.161f); // Bottom-right of middle segment
        glVertex2f(10.0f, -6.0f);   // Bottom-right
        glVertex2f(-10.0f, -6.0f);  // Bottom-left
        glVertex2f(-10.0f, -5.161f);// Bottom-left of middle segment

        glEnd();
    }
}

///42
void initSnow()
{
    srand(time(0));
    for (int i = 0; i < NUM_SNOW_DROPS; i++)
    {
        snowX[i] = -20 + (float)rand() / (RAND_MAX / 40.0); // Extend range for rotation
        snowY[i] = -15 + (float)rand() / (RAND_MAX / 30.0);
    }
}

///43
void drawSnow()
{
    if (!startSnow) return; // Skip rendering snow if startSnow is false

    glColor3f(1.0, 1.0, 1.0);

    glPushMatrix();

    glRotatef(angle, 0.0, 0.0, 1.0);

    glBegin(GL_LINES);
    for (int i = 0; i < NUM_SNOW_DROPS; i++)
    {
        glVertex2f(snowX[i], snowY[i]);
        glVertex2f(snowX[i], snowY[i] - 0.08);
    }
    glEnd();

    glPopMatrix();
}

///44
void drawCloud(float x, float y)
{
    glColor3f(0.9f, 0.9f, 0.9f); // Light gray color for clouds

    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++) {
        float theta = 2.0f * 3.1415926f * i / 100;
        float cx = 0.7f * cosf(theta);
        float cy = 0.5f * sinf(theta);
        glVertex2f(cx + x, cy + y);
    }
    glEnd();

    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++) {
        float theta = 2.0f * 3.1415926f * i / 100;
        float cx = 0.6f * cosf(theta);
        float cy = 0.4f * sinf(theta);
        glVertex2f(cx + x + 0.8f, cy + y + 0.2f);
    }
    glEnd();

    glBegin(GL_POLYGON);
    for (int i = 0; i < 100; i++) {
        float theta = 2.0f * 3.1415926f * i / 100;
        float cx = 0.5f * cosf(theta);
        float cy = 0.3f * sinf(theta);
        glVertex2f(cx + x - 0.8f, cy + y + 0.2f);
    }

    glEnd();
}

///45
void Cloud()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(_cloudMove, 0.0f, 0.0f);
    //Draw all clouds at fixed positions
    drawCloud(30.0f, 4.0f); // Cloud 1
    drawCloud(25.0f, 4.5f); // Cloud 2
    drawCloud(20.0f, 3.5f); // Cloud 3
    drawCloud(15.0f, 5.0f); // Cloud 4
    drawCloud(10.0f, 4.0f); // Cloud 5
    drawCloud(5.0f, 4.5f);  // Cloud 6
    drawCloud(0.0f, 3.5f);  // Cloud 7
    drawCloud(-5.0f, 5.0f); // Cloud 8
    drawCloud(-10.0f, 4.0f); // Cloud 9
    drawCloud(-15.0f, 4.5f); // Cloud 10

    glPopMatrix();
}

///46
void drawJeep()
{
    // Roof Light()

    glBegin(GL_POLYGON);
    glColor3ub(218, 225, 225);

    glVertex2f(-3.9098765401424,4.8989960352034);
    glVertex2f(-3.8302731981267,4.9527623098644);
    glVertex2f(-3.7247281277395,4.9959438423477);
    glVertex2f(-3.6058401445913,5.0326296380212);
    glVertex2f(-3.4835075166142,5.0542177488406);
    glVertex2f(-3.2569761242619,5.0871988553035);
    glVertex2f(-2.9576812486656,5.1202379000122);
    glVertex2f(-2.6389516408877,5.141616105412);
    glVertex2f(-2.310504667019,5.1474465250664);
    glVertex2f(-1.0525114379193,5.1339213472132);
    glVertex2f(-0.3544201306257,5.0959064740437);
    glVertex2f(0.0464639864339,5.0717151911177);
    glVertex2f(0.5060983620282,5.0233326252657);
    glVertex2f(0.7391774566162,4.9730454075559);
    glVertex2f(0.8341620539557,4.9450023359605);
    glVertex2f(0.9101497318273,4.9133408035139);
    glVertex2f(0.9312938446433, 4.8992447283033);

    glEnd();


    // Roof Dark()

    glBegin(GL_POLYGON);
    glColor3ub(199, 205, 205);

    glVertex2f(-4.0012674655658,4.7486395544843);
    glVertex2f(-3.9852104166234,4.8084041891508);
    glVertex2f(-3.9554783993316,4.8537796635387);
    glVertex2f(-3.9098765401424,4.8989960352034);
    glVertex2f(0.9312938446433, 4.8992447283033);
    glVertex2f(0.9671404902311,4.8753469645781);
    glVertex2f(0.98975587055,4.8364485104296);
    glVertex2f(0.9924697161883,4.8111192844724);
    glVertex2f(0.9834235640607,4.7830762128769);
    glVertex2f(0.9490481859759,4.7604608325579);
    glVertex2f(0.9201004991677,4.7487008347921);

    glEnd();


    // Body Back

    glBegin(GL_POLYGON);
    glColor3ub(170, 137, 121);

    glVertex2f(-4.0012674655658,4.7486395544843);
    glVertex2f(-4.0126309993138,4.5818752318891);
    glVertex2f(-3.7583203496456,4.5818752318891);
    glVertex2f(-3.7256020204485,4.577413641544);
    glVertex2f(-3.7003196751598,4.5670032640722);
    glVertex2f(-3.6794989202162,4.5506440994737);
    glVertex2f(-3.6631397556177,4.5313105413118);
    glVertex2f(-3.6542165749276,4.5045409992414);
    glVertex2f(-3.6559069891117,3.7823733102624);
    glVertex2f(-3.6696848571911,3.7385346391006);
    glVertex2f(-3.685967792194,3.6946959679389);
    glVertex2f(-3.7035032606587,3.6734028990889);
    glVertex2f(-3.7140358445062,3.6610772542869);
    glVertex2f(-3.7319585138013,3.6506705430833);
    glVertex2f(-3.7602878943001,3.6367949281451);
    glVertex2f(-3.7805231660849,3.6223411625845);
    glVertex2f(-3.8192592577873,3.6119344513809);
    glVertex2f(-3.843541583929,3.6061529451567);
    glVertex2f(-4.1329931082347,3.6081681673801);
    glVertex2f(-4.140434558785,3.5719812151491);
    glVertex2f(-4.141433921121,3.5392728455281);
    glVertex2f(-4.1313626254531,2.2503074731983);
    glVertex2f(-4.119959083119,1.9964422269412);
    glVertex2f(-3.8,2);
    glVertex2f(-3.7674338970482,2.0005040298647);
    glVertex2f(-3.7544259705246,1.8116428738276);
    glVertex2f(-3.7525562823138,1.7897193878184);
    glVertex2f(-3.6011758584832,1.7897193878184);
    glVertex2f(-3.5577865650286,1.8003256595518);
    glVertex2f(-3.5240393367861,1.8302160617094);
    glVertex2f(-3.4931847281072,1.8678201160367);
    glVertex2f(-3.4700437715981,1.9073525834065);
    glVertex2f(-3.4391891629192,1.9613481485945);
    glVertex2f(-3.4121913803252,2.0124510942189);
    glVertex2f(-3.3716947064342,2.0866949963523);
    glVertex2f(-3.3176991412462,2.1811872354313);
    glVertex2f(-3.2675604021431,2.2419322462678);
    glVertex2f(-3.1325714891731,2.3431739309953);
    glVertex2f(-3.0583275870397,2.3663148875044);
    glVertex2f(-3.0004751957668,2.3740285396741);
    glVertex2f(-1.8895601392292,2.3738480994569);
    glVertex2f(-1.8224374387591,2.3593881815853);
    glVertex2f(-1.7633190293655,2.3375400737659);
    glVertex2f(-1.7196228137268,2.3105512346949);
    glVertex2f(-1.6784969637139,2.2707105674949);
    glVertex2f(-1.6193785543203,2.2115921581014);
    glVertex2f(-1.583393435559,2.162755211211);
    glVertex2f(-1.5615453277397,2.1126330815078);
    glVertex2f(-1.53070094023,2.0406628439852);
    glVertex2f(-1.3422412867226,1.6022027333414);
    glVertex2f(-1.3203472450379,1.5468423105819);
    glVertex2f(-1.2976761442813,1.5083014392957);
    glVertex2f(-1.259135272995,1.4833632284635);
    glVertex2f(-1.2264818347485,1.4623923486701);
    glVertex2f(-1.1686156181975,1.4405317779731);
    glVertex2f(-1.1236085608801,1.4353881142797);
    glVertex2f(-1.0374521940153,1.4353881142797);
    glVertex2f(-0.973614223923,4.7408538287874);

    glEnd();


    // Body Font

    glBegin(GL_POLYGON);
    glColor3ub(170, 137, 121);

    glVertex2f(-1.0374521940153,1.4353881142797);
    glVertex2f(1.4921411546419,1.4362378589756);
    glVertex2f(1.5356288644928,1.4054340644979);
    glVertex2f(1.7,1.4);
    glVertex2f(2.5412320800353,2.3710251286589);
    glVertex2f(2.581903661505,2.4108084788548);
    glVertex2f(2.6375616694584,2.4415668516711);
    glVertex2f(2.6785728332136,2.4518196426099);
    glVertex2f(2.7151899437093,2.4620724335487);
    glVertex2f(3.7565633512323,2.4606252847114);
    glVertex2f(3.8156080412971,2.4456694893184);
    glVertex2f(3.8647763097831,2.4184513406922);
    glVertex2f(3.9139445782691,2.3877211728885);
    glVertex2f(4.1789362159723,2.2457578824813);
    glVertex2f(4.3240765668747,2.2303174196193);
    glVertex2f(4.3240765668747,2.2843590396362);
    glVertex2f(4.2329778359892,2.3600173076597);
    glVertex2f(4.2329778359892,2.5113338437069);
    glVertex2f(4.1559225489799,2.5269548241465);
    glVertex2f(4.1409183971582,2.5937915004431);
    glVertex2f(4.1450104385641,2.7738413223034);
    glVertex2f(4.1600145903858,2.8174897639664);
    glVertex2f(4.2173031700686,2.8174897639664);
    glVertex2f(4.2173031700686,2.983899447807);
    glVertex2f(4.198206976841,3.0370959860839);
    glVertex2f(4.1600145903858,3.0752883725391);
    glVertex2f(4.0263412377926,3.1175728004002);
    glVertex2f(3.2583117632018,3.2638325703954);
    glVertex2f(2.7060679902997,3.3413948980502);
    glVertex2f(2.2934364071762,3.3941372808554);
    glVertex2f(1.4036942228772,3.4304528527027);
    glVertex2f(1.3716325211041,3.6257377635026);
    glVertex2f(1.3308267188474,3.6752876662429);
    glVertex2f(1.2696180154623,3.6956905673712);
    glVertex2f(1.2084093120773,3.707349368016);
    glVertex2f(1.1736698213836,3.7016773938679);
    glVertex2f(0.9196926411941,4.6905088292815);
    glVertex2f(0.9201004991677,4.7487008347921);
    glVertex2f(-0.973614223923,4.7408538287874);

    glEnd();


     // Lower Body

    glBegin(GL_POLYGON);
    glColor3ub(154, 126, 113);
    glVertex2f(-4.1340966991975, 2.6002253485286);
    glVertex2f(-4.1313626254531,2.2503074731983);
    glVertex2f(-4.119959083119,1.9964422269412);
    glVertex2f(-3.8,2);
    glVertex2f(-3.7674338970482,2.0005040298647);
    glVertex2f(-3.7544259705246,1.8116428738276);
    glVertex2f(-3.7525562823138,1.7897193878184);
    glVertex2f(-3.6011758584832,1.7897193878184);
    glVertex2f(-3.5577865650286,1.8003256595518);
    glVertex2f(-3.5240393367861,1.8302160617094);
    glVertex2f(-3.4931847281072,1.8678201160367);
    glVertex2f(-3.4700437715981,1.9073525834065);
    glVertex2f(-3.4391891629192,1.9613481485945);
    glVertex2f(-3.4121913803252,2.0124510942189);
    glVertex2f(-3.3716947064342,2.0866949963523);
    glVertex2f(-3.3176991412462,2.1811872354313);
    glVertex2f(-3.2675604021431,2.2419322462678);
    glVertex2f(-3.1325714891731,2.3431739309953);
    glVertex2f(-3.0583275870397,2.3663148875044);
    glVertex2f(-3.0004751957668,2.3740285396741);
    glVertex2f(-1.8895601392292,2.3738480994569);
    glVertex2f(-1.8224374387591,2.3593881815853);
    glVertex2f(-1.7633190293655,2.3375400737659);
    glVertex2f(-1.7196228137268,2.3105512346949);
    glVertex2f(-1.6784969637139,2.2707105674949);
    glVertex2f(-1.6193785543203,2.2115921581014);
    glVertex2f(-1.583393435559,2.162755211211);
    glVertex2f(-1.5615453277397,2.1126330815078);
    glVertex2f(-1.53070094023,2.0406628439852);
    glVertex2f(-1.3422412867226,1.6022027333414);
    glVertex2f(-1.3203472450379,1.5468423105819);
    glVertex2f(-1.2976761442813,1.5083014392957);
    glVertex2f(-1.259135272995,1.4833632284635);
    glVertex2f(-1.2264818347485,1.4623923486701);
    glVertex2f(-1.1686156181975,1.4405317779731);
    glVertex2f(-1.1236085608801,1.4353881142797);
    glVertex2f(-1.0374521940153,1.4353881142797);
    glVertex2f(1.4921411546419,1.4362378589756);
    glVertex2f(1.4686353291173,1.4627397616432);
    glVertex2f(1.4596886057633,1.4836154494692);
    glVertex2f(1.4716175702353,1.5044911372952);
    glVertex2f(1.5014399814153,1.5303372269845);
    glVertex2f(2.349333612245,2.4732242587255);
    glVertex2f(2.404316066257,2.5249372327213);
    glVertex2f(2.443705831729,2.5581997013421);
    glVertex2f(2.4839709253225,2.588836185598);
    glVertex2f(2.5036977362679,2.59905635751);
    glVertex2f(2.47554708892,2.6002256124841);

    glEnd();


    // Font Shade

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(219, 225, 224);

    glVertex2f(3.85745058781,2.9946137105104);
    glVertex2f(3.85745058781,2.5599734564342);

    glEnd();


    // Back Tier Black

    glBegin(GL_POLYGON);
    glColor3ub(22, 32, 38);

    glVertex2f(-3.7525562823138,1.7897193878184);
    glVertex2f(-3.6011758584832,1.7897193878184);
    glVertex2f(-3.5577865650286,1.8003256595518);
    glVertex2f(-3.5240393367861,1.8302160617094);
    glVertex2f(-3.4931847281072,1.8678201160367);
    glVertex2f(-3.4700437715981,1.9073525834065);
    glVertex2f(-3.4391891629192,1.9613481485945);
    glVertex2f(-3.4121913803252,2.0124510942189);
    glVertex2f(-3.3716947064342,2.0866949963523);
    glVertex2f(-3.3176991412462,2.1811872354313);
    glVertex2f(-3.2675604021431,2.2419322462678);
    glVertex2f(-3.1325714891731,2.3431739309953);
    glVertex2f(-3.0583275870397,2.3663148875044);
    glVertex2f(-3.0004751957668,2.3740285396741);
    glVertex2f(-1.8895601392292,2.3738480994569);
    glVertex2f(-1.8224374387591,2.3593881815853);
    glVertex2f(-1.7633190293655,2.3375400737659);
    glVertex2f(-1.7196228137268,2.3105512346949);
    glVertex2f(-1.6784969637139,2.2707105674949);
    glVertex2f(-1.6193785543203,2.2115921581014);
    glVertex2f(-1.583393435559,2.162755211211);
    glVertex2f(-1.5615453277397,2.1126330815078);
    glVertex2f(-1.53070094023,2.0406628439852);
    glVertex2f(-1.3422412867226,1.6022027333414);
    glVertex2f(-1.3203472450379,1.5468423105819);
    glVertex2f(-1.2976761442813,1.5083014392957);
    glVertex2f(-1.259135272995,1.4833632284635);
    glVertex2f(-1.2264818347485,1.4623923486701);
    glVertex2f(-1.1686156181975,1.4405317779731);
    glVertex2f(-1.1236085608801,1.4353881142797);
    glVertex2f(-1.0374521940153,1.4353881142797);
    glVertex2f(-1.0374521940153,1.3486339292395);
    glVertex2f(-1.2600218361853,1.3486339292395);
    glVertex2f(-1.44565781753,1.2862076700262);
    glVertex2f(-3.4470457236068,1.5259131028978);
    glVertex2f(-3.7565163731545,1.6739411428032);

    glEnd();


    // Back Window

    glBegin(GL_POLYGON);
    glColor3ub(49, 41, 53);

    glVertex2f(-4.0310487214867,4.5815170228076);
    glVertex2f(-4.0126309993138,4.5818752318891);
    glVertex2f(-3.7583203496456,4.5818752318891);
    glVertex2f(-3.7256020204485,4.577413641544);
    glVertex2f(-3.7003196751598,4.5670032640722);
    glVertex2f(-3.6794989202162,4.5506440994737);
    glVertex2f(-3.6631397556177,4.5313105413118);
    glVertex2f(-3.6542165749276,4.5045409992414);
    glVertex2f(-3.6559069891117,3.7823733102624);
    glVertex2f(-3.6696848571911,3.7385346391006);
    glVertex2f(-3.685967792194,3.6946959679389);
    glVertex2f(-3.7035032606587,3.6734028990889);
    glVertex2f(-3.7140358445062,3.6610772542869);
    glVertex2f(-3.7319585138013,3.6506705430833);
    glVertex2f(-3.7602878943001,3.6367949281451);
    glVertex2f(-3.7805231660849,3.6223411625845);
    glVertex2f(-3.8192592577873,3.6119344513809);
    glVertex2f(-3.843541583929,3.6061529451567);
    glVertex2f(-4.1329931082347,3.6081681673801);

    glEnd();


    // Middle Window

    glBegin(GL_POLYGON);
    glColor3ub(49, 41, 53);

    glVertex2f(-3.4416029724794,4.4342944227023);
    glVertex2f(-3.4362786117958,4.5017363246944);
    glVertex2f(-3.415039364583,4.5317203335034);
    glVertex2f(-3.4,4.55);
    glVertex2f(-3.3722041146497,4.563023016147);
    glVertex2f(-3.346667715651,4.5745878692565);
    glVertex2f(-1.3519930846551,4.5745878692565);
    glVertex2f(-1.3187590403892,4.5579708471235);
    glVertex2f(-1.2855249961233,4.5413538249906);
    glVertex2f(-1.2522909518573,4.5081197807247);
    glVertex2f(-1.2285523488103,4.4677641555446);
    glVertex2f(-1.2285523488103,4.4084176479269);
    glVertex2f(-1.2261784885055,3.7508583435228);
    glVertex2f(-1.2356002651146,3.6949308453208);
    glVertex2f(-1.2575859908979,3.6625988956395);
    glVertex2f(-1.2847448286302,3.6367333358945);
    glVertex2f(-1.3176572939637,3.6212306941156);
    glVertex2f(-1.369041127115,3.6120550096243);
    glVertex2f(-3.3833807291237,3.6209253724742);
    glVertex2f(-3.3999266326494,3.6382985711762);
    glVertex2f(-3.4123360602937,3.6523625891731);
    glVertex2f(-3.4321911445245,3.6730449685802);
    glVertex2f(-3.4520462287554,3.710273251513);

    glEnd();


    // Front Window

    glBegin(GL_POLYGON);
    glColor3ub(49, 41, 53);

    glVertex2f(-0.8103474327124,3.6600546821714);
    glVertex2f(-0.8103474327124,4.5187754018864);
    glVertex2f(-0.8043686398176,4.5434645570986);
    glVertex2f(-0.7911031434025,4.5578129511803);
    glVertex2f(-0.7561796936565,4.5851561172605);
    glVertex2f(-0.7437263704913,4.5878633614268);
    glVertex2f(-0.7209855194939,4.5878633614268);
    glVertex2f(0.6625277762807,4.5878633614268);
    glVertex2f(0.7003071874699,4.5720162273079);
    glVertex2f(0.7159500027563,4.5569422416682);
    glVertex2f(0.7322037754588,4.540829449749);
    glVertex2f(0.7470660274417,4.5229947473696);
    glVertex2f(0.7619282794245,4.4962426938005);
    glVertex2f(0.777593575419,4.4495547683252);
    glVertex2f(0.9865182564192,3.7171029677801);
    glVertex2f(0.9910430428792,3.6699159089823);
    glVertex2f(0.977468683499,3.6363032095648);
    glVertex2f(0.9596565741729,3.6069882533593);
    glVertex2f(0.9327040126754,3.5943467864623);
    glVertex2f(0.8915601456624,3.5903974333607);
    glVertex2f(-0.734534151057,3.5903974333607);
    glVertex2f(-0.7605573004761,3.5979195085945);
    glVertex2f(-0.7855395403018,3.6166561884637);
    glVertex2f(-0.8001125135334,3.6416384282894);

    glEnd();



    // Font Tier Upper

    glBegin(GL_POLYGON);
    glColor3ub(191, 153, 141);

    glVertex2f(1.4921411546419,1.4362378589756);
    glVertex2f(1.5356288644928,1.4054340644979);
    glVertex2f(1.7,1.4);
    glVertex2f(2.5412320800353,2.3710251286589);
    glVertex2f(2.581903661505,2.4108084788548);
    glVertex2f(2.6375616694584,2.4415668516711);
    glVertex2f(2.6785728332136,2.4518196426099);
    glVertex2f(2.7151899437093,2.4620724335487);
    glVertex2f(3.7565633512323,2.4606252847114);
    glVertex2f(3.8156080412971,2.4456694893184);
    glVertex2f(3.8647763097831,2.4184513406922);
    glVertex2f(3.9139445782691,2.3877211728885);
    glVertex2f(4.1789362159723,2.2457578824813);
    glVertex2f(4.3240765668747,2.2303174196193);
    glVertex2f(4.3240765668747,2.2843590396362);
    glVertex2f(4.2329778359892,2.3600173076597);
    glVertex2f(3.9201915041838,2.5953006456288);
    glVertex2f(3.7399771142796,2.6566569980447);
    glVertex2f(2.5867248696902,2.6566569980447);
    glVertex2f(2.5036977362679,2.59905635751);
    glVertex2f(2.4839709253225,2.588836185598);
    glVertex2f(2.443705831729,2.5581997013421);
    glVertex2f(2.404316066257,2.5249372327213);
    glVertex2f(2.349333612245,2.4732242587255);
    glVertex2f(1.5014399814153,1.5303372269845);
    glVertex2f(1.4716175702353,1.5044911372952);
    glVertex2f(1.4596886057633,1.4836154494692);
    glVertex2f(1.4686353291173,1.4627397616432);

    glEnd();

    // Font Tier Black

    glBegin(GL_POLYGON);
    glColor3ub(22, 32, 38);

    glVertex2f(1.7,1.4);
    glVertex2f(1.6747039903682,1.4070956211365);
    glVertex2f(2.581903661505,2.4108084788548);
    glVertex2f(2.6375616694584,2.4415668516711);
    glVertex2f(2.6785728332136,2.4518196426099);
    glVertex2f(2.7151899437093,2.4620724335487);
    glVertex2f(3.7565633512323,2.4606252847114);
    glVertex2f(3.8156080412971,2.4456694893184);
    glVertex2f(3.8647763097831,2.4184513406922);
    glVertex2f(3.9139445782691,2.3877211728885);
    glVertex2f(4.1789362159723,2.2457578824813);
    glVertex2f(4.1813559353244,1.9062134186889);
    glVertex2f(4.3001625877246,1.9062134186889);
    glVertex2f(4.359020369312,1.9664924230775);
    glVertex2f(4.5937912285097,1.9664924230775);
    glVertex2f(4.5937912285097,1.8840379866705);
    glVertex2f(4.7026153259266,1.8840379866705);
    glVertex2f(4.7026153259266,1.5340724525357);
    glVertex2f(4.2384924772423,1.5340724525357);
    glVertex2f(2.2,1.2);
    glVertex2f(1.6969359128361,1.350590473163);
    glEnd();


    // Door

    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glColor3ub(133, 105, 93);


    glVertex2f(-0.973614223923,4.7408538287874);
    glVertex2f(-0.9996302491449,4.2855733874035);
    glVertex2f(-1.0191422680614,3.6286687505496);
    glVertex2f(-1.0256462743668,2.3083554705364);
    glVertex2f(-1.0191422680614,2.0742112435389);
    glVertex2f(-1,2);
    glVertex2f(-0.9811853481827,1.9468697597213);
    glVertex2f(-0.9446308806373,1.8981304696608);
    glVertex2f(-0.901113657369,1.8685387578383);
    glVertex2f(-0.8645591898236,1.8424284238773);
    glVertex2f(-0.8210419665553,1.8197994677778);
    glVertex2f(-0.7618585429104,1.8128367120548);
    glVertex2f(-0.6748240963737,1.8128367120548);
    glVertex2f(0.8000558636301,1.8128367120548);
    glVertex2f(0.8746129086613,1.8180709349425);
    glVertex2f(0.9361652198818,1.8360947139672);
    glVertex2f(0.978097567906,1.8646087106237);
    glVertex2f(1.030093679456,1.9115729404108);
    glVertex2f(1.0703487335593,1.9652463458818);
    glVertex2f(1.1055719058996,2.0289835148786);
    glVertex2f(1.1290540207932,2.0994298595593);
    glVertex2f(1.135763196477,2.1631670285561);
    glVertex2f(1.1361101422474,3.4709846622704);
    glVertex2f(0.8136903955771,4.7449424243872);

    glEnd();


    // Front

    glBegin(GL_POLYGON);
    glColor3ub(193, 154, 140);

    glVertex2f(1.6012077091882, 3.4223911744666);
    glVertex2f(1.6012077091882,2.8812514637178);
    glVertex2f(4.2173031700686, 2.8812514637178);
    glVertex2f(4.2173031700686,2.983899447807);
    glVertex2f(4.198206976841,3.0370959860839);
    glVertex2f(4.1600145903858,3.0752883725391);
    glVertex2f(4.0263412377926,3.1175728004002);
    glVertex2f(3.2583117632018,3.2638325703954);
    glVertex2f(2.7060679902997,3.3413948980502);
    glVertex2f(2.2934364071762,3.3941372808554);

    glEnd();


    // Font Shade Vartical
    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(133, 105, 93);

    glVertex2f(1.6012077091882, 3.4223911744666);
    glVertex2f(1.6012077091882,2.8812514637178);

    glEnd();


    // Font Shade Horizontal
    glLineWidth(2);
    glBegin(GL_LINES);

    glVertex2f(1.6012077091882,2.8812514637178);
    glVertex2f(4.2173031700686, 2.8812514637178);

    glEnd();


    // Mirror Base

    glBegin(GL_POLYGON);
    glColor3ub(23, 32, 29);
    glVertex2f(0.8189169112423,3.5583740872128);
    glVertex2f(0.8020683022706,3.5210664530613);
    glVertex2f(0.7936439977848,3.4837588189098);
    glVertex2f(0.785219693299,3.4368234082031);
    glVertex2f(0.7816092770908,3.3742428605941);
    glVertex2f(0.785219693299,3.3405456426508);
    glVertex2f(0.8141030229646,3.3236970336792);
    glVertex2f(0.8646488498796,3.3188831454015);
    glVertex2f(0.9151946767945,3.3188831454015);
    glVertex2f(0.9657405037094,3.3224935616098);
    glVertex2f(1.0042516099303,3.3273074498874);
    glVertex2f(1.0215885531823,3.332316999679);
    glVertex2f(1.0247321889654,3.3619569942053);
    glVertex2f(1.0247321889654,3.4059678951687);
    glVertex2f(1.0247321889654,3.435607889695);
    glVertex2f(1.0229358256608,3.4971333328784);
    glVertex2f(1.012157645833,3.5317133264925);
    glVertex2f(0.9932958311344,3.5537187769742);
    glVertex2f(0.977577652219,3.5631496843234);
    glVertex2f(0.960512200825,3.5644969568019);
    glVertex2f(0.8940467585539,3.5631496843234);
    glVertex2f(0.8549758566782,3.5631496843234);

    glEnd();


    // Mirror Stand

    glBegin(GL_POLYGON);
    glColor3ub(54, 66, 74);

    glVertex2f(1.0195055230019,3.6890885839159);
    glVertex2f(1.0195055230019,3.663630084012);
    glVertex2f(1.011504280175,3.6308977269927);
    glVertex2f(1,3.6);
    glVertex2f(0.9904689514395,3.5773221234436);
    glVertex2f(0.9722905510857,3.5526514372491);
    glVertex2f(0.9426439071423,3.5260740457521);
    glVertex2f(0.9215289294831,3.5072213871277);
    glVertex2f(0.913033786586,3.493918387644);
    glVertex2f(0.9156820580155,3.3879875304674);
    glVertex2f(0.9176682615875,3.3548841375998);
    glVertex2f(0.9322337544493,3.3389945090233);
    glVertex2f(0.9527578580272,3.3297255590204);
    glVertex2f(0.9795619187658,3.3296356231356);
    glVertex2f(0.9895643424217,3.3341528467222);
    glVertex2f(1,3.34);
    glVertex2f(1.0076332367679,3.352544399896);
    glVertex2f(1.0134410956649,3.3748078590011);
    glVertex2f(1.0179583192515,3.4099776712107);
    glVertex2f(1.0179583192515,3.4325637891435);
    glVertex2f(1.0162892256999,3.4589260986647);
    glVertex2f(1.0341454221029,3.4869008063628);
    glVertex2f(1.0485656147226,3.5231693019507);
    glVertex2f(1.05,3.55);
    glVertex2f(1.0524369482111,3.5863322228571);
    glVertex2f(1.0586060775881,3.6345424012136);
    glVertex2f(1.0669935879451,3.6764799529987);
    glVertex2f(1.0709876404961,3.6948525947331);
    glVertex2f(1.0234204664711,3.6962744351941);

    glEnd();


    // Mirror

    glBegin(GL_POLYGON);
    glColor3ub(24, 33, 29);

    glVertex2f(0.9482805892675,4.2760350741802);
    glVertex2f(0.9830033565338,4.2760350741802);
    glVertex2f(1.0085885534669,4.2696387749469);
    glVertex2f(1.0442250777665,4.2568461764804);
    glVertex2f(1.0762065739329,4.2413123069139);
    glVertex2f(1.0953954716327,4.2221234092141);
    glVertex2f(1.1109293411992,4.1956244552477);
    glVertex2f(1.1109293411992,4.0137868056161);
    glVertex2f(1.1237219396657,3.9982529360496);
    glVertex2f(1.127376967799,3.9726677391165);
    glVertex2f(1.127376967799,3.9306349155836);
    glVertex2f(1.127376967799,3.7487972659521);
    glVertex2f(1.1054467989993,3.723212069019);
    glVertex2f(1.0910923977905,3.7070174125225);
    glVertex2f(1.0577779581194,3.6910690105523);
    glVertex2f(1.0319061060343,3.6900057837542);
    glVertex2f(0.9943387591711,3.6970939624077);
    glVertex2f(0.9698845428168,3.7094982750512);
    glVertex2f(0.9585434569713,3.7367877628669);
    glVertex2f(0.9521640961832,3.7740007007975);
    glVertex2f(0.9486200068565,3.8151121369874);
    glVertex2f(0.9560625944426,3.8622485250327);
    glVertex2f(0.9695301338841,3.878196927003);

    glEnd();


    // Lower Black

    glBegin(GL_POLYGON);
    glColor3ub(22, 32, 38);

    glVertex2f(-1.259135272995,1.3486339292395);
    glVertex2f(-1.2264818347485,1.4623923486701);
    glVertex2f(-1.1686156181975,1.4405317779731);
    glVertex2f(-1.1236085608801,1.4353881142797);
    glVertex2f(-1.0374521940153,1.4353881142797);
    glVertex2f(1.4921411546419,1.4362378589756);
    glVertex2f(1.5356288644928,1.4054340644979);
    glVertex2f(1.7,1.4);
    glVertex2f(1.6969359128361,1.350590473163);
    glVertex2f(-1.2600218361853,1.3486339292395);

    glEnd();


    // Roof Shade

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(133, 105, 93);

    glVertex2f(-4.0012674655658,4.7486395544843);
    glVertex2f(0.9201004991677,4.7487008347921);

    glEnd();


    // Body Shade

    glLineWidth(4);
    glBegin(GL_LINES);
    glColor3ub(133, 105, 93);

    glVertex2f(-3.9803922670205,3.0937123361265);
    glVertex2f(-1.2247537784513,3.0937123361265);

    glEnd();


    // Door Handle

    glLineWidth(5);
    glBegin(GL_LINES);
    glColor3ub(27, 32, 41);

    glVertex2f(-0.8421802257123,3.1713359555228);
    glVertex2f(-0.492478123812,3.1713359555228);

    glEnd();



    // Door Handle Shade

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(133, 105, 93);

    glVertex2f(-0.828278469414,3.0727618118133);
    glVertex2f(-0.4674798414733,3.0727618118133);

    glEnd();


    // Red Light

    glBegin(GL_POLYGON);
    glColor3ub(161, 27, 31);

    glVertex2f(-3.8855771073267,2.7385423198006);
    glVertex2f(-3.5532146613804,2.7385423198006);
    glVertex2f(-3.5532146613804,2.6213047188346);
    glVertex2f(-3.8855771073267,2.6213047188346);

    glEnd();


    // Door Shade

    glLineWidth(4);
    glBegin(GL_LINES);
    glColor3ub(190, 155, 138);

    glVertex2f(-0.8200020487419,2.827574212482);
    glVertex2f(0.9265293876752,2.827574212482);

    glEnd();

    // Door Shade Shadow

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(133, 105, 93);

    glVertex2f(-0.8179481431839,2.7306657326542);
    glVertex2f(0.893254777931,2.7306657326542);

    glEnd();


    // Back White

    glBegin(GL_POLYGON);
    glColor3ub(129, 131, 135);

    glVertex2f(-4.3273181609319,1.9964422269412);
    glVertex2f(-4.119959083119,1.9964422269412);
    glVertex2f(-3.8,2);
    glVertex2f(-3.7674338970482,2.0005040298647);
    glVertex2f(-3.7544259705246,1.8116428738276);
    glVertex2f(-3.7525562823138,1.7897193878184);
    glVertex2f(-3.7565163731545,1.6739411428032);
    glVertex2f(-4.104901130889,1.4621099927667);
    glVertex2f(-4.3273181609319,1.4621099927667);

    glEnd();


    // Silencer

    glBegin(GL_POLYGON);
    glColor3ub(14, 25, 31);

    glVertex2f(-3.9477766943229,1.4792566839057);
    glVertex2f(-3.3985141074677,1.4792566839057);
    glVertex2f(-3.3985141074677,1.3613764113864);
    glVertex2f(-3.8863465240928,1.3613764113864);

    glEnd();


    // Front White

    glBegin(GL_POLYGON);
    glColor3ub(129, 131, 135);

    glVertex2f(4.6969709346452,1.9841937511097);
    glVertex2f(4.9459287619219,1.9841937511097);
    glVertex2f(4.9459287619219,1.4517616197777);
    glVertex2f(4.7001748798852,1.4517616197777);

    glEnd();


    // Front Shadow Vertical

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(146, 96, 95);

    glVertex2f(1.1860255016533,3.674224244733);
    glVertex2f(1.2457611612516,3.4237198657723);

    glEnd();


    // Front Shadow Horizontal

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(146, 96, 95);

    glVertex2f(1.2457611612516,3.4237198657723);
    glVertex2f(1.3671594372095,3.4256468225335);

    glEnd();


    // Head Light

    glBegin(GL_POLYGON);
    glColor3ub(244, 128, 34);

    glVertex2f(4.2329778359892,2.5113338437069);
    glVertex2f(4.1559225489799,2.5269548241465);
    glVertex2f(4.1409183971582,2.5937915004431);
    glVertex2f(4.1450104385641,2.7738413223034);
    glVertex2f(4.1600145903858,2.8174897639664);
    glVertex2f(4.2173031700686,2.8174897639664);
    glVertex2f(4.3047485106961,2.8187299368004);
    glVertex2f(4.3235133454158,2.8023863710768);
    glVertex2f(4.3277505661589,2.7727258258747);
    glVertex2f(4.330171835155,2.5481531264873);
    glVertex2f(4.3174601729256,2.5203085330322);
    glVertex2f(4.2835624069803,2.5160713122891);

    glEnd();


    // Back Tier

    glBegin(GL_POLYGON);
    glColor3ub(41, 33, 44);

    glVertex2f(-4.9364446969539,3.9470271927175);
    glVertex2f(-4.9364329017456,2.2034953458598);
    glVertex2f(-4.9089489211671,2.1473822188455);
    glVertex2f(-4.892916599163,2.1302047309839);
    glVertex2f(-4.8516906282953,2.1187530724096);
    glVertex2f(-4.3398014900215,2.1221885699819);
    glVertex2f(-4.2917045240092,2.1267692334116);
    glVertex2f(-4.2699368052727,2.1419355054387);
    glVertex2f(-4.2550722324071,2.1617549359263);
    glVertex2f(-4.2402076595414,2.1865292240356);
    glVertex2f(-4.2281744338883,2.2063486545232);
    glVertex2f(-4.2232195762664,2.2360778002544);
    glVertex2f(-4.2225117394633,2.2580207411513);
    glVertex2f(-4.131444870973, 2.2608335892678);
    glVertex2f(-4.1366227596507,3.8040613537092);
    glVertex2f(-4.2,3.8);
    glVertex2f(-4.2219942037772,3.8422538418711);
    glVertex2f(-4.2454981099894,3.9163158423731);
    glVertex2f(-4.2408125943995,3.9819130606324);
    glVertex2f(-4.2564309796993,4.0037788000522);
    glVertex2f(-4.282982234709,4.0147116697621);
    glVertex2f(-4.3048479741288,4.0365774091818);
    glVertex2f(-4.9014702925826,4.020959023882);
    glVertex2f(-4.9189630753245,4.0092971687208);
    glVertex2f(-4.9247940029051,3.994303354942);
    glVertex2f(-4.9339568891032,3.9743116032371);

    glEnd();

    // Back Tier Vartical

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(64, 64, 65);

    glVertex2f(-4.6,2.2);
    glVertex2f(-4.6,4.0);

    glEnd();


    // Back Tier Horizontal 1

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(64, 64, 65);

    glVertex2f(-4.9,3.9);
    glVertex2f(-4.7,3.9);

    glEnd();


    // Back Tier Horizontal 2

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(64, 64, 65);

    glVertex2f(-4.9,3.7);
    glVertex2f(-4.7,3.7);

    glEnd();


    // Back Tier Horizontal 3

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(64, 64, 65);

    glVertex2f(-4.9,3.5);
    glVertex2f(-4.7,3.5);

    glEnd();

    // Back Tier Horizontal 4

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(64, 64, 65);

    glVertex2f(-4.9,3.3);
    glVertex2f(-4.7,3.3);

    glEnd();


    // Back Tier Horizontal 5

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(64, 64, 65);

    glVertex2f(-4.9,3.1);
    glVertex2f(-4.7,3.1);

    glEnd();


    // Back Tier Horizontal 6

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(64, 64, 65);

    glVertex2f(-4.9,2.9);
    glVertex2f(-4.7,2.9);

    glEnd();


    // Back Tier Horizontal 7

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(64, 64, 65);

    glVertex2f(-4.9,2.7);
    glVertex2f(-4.7,2.7);

    glEnd();

    // Back Tier Horizontal 8

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(64, 64, 65);

    glVertex2f(-4.9,2.5);
    glVertex2f(-4.7,2.5);

    glEnd();


    // Back Tier Horizontal 9

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(64, 64, 65);

    glVertex2f(-4.9,2.3);
    glVertex2f(-4.7,2.3);

    glEnd();


    // Back Tier Horizontal 10

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(64, 64, 65);

    glVertex2f(-4.5,3.9);
    glVertex2f(-4.24,3.9);

    glEnd();


    // Back Tier Horizontal 11

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(64, 64, 65);

    glVertex2f(-4.5,3.7);
    glVertex2f(-4.24,3.7);

    glEnd();


    // Back Tier Horizontal 12

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(64, 64, 65);

    glVertex2f(-4.5,3.5);
    glVertex2f(-4.24,3.5);

    glEnd();

    // Back Tier Horizontal 13

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(64, 64, 65);

    glVertex2f(-4.5,3.3);
    glVertex2f(-4.24,3.3);

    glEnd();


    // Back Tier Horizontal 14

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(64, 64, 65);

    glVertex2f(-4.5,3.1);
    glVertex2f(-4.24,3.1);

    glEnd();


    // Back Tier Horizontal 16

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(64, 64, 65);

    glVertex2f(-4.5,2.9);
    glVertex2f(-4.24,2.9);

    glEnd();


    // Back Tier Horizontal 17

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(64, 64, 65);

    glVertex2f(-4.5,2.7);
    glVertex2f(-4.24,2.7);

    glEnd();

    // Back Tier Horizontal 18

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(64, 64, 65);

    glVertex2f(-4.5,2.5);
    glVertex2f(-4.24,2.5);

    glEnd();


    // Back Tier Horizontal 19

    glLineWidth(2);
    glBegin(GL_LINES);
    glColor3ub(64, 64, 65);

    glVertex2f(-4.5,2.3);
    glVertex2f(-4.24,2.3);

    glEnd();
}

///47
void drawTier1(float radius, float xc, float yc, float r, float g, float b)
{

    glBegin(GL_POLYGON);
    glColor3ub(r, g, b); // Normalize RGB values

    for (int i = 0; i < 360; i++)
    {
        float pi = 3.1416f;
        float angle = (i * 2 * pi) / 360; // Divide circle into 100 segments
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(x + xc, y + yc); // Translate the circle
    }

    glEnd();
}

///48
void Tier1_Line1(float radius, float xc, float yc, float r, float g, float b)
{

    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glColor3ub(r, g, b); // Normalize RGB values

    for (int i = 0; i < 360; i++)
    {
        float pi = 3.1416f;
        float angle = (i * 2 * pi) / 360; // Divide circle into 100 segments
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(x + xc, y + yc); // Translate the circle
    }

    glEnd();
}

///49
void Tier1_Line2(float radius, float xc, float yc, float r, float g, float b)
{

    glLineWidth(4);
    glBegin(GL_LINE_LOOP);
    glColor3ub(r, g, b); // Normalize RGB values

    for (int i = 0; i < 360; i++)
    {
        float pi = 3.1416f;
        float angle = (i * 2 * pi) / 360; // Divide circle into 100 segments
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(x + xc, y + yc); // Translate the circle
    }

    glEnd();
}

///50
void Tier1_Line3(float radius, float xc, float yc, float r, float g, float b)
{

    glLineWidth(4);
    glBegin(GL_LINE_LOOP);
    glColor3ub(r, g, b); // Normalize RGB values

    for (int i = 0; i < 360; i++)
    {
        float pi = 3.1416f;
        float angle = (i * 2 * pi) / 360; // Divide circle into 100 segments
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(x + xc, y + yc); // Translate the circle
    }

    glEnd();
}

///51
void Tier1_Inside(float radius, float xc, float yc, float r, float g, float b)
{

    glBegin(GL_POLYGON);
    glColor3ub(r, g, b); // Normalize RGB values

    for (int i = 0; i < 360; i++)
    {
        float pi = 3.1416f;
        float angle = (i * 2 * pi) / 360; // Divide circle into 100 segments
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(x + xc, y + yc); // Translate the circle
    }

    glEnd();
}

///52
void Tier1_Point1(float radius, float xc, float yc, float r, float g, float b)
{

    glBegin(GL_POLYGON);
    glColor3ub(r, g, b); // Normalize RGB values

    for (int i = 0; i < 360; i++)
    {
        float pi = 3.1416f;
        float angle = (i * 2 * pi) / 360; // Divide circle into 100 segments
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(x + xc, y + yc); // Translate the circle
    }

    glEnd();
}

///53
void Tier1_Point2(float radius, float xc, float yc, float r, float g, float b)
{

    glBegin(GL_POLYGON);
    glColor3ub(r, g, b); // Normalize RGB values

    for (int i = 0; i < 360; i++)
    {
        float pi = 3.1416f;
        float angle = (i * 2 * pi) / 360; // Divide circle into 100 segments
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(x + xc, y + yc); // Translate the circle
    }

    glEnd();
}

///54
void Tier1_Point3(float radius, float xc, float yc, float r, float g, float b)
{

    glBegin(GL_POLYGON);
    glColor3ub(r, g, b); // Normalize RGB values

    for (int i = 0; i < 360; i++)
    {
        float pi = 3.1416f;
        float angle = (i * 2 * pi) / 360; // Divide circle into 100 segments
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(x + xc, y + yc); // Translate the circle
    }

    glEnd();
}

///55
void Tier1_Point4(float radius, float xc, float yc, float r, float g, float b)
{

    glBegin(GL_POLYGON);
    glColor3ub(r, g, b); // Normalize RGB values

    for (int i = 0; i < 360; i++)
    {
        float pi = 3.1416f;
        float angle = (i * 2 * pi) / 360; // Divide circle into 100 segments
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(x + xc, y + yc); // Translate the circle
    }

    glEnd();
}

///56
void Tier1_Point5(float radius, float xc, float yc, float r, float g, float b)
{

    glBegin(GL_POLYGON);
    glColor3ub(r, g, b); // Normalize RGB values

    for (int i = 0; i < 360; i++)
    {
        float pi = 3.1416f;
        float angle = (i * 2 * pi) / 360; // Divide circle into 100 segments
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(x + xc, y + yc); // Translate the circle
    }

    glEnd();
}

///57
void drawTier2(float radius, float xc, float yc, float r, float g, float b)
{

    glBegin(GL_POLYGON);
    glColor3ub(r, g, b); // Normalize RGB values

    for (int i = 0; i < 360; i++)
    {
        float pi = 3.1416f;
        float angle = (i * 2 * pi) / 360; // Divide circle into 100 segments
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(x + xc, y + yc); // Translate the circle
    }

    glEnd();
}

///58
void Tier2_Line1(float radius, float xc, float yc, float r, float g, float b)
{

    glLineWidth(2);
    glBegin(GL_LINE_LOOP);
    glColor3ub(r, g, b); // Normalize RGB values

    for (int i = 0; i < 360; i++)
    {
        float pi = 3.1416f;
        float angle = (i * 2 * pi) / 360; // Divide circle into 100 segments
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(x + xc, y + yc); // Translate the circle
    }

    glEnd();
}

///59
void Tier2_Line2(float radius, float xc, float yc, float r, float g, float b)
{

    glLineWidth(4);
    glBegin(GL_LINE_LOOP);
    glColor3ub(r, g, b); // Normalize RGB values

    for (int i = 0; i < 360; i++)
    {
        float pi = 3.1416f;
        float angle = (i * 2 * pi) / 360; // Divide circle into 100 segments
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(x + xc, y + yc); // Translate the circle
    }

    glEnd();
}

///60
void Tier2_Line3(float radius, float xc, float yc, float r, float g, float b)
{

    glLineWidth(4);
    glBegin(GL_LINE_LOOP);
    glColor3ub(r, g, b); // Normalize RGB values

    for (int i = 0; i < 360; i++)
    {
        float pi = 3.1416f;
        float angle = (i * 2 * pi) / 360; // Divide circle into 100 segments
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(x + xc, y + yc); // Translate the circle
    }

    glEnd();
}

///61
void Tier2_Inside(float radius, float xc, float yc, float r, float g, float b)
{

    glBegin(GL_POLYGON);
    glColor3ub(r, g, b); // Normalize RGB values

    for (int i = 0; i < 360; i++)
    {
        float pi = 3.1416f;
        float angle = (i * 2 * pi) / 360; // Divide circle into 100 segments
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(x + xc, y + yc); // Translate the circle
    }

    glEnd();
}

///62
void Tier2_Point1(float radius, float xc, float yc, float r, float g, float b)
{

    glBegin(GL_POLYGON);
    glColor3ub(r, g, b); // Normalize RGB values

    for (int i = 0; i < 360; i++)
    {
        float pi = 3.1416f;
        float angle = (i * 2 * pi) / 360; // Divide circle into 100 segments
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(x + xc, y + yc); // Translate the circle
    }

    glEnd();
}

///63
void Tier2_Point2(float radius, float xc, float yc, float r, float g, float b)
{

    glBegin(GL_POLYGON);
    glColor3ub(r, g, b); // Normalize RGB values

    for (int i = 0; i < 360; i++)
    {
        float pi = 3.1416f;
        float angle = (i * 2 * pi) / 360; // Divide circle into 100 segments
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(x + xc, y + yc); // Translate the circle
    }

    glEnd();
}

///64
void Tier2_Point3(float radius, float xc, float yc, float r, float g, float b)
{

    glBegin(GL_POLYGON);
    glColor3ub(r, g, b); // Normalize RGB values

    for (int i = 0; i < 360; i++)
    {
        float pi = 3.1416f;
        float angle = (i * 2 * pi) / 360; // Divide circle into 100 segments
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(x + xc, y + yc); // Translate the circle
    }

    glEnd();
}

///65
void Tier2_Point4(float radius, float xc, float yc, float r, float g, float b)
{

    glBegin(GL_POLYGON);
    glColor3ub(r, g, b); // Normalize RGB values

    for (int i = 0; i < 360; i++)
    {
        float pi = 3.1416f;
        float angle = (i * 2 * pi) / 360; // Divide circle into 100 segments
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(x + xc, y + yc); // Translate the circle
    }

    glEnd();
}

///66
void Tier2_Point5(float radius, float xc, float yc, float r, float g, float b)
{

    glBegin(GL_POLYGON);
    glColor3ub(r, g, b); // Normalize RGB values

    for (int i = 0; i < 360; i++)
    {
        float pi = 3.1416f;
        float angle = (i * 2 * pi) / 360; // Divide circle into 100 segments
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(x + xc, y + yc); // Translate the circle
    }

    glEnd();
}

///67
void drawDashedCircle(float centerX, float centerY, float radius, int dashLength, int gapLength, int segments, int r, int g, int b)
{
    glColor3ub(r, g, b);
    glBegin(GL_LINES);

    float angleStep = 2.0f * M_PI / segments;
    float currentAngle = 0.0f;
    int dashCounter = 0;

    for (int i = 0; i < segments; i++)
    {
        float x1 = centerX + radius * cos(currentAngle);
        float y1 = centerY + radius * sin(currentAngle);
        float nextAngle = currentAngle + angleStep;
        float x2 = centerX + radius * cos(nextAngle);
        float y2 = centerY + radius * sin(nextAngle);

        if (dashCounter < dashLength)
        {
            glVertex2f(x1, y1);
            glVertex2f(x2, y2);
        }
        dashCounter++;
        if (dashCounter >= dashLength + gapLength)
        {
            dashCounter = 0;
        }

        currentAngle = nextAngle;
    }

    glEnd();
}

///68
void Tier1()
{
    drawTier1(-1.0, -2.5, 1.1, 41, 33, 44);
    Tier1_Line1(-0.8, -2.5, 1.1, 63, 54, 67);
    Tier1_Line2(-0.6, -2.5, 1.1, 63, 54, 67);
    Tier1_Line3(-0.45, -2.5, 1.1, 225, 227, 228);
    Tier1_Inside(-0.4, -2.5, 1.1, 165, 168, 170);
    Tier1_Point1(-0.1, -2.5, 1.1, 41, 43, 44);
    Tier1_Point2(-0.06, -2.5, 0.85, 41, 43, 44);
    Tier1_Point3(-0.06, -2.5, 1.35, 41, 43, 44);
    Tier1_Point4(-0.06, -2.25, 1.1, 41, 43, 44);
    Tier1_Point5(-0.06, -2.75, 1.1, 41, 43, 44);
    drawDashedCircle(-2.5, 1.1, 1.0, 10, 5, 360, 41, 33, 44);
}

///69
void Tier2()
{
    drawTier2(-1.0, 3.2, 1.2, 41, 33, 44);
    Tier2_Line1(-0.8, 3.2, 1.2, 63, 54, 67);
    Tier2_Line2(-0.6, 3.2, 1.2, 63, 54, 67);
    Tier2_Line3(-0.45, 3.2, 1.2, 225, 227, 228);
    Tier2_Inside(-0.4, 3.2, 1.2, 165, 168, 170);
    Tier2_Point1(-0.1, 3.2, 1.2, 41, 43, 44);
    Tier2_Point2(-0.06, 3.2, 0.95, 41, 43, 44);
    Tier2_Point3(-0.06, 3.2, 1.45, 41, 43, 44);
    Tier2_Point4(-0.06, 2.95, 1.2, 41, 43, 44);
    Tier2_Point5(-0.06, 3.45, 1.2, 41, 43, 44);
    drawDashedCircle(3.2, 1.2, 1.0, 10, 5, 360, 41, 33, 44);
}

///70
void Jeep()
{

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(0.39, 0.39, 1.0);
    glTranslatef(-18.0, -14.5, 0.0);

    glTranslatef(_move, 0.0f, 0.0f);

    drawJeep();

    glPushMatrix();
    glTranslatef(-2.5, 1.1, 0.0); // Move to center of Tier1
    glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f); // Rotate around Z-axis
    glTranslatef(2.5, -1.1, 0.0); // Move back to original position

    Tier1();

    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.2, 1.2, 0.0); // Move to center of Tier2
    glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f); // Rotate around Z-axis
    glTranslatef(-3.2, -1.2, 0.0); // Move back to original position

    Tier2();

    glPopMatrix();

    glPopMatrix();

}

///71
void drawRedFire()
{
    // Red

    glBegin(GL_POLYGON);
    glColor3ub(214, 50, 7);

    glVertex2f(1.548907927107,-3.5435978693614);
    glVertex2f(1.7039234786894,-3.5245281505321);
    glVertex2f(1.7590643690432,-3.5026959346957);
    glVertex2f(1.8188097691947,-3.4928386018897);
    glVertex2f(1.8820696046492,-3.4895528242877);
    glVertex2f(1.9312716988917,-3.4928386018897);
    glVertex2f(1.9910170990432,-3.4747668250786);
    glVertex2f(2.0507624991947,-3.4336946050536);
    glVertex2f(2.0982073757856,-3.3827650522225);
    glVertex2f(2.1421378170735,-3.3334783881924);
    glVertex2f(2.1772821701038,-3.2759772801573);
    glVertex2f(2.1966115642705,-3.2299763937293);
    glVertex2f(2.201883217225,-3.1806897296992);
    glVertex2f(2.1913399113159,-3.1396175096741);
    glVertex2f(2.1579527759371,-3.085402179241);
    glVertex2f(2.1140223346492,-2.9868288511809);
    glVertex2f(2.0999645934371,-2.9358992983498);
    glVertex2f(2.0999645934371,-2.8767553015137);
    glVertex2f(2.0577913698008,-2.8915413007227);
    glVertex2f(2.024404234422,-2.9227561879418);
    glVertex2f(1.9804737931341,-2.9539710751608);
    glVertex2f(1.9857454460886,-2.8948270783247);
    glVertex2f(2.0050748402553,-2.8488261918966);
    glVertex2f(2.0269814229246,-2.8226496167716);
    glVertex2f(2.0072220169442,-2.8218098980892);
    glVertex2f(1.9820736820601,-2.8402837091005);
    glVertex2f(1.9470456441857,-2.859597238794);
    glVertex2f(1.954230882724,-2.8100538365366);
    glVertex2f(1.9565843529333,-2.7467580071586);
    glVertex2f(1.9312996768099,-2.6980013452511);
    glVertex2f(1.8949529548825,-2.6477672087404);
    glVertex2f(1.8507047716666,-2.610830343659);
    glVertex2f(1.7890733736158,-2.5857132754036);
    glVertex2f(1.7132193452455,-2.5783259023873);
    glVertex2f(1.6247229788136,-2.5738934785776);
    glVertex2f(1.6058021424049,-2.5637072762717);
    glVertex2f(1.6002556682857,-2.5369149732583);
    glVertex2f(1.6091377729285,-2.5087234733715);
    glVertex2f(1.6642617555646,-2.4474075589076);
    glVertex2f(1.6662729153353,-2.4321419860351);
    glVertex2f(1.6542355981491,-2.4280495714609);
    glVertex2f(1.6405568286193,-2.4362344006093);
    glVertex2f(1.5983698451363,-2.4637135618494);
    glVertex2f(1.5658424095954,-2.4913600359782);
    glVertex2f(1.5461288122979,-2.5088694695931);
    glVertex2f(1.5274008948653,-2.5300650997585);
    glVertex2f(1.5,-2.55);
    glVertex2f(1.474174182162,-2.5761425566399);
    glVertex2f(1.4613603439186,-2.5945735393924);
    glVertex2f(1.4554462647294,-2.6176122678331);
    glVertex2f(1.4544605848645,-2.6434156436866);
    glVertex2f(1.4712171425674,-2.6673759212649);
    glVertex2f(1.4988161787839,-2.6876500022927);
    glVertex2f(1.5244438552706,-2.7051594359077);
    glVertex2f(1.5431717727033,-2.7263550660731);
    glVertex2f(1.5412004129735,-2.7493937945138);
    glVertex2f(1.521486815676,-2.7705894246792);
    glVertex2f(1.4889593801351,-2.798235898808);
    glVertex2f(1.474174182162,-2.8139022341476);
    glVertex2f(1.466288743243,-2.7853342108812);
    glVertex2f(1.4633317036484,-2.7567661876148);
    glVertex2f(1.4585085722013,-2.7484400169659);
    glVertex2f(1.4397850598436,-2.7455224644417);
    glVertex2f(1.422309781643,-2.75135756949);
    glVertex2f(1.3875548565824,-2.7717280290927);
    glVertex2f(1.3437823536194,-2.8082678126208);
    glVertex2f(1.2906300285928,-2.8491923701722);
    glVertex2f(1.2515474366615,-2.8901169277237);
    glVertex2f(1.2296611851799,-2.9383494419808);
    glVertex2f(1.2296611851799,-2.9836587735556);
    glVertex2f(1.2437309182752,-3.0245833311071);
    glVertex2f(1.2603347774513,-3.0622867321621);
    glVertex2f(1.2395477491135,-3.0622867321621);
    glVertex2f(1.2143845042835,-3.0622867321621);
    glVertex2f(1.1323304450554,-3.081721305923);
    glVertex2f(1.1596817981314,-3.0909271566518);
    glVertex2f(1.1837509888384,-3.1021787519871);
    glVertex2f(1.1957855841918,-3.1216133257479);
    glVertex2f(1.2176666666527,-3.1533223671473);
    glVertex2f(1.2242309913909,-3.1881000254562);
    glVertex2f(1.1705072581997,-3.1942454986836);
    glVertex2f(1.127226785847,-3.2081987882175);
    glVertex2f(1.0973781842244,-3.2277333935649);
    glVertex2f(1.0787228082103,-3.2451750054823);
    glVertex2f(1.0645447224396,-3.2751745779802);
    glVertex2f(1.0675295826018,-3.3142437886751);
    glVertex2f(1.0846925285348,-3.3449410256497);
    glVertex2f(1.1114252273539,-3.3820957885765);
    glVertex2f(1.1474635961353,-3.4279224216717);
    glVertex2f(1.1932201164176,-3.4606361492291);
    glVertex2f(1.2376308566916,-3.4820258941704);
    glVertex2f(1.3,-3.5);
    glVertex2f(1.3735546375303,-3.5034156391118);
    glVertex2f(1.4300773978791,-3.5134814014371);
    glVertex2f(1.4866001582279,-3.5273218246344);

    glEnd();
}

///72
void drawOrangeFire()
{
    // Orange

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glScalef(1.2, 1.2, 1.0);
    glTranslatef(-0.15, 0.6, 0.0);

    glBegin(GL_POLYGON);
    glColor3ub(246, 125, 17);

    glVertex2f(1.5220947993032,-3.525226698014);
    glVertex2f(1.5502525706963,-3.525226698014);
    glVertex2f(1.5743878033189,-3.5233462867024);
    glVertex2f(1.5985230359415,-3.5164514452267);
    glVertex2f(1.6233286916926,-3.5007813509637);
    glVertex2f(1.6514864630857,-3.4832308453892);
    glVertex2f(1.6796442344787,-3.4675607511262);
    glVertex2f(1.7,-3.45);
    glVertex2f(1.7171879296695,-3.428698917354);
    glVertex2f(1.7044498902298,-3.4111484117795);
    glVertex2f(1.6917137477697,-3.4001038034257);
    glVertex2f(1.6682470412958,-3.3923442986639);
    glVertex2f(1.6648949256538,-3.3810618307946);
    glVertex2f(1.6910414276617,-3.3603773063674);
    glVertex2f(1.7151766602843,-3.3409463894814);
    glVertex2f(1.7373006235217,-3.312740219808);
    glVertex2f(1.7600950098875,-3.2726247784948);
    glVertex2f(1.7661288180432,-3.23062892587);
    glVertex2f(1.75,-3.2);
    glVertex2f(1.7110689729454,-3.1630728180329);
    glVertex2f(1.6649286400662,-3.1373952402356);
    glVertex2f(1.6187883071869,-3.1168531779978);
    glVertex2f(1.5792394504333,-3.0891213939768);
    glVertex2f(1.5726479743077,-3.0541998881725);
    glVertex2f(1.5726479743077,-3.0254410010396);
    glVertex2f(1.5837164265717,-2.9859422626519);
    glVertex2f(1.6,-2.95);
    glVertex2f(1.6103496722471,-2.9174661021738);
    glVertex2f(1.6266726649369,-2.8746219146712);
    glVertex2f(1.6045314294264,-2.8913796022765);
    glVertex2f(1.5802815048196,-2.9130660215304);
    glVertex2f(1.5539228911166,-2.935738187114);
    glVertex2f(1.5296729665098,-2.9633390843462);
    glVertex2f(1.5064773864512,-2.9929114742379);
    glVertex2f(1.5033143528068,-2.9741822939732);
    glVertex2f(1.5149121428362,-2.9446099040815);
    glVertex2f(1.5265099328655,-2.9130660215304);
    glVertex2f(1.5033143528068,-2.924894977487);
    glVertex2f(1.4769557391038,-2.9436241577518);
    glVertex2f(1.4527058144971,-2.9653105770057);
    glVertex2f(1.4295102344384,-2.9988259522162);
    glVertex2f(1.4063146543798,-3.0293840884376);
    glVertex2f(1.3789016961287,-3.0678281952968);
    glVertex2f(1.3767930070324,-3.1092295411451);
    glVertex2f(1.390499486158,-3.130915960399);
    glVertex2f(1.4179124444091,-3.1535881259827);
    glVertex2f(1.4474340917565,-3.1782317842257);
    glVertex2f(1.4674666381708,-3.205832681458);
    glVertex2f(1.4674666381708,-3.2363908176794);
    glVertex2f(1.4442710581121,-3.2610344759224);
    glVertex2f(1.4231841671497,-3.283706641506);
    glVertex2f(1.4295102344384,-3.2442767883171);
    glVertex2f(1.4231841671497,-3.205832681458);
    glVertex2f(1.4063146543798,-3.1782317842257);
    glVertex2f(1.3883907970618,-3.1614740966204);
    glVertex2f(1.3914055452603,-3.2018630999429);
    glVertex2f(1.3939530403931,-3.2169475097001);
    glVertex2f(1.3778189045516,-3.2344136683663);
    glVertex2f(1.3363025778645,-3.2651686234412);
    glVertex2f(1.3,-3.3);
    glVertex2f(1.2793540908285,-3.329333602002);
    glVertex2f(1.2793540908285,-3.3566378481982);
    glVertex2f(1.2954164846079,-3.378481245155);
    glVertex2f(1.324620836934,-3.41397676521);
    glVertex2f(1.3611262773417,-3.4399157990963);
    glVertex2f(1.3976317177493,-3.463124408363);
    glVertex2f(1.4558854604123,-3.492883638528);
    glVertex2f(1.4830761613758,-3.5071025039549);
    glVertex2f(1.5061191282941,-3.5183052464124);

    glEnd();

    glPopMatrix();
}

///73
void drawYellowFire()
{
    // Yellow

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    glScalef(1.1, 1.1, 1.0);
    glTranslatef(-0.02, 0.35, 0.0);

    glBegin(GL_POLYGON);
    glColor3ub(255, 228, 0);

    glVertex2f(1.3819259624613,-3.317261969399);
    glVertex2f(1.3752274057977,-3.344400475986);
    glVertex2f(1.3692731332078,-3.3624928137106);
    glVertex2f(1.3752274057977,-3.3722348417162);
    glVertex2f(1.3782045420926,-3.3875437428678);
    glVertex2f(1.3878802350511,-3.4049402214492);
    glVertex2f(1.4109530413368,-3.4265118548901);
    glVertex2f(1.4347701316961,-3.4418207560417);
    glVertex2f(1.4675186309403,-3.4557379389069);
    glVertex2f(1.5054771187006,-3.4668716851989);
    glVertex2f(1.5404584701659,-3.4731344174882);
    glVertex2f(1.5717184012626,-3.469655121772);
    glVertex2f(1.6,-3.45);
    glVertex2f(1.6074440368017,-3.4167698268845);
    glVertex2f(1.6,-3.4);
    glVertex2f(1.6014897642118,-3.3778017148622);
    glVertex2f(1.6282839908662,-3.3694514051432);
    glVertex2f(1.65,-3.35);
    glVertex2f(1.6699638989951,-3.322828842545);
    glVertex2f(1.6878267167646,-3.2922110402418);
    glVertex2f(1.6967581256494,-3.262984956225);
    glVertex2f(1.6967581256494,-3.2414133227841);
    glVertex2f(1.6818724441748,-3.2198416893432);
    glVertex2f(1.6595439219629,-3.2024452107618);
    glVertex2f(1.6178640138339,-3.1808735773209);
    glVertex2f(1.5888369349584,-3.1753067041748);
    glVertex2f(1.55,-3.15);
    glVertex2f(1.5359927657235,-3.1328592964362);
    glVertex2f(1.5337599135023,-3.1133752404251);
    glVertex2f(1.5278056409125,-3.1245089867172);
    glVertex2f(1.5300384931337,-3.1460806201581);
    glVertex2f(1.5359927657235,-3.1669563944558);
    glVertex2f(1.5531112994193,-3.1850487321804);
    glVertex2f(1.5754398216313,-3.200357633332);
    glVertex2f(1.6007454801381,-3.221929266773);
    glVertex2f(1.5985126279169,-3.2372381679246);
    glVertex2f(1.5717184012626,-3.2567222239357);
    glVertex2f(1.5449241746083,-3.2782938573767);
    glVertex2f(1.5359927657235,-3.2956903359581);
    glVertex2f(1.5345041975761,-3.3304832931208);
    glVertex2f(1.5322713453549,-3.344400475986);
    glVertex2f(1.5091985390692,-3.3332667296939);
    glVertex2f(1.4928242894471,-3.3214371242585);
    glVertex2f(1.4920800053734,-3.2922110402418);
    glVertex2f(1.490591437226,-3.2803814348064);
    glVertex2f(1.4779386079725,-3.3033447865339);
    glVertex2f(1.4697514831615,-3.3214371242585);
    glVertex2f(1.4734729035301,-3.3367460254101);
    glVertex2f(1.4883585850048,-3.3541425039915);
    glVertex2f(1.4965457098158,-3.3617969545673);
    glVertex2f(1.4861257327836,-3.3666679685701);
    glVertex2f(1.4697514831615,-3.3680596868566);
    glVertex2f(1.4444458246546,-3.3722348417162);
    glVertex2f(1.4258387228114,-3.3778017148622);
    glVertex2f(1.4049987687469,-3.3701472642864);
    glVertex2f(1.3926460047994,-3.3560225498995);

    glEnd();

    glPopMatrix();

}

///74
void Fire()
{
    if (!startFire || !startScene3) return;

    glPushMatrix();
    glScalef(0.8, 0.8, 1.0);
    glTranslatef(-0.25, -0.15, 0.0);

    float redOffset = 0.08 * sin(fireTime); // Sinusoidal vertical motion
    glTranslatef(0.0f, redOffset, 0.0f); // Move up and down

    drawRedFire();

        glPushMatrix();
        float orangeOffset = 0.08 * sin(fireTime); // Sinusoidal vertical motion
        glTranslatef(0.0f, orangeOffset, 0.0f); // Move up and down

        drawOrangeFire();

            glPushMatrix();
            float yellowOffset = 0.08 * sin(fireTime); // Sinusoidal vertical motion
            glTranslatef(0.0f, yellowOffset, 0.0f); // Move up and down

            drawYellowFire();

            glPopMatrix();

        glPopMatrix();

    glPopMatrix();
}

///75
void Ringing()
{
    if (startScene2 == false) return;

    if (startRing == false) return;

    glPushMatrix();

    float ring = 0.02 * sin(ringTime); // Sinusoidal vertical motion
    glTranslatef(0.0f, ring, 0.0f); // Move up and down

    glBegin(GL_POLYGON);
    glColor3ub(255, 0, 0);

    glVertex2f(-3.0134014237237,-2.7582030600353);
    glVertex2f(-3.0056934558427,-2.7629553831935);
    glVertex2f(-2.9976643226332,-2.7545689305614);
    glVertex2f(-3.0061752038352,-2.7495370589822);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 0, 0);

    glVertex2f(-3.0215911395974,-2.752612091614);
    glVertex2f(-3.0644476274235,-2.731879047334);
    glVertex2f(-3.0517107326383,-2.7187672048749);
    glVertex2f(-3.014234869136,-2.7456304918643);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 0, 0);

    glVertex2f(-3.0323080200136,-2.6824416172808);
    glVertex2f(-3.0175849428424,-2.6753711362366);
    glVertex2f(-2.9967695578762,-2.7189724360088);
    glVertex2f(-3.0038772503037,-2.7244225984803);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 0, 0);

    glVertex2f(-3,-2.73);
    glVertex2f(-2.9944003270671,-2.7376797504381);
    glVertex2f(-2.9878003269558,-2.7319349845897);
    glVertex2f(-2.9930464808904,-2.7248645035456);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 0, 0);

    glVertex2f(-2.971056063769,-2.7245563085457);
    glVertex2f(-2.9758304621242,-2.73153199365);
    glVertex2f(-2.9635534377824,-2.7361329774422);
    glVertex2f(-2.9587790394272,-2.7273762663538);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(255, 0, 0);

    glVertex2f(-2.9662816654139,-2.7171353669453);
    glVertex2f(-2.9574149256114,-2.7199553247535);
    glVertex2f(-2.9357596187863,-2.6700865971991);
    glVertex2f(-2.9596316105621,-2.666821382895);

    glEnd();

    glPopMatrix();
}

///76
void updateRing()
{
    if (startScene && startSnow == true)
    {
        startRing = true;
        if (msg1 || msg2 == true)
        {
            startRing = false;
        }
        return;
    }
}

///77
void drawText(const char* text, float x, float y)
{
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);
    }
}

///78
void Text()
{
    if (!text) return;
    glBegin(GL_POLYGON);
    glColor3ub(0, 0, 0);

    glVertex2f(-2.15, -2.15);
    glVertex2f(1.0, -2.15);
    glVertex2f(1.0, -1.3);
    glVertex2f(-2.15, -1.3);

    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f); // White color
    drawText("What??? Fail!!!", -1.8, -1.7);
    drawText("I will Destroy AIUB", -2, -2);

}

///79
void Backside()
{
    glBegin(GL_POLYGON);
    glColor3ub(102, 0, 0); // Red color
    glVertex2f(0.4553955360745, -0.1172633447132);
    glVertex2f(0.4677444412462, -0.1430244458123);
    glVertex2f(0.4809649749311, -0.174467877279);
    glVertex2f(0.5, -0.22);
    glVertex2f(0.5541985121871, -0.3415585970059);
    glVertex2f(0.6327020020152, -0.3415585970059);
    glVertex2f(0.6273304934682, -0.302125954723);
    glVertex2f(0.620705475634, -0.3019051207952);
    glVertex2f(0.6155158783306, -0.3019051207952);
    glVertex2f(0.6033700123012, -0.3017947038313);
    glVertex2f(0.5996158355285, -0.3016842868674);
    glVertex2f(0.5964137435753, -0.301021785084);//S1
    glVertex2f(0.5934324855499, -0.3001384493727);
    glVertex2f(0.5903408105606, -0.2985926118781);
    glVertex2f(0.5866970507518, -0.2961634386722);
    glVertex2f(0.5832741248708, -0.2935134315385);
    glVertex2f(0.58, -0.29);
    glVertex2f(0.5775324427478, -0.2862259119209);
    glVertex2f(0.5752988119262, -0.2810792134471);
    glVertex2f(0.5722850795003, -0.2742983154889);
    glVertex2f(0.5689699738319, -0.2657091780752);
    glVertex2f(0.5665589878912, -0.2581748470106);
    glVertex2f(0.531344320064, -0.1416419667345);
    glVertex2f(0.5565818017577, -0.0813310131852);
    glVertex2f(0.5653392195566, -0.0612737014521);
    glVertex2f(0.5692162918954, -0.0517425652859);
    glVertex2f(0.5718010067879, -0.045765412097);
    glVertex2f(0.5751934450844, -0.038334356781);
    glVertex2f(0.5774550706153, -0.0362342759308);
    glVertex2f(0.5793936067847, -0.0344572844422);
    glVertex2f(0.5817443004801, -0.0329359922251);//K
    glVertex2f(0.5848861259313, -0.030903301465);
    glVertex2f(0.5884401089085, -0.0296109440188);
    glVertex2f(0.5916710025241, -0.0284801312533);
    glVertex2f(0.5966788876284, -0.0273493184878);
    glVertex2f(0.6020111173948, -0.0268646844455);
    glVertex2f(0.61026436764, -0.0271279538165);
    glVertex2f(0.6110308900749, -0.0250439709465);
    glVertex2f(0.6114542698501, -0.0232563674515);
    glVertex2f(0.612, -0.022);
    glVertex2f(0.6125832825838, -0.0201986246311);
    glVertex2f(0.6135241265285, -0.0175642615858);
    glVertex2f(0.6148413080512, -0.0139890545957);//Z
    glVertex2f(0.6169233449369, -0.0087343900745);
    glVertex2f(0.6262284629413, 0.0193074817275);
    glVertex2f(0.6337563202885, 0.0409500716006);
    glVertex2f(0.646930070646, 0.0804713226732);
    glVertex2f(0.665087604482, 0.1310969388828);
    glVertex2f(0.6042673161284, 0.130920135719);
    glVertex2f(0.558641645573, 0.0549813477283);
    glVertex2f(0.5235566336678, -0.0026353231987);
    glVertex2f(0.4553955360745, -0.1172633447132);
    glEnd();
}

///80
void BottomWhite()
{
    glBegin(GL_POLYGON);
    glColor3ub(105,105,105); //  color
    glVertex2f(-0.6781753252683, -0.2369379670535);
    glVertex2f(-0.6783289682679, -0.2413936140401);
    glVertex2f(-0.6781753252683, -0.2456956180271);//J2

    glVertex2f(-0.6764852522734, -0.2509194800114);
    glVertex2f(-0.6741806072804, -0.2555287699975);
    glVertex2f(-0.6712613902891, -0.2605989889823);
    glVertex2f(-0.6664741436442, -0.2650484552966);//S2
    glVertex2f(-0.6615639401668, -0.2696698232753);
    glVertex2f(-0.6569425721881, -0.2727025960113);
    glVertex2f(-0.6515106125805, -0.2762399360117);
    glVertex2f(-0.6440498047052, -0.2805032547976);
    glVertex2f(-0.6346095988222, -0.2850710963539);
    glVertex2f(-0.6263874840208, -0.2890298923694);
    glVertex2f(-0.617099539523, -0.2926841656144);//B3
    glVertex2f(-0.6058321970175, -0.2967952230151);
    glVertex2f(-0.5930422406599, -0.3012108031862);
    glVertex2f(-0.5741618288938, -0.3069967358241);//E3
    glVertex2f(-0.5618099259905, -0.3095470418048);
    glVertex2f(-0.5461249108692, -0.3130948428441);
    glVertex2f(-0.5349213286396, -0.3153355592901);//H3
    glVertex2f(-0.5147548806264, -0.3183231812179);
    glVertex2f(-0.501684034692, -0.3194435394409);
    glVertex2f(-0.49, -0.32);
    glVertex2f(-0.4785299647509, -0.3209373504048);
    glVertex2f(-0.4647122133345, -0.3211240767753);
    glVertex2f(-0.4564962530328, -0.3211240767753);
    glVertex2f(-0.4452926708033, -0.3209373504048);//O3
    glVertex2f(-0.3756839914317, -0.3208504277624);
    glVertex2f(-0.2503585184285, -0.3219402144841);//Q3
    glVertex2f(-0.1609960072437, -0.3219402144841);
    glVertex2f(-0.1468287798607, -0.3213953211233);
    glVertex2f(-0.1343178232639, -0.3198763078136);
    glVertex2f(-0.1233983653427, -0.3186708543188);
    glVertex2f(-0.1102195167452, -0.3165293207971);
    glVertex2f(-0.0981703634859, -0.3135170324823);
    glVertex2f(-0.0867906076299, -0.3098353467642);
    glVertex2f(-0.0754108517739, -0.3058189623444);
    glVertex2f(-0.0640310959178, -0.300463783118);
    glVertex2f(-0.0539901348684, -0.2927657129801);
    glVertex2f(-0.0446185712222, -0.2843982454389);
    glVertex2f(-0.0365858023827, -0.2763654765994);
    glVertex2f(-0.02587544393, -0.2636469259368);
    glVertex2f(-0.0168385789855, -0.252936567484);
    glVertex2f(-0.0071279044182, -0.242896284293);
    glVertex2f(0.0025817916363, -0.2331865882385);
    glVertex2f(0.0139097703666, -0.2222631801771);
    glVertex2f(0.024833178428, -0.2141717667984);
    glVertex2f(0.0365657278272, -0.2048666414128);
    glVertex2f(0.0478937065575, -0.1987980813787);
    glVertex2f(0.0628628213082, -0.1911112386688);
    glVertex2f(0.0754045120453, -0.1862563906416);//O4
    glVertex2f(0.0883507734514, -0.1830198252901);
    glVertex2f(0.1069610242226, -0.1789741186007);
    glVertex2f(0.127179952162, -0.1761060721573);//R4
    glVertex2f(0.1474481266058, -0.174079254713);
    glVertex2f(0.1727833446605, -0.1710390285464);
    glVertex2f(0.1930515191042, -0.169012211102);
    glVertex2f(0.1930515191042, -0.169012211102);
    glVertex2f(0.2163599197145, -0.1669853936576);
    glVertex2f(0.240681729047, -0.1644518718522);//W4
    glVertex2f(0.2736175125181, -0.1598915326023);
    glVertex2f(0.3136471570445, -0.1558378977136);
    glVertex2f(0.3474434706659, -0.1526254870926);
    glVertex2f(0.3837211337601, -0.1492943476443);
    glVertex2f(0.4098857303731, -0.1469941633266);//D5

    glVertex2f(0.4349099308282, -0.146199521358);
    glVertex2f(0.4511162965121, -0.1450419238092);
    glVertex2f(0.4677444412462, -0.1430244458123);
    glVertex2f(0.4628896003543, -0.1335448330674);
    glVertex2f(0.4601274693501, -0.1285729972598);//H5
    glVertex2f(0.4544190652747, -0.1289412813937);//I5
    glVertex2f(0.4488948032663, -0.1291254234606);//J5
    glVertex2f(0.4409766943876, -0.1301382048289);//K5
    glVertex2f(0.4322299462076, -0.1304144179293);//L5
    glVertex2f(0.4220100614921, -0.1312430572305);//M5
    glVertex2f(0.4131712422786, -0.1322558385987);//N5
    glVertex2f(0.4063579858016, -0.1326241227326);//O5
    glVertex2f(0.3947307004504, -0.1335592094067);
    glVertex2f(0.3835970952249, -0.1343270442498);
    glVertex2f(0.3748949670027, -0.1350948790929);
    glVertex2f(0.363889334251, -0.1358627139361);

    glVertex2f(0.3491724997575, -0.1363746038315);
    glVertex2f(0.3418780687477, -0.1370144662008);
    glVertex2f(0.3322906587517, -0.1382120019981);
    glVertex2f(0.31, -0.14);
    glVertex2f(0.2728563663259, -0.1424456776229);
    glVertex2f(0.2272468850678, -0.1451934514666);
    glVertex2f(0.186478273001, -0.1481054951857);
    glVertex2f(0.1329995860975, -0.1520054865707);
    glVertex2f(0.0789043183285, -0.1589369427099);//D6
    glVertex2f(0.0535588047743, -0.1645281713113);
    glVertex2f(0.0339921098671, -0.1705938467325);
    glVertex2f(0.025382764108, -0.1739201848668);
    glVertex2f(0.0191214217377, -0.1774421899501);//H6
    glVertex2f(0.0148167488581, -0.1807685280843);
    glVertex2f(0.0107077429276, -0.1846818670657);//J6
    glVertex2f(0.0069900708952, -0.1883995390981);//K6
    glVertex2f(0.0032723988629, -0.1923128780795);
    glVertex2f(-0.001814941813, -0.1966175509591);//M6
    glVertex2f(-0.0112069553684, -0.2048355628201);
    glVertex2f(-0.0157072951971, -0.2089445687506);
    glVertex2f(-0.0249413341524, -0.2155450054383);
    glVertex2f(-0.0381116484363, -0.2240669735044);
    glVertex2f(-0.0516693249051, -0.2310394928312);//S6
    glVertex2f(-0.0663890879284, -0.2380120121581);
    glVertex2f(-0.0818605735801, -0.2436924005282);
    glVertex2f(-0.1010519295976, -0.2496630446225);//V6
    glVertex2f(-0.1287727771785, -0.2539277904042);
    glVertex2f(-0.1611848451193, -0.2564866378732);
    glVertex2f(-0.1884792181221, -0.2560601632951);
    glVertex2f(-0.204907073856, -0.2554783354239);
    glVertex2f(-0.2234582356265, -0.2558683228059);//C7
    glVertex2f(-0.2419826362752, -0.256063316497);
    glVertex2f(-0.2568021567942, -0.2564533038791);
    glVertex2f(-0.270256721476, -0.2552833417328);
    glVertex2f(-0.3102261927905, -0.2547691390312);
    glVertex2f(-0.3801577602149, -0.2552833417328);//H7
    glVertex2f(-0.4692398365981, -0.2523221800183);
    glVertex2f(-0.4962975777214, -0.2512421835987);
    glVertex2f(-0.5252632152635, -0.2506510481386);
    glVertex2f(-0.5633914524364, -0.2494687772185);
    glVertex2f(-0.6032930959893, -0.2476953708384);//J7
    glVertex2f(-0.6220956304371, -0.2461565470257);//R2
    glVertex2f(-0.6326969974052, -0.245388332028);
    glVertex2f(-0.6419155773775, -0.2444664740308);
    glVertex2f(-0.6502122993525, -0.2435446160336);
    glVertex2f(-0.6578944493294, -0.2423154720373);//M2
    glVertex2f(-0.664654741309, -0.241086328041);
    glVertex2f(-0.6714150332887, -0.2395498980456);
    glVertex2f(-0.6781753252683, -0.2369379670535);//F2

    glEnd();
}

///81
void MiddleRed()
{
    glBegin(GL_POLYGON);
    glColor3ub(128,0,0); // Dark Red color
    glVertex2f(-0.6781753252683, -0.2369379670535);//F2
    glVertex2f(-0.6714150332887, -0.2395498980456);
    glVertex2f(-0.664654741309, -0.241086328041);
    glVertex2f(-0.6578944493294, -0.2423154720373);//M2
    glVertex2f(-0.6502122993525, -0.2435446160336);
    glVertex2f(-0.6419155773775, -0.2444664740308);
    glVertex2f(-0.6326969974052, -0.245388332028);
    glVertex2f(-0.6220956304371, -0.2461565470257);//R2
    glVertex2f(-0.6032930959893, -0.2476953708384);//J7
    glVertex2f(-0.5633914524364, -0.2494687772185);
    glVertex2f(-0.5252632152635, -0.2506510481386);
    glVertex2f(-0.4962975777214, -0.2512421835987);
    glVertex2f(-0.4692398365981, -0.2523221800183);
    glVertex2f(-0.3801577602149, -0.2552833417328);//H7
    glVertex2f(-0.3102261927905, -0.2547691390312);
    glVertex2f(-0.270256721476, -0.2552833417328);
    glVertex2f(-0.2568021567942, -0.2564533038791);
    glVertex2f(-0.2419826362752, -0.256063316497);
    glVertex2f(-0.2234582356265, -0.2558683228059);//C7
    glVertex2f(-0.204907073856, -0.2554783354239);
    glVertex2f(-0.1884792181221, -0.2560601632951);
    glVertex2f(-0.1611848451193, -0.2564866378732);
    glVertex2f(-0.1287727771785, -0.2539277904042);
    glVertex2f(-0.1010519295976, -0.2496630446225);//V6
    glVertex2f(-0.0818605735801, -0.2436924005282);
    glVertex2f(-0.0663890879284, -0.2380120121581);
    glVertex2f(-0.0516693249051, -0.2310394928312);//S6
    glVertex2f(-0.0381116484363, -0.2240669735044);
    glVertex2f(-0.0249413341524, -0.2155450054383);
    glVertex2f(-0.0249413341524, -0.2155450054383);
    glVertex2f(-0.0112069553684, -0.2048355628201);
    glVertex2f(-0.001814941813, -0.1966175509591);//M6
    glVertex2f(0.0032723988629, -0.1923128780795);
    glVertex2f(0.0069900708952, -0.1883995390981);//K6
    glVertex2f(0.0107077429276, -0.1846818670657);//J6
    glVertex2f(0.0148167488581, -0.1807685280843);
    glVertex2f(0.0191214217377, -0.1774421899501);//H6
    glVertex2f(0.025382764108, -0.1739201848668);
    glVertex2f(0.0339921098671, -0.1705938467325);
    glVertex2f(0.0535588047743, -0.1645281713113);
    glVertex2f(0.0789043183285, -0.1589369427099);//D6
    glVertex2f(0.1329995860975, -0.1520054865707);
    glVertex2f(0.1329995860975, -0.1520054865707);
    glVertex2f(0.186478273001, -0.1481054951857);
    glVertex2f(0.2728563663259, -0.1424456776229);
    glVertex2f(0.31, -0.14);
    glVertex2f(0.3322906587517, -0.1382120019981);
    glVertex2f(0.3418780687477, -0.1370144662008);
    glVertex2f(0.3491724997575, -0.1363746038315);
    glVertex2f(0.363889334251, -0.1358627139361);
    glVertex2f(0.3835970952249, -0.1343270442498);
    glVertex2f(0.3947307004504, -0.1335592094067);
    glVertex2f(0.4063579858016, -0.1326241227326);//O5
    glVertex2f(0.4131712422786, -0.1322558385987);//N5
    glVertex2f(0.4220100614921, -0.1312430572305);//M5
    glVertex2f(0.4322299462076, -0.1304144179293);//L5
    glVertex2f(0.4409766943876, -0.1301382048289);//K5
    glVertex2f(0.4488948032663, -0.1291254234606);//J5
    glVertex2f(0.4544190652747, -0.1289412813937);//I5
    glVertex2f(0.4601274693501, -0.1285729972598);//H5
    glVertex2f(0.4553955360745, -0.1172633447132);
    glVertex2f(0.4639351977006, -0.1032484193279);
    glVertex2f(0.4053097521076, -0.0997638535124);
    glVertex2f(0.3625487531006, -0.0973672193498);
    glVertex2f(0.2402595129519, -0.0909338990919);
    glVertex2f(0.1671985779304, -0.0868749582574);
    glVertex2f(0.1112322517196, -0.0839358093953);
    glVertex2f(0.1061411867233, -0.0827951342266);
    glVertex2f(0.1020744271468, -0.0819236857459);
    glVertex2f(0.0977171847434, -0.0806649268294);
    glVertex2f(0.0923574069618, -0.0790830959684);
    glVertex2f(0.084666738739, -0.0771021662747);
    glVertex2f(0.0788404749339, -0.0751212365809);
    glVertex2f(0.0723150594721, -0.0736064079916);
    glVertex2f(0.0657954551125, -0.0714813478482);
    glVertex2f(0.0549430194652, -0.0676829953716);
    glVertex2f(0.0455375752376, -0.0646081386049);
    glVertex2f(-0.006373241942, -0.0646081386049);
    glVertex2f(-0.0845467291012, -0.0646081386049);
    glVertex2f(-0.2007497283683, -0.0646081386049);
    glVertex2f(-0.2811251222408, -0.0646081386049);
    glVertex2f(-0.3758961090458, -0.0646081386049);
    glVertex2f(-0.425119447489, -0.0646081386049);
    glVertex2f(-0.4288139703723, -0.0645673317942);
    glVertex2f(-0.4317929385511, -0.0646968521498);
    glVertex2f(-0.4355490288635, -0.064308291083);
    glVertex2f(-0.4390460784647, -0.0634016485938);
    glVertex2f(-0.4428021687771, -0.0622359653934);
    glVertex2f(-0.4461696980227, -0.0605522007706);
    glVertex2f(-0.4477239422899, -0.059127476859);
    glVertex2f(-0.4482802707238, -0.0578871280235);
    glVertex2f(-0.4485010644235, -0.0561485086802);
    glVertex2f(-0.4543572938343, -0.0576506320458);
    glVertex2f(-0.4587120513417, -0.0585157583211);
    glVertex2f(-0.4636734998573, -0.060169574493);
    glVertex2f(-0.4764466021266, -0.0645531267857);
    glVertex2f(-0.4888766506843, -0.0720111559204);//H9


    //

    glVertex2f(-0.4835965687598, -0.07472073376);//H10
    glVertex2f(-0.4800112041586, -0.0774695132876);
    glVertex2f(-0.4784464306734, -0.0809122018185);
    glVertex2f(-0.4783929280917, -0.0848713928668);
    glVertex2f(-0.479141964236, -0.0876535271169);
    glVertex2f(-0.48, -0.09);
    glVertex2f(-0.4811215597601, -0.092040738819);
    glVertex2f(-0.4825661294669, -0.0941808420883);
    glVertex2f(-0.4842247095006, -0.0964814531028);
    glVertex2f(-0.487146823431, -0.0997682408575);//Q10
    glVertex2f(-0.4910380649879, -0.1037277498101);
    glVertex2f(-0.4941916241386, -0.107220351868);
    glVertex2f(-0.4981717708446, -0.1115707447792);
    glVertex2f(-0.5025221637558, -0.1164765069983);
    glVertex2f(-0.5067036603589, -0.1209809324652);
    glVertex2f(-0.5135467574035, -0.128720044501);
    glVertex2f(-0.521488448411, -0.1390529698869);//Z10
    glVertex2f(-0.5276440740255, -0.1477268059801);
    glVertex2f(-0.5325404807746, -0.1544808992339);
    glVertex2f(-0.5380359452894, -0.1630904603069);
    glVertex2f(-0.5398579368228, -0.1658173333287);
    glVertex2f(-0.5420148346344, -0.1689411163662);
    glVertex2f(-0.5443948598059, -0.1722880267636);
    glVertex2f(-0.5455848723916, -0.1739986698556);
    glVertex2f(-0.5465517576175, -0.1752630582279);
    glVertex2f(-0.5476673944166, -0.1763043192404);
    glVertex2f(-0.5485599038559, -0.1772712044663);
    glVertex2f(-0.5496011648684, -0.177717459186);
    glVertex2f(-0.5509866297445, -0.1777840515197);
    glVertex2f(-0.5521186994182, -0.1777174591859);//M11
    glVertex2f(-0.5534054895201, -0.1777796701489);
    glVertex2f(-0.5546773456042, -0.1775676941349);
    glVertex2f(-0.5557796208771, -0.1774405085265);
    glVertex2f(-0.5568395009471, -0.1771861373096);
    glVertex2f(-0.5580689618284, -0.1768469756872);
    glVertex2f(-0.5590220826131, -0.1766506151638);//S11
    glVertex2f(-0.5599983077711, -0.1763680236707);
    glVertex2f(-0.5606405611646, -0.1761881927206);
    glVertex2f(-0.5614369553725, -0.1759569814989);
    glVertex2f(-0.5624936991753, -0.1755700502894);
    glVertex2f(-0.5634607287588, -0.1753502708386);
    glVertex2f(-0.5649991849144, -0.174910711937);
    glVertex2f(-0.566845332301, -0.1741634618043);
    glVertex2f(-0.5686914796877, -0.1735480793421);
    glVertex2f(-0.5699662005023, -0.1731524763307);//Z11
    glVertex2f(-0.5712848772071, -0.1726250056487);
    glVertex2f(-0.5729657454408, -0.1719109838918);//P9


    //
    glVertex2f(-0.5844741870417, -0.1752300338643);
    glVertex2f(-0.6, -0.18);
    glVertex2f(-0.6141819663502, -0.1854204930457);
    glVertex2f(-0.6349265263913, -0.1945804286483);
    glVertex2f(-0.6502828890191, -0.2034709543802);
    glVertex2f(-0.6562784602447, -0.2080309089791);
    glVertex2f(-0.6630230762015, -0.2133074327537);
    glVertex2f(-0.6684329378972, -0.2189824837482);
    glVertex2f(-0.6718273609219, -0.2230663989498);
    glVertex2f(-0.6737367238733, -0.2257182919379);
    glVertex2f(-0.6752217839466, -0.2281049956272);
    glVertex2f(-0.6760703897028, -0.2297491692798);
    glVertex2f(-0.6768129197395, -0.2317115700909);
    glVertex2f(-0.6777676012152, -0.2338330844814);
    glVertex2f(-0.6781530933512, -0.2355585708968);
    glVertex2f(-0.6781753252683, -0.2369379670535);

    glEnd();

}

///82
void upperBodyWhite()
{
    glBegin(GL_POLYGON);
    glColor3ub(105,105,105); //  color
    glVertex2f(-0.4485010644235, -0.0561485086802);
    glVertex2f(-0.4482802707238, -0.0578871280235);
    glVertex2f(-0.4477239422899, -0.059127476859);
    glVertex2f(-0.4461696980227, -0.0605522007706);
    glVertex2f(-0.4428021687771, -0.0622359653934);
    glVertex2f(-0.4390460784647, -0.0634016485938);
    glVertex2f(-0.4355490288635, -0.064308291083);
    glVertex2f(-0.43176235008, -0.0647557984578);
    glVertex2f(-0.4288139703723, -0.0645673317942);
    glVertex2f(-0.425119447489, -0.0646081386049);
    glVertex2f(-0.3758961090458, -0.0646081386049);//Q8
    glVertex2f(-0.2811251222408, -0.0646081386049);
    glVertex2f(-0.2007497283683, -0.0646081386049);
    glVertex2f(-0.0845467291012, -0.0646081386049);

    //
    glVertex2f(-0.006373241942, -0.0646081386049);//M8
    glVertex2f(0.0455375752376, -0.0646081386049);//L8
    glVertex2f(0.0412489159835, -0.0631842749214);//U12
    glVertex2f(0.0373805332724, -0.0616369218369);
    glVertex2f(0.0340279349228, -0.0603474609332);
    glVertex2f(0.0293858756695, -0.0584132695777);
    glVertex2f(0.0265490616814, -0.057123808674);
    glVertex2f(0.0219070024281, -0.0549317251377);//R12
    glVertex2f(0.0137833987348, -0.0509343963363);
    glVertex2f(0.0092702855719, -0.0483554745289);
    glVertex2f(0.0054019028608, -0.0459054988119);
    glVertex2f(0.0013272086638, -0.0430517472902);
    glVertex2f(-0.0019599411804, -0.0406411707378);
    glVertex2f(-0.0050279477017, -0.0383401658468);//A13
    glVertex2f(-0.0071098092697, -0.0365870192633);
    glVertex2f(-0.0093012424991, -0.0347243010182);
    glVertex2f(-0.011821390713, -0.0326424394502);
    glVertex2f(-0.0140128239425, -0.0307797212052);//E13
    glVertex2f(-0.0185788691775, -0.0278081794825);
    glVertex2f(-0.0214182312776, -0.025720677923);
    glVertex2f(-0.0250772900261, -0.023159336799);
    glVertex2f(-0.03, -0.02);
    glVertex2f(-0.0351397015847, -0.0173048428013);
    glVertex2f(-0.0398964779579, -0.0147435016773);
    glVertex2f(-0.0462998307679, -0.0119992076159);
    glVertex2f(-0.0515511993713, -0.0098913672441);
    glVertex2f(-0.0563630834688, -0.0079666136051);
    glVertex2f(-0.0618165521126, -0.0062022561027);
    glVertex2f(-0.0680720014393, -0.0042775024637);
    glVertex2f(-0.0728838855367, -0.0028339372345);
    glVertex2f(-0.0764126005415, -0.0017111642784);//R13
    glVertex2f(-0.0904630839646, 0.0003010063108);
    glVertex2f(-0.107011461131, 0.0033405041577);
    glVertex2f(-0.1232221163143, 0.0053668360556);//U13
    glVertex2f(-0.1370687176168, 0.0067177239876);
    glVertex2f(-0.1610469784089, 0.0077308899365);
    glVertex2f(-0.1759067456603, 0.0084063339025);
    glVertex2f(-0.1927928448096, 0.0094194998515);
    glVertex2f(-0.209678943959, 0.0107703877834);
    glVertex2f(-0.2279159310402, 0.0107703877834);//D14
    glVertex2f(-0.2719740249078, 0.0101197056318);
    glVertex2f(-0.2852764677247, 0.0099702399821);
    glVertex2f(-0.2951412006001, 0.0095218430333);
    glVertex2f(-0.3057532617237, 0.0089239804347);
    glVertex2f(-0.3387269703437, 0.0057072652305);//J14
    glVertex2f(-0.3549140216216, 0.0033527850446);
    glVertex2f(-0.3711010728995, 0.0001153747891);
    glVertex2f(-0.381696233736, -0.0025334154201);
    glVertex2f(-0.3861761068188, -0.0041074754929);
    glVertex2f(-0.3916933974284, -0.0058152083007);
    glVertex2f(-0.3982616005351, -0.0084424895433);//C15
    glVertex2f(-0.4044357114553, -0.0108070426617);
    glVertex2f(-0.411003914562, -0.0144852364015);
    glVertex2f(-0.4170466614201, -0.0179007020169);
    glVertex2f(-0.4221212233671, -0.0214335746184);
    glVertex2f(-0.4257860946386, -0.0242527063657);
    glVertex2f(-0.4290280961479, -0.0267899249383);//U14
    glVertex2f(-0.4317062713079, -0.0293271435108);
    glVertex2f(-0.4348119270136, -0.0322918426292);
    glVertex2f(-0.4380180343011, -0.0366364628184);
    glVertex2f(-0.4411265094773, -0.0409639478676);
    glVertex2f(-0.4431988262615, -0.0446209774867);
    glVertex2f(-0.4453346624325, -0.0488254169337);//O14
    glVertex2f(-0.4472253661108, -0.0531224707479);
    glVertex2f(-0.4485010644235, -0.0561485086802);

    glEnd();
}

///83
void Glass1()
{

    glBegin(GL_POLYGON);
    glColor3ub(0,0,0); // Black color
    glVertex2f(-0.5738520217692, -0.1654963320736);
    glVertex2f(-0.5689328715154, -0.1681198788756);
    glVertex2f(-0.5623740045104, -0.1710713690278);

    glVertex2f(-0.5505680439014, -0.1713993123781);
    glVertex2f(-0.5210531423789, -0.1307343369471);
    glVertex2f(-0.487128694034, -0.092677995571);

    glVertex2f(-0.4822828085354, -0.0853696475868);
    glVertex2f(-0.48, -0.08);
    glVertex2f(-0.4803407223825, -0.0744454129763);
    glVertex2f(-0.4830110908428, -0.0710467622086);
    glVertex2f(-0.4907794354547, -0.0666770683644);
    glVertex2f(-0.5182114023654, -0.0928952314296);

    glEnd();

}

///84
void Glass2()
{

    glBegin(GL_POLYGON);
    glColor3ub(0,0,0); //  color
    glVertex2f(-0.5093304091165,-0.1892063829271);//A1
    glVertex2f(-0.5053728508763,-0.1915515582019);
    glVertex2f(-0.5000383305749,-0.1925774274906);
    glVertex2f(-0.494293462558,-0.1938084706371);//Z10
    glVertex2f(-0.4873175513947,-0.194629166068);
    glVertex2f(-0.4825985526665,-0.195449861499);
    glVertex2f(-0.4764433369341,-0.1952446876413);
    glVertex2f(-0.4044273128654,-0.1948343399258);
    glVertex2f(-0.3958178047999,-0.1916986676688);
    glVertex2f(-0.3918252604533,-0.1894675399457);
    glVertex2f(-0.3888895660809,-0.1864144177984);
    glVertex2f(-0.3879336683407,-0.1829094594177);
    glVertex2f(-0.3876946939057,-0.179324842892);
    glVertex2f(-0.3876946939057,-0.1762181752364);
    glVertex2f(-0.3861304010658,-0.1023777471359);
    glVertex2f(-0.3861304010658,-0.0977558172715);
    glVertex2f(-0.3864350974731,-0.0934391846893);
    glVertex2f(-0.3869429248186,-0.0907984824929);
    glVertex2f(-0.3877554485713,-0.0885640421728);
    glVertex2f(-0.3886695377932,-0.0860249054455);
    glVertex2f(-0.3921951408965,-0.0806938405961);
    glVertex2f(-0.3937906378658,-0.0794402358345);
    glVertex2f(-0.3955000989043,-0.0778447388652);//U11
    glVertex2f(-0.3970955958735,-0.0769330263113);
    glVertex2f(-0.3998307335352,-0.0767050981729);
    glVertex2f(-0.4024607173058,-0.0768308303482);
    glVertex2f(-0.4407212740232,-0.0768122999146);
    glVertex2f(-0.4436341828643,-0.0769389481251);
    glVertex2f(-0.4461671470739,-0.0780787820194);
    glVertex2f(-0.4531198255989,-0.0811732598496);
    glVertex2f(-0.4569372636126,-0.0838454664592);
    glVertex2f(-0.4607547016262,-0.0873765966218);
    glVertex2f(-0.4633314722855,-0.0898579313307);
    glVertex2f(-0.4670534743488,-0.0941525490962);
    glVertex2f(-0.5071719216191,-0.1637198790156);
    glVertex2f(-0.5103468387801,-0.1700697133374);
    glVertex2f(-0.5128162187941,-0.1767723162327);
    glVertex2f(-0.513521755941,-0.1820638448343);
    glVertex2f(-0.5126732206574,-0.1858060277737);
    glVertex2f(-0.5093304091165,-0.1892063829271);//A1

    glEnd();

}

///85
void BellowRedLine()
{
    glLineWidth(4.0);
    glBegin(GL_LINES); // Start drawing lines
    glColor3ub(102, 0, 0); // Red color

    glVertex2f(-0.5419797092173, -0.362915192356);
    glVertex2f(-0.5412043414459, -0.3662381970906);

    glVertex2f(-0.5412043414459, -0.3662381970906);
    glVertex2f(-0.5400690490384, -0.36927546336);

    glVertex2f(-0.5400690490384, -0.36927546336);
    glVertex2f(-0.5378280238055, -0.3725124998075);

    glVertex2f(-0.5378280238055, -0.3725124998075);
    glVertex2f(-0.5343419845544, -0.3757495362549);

    glVertex2f(-0.5343419845544, -0.3757495362549);
    glVertex2f(-0.5308559453033, -0.3774925558805);

    glVertex2f(-0.5308559453033, -0.3774925558805);
    glVertex2f(-0.5271209032485, -0.3792355755061);

    glVertex2f(-0.5271209032485, -0.3792355755061);
    glVertex2f(-0.5218913495952, -0.3803965165737);

    glVertex2f(-0.5218913495952, -0.3803965165737);
    glVertex2f(-0.5164137826916, -0.380729592328);

    glVertex2f(-0.5164137826916, -0.380729592328);
    glVertex2f(-0.5097309209821, -0.3814916016954);

    glVertex2f(-0.5097309209821, -0.3814916016954);
    glVertex2f(-0.5042851557045, -0.3814916016954);

    glVertex2f(-0.5042851557045, -0.3814916016954);
    glVertex2f(-0.4976724407245, -0.3812322795394);

    glVertex2f(-0.4976724407245, -0.3812322795394);
    glVertex2f(-0.4901520981982, -0.3814916016954);

    glVertex2f(-0.4901520981982, -0.3814916016954);
    glVertex2f(-0.4830207389061, -0.3812322795394);

    glVertex2f(-0.4830207389061, -0.3812322795394);
    glVertex2f(-0.4736851412872, -0.3814916016954);

    glVertex2f(-0.4736851412872, -0.3814916016954);
    glVertex2f(-0.4116731179133, -0.3814916016954);

    glVertex2f(-0.4116731179133, -0.3814916016954);
    glVertex2f(-0.133785502622, -0.3814916016954);

    glVertex2f(-0.133785502622, -0.3814916016954);
    glVertex2f(-0.0827663697243, -0.3814916016954);

    glVertex2f(-0.0827663697243, -0.3814916016954);
    glVertex2f(-0.0742500066491, -0.3792103399652);

    glVertex2f(-0.0742500066491, -0.3792103399652);
    glVertex2f(-0.0679952203621, -0.3761342155618);

    glVertex2f(-0.0679952203621, -0.3761342155618);
    glVertex2f(-0.0612277466745, -0.371827641397);

    glVertex2f(-0.0619985379256,-0.352924845602);
    glVertex2f(-0.4697345224877,-0.3619544594243);

    glVertex2f(-0.4697345224877,-0.3619544594243);
    glVertex2f(-0.46,-0.34);

    glVertex2f(-0.46,-0.34);
    glVertex2f(-0.4464540642884,-0.3001045383454);

    glVertex2f(-0.1598417729765,-0.3001045383454);
    glVertex2f(-0.1472345511013,-0.3380547668761);

    glVertex2f(-0.1472345511013,-0.3380547668761);
    glVertex2f(-0.1338606498264,-0.3780233601904);



    glEnd();
}

///86
void BellowBlackLine()
{
    glLineWidth(4.0);
    glBegin(GL_LINES); // Start drawing lines
    glColor3ub(0, 0, 0); // Black color

    glVertex2f(-0.5431481683901, -0.3442783029754);
    glVertex2f(-0.5413122249147, -0.3485621710848);

    glVertex2f(-0.5413122249147, -0.3485621710848);
    glVertex2f(-0.538741904049, -0.352111661804);

    glVertex2f(-0.538741904049, -0.352111661804);
    glVertex2f(-0.5349476208664, -0.3554163600598);

    glVertex2f(-0.5349476208664, -0.3554163600598);
    glVertex2f(-0.5280934318914, -0.3595778319375);

    glVertex2f(-0.5280934318914, -0.3595778319375);
    glVertex2f(-0.5207496579895,-0.3617809641081);

    glVertex2f(-0.5207496579895,-0.3617809641081);
    glVertex2f(-0.5081428461247,-0.3623929452666);

    glVertex2f(-0.5081428461247,-0.3623929452666);
    glVertex2f(-0.4359817156756,-0.3623929452666);

    glVertex2f(-0.4359817156756,-0.3623929452666);
    glVertex2f(-0.1574769845506,-0.3623929452666);

    glVertex2f(-0.1574769845506,-0.3623929452666);
    glVertex2f(-0.0880537744808,-0.3623929452666);

    glVertex2f(-0.0880537744808,-0.3623929452666);
    glVertex2f(-0.0792212232204,-0.3614432487515);

    glVertex2f(-0.0792212232204,-0.3614432487515);
    glVertex2f(-0.0687602837228,-0.3582699998995);

    glVertex2f(-0.0687602837228,-0.3582699998995);
    glVertex2f(-0.0619985379256,-0.352924845602);



    glEnd();
}

///87
void door()
{
    glLineWidth(1.0);
    glBegin(GL_LINES); // Start drawing lines
    glColor3ub(0, 0, 0); // Black color

    glVertex2f(-0.3805744941332, -0.2950468292592);
    glVertex2f(-0.38, -0.3);

    glVertex2f(-0.38, -0.3);
    glVertex2f(-0.3784260501836, -0.3054309750157);

    glVertex2f(-0.3784260501836, -0.3054309750157);
    glVertex2f(-0.3741291622843, -0.3093697889234);

    glVertex2f(-0.3741291622843, -0.3093697889234);
    glVertex2f(-0.3676838304354, -0.3104440108982);

    glVertex2f(-0.3676838304354, -0.3104440108982);
    glVertex2f(-0.3599984185686, -0.3106578058222);

    glVertex2f(-0.3599984185686, -0.3106578058222);
    glVertex2f(-0.2667778799647, -0.3104346169334);

    glVertex2f(-0.2667778799647, -0.3104346169334);
    glVertex2f(-0.2635448280214, -0.3095316714267);

    glVertex2f(-0.2635448280214, -0.3095316714267);
    glVertex2f(-0.2618078908252, -0.3082579174829);

    glVertex2f(-0.2618078908252, -0.3082579174829);
    glVertex2f(-0.259955157816, -0.3068104698194);

    glVertex2f(-0.259955157816, -0.3068104698194);
    glVertex2f(-0.2584498122459, -0.3049577368101);

    glVertex2f(-0.2584498122459, -0.3049577368101);
    glVertex2f(-0.2583980159171, -0.3024274664444);

    glVertex2f(-0.2583980159171, -0.3024274664444);
    glVertex2f(-0.2583980159171, -0.2986442891721);

    glVertex2f(-0.2583980159171, -0.2986442891721);
    glVertex2f(-0.25845806635, -0.2942606075709);

    glVertex2f(-0.25845806635, -0.2942606075709);
    glVertex2f(-0.25845806635, -0.2906575815973);

    glVertex2f(-0.25845806635, -0.2906575815973);
    glVertex2f(-0.2580063896595, -0.0795752142428);

    glVertex2f(-0.2580063896595, -0.0795752142428);
    glVertex2f(-0.2580063896595, -0.0740498374081);

    glVertex2f(-0.2580063896595, -0.0740498374081);
    glVertex2f(-0.2591057464186, -0.0715120323203);

    glVertex2f(-0.2591057464186, -0.0715120323203);
    glVertex2f(-0.26, -0.07);

    glVertex2f(-0.26, -0.07);
    glVertex2f(-0.261310515468, -0.0688511041572);

    glVertex2f(-0.261310515468, -0.0688511041572);
    glVertex2f(-0.262831045847, -0.0673305737782);

    glVertex2f(-0.262831045847, -0.0673305737782);
    glVertex2f(-0.2641234966691, -0.0665703085888);

    glVertex2f(-0.2641234966691, -0.0665703085888);
    glVertex2f(-0.265644027048, -0.0659620964372);

    glVertex2f(-0.265644027048, -0.0659620964372);
    glVertex2f(-0.2676207165406, -0.0660381229562);

    glVertex2f(-0.2676207165406, -0.0660381229562);
    glVertex2f(-0.2732466789426, -0.0660381229562);

    glVertex2f(-0.2732466789426, -0.0660381229562);
    glVertex2f(-0.3700814303612, -0.0661454485325);

    glVertex2f(-0.3700814303612, -0.0661454485325);
    glVertex2f(-0.3723071252839, -0.0665905875171);

    glVertex2f(-0.3723071252839, -0.0665905875171);
    glVertex2f(-0.3740876812221, -0.0679260044707);

    glVertex2f(-0.3740876812221, -0.0679260044707);
    glVertex2f(-0.3753118134296, -0.0694839909166);

    glVertex2f(-0.3753118134296, -0.0694839909166);
    glVertex2f(-0.3768697998755, -0.0708194078702);

    glVertex2f(-0.3768697998755, -0.0708194078702);
    glVertex2f(-0.3779826473369, -0.0725999638084);

    glVertex2f(-0.3779826473369, -0.0725999638084);
    glVertex2f(-0.3783165015753, -0.0761610756848);

    glVertex2f(-0.3783165015753, -0.0761610756848);
    glVertex2f(-0.3783566090966, -0.0800536513008);

    glVertex2f(-0.3783566090966, -0.0800536513008);
    glVertex2f(-0.3805744941332, -0.2950468292592);



    glEnd();
}

///88
void doorWindow()
{

    glBegin(GL_POLYGON);
    glColor3ub(0,0,0); // Black color
    glVertex2f(-0.3549152145501,-0.1850629931829);//5
    glVertex2f(-0.3539259341673,-0.1883605944589);//V5
    glVertex2f(-0.3524420135931,-0.1906689153521);
    glVertex2f(-0.350793212955,-0.1926474761177);
    glVertex2f(-0.348320011998,-0.1941313966919);//A6
    glVertex2f(-0.345846811041,-0.1956153172661);
    glVertex2f(-0.3412301692546,-0.1956153172661);
    glVertex2f(-0.2924256703697,-0.1956153172661);
    glVertex2f(-0.2890417953033,-0.1940796324177);
    glVertex2f(-0.2871226663289,-0.192824817319);
    glVertex2f(-0.2852035373544,-0.1912747516089);
    glVertex2f(-0.2836534716443,-0.1895032479402);
    glVertex2f(-0.2828300836331,-0.1880525166824);//I6
    glVertex2f(-0.2821635314336,-0.1869154570478);
    glVertex2f(-0.2820066956219,-0.1844845019672);
    glVertex2f(-0.2821776244551,-0.1826543001024);
    glVertex2f(-0.2821776244551,-0.1799673478379);
    glVertex2f(-0.2819709358194,-0.1779004614806);
    glVertex2f(-0.2820398320313,-0.1693573312037);
    glVertex2f(-0.2829865160976,-0.086741860904);
    glVertex2f(-0.2828034966492,-0.0832644913857);//Q6
    glVertex2f(-0.2829973605084,-0.0807214258769);
    glVertex2f(-0.2838118031951,-0.0790925405035);
    glVertex2f(-0.2846768648182,-0.077958188417);
    glVertex2f(-0.2856264968566,-0.0768661115729);
    glVertex2f(-0.287145908118,-0.0761064059422);

    glVertex2f(-0.2886178377775,-0.0750618106999);
    glVertex2f(-0.2903271754466,-0.0742071418654);
    glVertex2f(-0.292230196415,-0.0736799048497);
    glVertex2f(-0.294268148406,-0.0733524730308);
    glVertex2f(-0.2989213453942,-0.0733999546327);
    glVertex2f(-0.3044292112169,-0.0734474362346);
    glVertex2f(-0.3430138189309,-0.073718715538);

    glVertex2f(-0.3445699057094,-0.0740735433933);
    glVertex2f(-0.3460054121772,-0.0750305477052);
    glVertex2f(-0.3476535862699,-0.0761470527358);

    glVertex2f(-0.349142259644,-0.0772635577663);
    glVertex2f(-0.350365098487,-0.0782737289844);
    glVertex2f(-0.3514284366113,-0.0794965678274);
    glVertex2f(-0.352332274017,-0.0807194066704);

    glVertex2f(-0.3533956121413,-0.0822612469507);
    glVertex2f(-0.3537376075437,-0.0872201802852);
    glVertex2f(-0.3546363801852,-0.1791078197796);
    glVertex2f(-0.3544035785461,-0.1734041796229);



    glEnd();

}

///89
void window3()
{

    glBegin(GL_POLYGON);
    glColor3ub(0,0,0); // Black color
    glVertex2f(-0.2522222066944,-0.1650899929136);
    glVertex2f(-0.2522222066944,-0.1682723512843);
    glVertex2f(-0.2522222066944,-0.171454709655);
    glVertex2f(-0.2523896992402,-0.1749720531173);
    glVertex2f(-0.2521721169609,-0.1774609607423);
    glVertex2f(-0.2515522365111,-0.1804993071296);
    glVertex2f(-0.250262385878,-0.1840495329782);
    glVertex2f(-0.2484481413493,-0.1872005892649);
    glVertex2f(-0.2465384102664,-0.1897787262268);
    glVertex2f(-0.2441512464128,-0.1922613766345);
    glVertex2f(-0.2415731094509,-0.1942665942715);
    glVertex2f(-0.2389949724891,-0.1954124329213);
    glVertex2f(-0.2364168355272,-0.1959853522461);
    glVertex2f(-0.233647725457,-0.195889865692);
    glVertex2f(-0.23,-0.195);
    glVertex2f(-0.2175104978068,-0.1918794304179);
    glVertex2f(-0.1630980378636,-0.1777338579577);
    glVertex2f(-0.158720366617,-0.1757723303093);
    glVertex2f(-0.1553061024402,-0.1732772911031);
    glVertex2f(-0.1526719078419,-0.1712840106914);
    glVertex2f(-0.1507184552299,-0.1684812308567);
    glVertex2f(-0.1487485974095,-0.1652100401887);
    glVertex2f(-0.1484551607635,-0.1616888004366);
    glVertex2f(-0.1484693953144,-0.158780071105);//P8
    glVertex2f(-0.1484693953144,-0.1559413522881);
    glVertex2f(-0.1485482486149,-0.1522352471661);
    glVertex2f(-0.1480682920274,-0.0914589164667);
    glVertex2f(-0.1482902601895,-0.0862995068295);
    glVertex2f(-0.148956164676,-0.0838578570457);
    glVertex2f(-0.1499550214057,-0.0817491595052);//V8
    glVertex2f(-0.1529515915949,-0.0778647166674);
    glVertex2f(-0.1547273368922,-0.0763109395323);
    glVertex2f(-0.1567250503516,-0.0749791305593);
    glVertex2f(-0.1591520205508,-0.0740692385338);
    glVertex2f(-0.1651079578148,-0.0740155814413);
    glVertex2f(-0.2339659230556,-0.0734101740081);
    glVertex2f(-0.2384490564141,-0.0744053359182);
    glVertex2f(-0.2418516854805,-0.0762734459939);
    glVertex2f(-0.2445102989495,-0.0785697122921);
    glVertex2f(-0.2467888335377,-0.0804766936641);
    glVertex2f(-0.2483900707454,-0.0826783948247);
    glVertex2f(-0.25,-0.085);
    glVertex2f(-0.2509253629909,-0.0878824157498);
    glVertex2f(-0.2511619744064,-0.0924075789888);
    glVertex2f(-0.2512384462032,-0.0980776055644);
    glVertex2f(-0.2522222066944,-0.1650899929136);


    glEnd();


}

///90
void window3SideBox()
 {
    glLineWidth(2.0);
    glBegin(GL_LINES); // Start drawing lines
    glColor3ub(0, 0, 0); // Black color

    glVertex2f(-0.1379426122684, -0.2122509017437);
    glVertex2f(-0.1364242478858, -0.2159624591233);

    glVertex2f(-0.1364242478858, -0.2159624591233);
    glVertex2f(-0.1340623477352, -0.2183243592739);

    glVertex2f(-0.1340623477352, -0.2183243592739);
    glVertex2f(-0.131531740431, -0.2211923808853);

    glVertex2f(-0.131531740431, -0.2211923808853);
    glVertex2f(-0.1278201830514, -0.2225420381143);

    glVertex2f(-0.1278201830514, -0.2225420381143);
    glVertex2f(-0.12495216144, -0.2225420381143);

    glVertex2f(-0.12495216144, -0.2225420381143);
    glVertex2f(-0.0945848737892, -0.2225420381143);

    glVertex2f(-0.0945848737892, -0.2225420381143);
    glVertex2f(-0.0907682937584, -0.2214643841633);

    glVertex2f(-0.0907682937584, -0.2214643841633);
    glVertex2f(-0.0886198919639, -0.2199873579296);

    glVertex2f(-0.0886198919639, -0.2199873579296);
    glVertex2f(-0.0864714901693, -0.2182417814715);

    glVertex2f(-0.0864714901693, -0.2182417814715);
    glVertex2f(-0.0847259137112, -0.2158248294526);

    glVertex2f(-0.0847259137112, -0.2158248294526);
    glVertex2f(-0.0835174377018, -0.213676427658);

    glVertex2f(-0.0835174377018, -0.213676427658);
    glVertex2f(-0.0827117870288, -0.211125200527);

    glVertex2f(-0.0827117870288, -0.211125200527);
    glVertex2f(-0.0825775119167, -0.2083054231716);

    glVertex2f(-0.0825775119167, -0.2083054231716);
    glVertex2f(-0.0824432368045, -0.2060227462649);

    glVertex2f(-0.0824432368045, -0.2060227462649);
    glVertex2f(-0.0826710268943, -0.1600299982096);

    glVertex2f(-0.0826710268943, -0.1600299982096);
    glVertex2f(-0.0839351852847, -0.1562375230384);

    glVertex2f(-0.0839351852847, -0.1562375230384);
    glVertex2f(-0.0856207298052, -0.1526557409322);

    glVertex2f(-0.0856207298052, -0.1526557409322);
    glVertex2f(-0.0885704327162, -0.1505488102815);

    glVertex2f(-0.0885704327162, -0.1505488102815);
    glVertex2f(-0.0932056801477, -0.148863265761);

    glVertex2f(-0.0932056801477, -0.148863265761);
    glVertex2f(-0.0984730067744, -0.1482311865658);

    glVertex2f(-0.0984730067744, -0.1482311865658);
    glVertex2f(-0.1264951844283, -0.148863265761);

    glVertex2f(-0.1264951844283, -0.148863265761);
    glVertex2f(-0.1284444164829, -0.1492348780808);

    glVertex2f(-0.1284444164829, -0.1492348780808);
    glVertex2f(-0.13, -0.15);

    glVertex2f(-0.13, -0.15);
    glVertex2f(-0.1316945901489, -0.1510921201756);

    glVertex2f(-0.1316945901489, -0.1510921201756);
    glVertex2f(-0.1330453116724, -0.1523584216039);

    glVertex2f(-0.1330453116724, -0.1523584216039);
    glVertex2f(-0.1344804532912, -0.1536669330799);

    glVertex2f(-0.1344804532912, -0.1536669330799);
    glVertex2f(-0.1356623346243, -0.1553131249367);

    glVertex2f(-0.1356623346243, -0.1553131249367);
    glVertex2f(-0.1371601696779, -0.1571815942292);

    glVertex2f(-0.1371601696779, -0.1571815942292);
    glVertex2f(-0.137860213612, -0.1584941766056);

    glVertex2f(-0.137860213612, -0.1584941766056);
    glVertex2f(-0.1381227300873, -0.1617318798009);

    glVertex2f(-0.1381227300873, -0.1617318798009);
    glVertex2f(-0.1379426122684, -0.2122509017437);


    glEnd();
}

///91
void Wing()
{
    if (startScene6 == true)
    {
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glTranslatef(wingRotate, 0.0,  0.0);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture12);

        glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(-10.0f, -6.0f);   // Bottom-left
        glTexCoord2f(1.0f, 1.0f); glVertex2f(10.0f, -6.0f);    // Bottom-right
        glTexCoord2f(1.0f, 0.0f); glVertex2f(10.0f, 5.25f);    // Top-right
        glTexCoord2f(0.0f, 0.0f); glVertex2f(-10.0f, 5.25f);   // Top-left
        glEnd();

        glDisable(GL_TEXTURE_2D);

        glPopMatrix();
    }

/*

    glBegin(GL_POLYGON);
    glColor3ub(0,0,0); // Black color
    glVertex2f(-0.2634586340603,0.0074394028764);//I
    glVertex2f(-0.2133800036638,0.0074394028764);//J
    glVertex2f(-0.2123631108685,0.021246753463);
    glVertex2f(-0.2127102805387,0.0233297714839);
    glVertex2f(-0.2143304056661,0.0251813430581);
    glVertex2f(-0.2165291469104,0.0273800843024);
    glVertex2f(-0.2186121649313,0.0291159326531);
    glVertex2f(-0.2215052455159,0.0298102719934);//P
    glVertex2f(-0.2556398846729,0.0292346252696);
    glVertex2f(-0.2575861134009,0.028052986399);//J3
    glVertex2f(-0.2598798829731,0.0259677413333);
    glVertex2f(-0.2616612040302,0.0240241108242);
    glVertex2f(-0.2616612040302,0.0240241108242);

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0,0,0); // Black color
    glVertex2f(-0.2454697437299,0.028708577832);//L3
    glVertex2f(-0.2305931905049,0.028708577832);//M3
    glVertex2f(-0.2305931905049,0.0543293083861);//N3
    glVertex2f(-0.2442300309612,0.0551557835653);//O3

    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(0,0,0); // Black color
    glVertex2f(-0.2624059924975,0.0528696062464);
    glVertex2f(-0.2136164498782,0.051919160611);//Q3
    glVertex2f(-0.2123255846478,0.0586308012121);
    glVertex2f(-0.212646361992,0.0613574086386);
    glVertex2f(-0.2142502487135,0.0636028500486);
    glVertex2f(-0.2157739410989,0.0654473197783);
    glVertex2f(-0.2174580221564,0.0669710121636);
    glVertex2f(-0.2190619088778,0.0680135385326);
    glVertex2f(-0.2208261842714,0.0688956762294);
    glVertex2f(-0.2551493601103,0.0687352875572);
    glVertex2f(-0.2572344128482,0.0671314008358);
    glVertex2f(-0.26,0.065);
    glVertex2f(-0.2620460730125,0.0620791576632);
    glVertex2f(-0.2628480163732,0.0595129389089);
    glVertex2f(-0.2629644702724,0.0572423553835);

    glEnd();

    glLineWidth(4.0);
    glBegin(GL_LINES); // Start drawing lines
    glColor3ub(0, 0, 0); // Black color

    glVertex2f(-0.2383120464628,0.04098215909);
    glVertex2f(-0.4661712505961,0.0240576101585);

    glVertex2f(-0.2383120464628,0.04098215909);
    glVertex2f(-0.014655303046,0.0593373040241);

    glVertex2f(-0.2383120464628,0.04098215909);
    glVertex2f(-0.043680719624,0.0212550885032);


    glVertex2f(-0.2383120464628,0.04098215909);
    glVertex2f(-0.4886331357923,0.0576130680344);

    glEnd();
*/
}

///92
void Helicoptor()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(4.0, 4.0, 1.0);
    glTranslatef(_Heli, 1.0,  0.0);

    Backside();
    BottomWhite();
    MiddleRed();
    upperBodyWhite();
    Glass1();
    Glass2();
    BellowRedLine();
    BellowBlackLine();
    door();
    doorWindow();
    window3();
    window3SideBox();

    glPopMatrix();
}

///93
void TruckBody()
{
    glBegin(GL_POLYGON);
    glColor3ub(102, 0, 0); // Red color
    glVertex2f(0.0136743860191f, 0.0096327096498f);
    glVertex2f(0.5734076485232f, 0.0131155231276f);
    glVertex2f(0.5739974979592f, 0.2059962887177f);
    glVertex2f(0.0136743860191f, 0.2060040750907f);
    glEnd();


    //
    glLineWidth(7.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0); // Black color
    glVertex2f(0.0067094928827, 0.2134134300429);
    glVertex2f(0.597294369415, 0.2134134300429);
    glEnd();
}

///94
void BackupperBound1()
{
    glBegin(GL_POLYGON);
    glColor3ub(128,128,128);
    glVertex2f(0.0519901701656f, 0.0187481642153f);
    glVertex2f(0.2194993128396f, 0.0186132981438f);
    glVertex2f(0.2193865776049f, 0.2014295517274f);
    glVertex2f(0.0515503575629f, 0.2022110151274f);
    glEnd();

    glLineWidth(7.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(0.2041792093922, 0.1571629009029);
    glVertex2f(0.2041792093922, 0.0688257526571);
    glEnd();

}

///95
void BackupperBound2()
{
    glBegin(GL_POLYGON);
    glColor3ub(128,128,128);
    glVertex2f(0.27115508684f, 0.0190358557157f);
    glVertex2f(0.4059924204673f, 0.0190358557157f);
    glVertex2f(0.4071649190206f, 0.1990143836443f);
    glVertex2f(0.2729138346699f, 0.199600632921f);
    glEnd();

     glLineWidth(7.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(0.2833679737197f, 0.065163725935f);
    glVertex2f(0.2837835604109f, 0.1579290079798f);
    glEnd();
}

///96
void BackupperBound3()
{
    glBegin(GL_POLYGON);
    glColor3ub(128,128,128);
    glVertex2f(0.42f, 0.02f);
    glVertex2f(0.5652494042635f, 0.0194009655166f);
    glVertex2f(0.5656882172497f, 0.2001919158307f);
    glVertex2f(0.42f, 0.2f);
    glEnd();

    glLineWidth(7.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0);
    glVertex2f(0.4311800697753f, 0.0687615315298f);
    glVertex2f(0.4314042991434f, 0.1593300835103f);
    glEnd();
}

///97
void FrontupperBound1()
{
    glBegin(GL_POLYGON);
    glColor3ub(102, 0, 0); // Red color
    glVertex2f(-0.5374414392664, 0.0677968590798);
    glVertex2f(0.0075501439836, 0.06763770165);
    glVertex2f(0.0081593536025, 0.2874984691512);
    glVertex2f(-0.4169060483249, 0.2871107785558);//R1
    glVertex2f(-0.4186199228038, 0.285086242693);//T1
    glVertex2f(-0.4200749869923, 0.2832674124574);
    glVertex2f(-0.4219847587396, 0.2813576407101);
    glVertex2f(-0.4236217059516, 0.279720693498);
    glVertex2f(-0.4248948871166, 0.2779928047742);
    glVertex2f(-0.4266227758404, 0.2759920915151);//A2
    glVertex2f(-0.4282597230524, 0.2743551443031);//B2
    glVertex2f(-0.4293510211938, 0.2729000801146);
    glVertex2f(-0.4315990298711, 0.270414208617);
    glVertex2f(-0.4328762219464, 0.2651411595113);
    glVertex2f(-0.4392118264448, 0.2522939615006);
    glVertex2f(-0.4464273760125, 0.2394467634899);
    glVertex2f(-0.4578666619124, 0.2172721477454);
    glVertex2f(-0.4670082788327, 0.2003869351507);
    glVertex2f(-0.4809653317199, 0.1750104753558);
    glVertex2f(-0.5054959095217, 0.1297557887215);
    glVertex2f(-0.5224135493849, 0.0963434499915);
    glVertex2f(-0.5374414392664, 0.0677968590798);
    glVertex2f(0.0075501439836, 0.06763770165);
    glEnd();
}

///98
void FrontGlass2()
{

    glBegin(GL_POLYGON);
    glColor3ub(0,191,255); // Sky clor
    glVertex2f(-0.4937149147998, 0.1232110662562);
    glVertex2f(-0.3449865316807, 0.1235261687628);
    glVertex2f(-0.3449145740085, 0.2709763638827);
    glVertex2f(-0.4, 0.27);
    glVertex2f(-0.4072332258268, 0.2673195236782);
    glVertex2f(-0.4121090127661, 0.264424525183);
    glVertex2f(-0.4168620928117, 0.2610307745151);
    glVertex2f(-0.4204892715681, 0.2572632131158);
    glVertex2f(-0.4247882220869, 0.2532508592983);
    glVertex2f(-0.4266679344106, 0.2492459379457);
    glVertex2f(-0.428870147457, 0.2445662352221);
    glVertex2f(-0.4324487436574, 0.2390607026062);
    glVertex2f(-0.4349262333345, 0.2341057232518);//Z2
    glVertex2f(-0.4375330568288, 0.2288655503694);
    glVertex2f(-0.4396839330514, 0.2240260788684);
    glVertex2f(-0.4425517680149, 0.2193658470527);
    glVertex2f(-0.4457780823489, 0.2143471358665);
    glVertex2f(-0.4481081982568, 0.2096869040508);//E3
    glEnd();

}

///99
void FrontGlass3()
{

    glBegin(GL_POLYGON);
    glColor3ub(0,191,255); // Sky clor
    glVertex2f(-0.2965007029909, 0.1203599051211);
    glVertex2f(-0.1872216911655, 0.1216919365185);
    glVertex2f(-0.1853797103053, 0.2756383573539);
    glVertex2f(-0.281208250102, 0.2768737160621);//Z3
    glVertex2f(-0.2898557610597, 0.2763442766157);
    glVertex2f(-0.2977973527556, 0.2761677968002);
    glVertex2f(-0.3048565453742, 0.2758148371693);//U3
    glVertex2f(-0.310503899469, 0.2735205995683);
    glVertex2f(-0.3166806930102, 0.269991003259);
    glVertex2f(-0.3227952408047, 0.2625436107163);//R3
    glVertex2f(-0.3228591480222, 0.1741206939969);
    glVertex2f(-0.3223371986157, 0.1647256046788);
    glVertex2f(-0.3223371986157, 0.1568963635804);//O3
    glVertex2f(-0.3228591480222, 0.1485451730754);
    glVertex2f(-0.3228591480222, 0.1396720331638);
    glVertex2f(-0.3212932998025, 0.1339305896917);
    glVertex2f(-0.3186835527697, 0.1300159691425);
    glVertex2f(-0.3150299069238, 0.1261013485933);
    glVertex2f(-0.3103323622648, 0.1234916015605);//I3
    glVertex2f(-0.3043299440893, 0.1208818545277);
    glVertex2f(-0.2965007029909, 0.1203599051211);//G3
    glEnd();

}

///100
void FrontGlass4()
{

    glBegin(GL_POLYGON);
    glColor3ub(0,191,255); // Sky clor
    glVertex2f(-0.1637585968466, 0.1212733124494);
    glVertex2f(-0.048620160283, 0.1212733124494);
    glVertex2f(-0.0404212449395, 0.1228374781828);
    glVertex2f(-0.0339726593926, 0.127136535214);
    glVertex2f(-0.0288137909551, 0.1322954036515);
    glVertex2f(-0.0275240738458, 0.1396038006047);
    glVertex2f(-0.0277390266973, 0.1469121975578);//H4
    glVertex2f(-0.0281689324004, 0.1537906888078);
    glVertex2f(-0.0276106104054, 0.2607902005809);
    glVertex2f(-0.0285575468528, 0.2637415824288);
    glVertex2f(-0.03, 0.265);
    glVertex2f(-0.032473536601, 0.2673638729459);
    glVertex2f(-0.0349210301936, 0.2693218678199);
    glVertex2f(-0.0375643232736, 0.2715735619251);
    glVertex2f(-0.0403055160973, 0.2730420580807);
    glVertex2f(-0.043046708921, 0.2744126544925);//Q4
    glVertex2f(-0.0464731999506, 0.275587451417);
    glVertex2f(-0.0498996909802, 0.2757832509044);//S4
    glVertex2f(-0.1644631467023, 0.2752863166061);
    glEnd();
}

///101
void FrontGlass5()
{
    glLineWidth(7.0f);
    glBegin(GL_LINES);
    glColor3ub(0,191,255); // Sky clor
    glVertex2f(-0.4352249253715, 0.2721617024978);//H5
    glVertex2f(-0.4447663230871, 0.2548137066513);
    glVertex2f(-0.4447663230871, 0.2548137066513);
    glVertex2f(-0.4570015726261, 0.2333280880815);//F5
    glVertex2f(-0.4570015726261, 0.2333280880815);//F5
    glVertex2f(-0.4765008909631, 0.1973626787044);
    glVertex2f(-0.4765008909631, 0.1973626787044);
    glVertex2f(-0.4848228265266, 0.1803215888871);
    glVertex2f(-0.4848228265266, 0.1803215888871);
    glVertex2f(-0.4937111503202, 0.1636115401551);//C5
    glVertex2f(-0.4937111503202, 0.1636115401551);//C5
    glVertex2f(-0.506510336583, 0.1417462636228);
    glVertex2f(-0.506510336583, 0.1417462636228);
    glVertex2f(-0.5150438082973, 0.1244295150791);
    glVertex2f(-0.5150438082973, 0.1244295150791);
    glVertex2f(-0.5270209154235, 0.1019574057892);
    glVertex2f(-0.5270209154235, 0.1019574057892);
    glVertex2f(-0.5365637250543, 0.0858333481372);
    glVertex2f(-0.5365637250543, 0.0858333481372);
    glVertex2f(-0.5450739847681, 0.0709743940757);
    glVertex2f(-0.5450739847681, 0.0709743940757);
    glVertex2f(-0.5531843241949, 0.0481090997882);
    glEnd();
}

///102
void UpperlayerAsh()
{

    glBegin(GL_POLYGON);
    glColor3ub(128,128,128); // ash color
    glVertex2f(-0.4186245406239, 0.2896805643901);
    glVertex2f(-0.4141346597168, 0.2896805643901);
    glVertex2f(-0.4074772500958, 0.2896031526504);
    glVertex2f(-0.3797638472549, 0.2892160939515);//M5
    glVertex2f(0.0071980725259, 0.289635212882);
    glVertex2f(0.0072249047715, 0.3169147233311);
    glVertex2f(-0.3567583079887, 0.3140401699589);
    glVertex2f(-0.3626714871415, 0.3135739032894);
    glVertex2f(-0.3699332486312, 0.312601345947);
    glVertex2f(-0.3774543587454, 0.3113046028238);//T5
    glVertex2f(-0.3900976041961, 0.3069605133613);
    glVertex2f(-0.3972051518381, 0.3042736484646);//Q5
    glVertex2f(-0.406, 0.3);
    glVertex2f(-0.4344437404635, 0.2789581077445);
    glVertex2f(-0.4191033050785, 0.2900888522577);
    glEnd();

}

///103
void upperdesign1()
{
    glBegin(GL_POLYGON);
    glColor3ub(128,128,128); // ash color
    glVertex2f(-0.274579760998, 0.3100638729729);
    glVertex2f(-0.2398024791309, 0.3100638729729);//H6
    glVertex2f(-0.2400980303974, 0.4176534642361);
    glVertex2f(-0.251889202287, 0.4187692627347);
    glVertex2f(-0.2587966503828, 0.4153103228259);
    glVertex2f(-0.2643860159128, 0.4106807401927);//D6
    glVertex2f(-0.2679898904224, 0.4057634966309);
    glVertex2f(-0.2713489588985, 0.3997525319896);
    glVertex2f(-0.273824061986, 0.3917968434938);
    glEnd();

}

///104
void upperDesignMiddle()
{

    glLineWidth(4.0f);
    glBegin(GL_LINES);
    glColor3ub(128,128,128); // ash color
    glVertex2f(-0.2415497259132, 0.4127657291871);
    glVertex2f(0.5552237238116, 0.4123631402844);
    glEnd();

    //
    glLineWidth(4.0f);
    glBegin(GL_LINES);
    glColor3ub(128,128,128); // ash color
    glVertex2f(-0.2428477328647, 0.3252476466698);
    glVertex2f(0.5488105584274, 0.3257854075977);
    glEnd();

    //

    glLineWidth(4.0f);
    glBegin(GL_LINES);
    glColor3ub(128,128,128); // ash color
    glVertex2f(-0.2343858367782, 0.4111537950351);//M6
    glVertex2f(-0.1783708111319, 0.3256690169402);
    glEnd();

    //

    glLineWidth(4.0f);
    glBegin(GL_LINES);
    glColor3ub(128,128,128); // ash color
    glVertex2f(-0.1783708111319, 0.3256690169402);
    glVertex2f(-0.1237055451397, 0.4131784345163);//O6
    glEnd();

    //
    glLineWidth(4.0f);
    glBegin(GL_LINES);
    glColor3ub(128,128,128); // ash color
    glVertex2f(-0.1237055451397, 0.4131784345163);//O6
    glVertex2f(-0.0649428541394, 0.3247190940539);
    glEnd();

    //
    glLineWidth(4.0f);
    glBegin(GL_LINES);
    glColor3ub(128,128,128); // ash color
    glVertex2f(-0.0649428541394, 0.3247190940539);
    glVertex2f(-0.0124353223187, 0.413210808521);//Q6
    glEnd();

    //
    glLineWidth(4.0f);
    glBegin(GL_LINES);
    glColor3ub(128,128,128); // ash color
    glVertex2f(-0.0124353223187, 0.413210808521);//Q6
    glVertex2f(0.0446191692143, 0.326261902081);//R6
    glEnd();


     //
    glLineWidth(4.0f);
    glBegin(GL_LINES);
    glColor3ub(128,128,128); // ash color
    glVertex2f(0.0446191692143, 0.326261902081);//R6
    glVertex2f(0.0991792964965, 0.4122541542145);
    glEnd();

     //
    glLineWidth(4.0f);
    glBegin(GL_LINES);
    glColor3ub(128,128,128); // ash color
    glVertex2f(0.0991792964965, 0.4122541542145);
    glVertex2f(0.1566570569363, 0.3260375135548);
    glEnd();


     //
    glLineWidth(4.0f);
    glBegin(GL_LINES);
    glColor3ub(128,128,128); // ash color
    glVertex2f(0.1566570569363, 0.3260375135548);
    glVertex2f(0.2085363342163, 0.4122541542145);


    //
    glLineWidth(4.0f);
    glBegin(GL_LINES);
    glColor3ub(128,128,128); // ash color
    glVertex2f(0.2085363342163, 0.4122541542145);
    glVertex2f(0.2648943980242, 0.3264107457655);
    glEnd();

     //
    glLineWidth(4.0f);
    glBegin(GL_LINES);
    glColor3ub(128,128,128); // ash color
    glVertex2f(0.2648943980242, 0.3264107457655);
    glVertex2f(0.3173920006465, 0.4126091178894);
    glEnd();

     //
    glLineWidth(4.0f);
    glBegin(GL_LINES);
    glColor3ub(128,128,128); // ash color
    glVertex2f(0.3173920006465, 0.4126091178894);
    glVertex2f(0.3767349620098, 0.3261406012086);
    glEnd();


    //
    glLineWidth(4.0f);
    glBegin(GL_LINES);
    glColor3ub(128,128,128); // ash color
    glVertex2f(0.3767349620098, 0.3261406012086);
    glVertex2f(0.4305572548989, 0.4112145480334);
    glEnd();

    //
    glLineWidth(4.0f);
    glBegin(GL_LINES);
    glColor3ub(128,128,128); // ash color
    glVertex2f(0.4305572548989, 0.4112145480334);
    glVertex2f(0.4883873940776, 0.3268021663996);
    glEnd();

    //
    glLineWidth(4.0f);
    glBegin(GL_LINES);
    glColor3ub(128,128,128); // ash color
    glVertex2f(0.4883873940776, 0.3268021663996);
    glVertex2f(0.5425913658034, 0.412533952389);
    glEnd();

}

///105
void upperDesignBack()
{

    glBegin(GL_POLYGON);
    glColor3ub(128,128,128); // ash color
    glVertex2f(0.5468253699401, 0.3192944132308);
    glVertex2f(0.5928183653868, 0.3198803112619);//E7
    glVertex2f(0.5927988083047, 0.4232216500681);
    glVertex2f(0.5456204548642, 0.4234534854156);
    glEnd();
}

///106
void upperBoxDesign1(){

    glLineWidth(6.0f);
    glBegin(GL_LINES);
    glColor3ub(102, 0, 0); //Dark Red color
    glVertex2f(0.3138888596611, 0.2329584473658);
    glVertex2f(0.5914735082906, 0.2336436801017);
    glEnd();

    //
    glLineWidth(5.0f);
    glBegin(GL_LINES);
    glColor3ub(255,0,0); // Red color
    glVertex2f(0.3138888596611,  0.2451318613255);
    glVertex2f(0.5914735082906,  0.2451318613255);
    glEnd();

    //
    glLineWidth(5.0f);
    glBegin(GL_LINES);
    glColor3ub(255,255,255); // White color
    glVertex2f(0.3138888596611,  0.2573237646273);
    glVertex2f(0.5914735082906,  0.2573237646273);
    glEnd();


    //
    glLineWidth(7.0f);
    glBegin(GL_LINES);
    glColor3ub(255,0,0); // Red color
    glVertex2f(0.3138888596611,  0.2755147003477);
    glVertex2f(0.5914735082906,  0.2755147003477);
    glEnd();

    //
    glLineWidth(8.0f);
    glBegin(GL_LINES);
    glColor3ub(102, 0, 0); // Dark Red color
    glVertex2f(0.3138888596611, 0.3009062147907);
    glVertex2f(0.5914735082906, 0.3009062147907);
    glEnd();

    //
    glLineWidth(5.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0); // Black color
    glVertex2f(0.3138888596611, 0.3156863500636);
    glVertex2f(0.5914735082906, 0.3156863500636);
    glEnd();
}

///107
void upperBoxDesign2()
{
    glBegin(GL_POLYGON);
    glColor3ub(128,128,128); // gray color
    glVertex2f(0.0417302881795, 0.2264112098856);
    glVertex2f(0.2743473447335, 0.2264112098856);
    glVertex2f(0.2743473447335, 0.2869848347818);
    glVertex2f(0.0417302881795, 0.2869848347818);

    glEnd();
}

///108
void circle(float radius, float xc, float yc, float r, float g, float b)
{
    glBegin(GL_POLYGON);// Draw a Red 1x1 Square centered at origin
	for(int i=0;i<200;i++)
        {
            glColor3f(r,g,b);
            float pi=3.1416;
            float A=(i*2*pi)/200;
            float r=radius;
            float x = r * cos(A);
            float y = r * sin(A);
            glVertex2f(x+xc,y+yc);
        }
	glEnd();
}

///109
void lowerWhiteDesign()
{
    glBegin(GL_POLYGON);
    glColor3ub(255,255,240); // ivory color
    glVertex2f(-0.5591192996235, -0.0348193430308);
    glVertex2f(-0.3744889819183, -0.0348193430308);
    glVertex2f(0.0090136486314, -0.0348193430308);
    glVertex2f(0.0090136486314, 0.06763770165);
    glVertex2f(-0.5374414392664, 0.06763770165);//P1
    glVertex2f(-0.54, 0.06);
    glVertex2f(-0.5461504887582, 0.0512867429972);
    glVertex2f(-0.5522878780199, 0.0443310351674);
    glVertex2f(-0.5597744534104, 0.0336405087906);
    glEnd();
}

///110
void lowerRedDesign()
{
    glBegin(GL_POLYGON);
    glColor3ub(128,0,0); // Red color
    glVertex2f(-0.5401697841164, -0.1336641293976);
    glVertex2f(-0.4256525059607, -0.1336641293976);
    glVertex2f(-0.4077873521746, -0.1323547166561);//A2
    glVertex2f(-0.3744889819183, -0.0348193430308);
    glVertex2f(-0.5401697841164, -0.0350520287636);
    glEnd();

    //White
    glLineWidth(5.0f);
    glBegin(GL_LINES);
    glColor3ub(255, 255, 255); // White color
    glVertex2f(-0.5519193231743, -0.0679943948033);
    glVertex2f(-0.3898790833319, -0.0679943948033);
    glEnd();

}

///111
void WheelUpperDesign()
{
    glBegin(GL_POLYGON);
    glColor3ub(102, 0, 0); // Dark Red color
    glVertex2f(-0.2003093420464, -0.1115921446448);
    glVertex2f(0.1158090036224, -0.1115921446448);
    glVertex2f(0.1591013071179, 0.004139230127);
    glVertex2f(-0.2329807911797, 0.004139230127);//M8

    glEnd();

    //

    glBegin(GL_POLYGON);
    glColor3ub(128,128,128); // ash color
    glVertex2f(-0.1951296044127, -0.1014933678724);
    glVertex2f(0.1, -0.1014933678724);
    glVertex2f(0.1109968688513, -0.0623385437169);
    glVertex2f(-0.2072215030194, -0.0622244638274);
    glEnd();


    //

    glBegin(GL_POLYGON);
    glColor3ub(255,0,0); // Red color
    glVertex2f(-0.2113559172343, -0.0498909479201);
    glVertex2f(0.1130994368569, -0.0505908016789);
    glVertex2f(0.1262410556261, -0.0067289350693);
    glVertex2f(-0.2247254440997, -0.0030403441575);
    glEnd();
}

///112
void wheelBackBlackDesign()
{
    glBegin(GL_POLYGON);
    glColor3ub(128,128,128); // Black color
    glVertex2f(0.1202684284426, -0.1072670014207);
    glVertex2f(0.4893732402968, -0.1072144495576);//A
    glVertex2f(0.4899178310551, -0.0157232021629);
    glVertex2f(0.151155649192, -0.0140915583668);
    glEnd();

}

///113
void BackLight1()
{
    glBegin(GL_POLYGON);
    glColor3ub(102,0,0); // Dark Red color
    glVertex2f(0.5198082563785, -0.1158011316014);
    glVertex2f(0.5607417301884, -0.1162884348611);
    glVertex2f(0.560597439814, -0.012511593835);
    glVertex2f(0.4766190229729, -0.0130809390339);
    glEnd();

    //
    glBegin(GL_POLYGON);
    glColor3ub(255,0,0); // Red color
    glVertex2f(0.5256333323969, -0.1077672439751);
    glVertex2f(0.5545326974509, -0.1065107498423);
    glVertex2f(0.5552865939305, -0.0198126546804);
    glVertex2f(0.4891950025462, -0.0198126546804);
    glEnd();

    //
    glLineWidth(5.0f);
    glBegin(GL_LINES);
    glColor3ub(0,0,0); // Black color
    glVertex2f(0.5607242817765, -0.0721191371693);
    glVertex2f(0.5741354888962, -0.0721191371693);
    glEnd();

    //
    glBegin(GL_POLYGON);
    glColor3ub(169,169,169); // Dark Gray color
    glVertex2f(0.5679457009948, -0.0850145286306);
    glVertex2f(0.5741354888962,-0.0850145286306);
    glVertex2f(0.5741354888962, -0.0721191371693);
    glVertex2f(0.5679457009948, -0.0721191371693);
    glEnd();

    //
    glBegin(GL_POLYGON);
    glColor3ub(240,128,128); // Light Coral color
    glVertex2f(0.5741354888962, -0.0721191371693);
    glVertex2f(0.5679457009948, -0.0721191371693);
    glVertex2f(0.5741354888962, -0.0603843309395);
    glVertex2f(0.5679457009948, -0.0607711926834);
    glEnd();

    //
    glBegin(GL_POLYGON);
    glColor3ub(255,0,0); //  Red color
    glVertex2f(0.5786488759077, -0.0852724364598);
    glVertex2f(0.5836780785776, -0.0846276668868);
    glVertex2f(0.588191465589, -0.0824354503383);
    glVertex2f(0.5924469447713, -0.0790826485584);//F10
    glVertex2f(0.5950260230635, -0.0756008928639);
    glVertex2f(0.5952839308928, -0.0721191371693);
    glVertex2f(0.5741354888962, -0.0721191371693);
    glEnd();

    //

    glBegin(GL_POLYGON);
    glColor3ub(255,99,71); //  Tomato color
    glVertex2f(0.5741354888962, -0.0721191371693);
    glVertex2f(0.5952839308928, -0.0721191371693);
    glVertex2f(0.5936075300028, -0.0679926119017);
    glVertex2f(0.5910284517105, -0.0651556257802);//U
    glVertex2f(0.5878046038452, -0.0628344553172);
    glVertex2f(0.5841294848133, -0.0608079281962);
    glVertex2f(0.58, -0.06);
    glVertex2f(0.5742644428109, -0.0603843309395);
    glEnd();

}

///114
void BackLight2()
{

    //
    glLineWidth(5.0f);
    glBegin(GL_LINES);
    glColor3ub(0,0,0); // Black color
    glVertex2f(0.5607242817765, -0.0368014385987);
    glVertex2f(0.567558839251, -0.036509113445);
    glEnd();

    //
    glBegin(GL_POLYGON);
    glColor3ub(169,169,169); // Dark Gray color
    glVertex2f(0.5676877931656, -0.0494214137848);
    glVertex2f(0.5742644428109, -0.0494214137848);
    glVertex2f(0.5745900293496, -0.0363073587522);
    glVertex2f(0.567558839251, -0.036509113445);
    glEnd();

    //
    glBegin(GL_POLYGON);
    glColor3ub(240,128,128); // Light Coral color
    glVertex2f(0.5741354888962, -0.0721191371693);
    glVertex2f(0.5679457009948, -0.0721191371693);
    glVertex2f(0.5741354888962, -0.0603843309395);
    glVertex2f(0.5679457009948, -0.0607711926834);
    glEnd();

    //
    glBegin(GL_POLYGON);
    glColor3ub(255,0,0); //  Red color
    glVertex2f(0.5742644428109, -0.0494214137848);
    glVertex2f(0.5782093995994, -0.0495804137414);
    glVertex2f(0.5782093995994, -0.0495804137414);
    glVertex2f(0.5860907398667, -0.0475714446537);
    glVertex2f(0.5890269254564, -0.046026083817);
    glVertex2f(0.5921176471299, -0.04363077452);
    glVertex2f(0.5941266162176, -0.0414672693486);
    glVertex2f(0.5954401729288, -0.0382992796333);
    glVertex2f(0.595826513138, -0.0363073587522);
    glVertex2f(0.5745900293496, -0.0363073587522);
    glEnd();

    //
    glBegin(GL_POLYGON);
    glColor3ub(255,99,71); //  Tomato color
    glVertex2f(0.5745900293496, -0.0363073587522);
    glVertex2f(0.595826513138, -0.0363073587522);
    glVertex2f(0.594435688385, -0.0321178362865);
    glVertex2f(0.5918085749625, -0.0294134548222);
    glVertex2f(0.5891814615401, -0.0275590218181);
    glVertex2f(0.5867861522432, -0.0257045888141);
    glVertex2f(0.5837726986116, -0.0244683001447);
    glVertex2f(0.5789820800178, -0.024313764061);
    glVertex2f(0.5746550696749, -0.024313764061);
    glVertex2f(0.5745900293496, -0.0363073587522);
    glEnd();

}

///115
void LowerBodyBlackLine()
{

    glLineWidth(7.0f);
    glBegin(GL_LINES);
    glColor3ub(0, 0, 0); // Black color
    glVertex2f(-0.1024631531366, -0.0041396090496);
    glVertex2f(0.5967914596155, -0.0041396090496);
    glEnd();

    //
    glLineWidth(4.0f);
    glBegin(GL_LINES);
    glColor3ub(102,51,0); // wooden color
    glVertex2f(-0.1796434270923, -0.1247406618881);
    glVertex2f(-0.1796434270923, 0.0068767270173);
    glEnd();

    //
    glLineWidth(4.0f);
    glBegin(GL_LINES);
    glColor3ub(102,51,0); // wooden color
    glVertex2f(-0.1044334905749, -0.1247406618881);
    glVertex2f(-0.1044334905749, 0.0068767270173);
    glEnd();

    //
    glLineWidth(4.0f);
    glBegin(GL_LINES);
    glColor3ub(102,51,0); // wooden color
    glVertex2f(-0.1796434270923, -0.1087356824143);
    glVertex2f(-0.1044334905749, -0.1087356824143);
    glEnd();

    //
    glLineWidth(4.0f);
    glBegin(GL_LINES);
    glColor3ub(102,51,0); // wooden color
    glVertex2f(-0.1796434270923, -0.06);
    glVertex2f(-0.1044334905749, -0.06);
    glEnd();

    //
    glLineWidth(4.0f);
    glBegin(GL_LINES);
    glColor3ub(102,51,0); // wooden color
    glVertex2f(-0.1796434270923, -0.0157576926567);
    glVertex2f(-0.1044334905749, -0.0157576926567);
    glEnd();

}

///1156
void FrontBackSideBlackDesign()
{
    glBegin(GL_POLYGON);
    glColor3ub(128,128,128); //  Gray color
    glVertex2f(-0.4073825550889, -0.1229606099492);
    glVertex2f(-0.3947956176157, -0.1224361542212);
    glVertex2f(-0.2266211079192, -0.1227235284027);
    glVertex2f(-0.1961207708939, -0.1227235284027);
    glVertex2f(-0.1966087762863, -0.1119874097698);//K12
    glVertex2f(-0.2003093420464, -0.1115921446448);
    glVertex2f(-0.2027737615497, -0.101432054994);
    glVertex2f(-0.2123889225083, -0.0738407235476);
    glVertex2f(-0.2190777301316, -0.0479215940072);
    glVertex2f(-0.2316192444254, -0.0102970511258);//G12
    glVertex2f(-0.2692437873067, -0.00862484922);
    glVertex2f(-0.3005975730412, -0.0077887482671);
    glVertex2f(-0.3265167025817, -0.0098790006494);
    glVertex2f(-0.359542690222, -0.0228385654196);//C12
    glVertex2f(-0.3744889819183, -0.0348193430308);//H9
    glVertex2f(-0.3858798702389, -0.0508479473424);
    glVertex2f(-0.4, -0.08);
    glVertex2f(-0.4047602764487, -0.099884557915);
    glVertex2f(-0.4073825550889, -0.1229606099492);
    glEnd();

}

///117
void FrontSideBelowGrayDesign()
{
    glBegin(GL_POLYGON);
    glColor3ub(0,0,0); //  Black color
    glVertex2f(-0.5671050828212, -0.1381900563336);//Q13
    glVertex2f(-0.5665476572647, -0.1446956686158);
    glVertex2f(-0.561648064049, -0.1502485409269);//P12
    glVertex2f(-0.5547886335471, -0.1538415759517);
    glVertex2f(-0.4332787217988, -0.1531882968563);
    glVertex2f(-0.4289002714425, -0.1515114581819);
    glVertex2f(-0.4270555941803, -0.1478221036575);//A14
    glVertex2f(-0.4267748893633, -0.1282386703026);
    glVertex2f(-0.4265559699359, -0.1229846040442);//S13
    glVertex2f(-0.4265559699359, -0.1189345946367);
    glVertex2f(-0.4277600267867, -0.1168548600761);//U13
    glVertex2f(-0.4296208419199, -0.1148845852292);
    glVertex2f(-0.4309343584845, -0.1137899880921);//W13
    glVertex2f(-0.4431074106331, -0.1130488407818);//K13
    glVertex2f(-0.4976530177083, -0.1128751286573);//J13
    glVertex2f(-0.5028643814416, -0.1128751286573);
    glVertex2f(-0.5080757451749, -0.1118328559107);
    glVertex2f(-0.5136345331571, -0.1095745982929);
    glVertex2f(-0.5195407453882, -0.106100355804);//F13
    glVertex2f(-0.5231887000015, -0.1031472496885);
    glVertex2f(-0.527705215237, -0.0991518708263);
    glVertex2f(-0.5296445461123, -0.0944643673218);
    glVertex2f(-0.5299650133531, -0.0912596949133);
    glVertex2f(-0.5307127702484, -0.075770444939);//A13
    glVertex2f(-0.5311400599029, -0.0740612863212);
    glVertex2f(-0.5324219288663, -0.0719248380488);
    glVertex2f(-0.5347720219658, -0.0701088570174);
    glVertex2f(-0.5534420769196, -0.070488478326);
    glVertex2f(-0.5570497688227, -0.070488478326);
    glVertex2f(-0.56, -0.070488478326);
    glVertex2f(-0.5617656347659, -0.0715553964392);
    glVertex2f(-0.5636869134835, -0.073534895724);
    glVertex2f(-0.5653170893651, -0.0763294829496);
    glVertex2f(-0.5665476572647, -0.0793677590737);
    glVertex2f(-0.5671050828212, -0.1381900563336);
    glEnd();


}

///118
void FrontLightDesign()
{
    glBegin(GL_POLYGON);
    glColor3ub(178,34,34); //  FireBrick color
    glVertex2f(-0.56, -0.070488478326);
    glVertex2f(-0.5559642766837, -0.0683631203201);
    glVertex2f(-0.5514480258141, -0.0647976591073);
    glVertex2f(-0.5467733100018, -0.0603606407092);//J14
    glVertex2f(-0.5444359520956, -0.0571913418533);
    glVertex2f(-0.5432353278123, -0.0543638888892);
    glVertex2f(-0.543046279853, -0.0474951463657);
    glVertex2f(-0.5446803547726, -0.018876973385);
    glVertex2f(-0.5461507675462, -0.0157099304881);
    glVertex2f(-0.5489784844185, -0.0120904528916);
    glVertex2f(-0.5513537665912, -0.0094889533691);
    glVertex2f(-0.5544077008132, -0.0072267798713);
    glVertex2f(-0.5598369172079, -0.0055301497479);
    glVertex2f(-0.56, -0.070488478326);
    glEnd();
}

///119
void FireTruck()
{
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glScalef(4.0, 4.0, 1.0);
    glTranslatef(_Truck, -1.2, 0.0);

    TruckBody();  // Draw the truck body
    BackupperBound1();
    BackupperBound2();
    BackupperBound3();
    FrontupperBound1();
    FrontGlass2();
    FrontGlass3();
    FrontGlass4();
    FrontGlass5();
    UpperlayerAsh();
    upperdesign1();
    upperDesignMiddle();
    upperDesignBack();
    upperBoxDesign1();
    upperBoxDesign2();
    lowerWhiteDesign();
    lowerRedDesign();
    WheelUpperDesign();
    wheelBackBlackDesign();
    FrontBackSideBlackDesign();
    FrontSideBelowGrayDesign();
    FrontLightDesign();
    BackLight1();
    BackLight2();
    LowerBodyBlackLine();

    circle(0.015f,0.2126232097693f,0.2504617666668f,255,255,0);
    circle(0.015f,0.2528667602906f,0.2504617666668f,102,0,0);
    //front wheel
    circle(0.09f,-0.3102987257207f, -0.1074780855247f, 0, 0, 0);
    circle(0.06f,-0.3102987257207f, -0.1074780855247f, 64, 64, 64);
    //Back Wheel
    circle(0.09f,0.2219629990287f, -0.108439802228f, 0, 0, 0);
    circle(0.06f,0.2219629990287f, -0.108439802228f, 64, 64, 64);
    circle(0.09f,0.4110674500248f, -0.108439802228f, 0, 0, 0);
    circle(0.06f,0.4110674500248f, -0.108439802228f, 64, 64, 64);

    glPopMatrix();
}

///120
void timer1(int value) {
    fireTime += 0.02f; // Increment animation time
    glutPostRedisplay();   // Request a redraw
    glutTimerFunc(16, timer1, 0); // Call timer again after ~16ms (~60 FPS)
}

///121
void timer2(int value) {
    ringTime += 0.02f; // Increment animation time
    glutPostRedisplay();   // Request a redraw
    glutTimerFunc(16, timer2, 0); // Call timer again after ~16ms (~60 FPS)
}

///122
void update1(int value)
{
    if (moveJeep == true)
    {
        rotationAngle -= 2.0f; // Increment rotation angle
        if (rotationAngle > 360.0f)
            rotationAngle -= 360.0f; // Keep angle in range [0, 360]
    }
        glutPostRedisplay(); // Request display update
        glutTimerFunc(16, update1, 0); // Schedule next update after ~16ms (60 FPS)
}

///123
void update2(int value)
{
    if (moveJeep == true)
    {
        _move += .1;

        if (_move >= 50.0)
        {
            displayArko = true;
            _move = 0.0;
            moveJeep = false;
            displaySadia = false;
        }

        if (displayArko == true && _move >= 49.0)
        {
            startScene4 = true;
            _move = -15.0;
        }

        if (startScene4 == true && _move >= 30.0)
        {
            startScene5 = true;
            startC = true;
            startScene4 = false;
        }

        if (_move == 48.0)
        {
            _move = -15.0;
            moveJeep = false;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, update2, 0);
}

///124
void update3 (int value)
{
    _cloudMove += .1;

    if (_cloudMove >= 5.0)
    {
        _cloudMove = -15.0;
    }

    glutPostRedisplay();
    glutTimerFunc(25, update3, 0);
}

///125
void update4 (int value)
{
    if (startSun == true)
    {
        sunAngle += 0.1; // Increment sun angle
        if (sunAngle >= 10.0)
        {
            sunAngle = 10.0;

            if (startScene == true)
            {
                changeSkyColor = true;

                if (changeSkyColor == true)
                {
                    startMoon = true;
                    startFire = true;
                }
            }
        }
    }

    updateSun();


    if (startMoon == true)
    {

        moonAngle += 0.1; // Increment moon angle
        if (moonAngle >= 200.0)
        {
            moonAngle = 200.0;
        }
    }

    updateMoon();

    updateRing();

    glutPostRedisplay();
    glutTimerFunc(16, update4, 0);
}

///126
void updateHeli(int value)
{
    if (startScene6 == true)
    {
        _Heli -= 0.01;

        if (_Heli <= 1.0)
        {
            _Heli = 1.0;
        }

    }
        glutPostRedisplay();
        glutTimerFunc(16, updateHeli, 0);
}

///127
void updateTruck(int value)
{
    if (startScene6 == true)
    {
        _Truck -= 0.01;

        if (_Truck <= 1.0)
        {
            _Truck = 1.0;
            startWaterTrack = true;
        }

    }
        glutPostRedisplay();
        glutTimerFunc(16, updateTruck, 0);
}

///128
void updateWing(int value)
{
    if (startScene6 == true)
    {
        wingRotate -= 0.04;

        if (wingRotate <= 0.0)
        {
            wingRotate = 0.0;
        }

    }
        glutPostRedisplay();
        glutTimerFunc(16, updateWing, 0);
}

///129
void updateC(int value)
{
    if (startC == true)
    {
        moveC += .1;

        if (moveC >=20)
        {
            startC2 = true;
            startC = false;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, updateC, 0);
}

///130
void updateC2(int value)
{
    if (startC2 == true)
    {
        moveC2 -= .005;
        moveJeep = false;

        if (moveC2 <= -1.0)
        {
            startScene6 = true;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, updateC2, 0);
}

///131
void update(int value)
{
    for (int i = 0; i < NUM_SNOW_DROPS; i++)
    {
        // Move downward in the rotated space
        snowY[i] -= 0.1;

        // Compute rotated position for boundary check
        float rotatedX = snowX[i] * cos(angle * DEG_TO_RAD) - snowY[i] * sin(angle * DEG_TO_RAD);
        float rotatedY = snowX[i] * sin(angle * DEG_TO_RAD) + snowY[i] * cos(angle * DEG_TO_RAD);

        // Reset snowdrop if it goes out of bounds
        if (rotatedY < -15 || rotatedX < -20 || rotatedX > 20)
        {
            snowX[i] = -20 + (float)rand() / (RAND_MAX / 40.0); // Reinitialize in extended range
            snowY[i] = 15; // Start above the screen
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

///132
void handleKeypress(unsigned char key, int x, int y)
{
	switch (key)
    {
        case 'c':
            changeSkyColor = true;
            sunAngle = 25.0;
            break;

        case 'v':
            changeSkyColor = false;
            sunAngle = -25.0;
            break;

        case 's':
            startSun = true;
            break;

        case 'd':
            startSun = false;
            break;

        case 'm':
            startMoon = true;
            break;

        case 'n':
            startMoon = false;
            break;

        case 'w':
            startSnow = true;
            break;

        case 'e':
            startSnow = false;
            startScene = false;
            break;

        case 'j':
            moveJeep = true;
            text = false;
            startScene2 = false;
            startScene3 = false;
            break;

        case 'k':
            moveJeep = false;
            startScene3 = true;
            break;

        case 'f':
            startScene3 = true;
            startFire = true;
            break;

        case 'g':
            startScene3 = false;
            startFire = false;
            break;

        case 'r':
            startScene2 = true;
            startRing = true;
            break;

        case 't':
            startScene2 = false;
            startRing = false;
            break;

        case 'i':
            startRing = false;
            msg1 = true;
            break;

        case 'o':
            startRing = false;
            msg1 = false;
            msg2 = true;
            break;

        case 'p':
            text = true;
            startScene2 = false;
            msg1 = false;
            msg2 = false;
            break;

        case 'l':
            text = false;
            startScene2 = false;
            msg1 = false;
            msg2 = false;
            break;

        case 'q':
            startScene = false;
            startScene2 = false;
            startScene3 = false;
            startScene4 = true;
            break;

        case 'a':
            startScene = false;
            startScene2 = false;
            startScene3 = false;
            startScene4 = false;
            startScene5 = true;
            break;

        case 'z':
            startScene = false;
            startScene2 = false;
            startScene3 = false;
            startScene4 = false;
            startScene5 = false;
            startScene6 = true;
            break;

        default:
            break;

        glutPostRedisplay();
    }
}

///133
void handleMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
        start = true;

        if (displayArko == true)
        {
            startScene = true;
            startScene2 = true;
            startScene3 = true;
            startSun = true;
        }
	}

    if (button == GLUT_RIGHT_BUTTON)
    {
        sunAngle = -25.0;
        moonAngle = 160.0;
        _move = 0.0;
        start = startScene = startSun = startMoon = changeSkyColor = startSnow = moveJeep = startFire = startRing = msg1 = msg2 = false;
        displayArko = startScene4 = startScene5 = startScene6 = startWaterTrack = false;
        backgroundChanged = false;
        sunDisappeared = false;
        cloudsAppeared = false;
        carStarted = false;
    }

    glutPostRedisplay();
}

///134
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT);

    if (displaySadia == true)
    {
        // Handle background color change
        if (!backgroundChanged)
        {

            if (glutGet(GLUT_ELAPSED_TIME) >= 8000)
            { // After 3 seconds
                if (start == true)
                {
                    backgroundChanged = true;
                    red = 0.8f;
                    green = 0.8f;
                    blue = 1.0f; // Change background to light blue
                }
            }
        }

        // Handle sun disappearance after background change
        if (backgroundChanged && !sunDisappeared)
        {
            if (glutGet(GLUT_ELAPSED_TIME) >= 8000)
            { // After 5 seconds (2 seconds after background change)
                sunDisappeared = true;
            }
        }

        // Handle cloud appearance after background change
        if (backgroundChanged && !cloudsAppeared)
        {
            if (glutGet(GLUT_ELAPSED_TIME) >= 9000)
            { // After 6 seconds (1 second after sun disappears)
                cloudsAppeared = true;
            }
        }

        // Set background color
        glClearColor(red, green, blue, 1.0f);

        // Draw sun (disappears after 5 seconds)
        if (!sunDisappeared)
        {
           sun();
        }

            // Draw clouds (appear after 6 seconds)
        if (cloudsAppeared)
        {
            cloud1();
            cloud2();
            cloud3();
            cloud4();
        }

        greenlayer();
        anex1();
        building();
        tree();
        cBuilding();
        airplane();
        flower();
        road();
        people();
        car();
        text1();
        text2();
        text3();

    }

    if (displayArko == true)
    {
        Sky();
        Sun();
        Moon();
        Hill_Texture1();
        Hill_Texture2();
        Hill_Texture3();
        Cloud();
        Fire();
        Ringing();
        drawSnow();

        Msg_Texture1();
        Msg_Texture2();

        Text();

        Destroy_Texture1();
        Destroy_Texture2();
        C1();
        C_Front();
        C2();
        Destroy_Texture3();
        Wing();
        waterTrack();

        Helicoptor();
        FireTruck();
    }

    Jeep();

    glutSwapBuffers();
}

///135
// Initialization function
void initOpenGL()
{
    display();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10, 10, -6, 5.25, -10, 10);  // Set the orthographic projection
}

///136
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(1920, 1080);

    glutCreateWindow("OpenGL Setup Test");

    glutFullScreen();

    initOpenGL();

    glutDisplayFunc(display);

    glutTimerFunc(16, update01, 0);
    glutTimerFunc(16, update02, 0);
    glutTimerFunc(16, update03, 0);

    glutTimerFunc(16, timer1, 0);
    glutTimerFunc(16, timer2, 0);
    glutTimerFunc(16, update, 0);
    glutTimerFunc(16, update1, 0);
    glutTimerFunc(16, update2, 0);
    glutTimerFunc(25, update3, 0);
    glutTimerFunc(16, update4, 0);
    glutTimerFunc(16, updateHeli, 0);
    glutTimerFunc(16, updateTruck, 0);
    glutTimerFunc(16, updateC, 0);
    glutTimerFunc(16, updateC2, 0);
    glutTimerFunc(16, updateWing, 0);


    glutKeyboardFunc(handleKeypress);
    glutMouseFunc(handleMouse);

    // Load texture for the hill
    loadTexture("D:/Computer_Graphics-Full_Project\Computer_Graphics-Full_Project/Hill-01.png", &texture1); // Replace with the actual image path
    loadTexture("D:/Computer_Graphics-Full_Project\Computer_Graphics-Full_Project/Hill1-01.png", &texture4); // Replace with the actual image path
    loadTexture("D:/Computer_Graphics-Full_Project\Computer_Graphics-Full_Project/Hill2-01.png", &texture5); // Replace with the actual image path

    loadTexture("D:/Computer_Graphics-Full_Project\Computer_Graphics-Full_Project/Msg1-01.png", &texture2); // Replace with the actual image path
    loadTexture("D:/Computer_Graphics-Full_Project\Computer_Graphics-Full_Project/Msg2-01.png", &texture3); // Replace with the actual image path

    loadTexture("D:/Computer_Graphics-Full_Project\Computer_Graphics-Full_Project/AIUB Destroy1-01.png", &texture6); // Replace with the actual image path
    loadTexture("D:/Computer_Graphics-Full_Project\Computer_Graphics-Full_Project/AIUB Destroy2-01.png", &texture7); // Replace with the actual image path
    loadTexture("D:/Computer_Graphics-Full_Project\Computer_Graphics-Full_Project/AIUB Destroy3-01.png", &texture8); // Replace with the actual image path
    loadTexture("D:/Computer_Graphics-Full_Project\Computer_Graphics-Full_Project/AIUB Destroy4-01.png", &texture9); // Replace with the actual image path
    loadTexture("D:/Computer_Graphics-Full_Project\Computer_Graphics-Full_Project/AIUB Destroy5-01.png", &texture10); // Replace with the actual image path
    loadTexture("D:/Computer_Graphics-Full_Project\Computer_Graphics-Full_Project/AIUB Destroy6-01.png", &texture11); // Replace with the actual image path
    loadTexture("D:/Computer_Graphics-Full_Project\Computer_Graphics-Full_Project/AIUB Destroy7-01.png", &texture12); // Replace with the actual image path

    loadTexture("D:/Computer_Graphics-Full_Project\Computer_Graphics-Full_Project/Grass.png", &grass);
    loadTexture("D:/Computer_Graphics-Full_Project\Computer_Graphics-Full_Project/TTPC-01.png", &ttp);
    loadTexture("D:/Computer_Graphics-Full_Project\Computer_Graphics-Full_Project/TextureC-01.png",&ct);
    loadTexture("D:/Computer_Graphics-Full_Project\Computer_Graphics-Full_Project/people-01.png", &p1);
    loadTexture("D:/Computer_Graphics-Full_Project\Computer_Graphics-Full_Project/text1-01.png", &t1);
    loadTexture("D:/Computer_Graphics-Full_Project\Computer_Graphics-Full_Project/text2-01.png", &t2);
    loadTexture("D:/Computer_Graphics-Full_Project\Computer_Graphics-Full_Project/text3-01.png", &t3);

    glutMainLoop();

    return 0;
}
