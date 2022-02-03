// Jakub Lukasiewicz - 3

// vim: fen

import java.util.Scanner;

// Java doesn't support primitive types in generics
// Java in genetic class: " error: generic array creation "
// I hate this language...

// And this code is a mess... from start to finish...

class StackString {
    static final int MAX = 1000;
    int top;
    String a[] = new String[MAX];

    StackString() {
        top = -1;
    };

    boolean nonEmpty() {
        return (top >= 0);
    }

    void push(String x) {
        top++;
        a[top] = x;
    }

    String pop() {
        if (nonEmpty()) {
            String x = a[top];
            top--;
            return x;
        } else {
            return "";
        }
    }

    String peek() {
        return a[top];
    }
}

class StackChar {
    static final int MAX = 1000;
    int top;
    char a[] = new char[MAX];

    StackChar() {
        top = -1;
    };

    boolean nonEmpty() {
        return (top >= 0);
    }

    void push(char x) {
        top++;
        a[top] = x;
    }

    char pop() {
        if (nonEmpty()) {
            char x = a[top];
            top--;
            return x;
        } else {
            return ' ';
        }
    }

    char peek() {
        return a[top];
    }
}

class StackInt {
    static final int MAX = 1000;
    int top;
    int a[] = new int[MAX];

    StackInt() {
        top = -1;
    };

    boolean nonEmpty() {
        return (top >= 0);
    }

    void push(int x) {
        top++;
        a[top] = x;
    }

    int pop() {
        if (nonEmpty()) {
            int x = a[top];
            top--;
            return x;
        } else {
            return 0;
        }
    }

    int peek() {
        if (nonEmpty()) {
            return a[top];
        } else {
            return 0;
        }
    }
}

class Source {

    public static String pr_ln(char x) {
        if (x == '=') {
            return "0R";
        } else if ( x == '<' || x == '>' ) {
            return "1L";
        } else if ( x == '+' || x == '-' ) {
            return "2L";
        } else if ( x == '*' || x == '/' || x == '%' ) {
            return "3L";
        } else if ( x == '^' ) {
            return "4R";
        } else if ( x == '~' ) {
            return "5R";
        }
        return "";
    }

    public static int priority(char x) {
        if (x == '=') {
            return 0;
        } else if ( x == '<' || x == '>' ) {
            return 1;
        } else if ( x == '+' || x == '-' ) {
            return 2;
        } else if ( x == '*' || x == '/' || x == '%' ) {
            return 3;
        } else if ( x == '^' ) {
            return 4;
        } else if ( x == '~' ) {
            return 5;
        } else {
            return 6;
        }
    }

    public static String removeInvalidChars(String str, boolean isINF) {
        String out = "";
        for (int i = 0; i < str.length(); i++) {
            char x = str.charAt(i);
            if (x >= 'a' && x <= 'z') {
                out += x;
            } else if (isINF && (x == '(' || x == ')')) {
                out += x;
            } else {
                switch (x) {
                    case '=':
                    case '<':
                    case '>':
                    case '+':
                    case '-':
                    case '*':
                    case '/':
                    case '%':
                    case '^':
                    case '~':
                        out += x;
                        break;
                }
            }
        }
        return out;
    }

    public static String validateINF(String str) {
        str = removeInvalidChars(str, true);
        int p = 0;
        int state = 0;
        char x = '='; // this equal sign is just a dummy value
        for (int i = 0; i < str.length(); i++) {
            x = str.charAt(i);
            if (state == 0) {
                if (x >= 'a' && x <= 'z') {
                    state = 1;
                } else if (x == '~') {
                    state = 2;
                } else if (x == '(') {
                    if (p < 0) {
                        str = "error";
                    } else {
                        p++;
                    }
                } else {
                    str = "error";
                }
            } else if (state == 1) {
                if (x != ')') {
                    switch (x) {
                        case '=':
                        case '<':
                        case '>':
                        case '+':
                        case '-':
                        case '*':
                        case '/':
                        case '%':
                        case '^':
                            state = 0;
                            break;
                        default:
                            str = "error";
                            break;
                    }
                } else {
                    p--;
                }
            } else if (state == 2) {
                if (x != '~') {
                    if (x == '(') {
                        state = 0;
                        if (p < 0) {
                            str = "error";
                        } else {
                            p++;
                        }
                    } else if (x >= 'a' && x <= 'z') {
                        state = 1;
                    } else {
                        str = "error";
                    }
                }
            }
            if (str == "error") {
                break;
            }
        }

        if (p == 0) {
            switch (x) {
                case '=':
                case '<':
                case '>':
                case '+':
                case '-':
                case '*':
                case '/':
                case '%':
                case '^':
                case '~':
                    return "error";
            }
            return str;
        } else {
            return "error";
        }

    }

    public static String validateONP(String str) {
        str = removeInvalidChars(str, false);
        int p = 0;
        for (int i = 0; i < str.length(); i++) {
            char x = str.charAt(i);
            if (x >= 'a' && x <= 'z') {
                p++;
            } else if (x != '~') {
                p--;
            }
        }
        if (p == 1) {
            return str;
        } else {
            return "error";
        }
    }

