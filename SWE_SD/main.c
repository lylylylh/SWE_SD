#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define DISABLE 0
#define ENABLE 1

#define ON 2
#define OFF 3
#define UP 4


int Move_Forward,Move_Backward;
int Cleaner_Command;

typedef struct {
	int Dust_Existence; //1,0
	int* Obstacle_Location; //front, left, right
} Controller;

int Front_Sensor_Interface(){
	int fd = 1;
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

void InitController(Controller *Ctr){
	Ctr->Dust_Existence = Determine_Dust_Existence();
	Ctr->Obstacle_Location = Determine_Obstacle_Location();
	Move_Forward=ENABLE;
	Move_Backward=DISABLE;
	Cleaner_Command=ON;
}

void Turn_Left(){
	printf("Activate Turn Left\n");
}
void Turn_Right(){
	printf("Activate Turn Right\n");
}
void Stop(Controller *Ctr){
	if(!Ctr->Obstacle_Location[1]) {
		Move_Backward=DISABLE;
		Turn_Left();
	}
	else if(!Ctr->Obstacle_Location[2]){
		Move_Backward=DISABLE;
		Turn_Right();
	}
}

void Clean(){
	if(Cleaner_Command==ON) printf("Activate Clean\n\n");
	else if(Cleaner_Command==UP) {
		printf("Activate Power Clean\n");
		Cleaner_Command=ON;
	}
}
int main(void) {
	Controller ctr;

	while (1) {
		srand(time(NULL));
		InitController(&ctr);

		// test code
		printf("Dust : %d\n", ctr.Dust_Existence);
		printf("Front : %d\n", ctr.Obstacle_Location[0]);
		printf("Left : %d\n", ctr.Obstacle_Location[1]);
		printf("Right : %d\n\n", ctr.Obstacle_Location[2]);

		//Find Dust
		if (ctr.Dust_Existence) {
			Cleaner_Command = UP;
			Clean();
		}

		//Detect Obstacle
		if (ctr.Obstacle_Location[0] && !ctr.Obstacle_Location[1]) {
			Move_Forward = DISABLE;
			Cleaner_Command = OFF;
			Turn_Left();
		}
		else if (ctr.Obstacle_Location[0] && ctr.Obstacle_Location[1] && !ctr.Obstacle_Location[2]) {
			Move_Forward = DISABLE;
			Cleaner_Command = OFF;
			Turn_Right();
		}
		else if (ctr.Obstacle_Location[0] && ctr.Obstacle_Location[1] && ctr.Obstacle_Location[2]) {
			Move_Forward = DISABLE;
			Cleaner_Command = OFF;
			Stop(&ctr);
		}

		free(ctr.Obstacle_Location);
	}
	return 0;
}