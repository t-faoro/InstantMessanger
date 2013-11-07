#include <WinSock2.h>
#include <Windows.h>
#include <iostream>
#include <cstdio>

#define DEFAULT_BUFLEN 512


using namespace std;

/*
* This class will handle both the sending and receiving methods of the messanger program.
*/

class InstantMessanger{

public:
	int domain, type, protocol, socketVal, environmentType, result;	
	char *messageBuffer;
	char recvbuf[DEFAULT_BUFLEN];
	
	SOCKET activeSocket;
	sockaddr_in service;

	
	//:: Constructor 
	InstantMessanger::InstantMessanger(int sockDomain, int sockType, int sockProtocol){
		
		domain			= sockDomain;
		type			= sockType;
		protocol        = sockProtocol;
		result			= 0;
		messageBuffer = "Your Mother";
		
		//environmentType = clientServerType; //:: This will be the variable used to select whether the current system is client or server.

		activeSocket = INVALID_SOCKET;
		
		initWinsock();
		activeSocket = socket(domain, type, protocol);
		bindSocket(activeSocket);



	}
	/*
	 * Initializes the Winsock2 Environment allowing the program to create sockets.
	*/
	int InstantMessanger::initWinsock(){
	//:: Winsock Initialization Start
		
		WSADATA wsaData;
		result = WSAStartup(MAKEWORD(2,2), &wsaData);

		if (result != 0) {
			printf("WSAStartup failed: %d\n", result);
			return 1;
		}
	//:: Winsock Initializtion End
	}


	/*
	 * Binds the socket selected from within the constructor
	*/
	void InstantMessanger::bindSocket(SOCKET sock){
		    
		//:: Indicates the Following:
			//: AF_INET = IPv4
			//: s_addr = Input IP Address = Localhost
			//: stons = Port number = 64000 (randomly Determined)
			service.sin_family = AF_INET;
			service.sin_addr.s_addr = inet_addr("127.0.0.1");
			service.sin_port = htons(64000);
		
		result = bind(sock, (SOCKADDR *) &service, sizeof (service));

		if(result == SOCKET_ERROR){
			//printf("There was an error, Binding failed.\n\n");
			wprintf(L"bind failed with error %u\n\n", WSAGetLastError());
			
			closesocket(sock);
			WSACleanup();

		}
		else{
			printf("Binding was successful!\n\n");
			WSACleanup();
		}
	}
	
	/*
	 * Listens to the network for attempts to connect.
	*/
	void InstantMessanger::networkListen(){
		int status = listen(this->activeSocket, SOMAXCONN);

		if(status == SOCKET_ERROR){
			printf("There was an error while listening for a message.\n Error Code: %d", WSAGetLastError());
		}
	}

	/*
	 * Connects to an available service
	*/
	
	void InstantMessanger::messangerConnect(){
		int status = connect(activeSocket, (SOCKADDR *) &service, SOMAXCONN); 
	}

	void InstantMessanger::sendMessage(string message){
		int count = send(activeSocket, this->messageBuffer, (int)strlen(this->messageBuffer), 0 );
	}
	void InstantMessanger::receiveMessage(){
		int count = recv(activeSocket, this->recvbuf, DEFAULT_BUFLEN, 0); 
	}	

	
	//:: This is the method that will send the messages to the receiver

	//:: This method will be responsible for receiving messages.

	//:: This method will send an acknowledgment to the sender when the message is received.
	void InstantMessanger::sendAck(){		
	}
	//:: This method will manage the timout function of the sender side.
	void InstantMessanger::timeout(){		
	}


	/*
	 * Possibly unnecessary method, simply prints to screen whether or not a socket has been created.
	*/
	void InstantMessanger::getSocket(){
		//string x;
		
		if(activeSocket == INVALID_SOCKET){
			printf("The program failed to create a Socket.");
		}
		else{
			printf("The program created a Socket successfully!");
			  
		}

		//return x;
	}
	

	//:: Destructor
	InstantMessanger::~InstantMessanger(){
		
	}



};