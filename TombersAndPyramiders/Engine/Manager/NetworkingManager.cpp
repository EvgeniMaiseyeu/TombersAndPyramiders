#include "NetworkingManager.h"
#include "MessageManager.h"

NetworkingManager* NetworkingManager::s_instance;

NetworkingManager* NetworkingManager::getInstance()
{
	if (s_instance == NULL)
		s_instance = new NetworkingManager();
	return s_instance;
}

NetworkingManager::NetworkingManager()
{
	SDLNet_Init();
	m_messageQueue = new ThreadQueue<std::string>();
}

bool NetworkingManager::createHost()
{
	return host();
}

bool NetworkingManager::createClient()
{
	return join();
}

bool NetworkingManager::isConnected()
{
	return m_socket != NULL;
}

bool NetworkingManager::isHost()
{
	return m_isHost;
}

IPaddress NetworkingManager::getIP() {
	IPaddress ip;
	SDLNet_ResolveHost(&ip, NULL, m_port);
	return ip;
}

bool NetworkingManager::startGame() {
	
	if (!isHost() || !inLobby || gameStarted)
		return false;

	inLobby = false;
	gameStarted = true;
	std::cout << "Server start game!" << std::endl;
	return true;
}

bool NetworkingManager::startGameClient() {
	if (isHost() || !inLobby || gameStarted)
		return false;

	inLobby = false;
	gameStarted = true;
	std::cout << "Client start game!" << std::endl;
	return true;
}

void NetworkingManager::listenForStart()
{
	this->m_startPacketID = MessageManager::subscribe("STARTGAME", [](std::map<std::string, void*> data) -> void
	{
		NetworkingManager::getInstance()->startGameClient();
	}, this);
}

void NetworkingManager::stopListeningForStart() {
	MessageManager::unSubscribe("STARTGAME", m_startPacketID);
}

bool NetworkingManager::host()
{
	if (inLobby || gameStarted)
		return false;
	// create a listening TCP socket on port 9999 (server)
	IPaddress ip;
	int channel;

	int startConnTime = SDL_GetTicks();
	int timeoutTime = SDL_GetTicks();
	const int TIMEOUT = 60000;

	if (SDLNet_ResolveHost(&ip, NULL, m_port) == -1)
	{
		printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		return false;
	}

	m_socket = SDLNet_TCP_Open(&ip);
	if (!m_socket)
	{
		//  printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
		std::string error = SDLNet_GetError();
		return false;
	}
	
	m_udpSocket = SDLNet_UDP_Open(m_port);
	if (!m_udpSocket)
	{
		std::string udpError = SDLNet_GetError();
		return false;
	}

	inLobby = true;
	gameStarted = false;
	m_isHost = true;
	channel = SDLNet_UDP_Bind(m_udpSocket, DEFAULT_CHANNEL, &ip);

	bool result = false;
	while (!(result = accept()) && SDL_GetTicks() - startConnTime < TIMEOUT);
	if (result)
	{
		std::cout << "Connection established." << std::endl;
		return true;
	}
	else
	{
		std::cout << "No peer found, destroying server." << std::endl;
		close(ip.host);
		return false;
	}
}

bool NetworkingManager::join()
{
	if (inLobby || gameStarted)
		return false;

	IPaddress ip;
	int channel;

	if (SDLNet_ResolveHost(&ip, IP, m_port) == -1)
	{
		printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		return false;
	}

	m_socket = SDLNet_TCP_Open(&ip);
	if (!m_socket)
	{
		printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
		close(ip.host);
		return false;
	}
	/*
	m_udpSocket = SDLNet_UDP_Open(m_port);
	if (!m_udpSocket)
	{
		printf("SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		closeUDP();
		return false;
	}
	
	channel = SDLNet_UDP_Bind(m_udpSocket, DEFAULT_CHANNEL, &ip);*/

	inLobby = true;
	gameStarted = false;
	addPlayer(ip.host, m_socket); //right
	listenForStart();

	std::cout << "SDLNet_TCP_Open:A>A>A WE DID IT JOIN" << std::endl;
	pollMessages(ip.host);
	//pollMessagesUDP(ip.host);
	return true;
}

