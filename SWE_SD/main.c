#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>

typedef struct {
	int Dust_Existence; // true, false 1,0
	int* Obstacle_Location; //front, left, right
} Controller;

int Front_Sensor_Interface(){
	int fd = rand() % 2;
	return fd;
}

int Left_Sensor_Interface(){
	int ld = rand() % 2;
	return ld;
}

int Right_Sensor_Interface(){
	int rd = rand() % 2;
	return rd;
}

int Dust_Sensor_Interface() {
	int d = rand() % 2;
	return d;
}

int* Determine_Obstacle_Location() {
	int* FLR = (int*)malloc(3 * sizeof(int));
	FLR[0] = Front_Sensor_Interface();
	FLR[1] = Left_Sensor_Interface();
	FLR[2] = Right_Sensor_Interface();		
	return FLR;
}

int Determine_Dust_Existence() {
	return Dust_Sensor_Interface();
}

int main(void) {
	Controller ctr;
	while (1) {
		srand(time(NULL));
		ctr.Dust_Existence = Determine_Dust_Existence();
		ctr.Obstacle_Location = Determine_Obstacle_Location();
		// test code
		printf("Dust : %d\n", ctr.Dust_Existence);
		printf("Front : %d\n", ctr.Obstacle_Location[0]);
		printf("Left : %d\n", ctr.Obstacle_Location[1]);
		printf("Right : %d\n\n", ctr.Obstacle_Location[2]);
		free(ctr.Obstacle_Location);
		Sleep(1000);
	}
	return 0;
}