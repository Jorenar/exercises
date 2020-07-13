// Jakub Lukasiewicz - 3

import java.util.LinkedList;
import java.util.Scanner;

class Labirynth {
    boolean[] board;
    int n;
    int m;

    public Labirynth(boolean[] board_, int n_, int m_) {
        this.board = board_.clone();
        this.n = n_;
        this.m = m_;
    }

    public boolean get(int i, int j) {
        return board[i*m + j];
    }

    public void set(int i, int j, boolean x) {
        board[i*m + j] = x;
    }
}

class Pathfinder {
    Labirynth labirynth;
    LinkedList<String> stack = new LinkedList<>();
    int I;
    int J;
    public Pathfinder(boolean[] board_, int n_, int m_, int I_, int J_) {
        labirynth = new Labirynth(board_, n_, m_);
        I = I_;
        J = J_;
        stack.addLast("");
    }
    public boolean findPath(int i, int j) { return false; }
}

class RecursivePathfinder extends Pathfinder {
    public RecursivePathfinder(boolean[] board_, int n_, int m_, int I_, int J_) {
        super(board_, n_, m_, I_, J_);
    }

    public boolean findPath(int i, int j) {
        boolean found = false;

        int x;
        int y;

        if (i == I && j == J) {
            found = true;
        } else {
            labirynth.set(i, j, false);
        }

        x = i-1;
        if (!found && x >= 0 && x < labirynth.n) {
            if (labirynth.get(x,j)) {
                stack.addLast("S"); // because array is reversed
                found = findPath(x, j);
                if (!found) { stack.removeLast(); }
            }
        }

        y = j+1;
        if (!found && y < labirynth.m) {
            if (labirynth.get(i, y)) {
                stack.addLast("E");
                found = findPath(i, y);
                if (!found) { stack.removeLast(); }
            }
        }

        x = i+1;
        if (!found && x < labirynth.n) {
            if (labirynth.get(x, j)) {
                stack.addLast("N"); // because array is reversed
                found = findPath(x, j);
                if (!found) { stack.removeLast(); }
            }
        }

        y = j-1;
        if (!found && y >= 0 && y < labirynth.m) {
            if (labirynth.get(i, y)) {
                stack.addLast("W");
                found = findPath(i, y);
                if (!found) { stack.removeLast(); }
            }
        }

        return found;
    }
}

class IterativePathfinder extends Pathfinder {
    public IterativePathfinder(boolean[] board_, int n_, int m_, int I_, int J_) {
        super(board_, n_, m_, I_, J_);
    }

    public boolean findPath(int i, int j) {
        int x;
        int y;

        while (stack.size() != 0) {
            if (i == I && j == J) {
                return true;
            } else {
                labirynth.set(i, j, false);
                if (i-1 >= 0 && i-1<labirynth.n && labirynth.get(i-1,j)) {
                    --i;
                    stack.addLast("S");
                } else if (j+1 < labirynth.m && labirynth.get(i,j+1)) {
                    ++j;
                    stack.addLast("E");
                } else if (i+1 < labirynth.n && labirynth.get(i+1,j)) {
                    ++i;
                    stack.addLast("N");
                } else if (j-1 >= 0 && j-1 < labirynth.m && labirynth.get(i,j-1)) {
                    --j;
                    stack.addLast("W");
                } else {
                    switch (stack.removeLast()) {
                        case "S":
                            ++i;
                            break;
                        case "E":
                            --j;
                            break;
                        case "N":
                            --i;
                            break;
                        case "W":
                            ++j;
                            break;
                    }
                }
            }
        }

        return false;
    }
}

class Source {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int m = in.nextInt();
        int n = in.nextInt();
        boolean[] board = new boolean[n*m];
        for (int i = n-1; i >= 0; --i) {
            for (int j = 0; j < m; ++j) {
                board[i*m + j] = (in.nextInt() == 0);
            }
        }
        int Z = in.nextInt();
        for (int z = 0; z < Z; ++z) {
            char c = in.next().charAt(0);
            int x = in.nextInt();
            int y = in.nextInt();
            int X = in.nextInt();
            int Y = in.nextInt();

            System.out.print(c);

            Pathfinder finder;

            if (c == 'r') {
                finder = new RecursivePathfinder(board,n,m,Y,X);
            } else {
                finder = new IterativePathfinder(board,n,m,Y,X);
            }

            if (finder.findPath(y,x)) {
                System.out.println(String.join(" ", finder.stack));
            } else {
                System.out.println(" X");
            }
        }
    }
}

// vim: fen
