#include"SList.h"

//	�����ڵ�
SLT* CreatListNode(SLTDateType x)
{
	SLT* newnode = (SLT*)malloc(sizeof(SLT));
	newnode->data = x;
	newnode->next = NULL;

	return newnode;
}

//  ��ӡ
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

//	β��
void SLtPushBack(SLT** pphead, SLTDateType x)
{
	//	��β�ڵ�
	/*SLT* newnode = (SLT*)malloc(sizeof(SLTDataType));
	newnode->data = x;
	newnode->next = NULL; */	// ֱ�ӷ�װ��һ������

	assert(pphead);// ȷ��pphead��Ϊ�գ�Ҳ����&plist������plist����Ϊ��

	SLT* newnode = CreatListNode(x);
	if (*pphead == NULL)
	{
		*pphead = newnode;	// ������
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

//	ͷ��
void SLtPushFront(SLT** pphead, SLTDateType x)
{
	assert(pphead);
	SLT* newnode = CreatListNode(x); // �����½ڵ㣬ֵx�Ѿ�����newnode
	newnode->next = *pphead; // ��ԭ��ͷ�ĵ�ַ�����½ڵ��next
	*pphead = newnode;		//	���½ڵ���Ϊ�µ�ͷ
}

//	βɾ
void SLtPopBack(SLT** pphead)
{
	assert(pphead);
	//1 .ֱ��Ϊ��
	assert(*pphead != NULL);

	//2	.ֻ��һ�����(�ڶ���Ϊ��)
	if ((*pphead)->next == NULL)
	{
		free(*pphead);
		*pphead = NULL;
	}
	//3	.��� >= 3
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

//	ͷɾ
void SLtPopFront(SLT** pphead)
{
	assert(*pphead != NULL);

	SLT* head = (*pphead)->next;
	free(*pphead);
	*pphead = head;
}

//	����
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


//	��pos֮ǰ����
void SListInsert(SLT** pphead, SLT* pos, SLTDateType x)
{
	assert(pphead);
	assert(pos);
	SLT* newnode = CreatListNode(x);//	�����ڵ�x

	if (*pphead == pos)//���pos����ͷ
	{
		//newnode->next = *pphead;	// ֱ�Ӱ��½ڵ��next����ԭ����ͷ
		//*pphead = newnode;			// ���½ڵ�ĵ�ַ������Ϊ�µ�ͷ
		SLtPushFront(pphead, x);	//	ͷ��
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

//	��pos֮�����x
void SListInsertAfter(SLT* pos, SLTDateType x)
{
	assert(pos);
	SLT* newnode = CreatListNode(x);
	newnode->next = pos->next;
	pos->next = newnode;
}

//	ɾ��pos���һ���ڵ�
void SListEraseAfter(SLT* pos)
{
	assert(pos->next != NULL);
	SLT* posPrev = pos->next;
	pos->next = posPrev->next;
	free(posPrev);
}

//	ɾ��pos�ڵ�	O(N)
void SListErase(SLT**pphead,SLT* pos)
{
	if (pos == *pphead)
	{
		//	1.����д��
		/**pphead = pos->next;
		free(pos); 
		pos == NULL;*/
		//	2.����ͷɾ
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

//	��������
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