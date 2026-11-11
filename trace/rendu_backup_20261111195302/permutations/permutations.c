
////1. 연결리스트 구조체 필요, 큐 구조체 필요, is_empty, enqueue, dequeue

////2. 알파벳이 들어오면 이걸 온전히 받아내는 코드

////3. 최초에 큐에 하나씩 넣어주는 코드

////4. 큐를 꺼내보며 출력하고 종료할지, 아니면 아직 안사용한 문자를 하나씩 더해서 큐에 집어널을지 결정하는 코드

//#include <stdio.h>
//#include <stdlib.h>

//typedef struct s_node
//{
//	char	key[27];
//	struct s_node	*next;
//}	t_node;

//typedef struct s_queue
//{
//	struct s_node	*front;
//	struct s_node	*rear;
//	int	size;
//}	t_queue;

//int	queue_is_empty(t_queue *q)
//{
//	if (q->size == 0)
//		return (1);
//	return (0);
//}

//void	enqueue(t_queue *q, t_node *new)
//{
//	if(q->front == NULL)
//	{
//		q->front = new;
//		q->rear = new;
//	}
//	else
//	{
//		q->rear->next = new;
//		q->rear = new;
//	}
//	(q->size)++;
//}

//t_node	*dequeue(t_queue *q)
//{
//	t_node	*new;

//	if(q->rear == q->front)
//	{
//		new = q->rear;
//		q->front = NULL;
//		q->rear = NULL;
//	}
//	else
//	{
//		new = q->front;
//		q->front = q->front->next;
//		new->next = NULL;
//	}
//	(q->size)--;
//	return (new);
//}

//void	clear(t_queue *q)
//{
//	while(q->size > 0)
//	{
//		free(dequeue(q));
//	}
//}

//int main(int argc, char **argv)
//{
//	if (argc != 2 )
//		return 1;

//	char	*s = argv[1];
//	t_queue	q;
//	q.front = NULL;
//	q.rear = NULL;
//	q.size = 0;
//	for (int i=0; s[i] != 0; i++)
//	{
//		t_node *new = malloc(sizeof(t_node));
//		if (!new)
//		{
//			clear(&q);
//			return (1);
//		}
//		new->next = NULL;
//		for (int i = 0; i < 27 ; i++)
//			new->key[i] = 0;
//		new->key[0] = s[i];
//		enqueue(&q, new);
//	}
//	while(queue_is_empty(&q))
//	{
//		t_node *new = dequeue(&q);

//		for (int i = 0; s[i] != 0; i++)
//		{
//			for (int j = 0; new->key[j]; j++)
//			{
//				if (s[i] )
//			}
//		}
//	}
//}

#include <stdio.h>
#include <stdlib.h>

void	recurs(char *src, char *buf, int *used, int pos, int n)
{
	if (n == pos)
	{
		puts(buf);
		return ;
	}

	for (int i = 0; i < n; i++)
	{
		if (used[i] == 0)
		{
			buf[pos] = src[i];
			used[i] = 1;
			recurs(src, buf, used, pos + 1, n);
			buf[pos] = 0;
			used[i] = 0;
		}
	}
}

int main(int argc, char **argv)
{
	if (argc != 2 )
		return 1;

	int	sorting[256] = {0};
	int	cnt;
	for (cnt = 0; argv[1][cnt]; cnt++)
		sorting[(int)argv[1][cnt]] = 1;

	char	*src = calloc(sizeof(char), cnt + 1);
	if (!src)
		return (1);
	
	int j = 0;
	for (int i = 0; i < 256; i++)
	{
		if (sorting[i] == 1)
			src[j++] = i;
	}
	int	*used = calloc(sizeof(int), cnt);
	if (!used)
	{
		free(src);
		return (1);
	}
	char	*buff = calloc(sizeof(char), cnt + 1);
	if (!buff)
	{
		free(src);
		free(used);
		return (1);
	}
	recurs(src, buff, used, 0, cnt);
	free(src);
	free(buff);
	free(used);
}