//
// Created by lhc456 on 2022/7/10.
//

#ifndef DYNAMIC_ARRAY_GENLIST_H
#define DYNAMIC_ARRAY_GENLIST_H

#include<stdio.h>
#include<string.h>
#include<assert.h>
#include<stdlib.h>

#define AtomType int
typedef enum {
    HEAD, ATOM, CHILDLIST
} ElemTag;

typedef struct GLNode {
    ElemTag tag; //
    union {
        AtomType atom;
        struct GLNode *hp;
    };
    struct GLNode *tp;
} GLNode;

typedef GLNode *GenList; //
void InitGenList(GenList &gl) {
    gl = NULL;
}

void CreateGenList(GenList &gl, char *str) {
    int n = strlen(str);
    char *sub = (char *) malloc(sizeof(char) * (n - 2));
    char *hsub = (char *) malloc(sizeof(char) * (n - 2));
    assert(sub != NULL && hsub != NULL);

    //"1,2,3"
    strncpy(sub, str + 1, n - 2);
    sub[n - 2] = '\0';

    if (gl == NULL) {
        gl = (GLNode *) malloc(sizeof(GLNode));
        assert(gl != NULL);
        gl->tag = HEAD;
        gl->hp = gl->tp = NULL;
    }

    GLNode *p = gl;
    while (strlen(sub) != 0) {
        p = p->tp = (GLNode *) malloc(sizeof(GLNode));
        assert(p != NULL);
        p->hp = p->tp = NULL;

        //"1,2,3"  ==>  "1"  hsub="1", sub="2,3";
        //"(1,2),3,4" ==> hsub="(1,2)" sub="3,4"
        if (sever(sub, hsub)) {
            if (hsub[0] == '(') {
                p->tag = CHILDLIST;
                CreateGenList(p->hp, hsub);
            } else {
                p->tag = ATOM;
                p->atom = atoi(hsub);
            }
        }
    }
}

bool sever(char *sub, char *hsub);

///////////////////////////////////////////////////
void ShowGenList(GenList &gl);

bool GenListEmpty(GenList &gl);

int GenListLength(GenList &gl);

int GenListDepth(GenList &gl);

#endif //DYNAMIC_ARRAY_GENLIST_H
