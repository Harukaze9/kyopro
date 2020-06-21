#ifdef DEBUG
#include "utils.cpp"
#endif
#include <bits/stdc++.h>
using namespace std;

class Graph {
    protected:
    vector<int64_t> vlabels;
    vector<vector<int64_t>> elabels;
    vector<vector<int>> AL;
    bool isDirected = true;
    bool hasEdgeLabel = false;
    static const int INF = 1e9;
    
    public:
    Graph(bool isDirected = true): isDirected(isDirected) {}

    void addNode(int64_t label) {
        vlabels.push_back(label);
        AL.emplace_back();
    }

    void addEdge(int from, int to) {
        AL[from].push_back(to);
        if(!isDirected)
            AL[to].push_back(from);
    }

    void removeEdge(int from, int to) {
        int deletion = 0;
        for(auto itr = AL[from].begin(); itr != AL[from].end(); ++itr) {
            if (*itr == to) {
                AL[from].erase(itr);
                deletion++;
                break;
            }
        }
        assert(deletion==1); // 削除が起きたかチェック
        if (!isDirected) {
            for(auto itr = AL[to].begin(); itr != AL[to].end(); ++itr) {
                if (*itr == from) {
                    AL[to].erase(itr);
                    deletion++;
                    break;
                }
            }
        }
        assert(deletion==2); // 削除が起きたかチェック
        return;
    }

    void removeDualEdge(int from, int to) {
        int deletion = 0;
        for(auto itr = AL[from].begin(); itr != AL[from].end(); ++itr) {
            if (*itr == to) {
                AL[from].erase(itr);
                deletion++;
                break;
            }
        }
        for(auto itr = AL[to].begin(); itr != AL[to].end(); ++itr) {
            if (*itr == from) {
                AL[to].erase(itr);
                deletion++;
                break;
            }
        }
        assert(deletion==2); // 削除が起きたかチェック
        return;
    }

    void setEdgeLabel(int from, int to, int64_t v) {
        cout<<"elabels を初期化していないので使えません。"<<endl;
        exit(0);
        elabels[from][to] = v;
    }

    int64_t getEdgeLabel(int from, int to) {
        return 1;
    }

    void isolateNode(int vid) {
        auto neighbors = getNeighbors(vid);
        for(auto neighbor: neighbors)
            removeDualEdge(vid, neighbor);
    }

    void setLabel(int id, int label) {vlabels[id] = label;}
    int64_t getLabel(int id) { assert(id<vlabels.size()); return vlabels[id]; }
    vector<int> getNeighbors(int id) { return AL[id]; }
    
    void show() {
        cout<<"======= info ======="<<endl;
        cout<<"|V|: "<<vlabels.size()<<endl;
        int cnt=0; for (auto al: AL) cnt+=al.size();
        cout<<"|E|: "<<cnt<<endl;
        cout<<"======="<<endl;
        for(auto i=0; i<vlabels.size(); ++i) {
            cout<<i<<" ("<<vlabels[i]<<"): ";
            for (auto j=0; j<AL[i].size(); ++j) {
                cout<<AL[i][j];
                if (j != AL[i].size()-1) cout<<", ";
            }
            cout<<endl;
        }
        return;
    }

    int64_t getDistance(int from, int to) {
        if (!hasEdgeLabel) {
            return getDistanceByBFS(from, to);
        }
        else{
            cout<<"sorry, not supported"<<endl;
            exit(0);
        }
    }

    int size() {return vlabels.size();}

    private:
    
    int getDistanceByBFS(int from, int to) {
        // set<int> searchedNodes;
        vector<int64_t> distanceMap(size(), INF);
        distanceMap[from] = 0;
        queue<int> operations;
        operations.push(from);
        while(!operations.empty()) {
            auto op = operations.front();
            int f = op;
            int d = distanceMap[f];
            operations.pop();
            auto neighbors = getNeighbors(f);
            for(auto nb: neighbors) {
                if (distanceMap[nb] > d + 1) {
                    distanceMap[nb] = d+1;
                    operations.push(nb);
                }
            }
        }
        return distanceMap[to] == INF ? -1 : distanceMap[to];
    }

};

class GridGraph : public Graph {
    protected:
    int H, W;
    public:
    GridGraph(int H, int W, int label=0): Graph(), H(H), W(W){
        vlabels = vector<int64_t>(H*W, label);
        AL = vector<vector<int>>(H*W, vector<int>());
        vector<int> dh = {1, 0, -1, 0};
        vector<int> dw = {0, 1, 0, -1};
        for(int h=0; h<H; ++h) {
            for(int w=0; w<W; ++w) {
                int from = getIndex({h, w});
                for(int i=0; i < 4; ++i) {
                    int nh = h + dh[i];
                    int nw = w + dw[i];
                    if (nh < 0 or nw < 0 or nh >= H or nw >= W) continue;
                    int to = getIndex({nh, nw});
                    Graph::addEdge(from, to);
                }
            }
        }
    }
    int getIndex(pair<int, int> pos) {
        assert(pos.first <H and pos.second < W and pos.first >=0 and pos.second >=0);
        return pos.first * W + pos.second;
    }
    void addEdge(pair<int, int> from, pair<int, int> to) { Graph::addEdge(getIndex(from), getIndex(to)); }
    void setLabel(pair<int, int> pos, int label) { Graph::setLabel(getIndex(pos), label); }
    int64_t getLabel(pair<int, int> pos, int label) { return Graph::getLabel(getIndex(pos)); }
    void removeEdge(pair<int, int> from, pair<int, int> to) { Graph::removeEdge(getIndex(from), getIndex(to)); }
    void removeDualEdge(pair<int, int> from, pair<int, int> to) { Graph::removeDualEdge(getIndex(from), getIndex(to)); }
    vector<int> getNeighbors(pair<int, int> from) { return AL[getIndex(from)]; }
    void isolateNode(pair<int, int> v) {Graph::isolateNode(getIndex(v));}
    int64_t getDistance(pair<int, int> from, pair<int, int> to) { return Graph::getDistance(getIndex(from), getIndex(to)); }
};



