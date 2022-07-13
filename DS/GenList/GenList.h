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


bool sever(char *sub, char *hsub) {
    if (*sub == '\0' || strcmp(sub, "()") == 0) {
        hsub[0] = '\0';
        return true;
    }
    int n = strlen(sub);
    int i = 0;
    char ch = sub[0];
    int k = 0;
    while (i < n && (ch != ',' || k != 0)) {
        if (ch == '(')
            k++;
        else if (ch == ')')
            k--;
        i++;
        ch = sub[i];
    }
    if (i < n) {
        sub[i] = '\0';
        strcpy(hsub, sub);
        strcpy(sub, sub + i + 1);
    } else if (k != 0)
        return false;
    else {
        strcpy(hsub, sub);
        sub[0] = '\0';
    }

    return true;

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

void ShowGenList(GenList &gl) {
    GLNode *p = gl->tp;
    printf("(");
    while (p != NULL) {
        if (p->tag == ATOM) {
            printf("%d", p->atom);
            if (p->tp != NULL)
                printf(",");
            p = p->tp;
        } else if (p->tag == CHILDLIST) {
            ShowGenList(p->hp);
            p = p->tp;
        }
    }
    printf("),");
}


bool GenListEmpty(GenList &gl) {
    return gl->tp == NULL;
}

int GenListLength(GenList &gl) {

    int length = 0;
    GLNode *p = gl->tp;
    while (p != NULL) {
        length++;
        p = p->tp;
    }
    return length;
}

int GenListDepth(GenList &gl) {
    if (gl->tp == NULL)
        return 1;
    GLNode *p = gl->tp;
    int maxdepth = 0;
    int dep;

    while (p != NULL) {
        if (p->tag == CHILDLIST) {
            dep = GenListDepth(p->hp->tp);
            if (dep > maxdepth)
                maxdepth = dep;
        }
        p = p->tp;
    }
    return maxdepth + 1;
}

#endif //DYNAMIC_ARRAY_GENLIST_H
