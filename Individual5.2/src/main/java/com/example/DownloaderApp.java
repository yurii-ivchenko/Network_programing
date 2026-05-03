package com.example;

import javax.swing.*;
import java.awt.*;

public class DownloaderApp extends JFrame {
    private final DownloadManager manager;

    public DownloaderApp() {
        super("Multi-threaded Downloader");
        manager = new DownloadManager();

        setLayout(new BorderLayout());
        JTable table = manager.getTable();
        add(new JScrollPane(table), BorderLayout.CENTER);

        JPanel controls = new JPanel();
        JButton addBtn = new JButton("Add File");
        JButton startBtn = new JButton("Start");
        JButton stopBtn = new JButton("Stop");
        JButton resumeBtn = new JButton("Resume");

        controls.add(addBtn);
        controls.add(startBtn);
        controls.add(stopBtn);
        controls.add(resumeBtn);
        add(controls, BorderLayout.SOUTH);

        addBtn.addActionListener(e -> manager.addDownload());
        startBtn.addActionListener(e -> manager.startAll());
        stopBtn.addActionListener(e -> manager.stopAll());
        resumeBtn.addActionListener(e -> manager.resumeAll());

        setSize(600, 400);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setVisible(true);
    }

    public static void main(String[] args) {
        SwingUtilities.invokeLater(DownloaderApp::new);
    }
}
