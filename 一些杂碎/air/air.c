#include "myhead.h"
#include "menu.h"
typedef struct ueser_list {
    char username[50];
    char phoneNumber[15];
    char departureTime[10];
    char arrivalTime[10];
    char airlineName[50];
    int flightNumber;
    struct FlightInfo* next; // 指向下一个节点的指针
} mkUser;

int main()
{

    welcome_menu();
    while (1)
    {
       
    }
}

