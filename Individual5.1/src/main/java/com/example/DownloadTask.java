package com.example;

import java.io.RandomAccessFile;
import java.net.URL;
import java.net.URLConnection;

public class DownloadTask implements Runnable {
    private final String urlString;
    private final String outputFile;
    private final int start;
    private final int end;
    private final int id;

    public DownloadTask(String urlString, String outputFile, int start, int end, int id) {
        this.urlString = urlString;
        this.outputFile = outputFile;
        this.start = start;
        this.end = end;
        this.id = id;
    }

    @Override
    public void run() {
        try {
            URL url = new URL(urlString);
            URLConnection connection = url.openConnection();
            connection.setRequestProperty("User-Agent", "Mozilla/5.0");
            connection.setRequestProperty("Range", "bytes=" + start + "-" + end);

            try (RandomAccessFile raf = new RandomAccessFile(outputFile, "rw")) {
                raf.seek(start);
                byte[] buffer = connection.getInputStream().readAllBytes();
                raf.write(buffer);
            }

            System.out.println("Thread " + id + " finished downloading range " + start + "-" + end);
        } catch (Exception e) {
            System.out.println("Thread " + id + " error: " + e.getMessage());
        }
    }
}
