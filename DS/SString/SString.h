#ifndef __SSTRING_H__
#define __SSTRING_H__

#include<stdio.h>
#include<string.h>

#define MAXSTRLEN 20
#define u_char unsigned char

typedef u_char SString[MAXSTRLEN + 1];

void InitString(SString S) {
    S[0] = '\0';
}

void PrintString(SString S) {
    printf("%s\n", S);
}


void StrAssign(SString S, char *str) {
    int len = strlen(str);
    for (int i = 0; i < len; ++i) {
        S[i] = str[i];
    }
    S[len] = '\0';
}

int StrLength(SString S) {
    int len = 0;
    while (*S != '\0') {
        len++;
        S++;
    }
    return len;
}

void StrCopy(SString S, SString T) {
    int len = StrLength(T);
    for (int i = 0; i < len; ++i) {
        S[i] = T[i];
    }
    S[len] = '\0';
}

bool StrEmpty(SString S) {
    return S[0] == '\0';
}


int StrCompare(SString S, SString T) {
    int result = 0;
    while (*S != '\0' || *T != '\0') {
        result = *S - *T;
        if (result != 0)
            break;
        S++;
        T++;
    }
    if (result > 0)
        result = 1;
    else if (result < 0)
        result = -1;
    return result;

}


void StrConcat(SString T, SString s1, SString s2) {
    int len1 = StrLength(s1);
    int len2 = StrLength(s2);

    if (len1 + len2 <= MAXSTRLEN) {
        for (int i = 0; i < len1; ++i) {
            T[i] = s1[i];
        }
        for (int j = 0; j < len2; ++j) {
            T[i + j] = s2[j];
        }
        T[len1 + len2] = '\0';
    } else if (len1 < MAXSTRLEN) {
        int i = 0;
        for (i = 0; i < len1; ++i) {
            T[i] = s1[i];
        }
        for (int j = 0; j < MAXSTRLEN - len1; ++j) {
            T[i + j] = s2[j];
        }
        T[MAXSTRLEN] = '\0';
    } else {
        for (int i = 0; i < len1; ++i) {
            T[i] = s1[i];
        }
        T[MAXSTRLEN] = '\0';
    }
}

void SubString(SString S, SString sub, int pos, int len) {
    int s_len = StrLength(S);
    if (pos < 0 || pos >= s_len || len < 0 || len > s_len)

        return;
    int j = pos;
    for (int i = 0; i < len; ++i) {
        sub[i] = S[j + i];
    }
    sub[len] = '\0';
}

void StrInsert(SString S, int pos, SString T) {
    int s_len = StrLength(S);
    int t_len = StrLength(T);
    int i;
    if (s_len + t_len <= MAXSTRLEN) {
        for (int i = s_len - 1; i >= pos; --i) {
            S[i + t_len] = S[i];
        }

        int j = pos;
        for (i = 0; i < t_len; ++i) {
            S[j + i] = T[i];
        }
        S[s_len + t_len] = '\0';
    } else if (s_len < MAXSTRLEN) {
        t_len = MAXSTRLEN - s_len;
        for (int i = s_len - 1; i >= pos; --i) {
            S[i + t_len] = S[i];
        }

        int j = pos;
        for (i = 0; i < t_len; ++i) {
            S[j + i] = T[i];
        }
        S[s_len + t_len] = '\0';
    }

}

void StrDelete(SString S, int pos, int len) {
    int s_len = StrLength(S);
    for (int i = pos; i < s_len; ++i) {
        S[i] = S[i + len];
    }
    S[s_len - len] = '\0';
}


void StrClear(SString S);

/////////////////////////////////////////////////////////
int StrIndex(SString S, SString T, int pos);

void StrReplace(SString S, SString T, SString V);

#endif //__SSTRING_H__