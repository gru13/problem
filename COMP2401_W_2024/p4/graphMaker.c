#include <stdio.h>
#include <stdlib.h>

#include "obstacles.h"


// Return 1 if line segment (v1---v2) intersects line segment (v3---v4), otherwise return 0
unsigned char linesIntersect(short v1x, short v1y, short v2x, short v2y, short v3x, short v3y, short v4x, short v4y) {
	float uA = ((v4x-v3x)*(v1y-v3y) - (v4y-v3y)*(v1x-v3x)) / (float)(((v4y-v3y)*(v2x-v1x) - (v4x-v3x)*(v2y-v1y)));
	float uB = ((v2x-v1x)*(v1y-v3y) - (v2y-v1y)*(v1x-v3x)) / (float)(((v4y-v3y)*(v2x-v1x) - (v4x-v3x)*(v2y-v1y)));

	// If uA and uB are between 0-1, there is an intersection
	if (uA > 0 && uA < 1 && uB > 0 && uB < 1)
		return 1;

	return 0;
}

// function for distance calculation
int dista(short a,short b,short c,short d){return (a-c)*(a-c) + (b-d)*(b-d);}

// Create a graph using the numVertices and k parameters of the given environment.
void createGraph(Environment *env) {
	env->vertices = (Vertex**)malloc(sizeof(Vertex*)*env->numVertices);
	for (int i = 0; i < env->numVertices; i++){
		env->vertices[i] = (Vertex*)malloc(sizeof(Vertex));
		reapt:
			env->vertices[i]->x = rand()%env->maximumX;
			env->vertices[i]->y = rand()%env->maximumY;
			for(int j = 0;j<env->numObstacles;j++){if((env->vertices[i]->x <= env->obstacles[j].x + env->obstacles[j].w) && (env->vertices[i]->x >= env->obstacles[j].x)&&(env->vertices[i]->y <= env->obstacles[j].y)&&(env->vertices[i]->y >= env->obstacles[j].y - env->obstacles[j].h)){goto reapt;}}
		env->vertices[i]->neighbours = (Neighbour*)malloc(sizeof(Neighbour));
		env->vertices[i]->neighbours->vertex = env->vertices[i];
	}
	for(int i = 0 ; i < env->numVertices;i++){
		short x = env->vertices[i]->x;
		short y = env->vertices[i]->y;
		int dist[env->numVertices],sel[env->k],min_d = __INT_MAX__,min_i=-1;
		for (int j = 0; j < env->numVertices; j++){
			if(i == j){dist[j] =-1;continue;}
			short a = env->vertices[j]->x;
			short b = env->vertices[j]->y;
			int flag = 0;
			for (int o = 0; o < env->numObstacles; o++){
				Obstacle ob = env->obstacles[o];
				if(linesIntersect(x,y,a,b,ob.x,ob.y,ob.x+ob.w,ob.y) == (unsigned char)1){flag = 1;dist[j] = -1;}
				if(linesIntersect(x,y,a,b,ob.x,ob.y,ob.x,ob.y+ob.h) == (unsigned char)1){flag = 1;dist[j] = -1;}
				if(linesIntersect(x,y,a,b,ob.x+ob.w,ob.y+ob.h,ob.x,ob.y+ob.h) == (unsigned char)1){flag = 1;dist[j] = -1;}
				if(linesIntersect(x,y,a,b,ob.x+ob.w,ob.y+ob.h,ob.x+ob.w,ob.y) == (unsigned char)1){flag = 1;dist[j] = -1;}
			}
			if(flag == 1){continue;}
			dist[j] = dista(x,y,env->vertices[j]->x,env->vertices[j]->y);
			if(dist[j] < min_d){min_d = dist[j];min_i = j;}
		}
		sel[0] = min_i;
		for(int a = 1;a<env->k;a++){
			min_d = __INT_MAX__;
			min_i= -1;
			for(int b = 0;b<env->numVertices;b++){
				if(dist[b] != -1 && dist[b] < min_d && dist[b] > dist[sel[a-1]]){
					min_d = dist[b];
					min_i = b;
				} 
			}
			sel[a] = min_i;			
		}
		Neighbour* head = env->vertices[i]->neighbours;
		for(int l = 0;l<env->k;l++){
			if(sel[l] == -1){continue;}
			head->next = (Neighbour*)malloc(sizeof(Neighbour));
			head->next->vertex = env->vertices[sel[l]];
			head->next->next = NULL;
			head = head->next;
		}
	}
}
// This procedure cleans up everything by creeing all alocated memory
void cleanupEverything(Environment *env) {
	for (int i = 0; i < env->numVertices; i++) {
        free(env->vertices[i]->neighbours);
        free(env->vertices[i]);
    }
    free(env->vertices);
    free(env->obstacles);
}


