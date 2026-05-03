package com.example;

public class HtmlTextExtractor {
    private final String html;

    public HtmlTextExtractor(String html) {
        this.html = html;
    }

    public String extractText() {
        return html.replaceAll("<[^>]*>", " ");
    }
}
