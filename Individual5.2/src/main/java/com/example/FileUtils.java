package com.example;

import java.io.File;
import java.io.FileInputStream;
import java.net.URL;
import java.security.MessageDigest;

public class FileUtils {
    public static boolean fileExistsAndMatches(String urlString, String outputFile) {
        try {
            File file = new File(outputFile);
            if (!file.exists()) return false;

            String localHash = getMD5(file);

            long localSize = file.length();
            long remoteSize = new URL(urlString).openConnection().getContentLengthLong();

            return localSize == remoteSize && localHash != null;
        } catch (Exception e) {
            return false;
        }
    }

    private static String getMD5(File file) {
        try (FileInputStream fis = new FileInputStream(file)) {
            MessageDigest md = MessageDigest.getInstance("MD5");
            byte[] buffer = new byte[4096];
            int bytesRead;
            while ((bytesRead = fis.read(buffer)) != -1) {
                md.update(buffer, 0, bytesRead);
            }
            byte[] digest = md.digest();
            StringBuilder sb = new StringBuilder();
            for (byte b : digest) {
                sb.append(String.format("%02x", b));
            }
            return sb.toString();
        } catch (Exception e) {
            return null;
        }
    }
}
