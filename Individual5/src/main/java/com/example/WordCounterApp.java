package com.example;

public class WordCounterApp {
    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Usage: java -jar word-counter.jar <URL>");
            return;
        }

        try {
            String urlString = args[0];
            WebPageReader reader = new WebPageReader(urlString);

            String htmlContent = reader.readContent();
            HtmlTextExtractor extractor = new HtmlTextExtractor(htmlContent);
            String plainText = extractor.extractText();

            WordCounter counter = new WordCounter(plainText);
            int wordCount = counter.countWords();

            System.out.println("Word Count: " + wordCount);
        } catch (Exception e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}
