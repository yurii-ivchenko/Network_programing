package com.example.wordcounter;

public class Main {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java -jar wordcounter.jar <URL>");
            return;
        }

        String url = args[0];
        try {
            HtmlFetcher fetcher = new HtmlFetcher(url);
            String html = fetcher.fetch();

            HtmlCleaner cleaner = new HtmlCleaner(html);
            String text = cleaner.clean();

            WordCounter counter = new WordCounter(text);
            int count = counter.countWords();

            System.out.println("Word Count: " + count);
        } catch (Exception e) {
            System.err.println("Error: " + e.getMessage());
        }
    }
}
