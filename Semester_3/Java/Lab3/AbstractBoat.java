package org.example;

public abstract class AbstractBoat {
    protected int id;
    protected String type;

    protected AbstractBoat() {}

    public AbstractBoat(int id, String type)
    {
        this.id = id;
        this.type = type;
    }

    public int getId() { return id; }
    public String getType() { return type; }

    public void setId(int id) { this.id = id; }
    public void setType(String type) { this.type = type; }

    @Override
    public abstract String toString();
}
