#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

//defining the ascii value of the requirement to make a box
#define Space 32
#define Horizinatal_Line 196
#define Vertical_Line 179
#define Top_T 194
#define Left_Side_T 195
#define Right_Side_T 180
#define Bottom_T 193
#define Left_Top 218
#define Right_Top 191
#define Bottom_Left 192
#define Bottom_Right 217
#define Cross 197
#define Back_Space 8

//This is rows and columns of the total screen
#define Total_Column 80
#define Total_Rows 25

//width and dimension of the box
#define Width_Box 5
#define Dimension 7

//Defining the Keys
#define Left 75
#define Right 77
#define Up 72
#define Down 80

void gotoxy(int x, int y){
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
int isLeapYear(int Year){
    return (((Year % 4 == 0) && (Year % 100 != 0)) ||(Year % 400 == 0)) ? TRUE : FALSE;
}
void DaysInBox(void){
    int row;
    int column;
    char * dayNames[ ] = { "SUN","MON","TUE","WED","THU","FRI","SAT"};
    column = (Total_Column - ((Width_Box * Dimension) + (Dimension + 1)))/2;
    row = (Total_Rows - (Dimension +(Dimension + 1))) / 2;
    row = row + 1;
    column = column + 2;
    int counter;
    for(counter = 0; counter < Dimension ; counter+=1){
        gotoxy(column + (counter * (Width_Box + 1)), row);
        printf("%s",dayNames[ counter ]);
    }
}

int DayOfWeek( int y, int m, int d )
{
    static int t[] = { 0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4 };
    y -= m < 3;
    return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
}

void calendar(int Month, int Year){
    int Days_in_Month [ ] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    char *MonthName [ ] = {"","January","February","March","April","May","June","July","August","September","October","November","December"};
    int row;
    int column;
    int Day;
    int Counter;
    column = (Total_Column - ((Width_Box * Dimension) + (Dimension + 1)))/2;
    row = (Total_Rows - (Dimension + (Dimension + 1)))/2;
    row = row + 3;
    column = column + 3;
    gotoxy(30,3);
    printf("%10s,%d",MonthName[Month],Year);
    cleaner();
    if(isLeapYear(Year) == TRUE){
        Days_in_Month[2] = 29;
    }
    else{
        Days_in_Month[2] = 28;
    }
    for(Day = 1,Counter = DayOfWeek(Year,Month,1);Day <= Days_in_Month[Month];Day += 1){
        gotoxy(column+(Counter * (Width_Box + 1)),row);
        printf("%02d",Day);
        Counter+=1;
        if(Counter == Dimension){
            row = row + 2;
            Counter = 0;
        }
    }
}

void cleaner(){
    int row;
    int column;
    column = (Total_Column - ((Width_Box * Dimension) + (Dimension + 1)))/2;
    row = (Total_Rows - (Dimension + (Dimension + 1)))/2;
    row = row+3;
    column = column + 3;
    int counter;
    int week;
    for(week = 0; week <= 6; week += 1){
        for(counter = 0; counter < Dimension; counter += 1){
            gotoxy(column + (counter * (Width_Box+1)) , row + (week * 2));
            printf("  ");
        }
    }
}

void DrawBox(void){
    int row;
    int column;
    int counter1;
    int counter2;
    int counter3;
    int counter4;
    int Box_Extender;
    column = (Total_Column - ((Width_Box * Dimension)+(Dimension + 1)))/2;
    row = (Total_Rows - (Dimension + (Dimension + 1)))/2;
    gotoxy(column,row);
    printf("%c",Left_Top);
    for(counter2 = 0; counter2 < Dimension; counter2 += 1){
    for(counter1 = 0;counter1 < Width_Box;counter1 += 1){
        printf("%c",Horizinatal_Line);
    }
    printf("%c",Top_T);
    }
    printf("%c",Back_Space);
    printf("%c",Right_Top);
    //End Of First Line
    for(Box_Extender = 0; Box_Extender < Dimension; Box_Extender += 1){
    row = row+1;
    gotoxy(column , row);
    for(int counter4 = 0;counter4 <= Dimension; counter4 += 1){
    printf("%c",Vertical_Line);
    for(int counter3 = 0;counter3 < Width_Box;counter3 += 1){
       printf("%c",Space);
            }
        }
        row = row+1;
        gotoxy(column , row);
        printf("%c",Left_Side_T);
        for(counter2 = 0;counter2 < Dimension;counter2 += 1){
        for(counter1 = 0;counter1 < Width_Box;counter1 += 1){
            printf("%c",Horizinatal_Line);
            }
            printf("%c",Cross);
        }
        printf("%c",Back_Space);
        printf("%c",Right_Side_T);
    }
    gotoxy(column , row);
    printf("%c",Bottom_Left);
    for(counter2 = 0;counter2 < Dimension; counter2 += 1){
    for(counter1 = 0;counter1 < Width_Box;counter1 += 1){
    printf("%c",Horizinatal_Line);
    }
    printf("%c",Bottom_T);
    }
    printf("%c",Back_Space);
    printf("%c",Bottom_Right);
}
int main(){
    DrawBox();
    DaysInBox();
    int Month = 5;
    int Year = 2004;
    int Key;
    do{
    calendar(Month,Year);
    Key = getch();
    if(Key != 27){
        Key = getch();
    }
    switch(Key){
        case Left : Month = Month - 1;break;
        case Right : Month = Month + 1;break;
        case Up : Year = Year + 1;break;
        case Down : Year = Year - 1;break;
    }
    if(Month == 0){
        Year = Year - 1;
        Month = 12;
    }
    else if(Month > 12){
        Year = Year + 1;
        Month = 1;
    }
    }
    while(Key != 27);
    return EXIT_SUCCESS;
}
