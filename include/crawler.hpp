
#ifndef CRAWLER_HPP
#define CRAWLER_HPP


#include <string>
#include <unordered_set>
#include <queue>
#include <mutex>
#include <thread>
#include <vector>


struct CrawlResult {
    std::string url;
    std::string title;
    std::vector<std::string> links;
};

class WebCrawler {
public:
    WebCrawler(const std::string& startUrl, int depth, int maxThreads);
    void start();

private:
    void worker();
    void crawlPage(const std::string& url, int currentDepth);

    std::string baseUrl;
    int maxDepth;
    int threadCount;
    std::unordered_set<std::string> visited;
    std::queue<std::pair<std::string, int>> tasks;
    std::mutex queueMutex, visitMutex, outputMutex;
    std::vector<CrawlResult> results;
    bool stop = false;
};


#endif