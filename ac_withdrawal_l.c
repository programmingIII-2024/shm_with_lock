#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <pthread.h> //mutex使用

// 第一引数=口座番号(共有メモリID)、第二引数=mutex共有id、第三引数=入出金額
int main(int argc, char *argv[])
{
	int *balance;	//口座残高
	int shm_id;
	int now;
	int difference;	//残高増減値
	int shm_id_mutex;

	pthread_mutex_t *m_balance;

	//mutexの情報を共有メモリでシェア
	shm_id_mutex = atoi(argv[2]);
	m_balance = shmat(shm_id_mutex,NULL,0);

	shm_id = atoi(argv[1]);
	difference = atoi(argv[3]);


	balance = shmat(shm_id,NULL,0);
	
	//データ読み込み前にロック
	pthread_mutex_lock(m_balance);
	now = *balance;
	*balance = now + difference;
	//書き込み後にアンロック
	pthread_mutex_unlock(m_balance);

	printf("%d円入金しました。\n",difference);

	return 0;
}


