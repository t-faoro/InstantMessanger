//:: Include Custom Headers 
#include "InstantMessanger.class.h";
#include "socketMethods.class.h";

//:: Include Pre-Processor Directives
#include <iostream>
#include <WinSock2.h>
#include <Windows.h>
#include <cstdlib>
#include <string>
#include <sstream>

//:: Define Constants including namespace
#define CLIENT_SIDE  1;
#define SERVER_SIDE  2;
using namespace std;

//:: Program Start
void main(){

//:: Instantiate Instant Messanger Class. Constructor takes all necessary Socket information for connection.

InstantMessanger im(PF_INET, SOCK_DGRAM, 0);

// Call the getSocket method from the InstantMessanger Class, simply shows if the socket was created properly, or not.
im.getSocket();


cout << "\n\n";


//:: Exit the program gracefully.
 cout << "\n\n\n\n";
system("pause");

}
