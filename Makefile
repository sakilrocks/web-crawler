
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pthread
LIBS = -lcurl
INCLUDE = -Iinclude
SRC = src/main.cpp src/crawler.cpp src/fetcher.cpp src/parser.cpp src/utils.cpp
OUT = crawler

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(INCLUDE) $(LIBS) -o $(OUT)

run: $(OUT)
	./$(OUT) --url https://example.com --depth 2 --threads 5

clean:
	rm -f $(OUT)
