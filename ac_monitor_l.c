#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>

//	第一引数にモニタする口座id
int main(int argc, char *argv[])
{
	int *balance;
	int shm_id;

	shm_id = atoi(argv[1]);
	balance = shmat(shm_id, NULL, 0);

	while(1)
	{
		printf("balance is %d\n",*balance);
		sleep(1);
	}
	
	return 0;
}