bool NetworkingManager::accept()
{
	if (gameStarted)
		return false;

	TCPsocket m_client = SDLNet_TCP_Accept(m_socket);
	if (!m_client)
	{
		return false;
	}
	IPaddress *ip = SDLNet_TCP_GetPeerAddress(m_client);
	addPlayer(ip->host, m_client);
	pollMessages(ip->host);
	// communicate over new_tcpsock
	std::cout << "SDLNet_TCP_Accept:A>A>A WE DID IT ACCETP" << std::endl;
	return true;
}

bool NetworkingManager::close(Uint32 ip)
{
	if (m_clients.find(ip) != m_clients.end())
	{
		SDLNet_TCP_Close(m_clients[ip]);
		m_clients[ip] = NULL;
	}
	if (m_socket != NULL)
	{
		SDLNet_TCP_Close(m_socket);
		m_socket = NULL;
	}
	return true;
}

bool NetworkingManager::closeUDP()
{
	if (m_udpClient != NULL)
	{
		SDLNet_UDP_Close(m_udpClient);
		m_udpClient = NULL;
	}
	if (m_udpSocket != NULL)
	{
		SDLNet_UDP_Close(m_udpSocket);
		m_udpSocket = NULL;
	}
	return true;
}

//Host->Sending Messages->Client Exits->Host Crashes on line SDLNet_TCP_Send
void NetworkingManager::send(Uint32 ip, std::string *msg)
{
	// send a hello over sock
	//TCPsocket sock;
	int result, len;
	len = msg->length() + 1;

	if (m_clients.find(ip) != m_clients.end())
		result = SDLNet_TCP_Send(m_clients[ip], msg->c_str(), len);
	else if (m_socket != NULL)
		result = SDLNet_TCP_Send(m_socket, msg->c_str(), len);

	if (result < len)
	{
		//printf("SDLNet_TCP_Send: %s\n", SDLNet_GetError());
	}
}

bool NetworkingManager::createUDPPacket(int packetSize)
{
	m_udpPacket = SDLNet_AllocPacket(packetSize);

	if (m_udpPacket == NULL)
	{
		std::cout << "SDLNet_AllocPacket failed : " << SDLNet_GetError() << "\n";
		return false;
	}

	m_udpPacket->address.port = m_port;

	return true;
}

void NetworkingManager::sendUDP(std::string *msg)
{
	createUDPPacket(msg->length());
	memcpy(m_udpPacket->data, msg->c_str(), msg->length());

	if (SDLNet_UDP_Send(m_udpClient, DEFAULT_CHANNEL, m_udpPacket) == 0)
		std::cout << "SDLNET_UDP_SEND failed: " << SDLNet_GetError() << "\n";
}

void NetworkingManager::pollMessages(Uint32 ip)
{
	m_messagesToSend.clear();
	m_receiverThread = std::thread(&NetworkingManager::pollMessagesThread, this, ip);
	m_receiverThread.detach();
}

void NetworkingManager::pollMessagesThread(Uint32 ip)
{
#define MAXLEN 16384
	int result;
	char msg[MAXLEN];

	while (m_socket != NULL)
	{ 
		if (m_clients.find(ip) != m_clients.end())
			result = SDLNet_TCP_Recv(m_clients[ip], msg, MAXLEN);
		else if (m_socket != NULL)
			result = SDLNet_TCP_Recv(m_socket, msg, MAXLEN);
		if (result <= 0)
		{
			close(ip);
			continue;
		}
		std::string newMsg = msg;
		m_messageQueue->push(newMsg);
	}
	close(ip);
}

void NetworkingManager::pollMessagesUDP()
{
	m_messagesToSend.clear();
	m_udpReceiverThread = std::thread(&NetworkingManager::pollMessagesThreadUDP, this);
	m_udpReceiverThread.detach();
}

void NetworkingManager::pollMessagesThreadUDP()
{
#define MAXLEN 16384
	int result;
	char msg[MAXLEN];

	while (m_udpSocket != NULL)
	{ //replace with on connection lost

		if (m_udpClient != NULL || m_udpSocket != NULL)
			result = SDLNet_UDP_Recv(m_udpClient, &m_udpReceivedPacket);
		if (result < 0)
		{
			closeUDP();
			continue;
		}
		std::string newMsg(m_udpReceivedPacket.data, m_udpReceivedPacket.data+MAXLEN);
		m_messageQueue->push(newMsg);
	}
	closeUDP();
}

