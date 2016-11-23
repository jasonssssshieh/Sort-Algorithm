//
//  main.cpp
//  Graph Algorithm - Topological Sort
//
//  Created by Zijian Xie on 2016/11/14.
//  Copyright © 2016年 Jason Xie. All rights reserved.
//
#include <iostream>
#include <list>
#include <vector>
#include <stack>
#include <set>
using namespace std;

void topologicalsortDFS(vector<list<int>> graph, int src, vector<bool> &visited, list<int>& topologicalSortedList){
    if(!visited[src]){
        visited[src] = true;
        for(auto itr : graph[src]){
            topologicalsortDFS(graph, itr, visited, topologicalSortedList);
        }
        topologicalSortedList.push_front(src);
    }
}

list<int> topologicalSort(vector<list<int>> graph){
    list<int> topologicalSortedList;
    vector<bool> visited(graph.size(),false);
    for(int src = 0; src<graph.size(); src++){
        topologicalsortDFS(graph, src, visited, topologicalSortedList);
    }
    return topologicalSortedList;
}

int main(){
    vector<list<int>> graph;
    int v, e, src, des;
    cin>>v>>e;
    graph.resize(v);
    while(e--){
        cin>>src>>des;
        graph[src].push_back(des);
    }
    list<int> topologicalSortedList = topologicalSort(graph);
    for(list<int>::iterator itr = topologicalSortedList.begin();itr!=topologicalSortedList.end();itr++){
        cout << *itr << " ";
    }
    return 0;
}
