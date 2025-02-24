#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
using namespace std;
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void myLine(int x1, int y1, int x2, int y2, int R, int G, int B, int width) // use three 3 integers if you want colored lines.
{
    HWND console_handle = GetConsoleWindow();
    HDC device_context = GetDC(console_handle);

    // change the color by changing the values in RGB (from 0-255) to get shades of gray. For other colors use 3 integers for colors.
    HPEN pen = CreatePen(PS_SOLID, width, RGB(R, G, B)); // 2 is the width of the pen
    SelectObject(device_context, pen);
    MoveToEx(device_context, x1, y1, NULL);
    LineTo(device_context, x2, y2);
    ReleaseDC(console_handle, device_context);
    DeleteObject(pen);
}

// This function checks if any of the 4 cursor keys are pressed.
// If any cursor key is pressed, then the function returns true, and whichKey identifies which of the 4 cursor keys is pressed.
// whichkey is assigned following values if any cursor key is pressed. 1 for left, 2 for up, 3 for right and 4 for left.
bool isCursorKeyPressed(int &whichKey) // whichKey passed as reference....
{
    char key;
    key = GetAsyncKeyState(37);
    if (key == 1)
    {
        whichKey = 1; // 1 if left key is pressed
        return true;
    }
    key = GetAsyncKeyState(38);
    if (key == 1)
    {

        whichKey = 2; // 2 if up key is pressed
        return true;
    }

    key = GetAsyncKeyState(39);
    if (key == 1)
    {

        whichKey = 3; // 3 if right key is pressed
        return true;
    }
    key = GetAsyncKeyState(40);
    if (key == 1)
    {

        whichKey = 4; // 4 if down key is pressed
        return true;
    }
    return false;
}

void myRectangle(int x1, int y1, int x2, int y2, int R, int G, int B)
{
    HWND console_handle = GetConsoleWindow();
    HDC device_context = GetDC(console_handle);

    // change the color by changing the values in RGB (from 0-255)
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(R, G, B));
    SelectObject(device_context, pen);
    HBRUSH brush = ::CreateSolidBrush(RGB(0, 0, 0)); // Fill color can also be passed as parameter to the function!!!

    SelectObject(device_context, brush);

    Rectangle(device_context, x1, y1, x2, y2);
    ReleaseDC(console_handle, device_context);
    DeleteObject(pen);
    DeleteObject(brush);
}

void myEllipse(int x1, int y1, int x2, int y2, int R, int G, int B)
{
    HWND console_handle = GetConsoleWindow();
    HDC device_context = GetDC(console_handle);

    // change the color by changing the values in RGB (from 0-255)
    HPEN pen = CreatePen(PS_SOLID, 2, RGB(R, G, B));
    SelectObject(device_context, pen);

    // Set the brush to NULL to prevent filling
    HBRUSH oldBrush = (HBRUSH)SelectObject(device_context, GetStockObject(NULL_BRUSH));

    Ellipse(device_context, x1, y1, x2, y2);

    // Restore the original brush
    SelectObject(device_context, oldBrush);

    ReleaseDC(console_handle, device_context);
    DeleteObject(pen);
}

using namespace std;

int X1 = 470, Y1 = 360, X2 = 460, Y2 = 370;
int X3 = 470, Y3 = 360, X4 = 480, Y4 = 370;
int rightCursor = 0;
int ANGLE = 0;
int movement = 0;
int width = 2;
bool isPenDown = true;

bool commandvalid(char commands[][50], char command[30], int rows)
{
    for (int i = 0; i < rows; ++i)
    {
        if (strcmp(command, commands[i]) == 0)
        {
            return true;
        }
    }
    return false;
}

int Red = 0;
int Green = 191;
int Blue = 255;

