package com.example.wordcounter;

import org.jsoup.Jsoup;

public class HtmlFetcher {
    private final String url;

    public HtmlFetcher(String url) {
        this.url = url;
    }

    public String fetch() throws Exception {
        return Jsoup.connect(url).get().html();
    }
}
