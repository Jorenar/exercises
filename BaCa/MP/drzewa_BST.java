// Jakub Lukasiewicz - 3

// Not passed! (IDK why)

import java.util.Scanner;

class Int { // eh, no references for primitive types...
    public int val;
    Int(int v) { val = v; }
}

class Stack<T> { // standard, generic stack data structure
    private class Node {
        T data;
        Node prev;

        public Node(T x, Node p) {
            data = x;
            prev = p;
        }

    }

    private Node top;

    public Stack() {
        top = null;
    }

    void push(T x) {
        if (top == null) {
            top = new Node(x, null);
        } else {
            top = new Node(x, top);
        }
    }

    T pop() {
        T temp = top.data;
        top = top.prev;
        return temp;
    }

    T peek() {
        return top.data;
    }

    boolean empty() {
        return top == null;
    }

}

class Tree {
    class Node {
        public int info;
        public Node left;
        public Node right;

        public Node(int info) {
            this.info  = info;
            this.left  = null;
            this.right = null;
        }

    }

    private Node root;

    // Recursively creates tree from array given in preorder
    private Node createPre(int[] arr, Int i, int x, int min, int max, int N) {
        Node R = null;

        if (i.val < N && x > min && x < max) {
            R = new Node(x);
            ++(i.val); // `i` goes from 0 to N (it's reference) - linear complexity
            if (i.val < N) { // construct the subtree under R node; first left, then right (important!)
                R.left  = createPre(arr, i, arr[i.val], min, x, N); // smaller than `x` go in left  subtree
                if (i.val < N) {
                    R.right = createPre(arr, i, arr[i.val], x, max, N); // larger  than `x` go in right subtree
                }
            }
        }

        return R;
    }

    // Recursively creates tree from array given in postorder
    private Node createPost(int[] arr, Int i, int x, int min, int max, int N) {
        Node R = null;

        if (i.val >= 0 && x > min && x < max) {
            R = new Node(x);
            --(i.val); // `i` goes from N-1 to -1 (it's reference) - linear complexity
            if (i.val >= 0) { // construct the subtree under R node; first right, then left (important!)
                R.right = createPost(arr, i, arr[i.val], x, max, N); // larger  than `x` go in right subtree
                if (i.val >= 0) {
                    R.left  = createPost(arr, i, arr[i.val], min, x, N); // smaller than `x` go in left subtree
                }
            }
        }

        return R;
    }

    public Tree(int[] arr, String order) {
        int N = arr.length; // better than `arr.length` each time
        if (N > 0) {
            switch (order) {
                case "PREORDER":
                    root = createPre(arr, new Int(0), arr[0], Integer.MIN_VALUE, Integer.MAX_VALUE, N);
                    break;
                case "POSTORDER":
                    root = createPost(arr, new Int(N-1), arr[N-1], Integer.MIN_VALUE, Integer.MAX_VALUE, N);
                    break;
            }
        } else {
            root = null;
        }
    }

    private Node min(Node t) { // linear complexity
        while (t.left != null) {
            t = t.left;
        }
        return t;
    }

    private Node max(Node t) { // linear complexity
        while (t.right != null) {
            t = t.right;
        }
        return t;
    }

    private void printPre(int mult) {
        if (root == null) {
            return;
        }

        Stack<Node> s = new Stack<>();
        s.push(root);

        // Variables for SCAN
        int sum = 0;
        boolean first = true;

        while (!s.empty()) { // one loop - linear complexity

            // Pop the top item from stack and ...
            Node t = s.pop();
            System.out.print(" ");
            if (mult == 0) { // ... print it
                System.out.print(t.info);
            } else { // ... add and print sum
                sum += first ? t.info : mult * t.info;
                System.out.print(sum);
                first = false;
            }

            // Push right and left children of the popped node to stack
            if (t.right != null) {
                s.push(t.right);
            }
            if (t.left != null) {
                s.push(t.left);
            }
        }
    }

