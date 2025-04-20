#include <iostream>
#include <conio.h>
#include <thread>
#include <windows.h>
#include <string>




void setConsoleFontSize(int width, int height) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_FONT_INFOEX fontInfo;
    fontInfo.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);

    // Set font name (optional, e.g., "Consolas" or "Lucida Console")
    wcscpy_s(fontInfo.FaceName, L"Consolas");

    fontInfo.dwFontSize.X = width;  // Width of each character
    fontInfo.dwFontSize.Y = height; // Height of each character

    SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);
}

int keyPress;
enum board{
    none = 0,
    selected = 1,
    x = 2,
    o = 3
};
board screen[3][3]{
{none, none, none},
{none, selected, none},
{none, none, none}
};

const char* boardToString(board b) {
    switch (b) {
        case none: return " ";
        case selected: return "\u2588";
        case x: return "x";
        case o: return "o";
        default: return "unknown";
    }
}
void draw(){
    std::cout << "|" << boardToString(screen[0][0]) << "|" << boardToString(screen[0][1]) << "|" << boardToString(screen[0][2]) << "|" << std::endl;
    std::cout << "|" << boardToString(screen[1][0]) << "|" << boardToString(screen[1][1])<< "|" << boardToString(screen[1][2]) << "|" << std::endl;
    std::cout << "|" << boardToString(screen[2][0]) << "|" << boardToString(screen[2][1]) << "|" << boardToString(screen[2][2]) << "|" << std::endl;
} 
board checkwin(){
    board lookingfor = x;
    int filledamount = 0;
    for(int i =0; i < 3; i++){
        //up and down
        lookingfor = x;
        if(screen[0][i] == lookingfor && screen[1][i] == lookingfor && screen[2][i] == lookingfor){
            std::cout << "x win";
            return x;
        }
        lookingfor = o;
        if (screen[0][i] == lookingfor && screen[1][i] == lookingfor && screen[2][i] == lookingfor){
            std::cout << "o win";
            return o;

        }

        //side to side
        lookingfor = x;
        if(screen[i][0] == lookingfor && screen[i][1] == lookingfor && screen[i][2] == lookingfor){
            std::cout << "x win";
            return x;
        }
        lookingfor = o;
        if (screen[i][0] == lookingfor && screen[i][1] == lookingfor && screen[i][2] == lookingfor){
            std::cout << "o win";
            return o;

        }

      

        }

      // diagonal, doesnt need to be looped
      lookingfor = x;
      if(screen[0][0] == lookingfor && screen[1][1] == lookingfor && screen[2][2] == lookingfor){
          std::cout << "x win";
          return x;
      }
      
      if (screen[0][2] == lookingfor && screen[1][1] == lookingfor && screen[2][0] == lookingfor){
          std::cout << "x win";
          return o;

      }
      // o diagional
      lookingfor = o;
      if(screen[0][0] == lookingfor && screen[1][1] == lookingfor && screen[2][2] == lookingfor){
        std::cout << "o win";
        return x;
    }
    
    if (screen[0][2] == lookingfor && screen[1][1] == lookingfor && screen[2][0] == lookingfor){
        std::cout << "o win";
        return o;

    }


    for (auto& row : screen) {        // Loop over rows
        for (auto& cell : row) {      // Loop over each cell in the row
            if(cell == x || cell == o){
                filledamount++;
                //std::cout << filledamount;
                if(filledamount == 9){
                    filledamount = 0;
                    std::cout << "Tie!";
                    std::this_thread::sleep_for(std::chrono::seconds(2));
                    for (auto& row : screen) {        // Loop through each row
                        for (auto& cell : row) {      // Loop through each cell in the row
                            std::this_thread::sleep_for(std::chrono::milliseconds(100));
                            cell = none;              // Set the cell to 'none'
                            system("CLS");
                            draw();
                            

                        }
                    }
                }
            }
            
        }
    }


        return none;
}

struct Pos {
    int x;
    int y;
};
bool currentplayerisx = 1;

board last;
int main() {
    SetConsoleOutputCP(CP_UTF8);
    system("CLS");

    draw();
std::cout << "Press any key to start" << std::endl;
std::cout << "Press Q to quit at anytime" << std::endl;

    Pos currentPos;
    currentPos.x = 1;
    currentPos.y = 1;

    setConsoleFontSize(20, 40);
    while (true) {

        
        keyPress = _getch();
       // if (keyPress){

            //std::cout << keyPress;
       // }
        if (keyPress == '\r') { // '\r' is the Enter key
            if(last == none){
                    
            
                
                if(currentplayerisx){
                    last = x;
                    screen[currentPos.y][currentPos.x] = x;
                    currentplayerisx = !currentplayerisx;
                }else{
                    last = o;
                screen[currentPos.y][currentPos.x] = o;
                currentplayerisx = !currentplayerisx;
            }

            
            
        }
    }
        // Optionally, add an exit condition to break the loop (like pressing 'q')
        if (keyPress == 113) {
            break;
        }
        if (keyPress == 0 || keyPress == 224) {
            int arrow = _getch(); // second character (actual arrow key)
            switch (arrow) {
                case 72:
                    //std::cout << "Up arrow pressed!\n";
                    if(currentPos.y != 0){
                    currentPos.y--;
                    }
                    break;
                case 80:
                    //std::cout << "Down arrow pressed!\n";
                    if(currentPos.y != 2){
                        currentPos.y++;
                    }
                    
                    break;
                case 75:
                    //std::cout << "Left arrow pressed!\n";
                   
                    if(currentPos.x != 0){
                        currentPos.x--;
                    }
                    break;
                case 77:
                    //std::cout << "Right arrow pressed!\n";
                    if(currentPos.x != 2){
                        currentPos.x++;
                    }

                    break;
                default:
                    //std::cout << "Other special key: " << arrow << "\n";
                    break;
                    
            }
           
            for (auto& row : screen) {        // Loop over rows
                for (auto& cell : row) {      // Loop over each cell in the row
                    
                    if (cell == selected) {
                        cell = last;         // If any cell is "selected"
                    }
                }
            }
            if(currentPos.y > 3 || currentPos.x > 3){
                
            }else{
                last = screen[currentPos.y][currentPos.x];
                screen[currentPos.y][currentPos.x] = selected;
            }
            
            
        }
               system("CLS");

        draw();
        if(checkwin() != none){
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
            setConsoleFontSize(0, 16);
            return 0;
            
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
            
    }
        

setConsoleFontSize(0, 16);
}