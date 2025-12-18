package org.example;

import java.util.Map;
import java.util.SortedMap;
import java.util.TreeMap;

public class BoatMap extends AbstractBoatStorage{
    protected SortedMap<Integer, Boat>boats;

    public BoatMap() { boats = new TreeMap<>(); }

    @Override
    public Boat get(int index) { return boats.get(index); }

    @Override
    public int size() { return boats.size(); }

    @Override
    public void add(Boat boat)
    {
        int index = boat.getId();
        boats.put(index, boat);
    }

    @Override
    public void addAt(int index, Boat boat) { boats.put(index, boat); }

    public void remove(int index) { boats.remove(index); }

    @Override
    public void update(int index, Boat new_boat)
    {
        if(index >= 0 && index <= boats.size()){
            boats.put(index, new_boat);
        }
        else{
            System.out.println("Index out of range");
        }
    }

    @Override
    public boolean contains(Boat boat) { return boats.containsKey(boat.getId()) && boats.get(boat.getId()).equals(boat); }

    @Override
    public boolean isEmpty() { return boats.isEmpty();}

    @Override
    public void printInfo()
    {
        for (Map.Entry<Integer, Boat> entry : boats.entrySet()) {
            System.out.println(entry.getValue().toString());
        }
    }
}
