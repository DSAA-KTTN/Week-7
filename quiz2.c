#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include"jrb.h"
#include"dllist.h"
#define MAX 10
typedef JRB Graph;
Graph createGraph();
void addEdge(Graph graph, int v1, int v2);
int getAdjacentVertices (Graph graph, int v, int*
output);
void dropGraph(Graph graph);
void BFS(Graph graph, int start, int stop);
Graph createGraph(){
    return make_jrb();
}
void addEdge(Graph graph, int v1, int v2){
    JRB node=jrb_find_int(graph,v1);
    JRB node2=jrb_find_int(graph,v2);
    JRB tree;
    if(node==NULL){
        tree = make_jrb();
        jrb_insert_int(graph, v1, new_jval_v(tree));
        jrb_insert_int(tree, v2, new_jval_i(1));
    }else{
        tree = (JRB) jval_v(node->val);
        jrb_insert_int(tree, v2, new_jval_i(1));
    }
    if(node2==NULL){
        tree = make_jrb();
        jrb_insert_int(graph, v2, new_jval_v(tree));
        jrb_insert_int(tree, v1, new_jval_i(1));
    }else{
        tree = (JRB) jval_v(node2->val);
        jrb_insert_int(tree, v1, new_jval_i(1));
    }
}
int getAdjacentVertices (Graph graph, int v, int*
output){
    Graph node, tree;
    node = jrb_find_int(graph, v);
    tree = (JRB) jval_v(node->val);
    int total = 0;
    jrb_traverse(node, tree){
    output[total++] = jval_i(node->key);
    }
    return total;
}
void dropGraph(Graph graph){
    JRB node;
    jrb_traverse(node, graph){
    jrb_free_tree( jval_v(node->val) );
    }
}
void BFS(Graph graph, int start, int stop){
    int *visited=(int*)malloc(MAX*MAX*sizeof(int));
    int u,v;
    if(start>stop) stop=MAX*MAX-1;
    for(u=start;u<=stop;u++) visited[u]=0;
    Dllist node;
    JRB node1,tree;
    Dllist Q=new_dllist();
    dll_append(Q,new_jval_i(start));
    while(!dll_empty(Q)){
        node=dll_first(Q);
        u=jval_i(node->val);
        dll_delete_node(node);
        if(u>stop || u<start) continue;
        if(!visited[u]){
            printf("%4d ",u);
            visited[u]=1;
            node1=jrb_find_int(graph,u);
            jrb_traverse(tree,node1){
                v=jval_v(tree->key);
                if(v>stop || v<start) continue;
                if(!visited[v])
                dll_append(Q,new_jval_i(v));
            }
        }
    }
    free(visited);
}

void DFS(Graph graph, int start, int stop){
    int *visited=(int*)malloc(MAX*MAX*sizeof(int));
    int u,v;
    if(start>stop) stop=MAX*MAX-1;
    for(u=stop;u>=start;u--) visited[u]=0;
    Dllist node;
    JRB node1,tree;
    Dllist Q=new_dllist();
    while(jrb_find_int(graph,stop)==NULL){
        stop--;
    }
    dll_prepend(Q,new_jval_i(stop));
    while(!dll_empty(Q)){
        node=dll_first(Q);
        u=jval_i(node->val);
        dll_delete_node(node);
        if(u>stop || u<start) continue;
        if(!visited[u]){
            printf("%4d ",u);
            visited[u]=1;
            node1=jrb_find_int(graph,u);
            jrb_traverse(tree,node1){
                v=jval_v(tree->key);
                if(v>stop || v<start) continue;
                if(!visited[v])
                dll_prepend(Q,new_jval_i(v));
            }
        }
    }
    free(visited);
}

int main(){
    int size=5,n,i;
    int output[50];
    int m;
    Graph g=createGraph();
    addEdge(g, 0, 1);
    addEdge(g, 1, 2);
    addEdge(g, 1, 3);
    addEdge(g, 2, 3);
    addEdge(g, 2, 4);
    addEdge(g, 4, 5);
    /*m=1;
     n = getAdjacentVertices (g, m, output);
      if (n==0) printf("No adjacent vertices of node 1\n");
      else {
          printf("%d\n",n);
      printf("Adjacent vertices of node %d:",m);
      for (i=0; i<n; i++) printf("%d ", output[i]);
      printf("\n");
     }*/
     printf("\nBFS: start from node 1 to 5 : ");
BFS(g, 1, 5);
printf("\nDFS: start from node 5 downto 1 : ");
DFS(g, 1, 5);
printf("\nBFS: start from node 1 to all : ");
BFS(g, 1, -1);
printf("\nDFS: start from all downto 0 : ");
DFS(g, 0, -1);
printf("\n");
    dropGraph(g);   
}