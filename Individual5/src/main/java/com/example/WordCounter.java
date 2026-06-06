package com.example;

import java.util.regex.Pattern;

public class WordCounter {
    private final String text;

    public WordCounter(String text) {
        this.text = text;
    }

    public int countWords() {
        String cleaned = text.trim();
        if (cleaned.isEmpty()) return 0;
        String[] words = Pattern.compile("\\s+").split(cleaned);
        return words.length;
    }
}
