#include"student.h"
int id(void *a, void *b)
{
	STUDENT *temp1, *temp2;
	temp1 = (STUDENT *) a;
	temp2 = (STUDENT *) b;
	return temp1->id - temp2->id;
}