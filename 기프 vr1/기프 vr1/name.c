#include"student.h"

int name(void *a, void *b)
{
	STUDENT *temp1, *temp2;
	temp1 = (STUDENT *) a;
	temp2 = (STUDENT *) b;
	return strcmp(temp1->name, temp2->name);
}