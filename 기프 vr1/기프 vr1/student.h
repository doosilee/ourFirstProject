#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
char name[20];
long id;
float score;
}STUDENT;

void fuction1();
void fuction2();

int pluse_student();
int change();
int delete_student();
int name(const void *, const void *);
int id(const void *, const void *);
int score(const void *, const void *);