#include "Help.h"

int main()
{
    char commands[20][50] = {"fd", "forward", "bk", "history", "backward", "rt", "right", "lt", "leftturn", "repeat", "pu", "pen up", "pd", "pen down", "cs", "circle", "save", "Load", "width", "color"};
    ofstream ofile("Text.txt");

    int rows = 20;
    int red = 0;
    int green = 0;
    int blue = 255;

    while (true)
    {

        gotoxy(36, 30);
        myRectangle(290, 470, 680, 500, 160, 32, 240);
        myLine(300, 900, 600, 9000, 0, 191, 255, width);
        // myRectangle(910, 345, 1080, 625, 240, 42, 200);
        char command[30];
        cin >> command;
        bool isValidCommand = commandvalid(commands, command, rows);

        if (isValidCommand)
        {

            // cout << "Command is valid." << endl;
        }
        else
        {
            std::cout << "Command is not valid." << endl;
        }
        if (strcmp(command, "history") == 0)
        {
            ifstream ifile("Text.txt");
            string line;
            while (!ifile.eof())
            {

                getline(ifile, line);
                std::cout << line << endl;
            }
            ifile.close();
        }
        if (strcmp(command, "circle") == 0)
        {
            int radius;
            cin >> radius;
            drawCircle(470, 360, radius, Red, Green, Blue);
        }
        if (strcmp(command, "width") == 0)
        {
            int nwidth;
            cin >> nwidth;
            changeWidth(nwidth);
        }

        if (strcmp(command, "fd") == 0)
        {
            int distance;
            cin >> distance;
            removeCursor();
            std::cout << movement << endl;
            if (movement == 0)
            {
                moveForward(distance);
            }
            else if (movement == -1)
            {
                formoveLeft(distance);
            }
            else if (movement == 1)
            {
                formoveRight(distance);
            }
            else if (movement == 2)
            {
                moveForward(-distance);
            }
        }
        if (strcmp(command, "forward") == 0)
        {
            int distance;
            cin >> distance;
            removeCursor();
            if (movement == 0)
            {
                moveForward(distance);
            }
            else if (movement == -1)
            {
                formoveLeft(distance);
            }
            else if (movement == 1)
            {
                formoveRight(distance);
            }
            else if (movement == 2)
            {
                moveForward(-distance);
            }
        }
        else if (strcmp(command, "color") == 0)
        {
            char color[20];
            cin >> color;
            changeColor(color, red, green, blue);
        }

        else if (strcmp(command, "bk") == 0)
        {
            int distance;
            removeCursor();
            cin >> distance;
            removeCursor();

            //   moveBackward(distance);// commented for temporary purpose to check
            //  cout << movement << endl;
            if (movement == 0)
            {
                moveForward(-distance);
            }
            else if (movement == -1)
            {
                formoveRight(distance);
            }
            else if (movement == 1)
            {
                formoveLeft(distance);
            }
            else if (movement == 2)
            {
                moveForward(distance);
            }
        }
        else if (strcmp(command, "backward") == 0)
        {
            int distance;
            removeCursor();
            cin >> distance;
            removeCursor();

            //   moveBackward(distance);// commented for temporary purpose to check
            //  cout << movement << endl;
            if (movement == 0)
            {
                moveForward(-distance);
            }
            else if (movement == -1)
            {
                formoveRight(distance);
            }
            else if (movement == 1)
            {
                formoveLeft(distance);
            }
            else if (movement == 2)
            {
                moveForward(distance);
            }
        }
        else if ((strcmp(command, "rt") == 0) || (strcmp(command, "right") == 0))
        {
            int angle;
            cin >> angle;
            removeCursor();
            turnRight(angle);
        }

        else if ((strcmp(command, "leftturn") == 0) || (strcmp(command, "lt") == 0))
        {
            int angle;
            cin >> angle;
            turnLeft(angle);
        }
        else if (strcmp(command, "pu") == 0 || strcmp(command, "pen up") == 0)
        {
            penUp();
        }
        else if (strcmp(command, "pd") == 0 || strcmp(command, "pen down") == 0)
        {
            penDown();
        }

        else if (strcmp(command, "cls") == 0)
        {
            gotoxy(0, 0);
            system("CLS");
            myRectangle(300, 180, 680, 450, 255, 255, 0);
            myLine(300, 900, 600, 9000, 0, 191, 255, width);
            Sleep(2000);
        }
        else if (strcmp(command, "exit") == 0)
        {
            system("CLS");
            break; // Exit the loop if "exit" command is entered
        }
        if (isValidCommand)
        {

            ofile << command << endl;

            // cout << "Command is valid." << endl;
        }
    }

    ofile.close();
    std::cout << "Thank you for using the simple drawing tablet!" << endl;
    return 0;
}
