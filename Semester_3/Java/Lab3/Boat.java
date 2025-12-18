package org.example;

import java.util.Date;
import java.text.SimpleDateFormat;
import java.text.ParseException;
import java.util.logging.Level;
import java.util.logging.Logger;

public class Boat extends AbstractBoat{
    protected Date prod_date;
    protected String model;
    protected int engine_power;
    protected int max_load;

    private static final Logger logger = Logger.getLogger(Boat.class.getName());
    public Boat(){}

    public Boat(int id, String type, String prod_date, String model, int engine_power, int max_load)
    {
        this.id = id;
        this.type = type;
        this.prod_date = parseDate(prod_date);
        this.model = model;
        this.engine_power = engine_power;
        this.max_load = max_load;
    }

    public Date getProd_date() { return prod_date; }
    public String getModel() { return model; }
    public int getEngine_power() { return engine_power; }
    public int getMax_load() { return max_load; }

    public void setProd_date(Date prod_date) { this.prod_date = prod_date; }
    public void setModel(String model) { this.model = model; }
    public void setEngine_power(int engine_power) { this.engine_power = engine_power;}
    public void setMax_load(int max_load) { this.max_load = max_load;}

    public Date parseDate(String date_str)
    {
        try{
            SimpleDateFormat sdf = new SimpleDateFormat("dd.MM.yyyy");
            sdf.setLenient(false);
            return sdf.parse(date_str);
        }
        catch (ParseException e){
            logger.log( Level.SEVERE, e.toString(), e );
            return null;
        }
    }

    public void parseString(String boat_str)
    {
        id = 0;
        type = "";
        prod_date = null;
        model = "";
        engine_power = 0;
        max_load = 0;

        String[] fields = boat_str.split(",");
        try{
            String field_str = fields[0].trim();
            if(!field_str.isEmpty()) {
                try {
                    id = Integer.parseInt(field_str);
                }
                catch (NumberFormatException e){
                    logger.log( Level.SEVERE, e.toString(), e );
                }
            }

            type = fields[1].trim();

            field_str = fields[2].trim();
            if (!field_str.isEmpty()) {
                prod_date = parseDate(field_str);
            }

            model = fields[3].trim();

            field_str = fields[4].trim();
            if(!field_str.isEmpty()) {
                try {
                    engine_power = Integer.parseInt(field_str);
                    if(engine_power < 0){
                        System.out.println("Error: negative engine power");
                        engine_power = 0;
                    }
                }
                catch (NumberFormatException e){
                    logger.log( Level.SEVERE, e.toString(), e );
                }
            }

            field_str = fields[5].trim();
            if(!field_str.isEmpty()) {
                try {
                    max_load = Integer.parseInt(field_str);
                    if(max_load < 0){
                        System.out.println("Error: negative max load");
                        max_load = 0;
                    }
                }
                catch (NumberFormatException e){
                    logger.log( Level.SEVERE, e.toString(), e );
                }
            }
        }
        catch (Exception e){
            e.printStackTrace();
        }
    }

    public String formatDate(Date date)
    {
        if (date == null) {
            return "N/A";
        }
        SimpleDateFormat sdf = new SimpleDateFormat("dd.MM.yyyy");
        return sdf.format(date);
    }

    @Override
    public String toString()
    {
        return String.format("Boat(%s) | type: %s | production date: %s | model: %s | engine power: %shp | max load: %skg",
                id, type, formatDate(prod_date), model, engine_power, max_load);
    }
}
