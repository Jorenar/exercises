// 1162034

class Graph {

    class Vertex {
        public char label;
        public boolean visited;
        public Vertex(char l) {
            label = l;
            visited = false;
        }

    }

    private Vertex[] list;
    private boolean[][] matrix;
    private int size;
    private int max = 10;

    public Graph() {
        list = new Vertex[max];
        matrix = new boolean[max][max];
    }

    public void add(char label) {
        if (size < max) {
            list[size] = new Vertex(label);
            ++size;
        }
    }

    public void connect(int a, int b) {
        matrix[a][b] = true;
        matrix[b][a] = true;
    }

    public void printSimple() {
        for (int i = 0; i < size; ++i) {
            System.out.print(list[i].label + ":");
            for (int j = 0; j < size; ++j) {
                if (matrix[i][j]) {
                    System.out.print(" " + list[j].label);
                }
            }
            System.out.println();
        }
    }

    public void printDFS(int x, int n) {
        System.out.print(list[x].label + " ");
        list[x].visited = true;
        boolean foo = false;
        for (int i = size-1; i >= 0; --i) {
            if (matrix[x][i] && !list[i].visited) {
                printDFS(i, n+1);
                foo = true;
            }
        }
        if (!foo) {
            System.out.println();
            String indent = new String(new char[n]).replace("\0", " ");
            System.out.print(indent);
        }
    }

    public void printDFS(int x) {
        printDFS(x, 0);
    }

}

class zad2i3 {
    public static void main(String[] args) {
        Graph g = new Graph();

        g.add('A'); // 0
        g.add('B'); // 1
        g.add('C'); // 2
        g.add('D'); // 3
        g.add('E'); // 4

        g.connect(1, 0); // B - A
        g.connect(1, 3); // B - D
        g.connect(0, 2); // A - C
        g.connect(3, 2); // D - C
        g.connect(2, 4); // C - E

        g.printSimple();

        System.out.println();

        g.printDFS(0);  // start from A
    }
}

// vim: fen fdl=1
