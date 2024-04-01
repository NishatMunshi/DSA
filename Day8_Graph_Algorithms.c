#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_VERTICES_BFS 8
#define NUMBER_OF_VERTICES_DFS 4
#define NO 8
#define WHITE 0
#define GRAY 1
#define BLACK 2

void BFS(int graph[NUMBER_OF_VERTICES_BFS][NUMBER_OF_VERTICES_BFS], int start) {
  int color[NUMBER_OF_VERTICES_BFS];
  int distance[NUMBER_OF_VERTICES_BFS];
  int parent[NUMBER_OF_VERTICES_BFS];
  int queue[NUMBER_OF_VERTICES_BFS];
  int front = 0, rear = 0;

  for (int index = 0; index < NUMBER_OF_VERTICES_BFS; index++) {
    color[index] = WHITE; // Mark all nodes as white
    distance[index] = -1;
    parent[index] = -1;
  }

  color[start] = GRAY;
  distance[start] = 0;   // Distance to start node is 0
  parent[start] = -1;    // Start node has no parent
  queue[rear++] = start; // Enqueue start node

  printf("Visited Node\tQueue\t\t\tColor Array\t\t\t\tDistance Array\n");

  while (front != rear) {
    // Deque front node
    int visitingNode = queue[front++];
    printf("%d\t", visitingNode);

    // Display the queue contents
    printf("\t{");
    for (int index = front; index < rear; index++) {
      printf("%d%s", queue[index], (index < rear - 1) ? ", " : "");
    }
    printf("}\t\t");

    // display the color array
    printf("\t{");
    for (int index = 0; index < NUMBER_OF_VERTICES_BFS; index++) {
      printf("%d%s", color[index],
             (index < NUMBER_OF_VERTICES_BFS - 1) ? ", " : "");
    }
    printf("}\t");

    // display the distance array
    printf("\t{");
    for (int index = 0; index < NUMBER_OF_VERTICES_BFS; index++) {
      printf("%d%s", distance[index],
             (index < NUMBER_OF_VERTICES_BFS - 1) ? ", " : "");
    }
    printf("}\n");

    for (int potentialNeighbour = 0;
         potentialNeighbour < NUMBER_OF_VERTICES_BFS; potentialNeighbour++) {
      if (graph[visitingNode][potentialNeighbour] &&
          color[potentialNeighbour] == WHITE) {
        color[potentialNeighbour] = GRAY; // Mark potentialNeighbour as gray
        distance[potentialNeighbour] = distance[visitingNode] + 1;
        parent[potentialNeighbour] = visitingNode;
        queue[rear++] = potentialNeighbour; // Enque neighbour
      }
    }

    color[visitingNode] = 2; // Mark visitingNode as black
  }

  printf("\nTree Structure (pi) Array:\n");
  for (int index = 0; index < NUMBER_OF_VERTICES_BFS; index++) {
    printf("pi[%d] = %d\n", index, parent[index]);
  }
}

