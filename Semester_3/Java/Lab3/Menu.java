package org.example;

import java.util.Scanner;

public class Menu {
    Scanner scanner = new Scanner(System.in);
    FileHandler fp = new FileHandler();
    BoatList boats_list = new BoatList();
    BoatMap boats_map = new BoatMap();
    CipherHandler ch = new CipherHandler();
    Archiver arch = new Archiver();

    public void printMenu()
    {
        System.out.println("1.Read from txt file in list");
        System.out.println("2.Read from txt file in map");
        System.out.println("3.Read from JSON file in list");
        System.out.println("4.Read from XML file in list");
        System.out.println("5.Write list to txt file");
        System.out.println("6.Write map to txt file");
        System.out.println("7.Write list to JSON file");
        System.out.println("8.Write list to XML file");
        System.out.println("9.Add element to list");
        System.out.println("10.Add element to map");
        System.out.println("11.Redact list element");
        System.out.println("12.Redact map element");
        System.out.println("13.Remove element from list");
        System.out.println("14.Remove element from map");
        System.out.println("15.Print list");
        System.out.println("16.Print map");
        System.out.println("17.List sort");
        System.out.println("18.Encrypt out_list.txt");
        System.out.println("19.Decrypt out_list_enc.txt");
        System.out.println("20.Archive ZIP");
        System.out.println("21.Read archive ZIP");
        System.out.println("22.Archieve JAR");
        System.out.println("23.Read archive JAR");
        System.out.println("24.Exit");
    }

    public void addToList()
    {
        System.out.println("Enter boat(id, type, production date, model, engine power, max load)");
        String boat_str = scanner.nextLine();
        Boat boat = new Boat();
        boat.parseString(boat_str);
        boats_list.add(boat);
    }

    public void addToMap()
    {
        System.out.println("Enter boat(id, type, production date, model, engine power, max load)");
        String boat_str = scanner.nextLine();
        Boat boat = new Boat();
        boat.parseString(boat_str);
        boats_map.add(boat);
    }

    void replaceInList()
    {
        System.out.println("Enter element index for replace (1 - " + boats_list.size() +")" );
        int old_boat_id = scanner.nextInt();
        old_boat_id--;
        scanner.nextLine();
        System.out.println("Enter boat(id, type, production date, model, engine power, max load)");
        String boat_str = scanner.nextLine();
        Boat new_boat = new Boat();
        new_boat.parseString(boat_str);
        boats_list.update(old_boat_id, new_boat);
    }

    void replaceInMap()
    {
        System.out.println("Enter element id for replace");
        int old_boat_id = scanner.nextInt();
        scanner.nextLine();
        System.out.println("Enter boat(id, type, production date, model, engine power, max load)");
        String boat_str = scanner.nextLine();
        Boat new_boat = new Boat();
        new_boat.parseString(boat_str);
        boats_map.update(old_boat_id, new_boat);
    }

    void removeFromList()
    {
        System.out.println("Enter element index to remove (1 - " + boats_list.size() +")" );
        int del_boat_id = scanner.nextInt();
        del_boat_id--;
        boats_list.remove(del_boat_id);
    }

    void removeFromMap()
    {
        System.out.println("Enter element id to remove");
        int del_boat_id = scanner.nextInt();
        boats_list.remove(del_boat_id);
    }

    void listSort()
    {
        System.out.println("Enter field name for sort (id, type, prod_date, model, engine_power, max_load");
        String field = scanner.nextLine();
        switch (field) {
            case "id":
                boats_list.sortById();
                break;
            case "type":
                boats_list.sortByType();
                break;
            case "prod_date":
                boats_list.sortByProductionDate();
                break;
            case "model":
                boats_list.sortByModel();
                break;
            case "engine_power":
                boats_list.sortByEnginePower();
                break;
            case "max_load":
                boats_list.sortByMaxLoad();
                break;
        }
    }

    public void menu()
    {
        boolean exit = false;
        while(!exit) {
            printMenu();
            int choice = scanner.nextInt();
            scanner.nextLine();
            switch (choice) {
                case 1:
                    boats_list = fp.readFromFileList("input.txt");
                    break;
                case 2:
                    boats_map = fp.readFromFileMap("input.txt");
                    break;
                case 3:
                    boats_list = fp.readFromFileJSON("out_list.json");
                    break;
                case 4:
                    boats_list = fp.readFromFileXML("out_list.xml");
                    break;
                case 5:
                    fp.writeToFileList(boats_list, "out_list.txt");
                    break;
                case 6 :
                    fp.writeToFileMap(boats_map, "out_map.txt");
                    break;
                case 7:
                    fp.writeToFileJSON(boats_list, "out_list.json");
                    break;
                case 8:
                    fp.writeToFileXML(boats_list, "out_list.xml");
                    break;
                case 9:
                    addToList();
                    break;
                case 10:
                    addToMap();
                    break;
                case 11:
                    replaceInList();
                    break;
                case 12:
                    replaceInMap();
                    break;
                case 13:
                    removeFromList();
                    break;
                case 14:
                    removeFromMap();
                    break;
                case 15:
                    boats_list.printInfo();
                    break;
                case 16:
                    boats_map.printInfo();
                    break;
                case 17:
                    listSort();
                    break;
                case 18:
                    ch.cipherXOR("out_list.txt", "out_list_enc.txt");
                    break;
                case 19:
                    ch.cipherXOR("out_list_enc.txt", "out_list.txt");
                    break;
                case 20:
                    arch.createZip("out.zip");
                    break;
                case 21:
                    arch.readZip("out.zip");
                    break;
                case 22:
                    arch.createJar("boats.jar");
                    break;
                case 23:
                    arch.readJar("boats.jar");
                    break;
                case 24:
                    exit = true;
                    break;
                default:
                    System.out.println("Wrong input, repeat");
                    break;
            }
        }
    }
}
