package com.example;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.util.ArrayList;
import java.util.List;

public class DownloadManager {
    private final List<DownloadTask> tasks = new ArrayList<>();
    private final DefaultTableModel model;

    public DownloadManager() {
        model = new DefaultTableModel(new Object[]{"URL", "File", "Progress", "Status"}, 0);
    }

    public JTable getTable() {
        return new JTable(model);
    }

    public void addDownload() {
        String url = JOptionPane.showInputDialog("Enter file URL:");
        String file = JOptionPane.showInputDialog("Enter output file name:");
        DownloadTask task = new DownloadTask(url, file, model);
        tasks.add(task);
        model.addRow(new Object[]{url, file, "0%", "Pending"});
    }

    public void startAll() {
        tasks.forEach(DownloadTask::start);
    }

    public void stopAll() {
        tasks.forEach(DownloadTask::pause);
    }

    public void resumeAll() {
        tasks.forEach(DownloadTask::resume);
    }
}