void DFS(int graph[NUMBER_OF_VERTICES_DFS][NUMBER_OF_VERTICES_DFS], int start) {
  int color[NUMBER_OF_VERTICES_DFS];
  int parent[NUMBER_OF_VERTICES_DFS];
  int discovery_time[NUMBER_OF_VERTICES_DFS];
  int finish_time[NUMBER_OF_VERTICES_DFS];
  int stack[NUMBER_OF_VERTICES_DFS];
  int top = -1;
  int time = 0;

  for (int i = 0; i < NUMBER_OF_VERTICES_DFS; i++) {
    color[i] = WHITE; // Mark all nodes as white
    parent[i] = -1;
    discovery_time[i] = -1;
    finish_time[i] = -1;
  }

  color[start] = GRAY; // Mark the start node as gray
  discovery_time[start] = ++time;
  stack[++top] = start;

  printf("Visited Node\tStack\t\t\tColor Array\t\tDiscovery Time\t\tFinish Time\n");

  while (top != -1) {
    int visitingNode = stack[top];
    if (color[visitingNode] == GRAY) {
      printf("%d\t", visitingNode);

      // Display the stack contents
      printf("\t{");
      for (int i = 0; i <= top; i++) {
        printf("%d%s", stack[i], (i < top) ? ", " : "");
      }
      printf("}\t\t");

      printf("\t{");
      for (int i = 0; i < NUMBER_OF_VERTICES_DFS; i++) {
        printf("%d%s", color[i], (i < NUMBER_OF_VERTICES_DFS - 1) ? ", " : "");
      }
      printf("}\t");

      printf("\t{");
      for (int i = 0; i < NUMBER_OF_VERTICES_DFS; i++) {
        printf("%d%s", discovery_time[i],
               (i < NUMBER_OF_VERTICES_DFS - 1) ? ", " : "");
      }
      printf("}\t");

      printf("\t{");
      for (int i = 0; i < NUMBER_OF_VERTICES_DFS; i++) {
        printf("%d%s", finish_time[i],
               (i < NUMBER_OF_VERTICES_DFS - 1) ? ", " : "");
      }
      printf("}\n");
    }

    top--;
    color[visitingNode] = BLACK; // Mark visitingNode as black
    finish_time[visitingNode] = ++time;

    for (int potentialNextNode = 0; potentialNextNode < NUMBER_OF_VERTICES_DFS;
         potentialNextNode++) {
      if (graph[visitingNode][potentialNextNode] &&
          color[potentialNextNode] == WHITE) {
        color[potentialNextNode] = 1; // Mark potentialNextNode as gray
        parent[potentialNextNode] = visitingNode;
        discovery_time[potentialNextNode] = ++time;
        stack[++top] = potentialNextNode;
      }
    }
  }

  printf("\nTree Structure (pi) Array:\n");
  for (int i = 0; i < NUMBER_OF_VERTICES_DFS; i++) {
    printf("pi[%d] = %d\n", i, parent[i]);
  }

  printf("\nParenthesis Array:\n");
  for (int i = 0; i < NUMBER_OF_VERTICES_DFS; i++) {
    printf("(%d/%d) ", discovery_time[i], finish_time[i]);
  }
  printf("\n");
}

int main() {
  // Creating the BFS graph
  int graph[NUMBER_OF_VERTICES_BFS][NUMBER_OF_VERTICES_BFS];
  for (unsigned i = 0; i < NUMBER_OF_VERTICES_BFS; ++i) {
    for (unsigned j = 0; j < NUMBER_OF_VERTICES_BFS; ++j) {
      graph[i][j] = 0;
    }
  }
  graph[0][1] = graph[1][0] = 1;
  graph[1][2] = graph[2][1] = 1;
  graph[0][3] = graph[3][0] = 1;
  graph[3][4] = graph[4][3] = 1;
  graph[4][5] = graph[5][4] = 1;
  graph[3][5] = graph[5][3] = 1;
  graph[4][6] = graph[6][4] = 1;
  graph[5][6] = graph[6][5] = 1;
  graph[5][7] = graph[7][5] = 1;
  graph[6][7] = graph[7][6] = 1;

  printf("Graph created.\n");
  printf("Starting BFS from node 0:\n\n");
  BFS(graph, 0);

  // Creating the DFS graph
  int graph2[NUMBER_OF_VERTICES_DFS][NUMBER_OF_VERTICES_DFS];
  for (unsigned i = 0; i < NUMBER_OF_VERTICES_DFS; ++i) {
    for (unsigned j = 0; j < NUMBER_OF_VERTICES_DFS; ++j) {
      graph2[i][j] = 0;
    }
  }
  graph2[0][1] = 1;
  graph2[0][2] = 1;
  graph2[1][3] = 1;
  graph2[2][1] = 1;
  graph2[3][2] = 1;

  printf("\n\nGraph 2 created.\n");
  printf("Starting DFS from node 0:\n\n");
  DFS(graph2, 0);

  return 0;
}
