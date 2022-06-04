#include <iostream>

using namespace std;

int main(void) {
	int num;
	
	printf("enter : ");
	scanf("%d",&num);
	
	int matrix[num][num];
	
	printf("\n\n");
	for (int i =0; i<num; i++) {
		for (int j=0; j<num; j++) {
			matrix[i][j] = 0;
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
}
