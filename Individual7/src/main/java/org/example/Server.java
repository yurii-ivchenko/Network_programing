package org.example;

import java.io.*;
import java.net.*;
import java.time.Instant;

public class Server {
    public static void main(String[] args) throws IOException {
        ServerSocket serverSocket = new ServerSocket(5000);
        System.out.println("Server started on port 5000");

        while (true) {
            Socket clientSocket = serverSocket.accept();
            new Thread(() -> handleClient(clientSocket)).start();
        }
    }

    private static void handleClient(Socket socket) {
        try (BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
             PrintWriter out = new PrintWriter(socket.getOutputStream(), true)) {

            String input = in.readLine();
            Instant start = Instant.now();

            String result = input.toUpperCase();

            Instant end = Instant.now();
            long time = end.toEpochMilli() - start.toEpochMilli();

            out.println(result + " | Time: " + time + " ms");

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
