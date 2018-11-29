
#define VERSION "1.4.2"

#define PROG_NAME "MITRE_SFR" /* for DOS */

#ifndef M_PI
#define M_PI  3.14159265358979323846
#endif

extern char *strerror(int);

#define TOP 0
#define BOTTOM 2
#define LEFT 1
#define RIGHT 3
#define UNKNOWN 255

#define GET_COORD_PAIR(a,b,c)                                         \
{                                                                       \
                int i;                                                  \
                scanf("%u",a);                                          \
                while(!isdigit(i=getchar())){}                           \
                ungetc(i,stdin);                                        \
                scanf("%u",b);                                          \
                while(!isdigit(i=getchar())){}                           \
                ungetc(i,stdin);                                        \
                scanf("%u",c);                                          \
}

#define GET_INT_PAIR(a,b)                                             \
{                                                                       \
                int i;                                                  \
                scanf("%d",a);                                          \
                while(!isdigit(i=getchar())){}                           \
                ungetc(i,stdin);                                        \
                scanf("%d",b);                                          \
}

#define GET_FLOAT_PAIR(a,b)                                             \
{                                                                       \
                int i;                                                  \
                scanf("%f",a);                                          \
                while(!isdigit(i=getchar())){}                           \
                ungetc(i,stdin);                                        \
                scanf("%f",b);                                          \
}

#define MTFPRINT(a)                                                     \
{                                                                       \
        fprintf(stdout,a);                                              \
        fprintf(g_mtfout,a);                                            \
}

#define MTFPRINT2(a,b)                                                  \
{                                                                       \
        fprintf(stdout,a,b);                                            \
        fprintf(g_mtfout,a,b);                                          \
}

#define MTFPRINT3(a,b,c)                                                \
{                                                                       \
        fprintf(stdout,a,b,c);                                          \
        fprintf(g_mtfout,a,b,c);                                        \
}

#define MTFPRINT4(a,b,c,d)                                              \
{                                                                       \
        fprintf(stdout,a,b,c,d);                                        \
        fprintf(g_mtfout,a,b,c,d);                                      \
}

#define MTFPRINT5(a,b,c,d,e)                                            \
{                                                                       \
        fprintf(stdout,a,b,c,d,e);                                      \
        fprintf(g_mtfout,a,b,c,d,e);                                    \
}

#define MTFPRINT6(a,b,c,d,e,f)                                          \
{                                                                       \
        fprintf(stdout,a,b,c,d,e,f);                                    \
        fprintf(g_mtfout,a,b,c,d,e,f);                                  \
}

#define MTFPRINT7(a,b,c,d,e,f,g)                                        \
{                                                                       \
        fprintf(stdout,a,b,c,d,e,f,g);                                  \
        fprintf(g_mtfout,a,b,c,d,e,f,g);                                \
}

#define MTFPRINT8(a,b,c,d,e,f,g,h)                                      \
{                                                                       \
        fprintf(stdout,a,b,c,d,e,f,g,h);                                \
        fprintf(g_mtfout,a,b,c,d,e,f,g,h);                              \
}

#define MTFPRINT9(a,b,c,d,e,f,g,h,i)                                    \
{                                                                       \
        fprintf(stdout,a,b,c,d,e,f,g,h,i);                              \
        fprintf(g_mtfout,a,b,c,d,e,f,g,h,i);                            \
}

#define MTFPRINT10(a,b,c,d,e,f,g,h,i,j)                                 \
{                                                                       \
        fprintf(stdout,a,b,c,d,e,f,g,h,i,j);                            \
        fprintf(g_mtfout,a,b,c,d,e,f,g,h,i,j);                          \
}

#define MTFPRINT12(a,b,c,d,e,f,g,h,i,j,k,l)                             \
{                                                                       \
        fprintf(stdout,a,b,c,d,e,f,g,h,i,j,k,l);                        \
        fprintf(g_mtfout,a,b,c,d,e,f,g,h,i,j,k,l);                      \
}
typedef char TIFF;

#define MTFOUTNAME "SFROUT.txt"


#define MAX_PROBLEMS 60
#define MAX_LINE_LENGTH 132




