package org.example;

public abstract class AbstractBoatStorage {
    public abstract Boat get(int index);
    public abstract int size();
    public abstract void add(Boat boat);
    public abstract void addAt(int index, Boat boat);
    public abstract void remove(int index);
    public abstract void update(int index, Boat new_boat);
    public abstract boolean contains(Boat boat);
    public abstract boolean isEmpty();
    public abstract void printInfo();
}