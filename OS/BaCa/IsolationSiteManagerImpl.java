// Jakub Lukasiewicz

// only 60%

import java.util.Arrays;
import java.util.concurrent.Semaphore;
import java.util.Vector;

// class Patient { int group() { return 0; } }
// interface IsolationSiteManager {}

public class IsolationSiteManagerImpl
    implements IsolationSiteManager {

    private class Ward {
        private int patients;
        private int capacity;
        private Vector<Patient> list;
        private Semaphore mutex;
        private Semaphore foo;

        public Ward(int c) {
            this.capacity = c;
            this.patients = 0;
            this.list = new Vector<Patient>();

            mutex    = new Semaphore(1, true);
            foo      = new Semaphore(1, true);
        }

        public boolean full() {
            return patients == capacity;
        }

        public boolean onList(Patient p) {
            return list.contains(p);
        }

        public void lockFull() {
            foo.acquireUninterruptibly();
        }

        public void unlockFull() {
            foo.release();
        }

        public void lockMutex() {
            mutex.acquireUninterruptibly();
        }

        public void unlockMutex() {
            mutex.release();
        }

        public void add(Patient p) {
            list.add(p);
        }

        public void remove(Patient p) {
            list.removeElement(p);
        }

    }

    private class Yard {
        private int patients;
        private int group;
        private int capacity;
        private Semaphore mutex;
        private Semaphore foo;
        private Semaphore occupied;

        public Yard(int c) {
            this.capacity = c;
            this.patients = 0;

            mutex    = new Semaphore(1, true);
            foo      = new Semaphore(1, true);
            occupied = new Semaphore(1, true);
        }

        public boolean empty() {
            return patients == 0;
        }

        public boolean full() {
            return patients == capacity;
        }

        public boolean checkGroup(int g) {
            return g == group;
        }

        public void setGroup(int g) {
            group = g;
        }

        public void lockFull() {
            foo.acquireUninterruptibly();
        }

        public void unlockFull() {
            foo.release();
        }

        public void lockMutex() {
            mutex.acquireUninterruptibly();
        }

        public void unlockMutex() {
            mutex.release();
        }

        public void lockGroup() {
            occupied.acquireUninterruptibly();
        }

        public void unlockGroup() {
            occupied.release();
        }

    }

    private Yard yard;
    private Ward[] wards;

    public void init(int numWards, int wardCapacity, int yardCapacity) {
        this.yard  = new Yard(yardCapacity);
        this.wards = new Ward[numWards];
        for (Ward w: wards) {
            w = new Ward(numWards);
        }
    }

    public void newPatient(Patient p) {
        int g = p.group();
        wards[g].lockFull();
        if (!yard.checkGroup(g)) {
            yard.lockGroup();
        }
        yard.lockFull();
    }

    public void enterYard(Patient p) {
        yard.lockMutex();
        int g = p.group();
        yard.setGroup(g);
        yard.patients++;

        if (yard.full()) {
            yard.lockFull();
        } else {
            yard.unlockFull();
        }

        if (!wards[g].onList(p)) {
            wards[g].patients--;
        }

        yard.unlockMutex();
    }

    public void enterWard(Patient p) {
        int g = p.group();
        wards[g].lockMutex();
        yard.patients--;
        if (!wards[g].onList(p)) {
            wards[g].patients++;
            wards[g].add(p);
        }
        if (yard.empty()) {
            yard.unlockGroup();
        }
        if (!yard.full()) {
            yard.unlockFull();
        }
        if (!wards[g].full()) {
            wards[g].unlockFull();
        }
        wards[g].unlockMutex();
    }

    public void patientLeft(Patient p) {
        int g = p.group();
        wards[g].patients--;
        wards[g].remove(p);
        if (!wards[g].full()) {
            wards[g].unlockFull();
        }
    }

}

// vim: fen fdl=1