    private void printIn(int mult) {
        Stack<Node> s = new Stack<>();
        Node t = root;

        // Variables for SCAN
        int sum = 0;
        boolean first = true;

        while (t != null || !s.empty()) { // one loop - linear complexity
            if (t !=  null) { // reach the left most Node of the t Node
                s.push(t);
                t = t.left;
            } else {
                t = s.pop();
                System.out.print(" ");
                if (mult == 0) {
                    System.out.print(t.info);
                } else { // `mult` equals 1 or -1, then SCAN
                    sum += first ? t.info : mult * t.info;
                    System.out.print(sum);
                    first = false;
                }
                t = t.right; // the node and its left subtree was visited, now is right subtree's turn
            }
        }
    }

    private void printPost(int mult) {
        if (root == null) {
            return;
        }

        // create an empty s and push root node
        Stack<Node> s = new Stack<>();
        s.push(root);
        Stack<Integer> out = new Stack<>();

        while (!s.empty()) { // one loop - linear complexity
            // Pop the top item and push it to output stack
            Node t = s.pop();
            out.push(t.info);

            // Push left and right children of the popped node to stack
            if (t.left != null) {
                s.push(t.left);
            }
            if (t.right != null) {
                s.push(t.right);
            }
        }

        // Variables for SCAN
        int sum = 0;
        boolean first = true;

        // Print postorder traversal
        while (!out.empty()) {  // second loop, but outside the first one - still linear complexity
            System.out.print(" ");
            int x = out.pop();
            if (mult == 0) {
                System.out.print(x);
            } else { // `mult` equals 1 or -1, then SCAN
                sum += first ? x : mult * x;
                System.out.print(sum);
                first = false;
            }
        }
    }

    private int height(Node t) { // linear, recursive
        if (t == null) {
            return 0;
        } else {
            int l = height(t.left);  // height of left  subtree
            int r = height(t.right); // height of right subtree
            return ( l > r ? l : r ) + 1; // return height of bigger subtree (increased by 1)
        }
    }

    public void insert(int x) {
        Node s = new Node(x);

        if (root == null) { // insert as first element
            root = s;
        } else if (search(x) == null) { // insert if there isn't one already
            Node t = root;
            Node p = null;
            while (t != null) { // find right place; one loop - linear complexity
                p = t;
                t = x < t.info ? t.left : t.right;
            }
            if (x < p.info) {
                p.left = s;
            } else if (x > p.info) {
                p.right = s;
            }
        }
    }

    public boolean delete(int x) {
        if (root == null) {
            return false;
        }

        Node t = null;
        Node p = parent(x); // has linear complexity
        boolean isLeftChild = false;

        if (p == null) { // if parent is `null`, then either there is no node with value `x` or it's `root`
            if (root.info == x) {
                t = root;
            } else {
                return false;
            }
        } else if (p.left  != null && p.left.info  == x) { // check if `x` is left  child of parent
            isLeftChild = true;
            t = p.left;
        } else if (p.right != null && p.right.info == x) { // check if `x` is right child of parent
            t = p.right;
        } else { // just in case
            return false;
        }

        // If reached here means node to be deleted is found
        if (t.left == null && t.right == null) { // leaf node deletion case
            if (t == root) { // if root node is to be deleted
                root = null;
            } else if (isLeftChild) { // left child
                p.left = null;
            } else { // right child
                p.right = null;
            }
        } else if (t.left == null) { // node to be deleted has only right child
            if (t == root) { // if root node is to be deleted
                root = t.right;
            } else if (isLeftChild) { // if deleted node is left child
                p.left = t.right;
            } else { // if deleted node is right child
                p.right = t.right;
            }
        } else if (t.right == null) { // node to be deleted has only left child
            if (t == root) {
                root = t.left;
            } else if (isLeftChild) { // if deleted node is left child
                p.left = t.left;
            } else { // if deleted node is right child
                p.right = t.left;
            }
        } else { // node to be deleted has two children
            Node s = t;

            /* Find successor */ { // not using successor(), because successor parent (P) will be needed
                Node P = t;
                Node n = t.right;
                while (n != null) {
                    P = s;
                    s = n;
                    n = n.left;
                }

                // Variable P is needed here:
                //   When inorder successor is in the left subtree perform two ref changes
                if (s != t.right) {
                    P.left = s.right;
                    s.right = t.right;
                }
            } // and there was one loop - linear complexity

            if (t == root) {
                root = s;
            } else if (isLeftChild) { // if deleted node is left child
                p.left = s;
            } else { // if deleted node is right child
                p.right = s;
            }
            s.left = t.left;
        }

        return true;
    }