void changeColor(const char *color, int &red, int &green, int &blue)
{
    if (strcmp(color, "blue") == 0)
    {
        red = 0;
        green = 0;
        blue = 255;
    }
    else if (strcmp(color, "red") == 0)
    {
        red = 255;
        green = 0;
        blue = 0;
    }
    else if (strcmp(color, "green") == 0)
    {
        red = 0;
        green = 255;
        blue = 0;
    }
    else if (strcmp(color, "yellow") == 0)
    {
        red = 255;
        green = 255;
        blue = 0;
    }
    else if (strcmp(color, "cyan") == 0)
    {
        red = 0;
        green = 255;
        blue = 255;
    }
    else if (strcmp(color, "magenta") == 0)
    {
        red = 255;
        green = 0;
        blue = 255;
    }
    else if (strcmp(color, "orange") == 0)
    {
        red = 255;
        green = 165;
        blue = 0;
    }
    else if (strcmp(color, "purple") == 0)
    {
        red = 128;
        green = 0;
        blue = 128;
    }
    else if (strcmp(color, "pink") == 0)
    {
        red = 255;
        green = 192;
        blue = 203;
    }
    else if (strcmp(color, "brown") == 0)
    {
        red = 165;
        green = 42;
        blue = 42;
    }

    Red = red;
    Green = green;
    Blue = blue;
}

void drawCursor()
{
    myLine(X1, Y1, X2, Y2, Red, Green, Blue, width);
    myLine(X3, Y3, X4, Y4, Red, Green, Blue, width);
}

void eraseCursor()
{

    myLine(X1, Y1, X2, Y2, 0, 191, 255, width);

    myRectangle(X1 - 1, Y1 - 1, X4 + 1, Y4 + 1, 0, 0, 0);
}

void penUp()
{
    isPenDown = false;
}

void penDown()
{
    isPenDown = true;
}

void moveForward(int distance)
{
    // cout << "Forward Called\n";
    int initialX1 = X1, initialY1 = Y1;
    int initialX3 = X3, initialY3 = Y3;
    Y1 = Y1 - distance;
    Y2 = Y2 - distance;
    Y3 = Y3 - distance;
    Y4 = Y4 - distance;

    if (isPenDown)
    {
        myLine(initialX1, initialY1, X1, Y1, Red, Green, Blue, width);
        myLine(initialX3, initialY3, X3, Y3, Red, Green, Blue, width);
    }
    else
    {
        eraseCursor();
    }

    drawCursor();
}

void formoveRight(int distance)
{
    cout << "Move Right\n";
    int stX1 = X1, stY1 = Y1;
    int stX2 = X2, stY2 = Y2;
    if (rightCursor == 0)
    {
        rightCursor = X2 + distance;
    }
    else
    {
        rightCursor = rightCursor + distance;
    }
    if (isPenDown)
    {
        myLine(stX1, stY1, X1, Y1, Red, Green, Blue, width);
        myLine(stX2, stY2, rightCursor, Y2, Red, Green, Blue, width);
    }
    else
    {
        eraseCursor();
    }
    X2 = X2 + distance;
    X1 = X1 + distance;
    X3 = X3 + distance;
    X4 = X4 + distance;
    drawCursor();
}
void drawCircle(int x, int y, int r, int R, int G, int B)
{
    int x1 = x - r;
    int y1 = y - r;
    int x2 = x + r;
    int y2 = y + r;

    myEllipse(x1, y1, x2, y2, R, G, B);
}
void formoveLeft(int distance)
{
    cout << "Move Left\n";
    int stX1 = X1, stY1 = Y1;
    int stX2 = X2, stY2 = Y2;
    if (rightCursor == 0)
    {
        rightCursor = X2 - distance;
    }
    else
    {
        rightCursor = rightCursor - distance;
    }
    if (isPenDown)
    {
        myLine(stX1, stY1, X1, Y1, Red, Green, Blue, width);
        myLine(stX2, stY2, rightCursor, Y2, Red, Green, Blue, width);
    }
    else
    {
        eraseCursor();
    }
    X2 = X2 - distance;
    X1 = X1 - distance;
    X3 = X3 - distance;
    X4 = X4 - distance;
    drawCursor();
}

