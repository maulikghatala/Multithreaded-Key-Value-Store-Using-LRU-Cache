#include <iostream>
#include <thread>
#include <sstream>
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include "../store/kv_store.hpp"

KVStore store(100); // Shared global store with capacity 100

void handle_client(int client_sock)
{
    char buffer[1024] = {0};

    while (true)
    {
        ssize_t bytes_read = read(client_sock, buffer, sizeof(buffer));
        if (bytes_read <= 0)
            break;

        std::string input(buffer, bytes_read);
        std::istringstream iss(input);
        std::string cmd, key, value;
        iss >> cmd >> key;

        std::string response;

        if (cmd == "GET")
        {
            // auto val = store.get(key);
            // response = val.has_value() ? val.value() : "NOT_FOUND";
            auto val = store.get(key);
            if (val.has_value() && val.value() != "__DELETED__")
            {
                response = val.value();
            }
            else
            {
                response = "NOT_FOUND";
            }
        }
        else if (cmd == "SET")
        {
            iss >> value;
            store.put(key, value);
            response = "OK";
        }
        else if (cmd == "DEL")
        {
            store.remove(key);
            response = "DELETED";
        }
        else
        {
            response = "UNKNOWN_COMMAND";
        }

        send(client_sock, response.c_str(), response.size(), 0);
        memset(buffer, 0, sizeof(buffer));
    }

    close(client_sock);
}

void start_server(int port)
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 10);

    std::cout << "Server listening on port " << port << "...\n";

    while (true)
    {
        int client_sock = accept(server_fd, nullptr, nullptr);
        std::thread(handle_client, client_sock).detach();
    }
}
