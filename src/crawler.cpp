
#include "crawler.hpp"
#include "fetcher.hpp"
#include "parser.hpp"

#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;


WebCrawler::WebCrawler(const std::string& startUrl, int depth, int maxThreads)
    : baseUrl(startUrl), maxDepth(depth), threadCount(maxThreads) {
    tasks.push({startUrl, 0});
    visited.insert(startUrl);
}

void WebCrawler::start() {
    std::vector<std::thread> pool;
    for (int i = 0; i < threadCount; ++i)
        pool.emplace_back(&WebCrawler::worker, this);

    for (auto& t : pool) t.join();

    json j;
    j["base_url"] = baseUrl;
    j["depth"] = maxDepth;
    j["pages"] = json::array();

    for (auto& r : results) {
        json page;
        page["url"] = r.url;
        page["title"] = r.title;
        page["links"] = r.links;
        j["pages"].push_back(page);
    }

    std::ofstream file("output/results.json");
    file << j.dump(4);
    file.close();

    std::cout << "\ncrawl complete. results saved to output/results.json\n";
}

void WebCrawler::worker() {
    while (true) {
        std::pair<std::string, int> task;

        {
            std::lock_guard<std::mutex> lock(queueMutex);
            if (tasks.empty()) break;
            task = tasks.front();
            tasks.pop();
        }

        crawlPage(task.first, task.second);
    }
}

void WebCrawler::crawlPage(const std::string& url, int currentDepth) {
    if (currentDepth >= maxDepth) return;

    std::string html = fetchPage(url);
    if (html.empty()) return;

    std::string title = extractTitle(html);
    std::vector<std::string> links = extractLinks(html, baseUrl);

    {
        std::lock_guard<std::mutex> lock(outputMutex);
        results.push_back({url, title, links});
        std::cout << "[+] " << url << " (" << links.size() << " links)\n";
    }

    for (auto& link : links) {
        std::lock_guard<std::mutex> lock(visitMutex);
        if (!visited.count(link)) {
            visited.insert(link);
            std::lock_guard<std::mutex> qlock(queueMutex);
            tasks.push({link, currentDepth + 1});
        }
    }
    
}