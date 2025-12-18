package org.example;

import java.io.*;

public class CipherHandler {
    private final String ENCRYPTION_KEY = "1234";

    public void cipherXOR(String inputFile, String outputFile) {
        try (FileInputStream fis = new FileInputStream(inputFile);
             FileOutputStream fos = new FileOutputStream(outputFile)) {
            byte[] key_bytes = ENCRYPTION_KEY.getBytes();
            int key_index = 0;
            int data;
            while ((data = fis.read()) != -1) {
                byte encryptedByte = (byte) (data ^ key_bytes[key_index]);
                fos.write(encryptedByte);
                key_index = (key_index + 1) % key_bytes.length;
            }
        }
        catch (IOException e) {
            e.printStackTrace();
        }
    }
}
