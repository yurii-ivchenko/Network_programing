package org.example;

import java.io.*;
import java.net.*;
import java.util.Random;

public class ClientSession implements Runnable {
    private final int id;
    private final ClientResultTableModel tableModel;

    public ClientSession(int id, ClientResultTableModel tableModel) {
        this.id = id;
        this.tableModel = tableModel;
    }

    @Override
    public void run() {
        try (Socket socket = new Socket("localhost", 5000);
             PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
             BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()))) {

            String request = generateRandomString(8);
            out.println(request);

            String response = in.readLine();
            tableModel.addResult(id, request, response);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private String generateRandomString(int length) {
        String chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
        Random random = new Random();
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < length; i++) {
            sb.append(chars.charAt(random.nextInt(chars.length())));
        }
        return sb.toString();
    }
}