    public Node search(int x) {
        Node t = root;
        while (t != null && t.info != x) { // one loop - linear complexity
            t = x < t.info ? t.left : t.right;
        }
        return t;
    }

    public Node parent(int x) { // one loop - linear complexity
        Node t = root;
        Node p = null;
        while (t != null) {
            if (t.info == x) {
                break;
            }
            p = t;
            if (t.info < x) {
                t = t.right;
            } else {
                t = t.left;
            }
        }
        return t == null ? null : p;
    }

    public Node successor(int x) {
        Node t = root;
        Node s = null;

        while (t != null) { // one loop - linear complexity
            if (t.info == x) {
                 return t.right != null ? min(t.right) : s;
            } else if (t.info < x) {
                t = t.right;
            } else {
                s = t;
                t = t.left;
            }
        }

        return s;
    }

    public Node predecessor(int x) {
        Node t = root;
        Node p = null;

        while (t != null) { // one loop - linear complexity
            if (t.info == x) {
                return t.left != null ? max(t.left) : p;
            } else if (t.info < x) {
                p = t;
                t = t.right;
            } else {
                t = t.left;
            }
        }

        return p;
    }

    public int height() {
        int h = height(root);
        return h > 0 ? h - 1 : 0; // return height with correction
    }

    public void print(String order) {
        System.out.print(order + ":");
        switch (order) {
            case "PREORDER":
                printPre(0);
                break;
            case "INORDER":
                printIn(0);
                break;
            case "POSTORDER":
                printPost(0);
                break;
        }
        System.out.println();
    }

    public void scan(String op, String order) {
        System.out.print("SCAN " + op + " " + order + ":");
        int mult = op.equals("+") ? 1 : -1;
        switch (order) {
            case "PREORDER":
                printPre(mult);
                break;
            case "INORDER":
                printIn(mult);
                break;
            case "POSTORDER":
                printPost(mult);
                break;
        }
        System.out.println();
    }

}

class Source {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        Tree bst = null;
        Tree.Node temp = null;
        int n;

        int Z = Integer.parseInt(in.nextLine());
        for (int z = 1; z <= Z; ++z) {
            System.out.println("ZESTAW " + z);
            int Y = Integer.parseInt(in.nextLine());
            for (int y = 0; y < Y; ++y) {
                String[] cmd = in.nextLine().split(" ");
                switch (cmd[0]) {
                    case "CREATE":
                        n = Integer.parseInt(cmd[2]);
                        int[] arr = new int[n];
                        for (int i = 0; i < n; ++i) {
                            arr[i] = Integer.parseInt(cmd[i+3]);
                        }
                        bst = new Tree(arr, cmd[1]);
                        break;
                    case "INSERT":
                        for (int i = 2; i < Integer.parseInt(cmd[1]) + 2; ++i) {
                            bst.insert(Integer.parseInt(cmd[i]));
                        }
                        break;
                    case "PREORDER":
                    case "INORDER":
                    case "POSTORDER":
                        bst.print(cmd[0]);
                        break;
                    case "PARENT":
                    case "SUCCESSOR":
                    case "PREDECESSOR":
                        n = Integer.parseInt(cmd[1]);
                        switch (cmd[0]) {
                            case "PARENT":
                                temp = bst.parent(n);
                                break;
                            case "SUCCESSOR":
                                temp = bst.successor(n);
                                break;
                            case "PREDECESSOR":
                                temp = bst.predecessor(n);
                                break;
                        }
                        System.out.print(cmd[0] + " " + cmd[1] + ": ");
                        if (temp != null) {
                            System.out.println(temp.info);
                        } else {
                            System.out.println("BRAK");
                        }
                        break;
                    case "DELETE":
                        if (!bst.delete(n = Integer.parseInt(cmd[1]))) {
                            System.out.println(cmd[0] + " " + cmd[1] + ": BRAK");
                        }
                        break;
                    case "HEIGHT":
                        System.out.println(cmd[0] + ": " + bst.height());
                        break;
                    case "SCAN":
                        bst.scan(cmd[1], cmd[2]);
                        break;
                }
            }
        }

    }

}

// vim: fen
