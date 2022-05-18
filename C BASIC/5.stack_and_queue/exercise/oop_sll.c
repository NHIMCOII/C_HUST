#include"../../cgen/OOP/Sll.c"
#include"../../cgen/core.h"
int main(){
    SllG list = New(SllG);
    list->PushBack(list,(gtype){.i=100});
    list->PushBack(list,(gtype){.i=200});
    list->PushBack(list,(gtype){.i=100});
    list->PushFront(list,(gtype){.i=60});
    list->PPrint(list);
    return 0;
}