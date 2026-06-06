package com.example;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.net.URL;
import java.net.URLConnection;

public class WebPageReader {
    private final String urlString;

    public WebPageReader(String urlString) {
        this.urlString = urlString;
    }

    public String readContent() throws Exception {
        StringBuilder content = new StringBuilder();
        URL url = new URL(urlString);
        URLConnection connection = url.openConnection();
        connection.setRequestProperty("User-Agent", "Mozilla/5.0"); // важливо!

        BufferedReader in = new BufferedReader(new InputStreamReader(connection.getInputStream()));

        String inputLine;
        while ((inputLine = in.readLine()) != null) {
            content.append(inputLine).append(" ");
        }
        in.close();
        return content.toString();
    }
}
