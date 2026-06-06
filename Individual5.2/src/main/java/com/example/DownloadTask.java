package com.example;

import javax.swing.table.DefaultTableModel;
import java.io.RandomAccessFile;
import java.net.HttpURLConnection;
import java.net.URL;

public class DownloadTask implements Runnable {
    private final String urlString;
    private final String outputFile;
    private final DefaultTableModel model;
    private Thread thread;
    private volatile boolean paused = false;
    private volatile boolean completed = false;
    private int downloaded = 0;
    private int fileSize = -1;

    public DownloadTask(String urlString, String outputFile, DefaultTableModel model) {
        this.urlString = urlString;
        this.outputFile = outputFile;
        this.model = model;
    }

    public void start() {
        if (completed) return;
        thread = new Thread(this);
        thread.start();
    }

    public void pause() {
        paused = true;
    }

    public void resume() {
        paused = false;
        if (thread == null || !thread.isAlive()) {
            start();
        }
    }

    @Override
    public void run() {
        try {
            // Перевірка чи файл вже існує і збігається
            if (FileUtils.fileExistsAndMatches(urlString, outputFile)) {
                updateStatus("Already exists");
                completed = true;
                return;
            }

            HttpURLConnection connection = (HttpURLConnection) new URL(urlString).openConnection();
            connection.setRequestProperty("User-Agent", "Mozilla/5.0");
            if (downloaded > 0) {
                connection.setRequestProperty("Range", "bytes=" + downloaded + "-");
            }
            fileSize = connection.getContentLength();

            try (RandomAccessFile raf = new RandomAccessFile(outputFile, "rw")) {
                raf.seek(downloaded);
                byte[] buffer = new byte[4096];
                int bytesRead;
                var in = connection.getInputStream();

                while ((bytesRead = in.read(buffer)) != -1) {
                    if (paused) {
                        updateStatus("Paused");
                        return;
                    }
                    raf.write(buffer, 0, bytesRead);
                    downloaded += bytesRead;
                    int progress = (int) ((downloaded / (double) fileSize) * 100);
                    updateProgress(progress);
                }
            }

            updateStatus("Completed");
            completed = true;
        } catch (Exception e) {
            updateStatus("Error");
        }
    }

    private void updateProgress(int progress) {
        int row = model.getRowCount() - 1;
        model.setValueAt(progress + "%", row, 2);
    }

    private void updateStatus(String status) {
        int row = model.getRowCount() - 1;
        model.setValueAt(status, row, 3);
    }
}
