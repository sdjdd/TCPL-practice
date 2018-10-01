#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define BUFSIZE 100
#define MAXOP 100
#define MAXVAL 100
#define NUMBER '0'

int getop(char[]);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);
double fmod(double, double);
void printtop(void);
double gettop(void);
void swaptop(void);
void empty(void);

int sp = 0;
double val[MAXVAL];
char buf[BUFSIZE];
int bufp = 0;

int main() {
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
        switch (type) {
        case NUMBER:
            push(atof(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            op2 = pop();
            push(pop() - op2);
            break;
        case '/':
            op2 = pop();
            if (op2 == 0.0)
                printf("error: zero divisor\n");
            else 
                push(pop() / op2);
            break;
        case '\n':
            printf("\t%.8g\n", pop());
            break;
        case '%':
            op2 = pop();
            push(fmod(pop(), op2));
            break;
        case 's':
            push(sin(pop()));
            break;
        case 'e':
            push(exp(pop()));
            break;
        case 'p':
            op2 = pop();
            push(pow(pop(), op2));
            break;
        default:
            printf("error: unknown command %s\n", s);
        }
    }
    printtop();
    
    return 0;
}

void push(double f) {
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

double pop(void) {
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

void printtop(void) {
    printf("%f\n", gettop());
}

double gettop(void) {
    if (sp > 0)
        return val[sp-1];
    printf("error: stack empty\n");
    return 0.0;
}

void swaptop(void) {
    double t;
    if (sp > 1) {
        t = val[sp-1];
        val[sp-1] = val[sp-2];
        val[sp-2] = t;
    } else {
        printf("error: can't swap stack\n");
    }
}

void empty(void) {
    sp = 0;
}

int getop(char s[]) {
    int i, c;
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if (!isdigit(c) && c != '.')
        return c;
    i = 0;
    if (isdigit(c))
        while (isdigit(s[++i] = c = getch()))
            ;
    if (c == '.')
        while (isdigit(s[++i] = c = getch()))
            ;
    s[i] = '\0';
    if (c != EOF)
        ungetch(c);
    return NUMBER;
}

int getch(void) {
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

double fmod(double a, double b) {
    while ((a -= b) >= 0)
        ;
    return a + b;
}