bool NetworkingManager::getMessage(std::string &msg)
{
	if (!m_messageQueue->isEmpty())
	{
		m_messageQueue->pop(msg);
		return true;
	}
	return false;
}

void NetworkingManager::prepareMessageForSending(std::string key, std::map<std::string, std::string> data)
{
	Message message;
	message.key = key;
	message.data = data;
	m_messagesToSend.push_back(message);
}

//TODO: Do over time
void NetworkingManager::sendQueuedEvents()
{
	if (m_messagesToSend.size() < 1)
		return;
	std::string packet = "[";
	for (size_t i = 0; i < m_messagesToSend.size(); i++)
	{
		packet += serializeMessage(m_messagesToSend[i]);
		packet += ",";
	}
	packet.pop_back();
	packet += "]";
	//Submit it
	m_messagesToSend.clear();

	for (auto it = m_clients.begin(); it != m_clients.end(); it++) {
		send(it->first, new std::string(packet));
	}
}

void NetworkingManager::sendEventToReceiver(std::map<std::string, void*> data)
{
	std::string* key = (std::string*)data["key"];
	std::string value = *key;
	MessageManager::sendEvent(value, data);
}

std::string NetworkingManager::serializeMessage(Message message)
{
	std::string result = "{";
	message.data["key"] = message.key.c_str();

	for (const auto tuple : message.data)
	{
		result += tuple.first + ":" + message.data[tuple.first] + ",";
	}
	result.pop_back();
	result += "}";
	return result;
}


void NetworkingManager::handleParsingEvents(std::string packet)
{
	std::vector<std::string> messages;
	if (packet.size() > 2)
	{
		packet.erase(0, 1);
		packet.pop_back();
		std::string currentMessage;
		bool reading = false;
		while (packet.size() > 0)
		{
			if (!reading)
			{
				if (packet[0] == '{')
				{
					reading = true;
					currentMessage += packet[0];
				}
			}
			else
			{
				currentMessage += packet[0];
				if (packet[0] == '}')
				{
					reading = false;
					messages.push_back(currentMessage);
					sendEventToReceiver(deserializeMessage(currentMessage));
					currentMessage = "";
				}
			}

			packet.erase(0, 1);
		}
	}
}



//TODO: Deserialize this:
//Example: {key : Player|UPDATE,rotation : 37.000000,scale : 1.000000,x : 1.000000,y : 0.000000}
std::map<std::string, void*> NetworkingManager::deserializeMessage(std::string message)
{
	std::map<std::string, void*> data;
	std::string currentKey = "";
	std::string currentValue = "";
	bool readingKey;
	bool readingValue;
	while (message.size() > 0)
	{
		char curChar = message[0];
		message.erase(0, 1);

		if (curChar == ',' || curChar == '{')
		{
			//Start reading key
			readingKey = true;
			readingValue = false;
			if (curChar == ',')
			{
				data[currentKey] = (void*)new std::string(currentValue);
			}
			std::string newCurrentString = "";
			std::string newCurrentValue = "";
			currentKey = newCurrentString;
			currentValue = newCurrentValue;
			continue;
		}
		else if (curChar == ':')
		{
			//Start reading value
			readingValue = true;
			readingKey = false;
			continue;
		}
		else if (curChar == '}')
		{
			//End
			data[currentKey] = (void*)new std::string(currentValue);
			break;
		}
		if (!isspace(curChar))
		{
			if (readingKey)
			{
				currentKey += curChar;
			}
			else if (readingValue)
			{
				currentValue += curChar;
			}
		}

	}
	return data;
}

void NetworkingManager::setIP(char *ip, int p)
{
	IP = ip;
	m_port = p;
}

int NetworkingManager::addPlayer(Uint32 ip, TCPsocket sock)
{
	if (m_clients.size() > 16)
	{
		return 0;
	}
	m_clients.insert(std::pair<Uint32, TCPsocket>(ip, sock));
	return 1;
}

int NetworkingManager::removePlayer(Uint32 ip)
{
	for (auto it = m_clients.begin(); it != m_clients.end(); it++)
	{
		if (it->first == ip) 
		{
			m_clients.erase(it);
			return 1;
		}
	}
	return 0;
}