    public static int checkValid(String str) {
        int p = 0;
        for (int i = 0; i < str.length(); i++) {
            char x = str.charAt(i);
            if (x >= 'a' && x <= 'z') {
                p++;
            } else {
                switch (x) {
                    case '=':
                    case '<':
                    case '>':
                    case '+':
                    case '-':
                    case '*':
                    case '/':
                    case '%':
                    case '^':
                    case '~':
                        p++;
                        break;
                }
            }
        }
        return p;
    }

    public static String toINF(String str) {
        StackString stack = new StackString();
        StackInt priorities = new StackInt();

        String temp = "";

        for (int i = 0; i < str.length(); i++) {
            char x = str.charAt(i);
            if (x >= 'a' && x <= 'z') {
                stack.push(""+x);
                priorities.push(priority(x));
            } else {
                temp = "";

                if (x != '~') {
                    if (priorities.peek() <= priority(x) && x != '=') {
                        if (priorities.peek() == priority(x) && x == '^') {
                            temp = stack.pop();
                        } else {
                            temp = "(" + stack.pop() + ")";
                        }
                    } else {
                        temp = stack.pop();
                    }

                    priorities.pop();

                    if (priorities.peek() < priority(x)) {
                        temp = "(" + stack.pop() + ")" + x + temp;
                    } else {
                        temp = stack.pop() + x + temp;
                    }

                    priorities.pop();
                } else {
                    if (priorities.peek() < priority(x)) {
                        temp = x + "(" + stack.pop() + ")";
                    } else {
                        temp = x + stack.pop();
                    }

                    priorities.pop();
                }

                stack.push(temp);
                priorities.push(priority(x));
            }
        }

        String out = stack.pop();
        if (checkValid(str) == checkValid(out)) {
            return out;
        } else {
            return "error";
        }
    }

    public static String toONP(String str) {
        String out = "";
        StackChar stack = new StackChar();

        for (int i = 0; i < str.length(); i++) {
            char el = str.charAt(i);
            if (el >= 'a' && el <= 'z') {
                out += el;
            } else {
                if (el == '(') {
                    stack.push(el);
                } else if (el == ')') {
                    if (stack.nonEmpty() ) {
                        char x = stack.pop();
                        while (x != '(') {
                            out += x;
                            x = stack.pop();
                        }
                    }
                } else {
                    if (stack.nonEmpty()) {
                        char op2 = stack.peek();
                        String p1 = pr_ln(el);
                        String p2 = pr_ln(op2);

                        while (p2 != "" && ((p1.charAt(1) == 'L' && p2.charAt(0) >= p1.charAt(0)) || (p1.charAt(1) == 'R' && p2.charAt(0) > p1.charAt(0)))) {
                            out += stack.pop();
                            if (stack.nonEmpty()) {
                                op2 = stack.peek();
                                p2  = pr_ln(op2);
                            } else {
                                break;
                            }
                        }
                    }
                    stack.push(el);
                }
            }
        }

        while (stack.nonEmpty()) {
            out += stack.pop();
        }

        return out;
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int E = Integer.parseInt(in.nextLine());
        for (int e = 0; e < E; e++) {
            String str = in.nextLine();
            String prefix = str.substring(0, 5);
            str = str.replace(prefix, "");

            if (prefix.equals("ONP: ")) {
                prefix = "INF: ";
                str = validateONP(str);
                if (str != "error") {
                    str = toINF(str);
                }
            } else {
                prefix = "ONP: ";
                str = validateINF(str);
                if (str != "error") {
                    str = toONP(str);
                }
            }

            System.out.println(prefix + str);
        }
    }
}

/* INPUT
INF: a+b+(~a-a)
INF: a+b+(~a-a)
INF: x=~~a+b*c
INF: t = ~ a < x < ~b
INF: ~a-~~b<c+d&!p|!!q
INF: a^b*c-d<xp|q+x
INF: x=~a*b/c-d+e%~f
INF: x=a^b^c
INF: ((a+b*c))
INF: x=a=b=c^d^e

ONP: ( a,b,.).c;-,*
ONP: -abc-+de^/
ONP: a
ONP: ab*cd**
ONP: ab+a~a-+
ONP: ab+cd++
ONP: ab/c*
ONP: abc++def++g+++
ONP: abc-+de^/
ONP: xabc**=
*/

/* OUTPUT
ONP: ab+a~a-+
ONP: ab+a~a-+
ONP: xa~~bc*+=
ONP: ta~x<b~<=
ONP: error
ONP: error
ONP: xa~b*c/d-ef~%+=
ONP: xabc^^=
ONP: abc*+
ONP: xabcde^^===

INF: a*(b-c)
INF: error
INF: a
INF: a*b*(c*d)
INF: a+b+(~a-a)
INF: a+b+(c+d)
INF: a/b*c
INF: error
INF: (a+(b-c))/d^e
INF: x=a*(b*c)
*/
