package com.example.wordcounter;

import org.jsoup.Jsoup;

public class HtmlCleaner {
    private final String html;

    public HtmlCleaner(String html) {
        this.html = html;
    }

    public String clean() {
        return Jsoup.parse(html).text();
    }
}