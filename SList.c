#include"SList.h"

//	创建节点
SLT* CreatListNode(SLTDateType x)
{
	SLT* newnode = (SLT*)malloc(sizeof(SLT));
	newnode->data = x;
	newnode->next = NULL;

	return newnode;
}

//  打印
void SLtPrint(SLT* phead)
{
	SLT* cur = phead;
	while (cur != NULL)
	{
		printf("%d ", cur->data);
		cur = cur->next;
	}
	printf("NULL\n");
}

//	尾插
void SLtPushBack(SLT** pphead, SLTDateType x)
{
	//	找尾节点
	/*SLT* newnode = (SLT*)malloc(sizeof(SLTDataType));
	newnode->data = x;
	newnode->next = NULL; */	// 直接封装成一个函数

	assert(pphead);// 确保pphead不为空，也就是&plist，不过plist可能为空

	SLT* newnode = CreatListNode(x);
	if (*pphead == NULL)
	{
		*pphead = newnode;	// 解引用
	}
	else
	{
		SLT* tail = *pphead;
		while (tail->next != NULL)
		{
			tail = tail->next;
		}
		tail->next = newnode;
	}
}

//	头插
void SLtPushFront(SLT** pphead, SLTDateType x)
{
	assert(pphead);
	SLT* newnode = CreatListNode(x); // 创建新节点，值x已经传入newnode
	newnode->next = *pphead; // 将原来头的地址放入新节点的next
	*pphead = newnode;		//	将新节点作为新的头
}

//	尾删
void SLtPopBack(SLT** pphead)
{
	assert(pphead);
	//1 .直接为空
	assert(*pphead != NULL);

	//2	.只有一个结点(第二个为空)
	if ((*pphead)->next == NULL)
	{
		free(*pphead);
		*pphead = NULL;
	}
	//3	.结点 >= 3
	else
	{
		SLT* tail = *pphead;
		SLT* prev = NULL;
		while (tail->next != NULL)
		{
			prev = tail;
			tail = tail->next;
		}
		free(tail);
		tail = NULL;
		prev->next = NULL;

		//SLT* tail = *pphead;
		//while (tail->next->next)
		//{
		//	tail = tail->next;
		//}
		//free(tail->next);
		//tail->next = NULL;
	}
}

//	头删
void SLtPopFront(SLT** pphead)
{
	assert(*pphead != NULL);

	SLT* head = (*pphead)->next;
	free(*pphead);
	*pphead = head;
}

//	查找
SLT* SListFind(SLT* phead, SLTDateType x)
{
	SLT* cur = phead;
	while (cur)
	{
		if (cur->data == x)
		{
			return cur;
		}
		else
		{
			cur = cur->next;
		}
	}
	return NULL;
}


//	在pos之前插入
void SListInsert(SLT** pphead, SLT* pos, SLTDateType x)
{
	assert(pphead);
	assert(pos);
	SLT* newnode = CreatListNode(x);//	创建节点x

	if (*pphead == pos)//如果pos等于头
	{
		//newnode->next = *pphead;	// 直接把新节点的next存入原来的头
		//*pphead = newnode;			// 把新节点的地址放入作为新的头
		SLtPushFront(pphead, x);	//	头插
	}
	else
	{
		SLT* posPrev = *pphead;
		while (posPrev->next != pos)
		{
			posPrev = posPrev->next;
		}
		posPrev->next = newnode;
		newnode->next = pos;
	}
}

//	在pos之后插入x
void SListInsertAfter(SLT* pos, SLTDateType x)
{
	assert(pos);
	SLT* newnode = CreatListNode(x);
	newnode->next = pos->next;
	pos->next = newnode;
}

//	删除pos后的一个节点
void SListEraseAfter(SLT* pos)
{
	assert(pos->next != NULL);
	SLT* posPrev = pos->next;
	pos->next = posPrev->next;
	free(posPrev);
}

//	删除pos节点	O(N)
void SListErase(SLT**pphead,SLT* pos)
{
	if (pos == *pphead)
	{
		//	1.正常写法
		/**pphead = pos->next;
		free(pos); 
		pos == NULL;*/
		//	2.调用头删
		SLtPopFront(pphead);
	}
	else
	{
		SLT* posPrev = *pphead;
		while((posPrev)->next != pos)
		{
			posPrev = posPrev->next;
		}
		posPrev->next = pos->next;
		free(pos);
	}
}

//	销毁链表
void SListDestory(SLT** pphead)
{
	SLT* cur = *pphead;
	while (cur)
	{
		SLT* next = cur->next;
		free(cur);
		cur = next;
	}
	*pphead == NULL;
}