void removeCursor()
{

    myLine(X1, Y1, X2, Y2, 0, 0, 0, width);
    myLine(X3, Y3, X4, Y4, 0, 0, 0, width);
}

void moveBackward(int distance)
{
    int initialx1 = X1, initialy1 = Y1;
    int initialx2 = X2, initialy2 = Y2;
    int initialx3 = X3, initialy3 = Y3;
    int initialx4 = X4, initialy4 = Y4;

    Y1 = Y1 + distance;
    Y2 = Y2 + distance;
    Y3 = Y3 + distance;
    Y4 = Y4 + distance;

    if (isPenDown)
    {
        myLine(initialx1, initialy1, X1, Y1, Red, Green, Blue, width);
        myLine(initialx3, initialy3, X3, Y3, Red, Green, Blue, width);
    }
    drawCursor();
}
void turnRight(int angle)
{
    double radians = angle * (3.14 / 180.0);
    double cosAngle = cos(radians);
    double sinAngle = sin(radians);

    int centerx = (X1 + X4) / 2;
    int centery = (Y1 + Y4) / 2;

    X1 = X1 - centerx;
    Y1 = Y1 - centery;
    X2 = X2 - centerx;
    Y2 = Y2 - centery;
    X3 = X3 - centerx;
    Y3 = Y3 - centery;
    X4 = X4 - centerx;
    Y4 = Y4 - centery;

    int fiX1 = round(X1 * cosAngle - Y1 * sinAngle);
    int fiY1 = round(X1 * sinAngle + Y1 * cosAngle);
    int fiX2 = round(X2 * cosAngle - Y2 * sinAngle);
    int fiY2 = round(X2 * sinAngle + Y2 * cosAngle);
    int fiX3 = round(X3 * cosAngle - Y3 * sinAngle);
    int fiY3 = round(X3 * sinAngle + Y3 * cosAngle);
    int fiX4 = round(X4 * cosAngle - Y4 * sinAngle);
    int fiY4 = round(X4 * sinAngle + Y4 * cosAngle);

    X1 = fiX1 + centerx;
    Y1 = fiY1 + centery;
    X2 = fiX2 + centerx;
    Y2 = fiY2 + centery;
    X3 = fiX3 + centerx;
    Y3 = fiY3 + centery;
    X4 = fiX4 + centerx;
    Y4 = fiY4 + centery;

    drawCursor();

    ANGLE = ANGLE + angle;
    if (ANGLE > 360)
    {
        ANGLE = ANGLE - 360;
    }
    // cout << ANGLE << " Degree\n";
    if (ANGLE == 90)
    {
        movement = 1;
    }
    else if (ANGLE == 270)
    {
        movement = -1;
    }
    else if (ANGLE == 180)
    {
        movement = 2;
    }
    else
    {
        movement = 0;
    }
}

void turnLeft(int angle)
{

    if (ANGLE == 0)
    {
        ANGLE = 360 - angle;
    }
    else
    {
        ANGLE = ANGLE - angle;
    }
    if (ANGLE == 90)
    {
        movement = 1;
    }
    else if (ANGLE == 270)
    {
        movement = -1;
    }
    else if (ANGLE == 180)
    {
        movement = 2;
    }
    else
    {
        movement = 0;
    }

    if (ANGLE < 0)
    {
        ANGLE = ANGLE + 360;
    }
    if (ANGLE == 90)
    {
        movement = 1;
    }
    else if (ANGLE == 270)
    {
        movement = -1;
    }
    else if (ANGLE == 180)
    {
        movement = 2;
    }
    else
    {
        movement = 0;
    }
    turnRight(-angle);
    removeCursor();
}

void changeWidth(int nwidth)
{
    width = nwidth;
}

// void repeatCommand(int n, char command[]) {
//     for (int i = 0; i < n; i++) {
//         if (strcmp(command, "") == 0) {
//         }
//     }
// }
