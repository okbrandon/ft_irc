#include <cstdlib>
#include <iostream>
#include "../inc/IrcBot.hpp"

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " <server> <port> <password> <channel>\n";
        return EXIT_FAILURE;
    }

    const char* server = argv[1];
    int port = std::atoi(argv[2]);
    const char* password = argv[3];
    const char* channel = argv[4];

    IrcBot bot(port);
    bot.connect(server, password, channel);

    return EXIT_SUCCESS;
}
