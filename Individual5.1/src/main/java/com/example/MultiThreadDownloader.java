package com.example;

import java.io.RandomAccessFile;
import java.net.URL;
import java.net.URLConnection;

public class MultiThreadDownloader {
    private static final int THREAD_COUNT = 4; // кількість потоків

    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Usage: java MultiThreadDownloader <URL> <outputFile>");
            return;
        }

        String urlString = args[0];
        String outputFile = args[1];

        try {
            URL url = new URL(urlString);
            URLConnection connection = url.openConnection();
            connection.setRequestProperty("User-Agent", "Mozilla/5.0");

            int fileSize = connection.getContentLength();
            System.out.println("File size: " + fileSize + " bytes");

            RandomAccessFile raf = new RandomAccessFile(outputFile, "rw");
            raf.setLength(fileSize);
            raf.close();

            int partSize = fileSize / THREAD_COUNT;

            for (int i = 0; i < THREAD_COUNT; i++) {
                int start = i * partSize;
                int end = (i == THREAD_COUNT - 1) ? fileSize - 1 : (start + partSize - 1);

                Thread t = new Thread(new DownloadTask(urlString, outputFile, start, end, i));
                t.start();
            }

        } catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}
