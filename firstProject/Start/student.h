#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct {
char name[20];
char image_url[100];
long id;
float score;
}STUDENT;

void studentDB();
void userInterface1();
void userInterface2();
void attendanceBook();

int pluse_student();
int change_student();
int delete_student();
int name(const void *, const void *);
int id(const void *, const void *);
int score(const void *, const void *);