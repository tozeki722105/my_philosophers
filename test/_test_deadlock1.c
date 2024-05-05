#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
	int				deposit;
	pthread_mutex_t	dep_mutex;
	int				id;
} t_account;

typedef struct {
	t_account	*from;
	t_account	*to;
	int			amount;
} t_args;

t_account make_account(int initial_amount, int id)
{
	t_account nba;	
	nba.deposit = initial_amount;
	pthread_mutex_lock(&(nba.dep_mutex));
	nba.id = id;
	return (nba);
}

t_args make_args(t_account *from, t_account *to, int amount)
{
	t_args	args;
	args.from = from;
	args.to = to;
	args.amount = amount;
	return (args);
}

void *transactions(void *ptr)
{
	t_args *args = (t_args *)ptr;

	pthread_mutex_lock(&(args->from->dep_mutex));
	pthread_mutex_lock(&(args->to->dep_mutex));
	if (args->from->deposit < args->amount) {
		pthread_mutex_unlock(&(args->from->dep_mutex));
		pthread_mutex_unlock(&(args->to->dep_mutex));
		return (NULL);
	}
	args->from->deposit -= args->amount;
	args->to->deposit += args->amount;
	pthread_mutex_unlock(&(args->to->dep_mutex));
	pthread_mutex_unlock(&(args->from->dep_mutex));
	return (NULL);
}

int main(void)
{	
	pthread_t thr1, thr2;
	t_account ba1 = make_account(1000, 1);
	t_account ba2 = make_account(1000, 2);

	t_args arg1 = make_args(&ba1, &ba2, 100);
	t_args arg2 = make_args(&ba2, &ba1, 300);
	
	printf("%d %d\n", ba1.deposit, ba2.deposit);

	pthread_create(&thr1, NULL, transactions, &arg1);
	pthread_create(&thr2, NULL, transactions, &arg2);	

	pthread_join(thr1, NULL);
	pthread_join(thr2, NULL);

	printf("%d %d\n", ba1.deposit, ba2.deposit);
}