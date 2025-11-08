
#include "crawler.hpp"
#include "utils.hpp"

#include <iostream>


int main(int argc, char* argv[]) {
    if (argc < 4) {
        std::cout << "usage: ./crawler --url <url> --depth <n> --threads <t>\n";
        return 1;
    }

    std::string url;
    int depth = 1, threads = 4;

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--url" && i + 1 < argc) url = argv[++i];
        else if (arg == "--depth" && i + 1 < argc) depth = std::stoi(argv[++i]);
        else if (arg == "--threads" && i + 1 < argc) threads = std::stoi(argv[++i]);
    }

    if (url.empty()) {
        std::cerr << "please provide a proper URL\n";
        return 1;
    }

    WebCrawler crawler(url, depth, threads);
    crawler.start();

    return 0;
}
