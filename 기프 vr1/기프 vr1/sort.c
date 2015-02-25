#include"student.h"
int score(void *a, void *b)
{
	STUDENT *temp1, *temp2;
	temp1 = (STUDENT *) a;
	temp2 = (STUDENT *) b;
	return temp1->score - temp2->score;
}

int name(void *a, void *b)
{
	STUDENT *temp1, *temp2;
	temp1 = (STUDENT *) a;
	temp2 = (STUDENT *) b;
	return strcmp(temp1->name, temp2->name);
}

int id(void *a, void *b)
{
	STUDENT *temp1, *temp2;
	temp1 = (STUDENT *) a;
	temp2 = (STUDENT *) b;
	return temp1->id - temp2->id;
}