// Jakub Lukasiewicz - 3

import java.util.Scanner;

class Source {

    public static class ListWithHead {
        public class Node {
            public String name;
            public Node next;
            public Node prev;
            public Node(String name_) {
                name = name_;
                next = null;
                prev = null;
            }
        }

        public Node first;
        public Node last;
        public Node current;

        public ListWithHead() {
            first = new Node("");
            first.next = null;
            current = first;
        }

        public void insert(String x) {
            Node temp = new Node(x);
            if (current != null) {
                temp.prev = current;
                temp.next = current.next;
                current.next = temp;
            } else {
                first.next = temp;
            }
            if (last == null) {
                last = temp;
            }
            current = temp;
        }

        public void insertFirst(String x) {
            Node temp = new Node(x);
            temp.next = first.next;
            if (first.next != null) {
                first.next.prev = temp;
            }
            first.next = temp;
        }

        public void insertLast(String x) {
            Node temp = new Node(x);
            last.next = temp;
            temp.prev = last;
            last = temp;
        }

        public String popFirst() {
            if (first.next != null) {
                Node temp = first.next;
                if (temp.next != null) {
                    temp.next.prev = first;
                }
                first.next = temp.next;
                return temp.name;
            } else {
                return "";
            }
        }

        public String popLast() {
            if (last != null) {
                Node temp = last;
                if (last == first) {
                    last = null;
                    first.next = null;
                    return temp.name;
                }
                last = temp.prev;
                last.next = null;
                return temp.name;
            } else {
                return "";
            }
        }

        public boolean locate(String id) {
            current = first;
            while (current != null) {
                if (current.name.equals(id)) {
                    return true;
                } else {
                    current = current.next;
                }
            }
            return false;
        }

        public void display() {
            Node temp = first.next;
            while (temp != null) {
                System.out.print(temp.name + " ");
                temp = temp.next;
            }
            System.out.println("");
        }

        public void reverse() {
            Node temp = first.next;
            while (temp != null) {
                Node t = temp.next;
                temp.next = temp.prev;
                temp.prev = t;
                temp = temp.prev;
            }
            first.next.next = null;
            last.prev = first;
            temp = first.next;
            first.next = last;
            last = temp;
        }

    }

    public static class List {

        public static class Node {
            public String name;
            public Node next;
            public Node(String name_) {
                name = name_;
                next = null;
            }
            public ListWithHead cars = new ListWithHead();

            public void display() {
                System.out.print(name + ": ");
                cars.display();
            }
        }

        public Node first;

        public List() {
            first = null;
        }

        public void insert(String x) {
            Node temp = new Node(x);
            if (first != null) {
                temp.next = first;
            }
            first = temp;
        }

        public Node locate(String id) {
            Node temp = first;
            Node p = first;
            while (temp != null) {
                if (temp.name.equals(id)) {
                    return temp;
                } else {
                    p = temp;
                    temp = temp.next;
                }
            }
            return p;
        }

        public void deleteNode(Node obj) {
            Node t1 = first;
            Node t2 = first;
            while (t2 != obj) {
                t1 = t2;
                t2 = t2.next;
            }
            if (obj == first) {
                first = obj.next;
            } else {
                t1.next = obj.next;
            }
        }

        public void display() {
            System.out.print("Trains: ");
            Node temp = first;
            while (temp != null) {
                System.out.print(temp.name + " ");
                temp = temp.next;
            }
            System.out.println("");
        }

    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int Z = Integer.parseInt(in.nextLine());
        for (int z = 0; z < Z; ++z) {
            List trains = new List();
            int N = Integer.parseInt(in.nextLine());
            for (int n = 0; n < N; ++n) {
                String command[] = in.nextLine().split(" ");
                List.Node train = null;

                if (command.length > 1) {
                    train = trains.locate(command[1]);
                    boolean trainExist = (train != null && train.name.equals(command[1]));

                    if (command[0].equals("New")) {
                        if (trainExist) {
                            System.out.println("Train " + command[1] + " already exists");
                        } else {
                            trains.insert(command[1]);
                            trains.first.cars.insert(command[2]);
                        }
                    } else if (trainExist) {
                        switch (command[0]) {
                            case "InsertFirst":
                                train.cars.current = train.cars.first;
                                train.cars.insertFirst(command[2]);
                                break;
                            case "InsertLast":
                                train.cars.current = train.cars.last;
                                train.cars.insertLast(command[2]);
                                break;
                            case "Display":
                                train.display();
                                break;
                            case "Reverse":
                                train.cars.reverse();
                                break;
                            default:
                                List.Node train2 = trains.locate(command[2]);
                                boolean trainExist2 = (train2 != null && train2.name.equals(command[2]));
                                if (command[0].equals("Union")) {
                                    if (trainExist2) {
                                        train.cars.last.next = train2.cars.first.next;
                                        train.cars.last.next.prev = train.cars.last;
                                        train.cars.last = train2.cars.last;
                                        trains.deleteNode(train2);
                                    } else {
                                        System.out.println("Train " + command[2] + " does not exist");
                                    }
                                } else if (!trainExist2) {
                                    trains.insert(command[2]);
                                    String foo = "";
                                    switch (command[0]) {
                                        case "DelFirst":
                                            foo = train.cars.popFirst();
                                            if (foo.length() > 0) {
                                                trains.first.cars.insert(foo);
                                            }
                                            break;
                                        case "DelLast":
                                            foo = train.cars.popLast();
                                            if (foo.length() > 0) {
                                                trains.first.cars.insert(foo);
                                            }
                                            break;
                                    }
                                    if (train.cars.first.next == null) {
                                        trains.deleteNode(train);
                                    }
                                } else {
                                    System.out.println("Train " + command[2] + " already exists");
                                }
                        }
                    } else {
                        System.out.println("Train " + command[1] + " does not exist");
                    }
                } else {
                    trains.display();
                }
            }
        }
    }

}

// vim: fen fdl=1
