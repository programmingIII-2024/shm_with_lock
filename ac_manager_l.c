#include <stdio.h>
#include <sys/shm.h>
#include <unistd.h>
#include <pthread.h> // mutex使用

int main(void)
{
	int *balance;	//口座残高
	int shm_id,temp;
	int shm_id_mutex;

	pthread_mutex_t *m_balance;	//口座ロック用mutex
	pthread_mutexattr_t m_balance_attr; //mutexの設定変数

	//mutexの情報を共有メモリでシェア
	shm_id_mutex = shmget(IPC_PRIVATE, sizeof(pthread_mutex_t), IPC_CREAT|0666);
	m_balance = shmat(shm_id_mutex, NULL,0);
	printf("mutex share id = %d\n",shm_id_mutex);

	//mutex設定ファイルの初期化
	pthread_mutexattr_init(&m_balance_attr);

	//mutexをプロセス間通信のロックに使う設定
	pthread_mutexattr_setpshared(&m_balance_attr,PTHREAD_PROCESS_SHARED);

	//mutex初期化
	pthread_mutex_init(m_balance, &m_balance_attr);

	shm_id = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT|0666);

	balance = shmat(shm_id,NULL,0);
	printf("account share id is %d\n",shm_id);

	*balance = 10000;	//初期残高一万円

	while(1)
	{
		sleep(1);

		//データを読み出す前にロック
		pthread_mutex_lock(m_balance);
		temp = *balance;
		sleep(9);
		*balance = temp * 1.01;
		//書き込み後にアンロック
		pthread_mutex_unlock(m_balance);
	}
	return 0;
}