package org.example;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.transform.Transformer;
import javax.xml.transform.TransformerFactory;
import javax.xml.transform.dom.DOMSource;
import javax.xml.transform.stream.StreamResult;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.json.JSONObject;
import org.json.JSONArray;
import org.json.JSONException;
import java.io.*;
import java.util.Map;

public class FileHandler {
    private String getNodeText(Element elem, String tag) {
        NodeList nodes = elem.getElementsByTagName(tag);
        if (nodes.getLength() > 0) {
            String text = nodes.item(0).getTextContent().trim();
            return text;
        }
        return "";
    }

    public BoatList readFromFileList(String filename)
    {
        try(BufferedReader reader = new BufferedReader(new FileReader(filename))){
            BoatList boats = new BoatList();
            String line;
            while((line =reader.readLine())!=null)  {
                Boat readed_boat = new Boat();
                readed_boat.parseString(line);
                boats.add(readed_boat);
            }
            return boats;
        }
        catch (IOException e){
            e.printStackTrace();
            return null;
        }
    }

    public BoatMap readFromFileMap(String filename)
    {
        try(BufferedReader reader = new BufferedReader(new FileReader(filename))){
            BoatMap boats = new BoatMap();
            String line;
            while((line =reader.readLine())!=null)  {
                Boat readed_boat = new Boat();
                readed_boat.parseString(line);
                boats.add(readed_boat);
            }
            return boats;
        }
        catch (IOException e){
            e.printStackTrace();
            return null;
        }
    }

    public BoatList readFromFileXML(String filename) {
        try {
            Document doc = DocumentBuilderFactory.newInstance().newDocumentBuilder().parse(new File(filename));
            doc.getDocumentElement().normalize();

            BoatList boats = new BoatList();
            NodeList boat_nodes = doc.getElementsByTagName("boat");

            for (int i = 0; i < boat_nodes.getLength(); i++) {
                Node node = boat_nodes.item(i);
                if (node.getNodeType() == Node.ELEMENT_NODE) {
                    Element elem = (Element) node;

                    String id = getNodeText(elem, "id");
                    String type = getNodeText(elem, "type");
                    String prod_date = getNodeText(elem, "productionDate");
                    String model = getNodeText(elem, "model");
                    String engine_power = getNodeText(elem, "enginePower");
                    String max_load = getNodeText(elem, "maxLoad");
                    String boat_str = String.format("%s, %s, %s, %s, %s, %s", id, type, prod_date, model, engine_power, max_load);

                    Boat boat = new Boat();
                    boat.parseString(boat_str);
                    boats.add(boat);
                }
            }
            return boats;
        }
        catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public BoatList readFromFileJSON(String filename) {
        try (BufferedReader reader = new BufferedReader(new FileReader(filename))) {
            StringBuilder content = new StringBuilder();
            String line;
            while ((line = reader.readLine()) != null) {
                content.append(line);
            }

            JSONObject json = new JSONObject(content.toString());
            BoatList boats = new BoatList();
            JSONArray boats_array = json.getJSONArray("boats");
            for (int i = 0; i < boats_array.length(); i++) {
                JSONObject boatJson = boats_array.getJSONObject(i);
                Boat boat = new Boat();

                boat.setId(boatJson.optInt("id", 0));
                boat.setType(boatJson.optString("type", ""));
                boat.setModel(boatJson.optString("model", ""));
                String date_str = boatJson.optString("productionDate", "");
                boat.setProd_date(boat.parseDate(date_str));
                boat.setEngine_power(boatJson.optInt("enginePower", 0));
                boat.setMax_load(boatJson.optInt("maxLoad", 0));
                boats.add(boat);
            }
            return boats;
        }
        catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public void writeToFileList(BoatList boats, String filename)
    {
        try(BufferedWriter writer = new BufferedWriter(new FileWriter(filename))){
            for(int i = 0; i < boats.size(); i++){
                writer.write(boats.get(i).toString());
                writer.newLine();
            }
        }
        catch (IOException e){
            e.printStackTrace();
        }
    }

    public void writeToFileMap(BoatMap boats, String filename)
    {
        try(BufferedWriter writer = new BufferedWriter(new FileWriter(filename))){
            for(Map.Entry<Integer, Boat> entry : boats.boats.entrySet()){
                writer.write(entry.getValue().toString());
                writer.newLine();
            }
        }
        catch (IOException e){
            e.printStackTrace();
        }
    }

    public void writeToFileXML(BoatList boats, String filename) {
        try {
            DocumentBuilderFactory doc_factory = DocumentBuilderFactory.newInstance();
            DocumentBuilder doc_builder = doc_factory.newDocumentBuilder();

            Document doc = doc_builder.newDocument();
            Element root_element = doc.createElement("boats");
            doc.appendChild(root_element);

            for (int i = 0; i < boats.size(); i++) {
                Boat boat = boats.get(i);

                Element boat_element = doc.createElement("boat");
                root_element.appendChild(boat_element);

                Element id_element = doc.createElement("id");
                id_element.appendChild(doc.createTextNode(String.valueOf(boat.getId())));
                boat_element.appendChild(id_element);

                Element type_element = doc.createElement("type");
                type_element.appendChild(doc.createTextNode(boat.getType()));
                boat_element.appendChild(type_element);

                Element date_element = doc.createElement("productionDate");
                date_element.appendChild(doc.createTextNode(boat.formatDate(boat.getProd_date())));
                boat_element.appendChild(date_element);

                Element model_element = doc.createElement("model");
                model_element.appendChild(doc.createTextNode(boat.getModel()));
                boat_element.appendChild(model_element);

                Element power_element = doc.createElement("enginePower");
                power_element.appendChild(doc.createTextNode(String.valueOf(boat.getEngine_power())));
                boat_element.appendChild(power_element);

                Element load_element = doc.createElement("maxLoad");
                load_element.appendChild(doc.createTextNode(String.valueOf(boat.getMax_load())));
                boat_element.appendChild(load_element);
            }

            TransformerFactory transformer_factory = TransformerFactory.newInstance();
            Transformer transformer = transformer_factory.newTransformer();
            transformer.setOutputProperty(javax.xml.transform.OutputKeys.INDENT, "yes");
            transformer.setOutputProperty("{http://xml.apache.org/xslt}indent-amount", "4");

            DOMSource source = new DOMSource(doc);
            StreamResult result = new StreamResult(new File(filename));

            transformer.transform(source, result);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void writeToFileJSON(BoatList boats, String filename) {
        try {
            JSONObject json = new JSONObject();
            JSONArray boats_array = new JSONArray();
            for (int i = 0; i < boats.size(); i++) {
                Boat boat = boats.get(i);
                JSONObject boat_json = new JSONObject();
                try {
                    boat_json.put("id", boat.getId());
                    boat_json.put("type", boat.getType());
                    boat_json.put("model", boat.getModel());
                    boat_json.put("productionDate", boat.formatDate(boat.getProd_date()));
                    boat_json.put("enginePower", boat.getEngine_power());
                    boat_json.put("maxLoad", boat.getMax_load());
                    boats_array.put(boat_json);
                }
                catch (JSONException e){
                    e.printStackTrace();
                }
            }

            json.put("boats", boats_array);
            json.put("totalBoats", boats.size());

            try (PrintWriter out = new PrintWriter(new FileWriter(filename))) {
                out.write(json.toString(2));
            }

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}