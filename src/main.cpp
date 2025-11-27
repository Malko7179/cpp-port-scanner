#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() {
    WSADATA wsa;
    SOCKET sock;
    sockaddr_in server;

    cout << "Simple TCP Port Scanner " << endl;

    // Initialize WinSock
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        cout << "Failed. Error Code: " << WSAGetLastError();
        return 1;
    }

    string target;
    cout << "Enter target IP : ";
    cin >> target;

    int startPort, endPort;
    cout << "Start Port: ";
    cin >> startPort;
    cout << "End Port: ";
    cin >> endPort;

    for (int port = startPort; port <= endPort; port++) {
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == INVALID_SOCKET) continue;

        server.sin_addr.s_addr = inet_addr(target.c_str());
        server.sin_family = AF_INET;
        server.sin_port = htons(port);

        int result = connect(sock, (sockaddr*)&server, sizeof(server));

        if (result == 0) {
            cout << "[OPEN] Port " << port << endl;
        }

        closesocket(sock);
    }

    WSACleanup();
    return 0;
}
