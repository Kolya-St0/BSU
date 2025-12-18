package org.example;

import java.io.*;
import java.util.jar.*;
import java.util.zip.*;

public class Archiver {
    public void createZip(String zip_filename) {
        String[] files_to_archive = {"out_list.txt", "out_map.txt", "out_list.xml", "out_list.json"};
        try (ZipOutputStream zout = new ZipOutputStream(new FileOutputStream(zip_filename))) {
            for (String filename : files_to_archive) {
                File file = new File(filename);
                if (file.exists()) {
                    try (FileInputStream fis = new FileInputStream(filename)) {
                        ZipEntry entry = new ZipEntry(filename);
                        zout.putNextEntry(entry);

                        byte[] buffer = new byte[fis.available()];
                        fis.read(buffer);
                        zout.write(buffer);
                        zout.closeEntry();
                    }
                }
                else {
                    System.out.println("File " + filename + " not found");
                }
            }
        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void readZip(String zip_filename) {
        try (ZipInputStream zin = new ZipInputStream(new FileInputStream(zip_filename))) {
            ZipEntry entry;
            String name;
            while ((entry = zin.getNextEntry()) != null) {
                name = entry.getName();
                System.out.printf("File name: %s \n", name);

                FileOutputStream fout = new FileOutputStream("new_" + name);
                for (int c = zin.read(); c != -1; c = zin.read()) {
                    fout.write(c);
                }
                fout.flush();
                zin.closeEntry();
                fout.close();
            }

        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void createJar(String jar_filename) {
        String[] files_to_archive = {
                "src/main/java/org/example/Main.java",
                "src/main/java/org/example/Menu.java",
                "src/main/java/org/example/Boat.java",
                "src/main/java/org/example/BoatList.java",
                "src/main/java/org/example/BoatMap.java",
                "src/main/java/org/example/FileHandler.java",
                "src/main/java/org/example/AbstractBoat.java",
                "src/main/java/org/example/AbstractBoatStorage.java",
                "src/main/java/org/example/CipherHandler.java",
                "src/main/java/org/example/Archiver.java"};
        try {
            Manifest manifest = new Manifest();
            manifest.getMainAttributes().put(Attributes.Name.MANIFEST_VERSION, "1.0");
            manifest.getMainAttributes().put(Attributes.Name.MAIN_CLASS, "org.example.Main");

            try (JarOutputStream jos = new JarOutputStream(new FileOutputStream(jar_filename), manifest)) {
                for (String filename : files_to_archive) {
                    File file = new File(filename);
                    if (file.exists()) {
                        try (FileInputStream fis = new FileInputStream(filename)) {
                            JarEntry jarEntry = new JarEntry(filename);
                            jos.putNextEntry(jarEntry);

                            byte[] buffer = new byte[fis.available()];
                            fis.read(buffer);
                            jos.write(buffer);
                            jos.closeEntry();
                        }
                    } else {
                        System.out.println("File " + filename + " not found");
                    }
                }
            }

        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void readJar(String jar_filename) {
        try (JarInputStream jis = new JarInputStream(new FileInputStream(jar_filename))) {
            JarEntry entry;
            while ((entry = jis.getNextJarEntry()) != null) {
                String name = entry.getName();
                System.out.printf("File: %s \n", name);
                jis.closeEntry();
            }
        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }
}
