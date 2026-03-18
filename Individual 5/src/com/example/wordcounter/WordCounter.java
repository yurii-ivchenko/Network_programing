package com.example.wordcounter;

import java.util.regex.Pattern;

public class WordCounter {
    private final String text;

    public WordCounter(String text) {
        this.text = text;
    }

    public int countWords() {
        String[] words = Pattern.compile("\\s+").split(text.trim());
        int count = 0;
        for (String word : words) {
            if (!word.isEmpty()) {
                count++;
            }
        }
        return count;
    }
}