package org.example;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

public class BoatList extends AbstractBoatStorage{
    protected List<Boat> boats;

    public BoatList()
    {
        boats = new ArrayList<>();
    }

    @Override
    public Boat get(int index)
    {
        return boats.get(index);
    }

    @Override
    public int size() {
        return boats.size();
    }

    @Override
    public void add(Boat boat)
    {
        boats.add(boat);
    }

    @Override
    public void addAt(int index, Boat boat)
    {
        boats.add(index, boat);
    }

    public void remove(int index)
    {
        boats.remove(index);
    }

    @Override
    public void update(int index, Boat new_boat)
    {
        if(index >= 0 && index <= boats.size()){
            boats.set(index, new_boat);
        }
        else{
            System.out.println("Index out of range");
        }
    }

    @Override
    public boolean contains(Boat boat) {
        return boats.contains(boat);
    }

    @Override
    public boolean isEmpty() {
        return boats.isEmpty();
    }

    @Override
    public void printInfo()
    {
        for(int i = 0; i < boats.size(); i++){
            System.out.println(boats.get(i).toString());
        }
    }

    public void sortById() { boats.sort(Comparator.comparingInt(Boat::getId)); }
    public void sortByType() { boats.sort(Comparator.comparing(Boat::getType, String.CASE_INSENSITIVE_ORDER)); }
    public void sortByProductionDate() { boats.sort(Comparator.comparing(Boat::getProd_date, Comparator.nullsLast(Comparator.naturalOrder()))); }
    public void sortByModel() { boats.sort(Comparator.comparing(Boat::getModel, String.CASE_INSENSITIVE_ORDER)); }
    public void sortByEnginePower() { boats.sort(Comparator.comparingInt(Boat::getEngine_power)); }
    public void sortByMaxLoad() { boats.sort(Comparator.comparingInt(Boat::getMax_load)); }
}
