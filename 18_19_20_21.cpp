// 18.	Consider the page reference string as 7,1,0,2,0,3,0,4,2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1 with 3-page frames. Find  the total number of page faults using following page replacement algorithms:
// a.	First In First Out
// b.	Optimal
// c.lru
// d.clock


#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

// Function to simulate FIFO page replacement algorithm
int fifoPageReplacement(const vector<int>& pages, int numFrames) {
    queue<int> fifoQueue;
    unordered_set<int> inMemory;
    int pageFaults = 0;

    for (int page : pages) {
        if (!inMemory.count(page)) {
            if (fifoQueue.size() == numFrames) {
                int removedPage = fifoQueue.front();
                fifoQueue.pop();
                inMemory.erase(removedPage);
            }
            fifoQueue.push(page);
            inMemory.insert(page);
            pageFaults++;
        }
    }

    return pageFaults;
}

// Function to simulate Optimal page replacement algorithm
int optimalPageReplacement(const vector<int>& pages, int numFrames) {
    unordered_map<int, int> lastOccurrence;
    unordered_set<int> inMemory;
    int pageFaults = 0;

    for (int i = 0; i < pages.size(); i++) {
        if (!inMemory.count(pages[i])) {
            if (inMemory.size() == numFrames) {
                int pageToReplace = -1, farthestOccurrence = -1;
                for (auto page : inMemory) {
                    if (lastOccurrence[page] == -1) {
                        pageToReplace = page;
                        break;
                    }
                    if (lastOccurrence[page] > farthestOccurrence) {
                        farthestOccurrence = lastOccurrence[page];
                        pageToReplace = page;
                    }
                }
                inMemory.erase(pageToReplace);
            }
            inMemory.insert(pages[i]);
            pageFaults++;
        }
        lastOccurrence[pages[i]] = i;
    }

    return pageFaults;
}

// Function to simulate LRU page replacement algorithm
int lruPageReplacement(const vector<int>& pages, int numFrames) {
    unordered_map<int, int> lastUsed;
    vector<int> memory;
    int pageFaults = 0;

    for (int page : pages) {
        if (lastUsed.find(page) == lastUsed.end()) {
            if (memory.size() == numFrames) {
                int leastRecentIdx = 0;
                for (int i = 1; i < numFrames; i++) {
                    if (lastUsed[memory[i]] < lastUsed[memory[leastRecentIdx]]) {
                        leastRecentIdx = i;
                    }
                }
                lastUsed.erase(memory[leastRecentIdx]);
                memory[leastRecentIdx] = page;
            } else {
                memory.push_back(page);
            }
            lastUsed[page] = pageFaults++;
        } else {
            lastUsed[page] = pageFaults++;
        }
    }

    return pageFaults;
}

// Function to simulate Clock page replacement algorithm
int clockPageReplacement(const vector<int>& pages, int numFrames) {
    vector<pair<int, bool>> clock(numFrames, {0, false}); // {page, reference bit}
    unordered_map<int, int> pageToClockIdx;
    int hand = 0, pageFaults = 0;

    for (int page : pages) {
        if (pageToClockIdx.find(page) == pageToClockIdx.end()) {
            while (clock[hand].second) {
                clock[hand].second = false;
                hand = (hand + 1) % numFrames;
            }
            if (clock[hand].first != 0) {
                pageToClockIdx.erase(clock[hand].first);
            }
            pageToClockIdx[page] = hand;
            clock[hand] = {page, true};
            pageFaults++;
            hand = (hand + 1) % numFrames;
        } else {
            clock[pageToClockIdx[page]].second = true;
        }
    }

    return pageFaults;
}

int main() {
    vector<int> pageReference = {7, 1, 0, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 1, 2, 0, 1, 7, 0, 1};
    int numFrames = 3;

    int fifoPageFaults = fifoPageReplacement(pageReference, numFrames);
    cout << "Total number of page faults using FIFO algorithm: " << fifoPageFaults << endl;

    int optimalPageFaults = optimalPageReplacement(pageReference, numFrames);
    cout << "Total number of page faults using Optimal algorithm: " << optimalPageFaults << endl;

    int lruPageFaults = lruPageReplacement(pageReference, numFrames);
    cout << "Total number of page faults using LRU algorithm: " << lruPageFaults << endl;

    int clockPageFaults = clockPageReplacement(pageReference, numFrames);
    cout << "Total number of page faults using Clock algorithm: " << clockPageFaults << endl;

    return 0;
}
