#include <stdio.h>
#include <stdlib.h>

#include "obstacles.h"


int randint(int a){
	return rand()%a;
}

// Return 1 if line segment (v1---v2) intersects line segment (v3---v4), otherwise return 0
unsigned char linesIntersect(short v1x, short v1y, short v2x, short v2y, short v3x, short v3y, short v4x, short v4y) {
	float uA = ((v4x-v3x)*(v1y-v3y) - (v4y-v3y)*(v1x-v3x)) / (float)(((v4y-v3y)*(v2x-v1x) - (v4x-v3x)*(v2y-v1y)));
	float uB = ((v2x-v1x)*(v1y-v3y) - (v2y-v1y)*(v1x-v3x)) / (float)(((v4y-v3y)*(v2x-v1x) - (v4x-v3x)*(v2y-v1y)));

	// If uA and uB are between 0-1, there is an intersection
	if (uA > 0 && uA < 1 && uB > 0 && uB < 1) 
		return 1;

	return 0;
}



// Create a graph using the numVertices and k parameters of the given environment.
void createGraph(Environment *env) {	
	// init vertices
	env->vertices = (Vertex**)malloc(sizeof(Vertex*)*env->numVertices);
	for(int i = 0 ;i<env->numVertices;i++){
		env->vertices[i] = (Vertex*)malloc(sizeof(Vertex));
		env->vertices[i]->neighbours = NULL;
	}
	// creating vertex in env
	for(int i = 0;i < env->numVertices;i++){
		int tmpX = randint(env->maximumX)-1;
		int tmpY = randint(env->maximumY)-1;
		int flag = 0;
		for(int j = 0;j<env->numObstacles;j++){
			if((tmpX <= env->obstacles[j].x + env->obstacles[j].w) && (tmpX >= env->obstacles[j].x)&&(tmpY <= env->obstacles[j].y)&&(tmpY >= env->obstacles[j].y - env->obstacles[j].h)){
				flag = 1;
				break;
			}
		}
		if(flag == 0){
			env->vertices[i]->x = tmpX;
			env->vertices[i]->y = tmpY;
		}
	}
	// finding the near vertices
	for (int i = 0; i < env->numVertices; i++){
		int dist[env->numVertices];
		int sel[env->k];
		int min_index = -1;
		int min_dist =  __INT_MAX__;
		for(int a = 0;a < env->numVertices;a++){
			dist[a] = (env->vertices[i]->x - env->vertices[a]->x)*(env->vertices[i]->x - env->vertices[a]->x) + (env->vertices[i]->y - env->vertices[a]->y)*(env->vertices[i]->y - env->vertices[a]->y);
			if(dist[a] < min_dist && a != i){
				min_dist = dist[a];
				min_index = a;
			}
		}
		sel[0] = min_index;
		min_dist = __INT_MAX__;
		for(int a = 1 ; a < env->k;a++){
			for(int b = 0;b<env->numVertices;b++){
				if(sel[a-1] != b && dist[b] >= dist[sel[a-1]] && dist[b] < min_dist){
					min_dist = dist[b];
					min_index = b;
				}
			}
			sel[a] = min_index;
			int x1 = env->vertices[i]->x;
			int y1 = env->vertices[i]->y;
			int x2 = env->vertices[sel[a]]->x;
			int y2 = env->vertices[sel[a]]->y;
			for(int b = 0 ;b < env->numObstacles;b++){
				int x3 = env->obstacles[b].x;
				int y3 = env->obstacles[b].y;
				int w = env->obstacles[b].w;
				int h = env->obstacles[b].h;
				if(linesIntersect(x1,y1,x2,y2,x3,y3,x3+w,y3)){
					sel[a] = -1;
				}
				if(linesIntersect(x1,y1,x2,y2,x3,y3,x3,y3+h)){
					sel[a] = -1;
				}
				if(linesIntersect(x1,y1,x2,y2,x3+w,y3+h,x3,y3+h)){
					sel[a] = -1;
				}
				if(linesIntersect(x1,y1,x2,y2,x3+w,y3+h,x3+w,y3)){
					sel[a] = -1;
				}
			}
		}
		env->vertices[i]->neighbours = (Neighbour*)malloc(sizeof(Neighbour));
		Neighbour* head = env->vertices[i]->neighbours;
		for(int a = 0 ;a < env->k;a++){
			if(sel[a]  == -1 ){
				printf("%d",sel[a]);
				a++;
			}
			head->vertex = env->vertices[sel[a]];
			if(a == env->k-1){
				head->next = NULL;
			}else{
				head->next = (Neighbour*)malloc(sizeof(Neighbour));
				head = head->next;
			}
		}
	}
}


// This procedure cleans up everything by creeing all alocated memory
void cleanupEverything(Environment *env) {

	// ...
	// WRITE YOUR CODE HERE
	// ...
	
}


